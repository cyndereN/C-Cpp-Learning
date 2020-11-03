/*
Write a function to create and return a ragged 2D array data structure. A ragged 2D array
has rows of different lengths. The basic data structure has an array of pointers that point to each
row, each of which is an array of integers.

It would be better if the ragged array data structure also stored information about the number of
rows and the length of each row. Modify your data structure so that it can store the size
information, and also provide functions to create and free a ragged array, along with helper
functions to get and set values in a ragged array and print out a ragged array. 
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int MAX_ROW = 3;
const int MAX_COLUMN = 5;

struct array{
    int id;
    int size;
    int a[MAX_COLUMN];
};

struct array *ragged_array[MAX_ROW];
struct array *createArray(int i, int* arr, int j);

int main ()
{
    for (int i = 0; i < MAX_ROW; i++){
        int arr[MAX_COLUMN];
        int j = 0, x;
        while(scanf("%d", &x) == 1 && j < MAX_COLUMN) 
            arr[j++] = x;  
        struct array *new_array = createArray(i, arr, j);
        ragged_array[i] = new_array;
    }

    for (int i = 0; i < MAX_ROW; i++){
        printf("Ragged_array[%d] is: \n", i);
        for (int j = 0; j < ragged_array[i]->size; j++)  printf("%d ",ragged_array[i]->a[j]);
        printf("\nLength of ragged_array[%d] = %d\n", i, ragged_array[i]->size);
    }
    return 0;
}

struct array *createArray(int i, int *arr, int j){
    struct array *new_array = calloc(sizeof(struct array), 1);
    new_array->id = i;
    new_array->size = j;
    memcpy(new_array->a,arr,j*sizeof(int));
    return new_array;
}