/* Module: msg_parsing.c
*  Author:  Rahwa Bahta, Reza moussavi
*  
*/

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
#include <stdint.h>

=======
>>>>>>> f92a19bd9dffcb6a29ee665ad279d19a9402e881
=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
//Dont put any lines of code before this line
#ifndef _STATE_DEFINITIONS_H_
#define _STATE_DEFINITIONS_H_

//MASKS
#define MSG_ID_MASK		0xC0
#define MSG_CONTROL_MASK	0x80
#define MSG_SPECIAL_MASK	0xC0

#define MSG_REAR_MOTOR_MASK	0x01
#define MSG_FRONT_MOTOR_MASK	0x02
#define MSG_LEFT_MOTOR_MASK	0x04
#define MSG_RIGHT_MOTOR_MASK	0x08

#define MSG_PANIC_MASK	0x10
#define MSG_INCREASE_MASK	0x20

//MESSAGE STATES
# define START_MOTOR 0x40
# define START_ID 0x01 //this was added
# define STOP_MOTOR 0x0
# define STOP_ID 0x00 //this was added
# define CONTROL_ID 0x02 //this was added
# define SPECIAL_COMMAND_ID 0x03 //this was added
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
# define HOVER 0xFF
# define BAD_MESSAGE 0xf //this was added, when bits are not within the 0-255 range
# define NOTHING 0xB

# define INCREASE_ALL_NORMAL 0xEF
# define DECREASE_ALL_NORMAL 0xCF
# define INCREASE_ALL_PANIC 0xF0
# define DECREASE_ALL_PANIC 0xD0
=======

# define BAD_MESSAGE 0xf //this was added, when bits are not within the 0-255 range

>>>>>>> f92a19bd9dffcb6a29ee665ad279d19a9402e881
=======

# define BAD_MESSAGE 0xf //this was added, when bits are not within the 0-255 range

>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======

# define BAD_MESSAGE 0xf //this was added, when bits are not within the 0-255 range

>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b

# define  INCREASE_REAR_MOTOR 0xA1
# define  DECREASE_REAR_MOTOR 0x81
# define  INCREASE_FRONT_MOTOR 0xA2
# define  DECREASE_FRONT_MOTOR 0x82
# define  INCREASE_LEFT_MOTOR 0xA4
# define  DECREASE_LEFT_MOTOR 0x84
# define  INCREASE_RIGHT_MOTOR 0xA8
# define  DECREASE_RIGHT_MOTOR 0x88 
# define  DECREASE_FRONT_INCREASE_REAR 0xE3
# define  DECREASE_REAR_INCREASE_FRONT 0xC3
# define  DECREASE_RIGHT_INCREASE_LEFT 0xEC
# define  DECREASE_LEFT_INCREASE_RIGHT 0xCC

# define  FORWARD  0xE3
# define  BACKWARD 0xC3
# define  STRAFE_RIGHT 0xEC
# define  STRAFE_LEFT 0xCC //this was corrected
# define  TURN_RIGHT 0xFC //this was added
# define  TURN_LEFT 0xDC //this was added
 
# define  PANIC_INCREASE_REAR_MOTOR 0xB1
# define  PANIC_DECREASE_REAR_MOTOR 0x91
# define  PANIC_INCREASE_FRONT_MOTOR 0xB2
# define  PANIC_DECREASE_FRONT_MOTOR 0x92
# define  PANIC_INCREASE_LEFT_MOTOR 0xB4
# define  PANIC_DECREASE_LEFT_MOTOR 0x94
# define  PANIC_INCREASE_RIGHT_MOTOR 0xB8
# define  PANIC_DECREASE_RIGHT_MOTOR  0x98

# define  PANIC_FORWARD 0xF3
# define  PANIC_BACKWARD 0xD3
# define  PANIC_TURN_RIGHT 0xFC
# define  PANIC_TURN_LEFT 0xDC


struct bits_type
{
<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
	uint8_t ID :2;
	uint8_t INCREASE :1;
	uint8_t PANIC :1;
	uint8_t RIGHT :1;
	uint8_t LEFT :1;
	uint8_t FRONT :1;
	uint8_t REAR :1;
=======
=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
	unsigned char ID :2;
	unsigned char INCREASE :1;
	unsigned char PANIC :1;
	unsigned char RIGHT :1;
	unsigned char LEFT :1;
	unsigned char FRONT :1;
	unsigned char REAR :1;
<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> f92a19bd9dffcb6a29ee665ad279d19a9402e881
=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
};

// Dont put any code after this line
#endif
