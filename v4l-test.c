/* This file is written by Jon Kristensen and Mahdi Abdinejadi. */

#include <asm/types.h> /* needed for videodev2.h */
#include <fcntl.h>
#include <linux/videodev2.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <errno.h>

#include<stdlib.h>
#include<errno.h>
#include<netdb.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>

#include "v4l-test.h"

#include "network.h"

#define DEVICE_PATH "/dev/video0"

#define CAMERA_WIDTH 800
#define CAMERA_HEIGHT 600

struct buffer *bs = NULL;

int fd = 0;

/* reads a frame and prints its content */
int read_frame()
{
  struct v4l2_buffer b;
  unsigned int i;

  memset(&(b), 0, sizeof(b));

  b.memory = V4L2_MEMORY_MMAP;
  b.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

  if(ioctl(fd, VIDIOC_DQBUF, &b) == -1) /* blocks if no buffer in queue */
  {
    switch(errno)
    {
      case EAGAIN:
        return 0;

      case EIO:

    default:
      fprintf(stderr, "Error dequeing the buffer.\n");
    }
  }

  camera_input_stream_encode(bs);
  tcp_send(bs, sockfd);

  if(ioctl(fd, VIDIOC_QBUF, &b) == -1)
  {
    fprintf(stderr, "Error enqueing the buffer.\n");
    return -1;
  }

  return 0;
}

int main(int argc, char **argv)
{ /*--Begin---this part is added by @Yuhan Qiu and @Shuang Wu* for creating the server*/
  int sockfd;

  struct sockaddr_in server_addr;
  struct sockaddr_in client_addr;

  int portnumber;

  if(2!=argc){
  
    fprintf(stderr,"Usage:%s portnumber\a\n",argv[0]);

    exit(1);
  }

  if((portnumber=atoi(argv[1]))<0){

    fprintf(stderr,"Usage:%s portnumber\a\n",argv[0]);
    exit(1);
  }

  //creating the server
  if(1==(sockfd=socket(AF_INET,SOCK_STREAM,0))){

    fprintf(stderr,"Socket error:%s portnumber\a\n",strerror(errno));

    exit(1);
  }

  printf("Socket id is %d\n",sockfd);

  bzero(&server_addr,sizeof(struct sockaddr_in));

  server_addr.sin_family=AF_INET;
  server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
  server_addr.sin_port=portnumber;
  
  //binding sockfd

  if(-1==bind(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr))){
    fprintf(stderr,"Bind error:%s\n\a",strerror(errno));

    exit(1);

  }

  printf("Bind\n");


  //listening sockfd
  if(-1==(listen(sockfd,5))){
    fprintf(stderr,"Listen error:%s\n\a",strerror(errno));
    exit(1);
  }
  printf("Listen\n");

/*--end--this part is added by @Yuhan Qiu and @Shuang Wu*/

  /* open the v4l2 device, get a file descriptor */

  printf("Opening device...\n");

  fd = open(DEVICE_PATH, O_NONBLOCK | O_RDWR);

  if(fd == -1)
  {
    fprintf(stderr, "Could not open device.\n");
    return -1;
  }

  /* check the capabilities of the device */

  printf("Checking device capabilities...\n");

  struct v4l2_capability c;

  /* assumption: we can use ioctl instead of xioctl */

  if(ioctl(fd, VIDIOC_QUERYCAP, &c) == -1) // todo: error checking
  {
    fprintf(stderr, "Device is not a V4L2 device.\n");
    return -1;
  }

  if(!(c.capabilities & V4L2_CAP_VIDEO_CAPTURE))
  {
    fprintf(stderr, "Device is not a video capturing device.\n");
    return -1;
  }

  if(!(c.capabilities & V4L2_CAP_STREAMING))
  {
    fprintf(stderr, "Device does not support streaming.\n");
    return -1;
  }

  /* set format */

  printf("Setting video format...\n");

  struct v4l2_format f;
  memset(&(f), 0, sizeof(f));

  f.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
  f.fmt.pix.width = CAMERA_WIDTH;
  f.fmt.pix.height = CAMERA_HEIGHT;
  f.fmt.pix.field = V4L2_FIELD_INTERLACED;
  f.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;

  if(ioctl(fd, VIDIOC_S_FMT, &f) == -1)
  {
    fprintf(stderr, "Could not negotiate format.\n");
    return -1;
  }

  /* initialize memory mapping */

  printf("Initializing memory mapping...\n");

  struct v4l2_requestbuffers rb;
  memset(&(rb), 0, sizeof(rb));

  rb.count = 4;
  rb.memory = V4L2_MEMORY_MMAP;
  rb.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

  if(ioctl(fd, VIDIOC_REQBUFS, &rb) == -1)
  {
    fprintf(stderr, "Device does not support memory mapping.\n");
    return -1;
  }

  if(rb.count < 2)
  {
    fprintf(stderr, "Insufficient buffer memory.\n");
    return -1;
  }

  bs = calloc(rb.count, sizeof(*bs));

  if(!bs)
  {
    fprintf(stderr, "Out of memory.\n");
    return -1;
  }

  int i = 0;

  for(i = 0; i < rb.count; i++)
  {
    struct v4l2_buffer b;
    memset(&(b), 0, sizeof(b));

    b.index = i;
    b.memory = V4L2_MEMORY_MMAP;
    b.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    if(ioctl(fd, VIDIOC_QUERYBUF, &b) == -1)
    {
      fprintf(stderr, "Buffer status error; invalid buffer type or index.\n");
      return -1;
    }

    bs[i].size = b.length;
    bs[i].start = mmap(NULL, b.length, PROT_READ | PROT_WRITE, MAP_SHARED,
                       fd, b.m.offset);

    if(bs[i].start == MAP_FAILED)
    {
      fprintf(stderr, "Memory mapping failed.\n");
      return -1;
    }
  }

  printf("Initializing capturing...\n");

  unsigned int j;
  enum v4l2_buf_type t;

  for(j = 0; j < i; j++)
  {
    struct v4l2_buffer b;
    memset(&(b), 0, sizeof(b));

    b.index = j;
    b.memory = V4L2_MEMORY_MMAP;
    b.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

    if(ioctl(fd, VIDIOC_QBUF, &b) == -1)
    {
      fprintf(stderr, "Error enqueing the buffer.\n");
    }
  }

  t = V4L2_BUF_TYPE_VIDEO_CAPTURE;

  if(ioctl(fd, VIDIOC_STREAMON, &t) == -1)
  {
    fprintf(stderr, "Error streaming IO.\n");
  }

  printf("Capturing...\n");


    tcp_send(bs, sockfd);
  

  // todo: dispose of everything

  return 0;
}
