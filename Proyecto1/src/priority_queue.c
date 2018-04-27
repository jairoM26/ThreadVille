#include "../include/priority_queue.h"

void push (heap_t *h, int priority, void* data) {
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

void* pop (heap_t *h) {
    int i, j, k;
    if (!h->len) {
        return NULL;
    }
    void *pdata = h->nodes[1].data;
    
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
    return pdata;
}

void updatePriorityString(heap_t *h){
    char* tmp = (char*)calloc(4, sizeof(char));
    for(int i = 0; i < 4; i++)
        tmp[i] = 'n';    
    if(strcmp(h->type, "R")==0){
        for(int i = 1; i <= h->len; i++){
            if(i<=4){
                if(h->nodes[i].priority == 1) tmp[i-1] = 'R';
                else if(h->nodes[i].priority == 2) tmp[i-1] = 'A';
                else if(h->nodes[i].priority == 3) tmp[i-1] = 'C';
            }        
        }
    }
    else{
        for(int i = 1; i <= h->len; i++){
            if(i<=4){
                if(h->nodes[i].priority == 1) tmp[i-1] = 'r';
                else if(h->nodes[i].priority == 2) tmp[i-1] = 'a';
                else if(h->nodes[i].priority == 3) tmp[i-1] = 'c';
            }        
        }
    }
    char tmp2;
    if(strcmp(h->type, "L")==0){
        tmp2 = tmp[0];
        tmp[0] = tmp[3];
        tmp[3] = tmp2;
        tmp2 = tmp[1];
        tmp[1] = tmp[2];
        tmp[2] = tmp2;
    }
    strcpy(h->stringQ, tmp);
    free(tmp);
    //printf("tmp %s \n",h->stringQ);
}