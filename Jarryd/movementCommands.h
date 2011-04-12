/*
* Author: Jarryd Hall
* Purpose: Drone Movement Commands
*
*/

#ifndef MOVEMENTCOMMANDS_H
#define MOVEMENTCOMMANDS_H

// MovementCommand struct 
struct typedef
 {
	char type;  // (manual/auto)
	char order; //(lift off/ hovering/ moving/ land)
	int height;
	int distance;
	int yaw; // vertical
	int pitch; // lateral
	int roll; // longitudinal 
	int speed; 
}
movementCommand;

// Create a movement command 
void sendMovementCommand
(char type, char order , int height, int distance, int yaw, int pitch , int roll, int speed);

#endif /* MOVEMENTCOMMANDS_H */