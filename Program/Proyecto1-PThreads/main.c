#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "./include/carManager.h"
#include "readConfigFile.c"

int BRIDGE_SIZE = 0, SCHEDULER = 0, AVARAGE_SPEED = 0, DEBUGGER = 0,  RIGHT_OFFICER = 0, LEFT_OFFICER = 0, 
    TRAFFIC_CONTROL_B1 = 0, TRAFFIC_CONTROL_B2 = 0, TRAFFIC_CONTROL_B3 = 0, SEM_TIME_L = 0, SEM_TIME_R = 0, 
    A_P = 0, R_P = 0, MY_PTHREAD = 0, BRIDGE_TO_PRINT = 0, HARDWARE_AVAILABLE = 0;
double DISTRIBUTION = 0.0;
extern bridge* bridge1;

void initConfig(){
  info* pconf = (info*)calloc(1, sizeof(info));
  readConfigFile(pconf); //reading the config file
  BRIDGE_SIZE = pconf->bridgeSize;
  SCHEDULER = pconf->scheduler;
  AVARAGE_SPEED = pconf->avgSpeed;
  DEBUGGER = pconf->debbuger;
  DISTRIBUTION = pconf->distribution;
  RIGHT_OFFICER = pconf->right_officer;
  LEFT_OFFICER = pconf->leftt_officer;
  TRAFFIC_CONTROL_B1 = pconf->traffic_control_B1;
  TRAFFIC_CONTROL_B2 = pconf->traffic_control_B2;
  TRAFFIC_CONTROL_B3 = pconf->traffic_control_B3;
  SEM_TIME_L = pconf->sem_time_L;
  SEM_TIME_R = pconf->sem_time_R;
  A_P = pconf->ambulance_percentage;
  R_P = pconf->radioactive_percentage;
  MY_PTHREAD = pconf->myThread;
  BRIDGE_TO_PRINT = pconf->bridge_to_print;
  HARDWARE_AVAILABLE = pconf->hardware_available;
  if (DEBUGGER) printf( "bridgeSize: %d  scheduler: %d  avgSpeed: %d debbuger: %d distribution %lf \n traffic_control_B1: %d traffic_control_B2: %d traffic_control_B3: %d \n right_officer: %d leftt_officer: %d sem_time_L: %d sem_time_R: %d \n ambulance percentage: %d radioactive_percentage: %d \n my_thread %d \n",BRIDGE_SIZE, SCHEDULER, AVARAGE_SPEED, DEBUGGER, DISTRIBUTION,  TRAFFIC_CONTROL_B1, TRAFFIC_CONTROL_B2, TRAFFIC_CONTROL_B3, RIGHT_OFFICER, LEFT_OFFICER, SEM_TIME_L, SEM_TIME_R, A_P, R_P, MY_PTHREAD);      
}

int main(){       

    initConfig(); //get config info

    //init bridges
    bridge1 = (bridge*)calloc(1, sizeof(bridge));
    bridge2 = (bridge*)calloc(1, sizeof(bridge));
    bridge3 = (bridge*)calloc(1, sizeof(bridge));
    initBridge(bridge1, BRIDGE_SIZE);
    initBridge(bridge2, BRIDGE_SIZE);
    initBridge(bridge3, BRIDGE_SIZE);
    int valid[7];
    
    pthread_t thread [7];              


    //method to 
    valid[0] = pthread_create(&thread[0], NULL, create_cars, (void *)(bridge1));     
    valid[1] = pthread_create(&thread[1], NULL, create_cars, (void *)(bridge2));      
    valid[2] = pthread_create(&thread[2], NULL, create_cars, (void *)(bridge3));
    

    if(TRAFFIC_CONTROL_B1 == 0)valid[3] = pthread_create(&thread[3], NULL, semaphoreAlg, (void *)(bridge1));
    else if(TRAFFIC_CONTROL_B1 == 1)valid[3] = pthread_create(&thread[3], NULL, officer, (void *)(bridge1));
    else if(TRAFFIC_CONTROL_B1 == 2)valid[3] = pthread_create(&thread[3], NULL, jungleLaw, (void *)(bridge1));
    
    if(TRAFFIC_CONTROL_B2 == 0)valid[4] = pthread_create(&thread[4], NULL, semaphoreAlg, (void *)(bridge2));
    else if(TRAFFIC_CONTROL_B2 == 1)valid[4] = pthread_create(&thread[4], NULL, officer, (void *)(bridge2));
    else if(TRAFFIC_CONTROL_B2 == 2)valid[4] = pthread_create(&thread[4], NULL, jungleLaw, (void *)(bridge2));

    if(TRAFFIC_CONTROL_B3 == 0)valid[5] = pthread_create(&thread[5], NULL, semaphoreAlg, (void *)(bridge3));
    else if(TRAFFIC_CONTROL_B3 == 1)valid[5] = pthread_create(&thread[5], NULL, officer, (void *)(bridge3));
    else if(TRAFFIC_CONTROL_B3 == 2)valid[5] = pthread_create(&thread[5], NULL, jungleLaw, (void *)(bridge3));
    
    valid[9] = pthread_create(&thread[6], NULL, bridgeChar, (void *)NULL);      
    

  //if any error in creating threads
    if (valid[0]){
      printf("ERROR; return code from pthread_create() 0 is %d\n", valid[0]);     
      exit(-1);
    }
    if (valid[1]){
      printf("ERROR; return code from pthread_create() 1 is %d\n", valid[1]);     
      exit(-1);
    }
    if (valid[2]){
      printf("ERROR; return code from pthread_create() 2 is %d\n", valid[3]);     
      exit(-1);
    }
    if (valid[4]){
      printf("ERROR; return code from pthread_create() 4 is %d\n", valid[4]);     
      exit(-1);
    }
    
    if (valid[5]){
      printf("ERROR; return code from pthread_create() 5 is %d\n", valid[5]);     
      exit(-1);
    }
    if (valid[6]){
      printf("ERROR; return code from pthread_create() 6 is %d\n", valid[6]);     
      exit(-1);
    }
    pthread_exit(NULL);
    return 0;
}