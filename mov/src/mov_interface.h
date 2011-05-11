/*
 * file:         mov_interface.h
 * brief:
 * author:       Yanling Jin, Amber Olsson
 * date:         2011-05-10
 * version:      0.1
 * history      
 *
 * detail:
 */


#include <stdio.h>
#include <stdint.h>

struct nav
{
	char type;
	char order; 
	int height;
	int distance;
	int yaw;
};

struct sensor
{
	int pitch;
	int roll;
	int yaw;
	int height;
};

struct messages
{
    uint8_t msg1;
    uint8_t msg2;
    uint8_t msg3;
    uint8_t msg4;
    uint8_t msg5;
    uint8_t msg6;
    uint8_t msg7;
    uint8_t msg8;
};



/*mov_logic.c*/
void command_logic(void);
void hoverCommand(void);
void moveCommand (void);
void landCommand(void);
void check_height(void);
void check_heading(void);
void check_pitch_roll(int isHovering);
void updateDistanceToTravel(void);
void check_changingAltitude(void);
void doCa(void);
#ifdef DEBUG
void printOrientation(void);
#endif

/*mov_motor.c*/
void start_motors(void);
void stop_motors(void);
void increase_rear_motor(void);
void decrease_rear_motor(void);
void increase_front_motor(void);
void decrease_front_motor(void);
void increase_left_motor(void);
void decrease_left_motor(void);
void increase_right_motor(void);
void decrease_right_motor(void);
void increase_rear_decrease_front(void);
void increase_front_decrease_rear(void);
void increase_left_decrease_right(void);
void increase_right_decrease_left(void);
void increase_all(void);
void decrease_all(void);
void hover(void);
void go_forwards(void);
void go_backwards(void);
void strafe_left(void);
void strafe_right(void);
void turn_left(void);
void turn_right(void);
void land(void);

char to_MotorMessage(char ID0, char ID1, char increasing, char panicMode, 
					 char motor1,char motor2, char motor3, char motor4);
void pWrite(char msg);
void print_char_to_Binary(char bin);



/*mov_simulator.c*/
int read_command(void);
int get_loc(char line[],char c,int indexOfColumn);
void assignValue(int index,char *temp);
int do_sensor_simulation(int currentSensorValue, int command);


/*interface*/
int mov_init(void);
int mov_run(void);
void read_navCommand(void);
void read_caCommand(void);
void write_to_motor(unsigned char msg);
void send_dir_to_ca(int i);
void read_sensorCommand(void);
void clear_message_array();
void write_array();

/*mov_sensor.c*/
#ifdef ARDUINO
float sonar_distance(int sonarPin);
#elif defined PC
float sonar_distance(int sonarPin);
#endif
