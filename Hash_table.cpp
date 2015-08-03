// This file contains the definition of the functions of the Hash_table class

#include <iostream>
#include "Hash_table.h"

using namespace std;

// This is the constructor which takes in the size of the table to be created and creates a hash table of that size. 
Hash_table::Hash_table(int size){

}

// This is the copy constructor which takes in an object of the class and constructs a new object with the same contents of the 
// object passed as argument.
Hash_table::Hash_table(const Hash_table &another_table){

}

// This function returns the pointer to the vector which contains the words stored in the hash table. Since the vector returned 
// is a private member, it is returned as const.
const vector<string>* Hash_table::get_table() const{
	return new vector<string>();
}

// This function takes in a string and inserts the same into the hash table. If required, it re-sizes the hash table and inserts 
// the word. 
void Hash_table::insert(string word){

}

// This function takes in a string and returns the hashing value for the same according to a hash function used by it. 
int Hash_table::hash_function(string word){
	return 0;
}

// This function takes in a string and returns whether the string is present in the hash table or not.
bool Hash_table::find(string word){
	return true;
}

// This function takes in a string and removes the string from the hash table if it is present in the hash table. If required, it 
// also reduces the size of the hash table.
void Hash_table::remove(string word){

}

// This is the destructor which frees the memory dynamically allocated while constructing the object.
Hash_table::~Hash_table(){

}