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
# 32 "./model.h"
 typedef struct {

	UINT16 x_position, y_position;
	bool open_path;


}Cell;

extern Cell cell_map[11 ][18 ];

typedef struct {
	UINT16 x, y;
	int delta_x, delta_y;

	int current_frame;
	UINT8 direction;
	bool is_evil;
	bool has_collided;

	Cell* current_cell;

}Pacman;

typedef struct
{
	UINT16 x,y;
	int delta_x,delta_y;

	int current_frame;
	UINT8 direction;
	bool is_scared;

	Cell* current_cell;
	Cell path[18 ][11 ];

}Ghost;





extern Pacman pacman;
extern Ghost awkward_ghost;
extern Ghost crying_ghost;
extern Ghost moustache_ghost;
extern Ghost cyclops_ghost;



void move_ghost_position (Ghost *ghost, int current_x, int current_y);
void increase_ghost_velocity (Ghost *ghost, UINT16 vertical_velocity, UINT16 horizontal_velocity);
void move_pacman_position (Pacman *pacman, char input);

void init_map_cells(Cell cell_map[][18 ]);
void set_ghost_path(Ghost *ghost, UINT16* path_array[][18 ], Cell cell_map[][18 ]);
void init_ghost_paths(Ghost *ghost1, Ghost *ghost2, Ghost *ghost3, Ghost *ghost4, Cell cell_map[][18 ]);
bool check_collision (Pacman* pacman, UINT16 object_x_position, UINT16 object_y_position);
# 101 "./model.h"
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
# 34 "model.c"
Cell cell_map[11 ][18 ];

UINT16 tile_map[11 ][18 ] = {

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
# 64 "model.c"
Ghost crying_ghost = {
    0,0,
    0,0,
    0,
    1 ,
    0 


};
Ghost moustache_ghost = {
    0,0,
    0,0,
    0,
    1 ,
    0 
};
Ghost cyclops_ghost = {
    0,0,
    0,0,
    0,
    1 ,
    0 
};
Ghost awkward_ghost = {
    0,0,
    0,0,
    0,
    1 ,
    0 
};
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


void init_map_cells( Cell cell_map[][18 ] )
{
# 128 "model.c"
    int i, j;
    for (i=0; i <= 11 ; i++){
        for(j=0; j <= 18 ; j ++){
            cell_map[i][j].x_position = 31  + (j >> 5);
            cell_map[i][j].y_position = 20  + (i >> 5);
            if (tile_map[i][j] == 0) {
                cell_map[i][j].open_path = 1 ;
            } else {
                cell_map[i][j].open_path = 0 ;
            }
        }
    }

     for (i=0; i <= 11 ; i++){
        for(j=0; j <= 18 ; j ++){

            printf("%u,",cell_map[i][j]);
        }
        printf("\n,");
    }

}
void set_ghost_path(Ghost *ghost, UINT16* path_array[][18 ], Cell cell_map[][18 ]) {
    int i, j;
    for (i = 0; i < 11 ; i++) {
        for (j = 0; j < 18 ; j++) {
            ghost->path[i][j].x_position = cell_map[i][j].x_position;
            ghost->path[i][j].y_position = cell_map[i][j].y_position;
            if (path_array[i][j] == 0) {
                ghost->path[i][j].open_path = 1 ;
            } else {
                ghost->path[i][j].open_path = 0 ;
            }

        }

    }
}
void init_ghost_paths(Ghost *ghost1, Ghost *ghost2, Ghost *ghost3, Ghost *ghost4, Cell cell_map[][18 ]) {
    UINT16 crying_ghost_path[11 ][18 ] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,0,1,0,1,0,1,1,1,1,1,0,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
        {1,0,1,0,1,1,0,1,0,0,1,0,1,1,0,1,0,1},
        {1,0,0,0,0,0,0,1,1,1,1,0,1,1,0,0,0,1},
        {1,1,1,0,1,1,0,0,0,0,0,0,1,1,0,1,0,1},
        {1,0,1,0,0,0,0,0,1,1,1,0,0,0,0,1,0,1},
        {1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
    UINT16 awkward_ghost_path[11 ][18 ] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,0,1,0,1,0,1,1,1,1,1,0,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
        {1,0,1,0,1,1,0,1,0,0,1,0,1,1,0,1,1,1},
        {1,0,0,0,0,0,0,1,1,1,1,0,1,1,0,0,0,1},
        {1,1,1,0,1,1,0,0,0,0,0,0,1,1,0,1,0,1},
        {1,0,1,0,0,0,0,0,1,1,1,0,0,0,0,1,0,1},
        {1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
    UINT16 moustache_ghost_path[11 ][18 ] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,0,1,0,1,1,1,1,1,1,1,0,1},
        {1,0,1,0,0,0,0,0,0,0,1,0,0,0,0,1,0,1},
        {1,0,1,0,1,1,0,1,0,0,1,0,1,1,0,1,0,1},
        {1,0,0,0,0,0,0,1,1,1,1,0,1,1,0,0,0,1},
        {1,1,1,0,1,1,0,0,0,0,0,0,1,1,0,1,0,1},
        {1,0,1,0,0,0,0,0,1,1,1,0,0,0,0,1,0,1},
        {1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,1,0,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
    UINT16 cyclops_ghost_path[11 ][18 ] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,1,0,1,0,1,0,1,1,1,1,1,0,1},
        {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
        {1,0,1,0,1,1,0,1,0,0,1,0,1,1,0,1,1,1},
        {1,0,0,0,0,0,0,1,1,1,1,0,1,1,0,0,0,1},
        {1,1,1,0,1,1,0,0,0,0,0,0,1,1,1,1,0,1},
        {1,0,1,0,0,0,0,0,1,1,1,0,0,0,0,1,0,1},
        {1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };
    set_ghost_path(ghost1, &crying_ghost_path, cell_map);
    set_ghost_path(ghost2, &moustache_ghost_path, cell_map);
    set_ghost_path(ghost3, &cyclops_ghost_path, cell_map);
    set_ghost_path(ghost4, &awkward_ghost_path, cell_map);
}

void move_pacman_position(Pacman *pacman, char input)
{
    bool collision;
	UINT16 new_x_position, new_y_position;
    pacman -> delta_y = 0;
    pacman -> delta_x = 0;
    pacman->direction = 0;

	switch(input)
	{
		case 'w': pacman -> delta_y = -1;
            pacman->direction = 1;
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
# 274 "model.c"
    collision = check_collision(&pacman, new_x_position, new_y_position);




    if (collision == 0)
    {
        printf("MOVING HIM");
        pacman->x = new_x_position;
		pacman->y = new_y_position;


    }
# 299 "model.c"
}
# 308 "model.c"
void increase_ghost_velocity (Ghost *ghost, UINT16 vertical_velocity, UINT16 horizontal_velocity)
{

	ghost->delta_x = horizontal_velocity;
	ghost->delta_y = vertical_velocity;

}
# 329 "model.c"
void move_ghost_position (Ghost *ghost, int current_x, int current_y)
{
# 348 "model.c"
}

bool check_collision (Pacman* pacman, UINT16 object_x_position, UINT16 object_y_position)
{

    bool collision  = 0 ;

    if (cell_map[object_y_position][object_x_position].open_path == 0 ) {
        collision = 1 ;
        printf(" collision \n");
        printf("This value is for collision is: %d\n",tile_map[object_y_position][object_x_position]);
    }
    else{
        printf(" YOURE GOOD: %d\n",tile_map[object_y_position][object_x_position]);
    }


    return collision;


}
