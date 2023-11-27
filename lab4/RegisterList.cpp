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

  Register* first = head;
  Register* looper = head->get_next();
  if (looper == NULL) return first;

  while (looper != nullptr) {
    if (looper->get_queue_list()->get_items() < first->get_queue_list()->get_items()) {
      first = looper;
    }
    looper = looper->get_next();
  }
  return first;
}

Register* RegisterList::get_free_register() {
  // return the register with no customers
  // if all registers are occupied, return nullptr

  if (head == NULL) { //Empty register list case.
    return nullptr;
  }

  Register* iterator = head;

  //While the current register has a customer
  while (iterator->get_queue_list()->get_head() != NULL) {
    iterator = iterator->get_next();
    // If we push iterator to a register with no customers, loop stops running and
    // we return iterator.
    if (iterator == NULL) { //If we've reached the end of the register list.
      return nullptr;
    }
  }


  return iterator;
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
    if (p == NULL) {
      return false;
    }
  }
  return false;
}

Register* RegisterList::dequeue(int ID) {
  // dequeue the register with given ID

  // return the dequeued register
  // return nullptr if register was not found

  if (head == NULL) { //Empty list case
    return nullptr;
  } 
  
  Register* looker = head;

  if (head->get_ID() == ID) { //First node case
    head = head->get_next();
    looker->set_next(NULL);
    return looker;
  }

  while (looker->get_next() != NULL) {

    if (looker->get_next()->get_ID() == ID) {
      Register* toReturn = looker->get_next();
      looker->set_next(toReturn->get_next());
      toReturn->set_next(NULL);
      return toReturn;
    }

    looker = looker->get_next();
    if (looker->get_next() == NULL) {
      return nullptr;
    }
  }
  return nullptr;
}

Register* RegisterList::calculateMinDepartTimeRegister(double expTimeElapsed) {
  // return the register with minimum time of departure of its customer
  // if all registers are free, return nullptr

  //Check if all registers are free. aka,
  //Check that all registers' queueLists' heads are NULL.
  if (head == NULL) return nullptr; //Empty register list case

  int freeRegCounter = 0;
  Register* toReturn = head;
  Register* searcher;
  int minTime;
  
  if (head->get_next()!=NULL) {
    searcher=head->get_next();
  } else { return toReturn; }

  Register* checker = head;

  while (checker != NULL) {
    
    if (checker->get_queue_list()->get_head() != NULL) freeRegCounter++;
    /*
    //Register Debugging //////////////////////////////////////////////////
    cout << "Register ID: " << checker->get_ID();
      if (checker->get_queue_list()->get_head() == NULL) {
        cout <<" had no customers." << endl;
      } else {
        cout << " had a customer." << endl;
      }
    //Register DEbugging //////////////////////////////////////////////
    */
    checker = checker->get_next();

  }

  if (freeRegCounter <= 0) return nullptr;
  //End check of all free registers. Past this point, can assume there is at least
  //one occupied register.

  //Find the first occupied register to start from.
  searcher = head;
  while (searcher != NULL) {
    if (searcher->get_queue_list()->get_head()!=NULL) {
      toReturn = searcher;
      minTime = toReturn->get_queue_list()->get_head()->get_departureTime();
      break;
    }
    searcher = searcher->get_next();
  }

  //toReturn is now situated at the occupied register closest to the regList head
  searcher = toReturn->get_next();
  while (searcher != NULL) {
    
    if (  (searcher->get_queue_list()->get_head() != NULL)&&
          (searcher->calculateDepartTime() < minTime) ) {

          minTime = searcher->calculateDepartTime();
          toReturn = searcher;
    }

    searcher = searcher->get_next();

  }
  return toReturn;
}

void RegisterList::print() {
  Register* temp = head;
  while (temp != nullptr) {
    temp->print();
    temp = temp->get_next();
  }
}
