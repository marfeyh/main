<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
/*!@author Kristofer Hansson Aspman
 * @file moto_msg_manipulation.h
 * @version v0.02
 * @date 2011-05-08
 *
 * @brief Intended to include the necessary tools to handle\n
 * the binary motor control msg.\n
 * Defines the types msg and msg_pointer, frequently used\n
 * within the code of the motor control component.\n
 * Various tools such as macros for casting and function\n
 * for printing are found here.
 *
 * @history 2011-04-03: First version.
 *          2011-04-07: Implemented ifdefs.
 *          2011-05-08: Cleaned up a bit and added some comments.
 */

#include <stdint.h>

#ifdef ARDUINO_DBG
    #define ARDUINO
#endif
=======
>>>>>>> f92a19bd9dffcb6a29ee665ad279d19a9402e881
=======
#ifdef ARDUINO_DBG
    #define ARDUINO
#endif
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
#ifdef ARDUINO_DBG
    #define ARDUINO
#endif
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
#ifdef ARDUINO
   #include "WProgram.h"
#elif defined PC
   #include <stdio.h>
#endif

<<<<<<< HEAD
<<<<<<< HEAD
<<<<<<< HEAD
/* Casts a uint8_t into a pointer of type msg_pointer */
#define INT_TO_BITFIELD(a) *(msg_pointer)a

/* Casts a msg_pointer into a uint8_t */
#define BITFIELD_TO_CHAR(a) *(uint8_t*)a

/* Big endian control message
 * This is the actual bitfield used throughout
 * the motor control component.
 */
typedef struct control_message{
  uint8_t rear :1;
  uint8_t front :1;
  uint8_t left :1;
  uint8_t right :1;
  uint8_t panic :1;
  uint8_t increase :1;
  uint8_t ID :2;
} msg, *msg_pointer;

/*Little endian control message*/
/* struct control_message{ */
/*   uint8_t ID :2; */
/*   uint8_t increase :1; */
/*   uint8_t panic :1; */
/*   uint8_t right :1; */
/*   uint8_t left :1; */
/*   uint8_t front :1; */
/*   uint8_t rear :1; */

/* } msg, *msg_pointer; */

/*!@author Kristofer Hansson Aspman
 * @function printMsg
 * @param msg_pointer
 * @return void
 * @brief Simply prints out necessary debug information\n
 * such as the status of the motors and the bits of the message\n
 * sent in as a parameter to the functions.\n
 * Uses Serial.print or printf depending on what flag has been set\n
 * for the compilation (ARDUINO_DBG or PC respectively).
 */
=======
=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
#define INT_TO_BITFIELD(a) *(msg_pointer)a
#define BITFIELD_TO_CHAR(a) *(unsigned char*)a

//Big endian control message
typedef struct control_message{
  //unsigned char may not be portable
  //if that is the case, try just unsigned
  //also, endianess may be different on arduino
  unsigned char rear :1;
  unsigned char front :1;
  unsigned char left :1;
  unsigned char right :1;
  unsigned char panic :1;
  unsigned char increase :1;
  unsigned char ID :2;
} msg, *msg_pointer;

//Little endian control message
/* struct control_message{ */
/*   unsigned char ID :2; */
/*   unsigned char increase :1; */
/*   unsigned char panic :1; */
/*   unsigned char right :1; */
/*   unsigned char left :1; */
/*   unsigned char front :1; */
/*   unsigned char rear :1; */

/* } msg; */

<<<<<<< HEAD
<<<<<<< HEAD
>>>>>>> f92a19bd9dffcb6a29ee665ad279d19a9402e881
=======
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
void printMsg(msg_pointer mp);
