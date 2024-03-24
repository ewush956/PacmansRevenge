#ifndef ISR_H
#define ISR_H


#include "TYPES.H"


#define TRAP_28 28

typedef void (*Vector)();
Vector install_vector(int num, Vector vector);

void do_vbl();        
void trap28_isr();      /* in isr_asm file*/



#endif