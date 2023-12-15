using namespace std;

#include <iostream>

/*

    Write a recursive function called reverseArray that reverses an n-element 
    array in-place, i.e., without using an additional array. For example, given 
    int arr[] = {1, 2, 3, 4, 5, 6, 7};, the function changes the array to have 
    {7, 6, 5, 4, 3, 2, 1}.

    That is, the reverseArray function swaps elements a[i] with element 
    a[n - i - 1]. For an n-element array, the function is called lke this: 
    reverseArray(a, 0, n-1);.

    Write your answer below. You are not allowed to use any loops in your 
    solution.

*/

void reverseArray(int* array, int left, int right) {

    //Function is initially called with left = 0, right = n-1, where n is num_elements
    int temp;
    //Base case.
    if (left >= right) return; //Nice

    temp = array[left]; //Saves leftmost value.
    array[left] = array[right]; //Sets leftmost value to rightmost value.
    array[right] = temp; //Sets rightmost value to leftmost value.

    reverseArray(array, left+1, right-1); //Solution has this enclosed in an if statement:
    // if (right - left > 1)
    //is this just for efficiency? or will the extra call actually mess things up? Idk.

}