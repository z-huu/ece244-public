#include "QueueList.h"

#include "Customer.h"

QueueList::QueueList() { head = nullptr; }

QueueList::QueueList(Customer* customer) { head = customer; }

QueueList::~QueueList() {
  
}

Customer* QueueList::get_head() {  }

void QueueList::enqueue(Customer* customer) {
  // a customer is placed at the end of the queue
  // if the queue is empty, the customer becomes the head
  if (head == NULL) {
    head = customer;
  } else {
    Customer* p = head;
    while (p->get_next() != NULL) {
      p = p->get_next(); //iterate until p points to last customer
    }
    p->set_next(customer);
    customer->set_next(NULL); //is this line necessary? i think customers are always initalized to next = null
  }
}

Customer* QueueList::dequeue() {
  // remove a customer from the head of the queue 
  // and return a pointer to it
  if (head == NULL) {
    return NULL;
  } else {
    Customer* p = head;
    head = head->get_next();
    p->set_next(NULL); // should I be doing this?
    return p;
  }
}

int QueueList::get_items() {
  // count total number of items each customer in the queue has
  // traverse linked list of customers, adding each of their numOfItems to a sum as we
  // pass over them
  int sum = 0;
  if (head == NULL) {
    return sum;
  } else {
    Customer *p = head;
    while (p != NULL) {
      sum += p->get_numOfItems();
      p = p->get_next();
    }
    return sum;
  }
}

bool QueueList::empty_queue() {
  // if the queue is empty, return false
  // if the queue is not empty, delete all customers
  // and return true
  if (head == NULL) { //queue is empty
    return false;
  } else {
    Customer* p = head->get_next();
    Customer* prev = head;
    while (p!=NULL) {
      prev->set_next(NULL);
      prev = head;
      // little confused; is there any dynamically allocated memory in Customer.cpp?~~~~~~~~~~~~~~~~~~~~~
    }
  }
}

void QueueList::print() {
  // print customers in a queue
  Customer* temp = head;
  while (temp != nullptr) {
    temp->print();
    temp = temp->get_next();
  }
}
