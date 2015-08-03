// This file contains the definitions of the functions of the Spelling_checker class

#include <iostream>
#include <fstream>
#include "Spelling_checker.h"

using namespace std;

// This is the constructor which takes in a string which is the name of the file containing the dictionary and constructs a 
// spelling checker object.
Spelling_checker::Spelling_checker(string dictionary_name){

}

// This is the copy constructor which takes another object and constructs a new object having the same contents as the object 
// taken as argument.
Spelling_checker::Spelling_checker(const Spelling_checker &another_checker){

}

// This function returns the pointer to the hash table storing the dictionary words.
const Hash_table* Spelling_checker::get_dictionary() const{
	return dictionary;
}

// This function takes in the name of a file and checks the words in the file for spelling errors. If there any words with 
// spelling errors, then it stores those words in the hash table meant for it.
void Spelling_checker::check(string filename){

}

// This function prints the words with spelling errors found in the file checked. These words are stored in a private member.
void Spelling_checker::print_errors(){

}

// This function suggests new words in place of words with spelling errors. For each word with spelling error(the words are stored
// in a private member), this function prints new words obtained by adding a new alphabet to the word or removing an alphabet 
// from the word or exchanging two adjacent letters in the word.
void Spelling_checker::suggest_words(){

}

// This is the destructor which frees the memory allocated dynamically while constructing the object.
Spelling_checker::~Spelling_checker(){

}