/*

    Circular linked lists are a variation on linked lists described in class. 
    In a circular linked list, the next field in the last node in the list is 
    not set to NULL (or nullptr). Rather, the field is made to point to the 
    first node in the list, hence the name “circular”. An example of a circular 
    linked list is shown below.

    Consider the class ListNode shown below. It represents a node in a circular 
    linked list. It is similar to the one described in class and that you 
    implemented in the labs, but all members are public for simplicity. 
    The declaration of a head pointer, which points to the head of the list, 
    is also shown.

*/

using namespace std;
#include <iostream>

class ListNode {
 public:
  int id;
  ListNode* next;
};
ListNode* head;

//Q1: Write a non-member function traverse ListNode* h that traverses the 
//linked list. The function is invoked as traverse(head) to start the 
//traversal at the head of the list. In the traversal, visiting a node 
//is simply printing its id field to cout.

void traverse(ListNode* h) {

    if (h == NULL) return; //Empty list case.

    ListNode* traverser = h;

    do { //Accounts for one node case using the do while loop.
        cout << traverser->id << endl;
        traverser = traverser->next;
    } while (traverser != h);
}

/* Q2

    Write a non-member function deleteNode(ListNode*& h, ListNode* p) that 
    deletes the node after the one pointed to by p from the circular list 
    pointed to by h. The function is invoked as deleteNode(head, ptr), 
    where ptr is guaranteed to point to one of the nodes on the list.

*/

void deleteNode(ListNode*& h, ListNode* p) {

    //h is the head. Want to delete the node AFTER p.

    if (h == NULL) return;
    //p guaranteed to be node in the list

    if (h == p) {
        delete h;
        p = NULL; h = NULL;
        return;
    }

    ListNode* toDelete = p->next;
    if (toDelete == h) { //Two node case.
        h->next = NULL; delete h; h = p; p->next = p; return;
    } //So they didn't actually say you'd be penalized for memory leaks; simply h=p would do
    ListNode* newNext = p->next->next;

    toDelete->next = NULL;
    delete toDelete;
    p->next = newNext;
    return; 

}

/* Q3

    It is sometimes not known if the linked list pointed to by head is circular or 
    just a regular linked list with the next field in the last node set to NULL.
    Write a non-member function isCircular(ListNode* h) that returns true if the 
    list is circular and false otherwise. The function is invoked as isCircular(head).

*/

bool isCircular(ListNode* h) {

    // $$$$$$$ Forgot to check for empty list case $$$$$$$$$$$

    //h is always head.
    ListNode* traverser = h;
    while (traverser->next != NULL) {

        //

        if (traverser->next == h) return true;
        traverser = traverser->next;
    }

    return false;
}