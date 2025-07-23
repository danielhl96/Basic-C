typedef struct Node{
	char* value;
	struct Node* next;
}Node;


typedef struct Headlist{
	Node* first;
	Node* last;
	int length;
}Headlist;

Node* pop_back_list(Headlist* list);

Node* createNode(char* value, Node* next);

Headlist* create_HeadList();

void clearList(Headlist* list);

void index_clear(Headlist* list, int index);

int length_of_list(Headlist* list);

int index_list(Headlist* list, char* string);

bool contains_s(Headlist* list, char* string);

bool isEmpty(Headlist* list);

int compare(Headlist* list1, Headlist* list2);

void printList(Headlist* list);

void append_front_list(Headlist* list, char* value);

void append_back_list(Headlist* list, char* value);

void index_set(Headlist* list, char* value, int index);

Headlist* reverse(Headlist* list);

Headlist* connect_list(Headlist* list1, Headlist* list2, int pos); 