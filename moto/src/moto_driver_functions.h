/**
 * Module:       motor_control.h
 * Author(s):    Kristofer Hansson Aspman
<<<<<<< HEAD
 *               Magnus Bergqvist
=======
>>>>>>> f92a19bd9dffcb6a29ee665ad279d19a9402e881
 *
 * Description:  The typedef of the bitfield struct and
 *               all the prototypes for the functions used
 *               by tools.c, motor_control.c and parser.c.
 *
 */

<<<<<<< HEAD
#ifdef ARDUINO_DBG
    #define ARDUINO
#endif
=======
>>>>>>> f92a19bd9dffcb6a29ee665ad279d19a9402e881
#ifdef ARDUINO
   #include "WProgram.h"
#elif defined PC
   #include <stdio.h>
#endif
<<<<<<< HEAD
#include <stdint.h>

#define NORMAL_STEP 5
#define PANIC_STEP 50

/* defines which "pin" in the arduino, to be changed further on */
#define RIGHT_MOTOR 2
#define LEFT_MOTOR 3
#define FRONT_MOTOR 5
#define REAR_MOTOR 6


/* defines maximum and minimum pulse width in µs for every motor 
   i.e. at which pulse the motor starts turning and at which pulse it
   reaches its max speed */
#define MIN_PULSE_FRONT 1000
#define MAX_PULSE_FRONT 2000
#define MIN_PULSE_REAR 1000
#define MAX_PULSE_REAR 2000
#define MIN_PULSE_LEFT 1000
#define MAX_PULSE_LEFT 2000
#define MIN_PULSE_RIGHT 1000
#define MAX_PULSE_RIGHT 2000

/* defines the min and max values (pulse width in µs that are allowed) */
#define MIN_ESC_PULSE 1000
#define MAX_ESC_PULSE 2000

#define IDLE_SPEED 1100
#define STOP_PULSE 1000

/* defines hover speed pulse width in µs for every motor */
#define HOVER_PULSE_RIGHT 1400
#define HOVER_PULSE_LEFT 1400
#define HOVER_PULSE_FRONT 1400
#define HOVER_PULSE_REAR 1400

extern uint16_t rightPulse;
extern uint16_t leftPulse;
extern uint16_t frontPulse;
extern uint16_t rearPulse;


/*Motor pulse modification*/
void moto_startMotors(void);
void moto_stopMotors(void);
void moto_hover(void);
void moto_goForward(void);
void moto_goBackward(void);
void moto_strafeRight(void);
void moto_strafeLeft(void);
void moto_rotateLeft(void);
void moto_rotateRight(void);

void moto_increaseAllNormal(void);
void moto_increaseAllPanic(void);

void moto_decreaseAllNormal(void);
void moto_decreaseAllPanic(void);

void moto_increaseLeftNormal(void);
void moto_increaseRightNormal(void);
void moto_increaseFrontNormal(void);
void moto_increaseRearNormal(void);
void moto_increaseLeftPanic(void);
void moto_increaseRightPanic(void);
void moto_increaseFrontPanic(void);
void moto_increaseRearPanic(void);

void moto_decreaseLeftNormal(void);
void moto_decreaseRightNormal(void);
void moto_decreaseFrontNormal(void);
void moto_decreaseRearNormal(void);
void moto_decreaseLeftPanic(void);
void moto_decreaseRightPanic(void);
void moto_decreaseFrontPanic(void);
void moto_decreaseRearPanic(void);

void printMotorStatus(void);

void moto_left_motor(unsigned char,unsigned char);
void moto_right_motor(unsigned char,unsigned char);
void moto_front_motor(unsigned char,unsigned char);
void moto_rear_motor(unsigned char,unsigned char);

uint16_t rightMotorLimitIncrease(uint16_t currentPulse, uint16_t increment);
uint16_t rightMotorLimitDecrease(uint16_t currentPulse, uint16_t decrement);
uint16_t leftMotorLimitIncrease(uint16_t currentPulse, uint16_t increment);
uint16_t leftMotorLimitDecrease(uint16_t currentPulse, uint16_t decrement);
uint16_t frontMotorLimitIncrease(uint16_t currentPulse, uint16_t increment);
uint16_t frontMotorLimitDecrease(uint16_t currentPulse, uint16_t decrement);
uint16_t rearMotorLimitIncrease(uint16_t currentPulse, uint16_t increment);
uint16_t rearMotorLimitDecrease(uint16_t currentPulse, uint16_t decrement);

struct pulses{
    uint16_t right;
    uint16_t left;
    uint16_t front;
    uint16_t rear;
};
=======

#define NORMAL_INCREMENT 2
#define PANIC_INCREMENT 4
#define NORMAL_DECREMENT -2
#define PANIC_DECREMENT -4


extern unsigned char rightMotor;
extern unsigned char leftMotor;
extern unsigned char frontMotor;
extern unsigned char rearMotor;

/*Motor pulse modification*/
void _moto_startMotors(void);
void _moto_stopMotors(void);
void _moto_goForward(void);
void _moto_goBackward(void);
void _moto_strafeRight(void);
void _moto_strafeLeft(void);

void _moto_increaseLeftNormal(void);
void _moto_increaseRightNormal(void);
void _moto_increaseFrontNormal(void);
void _moto_increaseRearNormal(void);
void _moto_increaseLeftPanic(void);
void _moto_increaseRightPanic(void);
void _moto_increaseFrontPanic(void);
void _moto_increaseRearPanic(void);

void _moto_decreaseLeftNormal(void);
void _moto_decreaseRightNormal(void);
void _moto_decreaseFrontNormal(void);
void _moto_decreaseRearNormal(void);
void _moto_decreaseLeftPanic(void);
void _moto_decreaseRightPanic(void);
void _moto_decreaseFrontPanic(void);
void _moto_decreaseRearPanic(void);

void printMotorStatus(void);
>>>>>>> f92a19bd9dffcb6a29ee665ad279d19a9402e881
