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