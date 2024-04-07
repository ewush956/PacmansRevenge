#include "TYPES.H"
#include "model.h"
#include "bitmaps.h"
#include "effects.h"
#include "globals.h"
#include <stdio.h>

/*************************************************************
* Declaration: Cell cell_map[MAP_TILE_HEIGHT][MAP_TILE_LENGTH]
* Purpose: Represents the game's map, storing the state of each
*          cell (e.g., open path and relative pixle position).
*************************************************************/
Cell cell_map[MAP_TILE_HEIGHT][MAP_TILE_LENGTH];

void move_pacman (Pacman *pacman)
{
   Movement* pacman_movement = pacman->move;

    if (pacman_movement->delta_x == 0 && pacman_movement->delta_y == 0) {
        pacman_movement->last_last_x = pacman_movement->x;
        pacman_movement->last_last_y = pacman_movement->y;
        return;
    }
    
    pacman_movement->last_last_x = pacman_movement->last_x;
    pacman_movement->last_last_y = pacman_movement->last_y;

    pacman_movement->last_x = pacman_movement->x;
    pacman_movement->last_y = pacman_movement->y;

    pacman_movement->x += (pacman_movement->delta_x << 1);
    pacman_movement->y += (pacman_movement->delta_y << 1);
    align_axis(pacman_movement);
}
/*************************************************************
* Function: move_ghost
* Module: model
* Purpose: Updates a ghost's position based on its current velocity.
* Parameters: Ghost* ghost - Pointer to the Ghost structure.
* Details: Modifies the ghost's x and y coordinates by adding the current
*          delta_x and delta_y values. This change moves the ghost according to
*          its velocity, facilitating motion in the game world.
*************************************************************/
void move_ghost (Ghost *ghost)
{
    Movement* ghost_movement = ghost->move;
	UCHAR8 direction = ghost->move->direction;
    UINT16 x_cell_index = ghost->move->x_cell_index;
    UINT16 y_cell_index = ghost->move->y_cell_index;

    UINT16 old_x = ghost_movement->x;
    UINT16 old_y = ghost_movement->y;

    if (ghost->state == DEAD) { return; }
    
    switch(direction)
    {
        case UP:    set_deltas(ghost_movement, 0, -1); break;        
        case DOWN:  set_deltas(ghost_movement, 0, 1);  break;        
        case RIGHT: set_deltas(ghost_movement, 1, 0);  break;        
        case LEFT:  set_deltas(ghost_movement, -1, 0); break;
    }
    
    ghost_movement->last_last_x = ghost_movement->last_x;
    ghost_movement->last_last_y = ghost_movement->last_y;
    
    ghost_movement->last_x = ghost_movement->x;
    ghost_movement->last_y = ghost_movement->y;

    if (ghost->state == RUNNING) {
        ghost_movement-> x += (ghost_movement->delta_x << 1);
        ghost_movement-> y += (ghost_movement->delta_y << 1);
        if ((ghost_movement->x >> 4) != (old_x >> 4)) {
            ghost_movement->x -= ghost_movement->delta_x;
            align_axis(ghost_movement);
            return;
        }
        if ((ghost_movement->y >> 4) != (old_y >> 4)) {
            ghost_movement->y -= ghost_movement->delta_y;
            align_axis(ghost_movement);
            return;
        }
    } else {
        ghost_movement-> x += ghost_movement->delta_x;
        ghost_movement-> y += ghost_movement->delta_y;
    }
    align_axis(ghost_movement);
}
/*************************************************************
 * Function: check_wall_collision
 * Module: model
 * Purpose: Checks for collisions between an object and walls.
 * Parameters: Entities* entity - Pointer to the entities structure containing
 *              ghosts, UINT16 object_y_index - Y index of the object,
 *              UINT16 object_x_index - X index of the object,
 *              UINT16 y_delta - Y direction movement delta,
 *              UINT16 x_delta - X direction movement delta.
 * Details: Determines if the specified object's next position (based on deltas)
 *          will result in a collision with a wall.
 *          It returns WALL if a wall collision is detected, and 0 if no collision
 *          is detected.
 *************************************************************/
