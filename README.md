# PacmansRevenge
Arcade style variant of the arcade game "Pacman" created for Computing Machinery II at Mount Royal University. See `specs.md` for details.

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

## Known Bugs
1. Occasionally ghost movement causes half of a pellet sprite to render on either the back or the front buffer causing flickering.
This has been PARTIALLY fixed, the fix we came up with at re renders the pellet  but you can still see some flickering behind the ghost. 

2. Ghosts frames are not being updated properly, like an issue with ticks or seconds in ISR.C

3. The cyclops ghost's eye is not properly centered in some of it's alternate frames
causing the movement to look jittery. This is an issue with it's bitmap.

5. Ghosts don't clear properly when being eaten, and occasionally "jump" leaving a flickering, trail, this issue has been mostly resolved, but still occisionally leaves small pixels behind.

## Running the program

To run the program, simply type `compile.g` in the terminal.
This will execute a script that removes any object files and then runs the command `make all`.
This will create the following executables:
- `pacman`: Main game
- `tst_snd`: Music, effects, and PSG test driver
- `tst_rast`: Raster test driver
- `tst_rend`: Renderer test driver
- `tst_stru`: Model test driver