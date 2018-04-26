#include "../include/bridge.h"

int bridgeID =0;

void initBridge(bridge *pBridge, int pSize){	
    pBridge->inrightQueue = (heap_t *)calloc(1, sizeof (heap_t));
    pBridge->inrightQueue->type = "R";
    pBridge->inLeftQueue = (heap_t *)calloc(1, sizeof (heap_t));    
    pBridge->inLeftQueue->type = "L";
    pBridge->list.node1 = (heap_t *)calloc(1, sizeof (heap_t));
    pBridge->list.node2 = (heap_t *)calloc(1, sizeof (heap_t));
    pBridge->list.node3 = (heap_t *)calloc(1, sizeof (heap_t));
    pBridge->list.node4 = (heap_t *)calloc(1, sizeof (heap_t));
    pBridge->list.node5 = (heap_t *)calloc(1, sizeof (heap_t));
    pBridge->size = pSize;
    pBridge->car_in = 0;
    pBridge->id = bridgeID++;
    pBridge->inLeftQueue->bridge = pBridge->id;
    pBridge->inrightQueue->bridge = pBridge->id;
    printf("bridge created with id: %d \n", pBridge->id);
}

/**
 * @brief 
 * @details 
 * 
 * @param pBridge 
 * @return 
 */
void* semaphoreAlg(void *pBridge){
	bridge* myBridge =  (bridge *) pBridge;
	int flag =1;  //flag = 0 green for right side and red for left side
    int semCount =0; //semaphore time counter
    while(1)
    {
        //printf("semCount == %d \n", semCount);
        if(semCount ==0)
        {
            if(myBridge->list.node1->len == 0 
            && myBridge->list.node2->len == 0 
            && myBridge->list.node3->len == 0 
            && myBridge->list.node4->len == 0 
            && myBridge->list.node5->len == 0)
            {
                printf("semCount ==0  \n");
                if(flag)
                {
                    if (DEBUGGER) printf("From semaphore right queue size is %d and semCount is: %d and flag: %d\n", 
                                        myBridge->inrightQueue->len, semCount, flag);
                    //check if the right queue has cars
                    if(myBridge->inrightQueue->len > 0 &&  myBridge->list.node5->len == 0)
                    {
                        if (DEBUGGER) printf("dequeu de semCount: %d \n", semCount);
                        _car* queueCar = pop(myBridge->inrightQueue);
                        queueCar->activeRunning = 1;
                        queueCar->alive = 1; 
                    }
                    else;
                    semCount++;
                    usleep(1000000); //TO_DO sleep correcto del semaforo
                }
                else
                {
                    if (DEBUGGER) printf("From semaphore left queue size is %d and semCount is: %d and flag is: %d\n", myBridge->inLeftQueue->len, semCount, flag);
                    //check if the right queue has cars
                    if(myBridge->inLeftQueue->len > 0 && myBridge->list.node1->len == 0 )
                    {
                        if (DEBUGGER) printf("dequeu de semCount: %d \n", semCount);
                        _car* queueCar = pop(myBridge->inLeftQueue);
                        queueCar->activeRunning = 1; 
                        queueCar->alive = 1;
                    }
                    else;
                    semCount++;
                    usleep(1000000); //TO_DO sleep correcto del semaforo
                }
            }
            else
            {
            }
            //usleep(1000000); //TO_DO sleep correcto del semaforo
        }
        else
        {
            if(flag)
            {
                while(semCount < 8)
                {              
                    if (DEBUGGER) printf("From semaphore right queue size is %d and semCount is: %d and flag: %d\n", 
                                        myBridge->inrightQueue->len, semCount, flag);
                    //check if the right queue has cars
                    if(myBridge->inrightQueue->len > 0 &&  myBridge->list.node5->len == 0)
                    {
                        if (DEBUGGER) printf("semaphore Counter: %d \n", semCount);
                        _car* queueCar = pop(myBridge->inrightQueue);
                        queueCar->activeRunning = 1;
                        queueCar->alive = 1; 
                    }
                    else;
                    semCount++;
                    usleep(1000000); //TO_DO sleep correcto del semaforo
                }
                semCount = 0;
                flag = 0;                
                usleep(1000000); //TO_DO sleep correcto del semaforo
                
            }            
            else
            {
                while(semCount < 10000)
                {              
                    if (DEBUGGER) printf("From semaphore left queue size is %d and semCount is: %d and flag is: %d\n", myBridge->inLeftQueue->len, semCount, flag);
                    //check if the right queue has cars
                    if(myBridge->inLeftQueue->len > 0 && myBridge->list.node1->len == 0 )
                    {
                        if (DEBUGGER) printf("semaphore Counter: %d \n", semCount);
                        _car* queueCar = pop(myBridge->inLeftQueue);
                        queueCar->activeRunning = 1; 
                        queueCar->alive = 1;
                    }
                    else;
                    semCount++;
                    usleep(1000000); //TO_DO sleep correcto del semaforo
                }
                semCount = 0;
                flag = 1;                                
                usleep(1000000); //TO_DO sleep correcto del semaforo                
            }
        }    	                
    }
    //return 0;
}

