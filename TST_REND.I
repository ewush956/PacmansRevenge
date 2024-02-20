# 1 "tst_rend.c" 1
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
# 1 "tst_rend.c" 2
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
# 2 "tst_rend.c" 2
# 1 "./raster.h" 1
# 1 "./types.h" 1



typedef unsigned char UINT8;
typedef unsigned int  UINT16;
typedef unsigned long UINT32;

typedef signed char bool;
# 4 "./raster.h" 2
# 22 "./raster.h"
void plot_bitmap_16(UINT16* base, int x, int y, const UINT16 bitmap[], unsigned int height);
void plot_bitmap_32(UINT32* base, int x, int y, const UINT32 bitmap[], unsigned int height);
void clear_bitmap_32(UINT32* base, int x, int y, unsigned int height);

void plot_bitmap_32_quick(UINT32* base, int x, int y, const UINT32 bitmap[], unsigned int height);
void plot_bitmap_64(UINT32* base, int x, int y, const UINT32 bitmap[], unsigned int height);
void plot_letter(UINT8* base, int x, int y, const UINT8 bitmap[], unsigned int letter);
void plot_screen(UINT32* base, const UINT32* bitmap);
void clear_screen_q(UINT32* base);



void plot_screen(UINT32* base, const UINT32* bitmap);
# 3 "tst_rend.c" 2
# 1 "./model.h" 1
# 1 "./types.h" 1
# 4 "./model.h" 2
# 1 "./bitmaps.h" 1
# 1 "./TYPES.H" 1
# 4 "./bitmaps.h" 2




extern const UINT32* default_pacman_sprites[4 ][7];
extern const UINT32* evil_pacman_sprites[4 ][7];
extern const UINT32* crying_ghost_sprites[4 ][2];
extern const UINT32* awkward_ghost_sprites[4 ][2];
extern const UINT32* cyclops_ghost_sprites[4 ][2];
extern const UINT32* moustache_ghost_sprites[4 ][2];
extern const UINT32* frozen_ghost_sprites[4 ][2];
extern const UINT32* running_ghost_sprites[4 ][2];

extern const UINT32 evil_pac_up_2[32];
extern const UINT32 evil_pac_down_1[32];
extern const UINT32 pac_left_2[32];
extern const UINT32 cyclops_ghost_down_2[32];
extern const UINT32 evil_pac_up_3[32];
extern const UINT32 pac_up_2[32];
extern const UINT32 pac_left_3[32];
extern const UINT32 evil_pac_down_4[32];
extern const UINT32 pac_up_3[32];
extern const UINT32 pac_left_1[32];
extern const UINT32 evil_pac_left_2[32];
extern const UINT32 cyclops_ghost_left_2[32];
extern const UINT32 moustache_ghost_right_2[32];
extern const UINT32 evil_pac_left_4[32];
extern const UINT32 moustache_ghost_down_2[32];
extern const UINT32 evil_pac_up_1[32];
extern const UINT32 cyclops_ghost_right_2[32];
extern const UINT32 moustache_ghost_up_2[32];
extern const UINT32 crying_ghost_left_2[32];
extern const UINT32 crying_ghost_down_2[32];
extern const UINT32 pac_up_4[32];
extern const UINT32 evil_pac_left_3[32];
extern const UINT32 evil_pac_up_4[32];
extern const UINT32 awkward_ghost_down_2[32];
extern const UINT32 awkward_ghost_left_2[32];
extern const UINT32 pac_left_4[32];
extern const UINT32 cyclops_ghost_up_2[32];
extern const UINT32 awkward_ghost_up_2[32];
extern const UINT32 evil_pac_down_2[32];
extern const UINT32 crying_ghost_right_2[32];
extern const UINT32 moustache_ghost_left_2[32];
extern const UINT32 evil_pac_left_1[32];
extern const UINT32 pac_down_1[32];
extern const UINT32 pac_down_2[32];
extern const UINT32 crying_ghost_up_2[32];
extern const UINT32 evil_pac_down_3[32];
extern const UINT32 pac_down_4[32];
extern const UINT32 pac_up_1[32];
extern const UINT32 awkward_ghost_right_2[32];
extern const UINT32 pac_down_3[32];


extern const UINT32 pac_1[];
extern const UINT32 pac_2[];
extern const UINT32 pac_3[];
extern const UINT32 pac_4[];

extern const UINT32 evil_pac_1[];
extern const UINT32 evil_pac_2[];
extern const UINT32 evil_pac_3[];
extern const UINT32 evil_pac_4[];

extern const UINT32 moustache_ghost_up_1[];
extern const UINT32 moustache_ghost_down_1[];
extern const UINT32 moustache_ghost_left_1[];
extern const UINT32 moustache_ghost_right_1[];

