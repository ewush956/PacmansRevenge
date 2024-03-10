# 1 "effects.c" 1
# 1 "./effects.h" 1
# 1 "./TYPES.H" 1



typedef unsigned char UCHAR8;
typedef unsigned int  UINT16;
typedef unsigned long ULONG32;

typedef signed char bool;
# 1 "./effects.h" 2
# 1 "./psg.h" 1
# 1 "./TYPES.H" 1
# 1 "./psg.h" 2
# 1 "C:/c68/include/osbind.h" 1
# 1 "C:/c68/include/compiler.h" 1
# 9 "C:/c68/include/osbind.h" 2
# 1 "C:/c68/include/ostruct.h" 1
# 22 "C:/c68/include/ostruct.h"
typedef struct {
    long b_free;
    long b_total;
    long b_secsiz;
    long b_clsiz;
} _DISKINFO;


typedef struct {
  short time;
  short date;
} _DOSTIME;


typedef struct
{
        unsigned char maxlen;
        unsigned char actuallen;
        char    buffer[255];
} _CCONLINE;
# 48 "C:/c68/include/ostruct.h"
typedef struct _dta {
    char 	    dta_buf[21];
    char            dta_attribute;
    unsigned short  dta_time;
    unsigned short  dta_date;
    long            dta_size;
    char            dta_name[14];
} _DTA;
# 98 "C:/c68/include/ostruct.h"
typedef struct {
  short recsiz;
  short clsiz;
  short clsizb;
  short rdlen;
  short fsiz;
  short fatrec;
  short datrec;
  short numcl;
  short bflags;
} _BPB;




typedef struct _md {
    struct _md	*md_next;
    long	 md_start;
    long	 md_length;
    long	 md_owner;
} _MD;


typedef struct {
    _MD *mp_free;
    _MD *mp_used;
    _MD *mp_rover;
} _MPB;
# 141 "C:/c68/include/ostruct.h"
typedef struct {
    char    *ibuf;
    short   ibufsiz;
    volatile short   ibufhd;
    volatile short   ibuftl;
    short   ibuflow;
    short   ibufhi;
} _IOREC;


typedef struct {
	char	topmode;
	char	buttons;
	char	xparam;
	char	yparam;
	short	xmax;
	short	ymax;
	short	xstart;
	short	ystart;
} _PARAM;


typedef struct {
    void    (*midivec)	(void) ;
    void    (*vkbderr)	(void) ;
    void    (*vmiderr)	(void) ;
    void    (*statvec)	(void *) ;
    void    (*mousevec)	(void *) ;
    void    (*clockvec)	(void *) ;
    void    (*joyvec)	(void *) ;
    long    (*midisys)	(void) ;
    long    (*ikbdsys)	(void) ;
    char    kbstate;
} _KBDVECS;


typedef struct {
    void *unshift;
    void *shift;
    void *caps;
} _KEYTAB;


typedef struct
{
        void    *pb_scrptr;
        int     pb_offset;
        int     pb_width;
        int     pb_height;
        int     pb_left;
        int     pb_right;
        int     pb_screz;
        int     pb_prrez;
        void    *pb_colptr;
        int     pb_prtype;
        int     pb_prport;
        void    *pb_mask;
} _PBDEF;
# 17 "C:/c68/include/osbind.h" 2
# 33 "C:/c68/include/osbind.h"
 long _trap_1_w		(short) ;
 long _trap_1_ww	(short,short) ;
 long _trap_1_wl	(short,long) ;
 long _trap_1_wlw	(short,long,short) ;
 long _trap_1_wwll	(short,short,long,long) ;
 long _trap_1_wlww	(short,long,short,short) ;
 long _trap_1_www	(short,short,short) ;
 long _trap_1_wll	(short,long,long) ;
 long _trap_1_wwlll	(short,short,long,long,long) ;
 long _trap_1_wwwll	(short,short,short,long,long) ;
 long _trap_13_wl	(short,long) ;
 long _trap_13_w	(short) ;
 long _trap_13_ww	(short,short) ;
 long _trap_13_www	(short,short,short) ;
 long _trap_13_wwlwww	(short,short,long,short,short,short) ;
 long _trap_13_wwl	(short,short,long) ;
 long _trap_14_wwl	(short,short,long) ;
 long _trap_14_wwll	(short,short,long,long) ;
 long _trap_14_ww	(short,short) ;
 long _trap_14_w	(short) ;
 long _trap_14_wllw	(short,long,long,short) ;
 long _trap_14_wl	(short,long) ;
 long _trap_14_www	(short,short,short) ;
 long _trap_14_wllwwwww (short,long,long,short,short,short,short,short) ;
 long _trap_14_wllwwwwlw (short,long,long,short,short,short,short,long,short) ;
 long _trap_14_wllwwwwwlw (short,long,long,short,short,short,short,short,long,short) ;
 long _trap_14_wwwwwww	(short,short,short,short,short,short,short) ;
 long _trap_14_wlll	(short,long,long,long) ;
 long _trap_14_wllww	(short,long,long,short,short) ;
 long _trap_14_wwwwl	(short,short,short,short,long) ;
 long _trap_14_wwwl	(short,short,short,long) ;
 long _trap_14_wlwlw	(short,long,short,long,short) ;
