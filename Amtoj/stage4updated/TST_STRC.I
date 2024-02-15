# 1 "tst_strc.c" 1
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
# 1 "tst_strc.c" 2
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
# 2 "tst_strc.c" 2
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
# 3 "tst_strc.c" 2
# 1 "./struct.h" 1
# 1 "./types.h" 1



typedef unsigned char UINT8;
typedef unsigned int  UINT16;
typedef unsigned long UINT32;

typedef signed char bool;
# 4 "./struct.h" 2
# 24 "./struct.h"
void plot_bitmap_32(UINT32* base, int x, int y, const UINT32 bitmap[], unsigned int height);
void plot_bitmap_64(UINT32* base, int x, int y, const UINT32 bitmap[], unsigned int height);
void plot_letter(UINT8* base, int x, int y, const UINT8 bitmap[], unsigned int letter);
void plot_screen(UINT32* base, const UINT32* bitmap);
void clear_screen_q(UINT32* base);
void plot_screen(UINT32* base, const UINT32* bitmap);
# 5 "tst_strc.c" 2
# 1 "./TYPES.H" 1
# 6 "tst_strc.c" 2
# 1 "./font.h" 1
# 1 "./types.h" 1
# 4 "./font.h" 2


extern const UINT8 font[];
# 7 "tst_strc.c" 2
# 1 "./bitmaps.h" 1
# 1 "./TYPES.H" 1
# 4 "./bitmaps.h" 2


extern const UINT32 pac_1[];
extern const UINT32 pac_2[];
extern const UINT32 pac_3[];
extern const UINT32 pac_4[];

extern const UINT32 evil_pac_1[];
extern const UINT32 evil_pac_2[];
extern const UINT32 evil_pac_3[];
extern const UINT32 evil_pac_4[];

extern const UINT32 ghost_1_up[];
extern const UINT32 ghost_1_down[];
extern const UINT32 ghost_1_left[];
extern const UINT32 ghost_1_right[];

extern const UINT32 ghost_2_up[];
extern const UINT32 ghost_2_down[];
extern const UINT32 ghost_2_left[];
extern const UINT32 ghost_2_right[];

extern const UINT32 ghost_3_up[];
extern const UINT32 ghost_3_down[];
extern const UINT32 ghost_3_left[];
extern const UINT32 ghost_3_right[];

extern const UINT32 ghost_4_up[];
extern const UINT32 ghost_4_down[];
extern const UINT32 ghost_4_left[];
extern const UINT32 ghost_4_right[];

extern const UINT32 cyclops_ghost_L[];
extern const UINT32 cyclops_ghost_R[];
extern const UINT32 cyclops_ghost_U[];
extern const UINT32 cyclops_ghost_D[];

extern const UINT32 tombstone[];
extern const UINT32 ghost_run[];
extern const UINT32 ghost_freeze[];

extern const UINT32 wall_ULD[];
extern const UINT32 wall_all[];
extern const UINT32 wall_vert[];
extern const UINT32 wall_UL[];
extern const UINT32 wall_UR[];
extern const UINT32 wall_LDR[];
extern const UINT32 wall_ULR[];
extern const UINT32 wall_UDR[];
extern const UINT32 wall_LD[];
extern const UINT32 wall_DR[];
extern const UINT32 wall_horz[];
extern const UINT32 wall_single[];
extern const UINT16 wall_single_16[];

extern const UINT32 wall_horz_end_L[];

extern const UINT32 null_sprite_32[];

extern const UINT32 test64[];

extern const UINT32* wall_map[][20];
# 8 "tst_strc.c" 2
# 1 "./model.h" 1
# 1 "./types.h" 1
# 4 "./model.h" 2
# 1 "./bitmaps.h" 1
# 5 "./model.h" 2
# 31 "./model.h"
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
	bool is_evil;
	bool has_collided;

	int x_cell_index, y_cell_index;




}Pacman;

typedef struct
{
	UINT16 x,y;
	int delta_x,delta_y;

	int current_frame;
	UINT8 direction;
	bool is_scared;

	int x_cell_index, y_cell_index;
	struct Cell *current_cell;


}Ghost;

typedef struct{
	UINT16 seconds, minutes,
	MS_digit_minutes, LS_digit_minutes,
	MS_digit_seconds, LS_digit_seconds;

}Timer;

