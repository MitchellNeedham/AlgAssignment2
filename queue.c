// C program for array implementation of queue 
#include <stdio.h> 
#include <stdlib.h> 
#include <limits.h> 

struct Queue { 
    int front, rear, size; 
    unsigned capacity; 
    int* array; 
}; 

// creates empty queue and initialises values
struct Queue* createQueue(unsigned capacity) { 
    struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue)); 
    queue->capacity = capacity; 
    queue->front = queue->size = 0;  
    queue->rear = capacity - 1; 
    queue->array = (int*) malloc(queue->capacity * sizeof(int)); 
    return queue; 
} 

// determines if queue is full
int isFull(struct Queue* queue) {  
    return (queue->size == queue->capacity);  
} 
  
// determines if queue is empty
int isEmpty(struct Queue* queue) {  
    return (queue->size == 0); 
} 
  
// adds item to end of queue  
void enqueue(struct Queue* queue, int item) { 
    if (isFull(queue)) 
        return; 
    queue->rear = (queue->rear + 1)%queue->capacity; 
    queue->array[queue->rear] = item; 
    queue->size = queue->size + 1; 
} 

// adds item to start of queue
int dequeue(struct Queue* queue) { 
    if (isEmpty(queue)) 
        return INT_MIN; 
    int item = queue->array[queue->front]; 
    queue->front = (queue->front + 1)%queue->capacity; 
    queue->size = queue->size - 1; 
    return item; 
}

void freeQueue(struct Queue* queue) {
    while (!isEmpty(queue)) {
        dequeue(queue);
    }
    free(queue->array);
    free(queue);
}
  