
#include "psg.h"
#include "TYPES.H"
#include "osbind.h"

unsigned char read_psg(int reg);

/******************************************
* Function Name: set_note_frequency
* Purpose: Sets the frequency of a note for a specified PSG channel. 
*          This function calculates the appropriate register values based on the
*          input frequency and updates the PSG registers to produce the desired tone.
* Parameters:
*     - @param channel (int): The PSG channel to set the frequency for. Valid
*       channels are 0 (Channel A), 1 (Channel B), and 2 (Channel C).
*     - @param frequency (float): The frequency of the note in Hertz (Hz). This
*       value is used to calculate the PSG register settings.
* Returns: void 
******************************************/
void set_note_frequency(int channel, float frequency) {

    volatile char *PSG_reg_select = SELECT_REGISTER;
    volatile char *PSG_reg_write  = WRITE_REGISTER;

    unsigned int value = MASTER_CLOCK / (frequency * 16);

    write_psg(channel * 2, (value & 0x0F));
    write_psg((channel * 2) + 1, (value >> 8) & 0x0F);
}
/******************************************
* Function Name: set_tone
* Purpose: Sets the tone for a specified PSG channel. This function calculates
*          the appropriate register values based on the input frequency and
*          updates the PSG registers to produce the desired tone.
* Example Usage:  
*          set_tone(0, frequency);
* Parameters:
*     - @param channel (int): The PSG channel to set the frequency for. Valid
*       channels are 0 (Channel A), 1 (Channel B), and 2 (Channel C).
*     - @param frequency (float): The frequency of the note in Hertz (Hz). This
*       value is used to calculate the PSG register settings.
* Returns: void 
******************************************/
void set_tone(int channel, int tuning) {

    int fineTuneRegister = channel << 1; /* channel * 2*/    
    int coarseTuneRegister = fineTuneRegister + 1; 

    unsigned char fineTuneValue = tuning & 0xFF;         
    unsigned char coarseTuneValue = (tuning >> 8) & 0x0F;

    write_psg(fineTuneRegister, fineTuneValue);
    write_psg(coarseTuneRegister, coarseTuneValue);
}
/******************************************
* Function Name: set_volume 
* Purpose: Sets the volume for a given PSG channel.
*          This function updates the volume control register
*          for the specified channel to the desired volume level. 
*          The Atari PSG supports volume levels from
*          0 (silent) to 15 (maximum).
* Parameters:
*     - @param channel (int): The PSG channel to set the volume for. Valid
*       channels are 0 (Channel A), 1 (Channel B), and 2 (Channel C).
*     - @param volume (unsigned char): The volume level to set. Valid values are
*       from 0 (silent) to 15 (maximum volume).
* Returns: void
******************************************/
void set_volume(int channel, unsigned char volume) {
    write_psg(VOLUME_OFFSET + channel, (volume & 0x0F));
}
/******************************************
* Function Name: enableChannel
* Purpose: Enables or disables tone and noise generation for a specific PSG channel.
* This function updates the mixer control register to enable or disable tone and noise
* for the given channel, allowing for precise control over the sound output.
* Parameters:
*     - @param channel (int): The PSG channel to modify. Valid channels are 0
*       (Channel A), 1 (Channel B), and 2 (Channel C).
*     - @param toneOn (int): Specifies whether to enable (1) or disable (0) the tone
*       generation for the specified channel.
*     - @param noiseOn int : Specifies whether to enable (1) or disable (0) the noise
*       generation for the specified channel.
* Returns: void
* Note: The mixer settings are global for the PSG, so this function may
*       affect the output of other channels depending on their current settings.
******************************************/
void enable_channel(int channel, int toneOn, int noiseOn) {

    static unsigned char mixer = MIXER_MASK; 
   /* unsigned char mixer = read_psg(MIXER_OFFSET); */
    int toneBit = 0 + channel; 
    int noiseBit = 3 + channel;

    if (toneOn == TONE_ON) {
        mixer &= ~(1 << toneBit); 
    } else {
        mixer |= (1 << toneBit);
    }

    if (noiseOn == NOISE_ON) {
        mixer &= ~(1 << noiseBit); 
    } else {
        mixer |= (1 << noiseBit); 
    }

    write_psg(MIXER_OFFSET, mixer);
}
/*************************************************************
 * Function Name: set_master_volume
 * Purpose: Sets the master volume for all channels (A, B, and C) 
 *          on the PSG (Programmable Sound Generator). This function 
 *          directly manipulates hardware registers to apply the volume 
 *          setting across all channels simultaneously.
 * Parameters:
 *     - @param volume (unsigned char): The desired volume level to be set 
 *       across all channels. This value should be in the range of 
 *       0 (silent) to 15 (maximum volume), as only the lower 4 bits 
 *       are used (0x0F mask).
 * Usage:
 *     This function is called with a single byte representing the desired 
 *     volume level. It then accesses the PSG's registers through memory-mapped 
 *     IO to set the volume for each of the three channels to the specified level.
 *     Example usage: set_master_volume(10); 
 *************************************************************/
