#include "clist.h"
#include "stdlib.h"

void init_list(intrusive_list* list) {
	list->head = malloc(sizeof(intrusive_node));
	list->head->next = NULL;
	list->head->prev = NULL;
}

void add_node(intrusive_list* list, intrusive_node* node) {
    node->prev = list->head;
    node->next = list->head->next;
    list->head->next = node;
    if (node->next != NULL) {
        node->next->prev = node;
    }
}
void remove_node(intrusive_list* list, intrusive_node* node) {
    (void)list;
    node->prev->next = node->next;
    if (node->next != NULL) {
        node->next->prev = node->prev;
    }
}
int get_length(intrusive_list* list) {
	int length = 0;
	for (intrusive_node* cur = list->head->next; cur != NULL; cur = cur->next) {
		length++;
	}
	return length;
}
void delete1(intrusive_list* list){
   free(list->head);
}
