#ifndef ISR_H
#define ISR_H


#include "TYPES.H"



#define TRAP_28 28
#define TRAP_70 70
#define DISABLE 0xBF            /* we want to AND this to diable interrupts*/
#define ENABLE 0x40             /* we want to OR this in*/
#define INTERRUPT_REQUEST 0x80 /* not usign atm */

#define CLEAR_BIT_6 0xBF



typedef void (*Vector)();
Vector install_vector(int num, Vector vector);

void do_vbl();        
void do_IKBD_isr(); 

/*inside isr_asm.s*/
void trap28_isr();     
void trap70_isr();
/*---------------*/

void disable_MIDI_interrupts();
void enable_MIDI_interrupts();
extern int seconds;



#endif