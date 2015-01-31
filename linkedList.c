#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

void printList(LinkedList list){
	int i=0;
	Node* walker = list.head;
	printf("List-of-%d\n",list.count);
	printf("head=%p\n",list.head);
	printf("tail=%p\n",list.tail);
	while(walker != 0){
		printf("Node-%d Data-%d Address-%p\n",++i,*(int*)walker->data,walker );
		walker = walker->next;
	}
}

LinkedList createList(void){
	LinkedList list = {0,0,0};
	return list; 
}

Node* create_node(void* data){
	Node* n = calloc(1,sizeof(Node));
	n->data = data;
	return n;
}

int add_to_list(LinkedList* list, Node* node){
	if(!node || !list)
		return 0;
	if(list->head == NULL)
		list->head = node;
	else
		list->tail->next = node;

	list->tail = node;
	list->tail->next = 0;
	list->count++;
	return 1;
}

void* get_first_element(LinkedList list) {
	if(list.head==0)
		return 0;
	return list.head->data;
}

void* get_last_element(LinkedList list) {
	if(list.tail==0)
		return 0;
	return list.tail->data;
}

void traverse(LinkedList list, void (*function)(void*)){
	Node* walker = list.head;
	while(walker != 0){
		function(walker->data);
		walker = walker->next;
	}
}

void* getElementAt(LinkedList list, int index){
	int i=0;
	Node* walker = list.head;
	while(walker != 0){
		if(i++ == index){
			return walker->data;
		}
		walker = walker->next;
	}
	return 0;	
}

int indexOf(LinkedList list, void* data){
	int index=0;
	Node* walker = list.head;
	while(walker != 0){
		if(walker->data == data)
			return index;
		walker = walker->next;
		index++;
	}
	return -1;
}

void* deleteElementAt(LinkedList* list, int index){
	int i;
	void* deleted_data =0;
	Node *current= list->head,*previous=0;

	if(index<0 || index>=list->count)
		return 0;

	for(i=0 ; i<index ; i++){
		previous = current;
		current = current->next;
	}

	deleted_data = current->data;
	previous ? (previous->next = current->next) : (list->head = list->head->next);
	current == list->tail && (list->tail = previous);
	list->count--;

	return deleted_data;
}

int asArray(LinkedList list, void** array){
	int i=0;
	while(i < list.count)
		array[i++] = getElementAt(list,i);
	return i;
}

LinkedList* filter(LinkedList list, int(*function)(void*)){
	Node* walker = list.head;
	LinkedList* new_list = calloc(1,sizeof(list));
	while(walker != 0){
		if (function(walker->data)){
			add_to_list(new_list,create_node(walker->data));
		}
		walker = walker->next;
	}
	new_list->tail->next = 0;
	return new_list;
}