void *officer(void *pBridge){
	bridge* myBridge =  (bridge *) pBridge;
	int flag =1;  //flag = 0 left officer 1 right officer
    int officerCount =0; //officer counter    
    while(1){
        if(officerCount==0)
        {
            //check if the bridge is empty
            if(myBridge->list.node1->len == 0 
            && myBridge->list.node2->len == 0 
            && myBridge->list.node3->len == 0 
            && myBridge->list.node4->len == 0 
            && myBridge->list.node5->len == 0)
            {
                printf("officerCount ==0  \n");                                        
                if(flag)  //for right size            
                {
                
                    if (DEBUGGER) printf("From officer right queue size is %d and officerCount is: %d and flag is: %d\n", 
                                            myBridge->inrightQueue->len, officerCount, flag);
                        //check if the right queue has cars
                    if(myBridge->inrightQueue->len > 0 && myBridge->list.node5->len == 0 )
                    {                        
                        _car* queueCar = pop(myBridge->inrightQueue);
                        queueCar->activeRunning = 1; 
                        queueCar->alive = 1;
                        officerCount++;    
                        if (DEBUGGER) printf("Cars accesing the bridge,#cars: %d \n", officerCount);                        
                    }                            
                    else;
                        
                    usleep(250000);
                }
                
                else
                {   
                    if (DEBUGGER) printf("From officer left queue size is %d and officerCount is: %d and flag is: %d\n", 
                                            myBridge->inLeftQueue->len, officerCount, flag);
                    //check if the right queue has cars
                    if(myBridge->inLeftQueue->len > 0 && myBridge->list.node1->len == 0 )
                    {
                        if (DEBUGGER) printf("Cars accesing the bridge,#cars: %d \n", officerCount);
                        _car* queueCar = pop(myBridge->inLeftQueue);
                        queueCar->activeRunning = 1; 
                        queueCar->alive = 1;
                        officerCount++;
                        if (DEBUGGER) printf("Cars accesing the bridge,#cars: %d \n", officerCount);
                    }
                    else;                
                    usleep(250000);                       
                }
            }
            else
            {                    
            }                                                                                                                                                       
        }//End If Starting count                 
        else // BRIDGE ALREADY Has started, so it already verified it was empty
        {
            if(flag)  //for right size            
                {
                    while(officerCount < RIGHT_OFFICER){
                        if (DEBUGGER) printf("From officer right queue size is %d and officerCount is: %d and flag is: %d\n", 
                                            myBridge->inrightQueue->len, officerCount, flag);
                        //check if the right queue has cars
                        if(myBridge->inrightQueue->len > 0 && myBridge->list.node5->len == 0 )
                        {                            
                            _car* queueCar = pop(myBridge->inrightQueue);
                            queueCar->activeRunning = 1; 
                            queueCar->alive = 1;
                            officerCount++;
                            if (DEBUGGER) printf("Cars accesing the bridge,#cars: %d \n", officerCount);
                        }
                        else
                        {
                            //Bridge is full or right queue empty                        
                        }
                        
                        usleep(250000);

                    }
                    officerCount = 0;
                    flag = 0;          
                    //usleep(500000);                    
                }
                else //for left size
                { 
                    if (DEBUGGER) printf("From officer else left queue size is %d \n", myBridge->inLeftQueue->len);
                        while(officerCount < LEFT_OFFICER){
                            if (DEBUGGER) printf("From officer left queue size is %d and officerCount is: %d and flag is: %d\n", 
                                                myBridge->inLeftQueue->len, officerCount, flag);
                            //check if the right queue has cars
                            if(myBridge->inLeftQueue->len > 0 && myBridge->list.node1->len == 0 )
                            {                                
                                _car* queueCar = pop(myBridge->inLeftQueue);
                                queueCar->activeRunning = 1; 
                                queueCar->alive = 1;
                                officerCount++;
                                if (DEBUGGER) printf("Cars accesing the bridge,#cars: %d \n", officerCount);
                            }
                            else
                            {

                            }                    
                            usleep(250000);
                        } 
                        officerCount = 0;        
                        flag = 1;
                        //usleep(500000);                               
                }  

        } // END Else 
                    
    } //EndWhile
    //return 0;
    	
}

