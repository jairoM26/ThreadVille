#include <stdio.h>
#include <string.h>

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
void createCar(_car *pCar, int pColor, char* pModel, int pPriority,  char pInitPos, 
    char pEndPos, int pAmountTrips, float pStopTime, int pAvgSpeed){    

    (*pCar).model = pModel;
    (*pCar).color = pColor;    
    (*pCar).priority = pPriority;
    (*pCar).initialPosition = pInitPos;
    (*pCar).finalPosition = pEndPos;
    (*pCar).amountTrips = pAmountTrips;  
    (*pCar).stopTime = pStopTime;
    (*pCar).avgSpeed = pAvgSpeed;
}


/**
 * @brief Mannager of the car list
 * @details 
 * 
 * @param pArg _car list to be manage
 * @return nothing
 */
void* carManager(void *pArg){}

/**
 * @brief set the route of the car
 * @details [long description]
 */
void setRoute (){} //Uses Djikstra to select the best route

/**
 * @brief set the priority of the car
 * 
 * @param pPriority = priority to be set
 */
void setPriority(int pPriority){}

/**
 * @brief set the start and end position of the car
 * 
 * @param pInitPos initial position
 * @param pEndPos end position
 */
void setStartEndPoint(char pInitPos, char pEndPos){}

/**
 * @brief 
 * @details 
 * 
 * @param x 
 * @param y 
 */
void setPosition(int x, int y){}

/**
 * @brief 
 * @details 
 * 
 * @param pAmountTrips 
 */
void setAmountTrips(int pAmountTrips){}

/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param pStopTime [description]
 */
void setStopTime(float pStopTime){}

/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param pNextDestination [description]
 */
void setNextDestination(char pNextDestination){}

/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param pAvgSpeed [description]
 */
void setAvgSpeed(float pAvgSpeed){}

/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param pRGBColor [description]
 */
void setColor(int pRGBColor){}

/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param pModelString [description]
 * @param pCar
 */

void setModel(_car pCar, char* pModelString){
    pCar.model = pModelString;
}