#ifndef MODEL_H
#define MODEL_H

#include "types.h"

 /* move_ghost(int x, int y, Object *ref_to_object) */
 
 
typedef struct 
{
	UINT16 x,y;					/*positon */
	int delta_x,delta_y; 		/* displacement (horzontal or vertical) */
	

}Pacman;


typedef struct 
{
	UINT16 x,y;			
	int delta_x,delta_y; 		

}Ghost;



/*  (leave them for now prob wont need) 
typedef struct 
{
	unsigned int x,y;			
	int delta_x,delta_y; 		

}CryingGhost;

typedef struct 
{
	unsigned int x,y;			
	int delta_x,delta_y; 		
	

}MoustacheGhost;;

typedef struct 
{
	unsigned int x,y;			
	int delta_x,delta_y; 		
	

}SmilingGhost;

typedef struct 
{
	unsigned int x,y;		
	int delta_x,delta_y; 		
	
}NeutralGhost;
*/

#endif