void* jungleLaw(void *pBridge){
	bridge* myBridge =  (bridge *) pBridge;
    int moveSide = 2; //indicate if the move is from the left or the right... 0 is from the left and 1 from the right
    printf("Jungle Law scheduler \n");
    while(1)
    {           
        //check if the bridge is empty
        if((myBridge->list.node1->len == 0 
        && myBridge->list.node2->len == 0 
        && myBridge->list.node3->len == 0 
        && myBridge->list.node4->len == 0 
        && myBridge->list.node5->len == 0) && moveSide ==2)
        {
            printf("bridge is empty %d\n", moveSide);
            if(myBridge->inLeftQueue->len > 0)
            {
                moveSide = 0;
            }
            else if(myBridge->inrightQueue->len > 0)
            {
                moveSide = 1;
            }else;
        }
        else if(moveSide) //right
        {
            printf("right queue len is: %d \n", myBridge->inrightQueue->len);
            if(myBridge->inrightQueue->len > 0 && myBridge->list.node5->len == 0){
                _car* queueCar = pop(myBridge->inLeftQueue);
                queueCar->activeRunning = 1; 
                queueCar->alive = 1;
                if (DEBUGGER) printf("Cars accesing the bridge from the right in jungle alg\n");
            }
        }
        else if(moveSide== 0) //left
        {
            printf("left queue len is: %d \n", myBridge->inLeftQueue->len);
            if(myBridge->inLeftQueue->len > 0 && myBridge->list.node5->len == 0){
                _car* queueCar = pop(myBridge->inLeftQueue);
                queueCar->activeRunning = 1; 
                queueCar->alive = 1;
                if (DEBUGGER) printf("Cars accesing the bridge from the left in jungle alg\n");
            } 
        }
        else;
        usleep(1000000);
    }
}

/**
 * @brief 
 * 
 * @param pCar 
 * @return void* 
 */
