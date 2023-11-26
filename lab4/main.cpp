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

void queueCustomers(QueueList* singleQueue );

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

    if (mode == "single") { //BEGIN SINGLE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

      //New code skeleton

      // Update the system.
        //Depart all departable customers, queue customers into free registers
          //Condition for departable customers
            //  if (register)->get_queue_list()->get_head()->get_departureTime()
            //  <= expTimeElapsed
          //Condition for customers to queue
            //  if singleQueue->get_head() != NULL     if there is at least one customer in q
        //Repeat until no more departable customers, or no more customers to queue.

      Register* handler;
      Register* scanner = registerList->get_head();
      Register* toQueue;
      bool queuable = true;
      bool departable = true;
      //Outer while loop, to update the system
      while (queuable||departable) {
        cout << "The outer loop runs again! Debug in outer loop."<<endl;
        //Updating queuable and departable conditions. Note: they're set to true
        //every time a command is input.
          if (singleQueue->get_head()==NULL) queuable = false; //If no customers
          if (registerList->get_free_register() == NULL) queuable = false; //If all registers occupied.

          if (  (registerList->get_head() == NULL)||(registerList
                  ->calculateMinDepartTimeRegister(0) == nullptr) ) {
              //There are no registers currently, or ALL registers are free
              departable = false;
          } else {
              
            //Scan over the register list to see if there are any customers
            //whose departure times are smaller than expTimeElapsed.
            while (scanner !=NULL) {
              if (scanner->get_queue_list()->get_head() == NULL) { 
                //Scanner lands on an unoccupied register
                //Send the scanner to the next reg. Looking for registers WITH customers.
                scanner = scanner->get_next();

              } else if (scanner->get_queue_list()->get_head()->get_departureTime() <= expTimeElapsed) {
                departable = true; break;
                //If we find a customer who should be departed, break out of the loop.
              } else {
                scanner = scanner->get_next();
              }

              //If we reach the end of the regList and we are still in the loop, there
              //are no departable customers.
              if (scanner == NULL) {
                departable = false;
              }

            } //end scanner while
          }
        //End of updating queuable and departable.

          //Queuing customers into free registers
          if (queuable) {

            //Sets the register of interest to the first free one.
            //First referring to closest to the head of the registerList.

            toQueue = registerList->get_free_register();
            toQueue->get_queue_list()->enqueue(singleQueue->dequeue());

            //Dequeues a customer from the singleQueue and queues it in the
            //register of interest.

            //Output message.
            cout << "Queued a customer with free register "<< toQueue->get_ID() << endl;
            
            //Set the customer's departure time. 
            toQueue->get_queue_list()->get_head()->set_departureTime
            ( toQueue->calculateDepartTime()  );

            cout << "Finish queuing a customer! Debug message at end of queuable."<<endl;
          } //End queuable.

          //Departing customers from the registers
          if (departable) {

            //End of scanning
            //At this point, we've scanned and departable has been updated.
            //Begin departing customers in order of departure time.
            
              //Sends handler to the register with the smallest departure time.
              //We can assume handler is NOT nullptr as we have scanned and saw that
              //there are departable customers (nullptr is if all registers are free)

              handler = registerList->calculateMinDepartTimeRegister(0);
              //Departure message.
                cout << "Departed a customer at register ID "<<handler->get_ID()<<" at "
                << handler->get_queue_list()->get_head()->get_departureTime()<<endl;

              //Now that handler is pointing to a register, start departing.
              cout << "Departing a customer now! Debug message in departable."<<endl;
              handler->departCustomer(doneList);
                
              
        } //End departable.

      } //END OUTER WHILE ~~~~~~~~~~~~~~~~~

      ////////////// Debugging Processes ///////////////////////

      // Print the register list.
      bool printRegList = 0; //IF YOU WANT TO PRINT THE REGISTER LIST ~~~~~~~~~~~~~~~~~~~~~~~~~~
      if (printRegList) {

        cout <<"Printing Register List."<<endl;
        Register* printer = registerList->get_head();

        while (printer != NULL) {
          cout << "Register ID: "<<printer->get_ID() <<endl;
          printer = printer->get_next();
        }

        cout <<"End Register List"<<endl;
      }
    
    // END SINGLE ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    } else if (mode == "multiple") {

      //A code block that might be helpful for departing multiple customers at a queue
      /*

        while (handler != nullptr) { //while we haven't gone through all the registers

        handleHelper = handler->get_queue_list()->get_head();
        while (handleHelper->get_departureTime() < expTimeElapsed) { //
          
        }

      }
      
      */


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
  cout << "A customer entered"<<endl;

  if (mode == "single") { //enqueue customer in singleQueue
  
    singleQueue->enqueue(dude);
    cout <<"debug queued"<<endl;
    

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

      // Case where there's no customers to add
      if (singleQueue->get_head() != NULL) {
        
        newRegister->get_queue_list()->enqueue(singleQueue->dequeue());
        Customer* bungus = singleQueue->dequeue();

      }
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

/*
Register* handler;
      //CODE BELOW IS TO BE REDONE
      if (registerList->calculateMinDepartTimeRegister(0) == nullptr) { //all registers are free
        handler = registerList->get_head();
      } else {
        handler = registerList->calculateMinDepartTimeRegister(0);
      }

      if (handler != NULL) cout << "Register ID: " << handler->get_ID()<<endl;
 
      while ( (handler != NULL)&&(handler->get_queue_list()->get_head()!=NULL)&&(handler->get_queue_list()->get_head()->get_departureTime() <= expTimeElapsed)  ) { //while someone can still be departed
        //Dequeue all departable customers.
        cout << "Departed a customer at register ID "<<handler->get_ID()<<" at "<< handler->get_queue_list()->get_head()->get_departureTime()<<endl;
        handler->departCustomer(doneList);

        //Maybe queue up eligible customers here?
        if (singleQueue->get_head() != NULL) {
          handler->get_queue_list()->enqueue(singleQueue->dequeue());
          handler->get_queue_list()->get_head()->set_departureTime(handler->calculateDepartTime());
          cout << "Queued a customer with free register "<< handler->get_ID() << endl;
        }
        //send handler to the register with the next smallest departure time.
        handler = registerList->calculateMinDepartTimeRegister(0);
      }

      cout<<"Passed initial while loop in main (departing one)"<<endl;
      //queue customers (one deep)
      //while there is at least one free register. 
      //if multiple free registers, queue closest to head
      while ( (registerList->get_free_register() != nullptr)&&(singleQueue->get_head()!=NULL)  ) { 
        cout <<"A"<<endl;
        
        Register* queuer = registerList->get_head();
        if (  (queuer->get_queue_list()->get_head() == NULL)&&(singleQueue->get_head() != NULL) ) {
          queuer->get_queue_list()->enqueue(singleQueue->dequeue());
          cout<<"Queued a customer with free register "<<queuer->get_ID()<<endl;
          queuer->get_queue_list()->get_head()->set_departureTime(queuer->calculateDepartTime());
          break;
        } else {
          queuer = queuer->get_next();
        }
      }

*/