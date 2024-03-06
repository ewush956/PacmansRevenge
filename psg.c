
#include "psg.h"
#include "TYPES.H"
#include "osbind.h"

void setNoteFrequency(int channel, float frequency) {

    volatile char *PSG_reg_select = 0xFF8800;
    volatile char *PSG_reg_write  = 0xFF8802;
    /*long old_ssp = Super(0);*/

    unsigned int value = MASTER_CLOCK / (16 * frequency);

    *PSG_reg_select = channel * 2;
    *PSG_reg_write = value & 0xFF; 

    *PSG_reg_select = (channel * 2) + 1; 
    *PSG_reg_write = (value >> 8) & 0x0F; 
    /*Upper 4 bits*/
}

