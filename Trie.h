// The declaration of the trie class

#include <iostream>
#include <string>
#include <vector>

using namespace std;

#ifndef TRIE_H
#define TRIE_H

struct node{
	string label;
	vector<node*>* childlist;
	bool is_leaf;
	bool is_word;
};

class Trie{
private:
	node* root;
	int size;
	node* constructor_helper(const node*);
	void destructor_helper(node*);
	int get_common(string, string);
public:
	Trie();
	Trie(const Trie&);
	bool find(string);
	void insert(string);
	const node* get_root() const;
	int get_size() const;
	~Trie();
};

#endif