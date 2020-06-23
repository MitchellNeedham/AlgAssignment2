struct Hashtable* createHashtable(int capacity);

struct Hashtable* doubleHashtable();

int addToHashtable(struct Hashtable* hashtable, char* string, int hashPos, int step);

int getHashPosition(struct Hashtable* hashtable, char *string);

void printHashtable(struct Hashtable* hashtable);

void freeHashtable(struct Hashtable* hashtable);