// This file contains the definitions of the functions of the Spelling_checker class

#include <iostream>
#include <fstream>
#include <cctype>
#include "Spelling_checker.h"

using namespace std;

// This is the constructor which takes in a string which is the name of the file containing the dictionary and constructs a 
// spelling checker object. The dictionary should have its first line as the number of words in the dictionary. The size of
// the hash table is the number of words in the dictionary.
Spelling_checker::Spelling_checker(string dictionary_name){
	ifstream file;
	file.open(dictionary_name.c_str());
	int size;
	file >> size;
	dictionary = new Hash_table(size);
	string word;
	while(file >> word){
		word = to_lowercase(word);
		dictionary->insert(word);
	}
	file.close();
	wrong_words = new Hash_table(100);
}

// This is the copy constructor which takes another object and constructs a new object having the same contents as the object 
// taken as argument.
Spelling_checker::Spelling_checker(const Spelling_checker &another_checker){
	const Hash_table* dictionary2 = another_checker.get_dictionary();
	dictionary = new Hash_table(*dictionary2);
	wrong_words = new Hash_table(100);
}


// This function returns the pointer to the hash table storing the dictionary words.
const Hash_table* Spelling_checker::get_dictionary() const{
	return dictionary;
}

// This function takes in a string and changes all the letters in the string to lowercase and returns the string in lowercase.
string Spelling_checker::to_lowercase(string word){
	int i = 0;
	while(i < word.size()){
		if(!islower(word[i]))
			word[i] = tolower(word[i]);
		++i;
	}
	return word;
}

// This function takes in the name of a file and checks the words in the file for spelling errors. If there any words with 
// spelling errors, then it stores those words in the hash table meant for it.
void Spelling_checker::check(string filename){
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
		if(!dictionary->find(word))
			wrong_words->insert(word);
	}
}

// This function prints the words with spelling errors found in the file checked. These words are stored in a private member.
void Spelling_checker::print_errors(){
	if(!wrong_words->get_size())
		cout << "There are no errors in this file." << endl;
	else{
		cout << endl << "The errors in the file are : " << endl;
		int i = 0;
		const vector<vector<string>* >* file = wrong_words->get_table();
		while(i < file->size()){
			vector<string>* second = (*file)[i];
			int j = 0;
			while(j < second->size()){
				if((*second)[j] != "")
					cout << (*second)[j] << endl;
				++j;
			}
			++i;
		}
	}
}

// This function suggests new words in place of words with spelling errors. For each word with spelling error(the words are stored
// in a private member), this function prints new words obtained by adding a new alphabet to the word or removing an alphabet 
// from the word or exchanging two adjacent letters in the word.
void Spelling_checker::suggest_words(){
	if(!wrong_words->get_size())
		cout << "There are no suggestions since there are no errors." << endl;
	else{
		cout << endl << "The suggestions are : " << endl;
		int i = 0;
		const vector<vector<string>* >* file = wrong_words->get_table();
		while(i < file->size()){
			vector<string>* second = (*file)[i];
			int a = 0;
			while(a < second->size()){
				if((*second)[a] != ""){
					string word = (*second)[a];
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
				}
				++a;
			}
			++i;
		}
	}
}


// This is the destructor which frees the memory allocated dynamically while constructing the object.
Spelling_checker::~Spelling_checker(){
	delete dictionary;
	delete wrong_words;	
}