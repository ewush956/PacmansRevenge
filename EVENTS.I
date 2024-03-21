# 1 "events.c" 1
# 1 "./bitmaps.h" 1
# 1 "./TYPES.H" 1



typedef unsigned char UCHAR8;
typedef unsigned int  UINT16;
typedef unsigned long ULONG32;

typedef signed char bool;
# 4 "./bitmaps.h" 2




extern const ULONG32* default_pacman_sprites[5 ][9];
extern const ULONG32* evil_pacman_sprites[5 ][9];
extern const ULONG32* crying_ghost_sprites[5 ][2];
extern const ULONG32* awkward_ghost_sprites[5 ][2];
extern const ULONG32* cyclops_ghost_sprites[5 ][2];
extern const ULONG32* moustache_ghost_sprites[5 ][2];
extern const ULONG32* frozen_ghost_sprites[5 ][2];
extern const ULONG32* running_ghost_sprites[5 ][2];

extern const ULONG32 evil_pac_up_2[32];
extern const ULONG32 evil_pac_down_1[32];
extern const ULONG32 pac_left_2[32];
extern const ULONG32 cyclops_ghost_down_2[32];
extern const ULONG32 evil_pac_up_3[32];
extern const ULONG32 pac_up_2[32];
extern const ULONG32 pac_left_3[32];
extern const ULONG32 evil_pac_down_4[32];
extern const ULONG32 pac_up_3[32];
extern const ULONG32 pac_left_1[32];
extern const ULONG32 evil_pac_left_2[32];
extern const ULONG32 cyclops_ghost_left_2[32];
extern const ULONG32 moustache_ghost_right_2[32];
extern const ULONG32 evil_pac_left_4[32];
extern const ULONG32 moustache_ghost_down_2[32];
extern const ULONG32 evil_pac_up_1[32];
extern const ULONG32 cyclops_ghost_right_2[32];
extern const ULONG32 moustache_ghost_up_2[32];
extern const ULONG32 crying_ghost_left_2[32];
extern const ULONG32 crying_ghost_down_2[32];
extern const ULONG32 pac_up_4[32];
extern const ULONG32 evil_pac_left_3[32];
extern const ULONG32 evil_pac_up_4[32];
extern const ULONG32 awkward_ghost_down_2[32];
extern const ULONG32 awkward_ghost_left_2[32];
extern const ULONG32 pac_left_4[32];
extern const ULONG32 cyclops_ghost_up_2[32];
extern const ULONG32 awkward_ghost_up_2[32];
extern const ULONG32 evil_pac_down_2[32];
extern const ULONG32 crying_ghost_right_2[32];
extern const ULONG32 moustache_ghost_left_2[32];
extern const ULONG32 evil_pac_left_1[32];
extern const ULONG32 pac_down_1[32];
extern const ULONG32 pac_down_2[32];
extern const ULONG32 crying_ghost_up_2[32];
extern const ULONG32 evil_pac_down_3[32];
extern const ULONG32 pac_down_4[32];
extern const ULONG32 pac_up_1[32];
extern const ULONG32 awkward_ghost_right_2[32];
extern const ULONG32 pac_down_3[32];


extern const ULONG32 pac_1[];
extern const ULONG32 pac_2[];
extern const ULONG32 pac_3[];
extern const ULONG32 pac_4[];

extern const ULONG32 evil_pac_1[];
extern const ULONG32 evil_pac_2[];
extern const ULONG32 evil_pac_3[];
extern const ULONG32 evil_pac_4[];

extern const ULONG32 moustache_ghost_up_1[];
extern const ULONG32 moustache_ghost_down_1[];
extern const ULONG32 moustache_ghost_left_1[];
extern const ULONG32 moustache_ghost_right_1[];

extern const ULONG32 awkward_ghost_up_1[];
extern const ULONG32 awkward_ghost_down_1[];
extern const ULONG32 awkward_ghost_left_1[];
extern const ULONG32 awkward_ghost_right_1[];

extern const ULONG32 crying_ghost_up_1[];
extern const ULONG32 crying_ghost_down_1[];
extern const ULONG32 crying_ghost_left_1[];
extern const ULONG32 crying_ghost_right_1[];

