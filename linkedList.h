typedef struct node Node;
typedef struct linkedList LinkedList;

struct node {
	void* data;
	Node* next;
};

struct linkedList {
	Node* head;
	Node* tail;
	int count;
};

//--------------------Signatures-----------------

LinkedList createList(void);
Node* create_node(void*);
int add_to_list(LinkedList*,Node*);
void* get_first_element(LinkedList);
void* get_last_element(LinkedList);
void printList(LinkedList);
void traverse(LinkedList,void(*)(void*));
void* getElementAt(LinkedList,int);
int indexOf(LinkedList,void*);
void* deleteElementAt(LinkedList*,int);
int asArray(LinkedList,void**);
LinkedList* filter(LinkedList,int(*)(void*));