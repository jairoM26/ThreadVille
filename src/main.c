/**
 * main.c
 * @details program main
 * 
 * @author Jairo Mendez Martinez <jairomendezmartinez@gmail.com>
 * @author David Monestel Aguilar <p.david06.p@gmail.com>
 * @date 22-03-2018
 * 
 * compilation command: gcc main.c -o main
 * Execution: ./main
 */

#include <pthread.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
/***************************/
#include "priority_queue.c"
#include "readConfigFile.c"

int type [9] = {1,3,3,3,3,1,2,2,3};
int BRIDGE_SIZE = 0, SCHEDULER = 0, AVARAGE_SPEED = 0, DEBUGGER = 0;
char *models[] = {"Toyota","Izuzu","Ferrari", "Lamborgini", "Susuki", "Ford", "Mercedes", "Gio", "Mitsubishi"};

sem_t mutex;
time_t t;
/**
 * @brief structure for the bridge list
 * @details struct that contains a list of cars (5)
 */
typedef struct {
    _car *carList;
    int * bussyList;
} bridgeList;


/**
 * @brief Structure of a bridge
 * @details Struct the simulate the behavior of a bridge
 */
typedef struct { 
    heap_t *inLeftQueue;   //priority queue at the left of the bridge (input)
    heap_t *inrightQueue;  //priority queue at the right of the bridge (input)
    heap_t *outLeftQueue;   //priority queue at the left of the bridge  (output)
    heap_t *outrightQueue;  //priority queue at the right of the bridge (output)
    bridgeList list; //queue of the bridge (is a priority queue of all elements with priority of 1)
    int size;            //max size of the bridge (max space for cars = 5 *Setting on the config.conf file)
    int car_in;          //contain the count of how many cars are in the bridge
} bridge;

/**
 * @brief Init the bridge structure
 * @details where the bridge its initialize its queues, size
 * 
 * @param pBridge bridge to be intialized
 * @param pSize max size of the bridge
 */
void initBridge(bridge *pBridge, int pSize){	
    pBridge->inrightQueue = (heap_t *)calloc(1, sizeof (heap_t));
    pBridge->inrightQueue->type = "R";
    pBridge->inLeftQueue = (heap_t *)calloc(1, sizeof (heap_t));    
    pBridge->inLeftQueue->type = "L";
    pBridge->outrightQueue = (heap_t *)calloc(1, sizeof (heap_t));
    pBridge->outrightQueue->type = "R";
    pBridge->outLeftQueue = (heap_t *)calloc(1, sizeof (heap_t));    
    pBridge->outLeftQueue->type = "L";
    pBridge->list.carList = (_car *)calloc(pSize, sizeof (_car));
    pBridge->list.bussyList = (int *)calloc(pSize, sizeof (int));
    pBridge->size = pSize;
    pBridge->car_in = 0;
}


int genRandom(){    
    srand((unsigned) time(&t)); //setting the time t as the variable to initialize the root of srand 
    int tmp =  (rand()%8);
    return tmp;
}

void* semaphoreAlg(void* pBridge){
	bridge* myBridge =  (bridge *) pBridge;	
	int flag =0;  //flag = 0 green for right side and red for left side
	int bussy =0; //0 if there is no car on the bridge
    while(1){
    	if (DEBUGGER) printf("From semaphore left queue size is %d and right size is %d\n", myBridge->inLeftQueue->len, myBridge->inrightQueue->len);

    	//check if there is any car in the list
    	for(int i= 0; i < myBridge->size; i++){
    		if(myBridge->list.bussyList[i] == 1)
    			bussy = 1; 	//there is at least one car in the bridge
    	}

    	usleep(1005000); //TO_DO decrement the time of creating cars	
    }
}

void* officerAlg(bridge *pBridge){
    
}

void* jungleLawAlg(bridge *pBridge){
    
}

void* create_cars(void *pQueue){

    heap_t* myQueue =  (heap_t *) pQueue;  
    int i = 0;  
    while(1){  
        _car newCar;
        int rand = genRandom();
        if(i%2==0)
            createCar(&newCar, 3, models[rand], type[rand],'A','B',3,1.5,AVARAGE_SPEED+rand);
        else
            createCar(&newCar, 3, models[rand], type[rand],'A','B',3,1.5,AVARAGE_SPEED-rand);
        push(myQueue, type[rand], newCar);
        if (DEBUGGER) printf("Side bridge %s size %d, priority %d, modelo %s\n", myQueue->type ,myQueue->len, type[rand], models[rand]);      
        usleep(1005000); //TO_DO decrement the time of creating cars
    }
}

int main () {    
    readConfigFile(&SCHEDULER, &BRIDGE_SIZE, &AVARAGE_SPEED, &DEBUGGER); //reading the config file
    printf( "bridgeSize: %d  scheduler: %d  avgSpeed: %d debbuger: %d\n", BRIDGE_SIZE, SCHEDULER, AVARAGE_SPEED, DEBUGGER);

    pthread_t thread [2];

    bridge *myBridge = (bridge*)calloc(1, sizeof(bridge));
    initBridge(myBridge, BRIDGE_SIZE); 

    int valid[2];
    valid[0] = pthread_create(&thread[0], NULL, create_cars, (void *)(myBridge->inrightQueue)); 
    valid[1] = pthread_create(&thread[1], NULL, create_cars, (void *)(myBridge->inLeftQueue)); 
    valid[2] = pthread_create(&thread[2], NULL, semaphoreAlg, (void *)(myBridge)); 
    if (valid[0]){
      printf("ERROR; return code from pthread_create() is %d\n", valid[0]);      
      exit(-1);
    }
    if (valid[1]){
      printf("ERROR; return code from pthread_create() is %d\n", valid[1]);      
      exit(-1);
    }
    if (valid[2]){
      printf("ERROR; return code from pthread_create() is %d\n", valid[2]);      
      exit(-1);
    }
    pthread_exit(NULL);
    
    
    return 0;
}