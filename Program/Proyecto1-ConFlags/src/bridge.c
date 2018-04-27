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
    pBridge->bridgeString = (char*)calloc(16,sizeof(char));
    pBridge->list.stringInBridge = (char*)calloc(5,sizeof(char));
    pBridge->inLeftQueue->stringQ = (char*)calloc(4,sizeof(char));
    pBridge->inrightQueue->stringQ = (char*)calloc(4,sizeof(char));
    char* tmp = "nnnnn";
    strcpy(pBridge->list.stringInBridge, tmp);
    printf("bridge created with id: %d \n", pBridge->id);
    char* tmp2 = "nnnn";
    strcpy(pBridge->inLeftQueue->stringQ, tmp2);
    strcpy(pBridge->inrightQueue->stringQ, tmp2);
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
        {   int tmp;
            if(MY_PTHREAD) mymutex_lock(&myLock);
            else if (MY_PTHREAD == 0) pthread_mutex_lock(&lock);
            tmp = (myBridge->list.node1->len == 0 
            && myBridge->list.node2->len == 0 
            && myBridge->list.node3->len == 0 
            && myBridge->list.node4->len == 0 
            && myBridge->list.node5->len == 0);
            if(MY_PTHREAD) mymutex_unlock(&myLock);
            else if (MY_PTHREAD == 0) pthread_mutex_unlock(&lock);
            if(tmp ==1)
            {
                myBridge->list.stringInBridge[0] = 'n';
                myBridge->list.stringInBridge[1] = 'n';
                myBridge->list.stringInBridge[2] = 'n';
                myBridge->list.stringInBridge[3] = 'n';
                myBridge->list.stringInBridge[4] = 'n';
                if(flag)
                {
                    myBridge->side = flag;
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
                    //usleep(1000000); //work
                    usleep(500000);
                }
                else
                {
                    myBridge->side = flag;
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
                    //usleep(1000000); //work
                    usleep(500000);
                }
            }
            else
            {
            }
        }
        else
        {
            if(flag)
            {
                myBridge->side = flag;
                while(semCount < SEM_TIME_R*50)
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
                    //usleep(1000000); //work
                    usleep(500000);
                }
                semCount = 0;
                flag = 0;    
                myBridge->side = flag;            
                //usleep(1000000); //work
                usleep(500000);
            }            
            else
            {
                myBridge->side = flag;
                while(semCount < SEM_TIME_L*50)
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
                    //usleep(1000000); //work
                    usleep(500000);
                }
                semCount = 0;
                flag = 1; 
                myBridge->side = flag;                               
                //usleep(1000000); //work
                usleep(500000);
            }
        }    	                
    }
    //return 0;
}

