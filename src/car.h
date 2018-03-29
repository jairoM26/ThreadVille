#ifndef __CAR_H
#define __CAR_H


/*
 * 
 */
typedef struct
{
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
void createCar(_car pCar, int pColor, char* pModel, int pPriority,  char pInitPos, char pEndPos, int pAmountTrips, float pStopTime, float pAvgSpeed);





#endif