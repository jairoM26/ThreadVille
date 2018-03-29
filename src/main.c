/**
 * main.c
 * @details program main
 * 
 * @author Jairo Mendez Martinez <jairomendezmartinez@gmail.com>
 * @author David Monestel Aguilar <p.david06.p@gmail.com>
 * @date 29-03-2018
 * 
 * compilation command: gcc main.c -o main
 * Execution: ./main
 */

#include <pthread.h>
#include <stdio.h>
#include "priority_queue.c"
#define NUM_THREADS 5
/**
void *runner(void *param);

int main(int argc, char *argv[])
{
    int i, policy;
    pthread_t tid[NUM_THREADS];
    pthread_attr_t attr;

    pthread_attr_init(&attr);

    if(pthread_attr_getschedpolicy(&attr, &policy) != 0)
        fprintf(stderr, "Unable to get policy.\n");
    else{
        if(policy == SCHED_OTHER)
            printf("SCHED_OTHER\n");
        else if(policy == SCHED_RR)
            printf("SCHED_RR\n");
        else if(policy == SCHED_FIFO)
            printf("SCHED_FIFO\n");
    }

    if(pthread_attr_setschedpolicy(&attr, SCHED_FIFO) != 0)
        fprintf(stderr, "Unable to set policy.\n");
    // create the threads 
    for(i = 0; i < NUM_THREADS; i++)
        pthread_create(&tid[i], &attr, runner, NULL);
    //now join on each thread 
    for(i = 0; i < NUM_THREADS; i++)
        pthread_join(tid[i], NULL);

    if(pthread_attr_getschedpolicy(&attr, &policy) != 0)
        fprintf(stderr, "Unable to get policy.\n");
    else{
        if(policy == SCHED_OTHER)
            printf("SCHED_OTHER\n");
        else if(policy == SCHED_RR)
            printf("SCHED_RR\n");
        else if(policy == SCHED_FIFO)
            printf("SCHED_FIFO\n");
    }
}*/

// Each thread will begin control in this function 
/*void *runner(void *param)
{
     do some work... 

    pthread_exit(0);
}*/

int main () {
    heap_t *h = (heap_t *)calloc(1, sizeof (heap_t));
    _car newCar;
    createCar(&newCar, 3, "ferrari",0,'A','B',3,1.5,50.5);
    push(h, 3, newCar);
    createCar(&newCar, 3, "hyunday",0,'A','B',3,1.5,50.5);
    push(h, 1, newCar);
    createCar(&newCar, 3, "toyota",0,'A','B',3,1.5,50.5);
    push(h, 4, newCar);
    createCar(&newCar, 3, "honda",0,'A','B',3,1.5,50.5);
    push(h, 3, newCar);
    createCar(&newCar, 3, "Izuzu",0,'A','B',3,1.5,50.5);
    push(h, 2, newCar);
    for (int i = (*h).len; i >0 ; i--) {
        printf("%s\n", pop(h).model);
    }
    return 0;
}