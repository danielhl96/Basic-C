#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "List.h"

Node* createNode(char* value, Node* next){
	int length = strlen(value);
	Node* new = malloc(sizeof(Node));
	new->next = next;
	new->value = malloc(sizeof(char)*length);
	strcpy(new->value,value);
	return new;	
}
Headlist* create_HeadList(){
	Headlist* newList = calloc(1,sizeof(Headlist));
	newList->length = 0;
	return newList;
}

int length_of_list(Headlist* list){
	return list->length;
}

void clearList(Headlist* list){
	Node* list1 = list->first;
	Node* next = NULL;
	for(; list1 !=NULL; list1 = next){
		next = list1->next;
		free(list1->value);
		free(list1);
		list->length -=1;
	}
	free(list);
	list = NULL;
    
}

void index_clear(Headlist* list, int index){
	
	if(list==NULL) return;
	Node* node = NULL;
	
	if(index == 0){
		node = list->first->next;
		free(list->first->value);
		free(list->first);
		list->first = node;
		list->length -=1;
	}
	
	Node* node1 = NULL;
	node = list->first;
	if(index == length_of_list(list)-1){
		for(int i = 0; node != NULL; node = node->next,i++){
			if(i == index-1){
				node1 = node;
				free(node->next->value);
				free(node->next);
				list->last = node1;
				list->last->next = NULL;
				list->length -=1;
				break;
			}
		}
	}
	else{
		for(int i = 0; node != NULL; node = node->next,i++){
			if(i == index-1){
				node1 = node->next->next;
				free(node->next->value);
				free(node->next);
				node->next = node1;
				list->length -=1;
			}
		}
	}
}

void index_set(Headlist* list, char* value, int index){
	if(index == 0){
		append_front_list(list,value);
		return;
	}
	
	if(index == length_of_list(list)){
		append_back_list(list,value);
		return;
	}
	
	Node* node1 = createNode(value,NULL);
	Node* node2 = NULL;
	Node* node = list->first;
	
	for(int i = 0; node != NULL; node = node->next,i++){
		if(i == index-1){
			node2 = node->next;
			node->next= node1;
			node1->next= node2;
			list->length += 1;
			}
		}
	}

void clear_contains_elem(Headlist* list, char* string){
	index_clear(list,index_list(list,string));
}


bool isEmpty(Headlist* list){
	if(!length_of_list(list))return true;
	return false;
}

int index_list(Headlist* list, char* string){
	int index = 0;
	for (Node *node = list->first; node != NULL; node = node->next) {
		if(strcmp(node->value,string)==0) return index;
	index++;
	}
	return -1;
}

bool contains_s(Headlist* list, char* string){
	if(index_list(list,string)==-1) return false;
	return true;
}

void printList(Headlist* list){
	printf("[");
	for (Node *node = list->first; node != NULL; node = node->next) {
        printf("%s ", node->value);
    }
	printf("] Length of list: %d\n",length_of_list(list));
}

void append_front_list(Headlist* list, char* value){
	list->first = createNode(value,list->first);
	list->length +=1;
}


void append_back_list(Headlist* list, char* value){
	Node* n = createNode(value,NULL);
	if(list->first == NULL){ // empty list, first and last change
		list->first = n;
		list->last = n;
		list->length += 1;
	} 
	else { // non-empty list, only last changes
		list->last->next = n;
		list->last = n;
		list->length += 1;
	}
}

Node* pop_back_list(Headlist* list){
	
	Node* n = createNode(list->last->value,NULL);
	index_clear(list, list->length-1);
	return n;
}
	

Headlist* reverse(Headlist* list){
	Headlist* List = create_HeadList();
	for (Node *node = list->first; node != NULL; node = node->next) {
        append_front_list(List,node->value);
    }
	return List;
}

Headlist* connect_list(Headlist* list1, Headlist* list2, int pos){
	Headlist* listnew = create_HeadList();
	
	if(pos == 1){
		for (Node *node = list1->first; node != NULL; node = node->next){
			append_back_list(listnew,node->value);
	}
		for (Node *node = list2->first; node != NULL; node = node->next){
			append_back_list(listnew, node->value);
		}
	}
	
	if(pos == 0){
		for (Node *node = list2->first; node != NULL; node = node->next){
		append_back_list(listnew, node->value);
	}
		for (Node *node = list1->first; node != NULL; node = node->next){
		append_back_list(listnew, node->value);
		}
	}
	
	return listnew;
	
}

int compare(Headlist* list1, Headlist* list2){
	if(list1->length == list2->length){
		Node* node2 = list2->first;
		for(Node* node = list1->first; node != NULL; node = node->next,node2 = node2->next){
			if(strcmp(node->value,node2->value)) return 0;
		}
		return 1;
	}
	printf("Listen sind nicht gleich lang!\n");
	return 0;
	
}
int main(void) {
	Node* a = createNode("",NULL);
	Headlist* list1 = create_HeadList();
	append_back_list(list1,"Hallo");
	append_back_list(list1,"Welt");
	append_back_list(list1,"Deutschland");
	printList(list1);
	//a = pop_back_list(list1);
	append_front_list(list1,"TEST");
	index_clear(list1,3);
	printList(list1);
	Headlist* list2 = reverse(list1);
	printList(list2);
	int index = index_list(list2,"Welt");
	printf("Index: %d",index);
	return 0;
}