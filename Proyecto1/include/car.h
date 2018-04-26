#ifndef __CAR_H
#define __CAR_H

#include <stdio.h>
#include <string.h>
/* TO USE PTHREAD LIBRARY*/

/*************************/
#include "list.h"

extern int _globalCarID;
extern int BRIDGE_SIZE, SCHEDULER, AVARAGE_SPEED, DEBUGGER, DISTRIBUTION, RIGHT_OFFICER, LEFT_OFFICER, TRAFFIC_CONTROL_B1, TRAFFIC_CONTROL_B2, TRAFFIC_CONTROL_B3, SEM_TIME_L, SEM_TIME_R, A_P, R_P;

/**
 * @brief 
 * 
 */
typedef struct
{
    int id;                 //car id
    int priority;           // bridge access priority    
    int amountTrips;        // number of trips before dying
    float stopTime;         // stop time when a car arrives to a destination
    float avgSpeed;         // car speed
    char * color;              // car color in RGB
    char* model;            // car model in String
    int size;               // car size, normal cars = 1
    int activeRunning;      // if car is moving inside the bridge
    int alive;              //
    int bridgePos;          // car position inside the bridge
    char * side;            //side of the bridge
    int bridge;             //indicate in which bridge the car is
} _car;


/*
 *@brief Creates a _car data Type and assign its attributes
 *
 *@param pCar = car to be created
 *@param pColor = car color
 *@param pModel = name of the model 
 *@param pPriority = priority of the car
 *@param pInitPos = character of the Initial point EJ: X or Y
 *@param pEndPos = character of the final point EJ: X or Y
 *@param pAmountTrips = quantity of trips before the car Die
 *@param pStopTime = quantity of time to wait before starts a new trip
 *@param pAvgSpeed = Speed of the car
*/
void createCar(_car *pCar, char * pColor, char* pModel, int pPriority,  
                int pAmountTrips, float pStopTime, int pAvgSpeed, char* side, list* pCarList);
                
#endif