ObjectType check_wall_collision(Movement* entity) {

    UINT16 effective_y_position;
    UINT16 effective_x_position;
    UINT16 COLLISION_THRESHOLD = 4;
    UINT16 object_y_index = entity->y_cell_index;
    UINT16 object_x_index = entity->x_cell_index;
    int y_delta = entity->delta_y;
    int x_delta = entity->delta_x;

    if (cell_map[object_y_index + y_delta][object_x_index + x_delta].open_path == FALSE) {
        if ((entity->direction == UP || entity->direction == DOWN)) {
            effective_y_position = entity->y - COLLISION_THRESHOLD;
            if (effective_y_position <= (UINT16)cell_map[object_y_index][object_x_index].y_position)
                return WALL;
        }
        if ((entity->direction == LEFT || entity->direction == RIGHT)) {
            effective_x_position = entity->x - COLLISION_THRESHOLD;
            if (effective_x_position <= (UINT16)cell_map[object_y_index][object_x_index].x_position)
                return WALL;  
        }
    }
    return OPEN_PATH;
}
/***************************************************
 * Function: check_proximity
 * Module: model
 * Purpose: Checks if pacman and ghost are close, if they are it changes states
 * Parameters: Entities* all - Pointer to the entities structure containing
*******************************************************/
void check_proximity(Entities* all) {
    
    int ghostCountWithinRange = 0;
    int i;
    UINT16 pacman_x_index, pacman_y_index;
    UINT16 ghost_x_index, ghost_y_index;
    UINT16 x_distance, y_distance;

    Ghost *ghosts[4];
    ghosts[0] = all->crying_ghost;
    ghosts[1] = all->awkward_ghost;
    ghosts[2] = all->cyclops_ghost;
    ghosts[3] = all->moustache_ghost;

    pacman_x_index = all->pacman->move->x_cell_index;
    pacman_y_index = all->pacman->move->y_cell_index;

    for (i = 0; i < 4; i++) {

        if (ghosts[i]->state == DEAD) { continue; }

        ghost_x_index = ghosts[i]->move->x_cell_index;
        ghost_y_index = ghosts[i]->move->y_cell_index;

        if (pacman_x_index > ghost_x_index) {
            x_distance = pacman_x_index - ghost_x_index;
        } else {
            x_distance = ghost_x_index - pacman_x_index;
        }

        if (pacman_y_index > ghost_y_index) {
            y_distance = pacman_y_index - ghost_y_index;
        } else {
            y_distance = ghost_y_index - pacman_y_index;
        }

        if (x_distance <= PROXIMITY_THRESHOLD && y_distance <= PROXIMITY_THRESHOLD) {
            ghostCountWithinRange++;
            change_pacman_state(all->pacman, EVIL); 
            change_ghost_state(ghosts[i], RUNNING); 
        }
        else if (x_distance > EXIT_PROXIMITY || y_distance > EXIT_PROXIMITY){
            change_ghost_state(ghosts[i], DEFAULT);
        }
    }
    if (ghostCountWithinRange == 0) { change_pacman_state(all->pacman, DEFAULT); }
}

void change_pacman_state(Pacman* pacman, UCHAR8 new_state) {
    pacman->state = new_state;
}
void change_ghost_state(Ghost* ghost, UCHAR8 new_state) {
    if (ghost->state == DEAD) {
        return;
    }
    ghost->state = new_state;
}
void end_game() {

}

