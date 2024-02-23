# 1 "pacman.c" 1
# 1 "./pacman.h" 1
# 1 "./raster.h" 1
# 1 "./types.h" 1



typedef unsigned char UCHAR8;
typedef unsigned int  UINT16;
typedef unsigned long ULONG32;

typedef signed char bool;
# 4 "./raster.h" 2
# 22 "./raster.h"
void plot_bitmap_16(UINT16* base, int x, int y, const UINT16 bitmap[], unsigned int height);
void plot_bitmap_32(ULONG32* base, int x, int y, const ULONG32 bitmap[], unsigned int height);
void clear_letter(UCHAR8* base, int x, int y);
void plot_string(UCHAR8* base, int x, int y, const UCHAR8 bitmap[], const char* str);
void clear_bitmap_32(ULONG32* base, int x, int y, unsigned int height);

void plot_bitmap_32_quick(ULONG32* base, int x, int y, const ULONG32 bitmap[], unsigned int height);
void plot_bitmap_64(ULONG32* base, int x, int y, const ULONG32 bitmap[], unsigned int height);
void plot_letter(UCHAR8* base, int x, int y, const UCHAR8 bitmap[], unsigned int letter);
void plot_screen(ULONG32* base, const ULONG32* bitmap);
void clear_screen_q(ULONG32* base);



void plot_screen(ULONG32* base, const ULONG32* bitmap);
# 4 "./pacman.h" 2
# 1 "./model.h" 1
# 1 "./types.h" 1
# 4 "./model.h" 2
# 1 "./bitmaps.h" 1
# 1 "./TYPES.H" 1
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

extern const UINT16 wall_single_16[];

extern const ULONG32 null_sprite_16[];
extern const ULONG32 null_sprite_32[];

extern const ULONG32 test64[];

extern const ULONG32* wall_map[][20];

extern UINT16 tile_map[][40 ];
# 5 "./model.h" 2
# 28 "./model.h"
typedef enum {
    GHOST_TYPE_CRYING,
    GHOST_TYPE_AWKWARD,
    GHOST_TYPE_CYCLOPS,
    GHOST_TYPE_MOUSTACHE,
	PACMAN,
	WALL,
	OPEN_PATH,
	INVISIBLE_WALL

}ObjectType;

typedef struct {
	int x_position, y_position;
	bool open_path;
	bool occupied;
}Cell;


