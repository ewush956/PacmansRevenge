
#include "isr.h"    
#include "TYPES.H"
#include <osbind.h>
/*#include "pacman.h"     /*for rextern render requst*/

/*********************
*
*
*
*******************/
Vector install_vector(int num, Vector vector)
{
    Vector orig;
    Vector *vectp = (Vector *)((long)num << 2);
    long old_ssp = Super(0);
    orig = *vectp;
    *vectp = vector;
    Super(old_ssp);

    
    return orig;
}


void do_vbl()
{

    if (clock_ticks == 70)
    {
        request_to_render = TRUE;
        clock_ticks = 0;
    }

    clock_ticks++;

}