
#include <string.h>
 
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "car.h"
//#include "queue.c"
 
//void list_with_ints();
//void list_with_strings();
 
//void free_string(void *data);
 #define NUM_THREADS 4

int main(int argc, char *argv[])
{
  list list;
  struct _car newCar;  
  list_new(&list, sizeof(newCar), NULL);        

  
  createCar(3, "lamborgini",0,'A','B',3,1.5,50.5,&list);
  createCar(3, "lamborgini",0,'A','B',3,1.5,50.5,&list);
  createCar(3, "lamborgini",0,'A','B',3,1.5,50.5,&list);
  
  list_head(&list,&newCar,NULL);

  int endPoint = (newCar.id);

  printf (" End Point: %i\n", (endPoint) );

  pthread_t thread [NUM_THREADS];

  int i;
  int j;
  for (i = 0; i<4;i++)
  {
    
    struct _car newCar2;

    createCar(3, "lamborgini",0,'A','B',3,1.5,50.5,&list);
  
    list_tail(&list,&newCar2);    

    int carID = (newCar2.id);

    printf (" Car ID: %i\n", (carID) );

    pthread_create( &thread[i], NULL, carManager, (void*)& newCar2);
    usleep(1000);
  }

  /* block until all threads complete */
  
  /*for (j = 0; j < NUM_THREADS; ++j) {
    pthread_join(thread[j], NULL);
  }  */

  while(1);

  return 0;


 


/*
void list_with_strings()
{
  int numNames = 5;
  const char *names[] = { "David", "Kevin", "Michael", "Craig", "Jimi" };
 
  int i;
  list list;
  list_new(&list, sizeof(char *), free_string);
 
  char *name;
  for(i = 0; i < numNames; i++) {
    name = strdup(names[i]);
    list_append(&list, &name);
  }
  char* elemento;
  list_head(&list,elemento,NULL);

  printf (" name: %s\n", *(char **)elemento );
 
 
}

 
void free_string(void *data)
{
  free(*(char **)data);
}*/