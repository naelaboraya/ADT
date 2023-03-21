
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


//deletes/frees the array
void DeleteAdptArray(PAdptArray arr) {
    for (int i=0 ; i< arr->size ; i++){
        if (arr->elements[i] != NULL){
           arr->del_func(arr->elements[i]);
        }
    }
    free(arr->elements);
    free(arr);
}



//a helping function to resize the array capacity , used in SetAdptArrayAt function
 static void change_size(PAdptArray arr, int NEW_CAPACITY) {
    PElement* elems = (PElement*) realloc(arr->elements, NEW_CAPACITY * sizeof(PElement));
    if (elems == NULL) {
        return;//did not allocate
    }
    arr->elements = elems;
    for (int i = arr->size; i < NEW_CAPACITY; i++) {
        arr->elements[i] = NULL;
    }
    arr->capacity = NEW_CAPACITY;
}



//takes an index and an element , saves a copy of the element in the specific index , frees the old element if exists .
//returns result of the process (SUCCESS/FAIL)
Result SetAdptArrayAt(PAdptArray arr, int index, PElement elem) {
    if (index < 0) {
        return FAIL;//index should be positive!
    }
    if (index >= arr->capacity) {
        change_size(arr, index + 1);
    }
    if (index >= arr->size) {
        for (int i = arr->size; i <= index; i++) {
            free(arr->elements[i]);
        }
        arr->size = index + 1;
    }
    if (arr->elements[index] != NULL) {
        free(arr->elements[index]);
    }

    
    arr->elements[index] = arr->copy_func(elem) ;
    return SUCCESS;//the process succeeded
}

