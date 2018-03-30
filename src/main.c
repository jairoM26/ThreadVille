/**
 * main.c
 * @details program main
 * 
 * @author Jairo Mendez Martinez <jairomendezmartinez@gmail.com>
 * @author David Monestel Aguilar <p.david06.p@gmail.com>
 * @date 29-03-2018
 * 
 * compilation command: gcc main.c -o main
 * Execution: ./main
 */

#include <pthread.h>
#include <stdio.h>
#include "priority_queue.c"
#include "readConfigFile.c"
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex;

/**
 * @brief structure for the bridge list
 * @details struct that contains a list of cars (5)
 */
typedef struct {
    _car *carList;
} bridgeList;


/**
 * 
 * @brief Structure of a bridge
 * @details Struct the simulate the behavior of a bridge
 * 
 */
typedef struct { 
    heap_t *leftQueue;   //priority queue at the left of the bridge
    heap_t *rightQueue;  //priority queue at the right of the bridge
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
    pBridge->rightQueue = (heap_t *)calloc(1, sizeof (heap_t));
    pBridge->leftQueue = (heap_t *)calloc(1, sizeof (heap_t));    
    pBridge->list.carList = (_car *)calloc(pSize, sizeof (_car));
    pBridge->size = pSize;
    pBridge->car_in = 0;
}


void* create_cars(void *pQueue){

    heap_t myQueue =  *(heap_t *) pQueue;
    _car newCar;
    while(1){
        printf("Thread size %d\n", myQueue.len);
        usleep(1000000);
    }
}

int main () {
    int BRIDGE_SIZE = 0, SCHEDULER = 0, AVARAGE_SPEED = 0;
    readConfigFile(&SCHEDULER, &BRIDGE_SIZE, &AVARAGE_SPEED); //reading the config file
    printf( "bridgeSize: %d  scheduler: %d  avgSpeed: %d\n", BRIDGE_SIZE, SCHEDULER, AVARAGE_SPEED);


    pthread_t thread [1];

    bridge myBridge;

    initBridge(&myBridge, BRIDGE_SIZE);  
    printf("size %d\n", myBridge.rightQueue->len);

    int valid[1];
    valid[0] = pthread_create(&thread[0], NULL, create_cars, (void *)(myBridge.rightQueue)); 
    
    //xorT = pthread_create(&threadXOR, NULL, XOR, (void *)2);    
    
    if (valid[0]){
      printf("ERROR; return code from pthread_create() is %d\n", valid[0]);      
      exit(-1);
    }
    //if(xorT){
      //  printf("ERROR; return code from pthread_create() is %d\n", xorT);      
        //exit(-1);
    //}
    pthread_exit(NULL);
    
    
    return 0;
}