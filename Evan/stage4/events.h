

#define WALL 0
#define OBJECT 1

void clock_tick_handle();		/* calls move pacman calls all synch event handlers */
void handle_pacman_collision(UINT8 collision_type, Pacman *pacman);
void handle_pacman_collision();