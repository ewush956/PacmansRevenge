#ifndef ISR_H
#define ISR_H


#include "TYPES.H"

#define START_DELAY 7
#define TRAP_28 28
#define TRAP_70 70
#define DISABLE 0xBF            
#define ENABLE 0x40             
#define CLEAR_BIT_6 0xBF
#define BUFFER_SIZE_255_HEX 0xFF /* 255?*/



typedef void (*Vector)();
Vector install_vector(int num, Vector vector);
void do_vbl();        
void do_IKBD_isr(); 

/*** asm routines ***/
void trap28_isr();      
void trap70_isr();
int set_ipl(int mask);
/********************/
void install_custom_vectors();
void remove_custom_vectors();

void disable_MIDI_interrupts();
void enable_MIDI_interrupts();

void enqueue(SCANCODE code);
UCHAR8 dequeue();

void update_mouse();
void initialize_mouse();
bool is_mouse_in_bounds();

extern int seconds;

#endif