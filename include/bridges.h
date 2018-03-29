/**
 * bridges.h
 * @details 
 * 
 * @author Jairo Mendez Martinez <jairomendezmartinez@gmail.com>
 * @author David Monestel Aguilar <p.david06.p@gmail.com>
 * @date 27-03-2018
 */ 


#ifndef _BRIDGES_H
#define _BRIDGES_H

#include <stdio.h>
#include <string.h>
/* TO USE PTHREAD LIBRARY*/
#include <pthread.h>
#include "../src/priority_queue.c"


/**
 * @brief [brief description]
 * @details [long description]
 * 
 */
struct bridge {	
	int size;
	int car_in;
};

/**
 * @brief set the size of the bridge
 *
 * @param pBridge bridge where the size is gonna to be setted
 * @param pSize the size of the bride
 */
void setSize(struct bridge pBridge, int pSize);

/**
 * @brief 
 * @details 
 * 
 * @param pBridge bridge where the car inserted are gonna to be updated
 * @param pCarIn amount of cars in the bridge
 */
void updateBridge(struct bridge pBridge, int pCarIn);

/**
 * @brief insert a car into the bridge
 * @details A car will be inserted into the bridge if there is space available
 * 
 * @param pBridge bridge where the car is gonna to be inserted
 * @param pCar car to insert
 */
void insertCar(struct bridge pBridge, struct _car pCar);

/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param bridge [description]
 */
void semaphore(struct bridge);

/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param bridge [description]
 */
void transit_official(struct bridge);

/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param bridge [description]
 */
void jungle_law(struct bridge);

#endif