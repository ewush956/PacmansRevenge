# 1 "model.c" 1
# 1 "./TYPES.H" 1



typedef unsigned char UINT8;
typedef unsigned int  UINT16;
typedef unsigned long UINT32;

typedef int bool;
# 1 "model.c" 2
# 1 "./model.h" 1
# 1 "./types.h" 1
# 4 "./model.h" 2
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

extern const UINT32 wall_left_down_right[];
extern const UINT32 wall_up_down[];
extern const UINT32 wall_left_right[];
extern const UINT32 wall_down_right[];

extern const UINT32 tombstone[];
extern const UINT32 ghost_run[];
extern const UINT32 ghost_freeze[];

extern const UINT32 wall1_all[];
extern const UINT32 wall2_all[];

extern const UINT32 wall1_vert[];
extern const UINT32 wall2_vert[];

extern const UINT32 wall1_horz[];
extern const UINT32 wall2_horz[];

extern const UINT32 wall1_URD[];
extern const UINT32 wall1_LD[];
extern const UINT32 wall1_LUR[];
extern const UINT32 wall2_RDL[];
extern const UINT32 wall2_RD[];
extern const UINT32 wall2_DLU[];
extern const UINT32 wall2_LU[];
extern const UINT32 wall2_UR[];
extern const UINT32 wall2_UR[];

extern const UINT32 null_sprite_32[];

extern const UINT32 test64[];
# 5 "./model.h" 2
# 19 "./model.h"
extern const UINT16 tile_map[11 ][18 ];
# 27 "./model.h"
typedef struct
{
	UINT16 x, y;
	int delta_x, delta_y;

	int current_frame;
	UINT8 direction;
	UINT8 is_evil;
	UINT8 has_collided;

}Pacman;

typedef struct
{
	UINT16 x,y;
	int delta_x,delta_y;

	int current_frame;
	UINT8 direction;
	UINT8 is_scared;

}Ghost;
# 58 "./model.h"
void move_ghost_position (Ghost *ghost, int new_x, int new_y);
void increase_ghost_velocity (Ghost *ghost, UINT16 vertical_velocity, UINT16 horizontal_velocity);
void move_pacman_position (Pacman *pacman, char input);

bool check_collision(Pacman* pacman, UINT16 pacman_x_position, UINT16 pacman_y_position);
# 70 "./model.h"
void clock_tick_handle();
# 2 "model.c" 2
# 1 "./bitmaps.h" 1
# 3 "model.c" 2
# 1 "./events.h" 1
# 1 "./TYPES.H" 1
# 4 "./events.h" 2
# 1 "./model.h" 1
# 5 "./events.h" 2


void clock_tick_handle();

void handle_collision(Pacman* pacman, UINT16 x_position, UINT16 y_position);
# 4 "model.c" 2
# 1 "C:/c68/include/stdio.h" 1
# 1 "C:/c68/include/compiler.h" 1
# 11 "C:/c68/include/stdio.h" 2
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
# 5 "model.c" 2
# 32 "model.c"
const UINT16 tile_map[11 ][18 ] = {

{4,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3},
{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
{2,0,4,1,1,1,0,1,0,1,0,1,1,1,1,3,0,2},
{2,0,2,0,0,0,0,0,0,0,0,0,0,0,0,2,0,2},
{2,0,2,0,4,3,0,4,0,0,3,0,4,3,0,2,0,2},
{2,0,0,0,0,0,0,6,1,1,5,0,2,2,0,0,0,2},
{2,0,2,0,6,5,0,0,0,0,0,0,6,5,0,2,0,2},
{2,0,2,0,0,0,0,0,4,1,3,0,0,0,0,2,0,2},
{2,0,6,1,1,1,1,0,6,1,5,0,1,1,1,5,0,2},
{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
{6,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5}
};




Pacman pacman;
Ghost crying_ghost;
Ghost moustache_ghost;
Ghost cyclops_ghost;
Ghost awkward_ghost;

const UINT32 default_pac_sprites[][4];
const UINT32 evil_pac_sprites[][4];
const UINT32 crying_ghost_sprites[][4];
const UINT32 moustache_ghost_sprites[][4];
const UINT32 cyclops_ghost_sprites[][4];
const UINT32 awkward_ghost_sprites[][4];

const UINT32* default_pacman_sprites[4][4] = {
    {pac_1, pac_2, pac_3, pac_4},
    {pac_1, pac_2, pac_3, pac_4}
};
const UINT32* evil_pacman_sprites[4][4] = {
    {evil_pac_1, evil_pac_2, evil_pac_3, evil_pac_4},
    {evil_pac_1, evil_pac_2, evil_pac_3, evil_pac_4}
};
# 108 "model.c"
void move_pacman_position(Pacman *pacman, char input)
{
    bool collision;
	UINT16 new_x_position, new_y_position;
    pacman -> delta_y = 0;
    pacman -> delta_x = 0;

	switch(input)
	{
		case 'w': pacman -> delta_y = -1;
			break;

		case 'a': pacman -> delta_x = -1;
			break;

		case 's': pacman -> delta_y = 1;
			break;

		case 'd': pacman -> delta_x = 1;
			break;

		default:
			printf("Invalid input\n");
            pacman-> delta_x = 0;
            pacman -> delta_y = 0;
			break;
	}

	new_x_position = pacman->x + pacman->delta_x;
	new_y_position = pacman->y + pacman->delta_y;
# 152 "model.c"
    collision = check_collision(&pacman, new_x_position, new_y_position);




    if (collision == 0)
    {
        printf("MOVING HIM");
        pacman->x = new_x_position;
		pacman->y = new_y_position;

    }
# 176 "model.c"
}
# 185 "model.c"
void increase_ghost_velocity (Ghost *ghost, UINT16 vertical_velocity, UINT16 horizontal_velocity)
{

	ghost->delta_x = horizontal_velocity;
	ghost->delta_y = vertical_velocity;

}
# 202 "model.c"
void move_ghost_position (Ghost *ghost, int new_x, int new_y)
{



	if (!(ghost->x + new_x > 640  || ghost->x  + new_x < 0 ||
		ghost->y + new_y > 400  || ghost->y + new_y < 0))
	{
			ghost-> x += new_x;
			ghost->y += new_y;
	}


}
bool check_collision (Pacman* pacman, UINT16 pacman_x_position, UINT16 pacman_y_position)
{
    bool collision = 0;


    if (tile_map[pacman_y_position][pacman_x_position] == 1 ||
        tile_map[pacman_y_position][pacman_x_position] == 2 ||
        tile_map[pacman_y_position][pacman_x_position] == 3 ||
        tile_map[pacman_y_position][pacman_x_position] == 4 ||
        tile_map[pacman_y_position][pacman_x_position] == 5 ||
        tile_map[pacman_y_position][pacman_x_position] == 6)
        {


            printf(" collision \n");
            printf("This value is for collision is: %d",tile_map[pacman_y_position][pacman_x_position]);
            collision = 1;

        }

        else{

            printf(" YOURE GOOD: %d\n",tile_map[pacman_y_position][pacman_x_position]);
        }




        return collision;

}
