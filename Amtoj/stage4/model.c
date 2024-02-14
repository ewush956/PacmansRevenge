#include "TYPES.H"
#include "model.h"
#include "bitmaps.h"
#include "events.h"
#include <stdio.h>

#define MAX_MAP_LENGTH 18          /* 18 horiz walls x 32 pixels = 576 */
#define MAX_MAP_HEIGHT 11         /* 11 vert walls x 32 pixels = 352   */

/*
const UINT32* sprites[] = {
    pac_1, pac_2, pac_3, pac_4,
    evil_pac_1, evil_pac_2, evil_pac_3, evil_pac_4,
    ghost_1_up, ghost_1_down, ghost_1_left, ghost_1_right,
    ghost_2_up, ghost_2_down, ghost_2_left, ghost_2_right,
    ghost_3_up, ghost_3_down, ghost_3_left, ghost_3_right,
    ghost_4_up, ghost_4_down, ghost_4_left, ghost_4_right,
    wall_left_down_right, wall_up_down, wall_left_right, wall_down_right,
    tombstone, ghost_run, ghost_freeze
};
*/


/*
0 is a open square and 
1 is a horizontal wall
2 iS a vertical wall 
3 is a left-down (LD)
4 is RD
5 is LU
6 is UR (up -> right)
*/

Cell cell_map[MAP_TILE_HEIGHT][MAP_TILE_LENGTH];

