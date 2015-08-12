// This file contains the definitions of the functions of the Spelling_check class. This class uses a trie.

#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>
#include "Spelling_check.h"

using namespace std;

// This is the constructor which takes in a string which is the name of the file containing the dictionary and constructs a 
// spelling_check object. The time taken is O(nm) where nis the number of words in the dictionary and m is the length of the 
// longest word.
Spelling_check::Spelling_check(string dictionary_name){
	ifstream file;
	file.open(dictionary_name.c_str());
	dictionary = new Trie();
	string word;
	while(file >> word){
		word = to_lowercase(word);
		dictionary->insert(word);
	}
	file.close();
}


// This is the copy constructor which takes another object and constructs a new object having the same contents as the object 
// taken as argument.
Spelling_check::Spelling_check(const Spelling_check &another_checker){
	const Trie* dictionary2 = another_checker.get_dictionary();
	dictionary = new Trie(*dictionary2);
}


// This function returns the pointer to the hash table storing the dictionary words.
const Trie* Spelling_check::get_dictionary() const{
	return dictionary;
}


// This function takes in a string and changes all the letters in the string to lowercase and returns the string in lowercase.
string Spelling_check::to_lowercase(string word){
	int i = 0;
	while(i < word.size()){
		if(!islower(word[i]))
			word[i] = tolower(word[i]);
		++i;
	}
	return word;
}


// This function takes in the name of a file and checks the words in the file for spelling_checking errors. If there any words with 
// spelling_checking errors, then it stores those words in the hash table meant for it.
void Spelling_check::check(string filename){
	wrong_words = new vector<string>();
	ifstream file;
	file.open(filename.c_str());
	string word;
	while(file >> word){
		word = to_lowercase(word);
		// If there any symbols like .,"{( at the end of the word, then remove it.
		if((word[word.size()-1] >= 33 && word[word.size()-1] <= 47) || (word[word.size()-1] >= 58 && word[word.size()-1] <= 63) ||
		 (word[word.size()-1] >= 91 && word[word.size()-1] <= 96) || (word[word.size()-1] >= 123 && word[word.size()-1] <= 126)){
			word.erase(word.end() - 1);
			// If the word originally contained two symbols at the end of it (like the word wished." ), removing the symbols.
			if((word[word.size()-1] >= 33 && word[word.size()-1] <= 47) || (word[word.size()-1] >= 58 && word[word.size()-1] <= 63) ||
		 	(word[word.size()-1] >= 91 && word[word.size()-1] <= 96) || (word[word.size()-1] >= 123 && word[word.size()-1] <= 126))
				word.erase(word.end() - 1);
		}
		// If the word contained any symbols at the beginning of the word, removing it.
		if((word[0] >= 33 && word[0] <= 47) || (word[0] >= 58 && word[0] <= 63) ||(word[0] >= 91 && word[0] <= 96) || (word[0] >= 123 && word[0] <= 126)){
			word.erase(word.begin());
			if((word[0] >= 33 && word[0] <= 47) || (word[0] >= 58 && word[0] <= 63) ||(word[0] >= 91 && word[0] <= 96) || (word[0] >= 123 && word[0] <= 126))
				word.erase(word.begin());
		}
		if(word.size() > 0 && word != " " && !dictionary->find(word)){
			wrong_words->insert(wrong_words->end() ,word);
		}
	}
}


// This function prints the words with spelling errors found in the file checked. 
void Spelling_check::print_errors(){
	if(!wrong_words->size())
		cout << "There are no errors in this file." << endl;
	else{
		cout << endl << "The errors in the file are : " << endl;
		int i = 0;
		while(i < wrong_words->size()){
			cout << (*wrong_words)[i] << endl;
			++i;
		}
	}
}


// This function suggests new words in place of words with spelling errors. For each word with spelling error(the words are stored
// in a private member), this function prints new words obtained by adding a new alphabet to the word or removing an alphabet 
// from the word or exchanging two adjacent letters in the word.
void Spelling_check::suggest_words(){
	if(!wrong_words->size())
		cout << "There are no suggestions since there are no errors." << endl;
	else{
		cout << endl << "The suggestions are : " << endl;
		int i = 0;
		while(i < wrong_words->size()){
			string word = (*wrong_words)[i];
			cout << endl << "For the word : " << word << endl;
			int j = 0;
			char letter;
			string new_word;
			cout << "Possible words are : ";
			// Possible words by removing a letter.
			while(j < word.size()){
				new_word = word;
				new_word.erase(new_word.begin() + j);
				if(dictionary->find(new_word))
					cout << new_word << " , ";
				++j;
			}
			// Possible words by adding a letter.
			j = 0;
			while(j <= word.size()){
				letter = 'a';
				while(letter < 123){
					new_word = word;
					new_word.insert(new_word.begin() + j, letter);
					if(dictionary->find(new_word))
						cout << new_word << " , ";
					++letter;
				}
				++j;
			}
			// Possible words by exchanging two adjacent letters
			j = 0;
			while(j < word.size() - 1){
				new_word = word;
				letter = new_word[j];
				new_word[j] = new_word[j+1];
				new_word[j+1] = letter;
				if(dictionary->find(new_word))
					cout << new_word << " , ";
				++j;
			}
			// Possible words by replacing a letter with another letter.
			j = 0;
			while(j < word.size()){
				new_word = word;
				letter = 'a';
				while(letter < 123){
					new_word = word;
					if(new_word[j] != letter){
						new_word[j] = letter;
						if(dictionary->find(new_word))
							cout << new_word << " , ";
					}
					++letter;
				}
				++j;
			}
			cout << endl;
			++i;
		}
	}
}


// This is the destructor which frees the memory allocated dynamically while constructing the object.
Spelling_check::~Spelling_check(){
	delete dictionary;
	delete wrong_words;	
}