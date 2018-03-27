#include "car.h"

/*
* Creates a _car data Type and assign its attributes
    * pColor = car color
    * pModel = name of the model 
    * pPriority = priority of the car
    * pInitPos = character of the Initial point EJ: X or Y
    * pEndPos = character of the final point EJ: X or Y
    * pAmountTrips = quantity of trips before the car Die
    * pStopTime = quantity of time to wait before starts a new trip
    * pAvgSpeed = Speed of the car
*/
void createCar(int pColor, char* pModel, int pPriority, 
char pInitPos, char pEndPos, int pAmountTrips, float pStopTime, float pAvgSpeed,list* pCarList)
{
    struct _car newCar;     /* Declare newCar of type _car */    

    newCar.model = pModel;
    newCar.color = pColor;    
    newCar.priority = pPriority;
    newCar.initialPosition = pInitPos;
    newCar.finalPosition = pEndPos;
    newCar.amountTrips = pAmountTrips;  
    newCar.stopTime = pStopTime;
    newCar.avgSpeed = pAvgSpeed;    
    list_append(pCarList, &newCar);
}

void* carManager(void *pArg)
{

    /*while (pArg.amountTrips > 0)
    {
        for()
        {
            pthread_mutex_lock(&threadsMutex);
            pArg

        
        
        pthread_mutex_unlock(&threadsMutex);

        }
        
        usleep(10000);
    }*/
    

}