/*************************************************************
* Function: init_map_cells
* Purpose: Initializes the cell map with positions and path openness based on the tile map.
* Parameters: Cell cell_map[][MAP_TILE_LENGTH] - 2D array to store cell positions and status,
*             UINT16 tile_map[][MAP_TILE_LENGTH] - 2D array representing the layout of the map.
* Details: Iterates through each cell in the cell_map, setting its x and y positions based on
*          predefined offsets and its index. The open_path flag for each cell is set based on
*          the corresponding tile_map value, indicating whether the path is open (TRUE) or blocked (FALSE).
*************************************************************/
void init_map_cells(){
    int i, j;
    for (i=0; i < MAP_TILE_HEIGHT; i++){
        for(j=0; j < MAP_TILE_LENGTH; j ++){
            cell_map[i][j].x_position = (j << 4);  /* MULTIPLYING by 16 */
            cell_map[i][j].y_position = Y_PIXEL_OFFSET + (i << 4);
            if (tile_map[i][j] == 0) {
                cell_map[i][j].open_path = TRUE;
                cell_map[i][j].has_pellet = TRUE;
            } else {
                cell_map[i][j].open_path = FALSE;
                cell_map[i][j].has_pellet = FALSE;
            }
            if (i < (MAP_PIXEL_HEIGHT - 1) && 
               (tile_map[i+1][j] == 0)) {
                cell_map[i][j].can_go_down = TRUE;
            } else {
                cell_map[i][j].can_go_down = FALSE;
            }

            if (j < (MAP_PIXEL_LENGTH - 1) && (tile_map[i][j+1] == 0)) {
                cell_map[i][j].can_go_right = TRUE;
            } else {
                cell_map[i][j].can_go_right = FALSE;
            }

            if (tile_map[i-1][j] == 0 && i > 0) {
                cell_map[i][j].can_go_up = TRUE;
            } else {
                cell_map[i][j].can_go_up = FALSE;
            }

            if (tile_map[i][j-1] == 0 && j > 0) {
                cell_map[i][j].can_go_left = TRUE;
            } else {
                cell_map[i][j].can_go_left = FALSE;
            }
            
            init_map_cells_helper(direction_map,i,j);
        }
    }
    cell_map[10][17].has_pellet = FALSE;
    cell_map[10][18].has_pellet = FALSE;

    cell_map[10][20].has_pellet = FALSE;
    cell_map[10][21].has_pellet = FALSE;

    cell_map[12][17].has_pellet = FALSE;
    cell_map[12][18].has_pellet = FALSE;

    cell_map[12][20].has_pellet = FALSE;
    cell_map[12][21].has_pellet = FALSE;
}
/*********************
*   A helper funtion for initializing the map within in 
*   the loop from the calling function.
*******************/
void init_map_cells_helper(UCHAR8 direction_map[][40],int i, int j)
{

    switch (direction_map[i][j]) {
            case '^': cell_map[i][j].crying_path = UP;         break;
            case 'v': cell_map[i][j].crying_path = DOWN;       break;
            case '<': cell_map[i][j].crying_path = LEFT;       break;
            case '>': cell_map[i][j].crying_path = RIGHT;      break;
        }
        switch (direction_map2[i][j]) {
            case '^': cell_map[i][j].cyclops_path = UP;     break;
            case 'v': cell_map[i][j].cyclops_path = DOWN;   break;
            case '<': cell_map[i][j].cyclops_path = LEFT;   break;
            case '>': cell_map[i][j].cyclops_path = RIGHT;  break;
        }
        switch (direction_map3[i][j]) {
            case '^': cell_map[i][j].awkward_path = UP;    break;
            case 'v': cell_map[i][j].awkward_path = DOWN;  break;
            case '<': cell_map[i][j].awkward_path = LEFT;  break;
            case '>': cell_map[i][j].awkward_path = RIGHT; break;
        }
        switch (direction_map4[i][j]) {
            case '^': cell_map[i][j].moustache_path = UP;    break;
            case 'v': cell_map[i][j].moustache_path = DOWN;  break;
            case '<': cell_map[i][j].moustache_path = LEFT;  break;
            case '>': cell_map[i][j].moustache_path = RIGHT; break;
        }
}
/*************************************************************
* Function: update_cells
* Purpose: Updates the cell indices for movement calculations.
* Parameters: int* x_index - Pointer to the x index of a cell,
*             int* y_index - Pointer to the y index of a cell.
* Details: Increments the x and y cell indices if they are perfectly divisible by
*          PIXELS_PER_CELL, indicating a complete move into a new cell. This function
*          aids in tracking movement across cells in the game grid.
*************************************************************/
void update_cells(Entities* all) {
    
    
    Pacman* pacman = all->pacman;
    Ghost* crying = all->crying_ghost;
    Ghost* moustache = all->moustache_ghost;
    Ghost* cyclops = all->cyclops_ghost;
    Ghost* awkward = all->awkward_ghost;
    
    if (update_cell(awkward->move, awkward->state) == TRUE) {
        update_ghost_direction(awkward, pacman);
    }
    if (update_cell(moustache->move, moustache->state) == TRUE) {
        update_ghost_direction(moustache, pacman);
    }
    if (update_cell(crying->move, crying->state) == TRUE) {
        update_ghost_direction(crying, pacman);
    }
    if (update_cell(cyclops->move, cyclops->state) == TRUE) {
        update_ghost_direction(cyclops, pacman);
    }

    update_cell(pacman->move, DEFAULT);

}
/*Returns true if entity has entered a new cell*/
bool update_cell(Movement* entity, UCHAR8 state) {

    int x_index = entity->x_cell_index;
    int y_index = entity->y_cell_index;

    set_occupied(FALSE, y_index, x_index);
    if (state == DEAD) {
        return FALSE;
    }
    entity->x_cell_index = entity->x >> 4; 
    entity->y_cell_index = (entity->y >> 4) - 1;
    set_occupied(TRUE, y_index, x_index);

    if (((entity->x + entity->delta_x) & 15) == 0 || ((entity->y + entity->delta_y) & 15) == 0) {
        return TRUE;     
    }

    return FALSE;
}
/*************************************************************
 * Function: update_ghost_direction
 * Purpose: Updates the direction of the ghost relative position
 *          to pacman and the coresponding ghost path on cell map
 * Parameters: Ghost* ghost - Pointer to Ghost structure
 *             Pacman* pacman - Pointer to Pacman structure
 *************************************************************/
