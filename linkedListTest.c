#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "expr_assert.h"
#include "linkedList.h"

typedef struct student Student;
struct student{
	char* name;
	int id;
};

void test_createList_creates_an_empty_list_for_integer_data() {
	LinkedList l;
	l = createList();
	assertEqual((int)l.head,0);
	assertEqual((int)l.tail,0);
	assertEqual(l.count,0);
}

void test_create_node_creates_a_node_with_int_data() {
	int data = 10;
	void* data_ptr = &data;
	Node* n;
	n = create_node(data_ptr);
	assertEqual(*(int*)(n->data),data);
	assertEqual((int)n->next,0);
	free(n);
}

void test_create_node_creates_a_node_with_char_data() {
	char data = 'A';
	Node* n;
	n = create_node((void*)&data);
	assertEqual(*(char*)(n->data),data);
	free(n);
}

void test_create_node_creates_a_node_with_sturcture() {
	Student s = {"Dolly",1};
	Student *result;
	Node* n;
	n = create_node(&s);
	result->id = ((Student*)n->data)->id;
	result->name = ((Student*)n->data)->name;
	assertEqual(result->id,1);
	assertEqual(strcmp(result->name,"Dolly"),0);
	free(n);
}

void test_add_to_list_adds_node_to_linked_list_and_add_resets_head_tail_and_count_for_int_node() {
	int a,b,c;
	int data = 20;
	char data2 = 'A';
	Node* node = create_node(&data);
	Node* node2 = create_node(&data2);
	LinkedList list = createList();

	add_to_list(&list,node);
	assertEqual(list.count,1);
	assertEqual(*(int*)list.head->data,data);
	assertEqual(*(int*)list.tail->data,data);
	assertEqual((int)list.tail->next,0);

	add_to_list(&list,node2);
	assertEqual(list.count,2);
	assertEqual(*(int*)list.head->data,data);
	assertEqual(*(char*)list.tail->data,data2);
	assertEqual((int)list.tail->next,0);

	free(node);
	free(node2);
}

void test_add_to_list_adds_node_to_linked_list_for_structures() {
	Student s1={"Dolly",1},s2={"Polly",2};
	Student *result1,*result2;
	Node* node = create_node(&s1);
	Node* node2 = create_node(&s2);
	LinkedList list = createList();

	add_to_list(&list,node);
	result1 = (Student*)list.head->data;
	result2 = (Student*)list.tail->data;

	assertEqual(list.count,1);
	assertEqual(result1->id,s1.id);
	assertEqual(result2->id,s1.id);

	add_to_list(&list,node2);
	result1 = (Student*)list.head->data;
	result2 = (Student*)list.tail->data;

	assertEqual(list.count,2);
	assertEqual(result1->id,s1.id);
	assertEqual(result2->id,s2.id);
	assertEqual((int)list.tail->next,0);

	free(node);
	free(node2);
}

void test_add_to_list_returns_null_if_node_or_are_null() {
	int data = 10;
	LinkedList list = createList();
	Node* n = create_node(&data);

	add_to_list(&list,0);
	add_to_list(0,n);
}


void test_get_first_element_gives_the_head_of_the_list() {
	int data1 = 10;
	int data2 = 20;
	Node* n1 = create_node((void*)&data1);
	Node* n2 = create_node((void*)&data2);
	LinkedList list = createList();
	int* result;
	result = (int*)get_first_element(list);
	assertEqual((int)result,0);

	add_to_list(&list,n1);
	result = (int*)get_first_element(list);
	assertEqual(*result,data1);

	add_to_list(&list,n2);
	result = (int*)get_first_element(list);
	assertEqual(*result,data1);

	free(n1);
	free(n2);
}

void test_get_last_element_gives_the_tail_of_the_list() {
	int data1 = 10;
	int data2 = 20;
	Node* n1 = create_node(&data1);
	Node* n2 = create_node(&data2);
	LinkedList list = createList();
	int* result;
	result = (int*)get_last_element(list);
	assertEqual((int)result,0);

	add_to_list(&list,n1);
	result = (int*)get_last_element(list);
	assertEqual(*result,data1);

	add_to_list(&list,n2);
	result = (int*)get_last_element(list);
	assertEqual(*result,data2);

	free(n1);
	free(n2);
}

void square(void* data){
	int sqr = *(int*)data;
	*(int*)data = (*(int*)data)*(*(int*)data);
}

void test_traverse_squares_each_element_of_int_node_list_when_asked_to_sqaure(){
	int data1 = 10;
	int data2 = 20;
	Node* n1 = create_node(&data1);
	Node* n2 = create_node(&data2);
	LinkedList list = createList();
	add_to_list(&list,n1);
	add_to_list(&list,n2);
	traverse(list,square);
	assertEqual(data1,100);
	assertEqual(data2,400);

	free(n1);
	free(n2);
}

void test_getElementAt_returns_the_reference_to_the_ele_at_the_given_index() {
	int data1 = 10;
	int data2 = 20;
	int data3 = 30;
	int result;
	Node* n1 = create_node(&data1);
	Node* n2 = create_node(&data2);
	Node* n3 = create_node(&data3);
	LinkedList list = createList();
	add_to_list(&list,n1);
	add_to_list(&list,n2);
	add_to_list(&list,n3);

	result = *(int*)getElementAt(list,1);
	assertEqual(result,20);

	free(n1);
	free(n2);
	free(n3);
}

