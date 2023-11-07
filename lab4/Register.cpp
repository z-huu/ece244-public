
// Created by Salma Emara on 2023-06-02.
#include "Register.h"

#include <iostream>

Register::Register(int id, double timePerItem, double overhead,
                   double entryTime) {
  ID = id;
  secPerItem = timePerItem;
  overheadPerCustomer = overhead;
  availableTime = entryTime;
  next = nullptr;           // no other registers yet
  queue = new QueueList();  // no customers in line yet, but has to initialize a
                            // queue
}

Register::~Register() { }

QueueList* Register::get_queue_list() { return queue; }

Register* Register::get_next() { return next; }

int Register::get_ID() { return ID; }

double Register::get_secPerItem() { return secPerItem; }

double Register::get_overheadPerCustomer() { return overheadPerCustomer; }

double Register::get_availableTime() { return availableTime; }

void Register::set_next(Register* nextRegister) { next = nextRegister; }


void Register::set_availableTime(double availableSince) {
  availableTime = availableSince;
}

double Register::calculateDepartTime() {
  // Get the departure time of the first customer in the queue
  // returns -1 if no customer is in the queue
  if (queue->get_head() == NULL) {
    return -1;
  } else {
    return (secPerItem*(queue->get_head()->get_numOfItems())+overheadPerCustomer)+availableTime; //double check that this is calculated right
  } // departure time = ((secPerItem*numItems) + overheadPerCustomer ) + availableTime
    // processing time is (secPerItem * numItems) + overheadPerCustomer
    // departure time = processing time + availableTime
  
}

void Register::departCustomer(QueueList* doneList) {
  // dequeue the head, set last dequeue time, add to doneList,
  // update availableTime of the register
  availableTime += (((queue->get_head()->get_numOfItems())*secPerItem)+overheadPerCustomer); //new availableTime = customer's processing time + previous availableTime
  queue->get_head()->set_departureTime(availableTime); //sets last dequeue time
  doneList->enqueue(queue->dequeue()); //dequeues head and adds to doneList

  //is this legal lol ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}

void Register::print() {
  std::cout << "Register ID: " << ID << std::endl;
  std::cout << "Time per item: " << secPerItem << std::endl;
  std::cout << "Overhead per customer: " << overheadPerCustomer << std::endl;
  if (queue->get_head() != nullptr) {
    std::cout << "Queue has customers: \n";
    queue->print();
  }
}
