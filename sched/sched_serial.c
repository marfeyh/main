#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <string.h>


#define MAX_BYTES 4
#define HEAD char head
#define LEN int len
#define CHSM unsigned int chsm
#define UNWRAP LEN + HEAD + CHSM
#define MOTO 1
#define STAB 2
#define SCHED 4
#define MOVE 3
#define CA 5

struct msg {
  int snder;
  int rcver;
  int len;
  char data[32];
} msg;


//FILE  uart_stream(uart_putchar, uart_getchar, _FDEV_SETUP_RW);
struct msg msg;
char rawdata[32];

//read RX buffer
int uart_point(){
   //Returns if no complete message has been recieved
  if ((UCSR1A & (1<<RXC1))){
      return -1;
    } 
  
  rawdata = UDRn;
     
  return 0;
}
  
//pick head
void processRaw(){
  
//pick head
void processRaw(){
  HEAD = rawdata[0];
  LEN = rawdata[1];
  HEAD = rawdata[0];
  LEN = rawdata[1];
  if(rawdata[LEN] != '\0'){
    strcpy(rawdata, &'\0');
  }
  char temp[(sizeof(char)*2)] = rawdata[2];
  CHSM = strcat(temp, rawdata[3]);
  // datalng = cleanoff(rawdata)


  char data[datalng];
  for(i = 0; i < (datalng/8); i++){
    data[i] = rawdata[i];
  }
}

/*bit shift to create snd and rcv. 0 - 15 will equal various components */
void shift(char head){
  buff = head;
  buff2 = buff;
  buff = buff >> 4;
  buff2 = buff << 4 >> 4;
  //buff2 = buff2 >> 4;
  buff = msg.snder;
  buff2 = msg.rcver;
}


int_8 clean_off(struct msg msg, data){
  msg.data = msg - UNWRAP; 
  return data;
}


//write to global variables

void write_proto(struct msg msg){
  part = msg.rcver;

  switch (part){
  
  case (MOTOR) {
    write_motor(msg.data[]);
  }
  case (MOVE) {
    write_move(msg.data[]);
  }
  case (STAB) {
    write_stab(msg.data[]);
  }
  case (SCHED){
    write_sched(msg.data[]);
  }
  case (CA) {
    write_CA(msg.data[]);
  }

  }
}


//write TX buffer


/*
char write_TX(char c);
char read_RX(char c);
char RXbuff[32], TXbuff[32];
char msg[32];



char write_TX(char c){
  int i;
  while(i != 0){
    TXbuff[i] sends to RXbuff[i];
    i++;
  }

  char read_RX(char c){
    int i;
    while(i != 0){
      strcpy(RXbuff[i],msg);
    }
*/
}