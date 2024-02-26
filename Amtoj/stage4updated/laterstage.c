void render_pacman(Pacman *pacman, Ghost *ghost) {
    /*
    Amtoj
    1) Figure out pacman->delta_x and y based on direction 
    2) call move_pacman_position and pass in new 
    3) check return status -> if true, call handle_pacman_collision
    
    use check_next_cell(pacman->direction, pacman->x_cell_index, pacman->y_cell_index)*/

    /*later stage use this */
    UCHAR8 collision_type; 

    collision_type = check_collision(&ghost,&pacman,pacman->y,pacman->x);

    if (collision_type == NO_COLLISION)
        move_ghost(&pacman);
    else
         handle_pacman_collsion(collision_type);
}  
/*, UINT16 delta_x, UINT16 delta_y) */


     /*
   bool collided = FALSE;
    new_x_position = pacman->x + pacman->delta_x;
	new_y_position = pacman->y + pacman->delta_y;
    collided = check_collision(new_x_position, new_y_position);
    */

    /*
    if (collided == FALSE){

        /*handle_collsion()
        pacman->x = new_x_position;
		pacman->y = new_y_position;
        /*pacman->current_cell = &cell_map[MAP_TILE_HEIGHT][MAP_TILE_LENGTH]; 
        wefixed this so erpace with the updated code 
        
        printf("Direction: %d\n",pacman->direction);
       
    }
    */

    /* return has he collided false is NO 

    return collided;*/






/***********************************evan stuff*******************************************/

/*bool check_next_cell(int dirrection, int x_cell_index, int y_cell_index);*/
bool check_next_cell(int dirrection, int x_cell_index, int y_cell_index){
    /*returns true if the next cell in corresponding dirrection has an an open path, false otherwise*/
    switch(dirrection) {
        case UP:
            if (cell_map[y_cell_index - 1][x_cell_index].open_path == FALSE) {
                return FALSE;
            }
            break;
        case DOWN:
            if (cell_map[y_cell_index + 1][x_cell_index].open_path == FALSE) {
                return FALSE;
            }
            break;
        case LEFT:
            if (cell_map[y_cell_index][x_cell_index - 1].open_path == FALSE) {
                return FALSE;
            }
            break;
        case RIGHT:
            if (cell_map[y_cell_index][x_cell_index + 1].open_path == FALSE) {
                return FALSE;
            }
            break;
        return TRUE;
    }
}


void render_timer(Timer* timer) {
    /*
    Evan
    every 70 clock ticks timer.second++*/
    timer->seconds++;
    if (timer->seconds == 60) {
        timer->seconds = 0;
        timer->minutes++;
    }
    if (timer->minutes < 10) {
        /*plot_letter(base8, timer->MS_digit_minutes, 0, '0');
        plot_letter(base8, timer->x, timer->y, timer->minutes);
        */
    }
    else {
        
    }
    /*plot_letter(base8, timer) */
    
}



/*----------------*/
#include "TYPES.H"
#include "model.h"
#include "bitmaps.h"
/*#include "map_plot.c"*/

const UCHAR8 map[][25];	/* I don't know how many */

const ULONG32 default_pac_sprites[][4];
const ULONG32 evil_pac_sprites[][4];
const ULONG32 crying_ghost_sprites[][4];
const ULONG32 moustache_ghost_sprites[][4];
const ULONG32 cyclops_ghost_sprites[][4];
const ULONG32 awkward_ghost_sprites[][4];

const ULONG32* default_pacman_sprites[4][4] = {
    {pac_1, pac_2, pac_3, pac_4},
    {pac_1, pac_2, pac_3, pac_4}
};
const ULONG32* evil_pacman_sprites[4][4] = {
    {evil_pac_1, evil_pac_2, evil_pac_3, evil_pac_4},
    {evil_pac_1, evil_pac_2, evil_pac_3, evil_pac_4}
};


Cell cell_map[MAP_TILE_HEIGHT][MAP_TILE_LENGTH];

