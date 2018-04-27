#ifndef LIBFIBER_H
#define LIBFIBER_H 1

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 		
#include <signal.h>
#include <ucontext.h>

#define	LF_NOERROR	0
#define	LF_MAXFIBERS	1
#define LF_MALLOCERROR	2
#define LF_CLONEERROR	3
#define	LF_INFIBER	4
#define LF_SIGNALERROR	5

/* Define a debugging output macro */
#ifdef LF_DEBUG

#include <stdio.h>
#define LF_DEBUG_OUT( string ) fprintf( stderr, "libfiber debug: " string "\n")
#define LF_DEBUG_OUT1( string, arg ) fprintf( stderr, "libfiber debug: " string "\n", arg )

#else

#define LF_DEBUG_OUT( string )
#define LF_DEBUG_OUT1( string, arg )

#endif

/* The maximum number of fibers that can be active at once. */
#define MaxNum_THREADS 400
/* The size of the stack for each mythread_setsched. */
#define Thread_STACK (1024*1024)


/* The myThread Structure
*  Contains the information about individual fibers.
*/
typedef struct mypthread{
	ucontext_t context; /* Stores the current context */
	int active; /* A boolean flag, 0 if it is not active, 1 if it is */
	/* Original stack pointer. On Mac OS X, stack_t.ss_sp is changed. */
	void* stack;//Stack pointer
	int PRIO; 	//Prority for lottery
	int thread_id;	//identifier
	int thread_exited;//end of thread
	int thread_SchedulerAlgorithm;
} myThread;

typedef struct mypthread_attr{//For the input un mythread_create
	int SCHED_ALG;	//Scheduler algorithm
	int PRIO;			//priority
	int QUANTUM;	//Timeslice, for the quantum
	int thread_car_id;
}mythread_attr_t;

typedef struct mux_type{//Input attribute for the mutex
	int flag;
}mutextType;

/* Should be called before executing any of the other functions. */
extern void mythread_start(void (*func)(void), void* pArg);

/* Creates a new mythread_setsched, running the function that is passed as an argument. */
//extern int mythread_create(mythread_t* pmythread, void (*func)(void) );

/* To handle which algorithm to schedule use*/
extern void mythread_setsched();
extern int getNextExe();
extern int lottery();
extern int roundRobin_Algorithm();
extern int SRT();

int mythread_create(myThread* pmythread, mythread_attr_t* pAttri, void *(*func)(void*), void* pArg );

/* Stop thread execution*/
extern int mythread_end();
extern int mythread_exit();

/* Yield control to another execution context. */
extern void mythread_yield();

/* Execute the fibers until they all quit. */
extern int mythread_join();

/**/
extern int mythread_detach(myThread* pmythread);


void changeContext();
int getNext_IDThreadExe();

/**
 * Start mutex selected 
 * param pLock: Mutex to Start
*/
int mymutex_init(mutextType* pLock);

/**
 * Destroy mutex selected
 * param pLock: Mutex to destroy
*/
int mymutex_destroy(mutextType* pLock);

/**
 * Lock the context when executing a user level thread.
 * @param pLock: mutext to lock
*/
int mymutex_lock(mutextType* pLock);

/**
 * Releasing the lock of the context when executing a user level thread.
 * @param pLock: mutext to unlock
*/
int mymutex_unlock(mutextType* pLock);
/**
 * Lock the context if it is free when executing a user level thread.
 * @param pLock: mutext to lock
*/
int mymutex_trylock(mutextType* pLock);

#endif