void set_master_volume(unsigned char volume){

    write_psg(VOLUME_OFFSET, volume);
    write_psg(VOLUME_OFFSET + CHANNEL_B, volume);
    write_psg(VOLUME_OFFSET + CHANNEL_C, volume);
}
/*************************************************************************
 * Plays a note on a specified channel with given tuning and volume.
 * 
 * @param channel The sound channel to play the note on. Valid channels depend on the hardware, typically 0, 1, or 2.
 * @param tuning The frequency tuning value of the note. This value should be compatible with the `set_tone` function.
 * @param volume The volume at which to play the note. Expected to be a value that `set_volume` can accept.
 */
void play_note(int channel, int tuning, unsigned char volume) {

    set_tone(channel, tuning);
    set_volume(channel, volume);
    /*enable_channel(channel, TONE_ON, NOISE_OFF); */
}
/*****************************************************************
 * Function Name: stop_sound
 * Purpose: Stops the sound by setting the master volume to 0.
 * Parameters: None
 * @returns void
 ******************************************************************/
void stop_sound() {
    set_master_volume(0);
}
bool play_sound(int channel, const SoundCycle sound_cycle[], int cycle_length, SoundState *state) {
    int index = state->current_sound_index;
    int* time_left = &state->sound_time_left;

    if (*time_left == 0) {
        if (index < cycle_length) {
            *time_left = sound_cycle[index].duration; 
            play_note(channel, sound_cycle[index].frequency, sound_cycle[index].volume); 
            state->current_sound_index++; 
        } else {
            stop_sound(); 
            state->current_sound_index = 0; 
            return TRUE; 
        }
    }
    (*time_left)--; 
    return FALSE; 
}
void set_envelope(int shape, unsigned int sustain) {
    write_psg(11, sustain);
    write_psg(12, sustain);
    write_psg(13, shape);
}
/********************************************************
 *              ~~~~ Helper function ~~~~
 * Function Name: write_psg
 * Writes a value to a specific register on the PSG.
 * @param reg (int): The register to write to.
 * @param val (UCHAR8): The value to write to the register.
 * @returns void
 *******************************************************/
void write_psg(int reg, UCHAR8 val) {

    volatile char *PSG_reg_select = SELECT_REGISTER;
    volatile char *PSG_reg_write  = WRITE_REGISTER;

    if (reg > -1 && reg < 16) {

        *PSG_reg_select = reg;
        *PSG_reg_write = val;
    }
}
unsigned char read_psg(int reg) {

    volatile char *PSG_reg_select = SELECT_REGISTER;
    volatile char *PSG_reg_read  = WRITE_REGISTER;

    if (reg >= 0 && reg <= 15) {

        *PSG_reg_select = reg;
        return *PSG_reg_read;
    }
    return 0;
}
