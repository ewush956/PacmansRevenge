#include "TYPES.H"
#include "osbind.h"

#define MASTER_CLOCK 2457600

#define CHANNEL_A 0
#define CHANNEL_B 1
#define CHANNEL_C 2

void setNoteFrequency(int channel, float frequency);
void enableChannel(int channel, int toneOn, int noiseOn);
void setVolume(int channel, unsigned char volume);

