void render_pacman(Pacman *pacman, Ghost *ghost) {
    /*
    Amtoj
    1) Figure out pacman->delta_x and y based on direction 
    2) call move_pacman_position and pass in new 
    3) check return status -> if true, call handle_pacman_collision
    
    use check_next_cell(pacman->direction, pacman->x_cell_index, pacman->y_cell_index)*/

    /*later stage use this */
    UINT8 collision_type; 

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