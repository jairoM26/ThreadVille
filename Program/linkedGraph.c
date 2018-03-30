// A C Program to demonstrate adjacency list 
// representation of graphs

#include <stdlib.h>
#include <stdio.h> 
#include <string.h>
#include "priority_queue.c"

#define CONFIG_FILE_NAME "initGraphCity.txt"
 
// A structure to represent an adjacency list node
struct AdjListNode
{
    int dest;
    struct AdjListNode* next;
    int roadWeight; 
};
 
// A structure to represent an adjacency list
struct AdjList
{
    struct AdjListNode *head; 
    char* _idName;
    heap_t * blockQueue;       //This is the queue variable for each node     
    
};
 
// A structure to represent a graph. A graph
// is an array of adjacency lists.
// Size of array will be V (number of vertices 
// in graph)
struct Graph
{
    int V;
    struct AdjList* array;
};
 
// A utility function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest, int pWeight)
{
    struct AdjListNode* newNode =
     (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    newNode->roadWeight = pWeight;
    return newNode;
}
 
// A utility function that creates a graph of V vertices
struct Graph* createGraph(int V)
{
    struct Graph* graph = 
        (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
 
    // Create an array of adjacency lists.  Size of 
    // array will be V
    graph->array = 
      (struct AdjList*) malloc(V * sizeof(struct AdjList));
 
    // Initialize each adjacency list as empty by 
    // making head as NULL
    int i;
    for (i = 0; i < V; ++i){
        if(i <2)
        {
            graph->array[i].head = NULL;
            graph->array[i]._idName = "A1-6";

        }
        else{
            graph->array[i].head = NULL;
            graph->array[i]._idName = "A1-2";
        }
    }
    return graph;
}

// A utility function that creates a graph of vertices V= for ThreadVille.
struct Graph* initThreadVilleGraph( )
{
    int V = 6;
    struct Graph* graph = 
        (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;
 
    // Create an array of adjacency lists.  Size of 
    // array will be V
    graph->array = 
      (struct AdjList*) malloc(V * sizeof(struct AdjList));
 
    // Initialize each adjacency list as empty by 
    // making head as NULL
    int i;
    FILE * fp;    
    fp = fopen(CONFIG_FILE_NAME, "r");
    if (fp == NULL){
        fclose(fp); 
        exit(EXIT_FAILURE);
    }

    
    char key[256], value[256];
    int iVal;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    char arrayNames[V][10];
           
    for (i = 0; i < V; ++i)
    {
        (read = getline(&line, &len, fp));
        if(line[0] == '#' ) //|| line[0] == '\n'
        {
            i--;
            continue;
        }
            
        else
        {            
            char* nodeID;
            sscanf(line, "%s = %s", key, value);                      
            strcpy(arrayNames[i], key);
        }               
    }    

    for (i=0;i<V;i++)
    {
        graph->array[i].head = NULL;        
        graph->array[i]._idName= arrayNames[i];        
    }    
    fclose(fp);             
    return graph;
}
 
// Adds an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest,int pWeight)
{
    // Add an edge from src to dest.  A new node is 
    // added to the adjacency list of src.  The node
    // is added at the begining
    struct AdjListNode* newNode = newAdjListNode(dest,pWeight);    

    newNode->next = graph->array[src].head;            
    graph->array[src].head = newNode;
 
    // Since graph is undirected, add an edge from
    // dest to src also
   /* newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;*/
}

struct AdjList findVortex(char* pId_Name , struct Graph* pGraph)
{
    int i;
    
    
    for (i=0;i< pGraph->V; i++)
    {
        struct AdjList pCrawl = pGraph->array[i];

        if(strcmp(pCrawl._idName, pId_Name) == 0)
        {
            return (pCrawl); 
        }                            
            
    }
}
 
// A utility function to print the adjacency list 
// representation of graph
void printGraph(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->V; ++v)
    {
        struct AdjListNode* pCrawl = graph->array[v].head;
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (pCrawl)
        {
            printf("-> %d", pCrawl->dest);
            printf(" with weight of: %i", pCrawl->roadWeight);
        
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}
 
/* Function to print the adjacency list of graph*/
/*void displayGraph(graph_p graph)
{
    int i;
    for (i = 0; i < graph->num_vertices; i++)
    {
        adjlist_node_p adjListPtr = graph->adjListArr[i].head;
        printf("\n%d: ", i);
        while (adjListPtr)
        {
            printf("%d->", adjListPtr->vertex);
            adjListPtr = adjListPtr->next;
        }
        printf("NULL\n");
    }
}*/