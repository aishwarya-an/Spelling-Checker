// This file contains the definition of the functions of the Hash_table class

/* The hash table uses perfect hashing i.e it uses a secondary hash table for each slot in the hash table. This will reduce
the number of collisions and most importantly will reduce the time to access a word to O(1) time in the worst case.
*/

#include <iostream>
#include "Hash_table.h"

using namespace std;

// This is the constructor which takes in the size of the table to be created and creates a hash table of that size. If the size
// given is less than 50, then it creates the hash table of size 50.
Hash_table::Hash_table(int num_of_elements){
	if(num_of_elements < 50)
		table = new vector<vector<string>* >(50);
	else
		table = new vector<vector<string>* >(num_of_elements + 1);
	int i = 0;
	while(i < table->size()){
		(*table)[i] = new vector<string>();
		++i;
	}
	size = 0; 												// size represents the number of elements or words in the hash table
}

// This is the copy constructor which takes in an object of the class and constructs a new object with the same contents of the 
// object passed as argument.
Hash_table::Hash_table(const Hash_table &another_table){
	const vector<vector<string>* >* table2 = another_table.get_table();
	size = another_table.get_size();
	table = new vector<vector<string>* >(*table2);
}

// This function returns the pointer to the vector which contains the words stored in the hash table. Since the vector returned 
// is a private member, it is returned as const.
const vector<vector<string>* >* Hash_table::get_table() const{
	return table;
}

// This function returns the number of elements or words present in the hash table.
int Hash_table::get_size() const{
	return size;
}


// This function takes in a string and inserts the same into the hash table. It first goes to the slot given by the 
// hash_function() and then inserts the word in the secondary hash table pointed to by the slot. If the secondary hash
// table is empty, it first creates a hash table of size 11 and then inserts the word into the secondary table.
void Hash_table::insert(string word){
	int hash_value = hash_function(word);
	int hash_value2 = hash_function2(word);
	vector<string>* current = (*table)[hash_value];
	// Resizing the secondary hash table if it is empty.
	if(current->size() == 0)
		current->resize(11, "");
	if((*current)[hash_value2] == ""){
		(*current)[hash_value2] = word;
		++size;
	}
	// If there is a collision in the secondary hash table.
	else{
		int index = hash_value2;
		while((*current)[index] != "" && (*current)[index] != word){
			++index;
			if(index >= 11)
				index = index % 11;
		}
		++size;
		(*current)[index] = word;
	}
}

// This function takes in a string and returns the hashing value for the same according to a hash function used by it. 
int Hash_table::hash_function(string word){
	int i = 0;
	int hash = 0;
	while(i < word.size()){
		int letter = word[i];
		if(letter < 0)
			letter = 0;
		hash = ((hash << 5) + hash + letter) % table->size();
		++i;
	}
	return hash;
}

// This function is another hash function used for inserting the word into the secondary hash table. It takes in the string 
// and computes the hash value and returns the same.
int Hash_table::hash_function2(string word){
	int i = 0;
	int hash = 0;
	while(i < word.size()){
		hash = ((hash * 31) + word[i]) % 11;
		++i;
	}
	return hash; 
}

// This function takes in a string and returns whether the string is present in the hash table or not.
bool Hash_table::find(string word){
	int hash_value = hash_function(word);
	// Going to the scondary hash table pointed to by the slot given by the above hash value.
	vector<string>* current = (*table)[hash_value];
	// If the secondary hash table is of size 0, then there is no such word in the dictionary.
	if(current->size() == 0)
		return false;
	// If the secondary hash table is not of size 0, then getting the slot number where the word is placed.
	int hash_value2 = hash_function2(word);
	if((*current)[hash_value2] == "")
		return false;
	else{
		int index = hash_value2;
		while((*current)[index] != "" && (*current)[index] != word){
			++index;
			if(index >= 11)
				index = index % 11;
		}
		return (*current)[index] != "";
	}
}


// This is the destructor which frees the memory dynamically allocated while constructing the object.
Hash_table::~Hash_table(){
	delete table;
}