extern const UINT32 awkward_ghost_up_1[];
extern const UINT32 awkward_ghost_down_1[];
extern const UINT32 awkward_ghost_left_1[];
extern const UINT32 awkward_ghost_right_1[];

extern const UINT32 crying_ghost_up_1[];
extern const UINT32 crying_ghost_down_1[];
extern const UINT32 crying_ghost_left_1[];
extern const UINT32 crying_ghost_right_1[];

extern const UINT32 cyclops_ghost_left_1[];
extern const UINT32 cyclops_ghost_right_1[];
extern const UINT32 cyclops_ghost_up_1[];
extern const UINT32 cyclops_ghost_down_1[];

extern const UINT32 tombstone[];
extern const UINT32 ghost_run_1[];
extern const UINT32 ghost_freeze_1[];

extern const UINT16 wall_single_16[];

extern const UINT32 null_sprite_16[];
extern const UINT32 null_sprite_32[];

extern const UINT32 test64[];

extern const UINT32* wall_map[][20];

extern UINT16 tile_map[][40 ];
# 5 "./model.h" 2
# 26 "./model.h"
typedef struct {
	int x_position, y_position;
	bool open_path;
}Cell;

typedef struct
{
	UINT16 x, y;
	int delta_x, delta_y;

	int current_frame;
	UINT8 direction;
	UINT8 state;

	UINT16 y_cell_index, x_cell_index;
	struct Cell *current_cell;
}Pacman;

