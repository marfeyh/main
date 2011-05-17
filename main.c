/*!
 *  @file main.c
 *
 *  @brief This .c file launches the scheduler which in turn launches \n
 *  all arduino related processes.
 *  
 *  @author Joakim
 *  @author Anders
 *  @date 2011-04-14
 *
 *  @history    2011-04-10 - wrote original code
 *              2011-04-14 - added Doxygen comments
 *              2011-04-26 - changed format of scheduler to \n
 *                           fit both implementations(Anders)
 *              2011-04-27 - updated structure (Anders)
 *              2011-05-02 - Added profiler (Anders)
 */

#ifdef PC
/* 
#define _PROFILE_
#include "sched_profiler.h" 
*/
#elif ARDUINO
#include "WProgram.h"
#endif /*PC ARDUINO */

/* Includes code for implementation */
#ifdef BATMAN
#include "sched_batman_main.h"
#elif NAIVE
#include "sched_naive_sched.h"
#endif /* BATMAN */

int sched_main(void)
{
#ifdef BATMAN
    sched_batman_init();
    sched_batman_run();
#elif NAIVE
    sched_naive_init();
#endif
    return 0;
}

#ifdef _PROFILE_
int profiler(void)
{
    profile_main();
}
#endif

int main(void)
{
#ifdef _PROFILE_
    profile_main();
#else
    sched_main();
#endif
    return 0;
}