
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
 
int main(int argc, char *argv[])
{

  
  //pthread_t thread2;

  list list;
  struct _car newCar;  
  list_new(&list, sizeof(newCar), NULL);        

  
  createCar(3, "lamborgini",0,'A','B',3,1.5,50.5,&list);
  
  list_head(&list,&newCar,NULL);

  char endPoint = (newCar.finalPosition);

  printf (" End Point: %c\n", (endPoint) );



  //pthread_create( &thread1, NULL, carManager, (void*)& newCar);

  for (int i = 0; i<3;i++)
  {
    pthread_t thread1;
    struct _car newCar2;

    createCar(3, "lamborgini",0,'A','B',3,1.5,50.5,&list);
  
    list_head(&list,&newCar2,NULL);

    char endPoint = (newCar2.finalPosition);

    pthread_create( &thread1, NULL, carManager, (void*)& newCar2);
  }  

  while(1);

 /* printf("Loading int demo...\n");

  list list;
  struct _car carSize;  
  list_new(&list, sizeof(carSize), NULL);        

  
  createCar(3, "lamborgini",0,'A','B',3,1.5,50.5,&list);
  
  list_head(&list,&carSize,NULL);

  char endPoint = (carSize.finalPosition);

  printf (" End Point: %c\n", (endPoint) );
*/
}
 


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