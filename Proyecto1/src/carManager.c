#include "../include/carManager.h"

static int type [9] = {1,3,3,3,3,1,2,2,3};
static char *models[] = {"Toyota","Izuzu","Ferrari", "Lamborgini", "Susuki", "Ford", "Mercedes", "Gio", "Mitsubishi"};
static char * colors[] = {"Red", "Yellow", "Blue"};
static int tmpTime = 2500000;

/**
 * @brief 
 * 
 * @return int 
 */
int genRandom(){    
    srand((unsigned) time(&t)); //setting the time t as the variable to initialize the root of srand 
    int tmp =  (rand()%8);
    return tmp;
}

/**
 * @brief Create a cars object
 * 
 * @param pQueue 
 * @return void* 
 */
void* create_cars(void *pQueue){    
    pthread_t thread;  
    myThread m_thread;  
    mythread_attr_t* attr = calloc(1,sizeof(mythread_attr_t));
    attr->SCHED_ALG=SCHEDULER;// 0:SSR		1:LOT 	2:RT
    attr->PRIO=1;
	attr->QUANTUM=1;
    heap_t* myQueue =  (heap_t *) pQueue; 
    _car* newCar;   
    int i = 0;  
    int ptime = tmpTime; 
    while(1){        
         
        newCar = (_car*)calloc(1,sizeof(_car));
        int rand = genRandom();
    
        if(i%2==0){
            createCar(newCar, colors[type[rand] -1], models[rand], type[rand],3,1.5,AVARAGE_SPEED+rand, myQueue->type);
        }
        else{
            createCar(newCar, colors[type[rand] -1], models[rand], type[rand],3,1.5,AVARAGE_SPEED-rand, myQueue->type);
        }

       // printf("Out Car\n");
        newCar->bridge = myQueue->bridge;        
        push(myQueue, type[rand], newCar);
        if(MY_PTHREAD){ 
            mythread_create(&m_thread, attr, carMovement, (void*)(newCar));
            mythread_join();
        }
        else if (MY_PTHREAD == 0) pthread_create(&thread, NULL, carMovement, (void*)(newCar));
        if (DEBUGGER) printf("Side bridge %s size %d, priority %d, modelo %s, ID %d\n", myQueue->type ,myQueue->len, type[rand], models[rand],newCar->id);
        usleep(ptime); //TO_DO increment the time of creating cars
        i++;
        ptime = ptime*pow(2.7182818, -DISTRIBUTION);
    }
}


