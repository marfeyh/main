/*!
* @file proto_ca.c
* @brief Collision avoidance messages
* @author Elnaz Shahmehr
* @history 
* 			- 2011-04-11 first release
*			- 2011-05-10 updated by Elnaz
* 			- 2011-05-12 updated by Mihail
*			- 2011-05-12 updated by Elnaz
*/

#ifdef PC
   #include <stdio.h> 
#endif

#include <stdlib.h>
#include "proto_lib.h"
   
/*************************************************************************** 
    Implementations 
****************************************************************************/
int16_t yaw = -1;//int16_t yaw = -1; Default Value for direction 

void proto_write_yaw(int16_t value){ 
    yaw = value;
#ifdef PC
	storeForTint(PROTO_WRITE, PROTO_COLLISION, PROTO_UNKNOWN, value);
	#ifdef DEBUG
		printf("collision avodance value set to: %c\n", value);
	#endif
#endif
} 
 
int16_t proto_read_yaw(void){ 
#ifdef PC
	storeForTint(PROTO_READ, PROTO_MOVEMENT, PROTO_UNKNOWN, yaw);
	#ifdef DEBUG
		printf("collision avodance value is: %c\n", yaw);
	#endif
#endif
    return yaw; 
}


