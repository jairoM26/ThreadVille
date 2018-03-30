/**
 * priority_queue.c
 * @details Simple structure data for a priority queue for car struct
 * 
 * @author Jairo Mendez Martinez <jairomendezmartinez@gmail.com>
 * @author David Monestel Aguilar <p.david06.p@gmail.com>
 * @date 28-03-2018
 * 
 * reference: https://rosettacode.org/wiki/Priority_queue#C
 * 
 * compilation command: gcc priority_queue.c -o pq
 * Execution: ./pq
 */

#include <stdio.h>
#include <stdlib.h>
#include "car.c"

/**
 * struct that represen the node of the priority queue
 */ 
typedef struct {
    int priority; //priority of the node
    _car data;    //data to be stored 
} pq_node_t;

/**
 * struct that simulates a heap of queue
 */
typedef struct {
    pq_node_t *nodes;  //space for nodes
    int len;        //size of the queue
    int size;       //
    char * type;
} heap_t;

/**
 * @brief insert element into the queue
 * @details depending on the priority of the element, it would be inserted
 *          at the begining, int the middle or at the end of the queue
 *          Normally it is stored at the end of the queue
 * @param h the queue where the element is gonna to be inserted
 * @param priority the priority of the data inserted
 * @param data data to be inserted
 */
void push (heap_t *h, int priority, _car data) {
    if (h->len + 1 >= h->size) {
        h->size = h->size ? h->size * 2 : 4;
        h->nodes = (pq_node_t *)realloc(h->nodes, h->size * sizeof (pq_node_t));
    }
    int i = h->len + 1;
    int j = i / 2;
    while (i > 1 && h->nodes[j].priority > priority) {
        h->nodes[i] = h->nodes[j];
        i = j;
        j = j / 2;
    }
    h->nodes[i].priority = priority;
    h->nodes[i].data = data;
    h->len++;
}

/**
 * @brief [brief description]
 * @details [long description]
 * 
 * @param h [description]
 * @return [description]
 */ 
_car pop (heap_t *h) {
    int i, j, k;
    _car car;
    if (!h->len) {
        return car;
    }
    _car data = h->nodes[1].data;
 
    h->nodes[1] = h->nodes[h->len];
    int priority = h->nodes[1].priority;
 
    h->len--;
 
    i = 1;
    while (1) {
        k = i;
        j = 2 * i;
        if (j <= h->len && h->nodes[j].priority < priority) {
            k = j;
        }
        if (j + 1 <= h->len && h->nodes[j + 1].priority < h->nodes[k].priority) {
            k = j + 1;
        }
        if (k == i) {
            break;
        }
        h->nodes[i] = h->nodes[k];
        i = k;
    }
    h->nodes[i] = h->nodes[h->len + 1];
    return data;
}
 
/** example of how to use it 
int main () {
    heap_t *h = (heap_t *)calloc(1, sizeof (heap_t));
    _car newCar;
    createCar(&newCar, 3, "lamborgini",0,'A','B',3,1.5,50.5);
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
}*/