void update_ghost_direction(Ghost* ghost, Pacman* pacman) 
{
    Movement* ghost_movement  = ghost->move;
    Movement* pacman_movement = pacman->move;
    UCHAR8 ghost_path = ghost->path_number;
    UCHAR8 ghost_x_indx = ghost_movement->x_cell_index;
    UCHAR8 ghost_y_indx = ghost_movement->y_cell_index;

    bool reverse = FALSE;
    
    if (ghost->state == DEAD) { return; }
    if (ghost->state == RUNNING) {
        switch (pacman_movement->direction) {
            case UP:    if (pacman_movement->y_cell_index < ghost_y_indx) { reverse = TRUE; } break;
            case DOWN:  if (pacman_movement->y_cell_index > ghost_y_indx) { reverse = TRUE; } break;
            case LEFT:  if (pacman_movement->x_cell_index < ghost_x_indx) { reverse = TRUE; } break;
            case RIGHT: if (pacman_movement->x_cell_index > ghost_x_indx) { reverse = TRUE; } break;
        }
        if (reverse == TRUE) {
            flip_direction(pacman_movement);
            if (check_valid_path(ghost_movement, pacman_movement->direction) == TRUE) {
                ghost_movement->direction = pacman_movement->direction;
                flip_direction(pacman_movement);
                return;
            }
            flip_direction(pacman_movement);
        }
        else if (check_valid_path(ghost_movement, pacman_movement->direction) == TRUE )
        {
            ghost_movement->direction = pacman_movement->direction;
            return;
        }
        ghost_movement->direction = get_optimal_direction(ghost_movement, pacman_movement);
        return;
    }
    switch (ghost_path) 
    {
        case CRYING_PATH:    ghost_movement->direction = cell_map[ghost_y_indx][ghost_x_indx].crying_path;    break;
        case AWKWARD_PATH:   ghost_movement->direction = cell_map[ghost_y_indx][ghost_x_indx].awkward_path;   break;
        case CYCLOPS_PATH:   ghost_movement->direction = cell_map[ghost_y_indx][ghost_x_indx].cyclops_path;   break;
        case MOUSTACHE_PATH: ghost_movement->direction = cell_map[ghost_y_indx][ghost_x_indx].moustache_path; break;
    }
}

