/*
Write a function with the signature int* sort(int* n) that takes a pointer to an array of
integers, and returns a pointer to a new array containing the integers in sorted order.
Note that a sort function with the signature above is not given the size of the array to be sorted,
and can only work with a fixed size array where the size is specified elsewhere in the program. A
better signature would be int* sort(int* n, int size) that adds a second parameter
giving the size of the array to be sorted. Modify a copy of your function, edit it to have this
signature with a new name, and update the function body to use the size parameter. 
*/

//From low to high
#include <stdio.h>
#define maxn 1005
int a[maxn];

void insertionSort(int* n, int size);
void selectionSort(int* n, int size);
void bubbleSort(int* n, int size);

int main(void){
    int x, n = 0;
    while(scanf("%d", &x)==1 && x)  //Enter 0 to exit inputing
        a[n++] = x;         
    //insertionSort(a, n);
    //selectionSort(a, n);
    bubbleSort(a, n);
    for(int i=0;i<n;i++)
        printf("%d ", a[i]);
    return 0;
}

void insertionSort(int* n, int size){
    int i, j, tmp;    
    for (i = 1; i < size; i++) {    
        if (n[i] < n[i-1]) {    
            tmp = n[i];    
            for (j = i - 1; j >= 0 && n[j] > tmp; j--) {  
                n[j+1] = n[j];    
            }  
            n[j+1] = tmp;    
        }          
    }    
}

void selectionSort(int *n, int size){
    int i, j, k, tmp;
    for (i = 0; i < size - 1; i++) {
        k = i;
        for (j = i + 1; j < size; j++) {
            if (n[j] < n[k]) {
                k = j;
            }
        }
        tmp = n[k];
        n[k] = n[i];
        n[i] = tmp;
    }
}

void bubbleSort(int *n, int size){
    int i, j, tmp;
    for(i = 0; i < size-1; i++){
        for(j = 0; j < size - i - 1; j++){
            if(n[j] > n[j+1]){
                tmp = n[j];
                n[j] = n[j+1];
                n[j+1] = tmp;
            }
        }
    }
}