UINT16 tile_map[MAP_TILE_HEIGHT][MAP_TILE_LENGTH] = {
/*0                               18*/
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



/*
Pacman pacman = {
    X_PIXEL_OFFSET, Y_PIXEL_OFFSET,        /*Initial position, won't actually be 0,0*/
   /* 0,0,        /*Initial Displacement
    0,          /*Initial state index
    UP,         /*Initial direction
    FALSE,       /*Initial state
};
*/


Ghost crying_ghost = {
    0,0,
    0,0,
    0,
    UP,
    FALSE
               /*Or whatever cell it starts in*/
 
};
Ghost moustache_ghost = {
    0,0,
    0,0,
    0,
    UP,
    FALSE
};
Ghost cyclops_ghost = {
    0,0,
    0,0,
    0,
    UP,
    FALSE
};
Ghost awkward_ghost = {
    0,0,
    0,0,
    0,
    UP,
    FALSE
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


void init_map_cells( Cell cell_map[][MAP_TILE_LENGTH] )
{
    /*
    UINT16 tile_map[MAP_TILE_HEIGHT][MAP_TILE_LENGTH] = {

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
    };*/
    int i, j;
    for (i=0; i <= MAP_TILE_HEIGHT; i++){
        for(j=0; j <= MAP_TILE_LENGTH; j ++){
            cell_map[i][j].x_position = X_PIXEL_OFFSET + (j >> 5);
            cell_map[i][j].y_position = Y_PIXEL_OFFSET + (i >> 5); /* changed from <<*/
            if (tile_map[i][j] == 0) {
                cell_map[i][j].open_path = TRUE; 
            } else {
                cell_map[i][j].open_path = FALSE; 
            }
        }
    }

     for (i=0; i <= MAP_TILE_HEIGHT; i++){
        for(j=0; j <= MAP_TILE_LENGTH; j ++){
           
            printf("%d,",cell_map[i][j].open_path);
        }
        printf("\n,");
    }

}
void set_ghost_path(Ghost *ghost, UINT16* path_array[][MAP_TILE_LENGTH], Cell cell_map[][MAP_TILE_LENGTH]) {
    int i, j;
    for (i = 0; i < MAP_TILE_HEIGHT; i++) {
        for (j = 0; j < MAP_TILE_LENGTH; j++) {
            ghost->path[i][j].x_position = cell_map[i][j].x_position;
            ghost->path[i][j].y_position = cell_map[i][j].y_position;
            if (path_array[i][j] == 0) {
                ghost->path[i][j].open_path = TRUE;
            } else {
                ghost->path[i][j].open_path = FALSE;
            }

        }

    }
}
void init_ghost_paths(Ghost *ghost1, Ghost *ghost2, Ghost *ghost3, Ghost *ghost4, Cell cell_map[][MAP_TILE_LENGTH]) {
    
    UINT16 crying_ghost_path[MAP_TILE_HEIGHT][MAP_TILE_LENGTH] = {
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
    UINT16 awkward_ghost_path[MAP_TILE_HEIGHT][MAP_TILE_LENGTH] = {
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
    UINT16 moustache_ghost_path[MAP_TILE_HEIGHT][MAP_TILE_LENGTH] = {
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
    UINT16 cyclops_ghost_path[MAP_TILE_HEIGHT][MAP_TILE_LENGTH] = {
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

bool move_pacman_position(Pacman *pacman) 
{
    bool can_movec = FALSE;
	UINT16 new_x_position, new_y_position;
    /*
    pacman -> delta_y = 0;
    pacman -> delta_x = 0;              /* make this better? how to reset it everytime?
    pacman->direction = 0;
     */

	new_x_position = pacman->x + pacman->delta_x;
	new_y_position = pacman->y + pacman->delta_y;


    

    /*pacman->has_collided == FALSE) */

    can_move = check_collision(&pacman, new_x_position, new_y_position);

/* below for the events that handle this*/
    if (can_move == FALSE)
    {
        pacman->x = new_x_position;
		pacman->y = new_y_position;
        pacman->current_cell = &cell_map[MAP_TILE_HEIGHT][MAP_TILE_LENGTH];
        printf("Direction: %d\n",pacman->direction);
       
    }


    return can_move;
	
	
}


/* the end game conditon would call this..? 
*
* increase both vert and horizontal speed to capture pacman and end game
*  leave in x-y parameters now but later we can just use a constant 
*
*/
void increase_ghost_velocity (Ghost *ghost, UINT16 vertical_velocity, UINT16 horizontal_velocity)
{
	
	ghost->delta_x = horizontal_velocity;
	ghost->delta_y = vertical_velocity;
	
}
/* 
*	This is for checking if the ghost struct in 'model.h' is working correcctly 
*    
*	-Used ints for moving backwards by adding negatives 
*

*/

/* pass in the current posiition into this and update accordingly 
/* make different instances of ghosts in test main program to call
*/
/*bool move_ghost_position (Ghost *ghost,Pacman* pacman, int current_x, int current_y)*/

void move_ghost_position (Ghost *ghost, UINT16* ghost_path[][MAP_TILE_LENGTH],Cell *cell_map[][MAP_TILE_LENGTH])
{
 

    /* randomize it ...? */
    
    int random_direction = 0;

    if(ghost_path[ghost -> y][ghost -> x + 1] == TRUE)          /* can move right*/
        random_direction |= RIGHT;

    if(ghost_path[ghost -> y][ghost -> x - 1] == TRUE)          /* can move left*/
         random_direction |= LEFT;

    if(ghost_path[ghost -> y - 1][ghost -> x] == TRUE)      /* can move up*/
         random_direction |= UP;

    if(ghost_path[ghost -> y + 1][ghost -> x] == TRUE)
         random_direction |= DOWN;
        
 
         /* maybe randomize number mod 4 then get direction based upon that then move that way 
         by incrementing correpd x or y posisition? */
 
 
 /*!!!!! also change function protype in the model.h   */
 
 
 
    /**** this code below is what we talked about returns a bool based upon if obj can move ****

	bool can_move = FALSE;
    UINT16 new_x_position, new_y_position;
    
    new_x_position = ghost->x += delta_x;
    new_y_position = ghost->y += delta_y;

    can_move = check_collision(new_x_position,new_y_position);
        
    return can_move;          

    **************/


    /*      use in events not here
    if (pacman->direction == UP)
        ghost->direction = DOWN;   

    if (pacman->direction == DOWN)
        ghost->direction = UP;

     if (pacman->direction == LEFT)
        ghost->direction = RIGHT;   

    if (pacman->direction == RIGHT)
        ghost->direction = LEFT;   
    */

    
    /* then check for collsion if collsion then try a different direction and repreat */
}
bool check_collision (UINT16 object_x_position, UINT16 object_y_position)
{

    bool collision  = FALSE; 

    if (cell_map[object_y_position][object_x_position].open_path == FALSE) {
        collision = TRUE;

        printf(" collision \n");
        printf("This value is for collision is: %d\n",tile_map[object_y_position][object_x_position]);
    }
    
    else{
        printf(" YOURE GOOD: %d\n",tile_map[object_y_position][object_x_position]);
    }

    

    return collision;


}


/*
bool check_collision (Pacman* pacman, UINT16 object_x_position, UINT16 object_y_position)
{
    
    bool collision = 0; 

    /* checking if the location is occupied by a wall or corner sprite */
    /*if (tile_map[object_y_position][object_x_position] == 1 || 
        tile_map[object_y_position][object_x_position] == 2 ||
        tile_map[object_y_position][object_x_position] == 3 ||
        tile_map[object_y_position][object_x_position] == 4 ||
        tile_map[object_y_position][object_x_position] == 5 ||
        tile_map[object_y_position][object_x_position] == 6)
        {
            
            /*pacman-> has_collided = TRUE;
            printf(" collision \n");
            printf("This value is for collision is: %d\n",tile_map[object_y_position][object_x_position]);
         /*   printf("Direction: %d\n", pacman->direction);
            collision = 1;

        }

        else{

            printf(" YOURE GOOD: %d\n",tile_map[object_y_position][object_x_position]);
            printf("Direction: %u\n", pacman->direction);
        }
        /*
            pacman->has_collided = FALSE;
            

        return collision; 

}
*/