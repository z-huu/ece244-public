#include <iostream>
using namespace std;

//Note: 
//May not be able to actually run this code as the key generator is not given. Maybe
//make our own?

/*
    Given the following:
    class ListNode implementation
    class LinkedList implementation (with the following functions)

        constructor
        bool is_empty()
        void insert(ListNode* node)
        ListNode* remove(const string&name);
        bool find(const string& name);
        ListNode* pop_head();
        destructor
    
    int_string_hash(const string& name); --- generates key for vtuber name, implementation
                                             not shown
                                             
    class HashTable declaration

        constructor, destructor
        bool exist(const string& name) implementation given
        bool insert(const string& name) not implemented
        bool remove(const string& name) not implemented
        bool change_name(const string& old_name, const string& new_name) not implemented

*/

int string_hash(const string& name);

#define INIT_CAPACITY 32
class HashTable {
 private:
  // Array of Linked List: resolving collisions by chaining
  LinkedList** table;
  // The length of the table array,
  int table_slot_size;
  // Keep track of how many elements (names) are in the hash table
  int num_elements;
  int get_hash_index(const string& name) {
    return string_hash(name) % table_slot_size;
  }

 public:
  // Constructors and destructors.
  HashTable();
  ~HashTable();
  // Hash table method,
  bool exist(const string& name);
  bool insert(const string& name);
  bool remove(const string& name);
  bool change_name(const string& old_name, const string& new_name);
};

class ListNode {
 public:
  ListNode(const string& name_) {
    name = name_;
    next = NULL;
  };
  string name;
  ListNode* next;
};

class LinkedList {
 private:
  ListNode* head;

 public:
  // Default constructor: initialize the head to NULL.
  LinkedList();

  // Return true if and only if the list is empty,
  bool is_empty();

  // Insert the given node to the head of the list.
  // Time complexity: 0(1)
  void insert(ListNode* node);

  // Traversing from the head. Remove the first node found with the given
  // name from the list. The removed node is NOT deallocated.
  // Returns this node (or NULL if the name is not found).
  // Time complexity: 0(n)
  ListNode* remove(const string& name);

  // Return true if there exists at least one node with the given name.
  // Time complexity: 0(n)
  bool find(const string& name);

  // Remove the current head node from the linked list,
  // and return it.
  // Move the head one node forward.
  // Time complexity: 0(1)
  ListNode* pop_head();

  // Destructor: Properly deallocate all the nodes.
  ~LinkedList();
};

HashTable::HashTable() {
  table = new LinkedList*[INIT_CAPACITY];
  table_slot_size = INIT_CAPACITY;
  num_elements = 0;
  for (int i = 0; i < table_slot_size; ++i) {
    table[i] = NULL;
  }
}
bool HashTable::exist(const string& name) {
  int idx = this->get_hash_index(name);
  if (table[idx] == NULL) {
    return false;
  }
  return table[idx]->find(name);
}

/* Q1: Implement the insert() method of the hash table.

    The insert should fulfill the following requirements:

    You should maintain the unique name property. If the name already exists in the 
    hash table, you should return false. Otherwise, allocate a list node for the 
    string and insert it into the correct list, and return true.

    To address the collision, your hashtable should dynamically grow at run time. 
    Specifically, when you try to insert a new name but the value of num_elements 
    will become equal to or larger than table_slot_size/2, you should double table_slot_size and allocate a new table with the updated size. Then, you should move all the existing names from the old table to the newly allocated table, and deallocate the old table. Notice that the hash index is directly related to the table_slot_size, so the hash index of the same name can be changed when moving from one table to another.

    You can add additional member functions if you need to.

    Your code should not trigger any segmentation fault, and it should not leak memory. 
    You can define helper functions if you find them useful. You can make helpers 
    as member functions if you think that would be necessary.

*/

