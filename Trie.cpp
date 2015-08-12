// This is the definition file of the Trie class

#include <iostream>
#include "Trie.h"

using namespace std;

// This is the constructor of the Trie class which constructs an empty trie.
Trie::Trie(){
	root = new node();
	root->label = "";
	root->is_word = false;
	root->is_leaf = false;
	root->childlist = new vector<node*>();
	size = 0;
}


// This is the copy constructor of the trie class which takes in an object of the trie class and creates another object by copying
// the contents from the first object.
Trie::Trie(const Trie &another){
	size = another.get_size();
	const node* root2 = another.get_root();
	root = constructor_helper(root2);
}


// This is a private function which helps the copy constructor to copy the contents from one object into another. It takes
// a node and copies its contents into a newly created node and recursively calls itself with the nodes of the childlist
// of the current code taken as argument.
node* Trie::constructor_helper(const node* Node){
	node* new_node = new node();
	new_node->label = Node->label;
	new_node->is_word = Node->is_word;
	new_node->is_leaf = Node->is_leaf;
	if(!new_node->is_leaf){
		new_node->childlist = new vector<node*>(Node->childlist->size());
		int i = 0;
		while(i < new_node->childlist->size()){
			(*new_node->childlist)[i] = constructor_helper((*Node->childlist)[i]);
			++i;
		}
	}
	return new_node;
}



// This function takes in a string and returns whether the same is present in the trie or not in O(m) time where m is the length
// of the word.
bool Trie::find(string word){
	node* current = root;
	string remaining = word; 												// it stores the part of the word yet to be searched
	// While current node is not a leaf and the size of the part of the word to be searched is not 0.
	while(!current->is_leaf && remaining.size() != 0){
		int i = 0;
		int elements = current->childlist->size();
		while(i < current->childlist->size()){
			vector<node*>* children = current->childlist;
			string prefix = (*children)[i]->label;
			// If the label of the node in the childlist is a prefix in the word to be searched
			if(prefix.size() <= remaining.size() && remaining.substr(0, prefix.size()) == prefix){
				// Erase the prefix from the word and search for the rest of the word.
				remaining.erase(remaining.begin(), remaining.begin() + prefix.size());
				current = (*children)[i];
				break;
			}
			++i;
		}
		// If there is no word in the childlist which is a prefix of the word to be searched, then return false.
		if(i == elements)
			return false;
	}
	return (current->is_word && remaining.size() == 0);
}



// This function takes in a string and inserts the same into the trie object. Its running time is O(m) where m is the length 
// of the word inserted.
void Trie::insert(string word){
	++size;
	// size stores the number of words in the trie.
	node* current = root;
	string remaining = word;
	while(!current->is_leaf && remaining.size() != 0){
		int i = 0;
		int elements = current->childlist->size();
		// Searching the childlist of the current node for a prefix of the word to be inserted. If a prefix if found then
		// the function will go further in the path until the prefix of the word to be inserted cannot be found. At that
		// point it will insert that part of the word in the childlist of the last node in the path followed by it.

		while(i < current->childlist->size()){
			vector<node*>* children = current->childlist;
			string prefix = (*children)[i]->label;
			if(remaining[0] == prefix[0]){
				int common = get_common(remaining, prefix);
				// If the whole label is a prefix of the word to be inserted.
				if(common == prefix.size()){
					current = (*children)[i];
					remaining.erase(remaining.begin(), remaining.begin() + common);
					// If the whole word is present, then change its is_word status.
					if(remaining.size() == 0){
						if(current->is_word)
							--size;
						current->is_word = true;
						return;
					}
					break;
				}

				// If the whole label is not a prefix of the word to be inserted, then split the label to the point it is 
				// a prefix of the word. Create a new label which has the remaining part of the label and make the childlist
				// of the splitted label as the childlist of the new node created. Then insert both the word and new node
				// into the childlist of the splitted label node.
				remaining.erase(remaining.begin(), remaining.begin() + common);
				// This new_node is the remaining part of the splitted label.
				node* new_node = new node();
				new_node->label = prefix.substr(common, prefix.size() - common);
				if(!(*children)[i]->is_leaf){
					new_node->childlist = (*children)[i]->childlist;
					new_node->is_leaf = false;
				}
				else
					new_node->is_leaf = true;
				new_node->is_word = (*children)[i]->is_word;
				// This new_word node is the node of the word to be inserted.
				node* new_word = new node();
				new_word->label = remaining;
				new_word->is_word = true;
				new_word->is_leaf = true;
				// Creating a new childlist for the splitted labl node.
				children = new vector<node*>();
				children->insert(children->end(), new_word);
				children->insert(children->end(), new_node);
				(*current->childlist)[i]->childlist = children;
				(*current->childlist)[i]->is_word = false;
				// Splitting the labl
				(*current->childlist)[i]->label.erase((*current->childlist)[i]->label.begin() + common, (*current->childlist)[i]->label.end());
				(*current->childlist)[i]->is_leaf = false;
				return;
			}
			++i;
		}

		// If the current node is a leaf and there is still some part remaining in the word, then create a new childlist
		// for the current node and insert the remaining part into the childlist. 
		if(remaining.size() != 0 && current->is_leaf){
			current->childlist = new vector<node*>();
			node* new_node = new node();
			new_node->label = remaining;
			new_node->is_leaf = true;
			new_node->is_word = true;
			current->childlist->insert(current->childlist->end(), new_node);
			current->is_leaf = false;
			current->is_word = true;
			return;
		}

		// Else if, there is no label in the childlist which is a prefix of the word to be inserted, then insert the remaining
		// part of the word into the childlist.
		if(remaining.size() != 0 && i == elements){
			node* new_node = new node();
			new_node->label = remaining;
			new_node->is_leaf = true;
			new_node->is_word = true;
			current->childlist->insert(current->childlist->end(), new_node);
			return;
		}
	}
}



// This is a private function used by the insert function. It takes in two words and returns the length of the prefix which
// is common in both words.
int Trie::get_common(string word1, string word2){
	int i = 0;
	while(i < word1.size() && i < word2.size()){
		if(word1[i] != word2[i])
			break;
		++i;
	}
	return i;
}


// This function returns the root of the trie.
const node* Trie::get_root() const{
	return root;
}


// This function returns the number of words in the trie.
int Trie::get_size() const{
	return size;
}


// This is the destructor which frees the memory dynamically allocated during the insertion of words into the trie.
Trie::~Trie(){
	destructor_helper(root);
}


// This is a private function used by destructor of the class. It takes in a node and first recursively calls itself
// on the nodes of the childlist of the current node to free their memory and then frees the memory allocated for the current node.
void Trie::destructor_helper(node* Node){
	if(!Node->is_leaf){
		int i = 0;
		while(i < root->childlist->size()){
			destructor_helper((*Node->childlist)[i]);
			++i;
		}
		delete Node->childlist;
	}
	delete Node;
}