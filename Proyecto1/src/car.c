#include "../include/car.h"
#include <stdio.h>
#include <string.h>

int _globalCarID =0;

void createCar(_car *pCar, char * pColor, char* pModel, int pPriority,  
                int pAmountTrips, float pStopTime, int pAvgSpeed, char* side, list* pCarList){
    (*pCar).id =_globalCarID++;   
    (*pCar).model = pModel;
    (*pCar).color = pColor;    
    (*pCar).priority = pPriority;
    (*pCar).amountTrips = pAmountTrips;  
    (*pCar).stopTime = pStopTime;
    (*pCar).avgSpeed = pAvgSpeed;
    (*pCar).activeRunning = 0;
    (*pCar).bridgePos = 0;
    (*pCar).alive = 0;
    (*pCar).side = side;    
    list_append(pCarList, &pCar);    
}
