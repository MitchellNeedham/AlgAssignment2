typedef struct dag Dag;

struct dag {
    int ID;
    int parents;
    int children;
    Dag *child[];
};

Dag *create_node(int ID);

void add_child(Dag *node, Dag *child);

int complete_path(Dag *node, int pos, int total);

void free_dag_node(Dag *node);



