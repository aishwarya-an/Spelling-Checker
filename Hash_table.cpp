// This file contains the definition of the functions of the Hash_table class

#include <iostream>
#include "Hash_table.h"

using namespace std;

// This is the constructor which takes in the size of the table to be created and creates a hash table of that size. If the size
// given is less than 50, then it creates the hash table of size 50.
Hash_table::Hash_table(int num_of_elements){
	if(num_of_elements < 50)
		table = new vector<string>(50, "");
	else
		table = new vector<string>(num_of_elements + 1, "");
	size = 0; 												// size represents the number of elements or words in the hash table
	max_hash_value = 0;
}

// This is the copy constructor which takes in an object of the class and constructs a new object with the same contents of the 
// object passed as argument.
Hash_table::Hash_table(const Hash_table &another_table){
	const vector<string>* table2 = another_table.get_table();
	size = another_table.get_size();
	table = new vector<string>(table2->size());
	int i = 0;
	while(i < table2->size()){
		(*table)[i] = (*table2)[i];
		++i;
	}
	max_hash_value = another_table.get_max_hash();
}

// This function returns the pointer to the vector which contains the words stored in the hash table. Since the vector returned 
// is a private member, it is returned as const.
const vector<string>* Hash_table::get_table() const{
	return table;
}

// This function returns the number of elements or words present in the hash table.
int Hash_table::get_size() const{
	return size;
}

// This function returns the maximum index which has an element in it.
int Hash_table::get_max_hash() const{
	return max_hash_value;
}

// This function takes in a string and inserts the same into the hash table. If required, it re-sizes the hash table and inserts 
// the word. 
void Hash_table::insert(string word){
	int hash_value = hash_function(word);
	// Rehashes the table if the number of elements is more than half of the size of the table.
	if(hash_value >= table->size() || size > table->size() / 2){
		table->insert(table->end(), table->size(), "");
	}
	if((*table)[hash_value] == ""){
		(*table)[hash_value] = word;
		++size;
		if(hash_value > max_hash_value)
			max_hash_value = hash_value;
	}
	else{
		int i = 0;
		int index = hash_value;
		int hash_value2 = hash_function2(word);
		// Uses the method of double hashing
		while((*table)[index] != "" && (*table)[index] != word){
			++i;
			if(hash_value + i*hash_value2 >= table->size())
				index = (hash_value + i*hash_value2) % table->size();
			else
				index = hash_value + i*hash_value2;
		}
		if((*table)[index] == ""){
			(*table)[index] = word;
			++size;
			if(index > max_hash_value)
				max_hash_value = index;
		}
	}
}

// This function takes in a string and returns the hashing value for the same according to a hash function used by it. 
int Hash_table::hash_function(string word){
	int i = 0;
	int hash = 0;
	while(i < word.size()){
		hash = ((hash * 33) + word[i]) % 37;
		++i;
	}
	return hash;
}

// This function is another hash function used for double hashing. It takes in the string and computes the hash value and 
// returns the same.
int Hash_table::hash_function2(string word){
	int i = 0;
	int hash = 0;
	while(i < word.size()){
		hash = (hash * 29) + word[i];
		++i;
	}
	return 31 - (hash % 31); 
}


// This function takes in a string and returns whether the string is present in the hash table or not.
bool Hash_table::find(string word){
	int hash_value = hash_function(word);
	if(hash_value > max_hash_value)
		return false;
	else{
		if((*table)[hash_value] == "")
			return false;
		else if((*table)[hash_value] == word)
			return true;
		else{
			int i = 0;
			int index = hash_value;
			int hash_value2 = hash_function2(word);
			while((*table)[index] != "" && (*table)[index] != word){
				++i;
				if(hash_value + i*hash_value2 >= table->size())
					index = (hash_value + i*hash_value2) % table->size();
				else
					index = hash_value + i*hash_value2;
			}
			return ((*table)[index] != "");
		}
	}
}


// This is the destructor which frees the memory dynamically allocated while constructing the object.
Hash_table::~Hash_table(){
	delete table;
}