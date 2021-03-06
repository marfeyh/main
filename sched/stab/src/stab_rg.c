/***************************************************************************
 * @file read_rg.c
 * @brief Takes care of the communication with the gyroscope
 * @author Adam Debbiche & Yuwen He  	       
 * @date 05/04/2011
 * @history
 *    11/04/2011: Initial version // Adam
 *    14/04/2011: Added comments //Adam
 *    18/04/2011: Code now reflects coding standards
 ****************************************************************************/
#ifdef ARDUINO
#include <Wire.h>
#include "WProgram.h"
#include "stab.h"
/*
 * Macros that define the address registers of the 
 * gyroscope used (full list in the spec)
 */
#define	SMPL	0x15
#define DLPF	0x16
#define INT_C	0x17
#define PWR_M	0x3E
#define GYRO_ADDRESS 0x69
#define SSF 14.375 // Gyro's Sensitivity Scale Factor

struct vector
{
  float x;
  float y;
  float z;
};

/*
 *Function prototypes
 */
void write_data(byte addr, byte value);
void init_gyro_hardware();
struct vector read_gyro_data();
float convert_gyro_raw_to_deg_s(float a);


/*
 * Abstcract function that writes the value to the address given
 */
void write_data(byte addr, byte value)
{
  Wire.beginTransmission(GYRO_ADDRESS);
  Wire.send(addr);
  Wire.send(value);
  Wire.endTransmission();
  
}

/*
 * Initializeses the gyroscope hardware and sets options 
 * for the power management...
 */
void init_gyro_hardware()
{
  write_data(PWR_M, 0x00);
  write_data(SMPL, 0x07);
  write_data(DLPF, 0x1E);
  write_data(INT_C, 0x00);  
}

/*
 * Reads the raw data from the gyroscope:
 * Each axis's data is stored in 2 bytes so
 * 6 bytes are read at one then each pair 
 * is merged together using the bitwise 
 * operation shift(<<) and or (|)
 */
struct vector read_gyro_data()
{
  struct vector vect;
  byte buffer[6];
  int addr = 0x1D;
  read_stream(addr, 6, buffer);
  
  int x, y, z;
  
  x = ((buffer[0] << 8) | buffer[1]) + 120;
  y = ((buffer[2] << 8) | buffer[3]) + 20;
  z = ((buffer[4] << 8) | buffer[5]) + 93; 
 
  vect.x = convert_gyro_raw_to_deg_s(x);
  vect.y = convert_gyro_raw_to_deg_s(y);
  vect.z = convert_gyro_raw_to_deg_s(z);

  //Serial.println(x);
  //Serial.println(y);
  //Serial.println(z);

  return vect;
}

/*
 * Reads the bytes from the I2C bus and saves it to 
 * the buffer
 */
void read_stream(byte addr, int bytes_to_read, byte buffer[])
{
  Wire.beginTransmission(GYRO_ADDRESS);
  Wire.send(addr);
  Wire.endTransmission();
    
  Wire.beginTransmission(GYRO_ADDRESS);  
  Wire.requestFrom(GYRO_ADDRESS, bytes_to_read); 
  
  int i;
  while(Wire.available())
  {
    buffer[i] = Wire.receive();
    i++;    
  }
  Wire.endTransmission();
   
}

/*
 * Converts the raw data from the gyroscope to the scaled value
 * in degrees/s
 */
float convert_gyro_raw_to_deg_s(float a)
{
  return a / SSF;
}
#endif 
