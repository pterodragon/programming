// from http://www.geeksforgeeks.org/print-all-possible-combinations-of-r-elements-in-a-given-array-of-size-n/
// Program to print all combination of size r in an array of size n
#include <stdio.h>
#include <stdlib.h>
#include "combination1.h"
#include "combination2.h"


// Driver program to test above functions
int main()
{
    int arr[] = {1, 2, 1, 3, 1};
    int r = 3;
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("### Include and exclude every element\n");
    combination_include_and_exclude(arr, n, r);
    printf("--------------------------------------------------\n");
    printf("### fix elements and recur\n");
    fix_elements_and_recur(arr, n, r);
    return 0;
}

