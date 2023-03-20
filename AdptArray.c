
#include <stdlib.h>
#include <stdio.h>
#include "AdptArray.h"




struct AdptArray_ {
    PElement* elements;
    int size;
    int capacity;
    COPY_FUNC copy_func;
    DEL_FUNC del_func;
    PRINT_FUNC print_func;
};




//creates the array and initializes its values , default capacity = 8
PAdptArray CreateAdptArray(COPY_FUNC copy_func, DEL_FUNC del_func, PRINT_FUNC print_func) {
    PAdptArray arr = (PAdptArray) malloc(sizeof(struct AdptArray_));
    if (arr == NULL) {
        return NULL;//did not allocate
    }
    arr->elements = (PElement*) calloc(8, sizeof(PElement));//8 = default capacity
    if (arr->elements == NULL) {
        return NULL;//did not allocate
    }
    arr->size = 0;
    arr->capacity = 8;//default
    arr->copy_func = copy_func;
    arr->del_func = del_func;
    arr->print_func = print_func;
    
    return arr;
}