extern const ULONG32 cyclops_ghost_left_1[];
extern const ULONG32 cyclops_ghost_right_1[];
extern const ULONG32 cyclops_ghost_up_1[];
extern const ULONG32 cyclops_ghost_down_1[];

extern const ULONG32 tombstone[];
extern const ULONG32 ghost_run_1[];
extern const ULONG32 ghost_freeze_1[];
extern const ULONG32 splash[8000];

extern const UINT16 wall_single_16[];

extern const ULONG32 null_sprite_16[];
extern const ULONG32 null_sprite_32[];

extern const ULONG32 test64[];
extern const UCHAR8 pellet[8];

extern const ULONG32* wall_map[][20];


extern UCHAR8 direction_map[][40 ];
extern UINT16 direction_map2[][40 ];

extern UINT16 tile_map[][40 ];
# 2 "events.c" 2
# 1 "./model.h" 1
# 1 "./types.h" 1
# 4 "./model.h" 2
# 1 "./bitmaps.h" 1
# 5 "./model.h" 2
# 31 "./model.h"
typedef enum {
    GHOST_TYPE_CRYING,
    GHOST_TYPE_AWKWARD,
    GHOST_TYPE_CYCLOPS,
    GHOST_TYPE_MOUSTACHE,
	PACMAN,
	WALL,
	OPEN_PATH,
	INVISIBLE_WALL,
	GHOST

}ObjectType;

typedef struct {
	int x_position, y_position;
	bool open_path;
	bool occupied;
	bool has_pellet;

	bool can_go_up;
	bool can_go_down;
	bool can_go_left;
	bool can_go_right;

	UCHAR8 path;
	UCHAR8 alt_path;
}Cell;


typedef struct {
    UINT16 x;
    UINT16 y;
    int delta_x;
    int delta_y;
    UCHAR8 direction;
    UCHAR8 y_cell_index;
    UCHAR8 x_cell_index;

	UINT16 last_x;
	UINT16 last_y;

	UINT16 last_last_x;
	UINT16 last_last_y;

	bool changed_direction;

}Movement;

extern Movement* move;

typedef struct
{
	int current_frame;
	UCHAR8 state;
	ObjectType type;

	Movement* move;
}Pacman;

typedef struct
{
	int current_frame;
	UCHAR8 state;
	ObjectType type;
	bool has_collided;

	Movement* move;
}Ghost;

typedef struct{
	UINT16 seconds, minutes,
	MS_digit_minutes, LS_digit_minutes,
	MS_digit_seconds, LS_digit_seconds;

}Timer;


extern Cell cell_map[24 ][40 ];

extern Pacman pacman;
extern Ghost awkward_ghost;
extern Ghost crying_ghost;
extern Ghost moustache_ghost;
extern Ghost cyclops_ghost;

typedef struct {
    Pacman *pacman;
	Ghost *crying_ghost;
	Ghost *awkward_ghost;
	Ghost *moustache_ghost;
	Ghost *cyclops_ghost;

	Timer *timer;
}Entities;

void move_ghost (Ghost *ghost);
void move_pacman (Pacman *pacman);
ObjectType check_collision(Entities* entity, UINT16 object_y_index, UINT16 object_x_index, int y_delta, int x_delta,
                           ObjectType curr_type);
ObjectType check_pacman_collision(Entities* entity, UINT16 object_y_index,
                                  UINT16 object_x_index, int y_delta, int x_delta);





void init_map_cells(Cell cell_map[][40 ], UINT16 tile_map[][40 ]);
bool update_cell(Movement* entity, UCHAR8 state);
void set_occupied(bool set, int y_index, int x_index);
bool check_shared_occupied(Movement* ghost1_move, Movement* ghost2_move);
void update_cells(Entities* entity);
void update_ghost_direction(Ghost* ghost, Pacman* pacman);
bool check_valid_path(Movement* movement, UCHAR8 direction);
void kill_ghost(Ghost* ghost, Cell cell_map[][40 ]);
void add_wall_to_map(Cell cell_map[24 ][40 ], int y_cell_index, int x_cell_index);
UCHAR8 get_optimal_direction(Movement* movement);