typedef struct
{
	UINT16 x,y;
	int delta_x,delta_y;

	int current_frame;
	UINT8 direction;
	UINT8 state;

	UINT16 y_cell_index, x_cell_index;
	struct Cell *current_cell;

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
UINT8 check_collision(Entities* entity, UINT16 object_y_position, UINT16 object_x_position,UINT16 y_delta, UINT16 x_delta);

void init_map_cells(Cell cell_map[][40 ], UINT16 tile_map[][40 ]);
void update_cell(UINT16* x_index, UINT16* y_index, UINT16 x_position, UINT16 y_position, UINT8 direction, UINT8 state);
void update_cells(Entities* entity);
void kill_ghost(Ghost* ghost, Cell cell_map[][40 ]);
void add_wall_to_map(Cell cell_map[24 ][40 ], int y_cell_index, int x_cell_index);
# 4 "tst_rend.c" 2
# 1 "./renderer.h" 1
# 1 "./model.h" 1
# 2 "./renderer.h" 2
# 1 "./bitmaps.h" 1
# 3 "./renderer.h" 2
# 1 "./types.h" 1
# 4 "./renderer.h" 2


void render_map(UINT16* base, UINT16 tile_map[][40 ]);
void render_frame(UINT32* base, Entities* entity);
void render_pacman(UINT32* base32, Pacman* pacman);
void render_ghosts(UINT32* base32, Entities* entity);
void render_gameover();
void render_timer();
void de_render_ghost(UINT32* base32, Ghost* ghost, Cell cell_map[][40 ]);
void render_non_default_ghost(UINT32* base32, Ghost* ghost);
void refresh_screen(UINT32* base32, Entities* entity);
void render_initial_timer(UINT8* base);
# 5 "tst_rend.c" 2
# 1 "./TYPES.H" 1
# 6 "tst_rend.c" 2
# 1 "./font.h" 1
# 1 "./types.h" 1
# 4 "./font.h" 2


extern const UINT8 font[];
# 7 "tst_rend.c" 2
# 1 "./bitmaps.h" 1
# 8 "tst_rend.c" 2




int arbitrary_numbers_400[] = {
	141, 276, 392, 345, 72, 307, 51, 17, 198, 63,
	366, 304, 383, 71, 111, 190, 255, 39, 110, 307,
	297, 324, 393, 95, 386, 53, 222, 368, 85, 325,
	88, 100, 12, 92, 62, 275, 221, 131, 372, 300,
	388, 262, 174, 356, 84, 121, 276, 142, 210,
	21, 336, 300, 392, 238, 92, 369, 88, 210,
	262, 174, 356, 84, 121, 276, 142, 400, 365,
	18, 336, 300, 392, 238, 97, 369, 88, 210,
	8, 21, 57, 299, 238, 97, 369, 88, 210, 327,
	333, 1, 32, 109, 238, 97, 369, 0, 210
};

int arbitrary_numbers_640[] = {
	339, 287, 372, 220, 597, 186, 93, 429, 258,
	70, 496, 20, 633, 612, 333, 61, 556, 404, 0,
	369, 591, 383, 511, 433, 123, 320, 106, 268,
	508, 122, 602, 280, 617, 482, 460, 218, 246,
	11, 138, 317, 213, 326, 36, 456, 94, 9, 253,
	269, 226, 381, 303, 29, 154, 251, 537, 604, 340,
	647, 466, 367, 144, 123, 626, 389, 168, 638,
	240, 389, 110, 281, 444, 565, 18, 211, 44,
	213, 625, 603, 98, 94, 47, 382, 119, 312, 9,
	210, 240, 39, 255, 492, 515, 174, 377, 255, 37
};

void next_test(UINT32* base);
void test_pacman_movement(UINT32* base, Entities* entity, int stop);
void test_ghost_movement(UINT32* base, Entities* entity, Ghost* ghost, int stop);

void test_arbitrary_letter(UINT8* base);

int main()
{
	Entities entity = {
		&pacman,
		&crying_ghost,
		&moustache_ghost,
		&awkward_ghost,
		&cyclops_ghost
	};
	Pacman* pac = entity.pacman;
	Ghost* moustache = entity.moustache_ghost;
	Ghost* crying = entity.crying_ghost;
	Ghost* awkward = entity.awkward_ghost;
	Ghost* cyclops = entity.cyclops_ghost;

	void *base32 = (void*)_trap_14_w((short)0x2) ;
	void *base16 = (void*)_trap_14_w((short)0x2) ;
	void *base8 = (void*)_trap_14_w((short)0x2) ;

	int x, y, i, j, index, countx, county, offset_x, offset_y;

	init_map_cells(cell_map, tile_map);

	clear_screen_q(base32);
	next_test(base32);
    render_map(base16, tile_map);
	render_frame(base32, &entity);
	next_test(base32);


	refresh_screen(base32, &entity);
	test_pacman_movement(base32, &entity, 15);

	pacman.direction = ((UINT8)3) ;
	pacman.delta_x = 1;
	pacman.delta_y = 0;
	next_test(base32);

	next_test(base32);
	test_pacman_movement(base32, &entity, 16 * 15);

	pac->direction = ((UINT8)0) ;
	pac->delta_x = 0;
	pac->delta_y = -1;
	test_pacman_movement(base32, &entity, 32 + 16);
	next_test(base32);

	crying->delta_x = 1;
	crying->delta_y = 0;
	crying->direction = ((UINT8)3) ;

	test_ghost_movement(base32, &entity, crying, 32);

	crying->delta_x = 0;
	crying->delta_y = -1;
	crying->direction = ((UINT8)0) ;
	test_ghost_movement(base32, &entity, crying, 32+16);

	kill_ghost(moustache, cell_map);
	de_render_ghost(base32, moustache, tile_map);
	next_test(base32);
	de_render_ghost(base32, cyclops, tile_map);
	de_render_ghost(base32, crying, tile_map);
	de_render_ghost(base32, awkward, tile_map);
	next_test(base32);

	awkward->delta_x = -1;
	awkward->delta_y = 0;
	awkward->direction = ((UINT8)2) ;
	test_ghost_movement(base32, &entity, awkward, 32);

	moustache->delta_x = 0;
	moustache->delta_y = -1;
	moustache->direction = ((UINT8)0) ;
	test_ghost_movement(base32, &entity, moustache, 16);

	moustache->delta_x = 1;
	moustache->delta_y = 0;
	moustache->direction = ((UINT8)3) ;
	test_ghost_movement(base32, &entity, moustache, 64);

	next_test(base32);





	return 0;
}

void next_test(UINT32* base) {
	while(!(short)_trap_1_w((short)0x0B) ){
	}
	_trap_1_w((short)0x08) ;
}

void test_pacman_movement(UINT32* base, Entities* entity, int stop) {
	int i;
	UINT16 cell_x = entity->pacman->x_cell_index;
	UINT16 cell_y = entity->pacman->y_cell_index;

	for (i=0; i < stop; i++) {
		clear_bitmap_32(base, entity->pacman->x, entity->pacman->y, 32 );
		move_pacman(entity->pacman);
		update_cells(entity);
		render_frame(base, entity);
		if (i % 4 == 0) {
			entity->pacman->current_frame = ((entity->pacman->current_frame) + 1) % 6;
		}
# 159 "tst_rend.c"
		if (entity->pacman->y_cell_index != cell_y && entity->pacman->delta_x == 0) {
			next_test(base);
			cell_y = entity->pacman->y_cell_index;
		}

	}
}
void test_ghost_movement(UINT32* base, Entities* entity, Ghost* ghost, int stop) {
	int i;
	int cell_x = ghost->x_cell_index;
	int cell_y = ghost->y_cell_index;

	for (i=0; i < stop; i++) {
		clear_bitmap_32(base, ghost->x, ghost->y, 32 );
		move_ghost(ghost);
		update_cells(entity);
		render_frame(base, entity);
		if (i % 8 == 0) {
			ghost->current_frame = ((ghost->current_frame) + 1) % 2;
		}
	}
}
