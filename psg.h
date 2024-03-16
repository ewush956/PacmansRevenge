

/*************
* This file contains the definitions used for generating the 8-bit music and sound effects
*
****************/

#include "TYPES.H"
#include <osbind.h>

#define MASTER_CLOCK 2457600

#define CHANNEL_A 0
#define CHANNEL_B 1
#define CHANNEL_C 2
#define MIXER_OFFSET 7
#define VOLUME_OFFSET 8

#define VOLUME_MASK 0x0F
#define CHANNEL_MASK 0x03
#define MIXER_MASK 0x38

#define TONE_ON 1
#define NOISE_ON 1

#define TONE_OFF 0
#define NOISE_OFF 0

#define SELECT_REGISTER 0xFF8800
#define WRITE_REGISTER 0xFF8802

#define NUM_NOTES 12
#define FIRST_OCTAVE 0
#define SECOND_OCTAVE 1
#define THIRD_OCTAVE 2
#define FOURTH_OCTAVE 3
#define FIFTH_OCTAVE 4
#define SIXTH_OCTAVE 5
#define SEVENTH_OCTAVE 6
#define EIGHTH_OCTAVE 7

#define WHOLE_NOTE 32
#define HALF_NOTE 16
#define QUARTER_NOTE 8
#define EIGHTH_NOTE 4
#define SIXTEENTH_NOTE 2
#define THIRTY_SECOND_NOTE 1

#define C1 0xD5D
#define C1_SHARP 0xC9C
#define D1 0xBE7
#define D1_SHARP 0xB3C
#define E1 0xA9B
#define F1 0xA02
#define F1_SHARP 0x973
#define G1 0x8EB
#define G1_SHARP 0x86B
#define A1 0x7F2
#define A1_SHARP 0x780
#define B1 0x714

#define C2 (C1 >> SECOND_OCTAVE)
#define C2_SHARP (C1_SHARP >> SECOND_OCTAVE)
#define D2 (D1 >> SECOND_OCTAVE)
#define D2_SHARP (D1_SHARP >> SECOND_OCTAVE)
#define E2 (E1 >> SECOND_OCTAVE)
#define F2 (F1 >> SECOND_OCTAVE)
#define F2_SHARP (F1_SHARP >> SECOND_OCTAVE)
#define G2 (G1 >> SECOND_OCTAVE)
#define G2_SHARP (G1_SHARP >> SECOND_OCTAVE)
#define A2 (A1 >> SECOND_OCTAVE)
#define A2_SHARP (A1_SHARP >> SECOND_OCTAVE)
#define B2 (B1 >> SECOND_OCTAVE)

#define C3 (C1 >> THIRD_OCTAVE)
#define C3_SHARP (C1_SHARP >> THIRD_OCTAVE)
#define D3 (D1 >> THIRD_OCTAVE)
#define D3_SHARP (D1_SHARP >> THIRD_OCTAVE)
#define E3 (E1 >> THIRD_OCTAVE)
#define F3 (F1 >> THIRD_OCTAVE)
#define F3_SHARP (F1_SHARP >> THIRD_OCTAVE)
#define G3 (G1 >> THIRD_OCTAVE)
#define G3_SHARP (G1_SHARP >> THIRD_OCTAVE)
#define A3 (A1 >> THIRD_OCTAVE)
#define A3_SHARP (A1_SHARP >> THIRD_OCTAVE)
#define B3 (B1 >> THIRD_OCTAVE)

#define C4 (C1 >> FOURTH_OCTAVE)
#define C4_SHARP (C1_SHARP >> FOURTH_OCTAVE)
#define D4 (D1 >> FOURTH_OCTAVE)
#define D4_SHARP (D1_SHARP >> FOURTH_OCTAVE)
#define E4 (E1 >> FOURTH_OCTAVE)
#define F4 (F1 >> FOURTH_OCTAVE)
#define F4_SHARP (F1_SHARP >> FOURTH_OCTAVE)
#define G4 (G1 >> FOURTH_OCTAVE)
#define G4_SHARP (G1_SHARP >> FOURTH_OCTAVE)
#define A4 (A1 >> FOURTH_OCTAVE)
#define A4_SHARP (A1_SHARP >> FOURTH_OCTAVE)
#define B4 (B1 >> FOURTH_OCTAVE)

#define C5 (C1 >> FIFTH_OCTAVE)
#define C5_SHARP (C1_SHARP >> FIFTH_OCTAVE)
#define D5 (D1 >> FIFTH_OCTAVE)
#define D5_SHARP (D1_SHARP >> FIFTH_OCTAVE)
#define E5 (E1 >> FIFTH_OCTAVE)
#define F5 (F1 >> FIFTH_OCTAVE)
#define F5_SHARP (F1_SHARP >> FIFTH_OCTAVE)
#define G5 (G1 >> FIFTH_OCTAVE)
#define G5_SHARP (G1_SHARP >> FIFTH_OCTAVE)
#define A5 (A1 >> FIFTH_OCTAVE)
#define A5_SHARP (A1_SHARP >> FIFTH_OCTAVE)
#define B5 (B1 >> FIFTH_OCTAVE)

#define C6 (C1 >> SIXTH_OCTAVE)
#define C6_SHARP (C1_SHARP >> SIXTH_OCTAVE)
#define D6 (D1 >> SIXTH_OCTAVE)
#define D6_SHARP (D1_SHARP >> SIXTH_OCTAVE)
#define E6 (E1 >> SIXTH_OCTAVE)
#define F6 (F1 >> SIXTH_OCTAVE)
#define F6_SHARP (F1_SHARP >> SIXTH_OCTAVE)
#define G6 (G1 >> SIXTH_OCTAVE)
#define G6_SHARP (G1_SHARP >> SIXTH_OCTAVE)
#define A6 (A1 >> SIXTH_OCTAVE)
#define A6_SHARP (A1_SHARP >> SIXTH_OCTAVE)
#define B6 (B1 >> SIXTH_OCTAVE)

#define C7 (C1 >> SEVENTH_OCTAVE)
#define C7_SHARP (C1_SHARP >> SEVENTH_OCTAVE)
#define D7 (D1 >> SEVENTH_OCTAVE)
#define D7_SHARP (D1_SHARP >> SEVENTH_OCTAVE)
#define E7 (E1 >> SEVENTH_OCTAVE)
#define F7 (F1 >> SEVENTH_OCTAVE)
#define F7_SHARP (F1_SHARP >> SEVENTH_OCTAVE)
#define G7 (G1 >> SEVENTH_OCTAVE)
#define G7_SHARP (G1_SHARP >> SEVENTH_OCTAVE)
#define A7 (A1 >> SEVENTH_OCTAVE)
#define A7_SHARP (A1_SHARP >> SEVENTH_OCTAVE)
#define B7 (B1 >> SEVENTH_OCTAVE)

void set_note_frequency(int channel, float frequency);
void set_tone(int channel, int tuning);
void enable_channel(int channel, int toneOn, int noiseOn);
void set_volume(int channel, unsigned char volume);
void set_master_volume(unsigned char volume);
void play_note(int channel, int tuning, unsigned char volume);
void stop_sound();