ObjectType check_wall_collision(Movement* entity);

void check_proximity(Entities* entity);
void change_pacman_state(Pacman* pacman, UCHAR8 new_state);
void change_ghost_state(Ghost* ghost, UCHAR8 new_state);
void end_game();

void align_axis(Movement* entity);
void flip_direction(Movement* ghost);
void update_current_frame(Entities* all, int clock);

void set_prev_prev(Entities* entity);
void set_prev(Entities* entity);
# 3 "events.c" 2
# 1 "./TYPES.H" 1
# 4 "events.c" 2
# 1 "./events.h" 1
# 1 "./TYPES.H" 1
# 4 "./events.h" 2
# 1 "./model.h" 1
# 5 "./events.h" 2
# 17 "./events.h"
extern const UCHAR8 DIRECTION_ARRAY[4];
typedef struct
{

    ULONG32 value;

}Xor;

void clock_tick_handle(UINT16* clock_count, Entities* entity);
void handle_pacman_collision(ObjectType object_type, Entities* entity);
void handle_ghost_collision(Movement* ghost1, Movement* ghost2);

void handle_wall_collision(Movement* ghost, int ghost_identifier);
void handle_collisions(Entities* entity, UINT16 ticks);
ObjectType process_ghost_collision(Entities* all, UINT16 tick);
ULONG32 random_number_generator(Xor *xor);
void set_input(Pacman *pacman, char input);

UCHAR8 get_valid_paths(Movement *ghost);
void eat_pellet(Movement* pacman);
# 5 "events.c" 2
# 1 "./psg.h" 1
# 1 "./TYPES.H" 1
# 4 "./psg.h" 2
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
# 5 "./psg.h" 2
# 28 "./psg.h"
typedef struct {
    int frequency;
    int duration;
    int volume;
}Note;

typedef struct {
    int current_note_index;
    int note_time_left;
}MusicState;
# 150 "./psg.h"
void set_note_frequency(int channel, float frequency);
void set_tone(int channel, int tuning);
void enable_channel(int channel, int toneOn, int noiseOn);
void set_volume(int channel, unsigned char volume);
void set_master_volume(unsigned char volume);
void play_note(int channel, int tuning, unsigned char volume);
void stop_sound();
# 6 "events.c" 2
# 1 "./renderer.h" 1
# 1 "./model.h" 1
# 2 "./renderer.h" 2
# 1 "./bitmaps.h" 1
# 3 "./renderer.h" 2
# 1 "./types.h" 1
# 4 "./renderer.h" 2


void clear_entities(ULONG32* base32, Movement* pacman, Movement* crying,
                    Movement* moustache, Movement* awkward, Movement* cyclops);
void render_map(ULONG32* base, UINT16 tile_map[][40 ]);
void render_frame(ULONG32* base, Entities* entity);
void render_pacman(ULONG32* base32, Pacman* pacman);
void render_ghosts(ULONG32* base32, Entities* entity);
void render_gameover();
void render_timer();
void de_render_ghost(ULONG32* base32, Ghost* ghost, Cell cell_map[][40 ]);
void render_non_default_ghost(ULONG32* base32, Ghost* ghost);
void refresh_screen(ULONG32* base32, Entities* entity);
void render_initial_timer(UCHAR8* base);
void render_pellet(UCHAR8* base8, Movement* move);
void clear_pacman(ULONG32* base32, Movement* move);
void render_pellets(ULONG32* base32, Entities* all);
# 7 "events.c" 2
# 1 "C:/c68/include/stdio.h" 1
# 20 "C:/c68/include/stdio.h"
typedef unsigned long  size_t;
# 69 "C:/c68/include/stdio.h"
typedef	struct
	{
	long		_cnt;
	unsigned char	*_ptr;
	unsigned char	*_base;
	unsigned int	_flag;
	int		_file;
	long		_bsiz;
	unsigned char	_ch;
	}
	FILE;


