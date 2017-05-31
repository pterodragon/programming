#ifndef COMBINATION1_HPP
#define COMBINATION1_HPP 

// from http://www.geeksforgeeks.org/print-all-possible-combinations-of-r-elements-in-a-given-array-of-size-n/
// Program to print all combination of size r in an array of size n
#include <stdio.h>
#include <stdlib.h>

void combinationUtil1(int arr[], int data[], int start, int end, int index, int r);

int compare (const void * a, const void * b) {  return ( *(int*)a - *(int*)b );  }

// The main function that prints all combinations of size r
// in arr[] of size n. This function mainly uses combinationUtil1()
void fix_elements_and_recur(int arr[], int n, int r)
{
    // A temporary array to store all combination one by one
    int data[r];
    for (int i=0; i<r; ++i) {
        data[i] = -1;
    }
    printf("init data=[");
    for (int i=0; i<r; ++i)
        printf("%d " ,data[i]);
    printf("]\n");
    fflush( stdout );
    // Sort array to handle duplicates
    qsort (arr, n, sizeof(int), compare);
    printf("after qsort:\n");

    printf("fix_elements_and_recur([");
    for (int i=0; i<n; ++i)
        printf("%d " ,arr[i]);
    printf("], %d, %d)\n", n, r);

    // Print all combination using temprary array 'data[]'
    combinationUtil1(arr, data, 0, n-1, 0, r);
}

/* arr[]  ---> Input Array
   data[] ---> Temporary array to store current combination
   start & end ---> Staring and Ending indexes in arr[]
   index  ---> Current index in data[]
   r ---> Size of a combination to be printed */
void combinationUtil1(int arr[], int data[], int start, int end, int index, int r)
{
    printf("---data = [");
    for (int i=0; i<r; ++i)
        printf("%d " ,data[i]);
    printf("]");
    printf(", start = %d, end = %d, index = %d, r = %d\n", start, end, index, r);

    // Current combination is ready to be printed, print it
    if (index == r)
    {
        printf("result:[");
        for (int i=0; i<r; ++i)
            printf("%d " ,data[i]);
        printf("]\n");
        return;
    }

    // replace index with all possible elements. The condition
    // "end-i+1 >= r-index" makes sure that including one element
    // at index will make a combination with remaining elements
    // at remaining positions
    for (int i=start; i<=end && end-i+1 >= r-index; ++i)
    {
        printf("loop i=%d, start=%d, i<=end=%d, end>=(r-index+i-1)=%d\n", i, start, end, r-index+i-1);
        data[index] = arr[i];
        combinationUtil1(arr, data, i+1, end, index+1, r);
        data[index] = -1;


        // Remove duplicates
        while (i <= end && arr[i] == arr[i+1]) {
            printf("duplicate arr[%d] == arr[%d] == %d\n", i, i+1, arr[i]);
            ++i;
        }
        printf("i at end of loop = %d\n", i);
    }
}
#endif /* COMBINATION1_HPP */

