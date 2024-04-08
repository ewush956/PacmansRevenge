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
# Improvements of stages 5-7
- Added input module