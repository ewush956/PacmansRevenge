# PacmansRevenge
Arcade style variant of the arcade game "Pacman" created for Computing Machinery II at Mount Royal University.

# Improvements of stages 1-4

## Stage 1
- Adjusted specs to accurately reflect game

## Stage 2
- Plot screen now plots our splash screen
## Stage 3
- Removed random number generator
- Added movement struct to reduce code duplication.
  This allowed us to remove `Ghost*` or `Pacman*` pointers
  from function deffinitions and replaced them with the more generic `Movement*` pointer type.
## Stage 4
- `render_frame` in renderer now `clears_entities` which appropriately clears all sprites, previously this was not in the renderer.
# Improvements of stages 5-7
## Stage 5
- Added input module, `input.c` and `input.h` which was previously not present. Which contains appropriate input handeling functions. 
## Stage 7
- Removed code duplication by removing the `MusicState` typedef and using `SoundState`for all instances. Replaced similar code with a generic `update_sound()` function.

- Added event triggered sound events, when you eat a ghost a specific sound is played. The sound also changes depending on weather or not the current cell has a pellet