typedef struct {
    UINT16 x;
    UINT16 y;
    int delta_x;
    int delta_y;
    UCHAR8 direction;
    UCHAR8 y_cell_index;
    UCHAR8 x_cell_index;
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
void update_cell(Movement* entity, UCHAR8 state);
void update_cells(Entities* entity);
void kill_ghost(Ghost* ghost, Cell cell_map[][40 ]);
void add_wall_to_map(Cell cell_map[24 ][40 ], int y_cell_index, int x_cell_index);

ObjectType check_wall_collision(Movement* entity);

void check_proximity(Entities* entity);
void change_pacman_state(Pacman* pacman, UCHAR8 new_state);
void change_ghost_state(Ghost* ghost, UCHAR8 new_state);
void end_game();
# 5 "./pacman.h" 2
# 1 "./renderer.h" 1
# 1 "./model.h" 1
# 2 "./renderer.h" 2
# 1 "./bitmaps.h" 1
# 3 "./renderer.h" 2
# 1 "./types.h" 1
# 4 "./renderer.h" 2


void clear_entities(ULONG32* base32, Entities* entity);
void render_map(UINT16* base, UINT16 tile_map[][40 ]);
void render_frame(ULONG32* base, Entities* entity);
void render_pacman(ULONG32* base32, Pacman* pacman);
void render_ghosts(ULONG32* base32, Entities* entity);
void render_gameover();
void render_timer();
void de_render_ghost(ULONG32* base32, Ghost* ghost, Cell cell_map[][40 ]);
void render_non_default_ghost(ULONG32* base32, Ghost* ghost);
void refresh_screen(ULONG32* base32, Entities* entity);
void render_initial_timer(UCHAR8* base);
# 6 "./pacman.h" 2
# 1 "./TYPES.H" 1
# 7 "./pacman.h" 2
# 1 "./font.h" 1
# 1 "./types.h" 1
# 4 "./font.h" 2


extern const UCHAR8 font[];
# 8 "./pacman.h" 2
# 1 "./bitmaps.h" 1
# 9 "./pacman.h" 2
# 1 "./events.h" 1
# 1 "./TYPES.H" 1
# 4 "./events.h" 2
# 1 "./model.h" 1
# 5 "./events.h" 2
# 17 "./events.h"
typedef struct
{

    ULONG32 value;

}Xor;

void clock_tick_handle(UINT16* clock_count, Entities* entity);
void handle_pacman_collision(ObjectType object_type, Entities* entity);
void handle_ghost_collision(UCHAR8 collision_type, Ghost* ghost1, Ghost* ghost2);
void handle_collisions(Entities* entity, Xor *xor);
ULONG32 random_number_generator(Xor *xor);
void set_input(Pacman *pacman, char input);
# 10 "./pacman.h" 2
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
# 11 "./pacman.h" 2
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
# 12 "./pacman.h" 2
# 1 "C:/c68/include/linea.h" 1
# 325 "C:/c68/include/linea.h"
typedef struct {



   short  _VPLANES;
   short  _VWRAP;




   short  *_CONTRL;
   short  *_INTIN;
   short  *_PTSIN;
   short  *_INTOUT;
   short  *_PTSOUT;
# 349 "C:/c68/include/linea.h"
   short  _COLBIT0;
   short  _COLBIT1;
   short  _COLBIT2;
   short  _COLBIT3;




   short  _LSTLIN;



   short  _LNMASK;



   short  _WMODE;
# 372 "C:/c68/include/linea.h"
   short  _X1;

   short  _Y1;

   short  _X2;

   short  _Y2;


   short  *_PATPTR;

   short  _PATMSK;

   short  _MFILL;



   short  _CLIP;
   short  _XMINCL;
   short  _YMINCL;
   short  _XMAXCL;
   short  _YMAXCL;


   short  _XDDA;


   short  _DDAINC;



   short  _SCALDIR;
   short  _MONO;





   short  _SOURCEX;
# 417 "C:/c68/include/linea.h"
   short  _SOURCEY;

   short  _DESTX;
   short  _DESTY;
   short  _DELX;

   short  _DELY;

   short  *_FBASE;
   short  _FWIDTH;

   short  _STYLE;
# 435 "C:/c68/include/linea.h"
   short  _LITEMASK;

   short  _SKEWMASK;

   short  _WEIGHT;

   short  _ROFF;


   short  _LOFF;


   short  _SCALE;

   short  _CHUP;




   short  _TEXTFG;

   char  *_SCRTCHP;




   short  _SCRPT2;



   short  _TEXTBG;


   short  _COPYTRAN;
# 476 "C:/c68/include/linea.h"
 short(*_SEEDABORT) (void) ;
# 484 "C:/c68/include/linea.h"
} __LINEA;
# 546 "C:/c68/include/linea.h"
typedef struct _font {



   short  font_id;

   short  size;

   char   name[32];

   short  first_ade;


   short  last_ade;


   short  top;

   short  ascent;

   short  half;

   short  descent;

   short  bottom;



short max_char_width;

short max_cell_width;

  short left_offset;

  short right_offset;

   short  thicken;

   short  ul_size;

   short  lighten;

   short  skew;



   short  flags;





   char   *h_table;

   short  *off_table;

   char   *dat_table;

   short  form_width;

   short  form_height;

 struct _font *next_font;


} __FONT;
# 620 "C:/c68/include/linea.h"
typedef short(*FPTR) (void) ;
typedef FPTR *FUNCPTR;
# 628 "C:/c68/include/linea.h"
typedef struct {



   char   fg0bg0;
   char   fg0bg1;
   char   fg1bg0;
   char   fg1bg1;

} OP_TAB;





typedef struct  {
	short	bl_xmin;
	short	bl_ymin;
	char	*bl_form;
	short	bl_nxwd;
	short 	bl_nxln;
	short 	bl_nxpl;
}SDDB;
# 673 "C:/c68/include/linea.h"
typedef struct {



   short   bb_b_wd;
   short   bb_b_ht;
   short   bb_plane_ct;
   short   bb_fg_col;
   short   bb_bg_col;
   OP_TAB  bb_op_tab;
   SDDB	   bb_s;
   SDDB	   bb_d;
   short   *bb_p_addr;
   short   bb_p_nxln;
   short   bb_p_nxpl;
   short   bb_p_mask;
   char	   bb_fill[24];

} BBPB;
# 700 "C:/c68/include/linea.h"
typedef struct
{
	char		*fd_addr;


	short		fd_w;
	short		fd_h;
	short		fd_wdwidth;
	short		fd_stand;
	short		fd_nplanes;
	short		fd_r1;
	short		fd_r2;
	short		fd_r3;
} MFDB;
# 720 "C:/c68/include/linea.h"
typedef struct
{
	short	sp_xhot;
	short	sp_yhot;
	short	sp_format;
	short	sp_bg;
	short	sp_fg;
	short	sp_data[32];





} SFORM;
# 750 "C:/c68/include/linea.h"
extern __LINEA *__aline;



extern __FONT  **__fonts;



extern short  (**__funcs) (void) ;
# 1013 "C:/c68/include/linea.h"
 void linea0 (void) ;
 void linea1 (void) ;
 int linea2 (void) ;
 void linea3 (void) ;
 void linea4 (void) ;
 void linea5 (void) ;
 void linea6 (void) ;
 void linea7 (BBPB *P) ;
 void linea8 (void) ;
 void linea9 (void) ;
 void lineaa (void) ;
 void lineab (void) ;
 void lineac (void *P) ;
 void linead (int x, int y, SFORM *sd, void *ss) ;
 void lineae (void) ;
 void lineaf (void) ;
# 13 "./pacman.h" 2


typedef unsigned char GAME_STATE;
# 23 "./pacman.h"
ULONG32 get_time();
GAME_STATE update_game_state(GAME_STATE new_state, char input);
void debug_print(UCHAR8* base, UINT16 x, UINT16 y, UINT16 value);
void debug_cells_pac(UCHAR8* base, Pacman* pacman);
void update_pacman();
void update_ghosts();
void free_ghosts(ULONG32* base32, UCHAR8* base8, Entities* entity);
void manually_move_ghost(ULONG32* base, UCHAR8* base8, Entities* entity, Ghost* ghost1, Ghost* ghost2, int stop);
# 2 "pacman.c" 2
# 1 "./raster.h" 1
# 3 "pacman.c" 2
# 1 "./model.h" 1
# 4 "pacman.c" 2
# 1 "./renderer.h" 1
# 1 "./model.h" 1
# 2 "./renderer.h" 2
# 1 "./bitmaps.h" 1
# 3 "./renderer.h" 2
# 1 "./types.h" 1
# 4 "./renderer.h" 2


void clear_entities(ULONG32* base32, Entities* entity);
void render_map(UINT16* base, UINT16 tile_map[][40 ]);
void render_frame(ULONG32* base, Entities* entity);
void render_pacman(ULONG32* base32, Pacman* pacman);
void render_ghosts(ULONG32* base32, Entities* entity);
void render_gameover();
void render_timer();
void de_render_ghost(ULONG32* base32, Ghost* ghost, Cell cell_map[][40 ]);
void render_non_default_ghost(ULONG32* base32, Ghost* ghost);
void refresh_screen(ULONG32* base32, Entities* entity);
void render_initial_timer(UCHAR8* base);
# 5 "pacman.c" 2
# 1 "./TYPES.H" 1
# 6 "pacman.c" 2
# 1 "./font.h" 1
# 7 "pacman.c" 2
# 1 "./bitmaps.h" 1
# 8 "pacman.c" 2
# 1 "./events.h" 1
# 9 "pacman.c" 2
# 1 "C:/c68/include/osbind.h" 1
# 11 "pacman.c" 2
# 1 "C:/c68/include/stdio.h" 1
# 12 "pacman.c" 2
# 1 "C:/c68/include/linea.h" 1
# 13 "pacman.c" 2
# 21 "pacman.c"
Movement pacman_movement = {
        16  * 19, 16  * 21 + 16 ,
        0,0,
        ((UCHAR8)0) ,
        21,19
};
Pacman pacman = {
    0,
    ((UCHAR8)0) ,
    PACMAN,
    &pacman_movement
};

Movement crying_ghost_movement = {
        16  * 17, 16  * 10 + 16 ,
        0,0,
        ((UCHAR8)2) ,
        10, 17
};
Ghost crying_ghost = {
    0,
    ((UCHAR8)0) ,
    GHOST_TYPE_CRYING,
    &crying_ghost_movement
};

Movement cyclops_ghost_movement = {
        16  * 17, 16  * 12 + 16 ,
        0,0,
        ((UCHAR8)3) ,
        12, 17
};
Ghost cyclops_ghost = {
    0,
    ((UCHAR8)0) ,
    GHOST_TYPE_CYCLOPS,
    &cyclops_ghost_movement
};

Movement moustache_ghost_movement = {
        16  * 21, 16  * 10 + 16 ,
        0,0,
        ((UCHAR8)2) ,
        10, 21
};
Ghost moustache_ghost = {
    0,
    ((UCHAR8)0) ,
    GHOST_TYPE_MOUSTACHE,
    &moustache_ghost_movement
};

Movement awkward_ghost_movement = {
        16  * 21, 16  * 12 + 16 ,
        0,0,
        ((UCHAR8)2) ,
        12, 21
};
Ghost awkward_ghost = {
    0,
    ((UCHAR8)0) ,
    GHOST_TYPE_AWKWARD,
    &awkward_ghost_movement
};

Timer timer = {
    0,0,
    20, 28, 44, 52
};
# 125 "pacman.c"
int main()
{
    Entities entity = {
    &pacman,
    &crying_ghost,
    &awkward_ghost,
    &moustache_ghost,
    &cyclops_ghost,
    };

	char input;
	int i,j,counter;
    int ticks = 0;
	UCHAR8 collision_type = 0;
	ULONG32* base32 = (void*)_trap_14_w((short)0x2) ;
    UINT16* base16 = (void*)_trap_14_w((short)0x2) ;
    UCHAR8* base8 = (void*)_trap_14_w((short)0x2) ;

	ULONG32 time_then, time_now, time_elapsed;
    GAME_STATE state = ((UCHAR8)1) ;

    Xor xor = {123457};

	init_map_cells(cell_map,tile_map);
    clear_screen_q(base32);
    render_map(base16, tile_map);
    render_frame(base32, &entity);
    render_initial_timer(base8);
    free_ghosts(base32, base8, &entity);

	if ((short)_trap_1_w((short)0x0B) )
	{
		input = (char)_trap_1_w((short)0x08) ;
	}

    while (state != ((UCHAR8)0) ) {

        time_now = get_time();
        time_elapsed = time_now - time_then;

        if (time_elapsed > 0) {

            if ((short)_trap_1_w((short)0x0B) )
            {
                input = (char)_trap_1_w((short)0x08) ;
            }
# 178 "pacman.c"
                clear_entities(base32, &entity);
                set_input(&pacman,input);

                check_proximity(&entity);
                handle_collisions(&entity, &xor);

                update_pacman(ticks);
                update_ghosts();

                render_frame(base32, &entity);
                update_cells(&entity);

                debug_cells_pac(base8, &pacman);
            time_then = time_now;
        }
        update_game_state(state, input);
    }

	return 0;
}




void update_pacman(int do_the_roar){
    move_pacman(&pacman);
    if (do_the_roar % 2 == 0) {
        if (pacman.state == ((UCHAR8)0) ) {
            pacman.current_frame = ((pacman.current_frame) + 1) % 8;
        }
        else {
        pacman.current_frame = ((pacman.current_frame) + 1) % 6;
        }
    }
}
void update_ghosts(){
                move_ghost(&moustache_ghost);
                move_ghost(&crying_ghost);
                move_ghost(&cyclops_ghost);
                move_ghost(&awkward_ghost);

}
void free_ghosts(ULONG32* base32, UCHAR8* base8, Entities* entity) {
    crying_ghost.move->delta_x = 1;
	crying_ghost.move->delta_y = 0;
    crying_ghost.move->direction = ((UCHAR8)3) ;

    awkward_ghost.move->delta_x = -1;
    awkward_ghost.move->delta_y = 0;
    awkward_ghost.move->direction = ((UCHAR8)2) ;

	manually_move_ghost(base32, base8, entity, &crying_ghost, &awkward_ghost, 32);

	crying_ghost.move->delta_x = 0;
	crying_ghost.move->delta_y = -1;
	crying_ghost.move->direction = ((UCHAR8)0) ;

    awkward_ghost.move->delta_x = 0;
    awkward_ghost.move->delta_y = 1;
    awkward_ghost.move->direction = ((UCHAR8)1) ;

	manually_move_ghost(base32, base8, entity, &crying_ghost, &awkward_ghost, 32);


    awkward_ghost.move->delta_x = 0;
}
void manually_move_ghost(ULONG32* base, UCHAR8* base8, Entities* entity, Ghost* ghost1, Ghost* ghost2, int stop){
    int i;

	for (i=0; i < stop; i++) {
		clear_bitmap_32(base, ghost1->move->x, ghost1->move->y, 32 );
        clear_bitmap_32(base, ghost2->move->x, ghost2->move->y, 32 );

        ghost1 -> move-> x += (ghost1 -> move->delta_x);
        ghost1 -> move-> y += (ghost1 -> move->delta_y);

        ghost2 -> move-> x += (ghost2 -> move->delta_x);
        ghost2 -> move-> y += (ghost2 -> move->delta_y);

		update_cells(entity);

		render_frame(base, entity);
		if (i % 8 == 0) {
			ghost1->current_frame = ((ghost1->current_frame) + 1) % 2;
            ghost2->current_frame = ((ghost2->current_frame) + 1) % 2;
		}
	}
}
GAME_STATE update_game_state(GAME_STATE new_state, char input) {

    GAME_STATE state;
    if (input == '\033')
        state = ((UCHAR8)0) ;

    state = new_state;
}
ULONG32 get_time()
{

	ULONG32 *timer = (ULONG32 *)0x462;
	ULONG32 timeNow;
	ULONG32 old_ssp;
	old_ssp = _trap_1_wl((short)0x20,(long)(0)) ;
	timeNow = *timer;
	_trap_1_wl((short)0x20,(long)(old_ssp)) ;

	return timeNow;

}
void debug_print(UCHAR8* base, UINT16 x, UINT16 y, UINT16 value){
    UINT16 tens = value / 10;
    UINT16 ones = value % 10;

    unsigned int tens_char = tens + '0';
    unsigned int ones_char = ones + '0';

	clear_letter(base, x, y);
	clear_letter(base, x+8 , y);
    plot_letter(base, x , y, font, tens_char);
    plot_letter(base, x + 8 , y, font, ones_char);
}
void debug_cells_pac(UCHAR8* base, Pacman* pacman) {
    int j;

    const char strx[] = "X: ";
	const char stry[] = "Y: ";

    for (j = 0; j < 14; j++) {
    	clear_letter(base, j*8 , 0);
	}

    plot_string(base, 0, 0, font, strx);
    debug_print(base, 4*8 , 0, pacman->move->x_cell_index);
    plot_string(base, 8*8 , 0, font, stry);
    debug_print(base, 12*8 , 0, pacman->move->y_cell_index);
}
