
#include <stdlib.h>
#include <stdint.h>

#include "moto_interface.h"
#include "stab_interface.h"
#include "ca_interface.h" /* remember to change this! */
#include "sched_stubs.h"

#ifdef PC
/* non-arduino includes */
#include <stdio.h>

#endif /* PC */

#ifdef ARDUINO

#endif /* ARDUINO */

#include "sched_naive_sched.h"

#define NUMBER_OF_RUN_FUNS 10
#define NUMBER_OF_INIT_FUNS 6

static int16_t system_init(Fun_t funArrInit[]);
static void naive_loop(Fun_t funArrRun[]);

void sched_naive_init(void){
    /* function pointers to modules init functions */
    Fun_t funArrInit[] = {  &protoInit,
                            &moveInit,
                            &ca_init,
                            &stab_init,
                            &filterInit,
                            &moto_init };
    
    /* function pointers to modules run functions */
    Fun_t funArrRun[] = {   &protoRun,
                            &moveRun,
                            &protoRun,
                            &ca_run,
                            &protoRun,
                            &stab_run,
                            &protoRun,
                            &filterRun,
                            &protoRun,
                            &moto_run };
    
    /* call all other groups inits */
    if (system_init(funArrInit) != 1) {
        /* something went wrong during system initialization */
        #ifdef PC
            printf("Error in system initialization sequence!\n");
            exit(1);
        #endif /* PC */
        #ifdef ARDUINO
            /*  
             *  Do we have a way to give fatal error message on arduino,
             *  and exit? 
             */
            exit(1);
            
        #endif /* ARDUINO */
    }
    else {
        /* system initialization OK */
        /* call loop, pass array as argument */
        naive_loop(funArrRun);
    }
}

int16_t system_init(Fun_t *funArrInit){
    int16_t i;
    int16_t res;
    
    for (i = 0; i < NUMBER_OF_INIT_FUNS; i++){
        res = (*funArrInit[i])();

        #ifdef PC
        #ifdef DEBUG
            printf("function call result: %d\n", res);
        #endif /* DEBUG */
        #endif /* PC */
    }
    
    return 1;
}

void naive_loop(Fun_t *funArrRun){
    int16_t i;
    int16_t res;
    
    #ifdef DEBUG
        /* DEBUG flag is set, only do one loop iteration */
        for (i = 0; i < NUMBER_OF_RUN_FUNS; i++) {
            res = (*funArrRun[i])();
        }
        
    #else
        /* DEBUG flag is not set, do the normal scheduler loop */
        while (1) {
            for (i = 0; i < NUMBER_OF_RUN_FUNS; i++) {
                res = (*funArrRun[i])();
            }
        }
    #endif /* DEBUG */
}

int16_t time(void){
    int16_t currentTime;
    
    #ifdef PC
        /* call non-arduino timing functions to retrieve current time */
    #endif /* PC */
    
    #ifdef ARDUINO 
        /* call arduino specific timing functions to retrieve current time */    
    #endif /* ARDUINO */
    
    return currentTime;
}