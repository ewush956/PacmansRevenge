# PacmansRevenge
Arcade style variant of the arcade game "Pacman" created for Computing Machinery II at Mount Royal University. This game is intended for the Steem emulator. Almost all reliance on the operating system has been removed, with the exception of the `Super()` system call. This project had the purpose of learning low-level programming and hardware interations, as such this project is specific to the MC68000 architecture.

## Known Bugs
1. Occasionally ghost movement causes half of a pellet sprite to render on either the back or the front buffer causing flickering.
This has been PARTIALLY fixed, the fix we came up with at re renders the pellet  but you can still see some flickering behind the ghost. 

2. Ghosts frames are not being updated properly, like an issue with ticks or seconds in ISR.C

3. The cyclops ghost's eye is not properly centered in some of it's alternate frames
causing the movement to look jittery. This is an issue with it's bitmap.

5. Ghosts don't clear properly when being eaten, and occasionally "jump" leaving a flickering, trail, this issue has been mostly resolved, but still occisionally leaves small pixels behind.

## Running the program

To run the program, simply type `compile.g` in the **GU** terminal.
This will execute a script that removes any object files and then runs the command `make all`.
This will create the following executables:
- `pacman`: Main game
- `tst_snd`: Music, effects, and PSG test driver
- `tst_rast`: Raster test driver
- `tst_rend`: Renderer test driver

# Detailed Game Specifications

**Course:** COMP 2659 Winter 2024  
**Instructor:** Marc Schroeder  
**Author(s):** Amtoj Punia and Evan Wushke  
**Last Modified:** April 8th, 2024  

