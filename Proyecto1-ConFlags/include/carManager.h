#ifndef __CARMANAGER_H
#define __CARMANAGER_H

#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include "bridge.h"

time_t t;

extern int BRIDGE_SIZE, SCHEDULER, AVARAGE_SPEED, DEBUGGER,
            RIGHT_OFFICER, LEFT_OFFICER, TRAFFIC_CONTROL_B1, TRAFFIC_CONTROL_B2, 
            TRAFFIC_CONTROL_B3, SEM_TIME_L, SEM_TIME_R, A_P, R_P, MY_PTHREAD;
extern double DISTRIBUTION;

/**
 * @brief 
 * @details 
 * @return 
 */
int genRandom();

/**
 * @brief Create a cars object
 * 
 * @param pQueue 
 * @return void* 
 */
void *create_cars(void *pBridge);


#endif