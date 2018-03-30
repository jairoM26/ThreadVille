
#include <string.h>
 
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/*
#include "car.h"
//#include "queue.c"*/
 
//void list_with_ints();
//void list_with_strings();
 
//void free_string(void *data);
/* #define NUM_THREADS 4

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
  }*/

  /* block until all threads complete */
  
  /*for (j = 0; j < NUM_THREADS; ++j) {
    pthread_join(thread[j], NULL);
  }  */

 /* while(1);

  return 0;
*/

 


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






/*
 * =====================================================================================
 *
 *       Filename:  graph.c
 *
 *    Description:  Main program to run Adjacency_Matrix application
 *
 *        Version:  1.0
 *        Created:  17/04/2013 10:34:33
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Vitor Freitas (vfs), vitorfs@gmail.com
 *        Company:  Universidade Federal de Juiz de Fora (UFJF)
 *
 * =====================================================================================
 */

#include "linkedGraph.c"


// Driver program to test above functions
int main()
{
    // create the graph given in above fugure
    /*int V = 5;
    struct Graph* graph = createGraph(V);
    addEdge(graph, 0, 1,5);
    addEdge(graph, 0, 4,5);
    addEdge(graph, 1, 2,2);
    addEdge(graph, 1, 3,2);
    addEdge(graph, 1, 4,1);
    addEdge(graph, 2, 3,8);
    addEdge(graph, 3, 4,9);*/

    printf("hola\n");

    struct Graph* graph = initThreadVilleGraph();

    struct AdjList nodo = findVortex("A3-4",graph);    
    char* name = nodo._idName;
    printf ("NODO: %s\n", (char*)name);


    
    // print the adjacency list representation of the above graph
    /*printGraph(graph);*/
 
    return 0;
}
