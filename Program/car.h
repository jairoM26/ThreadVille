#ifndef __CAR_H
#define __CAR_H

#include <stdio.h>
#include <string.h>
/* TO USE PTHREAD LIBRARY*/

/*************************/
#include "list.h"
#include "queue.h"

extern int _globalCarID;


struct _car
{
    int id;                  // carID
    int priority;           // bridge access priority
    char initialPosition;   // cars always starts at Y
    char finalPosition;     // cars always finishes at Z
    int x,y;                // car position
    int amountTrips;        // number of trips before dying
    float stopTime;         // stop time when a car arrives to a destination
    char nextDestination;   // next label destination
    float avgSpeed;         // car speed
    int color;              // car color in RGB
    char* model;            // car model in String
    int size;               // car size, normal cars = 1
};


/**
 * 
 */
void createCar(int pColor, char* pModel, int pPriority, 
char pInitPos, char pEndPos, int pAmountTrips, float pStopTime, float pAvgSpeed, list* pCarList); //It should create a car and add it to the car list

void* carManager(void *pArg);

void setRoute (); //Uses Djikstra to select the best route

void setPriority(int pPriority);

void setStartEndPoint(char pInitPos, char pEndPos);

void setPosition(int x, int y);

void setAmountTrips(int pAmountTrips);

void setStopTime(float);

void setNextDestination(char pNextDestination);

void setAvgSpeed(float pAvgSpeed);

void setColor(int pRGBColor);

void setModel(char* pModelString);

void setSize(int pSize);



#endif