typedef unsigned long fpos_t;
# 92 "C:/c68/include/stdio.h"
extern	FILE	_iob[];
# 108 "C:/c68/include/stdio.h"
 char *	ctermid	(char *) ;




 int	remove	(const char *) ;
 int	rename	(const char *, const char *) ;
 char *	tmpnam	(char *) ;
 FILE *	tmpfile	(void) ;

 int	fclose	(FILE *) ;
 int	fflush	(FILE *) ;

 FILE *	fopen	(const char *, const char *) ;
 FILE *	freopen	(const char *, const char *, FILE *) ;

 void	setbuf	(FILE *, char *) ;
 int	setvbuf	(FILE *, char *, int, size_t) ;
# 132 "C:/c68/include/stdio.h"
 int  fscanf  (FILE *, const char *, ...) ;
 int  scanf   (const char *, ...) ;
 int  sscanf  (const char *, const char *, ...) ;


 int	fprintf	(FILE *, const char *, ...) ;
 int	printf	(const char *, ...) ;
 int	sprintf	(char *, const char *, ...) ;

 int 	vfprintf (FILE *, const char *, char * ) ;
 int 	vprintf	 (const char *, char * ) ;
 int 	vsprintf (char *, const char *, char * ) ;

 int	vscanf  (const char *, char * ) ;
 int	vfscanf (FILE *, const char *, char * ) ;
 int	vsscanf	(const char *, const char *, char * ) ;


 int	fgetc	(FILE *) ;
 char	*fgets	(char *, int, FILE *) ;
 char	*gets	(char *) ;
 int	fputc	(int c, FILE *) ;
 int	fputs	(const char *, FILE *) ;
 int	puts	(const char *) ;

 size_t	fread	(void *, size_t, size_t, FILE *) ;
 size_t	fwrite	(const void *, size_t, size_t, FILE *) ;

 int	fgetpos	(FILE *, fpos_t *) ;
 int	fsetpos	(FILE *, fpos_t *) ;

 int	fseek	(FILE *, long, int) ;
 long	ftell	(FILE *) ;
 void	rewind	(FILE *) ;

 void	perror	(const char *) ;


 FILE	*fdopen	(int, const char *) ;


 FILE *	fopenp	(const char *, const char *) ;
 int 	fungetc	(int, FILE *) ;
 int	pclose	(FILE *) ;
 FILE *	popen	(const char *, const char *) ;
 void	setlinebuf	(FILE *) ;

 void	_binmode	(int) ;
 long 	getl	(FILE *) ;
 long 	putl	(long, FILE *) ;
 short 	getw	(FILE *) ;
 short 	putw	(short, FILE *) ;
 void	_getbuf	(FILE *fp) ;
# 192 "C:/c68/include/stdio.h"
 int	_filbuf	(FILE *) ;
# 8 "events.c" 2


const UCHAR8 DIRECTION_ARRAY[4] = {((UCHAR8)0) , ((UCHAR8)1) , ((UCHAR8)2) , ((UCHAR8)3) };
# 27 "events.c"
void handle_ghost_collision(Movement* ghost1, Movement* ghost2) {

    flip_direction(ghost1);
    flip_direction(ghost2);
}