void *officer(void *pBridge){
	bridge* myBridge =  (bridge *) pBridge;
	int flag =0;  //flag = 0 left officer 1 right officer
    int officerCount =0; //officer counter
    myBridge->side=flag;    
    while(1){
        if(officerCount==0)
        {
            int tmp;
            if(MY_PTHREAD) mymutex_lock(&myLock);
            else if (MY_PTHREAD == 0) pthread_mutex_lock(&lock);
            tmp = (myBridge->list.node1->len == 0 
            && myBridge->list.node2->len == 0 
            && myBridge->list.node3->len == 0 
            && myBridge->list.node4->len == 0 
            && myBridge->list.node5->len == 0);
            if(MY_PTHREAD) mymutex_unlock(&myLock);
            else if (MY_PTHREAD == 0) pthread_mutex_unlock(&lock);

            //check if the bridge is empty
            if(tmp == 1)
            {
                //write string for empty bridge
                myBridge->list.stringInBridge[0] = 'n';
                myBridge->list.stringInBridge[1] = 'n';
                myBridge->list.stringInBridge[2] = 'n';
                myBridge->list.stringInBridge[3] = 'n';
                myBridge->list.stringInBridge[4] = 'n';                                        
                if(flag)  //for right size            
                {            
                    myBridge->side = flag;    
                    if (DEBUGGER) printf("From officer right queue size is %d and officerCount is: %d and flag is: %d\n", 
                                            myBridge->inrightQueue->len, officerCount, flag);
                        //check if the right queue has cars
                    if(myBridge->inrightQueue->len > 0 && myBridge->list.node5->len == 0 )
                    {                   
                        //pop car     
                        _car* queueCar = pop(myBridge->inrightQueue);
                        queueCar->activeRunning = 1; 
                        queueCar->alive = 1;
                        officerCount++;    
                        if (DEBUGGER) printf("Cars accesing the bridge,#cars: %d \n", officerCount);                        
                    }                            
                    else;                        
                    usleep(500000);
                }
                
                else
                {   
                    myBridge->side = flag;
                    if (DEBUGGER) printf("From officer left queue size is %d and officerCount is: %d and flag is: %d\n", 
                                            myBridge->inLeftQueue->len, officerCount, flag);
                    //check if the right queue has cars
                    if(myBridge->inLeftQueue->len > 0 && myBridge->list.node1->len == 0 )
                    {
                        if (DEBUGGER) printf("Cars accesing the bridge,#cars: %d \n", officerCount);
                        //pop car
                        _car* queueCar = pop(myBridge->inLeftQueue);
                        queueCar->activeRunning = 1; 
                        queueCar->alive = 1;
                        officerCount++;
                        if (DEBUGGER) printf("Cars accesing the bridge,#cars: %d \n", officerCount);
                    }
                    else;                
                    usleep(500000);                       
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
                    myBridge->side = flag;
                    while(officerCount < RIGHT_OFFICER){
                        if (DEBUGGER) printf("From officer right queue size is %d and officerCount is: %d and flag is: %d\n", 
                                            myBridge->inrightQueue->len, officerCount, flag);
                        //check if the right queue has cars
                        if(myBridge->inrightQueue->len > 0 && myBridge->list.node5->len == 0 )
                        {             
                            //pop car               
                            _car* queueCar = pop(myBridge->inrightQueue);
                            queueCar->activeRunning = 1; //set car asi running in the bridge
                            queueCar->alive = 1; //car is alive
                            officerCount++;
                            if (DEBUGGER) printf("Cars accesing the bridge,#cars: %d \n", officerCount);
                        }
                        else
                        {
                            //Bridge is full or right queue empty                        
                        }                        
                        usleep(500000);

                    }
                    officerCount = 0;
                    flag = 0;
                    myBridge->side = flag;          
                    usleep(500000);                    
                }
                else //for left size
                { 
                    myBridge->side = flag;
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
                            usleep(500000);
                        } 
                        officerCount = 0;        
                        flag = 1;
                        myBridge->side = flag;
                        usleep(500000);                               
                }  

        } // END Else 
                    
    } //EndWhile
    //return 0;
    	
}
/**
 * 
 * 1 = Left to Right
 * 0 = Right to Left
*/
void* jungleLaw(void *pBridge){
	bridge* myBridge =  (bridge *) pBridge;
    int jungleProbability;
    int moveSide = 1; //indicate if the move is from the left or the right... 0 is from the left and 1 from the right 
    myBridge->side = moveSide;   
    printf("Jungle Law scheduler \n");
    while(1)
    {
        if (moveSide)
        {
            myBridge->side = moveSide;
            if (DEBUGGER) printf("Moving from LEFT to RIGHT \n");
                //check if the bridge is empty
            if(myBridge->list.node1->len == 0 
            && myBridge->list.node2->len == 0 
            && myBridge->list.node3->len == 0 
            && myBridge->list.node4->len == 0 
            && myBridge->list.node5->len == 0
            && myBridge->inLeftQueue->len == 0
            && myBridge->inrightQueue->len > 0
            ||
            myBridge->list.node1->len == 0 
            && myBridge->list.node2->len == 0 
            && myBridge->list.node3->len == 0 
            && myBridge->list.node4->len == 0 
            && myBridge->list.node5->len == 0
            && myBridge->inrightQueue->len > 0
            && jungleProbability%2!=0)
            {
                if(myBridge->inrightQueue->len > 0 && myBridge->list.node5->len == 0 )
                {                
                    printf ("entre\n");
                    moveSide=0; 
                    myBridge->side = moveSide;                                  
                    _car* queueCar = pop(myBridge->inrightQueue);
                    queueCar->activeRunning = 1; 
                    queueCar->alive = 1;
                    if (DEBUGGER) printf("New car entering accesing the bridge from Right to Left in jungle alg, right queue is %d \n",myBridge->inrightQueue->len);
                }
                else;
            }
            else
            {
                if(myBridge->inLeftQueue->len > 0 && myBridge->list.node1->len == 0 )
                {
                    printf ("entre ELSE\n");
                    _car* queueCar = pop(myBridge->inLeftQueue);
                    queueCar->activeRunning = 1; 
                    queueCar->alive = 1;
                    if (DEBUGGER) printf("New car entering accesing the bridge from Left to Right in jungle alg, left queue is %d \n",myBridge->inLeftQueue->len);
                }
                
            }
            usleep(1000000);
        }
        else
        {
            myBridge->side = moveSide;
            if (DEBUGGER) printf("Moving from RIGHT to LEFT \n");
                //check if the bridge is empty
            if(myBridge->list.node1->len == 0 
            && myBridge->list.node2->len == 0 
            && myBridge->list.node3->len == 0 
            && myBridge->list.node4->len == 0 
            && myBridge->list.node5->len == 0
            && myBridge->inLeftQueue->len > 0
            && myBridge->inrightQueue->len == 0 
            ||
            myBridge->list.node1->len == 0 
            && myBridge->list.node2->len == 0 
            && myBridge->list.node3->len == 0 
            && myBridge->list.node4->len == 0 
            && myBridge->list.node5->len == 0
            && myBridge->inLeftQueue->len > 0
            && jungleProbability%2==0)
            {
                if(myBridge->inLeftQueue->len > 0 && myBridge->list.node5->len == 0 )
                {                                
                    moveSide=1;     
                    myBridge->side = moveSide;                              
                    _car* queueCar = pop(myBridge->inLeftQueue);
                    queueCar->activeRunning = 1; 
                    queueCar->alive = 1;
                    if (DEBUGGER) printf("New car entering accesing the bridge from Left to Right in jungle alg, left queue is %d \n",myBridge->inLeftQueue->len); 
                }
                else;
            }
            else
            {
                if(myBridge->inrightQueue->len > 0 && myBridge->list.node1->len == 0 )
                {
                    _car* queueCar = pop(myBridge->inrightQueue);
                    queueCar->activeRunning = 1; 
                    queueCar->alive = 1;
                    if (DEBUGGER) printf("New car entering accesing the bridge from Right to Left in jungle alg, right queue is %d \n",myBridge->inrightQueue->len);
                }
                else;
            }
            usleep(1000000);
        }                       
        usleep(1000000);
        jungleProbability++;
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
                        if(myCar->priority == 1) myBridge->list.stringInBridge[4] = 'R';
                        else if(myCar->priority == 2) myBridge->list.stringInBridge[4] = 'A';
                        else if(myCar->priority == 3) myBridge->list.stringInBridge[4] = 'C';
                        
                        if (DEBUGGER) printf("a car enter from the right with id %d model %s priority %d and speed %lf \n",
                                        myCar->id, myCar->model, myCar->priority, myCar->avgSpeed);
                        
                        if(MY_PTHREAD) mymutex_unlock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_unlock(&lock);
                        usleep(myCar->avgSpeed);
                        myBridge->list.stringInBridge[4] = 'n';
                    }                                            
                    else if(myBridge->list.node4->len ==0 
                    && myCar->bridgePos ==1)
                    {
                        if(MY_PTHREAD) mymutex_lock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_lock(&lock);
                        pop(myBridge->list.node5);
                        myCar->bridgePos=2;
                        push(myBridge->list.node4, 0, myCar);

                        if(myCar->priority == 1) myBridge->list.stringInBridge[3] = 'R';
                        else if(myCar->priority == 2) myBridge->list.stringInBridge[3] = 'A';
                        else if(myCar->priority == 3) myBridge->list.stringInBridge[3] = 'C';

                        if (DEBUGGER) printf("a car moving in the bridge from node5 to node4with id %d model %s priority %d and speed %lf \n",
                                        myCar->id, myCar->model, myCar->priority, myCar->avgSpeed);

                        if(MY_PTHREAD) mymutex_unlock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_unlock(&lock);
                        usleep(myCar->avgSpeed);
                        myBridge->list.stringInBridge[3] = 'n';
                    }
                    else if(myBridge->list.node3->len ==0 
                    && myCar->bridgePos ==2)
                    {
                        if(MY_PTHREAD) mymutex_lock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_lock(&lock);
                        pop(myBridge->list.node4);
                        myCar->bridgePos=3;
                        push(myBridge->list.node3, 0, myCar);

                        if(myCar->priority == 1) myBridge->list.stringInBridge[2] = 'R';
                        else if(myCar->priority == 2) myBridge->list.stringInBridge[2] = 'A';
                        else if(myCar->priority == 3) myBridge->list.stringInBridge[2] = 'C';

                        if (DEBUGGER) printf("a car moving in the bridge from node4 to node3 with id %d model %s priority %d and speed %lf \n",
                                        myCar->id, myCar->model, myCar->priority, myCar->avgSpeed);
                        if(MY_PTHREAD) mymutex_unlock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_unlock(&lock);
                        usleep(myCar->avgSpeed);
                        myBridge->list.stringInBridge[2] = 'n';
                    }

                    else if(myBridge->list.node2->len ==0 
                    && myCar->bridgePos ==3)
                    {
                        if(MY_PTHREAD) mymutex_lock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_lock(&lock);
                        pop(myBridge->list.node3);
                        myCar->bridgePos=4;
                        push(myBridge->list.node2, 0, myCar);

                        if(myCar->priority == 1) myBridge->list.stringInBridge[1] = 'R';
                        else if(myCar->priority == 2) myBridge->list.stringInBridge[1] = 'A';
                        else if(myCar->priority == 3) myBridge->list.stringInBridge[1] = 'C';

                        if (DEBUGGER) printf("a car moving in the bridge from node3 to node2 with id %d model %s priority %d and speed %lf \n",
                                        myCar->id, myCar->model, myCar->priority, myCar->avgSpeed);
                        if(MY_PTHREAD) mymutex_unlock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_unlock(&lock);
                        usleep(myCar->avgSpeed);
                        myBridge->list.stringInBridge[1] = 'n';
                    }
                    else if(myBridge->list.node1->len ==0 
                    && myCar->bridgePos ==4)
                    {
                        if(MY_PTHREAD) mymutex_lock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_lock(&lock);
                        pop(myBridge->list.node2);
                        myCar->bridgePos=5;
                        push(myBridge->list.node1, 0, myCar);

                        if(myCar->priority == 1) myBridge->list.stringInBridge[0] = 'R';
                        else if(myCar->priority == 2) myBridge->list.stringInBridge[0] = 'A';
                        else if(myCar->priority == 3) myBridge->list.stringInBridge[0] = 'C';

                        if (DEBUGGER) printf("a car moving in the bridge from node2 to node1 with id %d model %s priority %d and speed %lf \n",
                                        myCar->id, myCar->model, myCar->priority, myCar->avgSpeed);
                        if(MY_PTHREAD) mymutex_unlock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_unlock(&lock);
                        usleep(myCar->avgSpeed);
                        myBridge->list.stringInBridge[0] = 'n';
                    }
                    else if(myCar->bridgePos ==5)
                    {
                        if(MY_PTHREAD) mymutex_lock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_lock(&lock);
                        pop(myBridge->list.node1);
                        myCar->bridgePos=0;
                        myCar->activeRunning= 0;
                        myCar->alive = 0;
                        if (DEBUGGER) printf("the car moving outside the bridge from node1 with id %d model %s priority %d and speed %lf \n",
                                        myCar->id, myCar->model, myCar->priority, myCar->avgSpeed);
                        if(MY_PTHREAD) mymutex_unlock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_unlock(&lock);
                        usleep(myCar->avgSpeed);
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

                        if(myCar->priority == 1) myBridge->list.stringInBridge[0] = 'r';
                        else if(myCar->priority == 2) myBridge->list.stringInBridge[0] = 'a';
                        else if(myCar->priority == 3) myBridge->list.stringInBridge[0] = 'c';

                        if (DEBUGGER) printf("a car enter from the left with id %d model %s priority %d and speed %lf \n",
                                        myCar->id, myCar->model, myCar->priority, myCar->avgSpeed);
                        if(MY_PTHREAD) mymutex_unlock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_unlock(&lock);
                        usleep(myCar->avgSpeed);
                        myBridge->list.stringInBridge[0] = 'n';
                    }
                    else if(myBridge->list.node2->len ==0 
                    && myCar->bridgePos ==1)
                    {
                        if(MY_PTHREAD) mymutex_lock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_lock(&lock);
                        pop(myBridge->list.node1);
                        myCar->bridgePos=2;
                        push(myBridge->list.node2, 0, myCar);

                        if(myCar->priority == 1) myBridge->list.stringInBridge[1] = 'r';
                        else if(myCar->priority == 2) myBridge->list.stringInBridge[1] = 'a';
                        else if(myCar->priority == 3) myBridge->list.stringInBridge[1] = 'c';

                        if (DEBUGGER) printf("a car moving in the bridge from node1 to node2 with id %d model %s priority %d and speed %lf \n",
                                        myCar->id, myCar->model, myCar->priority, myCar->avgSpeed);
                        if(MY_PTHREAD) mymutex_unlock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_unlock(&lock);
                        usleep(myCar->avgSpeed);
                        myBridge->list.stringInBridge[1] = 'n';
                    }

                    else if(myBridge->list.node3->len ==0 
                    && myCar->bridgePos ==2)
                    {
                        if(MY_PTHREAD) mymutex_lock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_lock(&lock);
                        pop(myBridge->list.node2);
                        myCar->bridgePos=3;
                        push(myBridge->list.node3, 0, myCar);

                        if(myCar->priority == 1) myBridge->list.stringInBridge[2] = 'r';
                        else if(myCar->priority == 2) myBridge->list.stringInBridge[2] = 'a';
                        else if(myCar->priority == 3) myBridge->list.stringInBridge[2] = 'c';

                        if (DEBUGGER) printf("a car moving in the bridge from node2 to node3 with id %d model %s priority %d and speed %lf \n",
                                        myCar->id, myCar->model, myCar->priority, myCar->avgSpeed);
                        if(MY_PTHREAD) mymutex_unlock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_unlock(&lock);
                        usleep(myCar->avgSpeed);
                        myBridge->list.stringInBridge[2] = 'n';
                    }

                    else if(myBridge->list.node4->len ==0 
                    && myCar->bridgePos ==3)
                    {
                        if(MY_PTHREAD) mymutex_lock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_lock(&lock);
                        pop(myBridge->list.node3);
                        myCar->bridgePos=4;
                        push(myBridge->list.node4, 0, myCar);

                        if(myCar->priority == 1) myBridge->list.stringInBridge[3] = 'r';
                        else if(myCar->priority == 2) myBridge->list.stringInBridge[3] = 'a';
                        else if(myCar->priority == 3) myBridge->list.stringInBridge[3] = 'c';

                        if (DEBUGGER) printf("a car moving in the bridge from node3 to node4 with id %d model %s priority %d and speed %lf \n",
                                        myCar->id, myCar->model, myCar->priority, myCar->avgSpeed);
                        if(MY_PTHREAD) mymutex_unlock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_unlock(&lock);
                        usleep(myCar->avgSpeed);
                        myBridge->list.stringInBridge[3] = 'n';
                    }
                    else if(myBridge->list.node5->len ==0 
                    && myCar->bridgePos ==4)
                    {
                        if(MY_PTHREAD) mymutex_lock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_lock(&lock);
                        pop(myBridge->list.node4);
                        myCar->bridgePos=5;
                        push(myBridge->list.node5, 0, myCar);

                        if(myCar->priority == 1) myBridge->list.stringInBridge[4] = 'r';
                        else if(myCar->priority == 2) myBridge->list.stringInBridge[4] = 'a';
                        else if(myCar->priority == 3) myBridge->list.stringInBridge[4] = 'c';

                        if (DEBUGGER) printf("a car moving in the bridge from node4 to node5 with id %d model %s priority %d and speed %lf \n",
                                        myCar->id, myCar->model, myCar->priority, myCar->avgSpeed);
                        
                        if(MY_PTHREAD) mymutex_unlock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_unlock(&lock);
                        usleep(myCar->avgSpeed);
                        myBridge->list.stringInBridge[4] = 'n';
                    }
                    else if(myCar->bridgePos ==5)
                    {
                        if(MY_PTHREAD) mymutex_lock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_lock(&lock);
                        pop(myBridge->list.node5);
                        myCar->bridgePos=0;
                        myCar->activeRunning= 0;
                        myCar->alive = 0;
                        if (DEBUGGER) printf("the car moving outside the bridge from node5 with id %d model %s priority %d and speed %lf \n",
                                        myCar->id, myCar->model, myCar->priority, myCar->avgSpeed);
                        if(MY_PTHREAD) mymutex_unlock(&myLock);
                        else if (MY_PTHREAD == 0) pthread_mutex_unlock(&lock);
                        usleep(myCar->avgSpeed);
                    }
                }                
            }  
        }
        if(myCar->alive == 1) printf("im not moving with id %d model %s\n",myCar->id, myCar->model); 
        usleep(myCar->avgSpeed); 
    }                    
}

