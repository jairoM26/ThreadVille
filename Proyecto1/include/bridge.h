#ifndef __BRIDGE_H
#define __BRIDGE_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include "priority_queue.h"
#include "car.h"

int bridgeID;

extern int BRIDGE_SIZE, SCHEDULER, AVARAGE_SPEED, DEBUGGER,
        RIGHT_OFFICER, LEFT_OFFICER, TRAFFIC_CONTROL_B1, TRAFFIC_CONTROL_B2, 
        TRAFFIC_CONTROL_B3, SEM_TIME_L, SEM_TIME_R, A_P, R_P, MY_PTHREAD;
extern double DISTRIBUTION;

/**
 * @brief structure for the bridge list
 * @details struct that contains a list of cars (5)
 */
typedef struct {
    heap_t *node1;   //queue for node 1 of the bridge
    heap_t *node2;  //queue for node 2 of the bridge
    heap_t *node3;  //queue for node 3 of the bridge
    heap_t *node4;  //queue for node 4 of the bridge
    heap_t *node5;  //queue for node 5 of the bridge
    char* stringInBridge; //save the cars in bridge
} bridgeList;


/**
 * @brief Structure of a bridge
 * @details Struct the simulate the behavior of a bridge
 */
typedef struct { 
    heap_t *inLeftQueue;   //priority queue at the left of the bridge (input)
    heap_t *inrightQueue;  //priority queue at the right of the bridge (input)
    bridgeList list;       //queue of the bridge (is a priority queue of all elements with priority of 1)
    int size;              //max size of the bridge (max space for cars = 5 *Setting on the config.conf file)
    int car_in;            //contain the count of how many cars are in the bridge
    int id;                //contain the id of the bridge
    int side;              //contain if the bridge its excecuting left or right semaphore, or official
    char* bridgeString;
} bridge;


bridge* bridge1;
bridge* bridge2;
bridge* bridge3;
pthread_mutex_t lock;
mutextType myLock;

/**
 * @brief Init the bridge structure
 * @details where the bridge its initialize its queues, size
 * 
 * @param pBridge bridge to be intialized
 * @param pSize max size of the bridge
 */
void initBridge(bridge *pBridge, int pSize);

/**
 * @brief 
 * @details 
 * 
 * @param pBridge 
 * @return 
 */
void *semaphoreAlg(void* pBridge);

/**
 * @brief 
 * @details 
 * 
 * @param pBridge 
 * @return 
 */
void *officer(void* pBridge);

/**
 * @brief 
 * @details 
 * 
 * @param pBridge 
 * @return 
 */
void *jungleLaw(void* pBridge);

/**
 * @brief 
 * 
 * @param pCar 
 * @return void* 
 */
void *carMovement(void* pCar);

/**
 * @brief 
 * 
 * @param pBridge 
 * @return void* 
 */
void *bridgeChar(void* pBridge);
#endif