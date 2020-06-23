struct TrieNode *getNode();

void insert(struct TrieNode *root, char *key);

void printTrie(struct TrieNode *node);

int getFrequency(struct TrieNode *node, char *key);

int getExactFrequency(struct TrieNode *node, char *key);

struct LLNode *searchPrefixes(struct TrieNode *node, struct LLNode *lnode, int length, int count, char *prefix);

void freeTrie(struct TrieNode *node);