// This is the declaration of the hash table class

#include <iostream>
#include <vector>
#include <string>

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

using namespace std;

class Hash_table{
private:
	vector<string>* table;
	int size;
	int max_hash_value;
public:
	Hash_table(int);
	Hash_table(const Hash_table&);
	const vector<string>* get_table() const;
	void insert(string);
	int hash_function(string);
	bool find(string);
	void remove(string);
	~Hash_table();
};

#endif