UCHAR8 get_optimal_direction(Movement* movement, Movement* pacman_movement) {
    UINT16 x = movement->x;
    UINT16 y = movement->y;

    UINT16 pac_x = pacman_movement->x;
    UINT16 pac_y = pacman_movement->y;

    switch (movement->direction) {
        case UP:
            if (cell_map[movement->y_cell_index][movement->x_cell_index].can_go_up    == TRUE) { return UP;    }
            if (cell_map[movement->y_cell_index][movement->x_cell_index].can_go_left  == TRUE) { return LEFT;  }
            if (cell_map[movement->y_cell_index][movement->x_cell_index].can_go_right == TRUE) { return RIGHT; }
            return DOWN;

        case DOWN:
            if (cell_map[movement->y_cell_index][movement->x_cell_index].can_go_down  == TRUE) { return DOWN;  }
            if (cell_map[movement->y_cell_index][movement->x_cell_index].can_go_right == TRUE) { return RIGHT; }
            if (cell_map[movement->y_cell_index][movement->x_cell_index].can_go_left  == TRUE) { return LEFT;  }
            return UP;

        case LEFT:
            if (cell_map[movement->y_cell_index][movement->x_cell_index].can_go_left  == TRUE) { return LEFT;  }
            if (cell_map[movement->y_cell_index][movement->x_cell_index].can_go_up    == TRUE) {
                if (y > MIDDLE_OF_SCREEN_Y) { return UP; }
            }
            if (cell_map[movement->y_cell_index][movement->x_cell_index].can_go_down  == TRUE) { return DOWN;  }
            return RIGHT;

        case RIGHT:
            if (cell_map[movement->y_cell_index][movement->x_cell_index].can_go_right == TRUE) { return RIGHT; }
            if (cell_map[movement->y_cell_index][movement->x_cell_index].can_go_down  == TRUE) {
                if (y < MIDDLE_OF_SCREEN_Y) { return DOWN; }
            }
            if (cell_map[movement->y_cell_index][movement->x_cell_index].can_go_up    == TRUE) { return UP;    }
            return LEFT;
    }
}
bool check_valid_path(Movement* movement, UCHAR8 direction) {
    switch (direction) {
        
        case UP:    return cell_map[movement->y_cell_index][movement->x_cell_index].can_go_up; 
        case DOWN:  return cell_map[movement->y_cell_index][movement->x_cell_index].can_go_down; 
        case LEFT:  return cell_map[movement->y_cell_index][movement->x_cell_index].can_go_left;
        case RIGHT: return cell_map[movement->y_cell_index][movement->x_cell_index].can_go_right;
    }
}
void set_occupied(bool set, int y_index, int x_index) {
    cell_map[y_index][x_index].occupied         = set;
    cell_map[y_index + 1][x_index].occupied     = set;
    cell_map[y_index][x_index + 1].occupied     = set;
    cell_map[y_index + 1][x_index + 1].occupied = set;
}
/*Checks if two ghosts share an occupied region
A ghost occupies 4 cells*/
bool check_shared_occupied(Movement* entity1, Movement* entity2) {
    int i, j, k, l;
    int ghost1_y, ghost1_x, ghost2_y, ghost2_x;

    for (i = 0; i < 2; ++i) {
        for (j = 0; j < 2; ++j) {
            ghost1_y = entity1->y_cell_index + i;
            ghost1_x = entity1->x_cell_index + j;
            for (k = 0; k < 2; ++k) {
                for (l = 0; l < 2; ++l) {
                    ghost2_y = entity2->y_cell_index + k;
                    ghost2_x = entity2->x_cell_index + l;
                    if (ghost1_y == ghost2_y && ghost1_x == ghost2_x && 
                        cell_map[ghost1_y][ghost1_x].occupied == TRUE) {
                        return TRUE;
                    }
                }
            }
        }
    }
    return FALSE;
    
}
/*************************************************************
* Function: kill_ghost
* Purpose: Marks a ghost as dead and updates the map accordingly.
* Parameters: Ghost* ghost - Pointer to the ghost to be marked dead,
*             Cell cell_map[][MAP_TILE_LENGTH] - The game's cell map.
* Details: This function changes the specified ghost's state to DEAD
*          and adds a wall (tombstone) to the map at the ghost's last position,
*          effectively removing the ghost from play and altering the map.
*************************************************************/
void kill_ghost(Ghost* ghost) {
    int y_cell_index, x_cell_index;

    if (ghost->state == DEAD) { return; }
    ghost->state = DEAD;

    ghost->move->x = (ghost->move->x_cell_index << 4);
    ghost->move->y = ((ghost->move->y_cell_index + 1) << 4);
    set_deltas(ghost->move, 0, 0);

    y_cell_index = ghost->move->y_cell_index;
    x_cell_index = ghost->move->x_cell_index;
    
    add_wall_to_map(y_cell_index, x_cell_index);
    if (kill_ghost_flag == FALSE)
        play_kill_ghost_sound();
        set_derender_ghost_flag(ghost, TRUE);
}
/*************************************************************
* Function: add_wall_to_map
* Purpose: Marks a specified cell in the map as a wall.
* Parameters: Cell cell_map[MAP_TILE_HEIGHT][MAP_TILE_LENGTH] - The game map's cell matrix,
*             int y_cell_index - The Y index of the cell to mark as a wall,
*             int x_cell_index - The X index of the cell to mark as a wall.
* Details: This function updates the cell at the specified indices
*          in the game map to indicate it is not an open path, effectively
*          making it a wall. This is used to dynamically alter the map's layout.
*************************************************************/
void add_wall_to_map(int y_cell_index, int x_cell_index) {
    cell_map[y_cell_index][x_cell_index].open_path  = FALSE;
    cell_map[y_cell_index][x_cell_index].has_pellet = FALSE;

    cell_map[y_cell_index+1][x_cell_index].open_path  = FALSE;
    cell_map[y_cell_index+1][x_cell_index].has_pellet = FALSE;

    cell_map[y_cell_index][x_cell_index+1].open_path  = FALSE;
    cell_map[y_cell_index][x_cell_index+1].has_pellet = FALSE;

    cell_map[y_cell_index+1][x_cell_index+1].open_path  = FALSE;
    cell_map[y_cell_index+1][x_cell_index+1].has_pellet = FALSE;

    cell_map[y_cell_index-1][x_cell_index].open_path  = FALSE;
    cell_map[y_cell_index-1][x_cell_index].has_pellet = FALSE;

}
void align_axis(Movement* entity) {

        if (entity->direction == UP || entity->direction == DOWN) { 
            entity->x = (entity->x_cell_index << 4);
        }
        else if (entity->direction == LEFT || entity->direction == RIGHT) {
            entity->y = (entity->y_cell_index + 1) << 4;
        }
}
void flip_direction(Movement* ghost) {
    UCHAR8 direction = ghost->direction;
    if (ghost->delta_x == 0 && ghost->delta_y == 0) {
        return;
    }
    if (direction == UP)
        direction = DOWN;

    else if (direction == DOWN)
        direction = UP;

    else if (direction == LEFT)
        direction = RIGHT;

    else 
        direction = LEFT;
}
void set_deltas(Movement* move, UINT16 dx, UINT16 dy) {
    move->delta_x = dx;
    move->delta_y = dy;
}
void update_current_frame(Entities* all, int clock) {
    Pacman* pacman = all->pacman;
    
    Ghost *ghosts[4];
    int i;
    ghosts[0] = all->crying_ghost;
    ghosts[1] = all->awkward_ghost;
    ghosts[2] = all->cyclops_ghost;
    ghosts[3] = all->moustache_ghost;

    if (pacman->state == DEFAULT) {

        pacman->current_frame = ((pacman->current_frame) + 1) & 7;
    }
    else {

        pacman->current_frame += 1;
        if (pacman->current_frame > 5) 
            pacman->current_frame -= 6;
        }
    
    for (i = 0; i < 4; i++) {

        if (ghosts[i]->state == DEFAULT && ((clock & 3) == 0) || (clock & 3) == 1) {
            ghosts[i]->current_frame = (ghosts[i]->current_frame + 1) & 1;
        }

    }
}
void update_timer()
{
    if (second_has_passed == TRUE) {
        timer.seconds_value -= 1;
        
        if (timer.seconds_value == 0) {
            game_over_flag = TRUE;
            return;
        }
       
        if (timer.LS_digit_ascii == '0') { 
            timer.LS_digit_ascii = '9'; 
            timer.MS_digit_ascii--; 
        } else {
            timer.LS_digit_ascii--; 
        }
        second_has_passed = FALSE;   
    }
}
void set_derender_ghost_flag(Ghost* ghost, bool flag) {
    
    switch (ghost->type ) {
        case GHOST_TYPE_AWKWARD: derender_awkward_flag = flag; break;
        case GHOST_TYPE_CYCLOPS: derender_cyclops_flag = flag; break;
        case GHOST_TYPE_MOUSTACHE: derender_moustache_flag = flag; break;
        case GHOST_TYPE_CRYING: derender_crying_flag = flag; break; 
    }
}
