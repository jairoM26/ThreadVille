#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
#include "car.h"

#include "queue.c"
 
void list_with_ints();
void list_with_strings();
 
void free_string(void *data);
 
int main(int argc, char *argv[])
{

  node_t *head = NULL;
    int ret;

    enqueue(&head, 11);
    enqueue(&head, 22);
    enqueue(&head, 33);
    enqueue(&head, 44);

    print_list(head);
    
    while ((ret=dequeue(&head)) > 0) {
        printf("dequeued %d\n", ret);
    }
    printf("done. head=%p\n", head);

    return 0;




 /* printf("Loading int demo...\n");

  printf("Loading int demo...\n");


  list list;
  struct _car carSize;  
  list_new(&list, sizeof(carSize), NULL);        

  
  createCar(3, "lamborgini",0,'A','B',3,1.5,50.5,&list);
  
  list_head(&list,&carSize,NULL);

  char endPoint = (carSize.finalPosition);

  printf (" End Point: %c\n", (endPoint) );

*/
}
 



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
}