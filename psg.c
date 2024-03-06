
#include "psg.h"
#include "TYPES.H"
#include "osbind.h"

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
    /*long old_ssp = Super(0);*/

    unsigned int value = MASTER_CLOCK / (16 * frequency);

    *PSG_reg_select = channel * 2;
    *PSG_reg_write = value & 0xFF; 

    *PSG_reg_select = (channel * 2) + 1; 
    *PSG_reg_write = (value >> 8) & 0x0F; 
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

    volatile char *PSG_reg_select = SELECT_REGISTER;
    volatile char *PSG_reg_write  = WRITE_REGISTER;

    *PSG_reg_select = VOLUME_OFFSET + channel;
    *PSG_reg_write = volume & 0x0F; 
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

    volatile char *PSG_reg_select = SELECT_REGISTER;
    volatile char *PSG_reg_write  = WRITE_REGISTER;
    
    int toneBit = 0 + channel; 
    int noiseBit = 3 + channel; 

    if (toneOn) {
        MIXER_MASK &= ~(1 << toneBit); 
    } else {
        MIXER_MASK |= (1 << toneBit);
    }

    if (noiseOn) {
        MIXER_MASK &= ~(1 << noiseBit); 
    } else {
        MIXER_MASK |= (1 << noiseBit); 
    }

    *PSG_reg_select = 7;
    *PSG_reg_write = MIXER_MASK;
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

    volatile char *PSG_reg_select = SELECT_REGISTER;
    volatile char *PSG_reg_write  = WRITE_REGISTER;

    *PSG_reg_select = VOLUME_OFFSET;
    *PSG_reg_write = volume & 0x0F;

    *PSG_reg_select = VOLUME_OFFSET + CHANNEL_B;
    *PSG_reg_write = volume & 0x0F;

    *PSG_reg_select = VOLUME_OFFSET + CHANNEL_C;
    *PSG_reg_write = volume & 0x0F;
}


