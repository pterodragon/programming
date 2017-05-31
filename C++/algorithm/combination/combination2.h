#ifndef COMBINATION2_H
#define COMBINATION2_H 

// Program to print all combination of size r in an array of size n
#include <stdio.h>
#include <stdlib.h>

void combinationUtil2(int arr[],int n,int r,int index,int data[],int i);
int compare2 (const void * a, const void * b) {  return ( *(int*)a - *(int*)b );  }
 
// The main function that prints all combinations of size r
// in arr[] of size n. This function mainly uses combinationUtil2()
void combination_include_and_exclude(int arr[], int n, int r)
{
    // Sort array to handle duplicates
    qsort(arr, n, sizeof(int), compare2);
    // A temporary array to store all combination one by one
    int data[r];
 
    // Print all combination using temprary array 'data[]'
    combinationUtil2(arr, n, r, 0, data, 0);
}
 
/* arr[]  ---> Input Array
   n      ---> Size of input array
   r      ---> Size of a combination to be printed
   index  ---> Current index in data[]
   data[] ---> Temporary array to store current combination
   i      ---> index of current element in arr[]     */
void combinationUtil2(int arr[], int n, int r, int index, int data[], int i)
{
    // Current cobination is ready, print it
    if (index == r)
    {
        for (int j=0; j<r; j++)
            printf("%d ",data[j]);
        printf("\n");
        return;
    }
 
    // When no more elements are there to put in data[]
    if (i >= n)
        return;
 
    // current is included, put next at next location
    data[index] = arr[i];
    combinationUtil2(arr, n, r, index+1, data, i+1);
    while (i < n && arr[i] == arr[i+1]) {
        ++i; 
    }
    // current is excluded, replace it with next (Note that
    // i+1 is passed, but index is not changed)
    combinationUtil2(arr, n, r, index, data, i+1);
}

#endif /* COMBINATION2_H */