# 103 "C:/c68/include/osbind.h"
 long _trap_1_ 	(short,...) ;
 long _trap_14_ 	(short,...) ;
 long _trap_13_ 	(short,...) ;
# 2 "./psg.h" 2
# 133 "./psg.h"
void set_note_frequency(int channel, float frequency);
void set_tone(int channel, int tuning);
void enable_channel(int channel, int toneOn, int noiseOn);
void set_volume(int channel, unsigned char volume);
void set_master_volume(unsigned char volume);
void play_note(int channel, int tuning, unsigned char volume);
void stop_sound();
# 2 "./effects.h" 2




typedef struct {
    int frequency;
    int volume;
    int duration;
}SoundCycle;

typedef struct {
    int current_sound_index;
    int sound_time_left;
}SoundState;

extern const SoundCycle waka_sound_cycle[14 ];
extern const SoundCycle waka_noise_cycle[14 ];

bool play_waka_sound(int channel, const SoundCycle sound_cycle[], int cycle_length, SoundState *state);
# 1 "effects.c" 2
# 1 "./psg.h" 1
# 1 "./TYPES.H" 1
# 1 "./psg.h" 2
# 1 "C:/c68/include/osbind.h" 1
# 2 "./psg.h" 2
# 133 "./psg.h"
void set_note_frequency(int channel, float frequency);
void set_tone(int channel, int tuning);
void enable_channel(int channel, int toneOn, int noiseOn);
void set_volume(int channel, unsigned char volume);
void set_master_volume(unsigned char volume);
void play_note(int channel, int tuning, unsigned char volume);
void stop_sound();
# 2 "effects.c" 2
# 1 "./TYPES.H" 1
# 3 "effects.c" 2





const SoundCycle waka_sound_cycle[14 ] = {
    {(0xA9B  >> 3 ) , 12 , 1 },
    {(0x86B  >> 3 ) , 12 , 1 },
    {(0xD5D  >> 4 ) , 12 , 1 },
    {(0xB3C  >> 4 ) , 12 , 1 },
    {(0x973  >> 4 ) , 12 , 1 },
    {(0x780  >> 4 ) , 12 , 1 },

    {0xA9B , 0, 2 },

    {(0x714  >> 4 ) , 12 , 1 },
    {(0x8EB  >> 4 ) , 12 , 1 },
    {(0xA9B  >> 4 ) , 12 , 1 },
    {(0xC9C  >> 4 ) , 12 , 1 },
    {(0x7F2  >> 3 ) , 12 , 1 },
    {(0xA02  >> 3 ) , 12 , 1 },
    {0xA9B , 0, 2 }
};
const SoundCycle waka_noise_cycle[14 ] = {
    {(0xA9B  >> 2 ) , 14 , 1 },
    {(0x86B  >> 2 ) , 14 , 1 },
    {(0xD5D  >> 3 ) , 14 , 1 },
    {(0xB3C  >> 3 ) , 14 , 1 },
    {(0x973  >> 3 ) , 14 , 1 },
    {(0x780  >> 3 ) , 14 , 1 },

    {0xA9B , 0, 2 },

    {(0x714  >> 3 ) , 14 , 1 },
    {(0x8EB  >> 3 ) , 14 , 1 },
    {(0xA9B  >> 3 ) , 14 , 1 },
    {(0xC9C  >> 3 ) , 14 , 1 },
    {(0x7F2  >> 2 ) , 14 , 1 },
    {(0xA02  >> 2 ) , 14 , 1 },
    {0xA9B , 0, 2 }
};

bool play_waka_sound(int channel, const SoundCycle sound_cycle[], int cycle_length, SoundState *state) {
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
            return -1 ;
        }
    }
    (*time_left)--;
    return 0 ;
}
