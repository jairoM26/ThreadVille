#include "../include/carManager.h"

/**
 * @brief 
 * @details 
 * @return 
 */
int genRandom(){    
    srand((unsigned) time(&t)); //setting the time t as the variable to initialize the root of srand 
    int tmp =  (rand()%8);
    return tmp;
}

void* create_cars(void *pQueue){    
    pthread_t thread;
    int type [9] = {1,3,3,3,3,1,2,2,3};
    char *models[] = {"Toyota","Izuzu","Ferrari", "Lamborgini", "Susuki", "Ford", "Mercedes", "Gio", "Mitsubishi"};
    char * colors[] = {"Red", "Yellow", "Blue"};
    heap_t* myQueue =  (heap_t *) pQueue; 
    list list;
    list_new(&list, sizeof(_car), NULL);     
    int i = 0;  
    while(1){        
         
        _car* newCar = (_car*)calloc(1,sizeof(_car));
        int rand = genRandom();
    
        if(i%2==0){
            createCar(newCar, colors[type[rand] -1], models[rand], type[rand],3,1.5,AVARAGE_SPEED+rand, myQueue->type, &list);
        }
        else{
            createCar(newCar, colors[type[rand] -1], models[rand], type[rand],3,1.5,AVARAGE_SPEED-rand, myQueue->type, &list);
        }

       // printf("Out Car\n");
        newCar->bridge = myQueue->bridge;        
        push(myQueue, type[rand], newCar);
        pthread_create(&thread, NULL, carMovement, (void*)(newCar));
        if (DEBUGGER) printf("Side bridge %s size %d, priority %d, modelo %s, ID %d\n", myQueue->type ,myQueue->len, type[rand], models[rand],newCar->id);
        usleep(4005000); //TO_DO increment the time of creating cars
        i++;
    }
}

