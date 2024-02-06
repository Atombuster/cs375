/*
Austen Turbyne
*/

#include <llist.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

/* 
my notes

-> lets me access the data that the pointer points to

** is just a pointer to pointer lets me mod the pointer

* operator dereferences the pointer giveing me access to the 
value that the pointer

& operator is used to get address of a variable
for example &variable gives the address of variable "variable"
this can be used to modify the pointer leaving the node untouched

(Austen Kyler Turbyne not forget this again)
*/
int main(int argc, char *argv[]){
	
	struct node *list = NULL;
	for(int i = 1; i < argc; i++){
		if (strcmp(argv[i], "ih") == 0) {
			struct node *n = node_alloc(atoi(argv[i+1]));
			llist_insert_head(&list, n);
			i++;
		} else if (strcmp(argv[i], "it") == 0){
			struct node *n = node_alloc(atoi(argv[i+1]));
			llist_insert_tail(&list, n);
			i++;
		} else if (strcmp(argv[i], "dh") == 0){
			struct node *n = llist_delete_head(&list);
			node_free(n);
		} else if (strcmp(argv[i], "f") == 0){
			llist_free(&list);
		} else if (strcmp(argv[i], "p") == 0){
			llist_print(list);
		}
	}// go through all commands and do them if found
	
	return 0;
}

struct node *node_alloc(int value){
	struct node *n = (struct node*)malloc(sizeof(struct node));
	n->value = value;
	n->next = NULL;
	return n;
}// allocate nodes

void node_free(struct node *n) {
	free(n);
}//free this node

void llist_print(struct node *head) {
	struct node *curr = head;
	while(curr != NULL) {
		printf("%d ", curr->value);
		curr = curr->next;
		
	}
    
    printf("\n");
}// print out the whole linked list

void llist_insert_head(struct node **head, struct node *n) {
	n->next = *head;
	*head = n;

}//insert node at head

void llist_insert_tail(struct node **head, struct node *n){
	if(*head == NULL){
		*head = n;
	} else {
		struct node *curr = *head;
		while(curr->next != NULL){
			curr = curr->next;
		}//loop to end of loop
		curr->next = n;
	}
}//add a node to the end of a list

struct node *llist_delete_head(struct node **head){
	if (*head == NULL) {
		return NULL;
	}
	struct node *temp = *head;
	*head = (*head)->next;
	return temp;
}//delete head of linked list

void llist_free(struct node **head){
	struct node *curr = *head;
	struct node *next;
	while(curr != NULL){
			next = curr->next;
			node_free(curr);
			curr = next;
	}
	*head = NULL;
}//free the linked list

