// This is the declaration of the hash table class

#include <iostream>
#include <vector>
#include <string>

#ifndef HASH_TABLE_H
#define HASH_TABLE_H

using namespace std;

class Hash_table{
private:
	vector<vector<string>* >* table;
	int size;
public:
	Hash_table(int);
	Hash_table(const Hash_table&);
	const vector<vector<string>* >* get_table() const;
	int get_size() const;
	void insert(string);
	int hash_function(string);
	int hash_function2(string);
	bool find(string);
	~Hash_table();
};

#endif