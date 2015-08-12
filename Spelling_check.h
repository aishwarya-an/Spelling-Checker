// The declaration of spelling_checking checker class

#include <iostream>
#include <string>
#include "Trie.h"

#ifndef SPELLING_CHECK_H
#define SPELLING_CHECK_H

using namespace std;

class Spelling_check{
private:
	Trie* dictionary;
	vector<string>* wrong_words;
public:
	Spelling_check(string);
	Spelling_check(const Spelling_check&);
	const Trie* get_dictionary() const;
	string to_lowercase(string);
	void check(string);
	void print_errors();
	void suggest_words();
	~Spelling_check();
};

#endif