ObjectType process_ghost_collision(Entities* all, UINT16 tick)
{

    ObjectType collision = OPEN_PATH;
    int i, n;

    Ghost* ghost_array[4];

    Movement *all_ghosts[4];
    all_ghosts[0] = all->crying_ghost->move;
    all_ghosts[1] = all->awkward_ghost->move;
    all_ghosts[2] = all->cyclops_ghost->move;
    all_ghosts[3] = all->moustache_ghost->move;

    ghost_array[0] = all->crying_ghost;
    ghost_array[1] = all->awkward_ghost;
    ghost_array[2] = all->cyclops_ghost;
    ghost_array[3] = all->moustache_ghost;
# 63 "events.c"
    for (i = 0; i < 4; i++){
        if (check_wall_collision(all_ghosts[i]) != OPEN_PATH && ghost_array[i]->state != ((UCHAR8)3) ) {
            handle_wall_collision(all_ghosts[i], i);


        }
    }



}
void handle_wall_collision(Movement* ghost, int ghost_identifier) {

    int i, direction;
    UCHAR8 possible_direction = 0;
    UCHAR8 number_of_open_paths = get_valid_paths(ghost);

    direction = ghost->direction;
# 89 "events.c"
        switch(cell_map[ghost->y_cell_index][ghost->x_cell_index].path)
		{
			case ((UCHAR8)0) :
				ghost->delta_y = -1;
				ghost->delta_x = 0;
				break;

			case ((UCHAR8)1) :
				ghost-> delta_y = 1;
				ghost-> delta_x = 0;
				break;

			case ((UCHAR8)3) :
				ghost ->delta_x = 1;
				ghost ->delta_y = 0;
				break;

			case ((UCHAR8)2) :
				ghost ->delta_x = -1;
				ghost ->delta_y = 0;
				break;
        }
# 141 "events.c"
}
# 151 "events.c"
void handle_pacman_collision(ObjectType object_type, Entities* entity) {

    Movement* pacman = entity->pacman->move;

    switch(object_type)
    {
    case OPEN_PATH:

        break;
    case WALL:

        pacman->delta_y = 0;
        pacman->delta_x = 0;

        break;
    case GHOST:

        switch (object_type)
        {
        case GHOST_TYPE_CRYING:
            kill_ghost(entity->crying_ghost, cell_map);
            break;

        case GHOST_TYPE_AWKWARD:
            kill_ghost(entity->awkward_ghost, cell_map);
            break;

        case GHOST_TYPE_MOUSTACHE:
            kill_ghost(entity->moustache_ghost, cell_map);
            break;

        case GHOST_TYPE_CYCLOPS:
            kill_ghost(entity->cyclops_ghost, cell_map);
            break;

        default:
            break;
        }
        break;
    }
}
# 199 "events.c"
void handle_collisions(Entities* entity, UINT16 ticks) {
    int i;
    ObjectType collision_type = OPEN_PATH;
    Movement* pacman = entity->pacman->move;



    process_ghost_collision(entity, ticks);

    collision_type = check_wall_collision(pacman);
    handle_pacman_collision(collision_type, entity);

    if (check_shared_occupied(pacman, entity->awkward_ghost->move) == -1 )
        kill_ghost(entity->awkward_ghost, cell_map);

    if (check_shared_occupied(pacman, entity->moustache_ghost->move) == -1 )
        kill_ghost(entity->moustache_ghost, cell_map);

    if (check_shared_occupied(pacman, entity->cyclops_ghost->move) == -1 )
        kill_ghost(entity->cyclops_ghost, cell_map);

    if (check_shared_occupied(pacman, entity->crying_ghost->move) == -1 )
        kill_ghost(entity->crying_ghost, cell_map);

}
void set_input(Pacman *pacman, char input)
{
    Movement* movement = pacman->move;

   	movement -> delta_y = 0;
    movement -> delta_x = 0;

	switch(input)
	{
		case 'w' :
                movement -> delta_y = -1;
                movement -> delta_x = 0;
                movement -> direction = ((UCHAR8)0) ;
			break;

		case 'a' :
                movement -> delta_x = -1;
                movement -> delta_y = 0;
                movement -> direction = ((UCHAR8)2) ;
			break;

		case 's' :
                movement -> delta_y = 1;
                movement -> delta_x = 0;
                movement -> direction = ((UCHAR8)1) ;
			break;

		case 'd' :
                movement -> delta_x = 1;
                movement -> delta_y = 0;
                movement -> direction = ((UCHAR8)3) ;
			break;

		default:
            movement -> delta_x = 0;
            movement -> delta_y = 0;

			break;
	}


}





UCHAR8 get_valid_paths(Movement *ghost)
{
    UCHAR8 count = 0;
    if (cell_map[ghost->y_cell_index - 1][ghost->x_cell_index].open_path == -1 )
        count++;
    if (cell_map[ghost->y_cell_index + 1][ghost->x_cell_index].open_path == -1 )
        count++;
    if (cell_map[ghost->y_cell_index][ghost->x_cell_index - 1].open_path == -1 )
        count++;
    if (cell_map[ghost->y_cell_index][ghost->x_cell_index + 1].open_path == -1 )
        count++;
    return count;
}
void eat_pellet(Movement* pacman) {
    cell_map[pacman->y_cell_index][pacman->x_cell_index].has_pellet = 0 ;
}
