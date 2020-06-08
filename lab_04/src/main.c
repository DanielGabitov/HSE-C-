#include <stddef.h> 
#include "mergesort.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int comparator_int (const void * a, const void * b){
    return *(int * )a - *(int * )b;
}

int comparator_char (const void * a, const void * b){
    return *(char *)a - *(char *) b;
}

int comparator_str (const void * a, const void * b){
    return strcmp(*(const char **)a,*(const char **)b);
}

int main(int argc, char **argv) {
    if (argc <= 2){
        printf("What am i supposed to do? Give me some data! \n");
        return 0;
    }
    size_t elements = argc - 2;
    if ( strcmp(*(argv + 1), "int") == 0 ){
        int * data_int = malloc(sizeof(int) * elements);
        for (size_t i = 0; i < elements; i++){
            *(data_int + i) = atoi( *(argv + 2 + i));
        } 

        mergesort((void*)data_int, elements, sizeof(int), comparator_int);

        for (size_t i = 0; i < elements; i++){
            printf("%d", *(data_int + i));
            printf ("%c",' ');
        }
        printf("%c", '\n');
        free(data_int);

    } else if ( strcmp(*(argv + 1), "char") == 0 ) {
        char * data_char = malloc(sizeof(char) * elements) ;
        for (size_t i = 0; i < elements; i++){
            *(data_char + i) = *(*(argv + 2 + i));
        }
        mergesort((void *)data_char, elements,sizeof(char), comparator_char);

        for (size_t i = 0; i < elements; i++){
            printf("%c", *(data_char + i));
            printf("%c", ' ');
        }
        printf("%c", '\n');
        free(data_char);
    } else {
        char ** data_string = malloc (sizeof(char *) * elements);
        for (size_t i = 0; i < elements; i++){
            *(data_string + i) = *(argv + 2 + i);
        }
        mergesort((void **)data_string, elements, sizeof(char *), comparator_str);

        for (size_t i = 0; i < elements; i++){
            printf("%s", *(data_string + i));
            printf("%c", ' ');
        }
        printf("%c", '\n');
        free(data_string);

    }
}