## 1. General Game Overview
![Pacman's Revenge Splash Screen](screenshots/Screenshot%202024-04-07%20140225.png "Splash Screen")
Pacman wants to get revenge on the ghosts that have tormented him for years; however, he only has the strength to take on one ghost at a time.  
Your main objective is to corner and eat all of the ghosts without getting overpowered.

## 2. Game Play Details for Core 1-Player Version
![Pacman's Revenge Splash Screen](screenshots/Screenshot%202024-04-07%20140242.png "Splash Screen")
### Objectives and Rules

- Pacman Starts in the lower center of the map ghosts will start in the center and branch off to their respective static paths. There is a visible timer which will start at 99 and will increase in seconds.  
- The objective is to eat all the ghosts. Ghosts will not change their behavior unless Pacman reaches a certain proximity to one of them. Once Pacman is close to a ghost it will attempt to run to the farthest corner of the map relative to its current location. Once the ghost reaches the corner, if Pacman is still in the ghost's proximity it will freeze; if Pacman is not there, it will continue along its default path.  
- Pacman can move in four directions; up, left, down, right. The user will specify a direction using the `W`,`A`,`S`,`D` keys respectively. Pacman moves at a constant velocity. The ghosts have a slower velocity than Pacman in their default state and will have a velocity just slightly slower than pacman  when running away.   
- Ghosts will plot a tombstone if pacman catches up to them, this tombstone will become a part of the map.
- The user can press `ENTER` to respawn, this can only be done when pacman is not moving. This was added to avoid softlocking.
- Final score has not been implemented, there is only a win or loose condition.
### Win Condition
![Pacman's Revenge Splash Screen](screenshots/winScreen.png "Win Screen")
- The player wins if they manage to eat all 4 ghosts within the allotted time (99 seconds).

### Lose Condition
![Pacman's Revenge Splash Screen](screenshots/lose_screen.png "Lose Screen")
- If the player cannot eat the ghosts within 99 seconds the player looses.
### Objects
- **Map:** represented as a 2D `Cell` array that represents the map.
    ![Pacman's Revenge Splash Screen](screenshots/cell_map.jpg "Splash Screen")
    - **Path** (light blue) cell for entities to move freely
    - **Wall** (black) Physical barrier no entities can pass through
    - **Invisible Wall** (white) Destination for ghosts when running
    - **Occupied Region** (Red) Represents 4 cells which are currently occupied by an entity.
    - **Hotspot** (Dark blue) As a cell attribute this is represented by `x` and `y`.
- **Tombstone:** Generates when Pacman eats a ghost at that specific location. The tombstone still represents a ghost instance in the `DEAD` state. The tombstone will become a part of the map.
![Tombstone](new_sprites/tombstone.png "Tombstone")

### Structs
- **Entities**: A Structure that encapsulates the model, this includes all entities and the timer.
```
typedef struct {
    Pacman *pacman;
	Ghost *crying_ghost;
	Ghost *awkward_ghost;
	Ghost *moustache_ghost;
	Ghost *cyclops_ghost;

	Timer *timer;
}Entities;
```
- **Pacman**: represents pacman, controlled by the player. Pacman can be in a `DEFAULT` state, or an `EVIL` state.
Pacmans respective sprites has 4 different variations for all 4 directions. 
![1](new_sprites/pac_left_1.png) ![2](new_sprites/pac_left_2.png) ![3](new_sprites/pac_left_3.png) ![4](new_sprites/pac_left_4.png) ![1](new_sprites/evil_pac_left_1.png) ![2](new_sprites/evil_pac_left_2.png) ![3](new_sprites/evil_pac_left_3.png) ![4](new_sprites/evil_pac_left_4.png)
```typedef struct 
typdef struct {
	int current_frame;		        
	UCHAR8 state;					
	ObjectType type;
	Movement* move;
}Pacman; 
```

- **Ghost**: Object representing entities that are running from pacman. There are 4 ghosts, `awkward_ghost`, `moustache_ghost`, `cyclops_ghost`, and `crying_ghost`. The only difference between the ghosts are their sprites and their default paths.
![1](new_sprites/awkward_ghost_down_2.png) ![2](new_sprites/awkward_ghost_left_2.png) ![3](new_sprites/awkward_ghost_right_2.png) ![4](new_sprites/awkward_ghost_up_2.png)
![1](new_sprites/moustache_ghost_down_2.png) ![2](new_sprites/moustache_ghost_left_2.png) ![3](new_sprites/moustache_ghost_right_2.png) ![4](new_sprites/moustache_ghost_up_2.png)
![1](new_sprites/cyclops_ghost_down_2.png) ![2](new_sprites/cyclops_ghost_left_2.png) ![3](new_sprites/cyclops_ghost_right_2.png) ![4](new_sprites/cyclops_ghost_up_2.png)
![1](new_sprites/crying_ghost_down_2.png) ![2](new_sprites/crying_ghost_left_2.png) ![3](new_sprites/crying_ghost_right_2.png) ![4](new_sprites/crying_ghost_up_2.png)

```
typedef struct
{
	int current_frame;
	UCHAR8 state;		
	ObjectType type;
	bool has_collided;
	UCHAR8 path_number;
	Movement* move;
}Ghost;
```
- **Timer**: Used to keep track of the in-game clock, initialized to 99 and counts down to 0.
```
typedef struct {
	UCHAR8 seconds_value;
	UCHAR8 MS_digit_ascii, LS_digit_ascii;
}Timer;
```
- **Cell**: A structure made to represent a single region of the map, cells are relative to every 16 pixels. Cells contain boolean values which act as game specific flags. They also contain information about the ghosts default paths.
```
typedef struct {
	int x_position, y_position;
	bool open_path;
	bool occupied;
	bool has_pellet;

	bool can_go_up;
	bool can_go_down;
	bool can_go_left;
	bool can_go_right;

	UCHAR8 crying_path;
	UCHAR8 cyclops_path;
	UCHAR8 awkward_path;
	UCHAR8 moustache_path;
}Cell;
```
- **Movement**: Used as a generic atribute between `Ghost` and `Pacman` types. Movements consist of anything relating to an objects motion, i.e position, velocity, direction, etc.
```
typedef struct {
    UINT16 x;
    UINT16 y;
    int delta_x;
    int delta_y;
    UCHAR8 direction;
    UCHAR8 y_cell_index;
    UCHAR8 x_cell_index;

	UINT16 last_x;
	UINT16 last_y;

	UINT16 last_last_x;
	UINT16 last_last_y;

	bool changed_direction;
	
}Movement;
```
### Physics

- There is collision detection in this game as there is a maze that Pacman and the ghosts have to follow so there are walls surrounding him. This is to stop the objects from moving through the game environment.
- The velocity for the object is constant (i.e., Pacman always moves at a constant speed). The ghosts can, however, move at a faster speed (when triggered) and it's just the base constant (64 pixels/second + 8 pixels/second) = 72 pixels/second.

### Asynchronous (Input) Events

- **Move down:** `S` key is pressed. Changes Pacman's direction to down.
- **Move up:** `W` key is depressed. Changes Pacman's current direction to ‘up’.
- **Move left:** `A` key is depressed. Changes Pacman's direction to left.
- **Move right:** `D` key is depressed. Changes Pacman's direction to right.
- **Respawn:** `ENTER` key is pressed. Respawns pacman to initial position.

### Synchronous (Timed) Events

- **Pacman moves:** 140 pixels per 70 frames. Pacman moves in the direction specified by the user at the default speed.
- **Ghost moves (default):** 70 pixels per 70 frames. Ghosts have this as their default speed during the whole game.
- **Ghost moves (Running):** 136 pixels per second. When this is triggered, the ghosts will gain speed. 

### Condition-Based (Cascaded) Events

- **Wall collision:** Hitting a wall on the map. 
    - **Pacman**: If Pacman collides with a wall, it will stop (delta y = 0 and delta x = 0).
    - **Ghost**: If Ghost collides with a wall, in it's default state, it will choose the new direction determined by it's path. In it's scared state, it will choose the 'optimal' direction, this is calculated by pacman's relative position to the ghost and the available paths.
- **Proximity Alert:** Pacman gets within a certain proximity of a ghost. A single ghost has entered Pacman's Hitbox. Pacman's sprite and the ghost sprite will change.
- **Timer runs out (Game Over):** Can only occur if the timer reaches 0.
- **All ghosts cleared (Win):** Ghost encounter a corner. Ghost encounters an open location while on its current path. Ghost is killed. Final ghost is eaten. (no ghosts left).

### Hypothetical Gaming Session

In "Pacman's Revenge," the game commences with Pacman positioned at the lower center of the maze with the ghosts originating from the center and moving along their predestined paths. The on-screen timer starts at 99. As Pacman navigates the maze using the `W`, `A`, `S`, or `D` keys for movement, the ghosts maintain their standard speed until Pacman nears one. This proximity triggers the ghost to flee the opposite directions from Pacman or it picks an optimal direction based upon a direction map that is given to them if they encounter a wall. During this phase, the ghost's speed increases slightly, providing a challenge as Pacman tries to intercept it. Upon successfully cornering and consuming a ghost, the ghost will be cleared and a tombstone is placed in that location. The player maneuvers Pacman to avoid walls and tombstones as these become a part of the environment once a ghost is killed there. This means that there is a slight chance that the player can lock themselves inside a location on the map and not be able to win the game, so they must be strategic about this. The session culminates with the capture of the final ghost, triggering the win screen.

## 3. Game Play Details for Core 2-Player Version

A co-op version of the game with the same mechanics. The only difference is there is a second Pacman on the board controlled by another player. The objective stays the same, and this time both players have to kill all of the ghosts. (Note: This has not been implemented in the game's current version.)

## 4. Sound Effects

- **Pacman Travel Sound:** The classic pacman sound that is made as the game runs on. This sound has two variants, one for cells occupied with pellets, and one for cells without pellets.
- **Ghost Eaten Sound:** When Pacman eats a ghost a “power up” type sound will be played. Triggered when Pacman's position matches with a ghost's position.
- **Pacman Intro Sound:** Before the game starts, the classic pacman intro plays with all entities stationary and the game will not start until this intro is finished playing. Triggered when the '1 Player' option is selected and the game begins.

## 5. Pellets 
- The pellets on the map do not offer any functionality aside from changing the current sound being played. They can only be eaten by pacman. 

## 6. Additional Features (Time Permitting)

- Powerup pickups
- Color in the maze and the objects
- Intro animation
- Ghosts death animation
- 2 player mode

## Improvements of stages 1-4

### Stage 1
- Adjusted specs to accurately reflect game

## Stage 2
- Plot screen now plots our splash screen
## Stage 3
- Removed random number generator
- Added movement struct to reduce code duplication.
  This allowed us to remove `Ghost*` or `Pacman*` pointers
  from function deffinitions and replaced them with the more generic `Movement*` pointer type.
### Stage 4
- `render_frame` in renderer now `clears_entities` which appropriately clears all sprites, previously this was not in the renderer.
## Improvements of stages 5-7
### Stage 5
- Added input module, `input.c` and `input.h` which was previously not present. Which contains appropriate input handeling functions. 
### Stage 7
- Removed code duplication by removing the `MusicState` typedef and using `SoundState`for all instances. Replaced similar code with a generic `update_sound()` function.

- Added event triggered sound events, when you eat a ghost a specific sound is played. The sound also changes depending on weather or not the current cell has a pellet