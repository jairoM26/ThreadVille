#ifdef __APPLE__
#define _XOPEN_SOURCE
#endif

#include "../include/mythread.h"

/* The myThread "queue" */
static myThread threadList[ MaxNum_THREADS ];
static myThread threadList_RR_Running[ MaxNum_THREADS ];

/* The index of the currently executing myThread */
static int currentThread = -1;
/* A boolean flag indicating if we are in the main process or if we are in a myThread */
static int inMainThread = 0;
/* The number of active fibers */
static int numThreads = 0;
/* Scheduler algoritm 1: Selsfish Round Robin, 2:Lottery, 3:Soft Real Time*/
static int SCHEDULER_ALGORITHM =0;
/* The quantum in seconds*/
int QUANTUM=1;
int RR_CurrentProcess=0;
/* The "main" execution context */
static ucontext_t mainContext;


/**
* This method uses every quantum in order to use the threads with its signal
* @sig signal to manage threads
*/

void signalHandler(int sig) {
    int randNum = rand() % 10;
		mythread_yield();	
    alarm(QUANTUM);
}


/**
 *  Apply the function of changing contexts
 *  Stops the running process and starts the next process
*/
void changeContext(){
	if ( numThreads == 0 ) return;	

	currentThread = getNext_IDThreadExe();   //Get the next thread execution ID
	
	LF_DEBUG_OUT1( "Switched to myThread %d.", currentThread );
	inMainThread = 1;
	swapcontext( &mainContext, &threadList[ currentThread ].context );
	inMainThread = 0;
	LF_DEBUG_OUT1( "myThread %d switched to main context.", currentThread );
	if ( threadList[currentThread].active == 0 ){
		LF_DEBUG_OUT1( "myThread %d is finished. Cleaning up.\n", currentThread );
		/* Free the "current" myThread's stack */
		free( threadList[currentThread].stack );
		/* Swap the last myThread with the current, now empty, entry */
		-- numThreads;
		if ( currentThread != numThreads ){
			threadList[ currentThread ] = threadList[ numThreads ];
		}
		threadList[ numThreads ].active = 0;
	}
}
/**
 * Calls the scheduler algorithm respectively by user choice 
 * Where:
 *        -SCHEDULER ALGORTIHM = 1  is Lottery Algorithm
 * 		  -SCHEDULER ALGORTIHM = 2  is Soft Real Time Algorithm
 * 		  -SCHEDULER ALGORTIHM = x or not specified , is RR Algorithm
 * */
int getNext_IDThreadExe(){
	if(SCHEDULER_ALGORITHM==2){//Soft real time
		int next=0;
		return SRT();
	}else if(SCHEDULER_ALGORITHM==1){//Lottery
		//printf("Scheduler: Lottery\n");
		return lottery();
	}else{//Selsfish Round Robin
		//printf("Scheduler: Selsfish Round Robin\n");
		return roundRobin_Algorithm();
	}
}



/**
 * Soft Real Time Algorithm
*/
int SRT(){
	int next = (currentThread + 1) % numThreads;
	if(threadList[next].thread_exited==1){
		currentThread++;
		return SRT();
 	}else{
	 	printf("SRT selected: %d\n", next);
	 	return next;
	}
}
/**
 * Lottery Algorithm
*/
int lottery(){
	int totaltickets=0;
	int i=0;
	for(i=0;i<numThreads;i++){
		totaltickets+=threadList[i].PRIO;
	}int winnerTicket = rand() % totaltickets;
	if(threadList[winnerTicket].thread_exited==1){
		 return lottery();
  }else{
		printf("Lottery selected: %d\n",winnerTicket);
		return winnerTicket;
	}
}

int roundRobin_Algorithm(){

	int i;

	//Fin out the next one in the running tail
	for(i=0;i<numThreads;i++){
		if(threadList[i].thread_exited==0){
			if(RR_CurrentProcess==numThreads-1){
				RR_CurrentProcess=0;
				break;
			}else if(i>RR_CurrentProcess){
				RR_CurrentProcess=i;
				break;
			}
		}
	}
		printf("selected by Round Robin Process: %d\n",RR_CurrentProcess);
		return RR_CurrentProcess;
//	}
	//return (currentThread + 1) % numThreads;
}


/**
 * Records Thread data when started, it shows when a thread is active or if it is done
*/
static void mythread_Start( void (*func)(void*), void* pArg){
	threadList[currentThread].active = 1;
	func(pArg);
	threadList[currentThread].active = 0;
	mythread_yield();
}

