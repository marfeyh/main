#include <stdio.h>
/*
stab_pitch() -> adjust motor 2 and 4
stab_roll() -> adjust motor 1 and 3
stab_qc() -> adjust all motors
*/

// desired data
float d_pitch;
float d_roll;
float d_yaw;
// data from the sensors
float s_pitch;
float s_roll;
float s_yaw;
// dif. data
float  dif_pitch;
float  dif_roll;
float  dif_yaw;

int flag = 0;

void forward()
{
  stab_pitch();// stabilization for the pitch angle - motor 2 and 4 
  desired_roll(dif_roll);
}//end of forward


// aranging the roll angle for move forward - motor 1 and 3
void desired_roll(float dif_roll)
{
  if(dif_roll > 0 && flag = 0)
  {
    motor(0,0,1,0);
    flag++;
  }
  if else(dif_roll > 0 && flag = 1)
  {
    motor(-1,0,0,0);
    flag--;
  }
  if else(dif_roll < 0 && flag = 0)
  {
    motor(0,0,-1,0);
    flag++;
  }
  if else(dif_roll < 0 && flag = 1)
  {
    motor(1,0,0,0);
    flag--;
  }  
}//end of desired_roll


// change the yaw to the wanted data

void change_yaw(float yaw)
{
  stab_pitch();
  stab_roll();

  if(yaw > 180)
  {
    motor(0,1,0,1);
  }
else
  {
    motor(1,0,1,0);
  }
}


void attitude()
{

  //stab_pitch();
  //stab_roll();
  change_yaw(dif_yaw);

  if(dif_yaw = 0)
  {
    forward();
  }
}
/*
right()
{

desired_yaw();
desired_roll();

}

left()
{

derired_yaw();
desired_roll();

}*/

ascend()
{

stab_qc();


}

descend()
{

stab_qc();


}
