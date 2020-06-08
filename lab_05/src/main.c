#include "point_list.h"
#include "clist.h"
#include <stdio.h>
#include <string.h>

void count (intrusive_node *node, void *data){
    *(int *)data = *(int *)data + 1;
    (void)node;
}

void print_data (intrusive_node *node, void *data) {
    point_node *pnode = get_point(node);
    printf ((const char *)data, pnode->x,pnode->y);
}

void inode_printf(intrusive_node *node, void *data) {
    point_node *pnode = get_point(node);
    fprintf((FILE *)data, "%d %d\n", pnode->x, pnode->y);
}

void inode_fprintf(intrusive_node *node, void *data){
    point_node *pnode = get_point(node);
    int x = (pnode->x & 0xFF) + ((pnode->x >> 8) & 0xFF) +((pnode->x >> 16) & 0xFF);
    int y = (pnode->y & 0xFF) + ((pnode->y >> 8) & 0xFF) +((pnode->y >> 16) & 0xFF);
    fwrite(x,y, sizeof(char), 6, (FILE *)data);
}


int main(int argc, char *argv[] ) {
    if (argc <= 3){
        printf("Give me some data to work with!");
        return 0;
    }
    intrusive_list list;
    intrusive_list* l = &list;
    init_list(l);
    if (strcmp( (const char *)(argv[1]), "loadtext") == 0){
        FILE * src_file = fopen( argv[2], "r");

        if (!src_file){
            printf("usage\n");
            return EXIT_FAILURE;
        }
        int x, y;
        while (fscanf(src_file, "%d %d", &x, &y) == 2) {
            add_point(l, x, y);
        }
        fclose(src_file);

    } else {
        FILE * src_file = fopen( argv[2], "rb");
        if (!src_file){
            printf("usage\n");
            return EXIT_FAILURE;
        }
        int a,b;
        while ( fread(void*)&a, sizeof(char), 3, src_file) == 3 && 
        fread((void*)&b, sizeof(char), 3, src_file) == 3 ) {
            add_point(l, a, b);
        }
        fclose(src_file);
    }
    char action  = *argv[3];
    if (action == 's'){
        if (strcmp((const char *)(argv[3]),"savetext") == 0){
            FILE* end_file = fopen(argv[4], "w");
            apply(l, inode_printf, end_file);
        } else {
            FILE* end_file = fopen (argv[4], "wb");
            apply (l, inode_fprintf, end_file);
            fclose (end_file);
        }

    } else if (action == 'p'){
        char * fmt;
        fmt = argv[4];
        apply(l, print_data, fmt);
        printf("\n");
    } else {
        int counter = 0;
        int * p = &counter;
        apply(l,count,(void *)p);
        printf("%d\n", counter);
    }
    remove_all_points(l);
}
