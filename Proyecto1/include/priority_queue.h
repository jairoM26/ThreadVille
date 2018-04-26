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

#ifndef __PRIORITY_QUEUE_H
#define __PRIORITY_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * struct that represent the node of the priority queue
 */ 
typedef struct pq_node{
    int priority; //priority of the node
    void* data;    //data to be stored 
} pq_node_t;

/**
 * struct that simulates a heap of queue
 */
typedef struct pq {
    pq_node_t *nodes;  //space for nodes
    int len;        //size of the queue
    int size;       //
    char * type;
    int bridge;
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
void push (heap_t *h, int priority, void* data);

/**
 * @brief 
 * 
 * @param h 
 * @param pdata 
 */
void* pop (heap_t *h);

#endif