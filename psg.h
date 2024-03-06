#include "TYPES.H"
#include <osbind.h>

#define MASTER_CLOCK 2457600

#define CHANNEL_A 0
#define CHANNEL_B 1
#define CHANNEL_C 2
#define VOLUME_OFFSET 8

#define VOLUME_MASK 0x0F
#define CHANNEL_MASK 0x03

#define SELECT_REGISTER 0xFF8800
#define WRITE_REGISTER 0xFF8802

void set_note_frequency(int channel, float frequency);
void enable_channel(int channel, int toneOn, int noiseOn);
void set_volume(int channel, unsigned char volume);
void set_master_volume(unsigned char volume);

