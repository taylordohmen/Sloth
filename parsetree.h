
#define ID_SIZE 100
#define MAX_CHILDREN 3

struct Node {
	// type of this node
	int type;
	// value of this node
	double value;
	// id of this node if it is an identifier
	char id[ID_SIZE];

	int num_children;
	struct Node* children[MAX_CHILDREN];
};

struct Node* make_node(int type, double value, char* id);

void attach_node(struct Node* parent, struct Node* child);

void print_tree(struct Node* node, int tabs);