bool HashTable::insert(const string& name) { //Function for Q1 submission

  //Given a vTuber name, write a function to insert it into the HashTable maintaining
  //a list of all currently streaming vtubers.

  //Check if name already exists.
  if (exist(name)) { //If name exists
    return false;
  }

  /////////////CORRECTION: should be this->exist(name)

  //Past this point, we are inserting because the name doesn't exist.

  //Checking if inserting will require new table (doubling of table_slot_size)
  if (num_elements+1 >= table_slot_size/2) { //Perfect. well done
    
    //Double table_slot_size.
    table_slot_size = table_slot_size*2; //Nice

    //Allocate a new table with the updated size.
    LinkedList** newTable = new LinkedList*[table_slot_size]; //great

    for (int i = 0; i < table_slot_size; i++) {
      newTable[i] = NULL;
    } //Nice

    //Move all names from the old table to the new table.
    //Deallocate the old table.


    ///////////CORRECTION: This whole loop is pretty incorrect.
    for (int i = 0; i < num_elements; i++) { //Incorrect for loop condition as well
      //move key index (LinkedList*) to newTable, then deallocate old table index. AMAZINGNESS
      table[i] = newTable[i]; //We don't have accessors for names in the key indices
      //^^^ Probably illegal because we haven't defined a copy constructor for our LinkedList class.
      delete table[i];
    }

    //The solution provided:
    /*

      for (int i = 0; i < table_slot_size/2 ; i++) {
        if (table[i] != NULL) { $$$If there are nodes (vTubers) with the current key$$$
          ListNode* temp = table[i]->pop_head();
          while (temp != NULL) {
            int idx = get_hash_index(n->name);
              if (newTable[idx] == NULL) {
                newTable[idx] = newLinkedList;
              }
            newTable[idx]->insert(temp);
            n = table[i]->pop_head();
          }
        } //end if
      }
    
    tldr; we forgot to check if key indices were NULL and didn't really think of an
    algorithm to bring old names to new Table using the given LinkedList functions.

    */

    delete table; //////////CORRECTION: incorrect syntax. should be delete[] table 
    table = newTable; //Good

  }

  //Allocate a list node for the string.
  ListNode* toInsert = new ListNode(name); //good
  //Insert the node.

  ////CORRECTION: Forgot to check if the key index is NULL.
  /*

    if (table[idx] == NULL) table[idx] = new LinkedList;
  
  */
  int idx = this->get_hash_index(name); //Good
  table[idx]->insert(toInsert); //Good
  num_elements++; //Good

  return true; //Good

}

/*Q2 -  Implement the remove method. Return true if the given name exists 
        and is successfully removed, otherwise, return false. Your code should not 
        trigger any segmentation fault, and it should not leak memory.
*/

bool HashTable::remove (const string& name) { //Perfect!
  //Check if name exists in hashtable.

  if (this->exist(name) == false) { //If the name DNE
    return false;
  }

  //Delete the node
  int idx = this->get_hash_index(name);
  ListNode* toDelete = table[idx]->remove(name);
  delete toDelete;

  num_elements--;

  return true;

}

// Q3 - Implement the change_name method. It removes the old_name and inserts 
// the new_name. Return true if successful. Otherwise, it returns false either when 
// the old_name doesn’t exist, or the new_name is the same as any existing name. 
// Your code should not trigger any segmentation fault, and it should not leak memory. 
// Hint: you can use the function you implemented in the previous questions.

bool HashTable::change_name(const string& old_name, const string& new_name) { //Should be perfect.

  //Check if old_name DNE
  //Check if new_name already exists

  if (this->exist(old_name) == false) return false;
  if (this->exist(new_name) == true) return false;

  //Deleting old name.
  int idx = this->get_hash_index(old_name);
  ListNode* removed = table[idx]->remove(old_name);
  delete removed;

  //Inserting new name.
  ListNode* toInsert = new ListNode(new_name);
  idx = this->get_hash_index(new_name);
  table[idx]->insert(toInsert);

  return true;
}

// Q4 - Implement the destructor of HashTable. It should deallocate the table
// array and all the lists. Your code should not trigger any segmentation fault, 
// and it should not leak memory.

HashTable::~HashTable() { //Perfect!

  for (int i = 0; i < table_slot_size; i++) {
    if (table[i] != NULL) delete table[i];
  }

  delete[] table;

}