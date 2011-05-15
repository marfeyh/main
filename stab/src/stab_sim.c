/*************************************************************************
 * @file stab_sim.c
 * @brief This is a small simulator that creates random value as 
 *               output the gyroscope and acceleometer. The simulator 
 *               returns a vector with x, y and z values randomly 
 *               generated.
 * @author Adam Debbiche 	       
 * @date 05/04/2011
 * @history 
 *    04/04/2011: Initial version // Adam
 *    08/04/2011: Removed the pipe version, the sim now works when it is
 *                invoked. Added comments to each function.
 *                Added time as seed so values are always random.This was 
 *                a bug before. //Adam
 *    11/04/2011: Renamed file to stab_sim (was stab_gyro_sim) // Adam
 *    18/04/2011: Updated code to reflect coding standards
 *    11/05/2011: //My
 *    15/05/2011: Fixed a small integer overflow error //Adam
 *************************************************************************/
#ifdef PC
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "stab.h"

/* 
 * Function prototype
 */
float gen_float(float a, float b);
long gen_long(long a, long b);
int gen_int(int a, int b);

/*
 * A struct that is returned by the simulator when simulated
 * attitude data is requested.
 */
struct attitude {
  float pitch;
  float roll;
  int heading;
};

struct vector {
    float x;
    float y;
    float z;
};

struct baro_data {
    int temp;
    long pressure;
    float height;
};

//=========================================================
/*
 * Generates random attitude data. 
 * For testing purposes only.
 * New version of messages. 
 */
struct attitude sim_attitude(void) {
    struct attitude att;
    srand(time(NULL));
    att.pitch = gen_float(-180.0, 90.0);
    att.roll = gen_float(-180.0, 90.0);
    att.heading = gen_int(0, 360);

    return att;
}

/*
 * Generates random vector with degrees. 
 * For testing purposes only.
 */
struct vector sim_vector(void) {
    struct vector vect;
    srand(time(NULL));
    vect.x = gen_float(-180.0, 90.0);
    vect.y = gen_float(-180.0, 90.0);
    vect.z = gen_float(-180.0, 90.0);

    return vect;
}

/*
 * Generates random heading (angle, type:int). 
 * For testing purposes only.
 */
int sim_heading() {
    //generate a heading between 0 and 360 degrees
        //0/360 = North
        //90 =    East
        //180 =   South
        //270 =   West
    return gen_int(0, 360);
}

/*
 * Generates random barometer data. 
 * For testing purposes only.
 */
struct baro_data sim_baro() {
    //generate a height above sea level between 0 and 100 meters
    struct baro_data baro;
    srand(time(NULL));
    baro.temp = gen_int(-20,100);
    baro.pressure = gen_long(100000.0,101000.0);
    baro.height = gen_float(1.0,100.0);

    return baro;
}

//===HELPER=FUNCTIONS=======================================
/*
 * Function that generates random float
 */
float gen_float(float start, float end) { 
    return start + (int)(end * rand() / (RAND_MAX + 1.0));
}

/*
 * Function that generates random int
 */
int gen_int(int start, int end) { 
    return start + (int)(end * rand() / (RAND_MAX + 1.0));
}

/*
 * Function that generates random long
 */
long gen_long(long start, long end) { 
    return start + (int)(end * rand() / (RAND_MAX + 1.0));
}

#endif
