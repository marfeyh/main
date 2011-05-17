/*!
 *  @file conn_tcpserver.h
 *
 *  @brief Header file for tcpserver
 *
 *  @author Michal Musialik
 *  @date 2011-05-07
 *  @history    2011-05-07 - first outcast of conn_tcpserver.h file
 */

#define IP_BUFFER_LENGTH 200
#define PORT 9600 
#define BUFFER_SIZE 20
#define MAX_NR_OF_CONNECTIONS 3
#define CLOSE_NEW_SOCKET close(new_socket)
#define CLOSE_SOCKET_TCP close(socket_tcp)

struct sockaddr_in client; 
struct sockaddr_in server;
struct hostent * host ;

void host_setup(void);
int socket_create(void);
int socket_reusing(void);
int socket_keep_alive(void);
int socket_binding(void);
int socket_listening(void);
int socket_accept(void);
int socket_accept(void);
int data_passing(void);
void message_handling(int new_socket,int parrent_pid);