Pacman pacman = {
    PIXELS_PER_CELL * 19, PIXELS_PER_CELL * 21 + Y_PIXEL_OFFSET,        /*Initial position, won't actually be 0,0*/
    0,0,        /*Initial Displacement*/
    0,          /*Initial state index*/
    UP,         /*Initial direction*/
    FALSE,       /*Initial state*/

};

Ghost crying_ghost = {
    PIXELS_PER_CELL * 17, PIXELS_PER_CELL * 10 + Y_PIXEL_OFFSET,      /*starts in [10][18]*/
    0,0,
    0,
    UP,
    FALSE
               /*Or whatever cell it starts in*/
 
};
Ghost moustache_ghost = {
    PIXELS_PER_CELL * 21, PIXELS_PER_CELL * 10 + Y_PIXEL_OFFSET,
    0,0,
    0,
    UP,
    FALSE
};
Ghost cyclops_ghost = {
    PIXELS_PER_CELL * 17, PIXELS_PER_CELL * 12 + Y_PIXEL_OFFSET,
    0,0,
    0,
    UP,
    FALSE
};
Ghost awkward_ghost = {
    PIXELS_PER_CELL * 21, PIXELS_PER_CELL * 12 + Y_PIXEL_OFFSET,
    0,0,
    0,
    UP,
    FALSE
};

Timer timer = {
    0,0,
    20, 28, 44, 52
};


void move_pacman (Pacman *pacman)
{
    pacman -> x += pacman->delta_x;
    pacman -> y += pacman->delta_y;
    
}

void increase_ghost_velocity (Ghost *ghost, UINT16 vertical_velocity, UINT16 horizontal_velocity){
	
	ghost->delta_x = horizontal_velocity;
	ghost->delta_y = vertical_velocity;
		
}

void move_ghost (Ghost *ghost, Cell *cell_map[][MAP_TILE_LENGTH], int new_x, int new_y){
    /*Amtoj is doing this, if you are evil pacman you should NOT even be READING this, GO AWAY! */
    return;


}/* 
bool check_collision (UINT16 object_x_position, UINT16 object_y_position){
  
    bool collision = FALSE; 

    if (cell_map[object_y_position][object_x_position].open_path == FALSE) {
        collision = TRUE;
        printf(" collision \n");
        printf("This value is for collision is: %d\n",tile_map[object_y_position][object_x_position]);
    }
    /*remove this before submit
    else if (p)
    else{
        printf(" YOURE GOOD: %d\n",tile_map[object_y_position][object_x_position]);
    }

    return collision;


}
*/

