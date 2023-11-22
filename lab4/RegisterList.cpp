#include "RegisterList.h"

#include <iostream>

#include "Register.h"
using namespace std;

RegisterList::RegisterList() {
  head = nullptr;
  size = 0;
}

RegisterList::~RegisterList() {
  // Delete all registers in the list
  // Since each register has a next, we can delete the RegisterList head and hence
  // delete all Registers in the list. (unless there is some dynamically allocated memory?)
    //this would mean losing access to all customer queues attached to the registers.
    //but are they even dynamically allocated like bruh
  delete head;
}

Register* RegisterList::get_head() { return head; }

int RegisterList::get_size() { 
  // return number of registers 
  return size;
}


Register* RegisterList::get_min_items_register() {
  // loop all registers to find the register with least number of items

  if (head == nullptr) { //empty list case
    return nullptr;
  }

  //to find items, loop through each queueList. 

  Register* p = head;
  int minItems;

    Customer* hah = head->get_queue_list()->get_head();
    while (hah != nullptr) {
      minItems += hah->get_numOfItems();
      hah = hah->get_next();
    }
      
  int currentItems;
  Register* looper = head->get_next();

  while (looper != nullptr) {

      Customer* hah = looper->get_queue_list()->get_head();
        while (hah != nullptr) {
        minItems += hah->get_numOfItems();
        hah = hah->get_next();
      }

      if (currentItems < minItems) {
          minItems = currentItems;
          p = looper;
      }

      looper = looper->get_next();

  }

  return p;
}

Register* RegisterList::get_free_register() {
  // return the register with no customers
  // if all registers are occupied, return nullptr

  if (head == NULL) {
    return nullptr;
  }

  Register* p = head;
  while (p != NULL) {
    if (p->get_queue_list()->get_head() == NULL) { //if a register's queue list is empty (no customers)
      return p;
    }
    p->set_next(p->get_next());
  }

  return nullptr;
}

void RegisterList::enqueue(Register* newRegister) {
  // a register is placed at the end of the queue
  // if the register's list is empty, the register becomes the head
  // Assume the next of the newRegister is set to null
  // You will have to increment size 

  if (head == NULL) {
    head = newRegister;
    return;
  } ///////////////// Doesn't proceed past this if statement (if triggered)

  Register *p = head;
  while (p->get_next() != NULL) { // Iterate to the last register in the list
    p = p->get_next();
  }

  p->set_next(newRegister);
  size++;
  return;
}

bool RegisterList::foundRegister(int ID) {
  // look for a register with the given ID
  // return true if found, false otherwise
  if (head == NULL) {
    return false;
  }

  Register *p = head;
  while (p!=NULL) {

    if (p->get_ID() == ID) {
      return true;
    }
    p = p->get_next();
  }
  return false;
}

Register* RegisterList::dequeue(int ID) {
  // dequeue the register with given ID

  // return the dequeued register
  // return nullptr if register was not found

  if (head == NULL) {
    return nullptr;
  } else if (head->get_next() == NULL) {
    head->set_next(NULL);
    Register *p = head;
    head = NULL;
    return p;
  }

  Register* p = head;
  while (p != NULL || p->get_next()->get_ID() != ID) {
    p = p->get_next();
  }

  if (p == NULL) { //register with given ID doesn't exist
    return nullptr;
  } else { //found the register with given ID (pointing to node prior)

    Register* newNext = p->get_next()->get_next();
    p->get_next()->set_next(NULL);
    //delete p->get_next();
    Register* toReturn = p->get_next();
    p->set_next(newNext);
    return toReturn;

  }
}

Register* RegisterList::calculateMinDepartTimeRegister(double expTimeElapsed) {
  // return the register with minimum time of departure of its customer
  // if all registers are free, return nullptr

  if (head == nullptr) { //empty list case
    return nullptr;
  }

  ////////////////////////////////////////////////////
  //                                                //
  //    Initially implemented w/o expTimeElapsed    //
  ////////////////////////////////////////////////////


  //if all registers are free
  Register *searcher = head;
  while (searcher->get_queue_list()->get_head() == NULL) { //traverse while reg line is empty

    if (searcher = nullptr) { //if we reach end and there all reg are empty, return nullptr
      return nullptr;
    }

    searcher = searcher->get_next();
  }

  Register* p = head;
  int minTime = p->get_queue_list()->get_head()->get_departureTime();

  Register* looper = head->get_next();

  while (looper != nullptr) {

    int currTime = looper->get_queue_list()->get_head()->get_departureTime();
    if (currTime < minTime) {
      minTime = currTime;
      p = looper;
    }

    looper = looper->get_next();

  }

  return p;
  
}

void RegisterList::print() {
  Register* temp = head;
  while (temp != nullptr) {
    temp->print();
    temp = temp->get_next();
  }
}
