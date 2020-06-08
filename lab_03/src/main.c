#include "clist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define container_of(ptr, type, member) (type*)((char*)(ptr) - offsetof(type, member))

typedef struct point {
    int x, y;
    struct intrusive_node node;
}point;

void add_point(intrusive_list* list, int x, int y) {
    point* n = malloc(sizeof (struct point));
    n->x = x;
    n->y = y;
    add_node(list, &(n->node));
}

void remove_point(intrusive_list* list, int x, int y) {
    for (intrusive_node* cur = list->head->next; cur != NULL; cur = cur->next) {
        point* now = container_of(cur, point, node);
	if (now->x == x && now->y == y){
	    remove_node(list, cur);
            cur = cur->prev;
	    free(now);
        }
    }
}

void show_all_points(intrusive_list* list) {
    for (intrusive_node* cur = list->head->next; cur != NULL; cur = cur->next) {
        point* now = container_of(cur, point, node);
        printf("(%d %d) ", now->x, now->y);
    }
}

void remove_all_points(intrusive_list* list) {
    for (intrusive_node* cur = list->head->next; cur != NULL; cur = cur->next) {
        point* p = container_of(cur, point, node);
	cur = cur->prev;
	remove_node(list, cur->next);
        free(p);
    }
}
int main () {
    intrusive_list* list = malloc(sizeof(intrusive_list));
    init_list(list);
    while (1){
        char add [4] = "add";
        char rm [3] = "rm";
        char print [6] = "print";
        char rma [4] = "rma";
        char len [4] = "len";
        char exit [6] = "exit";
        char s [240];
        scanf("%239s", s);
        if (!strcmp(s, add)) {
	    int x, y;
            scanf("%d %d", &x, &y);
            add_point(list, x, y);
        }
        else if (!strcmp(s,rm)){
	    int x, y;
            scanf("%d %d", &x, &y);
            remove_point (list, x, y);
        }
        else if (!strcmp(s,print)){
            show_all_points(list);
        }
        else if (!strcmp(s,rma)){
            remove_all_points(list);
        }
        else if (!strcmp(s,len)){
            printf ("%d", get_length(list));
        }
	else if (!strcmp(s,exit)){
            remove_all_points(list);
            delete1(list);
            break;
	}
	else printf("Unknown command\n");

    }

}
