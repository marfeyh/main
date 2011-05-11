#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>


#define PORT 9600


int main(){

int server_socket;
struct sockaddr_in server;



 if ((server_socket = socket(AF_INET,SOCK_DGRAM,0))<0){
    perror("socket()");
  }
  else{
    printf("Socket ok\n");
  }
  server.sin_family = AF_INET;
  server.sin_port = htons(PORT);
  server.sin_addr.s_addr = INADDR_ANY;

  if( bind(server_socket,(struct sockaddr *)&server,sizeof(struct sockaddr))<0){
    perror("bind()");
  }
  else{
    printf("Bind ok\n");
  }

  

  char send_data [5] = "hallo";

  while (1){
    sleep(1);
   
sendto(server_socket, send_data, strlen(send_data), 0,
              (struct sockaddr *)&server, sizeof(struct sockaddr));

 printf("sending %s\n", send_data);
  }
 close(server_socket);

  return 0;
}
