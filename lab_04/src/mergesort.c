#include "mergesort.h"
#include <stddef.h> 
#include <stdlib.h>
#include <stddef.h> 
void cpy (void * source, void * dest, size_t element_size){
    for (size_t i = 0; i < element_size; i++){
        *((char *)dest + i) = *((char *)source + i); 
    }
}



void mergesort(void *array, size_t elements, size_t element_size, int (*comparator)(const void*, const void*)){
    if (elements <= 1){
        return;
    }
    size_t left_size = elements / 2;
    size_t right_size = elements - left_size;
    mergesort(array, left_size, element_size, comparator);
    mergesort((char *)array + left_size * element_size, right_size, element_size, comparator);
    char * tmp = malloc(elements * element_size);
    char * left_end = (char *)array + left_size * element_size;
    char * right_end = (char *)array + elements * element_size;
    char * tmp_cur = tmp;
    char * left_cur = array;
    char * right_cur = (char *)array + left_size * element_size;
    while (left_cur < left_end && right_cur < right_end){
        if (comparator (left_cur,right_cur) < 0){
            cpy (left_cur, tmp_cur, element_size);
            left_cur += element_size;
            tmp_cur += element_size;
        }
        else {
            cpy(right_cur, tmp_cur, element_size);
            right_cur += element_size;
            tmp_cur += element_size;
        }
    }
    while (left_cur < left_end){
        cpy(left_cur, tmp_cur, element_size);
        left_cur += element_size;
        tmp_cur += element_size;
    }
    while (right_cur < right_end){
        cpy(right_cur, tmp_cur, element_size);
        right_cur += element_size;
        tmp_cur += element_size;
    }
    tmp_cur = tmp;
    cpy (tmp_cur,array, element_size * elements);
    free(tmp);
}