void test_indexOf_returns_first_index_of_the_given_element (){
	int data1 = 10,data2 = 20,data3 = 30,data4 = 40;

	Node* n1 = create_node(&data1);
	Node* n2 = create_node(&data2);
	Node* n3 = create_node(&data3);
	LinkedList list = createList();
	add_to_list(&list,n1);
	add_to_list(&list,n2);
	add_to_list(&list,n3);

	assertEqual(indexOf(list,&data2),1);
	assertEqual(indexOf(list,&data3),2);

	free(n1);
	free(n2);
	free(n3);
}

void test_indexOf_returns_negative_1_for_data_that_is_not_in_list (){
	int data1 = 10,data2 = 20,data3 = 30,data4 = 40;

	Node* n1 = create_node(&data1);
	Node* n2 = create_node(&data2);
	Node* n3 = create_node(&data3);
	LinkedList list = createList();
	add_to_list(&list,n1);
	add_to_list(&list,n2);
	add_to_list(&list,n3);

	assertEqual(indexOf(list,&data4),-1);

	free(n1);
	free(n2);
	free(n3);
}

void test_deleteElementAt_deletes_the_node_and_returns_deleted_data_reference (){
	int data1 = 10,data2 = 20,data3 = 30;

	Node* n1 = create_node(&data1);
	Node* n2 = create_node(&data2);
	Node* n3 = create_node(&data3);
	LinkedList list = createList();
	add_to_list(&list,n1);
	add_to_list(&list,n2);
	add_to_list(&list,n3);

	assertEqual(*(int*)n1->next->data,data2);
	assertEqual(*(int*)deleteElementAt(&list,1),data2);
	assertEqual(*(int*)n1->next->data,data3);

	free(n1);
	free(n2);
	free(n3);
}

void test_deleteElementAt_deletes_the_head_and_head_changes_to_2nd_node (){
	int data1 = 10,data2 = 20,data3 = 30;
	int* result;

	Node* n1 = create_node(&data1);
	Node* n2 = create_node(&data2);
	Node* n3 = create_node(&data3);
	LinkedList list = createList();
	add_to_list(&list,n1);
	add_to_list(&list,n2);
	add_to_list(&list,n3);

	assertEqual(*(int*)list.head->data,data1);
	result = deleteElementAt(&list,0);
	assertEqual(*result,data1);
	assertEqual(*(int*)list.head->data,data2);

	free(n1);
	free(n2);
	free(n3);
}

void test_deleteElementAt_deletes_the_tail_and_tail_changes_to_last_2nd_node (){
	int data1 = 10,data2 = 20,data3 = 30;
	int* result;

	Node* n1 = create_node(&data1);
	Node* n2 = create_node(&data2);
	Node* n3 = create_node(&data3);
	LinkedList list = createList();
	add_to_list(&list,n1);
	add_to_list(&list,n2);
	add_to_list(&list,n3);

	assertEqual(*(int*)list.tail->data,data3);
	assertEqual(list.count,3);
	result = deleteElementAt(&list,2);
	assertEqual(list.count,2);
	assertEqual(*result,data3);
	assertEqual(*(int*)list.tail->data,data2);

	free(n1);
	free(n2);
	free(n3);
}

void test_asArray_copies_list_to_array_and_returns_array_length() {
	int data1 = 10,data2 = 20,data3 = 30;
	int* result;
	int* array[3];

	Node* n1 = create_node(&data1);
	Node* n2 = create_node(&data2);
	Node* n3 = create_node(&data3);
	LinkedList list = createList();
	add_to_list(&list,n1);
	add_to_list(&list,n2);
	add_to_list(&list,n3);

	assertEqual(asArray(list,(void**)array),3 );
	assertEqual(*array[0],data1);
	assertEqual(*array[1],data2);
	assertEqual(*array[2],data3);

	free(n1);
	free(n2);
	free(n3);
}

int isEven(void* item){
	int _item = *(int*)item;
	return _item%2 == 0;
}

void test_filter_returns_the_filtered_linked_list() {
	int data1 = 15,data2 = 20,data3 = 30;
	int* result;
	int* array[3];

	Node* n1 = create_node((void*)&data1);
	Node* n2 = create_node((void*)&data2);
	Node* n3 = create_node((void*)&data3);
	LinkedList list = createList(), *filtered;
	add_to_list(&list,n1);
	add_to_list(&list,n2);
	add_to_list(&list,n3);
	
	filtered = filter(list,&isEven);
	assertEqual(filtered->count,2 );
	assertEqual(*(int*)filtered->head->data,data2);
	assertEqual(*(int*)filtered->tail->data,data3);

	free(n1);
	free(n2);
	free(n3);
}

void test_filter_returns_the_filtered_linked_list_with_the_new_head_and_tail() {
	int data1 = 15,data2 = 20,data3 = 30,data4=19;
	int* result;
	int* array[3];

	Node* n1 = create_node((void*)&data1);
	Node* n2 = create_node((void*)&data2);
	Node* n3 = create_node((void*)&data3);
	Node* n4 = create_node((void*)&data4);
	LinkedList list = createList(), *filtered;
	add_to_list(&list,n1);
	add_to_list(&list,n2);
	add_to_list(&list,n3);
	add_to_list(&list,n4);
	
	filtered = filter(list,&isEven);
	assertEqual(filtered->count,2 );
	assertEqual(*(int*)filtered->head->data,data2);
	assertEqual(*(int*)filtered->tail->data,data3);

	free(n1);
	free(n2);
	free(n3);
}