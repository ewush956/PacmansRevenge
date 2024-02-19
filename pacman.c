#include "pacman.h"
#include "model.h"
#include "raster.h"
#include "TYPES.H"

/*probably can remove after adjusting init_map_cells*/
#include "bitmaps.h"

Entities entities = {
    &pacman,
    &moustache_ghost,
    &crying_ghost,
    &cyclops_ghost,
    &awkward_ghost
};

GAME_STATE state = PLAY;
init_map_cells(cell_map, tile_map);
render_map(cell_map, tile_map);

int main()
{
    while (state != QUIT) {
    
        /* from stage 5 document: 

            if input is pending
                process async event      <-- update model
            if clock has ticked
                process sync events      <-- update model
                render model (next frame)
        */
        state = update_game_state(state);
    }
    return 0;
}

GAME_STATE update_game_state(GAME_STATE new_state) {
    /*Do something that updates the gamestate*/
    state = new_state;
}


/*TODO:
1) Initialize cell map
NOTES: init_map_cells could do without tile_map since it's included in bitmaps.h (globally accessable in renderer)

2) initialize first frame (render map)
3) make main game loop
NOTES: need a QUIT sentenel, i'm thinking we make it -1 or something that isn't easily mixed up with our other typedefs.
        while (state != QUIT) ...
*/