typedef struct
{
    struct Pacman *pacman;
	struct Ghost *crying_ghost;
	struct Ghost *awkward_ghost;
	struct Ghost *moustache_ghost;
	struct Ghost *cyclops_ghost;

}Entities;


extern int tile_map[24 ][40 ];
extern Cell cell_map[24 ][40 ];


extern Pacman pacman;
extern Ghost awkward_ghost;
extern Ghost crying_ghost;
extern Ghost moustache_ghost;
extern Ghost cyclops_ghost;



void move_ghost (Ghost *ghost, Cell *cell_map[][40 ], int new_x, int new_y);
void increase_ghost_velocity (Ghost *ghost, UINT16 vertical_velocity, UINT16 horizontal_velocity);
void move_pacman (Pacman *pacman);



UINT8 check_collision(Entities *entity, UINT16 object_y_position, UINT16 object_x_position);


void init_map_cells(Cell cell_map[][40 ]);
void set_ghost_path(Ghost *ghost, UINT16* path_array[][40 ], Cell cell_map[][40 ]);


void update_cell(int* x_index, int* y_index);
# 10 "tst_strc.c" 2
# 1 "./events.h" 1
# 1 "./TYPES.H" 1
# 1 "./events.h" 2


void clock_tick_handle(UINT16 *clock_count, Ghost *ghost, Pacman *pacman, Timer *timer);

void handle_ghost_collision();
void handle_pacman_collision(UINT8 collision_type);
# 11 "tst_strc.c" 2
# 1 "./input.h" 1
# 12 "tst_strc.c" 2
# 1 "./renderer.h" 1
# 1 "./model.h" 1
# 2 "./renderer.h" 2
# 1 "./bitmaps.h" 1
# 3 "./renderer.h" 2
# 1 "./types.h" 1
# 4 "./renderer.h" 2


typedef struct {

    UINT32 value;

}Xor;

void clock_tick_handle();
void render_map(UINT16* base);
void render_pacman(Pacman *pacman, Ghost *ghost);
void render_ghosts(Ghost *ghost);
void render_gameover();

void render_timer(Timer *timer);

void clear_sprite(UINT32* base, int x, int y);
bool check_next_cell(int dirrection, int x_cell_index, int y_cell_index);
UINT32 random_number_generator(Xor* xor);
# 13 "tst_strc.c" 2
# 30 "tst_strc.c"
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
void display_all_ascii(UINT8* base, int x0, int y0);
void test_arbitrary_letter(UINT8* base);

void set_input(Pacman *pacman,char input);
# 72 "tst_strc.c"
int main()
{





	char input;
	Pacman pacman_obj = {1,9,0,0,0,0,0,0};

	Ghost crying_ghost = {
	16  * 17, 16  * 10 + 8 ,
    0,0,
    0,
    1 ,
    0 
	};

	Xor xor = {1234567};

	init_map_cells(cell_map);
# 107 "tst_strc.c"
	printf("pacman position old : (%d, %d)\n", pacman_obj.y, pacman_obj.x);
# 123 "tst_strc.c"
	while(!(short)_trap_1_w((short)0x0B) )
	{




		input = _trap_1_w((short)0x01) ;

		 printf("RAND::::%u\n",random_number_generator(&xor));

		 set_input(&pacman_obj,input);

		 render_pacman(&pacman,&crying_ghost);




		 printf("pacman position now: (%d, %d)\n", pacman_obj.y, pacman_obj.x);

	}



	printf("pacman position new : (%d, %d)\n", pacman_obj.y, pacman_obj.x);


	return 0;
}


void next_test(UINT32* base) {

	while(!(short)_trap_1_w((short)0x0B) ){

	}
	_trap_1_w((short)0x08) ;
	clear_screen_q(base);
}



void set_input(Pacman *pacman, char input)
{

	pacman -> delta_y = 0;
    pacman -> delta_x = 0;


	switch(input)
	{
		case 'w' :
			pacman -> delta_y = -1;
            pacman -> direction = 1 ;
			break;

		case 'a' :
			pacman -> delta_x = -1;
            pacman -> direction = 3 ;
			break;

		case 's' :
			pacman -> delta_y = 1;
            pacman -> direction = 2 ;
			break;

		case 'd' :
			pacman -> delta_x = 1;
            pacman -> direction = 4 ;
			break;

		default:
			printf("Invalid input\n");
            pacman-> delta_x = 0;
            pacman -> delta_y = 0;

			break;
	}




}