void* carMovement(void* pCar)
{
    while(1)
    {
        _car* myCar =  (_car *) pCar;
        bridge* myBridge;
        if(myCar->bridge == 0) myBridge = bridge1;
        else if(myCar->bridge == 1) myBridge = bridge2;
        else if(myCar->bridge == 2) myBridge = bridge3;
        if(myCar->activeRunning)
        {          
            while(myCar->activeRunning)
            {
                if(strcmp(myCar->side, "R") == 0){  //if moving from right side to left side               
                    //check if the bridge is empty
                    
                    if(myBridge->list.node5->len ==0 && myCar->bridgePos==0)
                    {
                        if(MY_PTHREAD) mymutex_lock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_lock(&lock);
                        myCar->bridgePos=1;
                        push(myBridge->list.node5, 0, myCar);
                        
                        if (DEBUGGER) printf("a car enter from the right with id %d model %s\n",myCar->id, myCar->model);
                        if(MY_PTHREAD) mymutex_unlock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_unlock(&lock);

                    }
                    
                        
                    else if(myBridge->list.node4->len ==0 
                    && myCar->bridgePos ==1)
                    {
                        if(MY_PTHREAD) mymutex_lock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_lock(&lock);
                        pop(myBridge->list.node5);
                        myCar->bridgePos=2;
                        push(myBridge->list.node4, 0, myCar);

                        if (DEBUGGER) printf("a car moving in the bridge from node5 to node4 with id %d model %s\n",
                                            myCar->id, myCar->model);
                        if(MY_PTHREAD) mymutex_unlock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_unlock(&lock);
                    }

                    else if(myBridge->list.node3->len ==0 
                    && myCar->bridgePos ==2)
                    {
                        if(MY_PTHREAD) mymutex_lock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_lock(&lock);
                        pop(myBridge->list.node4);
                        myCar->bridgePos=3;
                        push(myBridge->list.node3, 0, myCar);

                        if (DEBUGGER) printf("a car moving in the bridge from node4 to node3 with id %d model %s\n",
                                            myCar->id, myCar->model);
                        if(MY_PTHREAD) mymutex_unlock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_unlock(&lock);
                    }

                    else if(myBridge->list.node2->len ==0 
                    && myCar->bridgePos ==3)
                    {
                        if(MY_PTHREAD) mymutex_lock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_lock(&lock);
                        pop(myBridge->list.node3);
                        myCar->bridgePos=4;
                        push(myBridge->list.node2, 0, myCar);

                        if (DEBUGGER) printf("a car moving in the bridge from node3 to node2 with id %d model %s\n",
                                            myCar->id, myCar->model);
                        if(MY_PTHREAD) mymutex_unlock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_unlock(&lock);
                    }
                    else if(myBridge->list.node1->len ==0 
                    && myCar->bridgePos ==4)
                    {
                        if(MY_PTHREAD) mymutex_lock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_lock(&lock);
                        pop(myBridge->list.node2);
                        myCar->bridgePos=5;
                        push(myBridge->list.node1, 0, myCar);

                        if (DEBUGGER) printf("a car moving in the bridge from node2 to node1 with id %d model %s\n",
                                            myCar->id, myCar->model);
                        if(MY_PTHREAD) mymutex_unlock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_unlock(&lock);
                    }
                    else if(myCar->bridgePos ==5)
                    {
                        if(MY_PTHREAD) mymutex_lock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_lock(&lock);
                        pop(myBridge->list.node1);
                        myCar->bridgePos=0;
                        
                        myCar->activeRunning= 0;
                        myCar->alive = 0;
                        if (DEBUGGER) printf("the car moving outside the bridge from node1 with id %d model %s\n",
                                            myCar->id, myCar->model);
                        if(MY_PTHREAD) mymutex_unlock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_unlock(&lock);
                    }
                }

                if(strcmp(myCar->side, "L") == 0){  //if moving from right side to left side               
                        //check if the bridge is empty                        
                    if(myBridge->list.node1->len ==0 && myCar->bridgePos==0)
                    {
                        if(MY_PTHREAD) mymutex_lock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_lock(&lock);
                        myCar->bridgePos=1;
                        push(myBridge->list.node1, 0, myCar);

                        if (DEBUGGER) printf("a car enter from the left with id %d model %s\n",myCar->id, myCar->model);
                        if(MY_PTHREAD) mymutex_unlock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_unlock(&lock);
                    }
                    
                        
                    else if(myBridge->list.node2->len ==0 
                    && myCar->bridgePos ==1)
                    {
                        if(MY_PTHREAD) mymutex_lock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_lock(&lock);
                        pop(myBridge->list.node1);
                        myCar->bridgePos=2;
                        push(myBridge->list.node2, 0, myCar);

                        if (DEBUGGER) printf("a car moving in the bridge from node1 to node2 with id %d model %s\n"
                                            ,myCar->id, myCar->model);
                        if(MY_PTHREAD) mymutex_unlock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_unlock(&lock);
                    }

                    else if(myBridge->list.node3->len ==0 
                    && myCar->bridgePos ==2)
                    {
                        if(MY_PTHREAD) mymutex_lock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_lock(&lock);
                        pop(myBridge->list.node2);
                        myCar->bridgePos=3;
                        push(myBridge->list.node3, 0, myCar);

                        if (DEBUGGER) printf("a car moving in the bridge from node2 to node3 with id %d model %s\n",
                                            myCar->id, myCar->model);
                        if(MY_PTHREAD) mymutex_unlock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_unlock(&lock);
                    }

                    else if(myBridge->list.node4->len ==0 
                    && myCar->bridgePos ==3)
                    {
                        if(MY_PTHREAD) mymutex_lock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_lock(&lock);
                        pop(myBridge->list.node3);
                        myCar->bridgePos=4;
                        push(myBridge->list.node4, 0, myCar);

                        if (DEBUGGER) printf("a car moving in the bridge from node3 to node4 with id %d model %s\n",
                                        myCar->id, myCar->model);
                        if(MY_PTHREAD) mymutex_unlock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_unlock(&lock);
                    }
                    else if(myBridge->list.node5->len ==0 
                    && myCar->bridgePos ==4)
                    {
                        if(MY_PTHREAD) mymutex_lock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_lock(&lock);
                        pop(myBridge->list.node4);
                        myCar->bridgePos=5;
                        push(myBridge->list.node5, 0, myCar);

                        if (DEBUGGER) printf("a car moving in the bridge from node4 to node5 with id %d model %s\n",
                                        myCar->id, myCar->model);
                        
                        if(MY_PTHREAD) mymutex_unlock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_unlock(&lock);
                    }
                    else if(myCar->bridgePos ==5)
                    {
                        if(MY_PTHREAD) mymutex_lock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_lock(&lock);
                        pop(myBridge->list.node5);
                        myCar->bridgePos=0;
                        myCar->activeRunning= 0;
                        myCar->alive = 0;
                        if (DEBUGGER) printf("the car moving outside the bridge from node5 with id %d model %s\n",
                                        myCar->id, myCar->model);
                        if(MY_PTHREAD) mymutex_unlock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_unlock(&lock);
                    }
                }
                usleep(myCar->avgSpeed);
            }  
        }
        if(myCar->alive == 1) printf("im not moving with id %d model %s\n",myCar->id, myCar->model); 
        usleep(myCar->avgSpeed); 
    }                    
}