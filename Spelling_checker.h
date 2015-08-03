// The declaration of spelling checker class

#include <iostream>
#include <string>
#include "Hash_table.h"

#ifndef SPELLING_CHECKER_H
#define SPELLING_CHECKER_H

using namespace std;

class Spelling_checker{
private:
	Hash_table* dictionary;
	Hash_table* wrong_words;
public:
	Spelling_checker(string);
	Spelling_checker(const Spelling_checker&);
	void check(string);
	void print_errors();
	void suggest_words();
	~Spelling_checker();
};

#endif