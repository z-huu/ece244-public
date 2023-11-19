#include <cmath>
#include <cstdlib>
#include <iostream>
#include <sstream>

#include "Customer.h"
#include "QueueList.h"
#include "Register.h"
#include "RegisterList.h"

using namespace std;

// Function Declarations:

// Set mode of the simulation
string getMode();

// Register
void parseRegisterAction(stringstream &lineStream, string mode);
void openRegister(
    stringstream &lineStream,
    string mode);  // register opens (it is upto customers to join)
void closeRegister(stringstream &lineStream,
                   string mode);  // register closes 

// Customer
void addCustomer(stringstream &lineStream,
                 string mode);  // customer wants to join


// Helper functions
bool getInt(stringstream &lineStream, int &iValue);
bool getDouble(stringstream &lineStream, double &dValue);
bool foundMoreArgs(stringstream &lineStream);

// Global variables
RegisterList *registerList; // holding the list of registers
QueueList *doneList; // holding the list of customers served
QueueList *singleQueue; // holding customers in a single virtual queue
double expTimeElapsed; // time elapsed since the beginning of the simulation

// List of commands:
// To open a register
// register open <ID> <secPerItem> <setupTime> <timeElapsed>
// To close register
// register close <ID> <timeElapsed>
// To add a customer
// customer <items> <timeElapsed>

int main() {
  registerList = new RegisterList();
  doneList = new QueueList();
  singleQueue = new QueueList();
  expTimeElapsed = 0;

  // Set mode by the user
  string mode = getMode();

  string line;
  string command;

  cout << "> ";  // Prompt for input
  getline(cin, line);

  while (!cin.eof()) {
    stringstream lineStream(line);
    lineStream >> command;
    if (command == "register") {
      parseRegisterAction(lineStream, mode);
    } else if (command == "customer") {
      addCustomer(lineStream, mode);
    } else {
      cout << "Invalid operation" << endl;
    }

    if (mode == "single") {

      

    } else if (mode == "multiple") {

    }

    cout << "> ";  // Prompt for input
    getline(cin, line);
  }

  // You have to make sure all dynamically allocated memory is freed 
  // before return 0
  delete registerList->get_head();

  return 0;
}

string getMode() {
  string mode;
  cout << "Welcome to ECE 244 Grocery Store Queue Simulation!" << endl;
  cout << "Enter \"single\" if you want to simulate a single queue or "
          "\"multiple\" to "
          "simulate multiple queues: \n> ";
  getline(cin, mode);

  if (mode == "single") {
    cout << "Simulating a single queue ..." << endl;
  } else if (mode == "multiple") {
    cout << "Simulating multiple queues ..." << endl;
  }

  return mode;
}

void addCustomer(stringstream &lineStream, string mode) {
  int items;
  double timeElapsed;
  if (!getInt(lineStream, items) || !getDouble(lineStream, timeElapsed)) {
    cout << "Error: too few arguments." << endl;
    return;
  }
  if (foundMoreArgs(lineStream)) {
    cout << "Error: too many arguments." << endl;
    return;
  }
  // Depending on the mode of the simulation (single or multiple),
  // add the customer to the single queue or to the register with
  // fewest items

  expTimeElapsed += timeElapsed;
  Customer* dude = new Customer(expTimeElapsed, items); //make our customer to enqueue

  if (mode == "single") { //just one register, we can simply enqueue the customer

    registerList->get_head()->get_queue_list()->enqueue(dude);

  } else if (mode == "multiple") { //need to enqueue the customer at the register with
                                   //least number of items.
    
    Register* bestReg = registerList->get_min_items_register();
    bestReg->get_queue_list()->enqueue(dude);
    
  }
  
}

void parseRegisterAction(stringstream &lineStream, string mode) {
  string operation;
  lineStream >> operation;
  if (operation == "open") {
    openRegister(lineStream, mode);
  } else if (operation == "close") {
    closeRegister(lineStream, mode);
  } else {
    cout << "Invalid operation" << endl;
  }
}

void openRegister(stringstream &lineStream, string mode) {
  int ID;
  double secPerItem, setupTime, timeElapsed;
  // convert strings to int and double
  if (!getInt(lineStream, ID) || !getDouble(lineStream, secPerItem) ||
      !getDouble(lineStream, setupTime) ||
      !getDouble(lineStream, timeElapsed)) {
    cout << "Error: too few arguments." << endl;
    return;
  }
  if (foundMoreArgs(lineStream)) {
    cout << "Error: too many arguments" << endl;
    return;
  }

  expTimeElapsed += timeElapsed;
  bool registerExists = registerList->foundRegister(ID);

  if (registerExists) { //register already exists

    cout << "Error: register "<<ID<< " is already open." << endl; //print error message
    return;

  } else { //doesn't exist. open the register

    Register* newRegister = new Register(ID, secPerItem, setupTime, expTimeElapsed);
    registerList->enqueue(newRegister);
    cout << "Opened register "<<ID<<endl;

    if (mode == "single") { //adding a customer as we open the register

      newRegister->get_queue_list()->enqueue(singleQueue->get_head());
      Customer* bungus = singleQueue->dequeue();

    }

  }
  // Check if the register is already open
  // If it's open, print an error message
  // Otherwise, open the register
  // If we were simulating a single queue, 
  // and there were customers in line, then 
  // assign a customer to the new register
  
}

void closeRegister(stringstream &lineStream, string mode) {
  int ID;
  double timeElapsed;
  // convert string to int
  if (!getInt(lineStream, ID) || !getDouble(lineStream, timeElapsed)) {
    cout << "Error: too few arguments." << endl;
    return;
  }
  if (foundMoreArgs(lineStream)) {
    cout << "Error: too many arguments" << endl;
    return;
  }

  // Check if the register is open
  bool foundRegister = registerList->foundRegister(ID);

  if (foundRegister) { //if register exists

    //dequeue register & free its memory
    Register* dequeued = registerList->dequeue(ID);
    delete dequeued;

  } else { //register doesn't exist

    //print error message
    cout << "Error: register "<<ID << " is not open" << endl;

  }

}

bool getInt(stringstream &lineStream, int &iValue) {
  // Reads an int from the command line
  string command;
  lineStream >> command;
  if (lineStream.fail()) {
    return false;
  }
  iValue = stoi(command);
  return true;
}

bool getDouble(stringstream &lineStream, double &dvalue) {
  // Reads a double from the command line
  string command;
  lineStream >> command;
  if (lineStream.fail()) {
    return false;
  }
  dvalue = stod(command);
  return true;
}

bool foundMoreArgs(stringstream &lineStream) {
  string command;
  lineStream >> command;
  if (lineStream.fail()) {
    return false;
  } else {
    return true;
  }
}
