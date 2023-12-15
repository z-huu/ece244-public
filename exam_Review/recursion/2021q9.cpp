using namespace std;

#include <iostream>

/*

    Write a recursive function that replaces each element of an array of 
    positive integers with its prefix sum. The prefix sum of an element 
    is the sum of the element and all the elements that are at smaller 
    indices than it. For example, for the 4-element array, 
    int arr[] = {1, 2, 3, 4};, the function replaces the elements of the 
    array to be {1, 3, 6, 10}.

*/

void prefixsum(int* arr, int left, int right, int psum) {

    // Tracing the process.
    // 1 2 3 4  First index unchanged   psum1
    // 1 3 3 4  Update 2                psum3
    // 1 3 6 4  Update 3                psum6
    // 1 3 6 10 Update 4                psum10

    //Left is initially 0, while right is passed as n-1 (n is the number of elements)
    //psum is initially 0
    //Each recursion should call prefixsum with left as n+1. That will be 

    //Base case.
    if (right == left) return; //Should be (left > right). Otherwise missing one operation

    psum += arr[left]; //Good.
    arr[left] = psum; //Good.

    prefixsum(arr, left+1, right, psum); //Good

}