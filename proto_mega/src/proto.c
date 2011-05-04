/*****************************************************************************
* Product: 
* Version: 
* Released: April 7 2011
* Updated: April 28 2011
*
* Copyright (C) 2011 Elnaz Shahmehr
*
* Updated by Elnaz Shahmehr 
*
* <IT University of Goteborg>
*****************************************************************************/


#ifdef PC
	#include <stdio.h>
	#include "proto_lib.h"
#endif

unsigned char filter_message;
unsigned char motor_message;

void proto_write_filter(unsigned char message){
	filter_message=message;
#ifdef pc
                storeForTint(WRITE, FILTER, UNKNOWN, filter_message);
      #ifdef DEBUG
		printf("filter value set to: %c\n", filter_message);
      #endif

#endif	
}

unsigned char proto_read_filter(void){
	unsigned char temp=filter_message;
	filter_message=0;
#ifdef PC
 storeForTint(READ, MOTOR, UNKNOWN, temp);
      #ifdef DEBUG
	printf("filter value set to: %c\n", temp);
       #endif
#endif
	return temp;
}

void proto_write_motor(unsigned char message){
	motor_message=message;
#ifdef PC
      storeForTint(WRITE, MOTOR, UNKNOWN, motor_message);
      #ifdef DEBUG
	printf("motor value set to: %c\n", motor_message);
   #endif
#endif
} 
   
unsigned char proto_read_motor(void){
	unsigned char temp=motor_message;
	motor_message=0;
#ifdef PC
    storeForTint(READ, FILTER, UNKNOWN, temp);
      #ifdef DEBUG
	printf("motor value set to: %c\n", temp);
    #endif
#endif
	return temp;
}


void test_send_to_filter(unsigned char);
void test_receive_filter();
void test_send_to_motor(unsigned char);
void test_receive_motor();

int main(){
	test_send_to_filter(127);
	test_receive_filter();
	test_send_to_motor(231);
	test_receive_motor();
	return 1;
}

void test_send_to_filter(unsigned char message){
	write_filter(message);
	printf("Sent to FILTER:%d\n",(int)message);
}

void test_receive_filter(){
	printf("FILTER received:%d\n",(int)read_filter());
	read_filter();
}

void test_send_to_motor(unsigned char message){
	write_motor(message);
	printf("Sent to MOTOR:%d\n",(int)message);
}

void test_receive_motor(){
	printf("MOTOR received:%d\n",(int)read_motor());
	read_motor();
}
