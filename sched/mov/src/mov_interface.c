/*****************************************************************************
  * Product: movementInterface.c
  * Version: 0.1
  * Created: April 7, 2011
  * History:
  *          
  *
  *
  * Movement/CA Group
  *****************************************************************************/


#include "mov_header.h"

#include <stdlib.h>
#include <stdio.h>

#ifdef ARDUINO
//************************************************************
// ARDUINO
// All movement preperation goes here.
//************************************************************
int movement_init()
{
  //start magnetometer

  return 1;
}


//************************************************************
// ARDUINO
// Movement is started here
//************************************************************
int movement_run()
{
  

  return 1;

}
#endif



#ifdef PC
//************************************************************
// PC
//  All movement preperation goes here.
//************************************************************
int movement_init()
{
  

  return 1;

}

//************************************************************
// PC
// Movement is started here
//************************************************************
int movement_run()
{


  return 1;
}
#endif