/**
 * Sets everythinh for the thread initialization. Thread start running.
*/
int mythread_create(myThread* pmythread, mythread_attr_t* pAttri, void *(*func)(void*), void* pArg ){
	if ( numThreads == MaxNum_THREADS ) return LF_MAXFIBERS;
	if (pAttri!=NULL){
		QUANTUM=pAttri->QUANTUM;	
		SCHEDULER_ALGORITHM=pAttri->SCHED_ALG;		
	}
	getcontext( &threadList[numThreads].context );

	//Set stack context
	threadList[numThreads].PRIO=pAttri->PRIO;
	threadList[numThreads].thread_SchedulerAlgorithm = pAttri->SCHED_ALG;
	threadList[numThreads].context.uc_link = 0;
	threadList[numThreads].stack = calloc(1, Thread_STACK );
	threadList[numThreads].context.uc_stack.ss_sp = threadList[numThreads].stack;
	threadList[numThreads].context.uc_stack.ss_size = Thread_STACK;
	threadList[numThreads].context.uc_stack.ss_flags = 0;
	threadList[numThreads].thread_id = pAttri->thread_car_id;
	threadList[numThreads].thread_exited=0;
	if ( threadList[numThreads].stack == 0 ){
		LF_DEBUG_OUT( "Error: Could not allocate stack." );
		return LF_MALLOCERROR;
	}

	// Create the context using mythread_Start function .
	makecontext( &threadList[ numThreads ].context, (void (*)(void)) &mythread_Start, 2, func, pArg );
	++ numThreads;

	return LF_NOERROR;
}



//Mark as exit the pID thread
/**
 * Set an exit flag for the thread with the id seleceted 
 * @param pID: Id of the thread that needs to exit
*/
int mythread_end(int pID){
	return mythread_exit(pID);
}

/**
 * Auxiliar of mythread_end
 * @param pID: Id of the thread that needs to exit
*/
int mythread_exit(int pID){
	//threadList[numThreads].thread_id
	printf("Thread exited for: %d\n",pID);
	int i;
	for(i=0;i<numThreads;i++){
		if(threadList[i].thread_id==pID){
			threadList[i].thread_exited=1;
			break;
		}
	}
}

/**
 * Changes Thread domain, it change from the main process to the thread
*/
void mythread_yield(){
	signal(SIGALRM, signalHandler);
 	alarm(1);
	// The program is in my threada and it is needed to switch to the main process
	if ( inMainThread )
	{
		LF_DEBUG_OUT1( "libfiber debug: myThread %d yielding the processor...", currentThread );
		swapcontext( &threadList[currentThread].context, &mainContext );
	}
	//The program is in the main process and it is needed to dispatch a new myThread
	else
	{	
		changeContext();
	}
	return;
}


/**
 * Bind the running threads
*/
int mythread_join(){
	int threadsLeft = 0;

	//Program in a myThread, wait for all the other threads to quit 
	if ( inMainThread ) threadsLeft = 1;

	LF_DEBUG_OUT1( "Waiting until there are only %d threads remaining...", threadsLeft );

	//Execute all threads until they finish or exits	
	while ( numThreads > threadsLeft ){
		mythread_yield();
	}
	return LF_NOERROR;
}

/**
 * Separate the thread execution from the thread object
*/
int mythread_detach(){
	//printf("Not implemmented yet\n");

	//TODO 

}

int mymutex_init(mutextType* pLock){
		pLock->flag=0;
		return 0;
}


int mymutex_destroy(mutextType* pLock){
	free(pLock);
	return 0;
}


int mymutex_lock(mutextType* pLock){
		while(pLock->flag==1){}
		pLock->flag=1;
		return 0;
}

int mymutex_unlock(mutextType* pLock){
	pLock->flag=0;
	return 0;
}

int mymutex_trylock(mutextType* pLock){
	if(pLock->flag==1){
		return 1;
	}else{
		pLock->flag=1;
		return 0;
	}
}


/* Sets all the fibers to be initially inactive */
/**
 * Set the scheduler that is going to be running
 * @param pScheduler: Scheduler that's going to run
*/
void mythread_setsched(int pScheduler){
	srand(time(NULL));
	SCHEDULER_ALGORITHM=pScheduler;
	int i;
	for ( i = 0; i < MaxNum_THREADS; ++ i ){
		threadList[i].active = 0;
	}
	return;
}