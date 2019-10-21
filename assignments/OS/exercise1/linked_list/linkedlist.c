/**
 *  Source file for a linked list in C
 *
 * @authors:   		Michael Denzel
 * @creation_date:	2016-09-05
 * @contact:		m.denzel@cs.bham.ac.uk
 */

//standard includes
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

//own includes
#include "linkedlist.h"

int count(list* l)
{
    int cnt = 0;
    list* current_node = l;
    while (current_node != NULL) {
	cnt++;
	printf("INDEX: %d, DATA: %d\n", current_node->index, current_node->data);
	current_node = current_node->next;
    }
    return (cnt);
}

int get(list* l, unsigned int index)
{
    list* current = l;
    if (l == NULL)
	return -1;
    while (current->index != index) {
	if (current->next == NULL)
	    return -1;
	else
	    current = current->next;
    }
    return current->data;
}

int prepend(list* l, int data)
{

    list* new_l = (list*)malloc(sizeof(list));
    new_l->data = data;
    new_l->next = l;
    l = new_l;
    printf("Hello world\n");
    return 0;
}

int append(list* l, int data)
{
    list* current = l;
    while (current->next != NULL) {
	current = current->next;
    }
    current->next = (list*)malloc(sizeof(list));
    if (current->next == NULL)
	return -1;
    current->next->data = data;
    current->next->next = NULL;
    return 0;
}

int remove_element(list* l, unsigned int index)
{

    //start from the first link
    list* current = l;
    list* previous = NULL;

    //if list is empty
    if (l == NULL) {
	return -1;
    }

    //navigate through list
    while (current->index != index) {

	//if it is last node
	if (current->next == NULL) {
	    return -1;
	} else {
	    //store reference to current link
	    previous = current;
	    //move to next link
	    current = current->next;
	}
    }

    //found a match, update the link
    if (current == l) {
	//change first to point to next link
	l = l->next;
    } else {
	//bypass the current link
	previous->next = current->next;
    }
    return 0;
}

int insert(list* l, unsigned int index, int data)
{
    list* current = l;
    list* new_l;
    while (current->index != index) {
	current = current->next;
    }
    new_l = (list*)malloc(sizeof(list));
    if (new_l == NULL)
	return -1;
    new_l->data = data;
    new_l->next = current->next;
    current->next = new_l;
    print_list(l);
    return 0;
}

void print_list(list* l)
{

    list* current = l;
    while (current != NULL) {
	if (current->data == 0) {
	    printf("empty list\n");
	    break;
	}
	printf("%d ", current->data);
	current = current->next;
    }
    printf("\n");
}

void init(list* l)
{
    l = NULL;
    l = (list*)malloc(sizeof(list));
    l->data = 12;
    l->index = 0;
    l->next = NULL;
}

void destroy(list* l)
{

    free(l);
    l = NULL;
}
