<<<<<<< HEAD
<<<<<<< HEAD
/*
 * file:         ca_object_calculation.c
 * brief:        calculations involved with objects movements detected.
 * author:       Amber
 * date:         2011-04-26
 * version:      0.1
 * history       2011-03-21 create the file
 *
 * detail:       
 */
=======
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b

/*****************************************************************************
 * Product: object_calculations.c
 * Version: 0.1
 * Creators: Amber
 * Created: March 21, 2011
 * History:
 * 
 *
 * Description: calculations involved with objects movements detected.
 * Movement/CA Group
 *****************************************************************************/
<<<<<<< HEAD
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
#include <stdlib.h>
#include <stdio.h>
#include "ca_interface.h"

#define IGNORINGLITTLECHANGE 10



<<<<<<< HEAD
<<<<<<< HEAD
/*
 * Receives array of differences where values are [Value2 - Value1, Value2 - Value1, Value2 - Value1]
 * where value1 is the first measurement and value2 is the second measurement. 
 * 0 is moving closer
 * 1 is moving farther away
 */
unsigned char* moving_closer (int* irDistances)
{
  
	//an array of 4 values 0 or 1, to be returned
	unsigned char *movements = (unsigned char *)calloc(4, sizeof(unsigned char) );

	unsigned char i;
	for(i = 0; i < 4; i++)
		{
			//** The IGNORINGLITTLECHANGE helps ignore sensor variations
			if(*(irDistances + i) + IGNORINGLITTLECHANGE <= 0) 
				*(movements + i)= 1;	
			else
				*(movements + i) = 0;
		}

	return movements;
=======
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
//******************************************************************
// Receives array of differences where values are [Value2 - Value1, Value2 - Value1, Value2 - Value1]
// where value1 is the first measurement and value2 is the second measurement. 
//0 is moving closer
//1 is moving farther away
//******************************************************************
unsigned char* moving_closer (int* irDistances)
{
  
  //an array of 4 values 0 or 1, to be returned
  unsigned char *movements = ( unsigned char *)calloc(4, sizeof(unsigned char) );

 unsigned char i;
  for(i = 0; i < 4; i++)
    {
      //** The IGNORINGLITTLECHANGE helps ignore sensor variations
      if(*(irDistances + i) + IGNORINGLITTLECHANGE <= 0) 
	*(movements + i)= 1;	
      else
	*(movements + i) = 0;
    }

  return movements;
<<<<<<< HEAD
>>>>>>> 040f404a80bdac3a1098d380a4f35b169d4e8e16
=======
>>>>>>> 63448f47519691d1491cc311c9f5cb7b4f57917b
}
