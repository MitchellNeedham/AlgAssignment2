struct LLNode { 
    struct LLNode *next;
    struct LLNode *prev;
    char* string; 
    int length;
    int data;
};

struct LLNode* initLinkedList(int length);

struct LLNode* newNode(struct LLNode *prev);

struct LLNode* addString(struct LLNode* node, char *s);

struct LLNode* addFreqData(struct LLNode* node, char *s, int data);

struct LLNode* sortList(struct LLNode* node);

void freeLinkedList(struct LLNode* node);
