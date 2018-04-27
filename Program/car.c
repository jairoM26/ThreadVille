#include "car.h"

int _globalCarID=0;

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
    newCar.id = _globalCarID;
    _globalCarID = _globalCarID+1;
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

    node_t *head = NULL;
    int ret;
    
    struct _car threadedCar =  *(struct _car*) pArg;
    printf("Car moving: %i\n", threadedCar.id); 
    enqueue(&head, 1);
    enqueue(&head, 2);
    enqueue(&head, 3);
    enqueue(&head, 4);
    enqueue(&head, 5);

<<<<<<< HEAD
=======
    /*while ((ret=dequeue(&head)) > 0) {
        printf("Car moving %d\n", ret);
    }*/
    //while (pArg.amountTrips > 0)
>>>>>>> de61c52e754e4f5db88eba1dfd6da58e327c8940
    while ((ret=dequeue(&head)) > 0) 
    {
        


        threadedCar.priority = ret;
                                           
        usleep(1000000);
    }

<<<<<<< HEAD
    printf("Car stopped\n");                                             
=======
    printf("Car stopped\n");                                                
>>>>>>> de61c52e754e4f5db88eba1dfd6da58e327c8940
    
}