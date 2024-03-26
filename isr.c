
#include <osbind.h>

#include "isr.h"    
#include "TYPES.H"
#include "globals.h"

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
    ticks++;
    request_to_render = TRUE; /**/


}