/* * * * * * * * * * * * * * 
* Trying this as now we have a case where we can handle colliding with a ghost
* without using two spearate check_collsions() funcs
*
* * * * * * * * * * * * * * */
/*UCHAR8 check_collision(Ghost *ghost, Pacman *pacman, UINT16 object_y_position, UINT16 object_x_position)*/
UCHAR8 check_collision(Entities* entity, UINT16 object_y_position, UINT16 object_x_position)
{  
    UCHAR8* collision = 0;
   /* Enitites *crying = entity->crying_ghost; */


    if (cell_map[object_y_position][object_x_position].open_path == FALSE) 
        collision = WALL;                       /*defined in types.h*/

    else if (entity.crying_ghost->x == entity.pacman->x && entity.crying_ghost->y == entity.pacman->y)
        collision = OBJECT;
    
    else if (entity->moustache_ghost->x == entity->pacman-> x && entity->moustache_ghost->y == entity->pacman->y)
        collision = OBJECT;
    
    else if (entity->awkward_ghost->x == entity->pacman->x && entity->awkward_ghost->y == entity->pacman->y)
        collision = OBJECT;

    else if (entity->cyclops_ghost->x == entity->pacman->x && entity->cyclops_ghost->y == entity->pacman->y)
        collision = OBJECT;


    return collision;

}
void init_map_cells(Cell cell_map[][MAP_TILE_LENGTH]){

    int i, j;
    for (i=0; i <= MAP_TILE_HEIGHT; i++){
        for(j=0; j <= MAP_TILE_LENGTH; j ++){
            cell_map[i][j].x_position = X_PIXEL_OFFSET + (j << 4); /*MULTIPLYING!!! by 16:))))*/
            cell_map[i][j].y_position = Y_PIXEL_OFFSET + (i << 4);
            if (tile_map[i][j] == 0) {
                cell_map[i][j].open_path = TRUE;
            } else {
                cell_map[i][j].open_path = FALSE;
            }
        }
    }
}
void set_ghost_path(Ghost *ghost, UINT16* path_array[][MAP_TILE_LENGTH], Cell cell_map[][MAP_TILE_LENGTH]) {

    /*

    probably wont use this, might use djsktras from running
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
    */
}
void update_cell(int* x_index, int* y_index) {
    /*Evans Doing this
    update sprite cell indeces, mod 16 or something
    */
   if (*x_index % PIXELS_PER_CELL == 0) {
       *x_index = (*x_index)++;
   }

   if (*y_index % PIXELS_PER_CELL == 0) {
       *y_index = (*y_index)++;
   }

}
void handle_collisions(Entities* entity, Xor *xor) {

    /*UCHAR8 collision_type;*/
    Pacman* pac = entity->pacman;
    Ghost* moustache = entity->moustache_ghost;
    Ghost* crying = entity->crying_ghost;
    Ghost* cyclops = entity->cyclops_ghost;
    Ghost* awkward = entity->awkward_ghost;

    if (check_collision(entity, pac->y_cell_index, 
                                    pac->x_cell_index, 
                                    pac->delta_y, 
                                    pac->delta_x,
                                    pac->type) != NO_COLLISION) {
        handle_pacman_collision(collision_type, pac);


    if (check_collision(entity, awkward->y_cell_index, 
                                    awkward->x_cell_index, 
                                    awkward->delta_y, 
                                    awkward->delta_x,
                                    awkward->type) != NO_COLLISION)
        handle_ghost_collision(collision_type, awkward, cell_map, xor);
    

    if (check_collision(entity, moustache->y_cell_index, moustache->x_cell_index, 
                moustache->delta_y, moustache->delta_x,
                moustache->type) != NO_COLLISION)
        handle_ghost_collision(collision_type, moustache, cell_map, xor);
            

    if(check_collision(entity, crying->y_cell_index, 
                                    crying->x_cell_index, 
                                    crying->delta_y, 
                                    crying->delta_x,
                                    crying->type) != NO_COLLISION) 
                                    {
        handle_ghost_collision(collision_type, crying, cell_map, xor);
    }

    if(check_collision(entity, cyclops->y_cell_index, 
                                    cyclops->x_cell_index, 
                                    cyclops->delta_y, 
                                    cyclops->delta_x,
                                    cyclops->type) != NO_COLLISION)
                                    {
        handle_ghost_collision(collision_type, cyclops, cell_map, xor);
    }
}


/***********************************feb 23 today***********************/


#include "bitmaps.h"
#include "model.h"
#include "TYPES.H"
#include "events.h"
#include <stdio.h>

/*********************************************************************************
*   This function handles collisions between a ghost and a wall in the game environment.
*   If a collision with a wall occurs, the function determines possible directions the ghost
*   can move to and selects one of them randomly. It uses an XOR algorithm to generate a random 
*   number, which is then modded by the available directions to choose a random direction.
*   
*   Parameters:
*      - collision_type: An integer representing the type of collision (e.g., WALL).
*      - ghost: A pointer to the Ghost structure representing the ghost involved in the collision.
*      - cell_map: A 2D array representing the game map.
*      - xor_shift_struct: A pointer to the XOR shift structure used for random number generation.
*
*   Note: This function is currently not functional due to a bug with random number generation
*         and a logic error.
 *************************************************************************************/
void handle_ghost_collision(UCHAR8 collision_type, Ghost* ghost, Cell cell_map[][MAP_TILE_LENGTH], Xor *xor_shift_struct) {
  
    UCHAR8 possible_direction = 0;
    ULONG32 random_number;
    UCHAR8 counter = 0;
    UCHAR8 prev_direction = ghost -> direction;

    if (collision_type == WALL)
    {
        
        if (cell_map[ghost->y_cell_index][ghost -> x_cell_index + 1].open_path == TRUE )
        {
            possible_direction |= RIGHT_RANDOM;
          
        }
        if (cell_map[ghost->y_cell_index][ghost->x_cell_index - 1].open_path == TRUE)
        {
            possible_direction |= LEFT_RANDOM;
          
        }
        if (cell_map[ghost->y_cell_index + 1][ghost->x_cell_index].open_path == TRUE)
        {
            possible_direction |= DOWN_RANDOM;
          
        }

        if (cell_map[ghost-> y_cell_index - 1][ghost->x_cell_index].open_path == TRUE)
        {
            possible_direction |= UP_RANDOMN;
           
        }

        /* make an array of different possibilities.. to make it more random?*/
        
        if(possible_direction & 0x04)
            ghost -> direction = LEFT;            /*add this back later*/

        if (possible_direction & 0x01)
            ghost -> direction = UP;

        else if(possible_direction & 0x08)
            ghost -> direction = RIGHT;

        else
            ghost -> direction = DOWN;
    }
    
 
}
/*************************************************************
 * Function: handle_pacman_collision
 * Purpose: Handles collisions between pacman and other entities
 * Parameters: ObjectType object_type - The type of object
 *              Entities* entity - Pointer to the entity
 * Details: 
 * the OPEN_PATH case will lock pacmans x / y movement to valid positions
****************************************************************/
void handle_pacman_collision(ObjectType object_type, Entities* entity) {

    /*if pacman collides w ghost call init_tombstone then de_render_ghost then render_tombstone*/
    Pacman *pacman = entity->pacman;
    
    switch(object_type)
    {
    case OPEN_PATH:
        if (entity->pacman->direction == UP || entity->pacman->direction == DOWN) {
            pacman->x = pacman->x_cell_index * PIXELS_PER_CELL;
        }
        else if (entity->pacman->direction == LEFT || entity->pacman->direction == RIGHT) {
            pacman->y = pacman->y_cell_index * PIXELS_PER_CELL + PIXELS_PER_CELL;
        }
        break;

    case WALL:
        pacman->delta_y = 0;
        pacman->delta_x = 0;
        
        break;
    case GHOST_TYPE_CRYING:
       /* kill_ghost(&entity->crying_ghost, cell_map);*/                     
        break;

    case GHOST_TYPE_AWKWARD:
        break;
    
    case GHOST_TYPE_MOUSTACHE:
        break;

    case GHOST_TYPE_CYCLOPS:
        break;        
    }
}
/***********************************************************
*  Uses an XOR shift algorthm to generate a random number 
*   -For randomizing direction of any ghost
*    
*   @return 'state' this is the random number that is returned
*
***********************************************************/
void handle_collisions(Entities* entity, Xor *xor) {

    ObjectType collision_type;
    Pacman* pac = entity->pacman;
    Ghost* moustache = entity->moustache_ghost;
    Ghost* crying = entity->crying_ghost;
    Ghost* cyclops = entity->cyclops_ghost;
    Ghost* awkward = entity->awkward_ghost;

    collision_type = check_pacman_collision(entity, pac->y_cell_index, 
                                    pac->x_cell_index, 
                                    pac->delta_y, 
                                    pac->delta_x);
    handle_pacman_collision(collision_type, entity); 
    /*NOTE:
     currently handle_pacman_collision is handling all cases, thats why it's not in an if block
    we should change that at some point but my brain hurts and I no no wanna :(*/
    


    collision_type = check_collision(entity, awkward->y_cell_index, 
                                    awkward->x_cell_index, 
                                    awkward->delta_y, 
                                    awkward->delta_x,
                                    awkward->type);
    
    if (collision_type != OPEN_PATH)
    {
        handle_ghost_collision(collision_type, awkward, cell_map, xor);
        
    }
    else
    {
        update_awkward_direction(awkward);
        move_ghost(awkward);
    }
                
    collision_type = check_collision(entity, moustache->y_cell_index, 
                                    moustache->x_cell_index, 
                                    moustache->delta_y, 
                                    moustache->delta_x,
                                    moustache->type);
    if (collision_type != OPEN_PATH)
        handle_ghost_collision(collision_type, moustache, cell_map, xor);
    else   
    {    
        if (cell_map[moustache->y_cell_index - 1][moustache->x_cell_index].open_path == TRUE)
        {   
            moustache -> direction = UP;
            move_ghost(moustache);
        }
        else if (cell_map[moustache->y_cell_index][moustache->x_cell_index+1].open_path == TRUE)
        {
            moustache -> direction = RIGHT;
            move_ghost(moustache);
        }

    }
    

    collision_type = check_collision(entity, crying->y_cell_index, 
                                    crying->x_cell_index, 
                                    crying->delta_y, 
                                    crying->delta_x,
                                    crying->type);
    if (collision_type != OPEN_PATH)
    {
        handle_ghost_collision(collision_type, crying, cell_map, xor);
        

    }
    else   
    {    
        update_crying_direction(crying);
        move_ghost(crying);

    }

    collision_type = check_collision(entity, cyclops->y_cell_index, 
                                    cyclops->x_cell_index, 
                                    cyclops->delta_y, 
                                    cyclops->delta_x,
                                    cyclops->type);
    if (collision_type != OPEN_PATH)
    {
      
        handle_ghost_collision(collision_type, cyclops, cell_map, xor);
        /*printf("cyclops ghost direction after %u\n",cyclops->direction);*/
      
    }
    else
    {
        if (cell_map[cyclops->y_cell_index][cyclops->x_cell_index+1].open_path == TRUE)
        {   
            cyclops -> direction = RIGHT;
            move_ghost(cyclops);
        }
        else if (cell_map[cyclops->y_cell_index-1][cyclops->x_cell_index].open_path == TRUE)
        {
            cyclops -> direction = LEFT;
            move_ghost(cyclops);
        }
    }

}
ULONG32 random_number_generator(Xor *xor)
{

    ULONG32 state = xor->value;

	state ^= state << 13;
	state ^= state >> 17;
	state ^= state << 5;
    xor->value = state;

    return state;
}
void set_input(Pacman *pacman, char input)
{

	pacman -> delta_y = 0;
    pacman -> delta_x = 0;
      

	switch(input)
	{
		case W_KEY: 
			pacman -> delta_y = -1;   		/* UP 1*/
            pacman -> delta_x = 0;
            pacman -> direction = UP; 
			break;
				
		case A_KEY: 
			pacman -> delta_x = -1;			/*Left 3*/
            pacman -> delta_y = 0;
            pacman -> direction = LEFT;
			break;
				
		case S_KEY: 
			pacman -> delta_y = 1;			/*Down 2*/
            pacman -> delta_x = 0;
            pacman -> direction = DOWN;
			break;
				
		case D_KEY: 
			pacman -> delta_x = 1;			/* Right 4*/
            pacman -> delta_y = 0;
            pacman -> direction = RIGHT;
			break;

		default:	
			break;
	}

}


void update_awkward_direction (Ghost *awkward )
{

        if (cell_map[awkward->y_cell_index +  1][awkward->x_cell_index].open_path == TRUE)
        {   
            awkward->direction = DOWN;
            
        }
         else if (cell_map[awkward->y_cell_index ][awkward->x_cell_index+1].open_path == TRUE)
        {   
            awkward->direction = RIGHT;
            
        }
        else if (cell_map[awkward->y_cell_index ][awkward->x_cell_index-1].open_path == TRUE)
        {   
            awkward->direction = LEFT;
            
        }
        else
        {
            awkward -> direction = UP;
                 
        }

}
void update_crying_direction(Ghost *crying)
{


    if (cell_map[crying->y_cell_index][crying->x_cell_index +1].open_path == TRUE)
         crying -> direction = RIGHT;
    
    else if (cell_map[crying->y_cell_index + 1][crying->x_cell_index].open_path == TRUE)
         crying -> direction = DOWN;
    
    else if (cell_map[crying->y_cell_index - 1][crying->x_cell_index].open_path == TRUE)
         crying -> direction = UP;
    else
        crying -> direction = LEFT;

            
        
}