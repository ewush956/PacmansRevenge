#include "TYPES.H"
#include "psg.h"

#define BASS_VOLUME 15
#define TREBLE_VOLUME 14

typedef struct {
    int frequency;
    int duration;
    int volume;
}Note;

typedef struct {
    int current_note_index;
    int note_time_left;
}MusicState;

extern const Note notes[12];
extern const Note pacman_intro_treble[38];
extern const Note pacman_intro_bass[22];


int generate_frequency(int base_note, UCHAR8 target_octave);
void play_intro();
void play_jaws_theme();
void stop_music();
/*void update_music(int channel, const Note song[], int song_length);*/
bool update_music(int channel, const Note song[], int song_length, MusicState *state);

void update_song(int treble_channel, const Note treble_song[], int treble_song_length,
                 int bass_channel, const Note bass_song[], int bass_song_length,
                 int elapsed_time);