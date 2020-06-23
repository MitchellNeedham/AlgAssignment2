struct Queue* createQueue(unsigned capacity);
  
int isFull(struct Queue* queue);
  
int isEmpty(struct Queue* queue);
  
void enqueue(struct Queue* queue, int item);
  
int dequeue(struct Queue* queue);

void freeQueue(struct Queue* queue);
  