void *bridgeChar(void* pBridge){
    bridge1->bridgeString[15] = ':';
    bridge2->bridgeString[15] = ':';
    bridge3->bridgeString[15] = ':';
    FILE* moveFile = fopen("moveFile.txt","w"); //open file
    if(moveFile == NULL){ //if the file can not be open
        fclose(moveFile); 
        exit(EXIT_FAILURE);
    }

    fclose(moveFile);

    char* tmp1;
    char*tmp2;
    char*tmp3;
    if(TRAFFIC_CONTROL_B1 == 0) tmp1 = "Semaphore";
    else if(TRAFFIC_CONTROL_B1 == 1) tmp1 = "oficer";
    else if(TRAFFIC_CONTROL_B1 == 2) tmp1 = "Jungle Law";
    if(TRAFFIC_CONTROL_B2 == 0) tmp2 = "Semaphore";
    else if(TRAFFIC_CONTROL_B2 == 1) tmp2 = "oficer";
    else if(TRAFFIC_CONTROL_B2 == 2) tmp2 = "Jungle Law";
    if(TRAFFIC_CONTROL_B3 == 0) tmp3 = "Semaphore";
    else if(TRAFFIC_CONTROL_B3 == 1) tmp3 = "oficer";
    else if(TRAFFIC_CONTROL_B3 == 2) tmp3 = "Jungle Law";
    while(1){
        FILE* moveFile = fopen("moveFile.txt","a+"); //open file
        FILE* dataFile = fopen("data.txt","w+"); //open file
        if(moveFile == NULL){ //if the file can not be open
            fclose(moveFile); 
            exit(EXIT_FAILURE);
        }
        if(dataFile == NULL){ //if the file can not be open
            fclose(dataFile); 
            exit(EXIT_FAILURE);
        }
        if(MY_PTHREAD) mymutex_lock(&myLock);
        else if (MY_PTHREAD == 0) pthread_mutex_lock(&lock);  
        updatePriorityString(bridge1->inLeftQueue);
        updatePriorityString(bridge1->inrightQueue);
        updatePriorityString(bridge2->inLeftQueue);
        updatePriorityString(bridge2->inrightQueue);
        updatePriorityString(bridge3->inLeftQueue);
        updatePriorityString(bridge3->inrightQueue);     
        printf("bridge1 with algorithm: %s with flag in: %d and bridge behavor: %s",tmp1, bridge1->side ,bridge1->inLeftQueue->stringQ);
        printf("%s", bridge1->list.stringInBridge);
        printf("%s\n",bridge1->inrightQueue->stringQ);
        fprintf(moveFile,"bridge1 with algorithm: %s with flag in: %d and bridge behavor: %s",tmp1, bridge1->side ,bridge1->inLeftQueue->stringQ);
        fprintf(moveFile,"%s", bridge1->list.stringInBridge);
        fprintf(moveFile,"%s\n",bridge1->inrightQueue->stringQ); 

        printf("bridge2 with algorithm: %s with flag in: %d and bridge behavor: %s",tmp2, bridge2->side ,bridge2->inLeftQueue->stringQ);
        printf("%s", bridge2->list.stringInBridge);
        printf("%s\n",bridge2->inrightQueue->stringQ);
        fprintf(moveFile,"bridge2 with algorithm: %s with flag in: %d and bridge behavor: %s",tmp2, bridge2->side ,bridge2->inLeftQueue->stringQ);
        fprintf(moveFile,"%s", bridge2->list.stringInBridge);
        fprintf(moveFile,"%s\n",bridge2->inrightQueue->stringQ); 

        printf("bridge3 with algorithm: %s with flag in: %d and bridge behavor: %s",tmp3, bridge3->side ,bridge3->inLeftQueue->stringQ);
        printf("%s", bridge3->list.stringInBridge);
        printf("%s\n",bridge3->inrightQueue->stringQ);
        fprintf(moveFile,"bridge3 with algorithm: %s with flag in: %d and bridge behavor: %s",tmp3, bridge3->side ,bridge3->inLeftQueue->stringQ);
        fprintf(moveFile,"%s", bridge3->list.stringInBridge);
        fprintf(moveFile,"%s\n",bridge3->inrightQueue->stringQ); 
        fprintf(moveFile,"---------------------------------------------------------------------------- \n");

        //0:006:nccccrrrnnnnncn:002:1#0:006:nnaaarrccccncnn:002:0#2:006:aaannnnnccnccnn:002:0
        char* tmp11;
        char* tmp12;
        char* tmp21;
        char* tmp22;
        char* tmp31;
        char* tmp32;
        if(bridge1->side){
            tmp11 = "0";
            tmp12 = "1";
        }else if(bridge1->side == 0){
            tmp11 = "1";
            tmp12 = "0";
        }
        if(bridge2->side){
            tmp21 = "0";
            tmp22 = "1";
        }else if(bridge2->side == 0){
            tmp21 = "1";
            tmp22 = "0";
        }
        if(bridge3->side){
            tmp31 = "0";
            tmp32 = "1";
        }else if(bridge3->side == 0){
            tmp31 = "1";
            tmp32 = "0";
        }
        fprintf(dataFile, "%d:%s%s%s%s%s#%d:%s%s%s%s%s#%d:%s%s%s%s%s# \n", 
                TRAFFIC_CONTROL_B1, bridge1->inLeftQueue->stringQ, tmp11, bridge1->list.stringInBridge, tmp12, bridge1->inrightQueue->stringQ,
                TRAFFIC_CONTROL_B2, bridge2->inLeftQueue->stringQ, tmp21, bridge2->list.stringInBridge, tmp22, bridge2->inrightQueue->stringQ,
                TRAFFIC_CONTROL_B3, bridge3->inLeftQueue->stringQ, tmp31, bridge3->list.stringInBridge, tmp32, bridge3->inrightQueue->stringQ);
        fclose(moveFile);
        fclose(dataFile);
        if(MY_PTHREAD) mymutex_unlock(&myLock);
        else if (MY_PTHREAD == 0) pthread_mutex_unlock(&lock);       
        usleep(600000);
    }
}