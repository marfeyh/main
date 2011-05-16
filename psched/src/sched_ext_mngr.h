/*! * * * * * * * * * * * * * * * * * *
 * @file extsched_mngr.h
 * @brief Extended Sheduler process manager
 * @date 2011-05-02
 * @author Taher Odeh
 * @version 1.2
 * * * * * * * * * * * * * * * * * * * */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <unistd.h> 
#include <time.h>

//#include "mq.h" /* message queue disabled */
#include "extsched_sm.h" /* include shared memory functions */

/*  process struct  */
struct extsched_proc{
  pid_t pid; /* pid of the running process */
  char running; /* process status (not used). */
  time_t running_time; /* elapsed time (not used) */
  int16_t (*init_fun)(); /* init function pointer */
  int16_t (*run_fun)(); /* run function pointer */
  enum proc_type type; /* process type (defined in extsched_proc_types.h) */
};

/* process poll struct */  
struct proc_pool{
  struct extsched_proc *p; /* pointer to process */
  struct proc_pool *next_proc; /* pointer to next process */
  short int num_procs; /* number of processes running */
  int shmid; /* shared memoy id */
};

<<<<<<< HEAD
// creates a process by passing a function pointer.

/* creates a process.
=======
/** creates a process.
>>>>>>> 263235128aabdf1a6d600e10d13724c473ef3e04
   return: a process struct member with it's type, init function and run function set.
 */
struct extsched_proc create_proc(enum proc_type type, int16_t (*init_fun)(), int16_t (*run_fun)());

<<<<<<< HEAD
/* initializes a process and adds it to the poll */
void init_proc(struct extsched_proc *);

/* initializes a process poll */
void init_pool(struct proc_pool **);

/* frees the poll */
void free_pool(struct proc_pool *);

/* runs the processes in the poll passed */
=======
/** initializes a process and adds it to the poll */
void init_proc(struct extsched_proc *);

/** initializes a process poll */
void init_pool(struct proc_pool **);

/** frees the poll */
void free_pool(struct proc_pool *);

/** runs the processes in the poll passed */
>>>>>>> 263235128aabdf1a6d600e10d13724c473ef3e04
void run_pool(struct proc_pool *);

// message queue related functions

<<<<<<< HEAD
/* receive a meessage related to the process type id.
=======
/** receive a meessage related to the process type id.
>>>>>>> 263235128aabdf1a6d600e10d13724c473ef3e04
   return: length of data read.
 */
size_t proc_recv(enum proc_type, char *);

<<<<<<< HEAD
/* sends a meessage to the message \n
=======
/** sends a meessage to the message \n
>>>>>>> 263235128aabdf1a6d600e10d13724c473ef3e04
   queue assigned to a specific process.
   return: length of data written.
 */
size_t proc_send(enum proc_type, enum proc_type, char *); 

// Shared memory related functions. 

<<<<<<< HEAD
/* reads the process' state from the shared memory
=======
/** reads the process' state from the shared memory
>>>>>>> 263235128aabdf1a6d600e10d13724c473ef3e04
 * allocated and stores it in a buffer. 
 * return: length of data read.
 */
int proc_read_state(enum proc_type, void *);

<<<<<<< HEAD
/* writes the buffer to the shared memory
=======
/** writes the buffer to the shared memory
>>>>>>> 263235128aabdf1a6d600e10d13724c473ef3e04
 * located to a specific process
 * return: length of data written.
 */
int proc_write_state(enum proc_type, void *);

/* global pool */
struct proc_pool *pool;
