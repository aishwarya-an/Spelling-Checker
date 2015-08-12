**Spelling checker**  
===============  

Checks the spelling of words in a file and suggests new words in case of spelling errors.  

---  

### **Introduction :** ###
A spelling checker basically takes in a file as input and checks the spelling of the words in the file. The operations performed by this library are :  
1. Checking the spelling of the words in the file.  
2. Printing the words with spelling errors.  
3. In case of spelling errors, suggesting new words obtained by adding a new alphabet to the word or removing an alphabet from the word or exchanging two adjacent letters in the word or replacing a letter in the word by another letter.  

---  

### **Description of the interface :** ###
This library will use a class to represent spelling checkers as objects. The functions offered by this class are :  
  1. *spelling_checker(string dictionary_name);*  
  This is the constructor of the class which constructs an object of the spelling checker class. The parameter passed is the filename which contains the dictionary of words. Its running time is O(n) where n is the number of words in the dictionary.  
  2. *void check(string filename);*  
  This function takes in a filename as argument and checks the spelling of the words in the file. It then stores the words with wrong spelling in a private member. Its running time is O(n) where n is the number of words in the file.  
  3. *void print_errors();*  
  This function prints the errors found in the file which is passed as an argument to the check() function. The errors are stored in a private member and this function just prints those words. Its running time is O(n) where n is the number of words in the file.  
  4. *void suggest_words();*  
  This function suggests new words for each word with spelling error. For each word with spelling error, the new words are obtained by adding a new alphabet to the word or removing an alphabet from the word or exchanging two adjacent letters in the word. Its running time is O(mk) where m is the number of words with wrong spelling and k is the length of the longest word.  
  5. *~spelling_checker();*  
  This is the destructor which frees the memory dynamically allocated while constructing the object.  

---  

### **Description of internal implementation :** ###
The spelling checker has been implemented using both hash tables and tries(radix trees). The class which uses the hash table data structure is called Spelling_checker class. The class which uses the trie is called the Spelling_check class.  

*The description of the internal implementation of the Spelling_checker class is as follows :*  
The data structures used are hash tables. A hash table is used to store the words from the dictionary. Another hash table is used to store the words (of the file checked) with spelling errors. A proper hash function is used to store the words from the dictionary in the hash table such that accessing the words can be done in O(1) time. The hash table implemented uses perfect hashing i.e it uses a secondary hash table for each slot in the hash table. This will reduce the number of collisions and most importantly will reduce the time to access a word to O(1) time in the worst case.  

*The description of the internal implementation of the Spelling_check class is as follows :*  
The data structure used is radix tree(or compressed trie) and vectors. A trie is used to store the words from the dictionary and the vector is used to store the wrong words from the file checked. The space used by the trie is O(nl) where n is the number of words in the dictionary and l is the length of the longest word in the dictionary. The time to insert a word into the trie is O(m) where m is the length of the word inserted and so the time to insert all the words from the dictionary is O(nl) where n is the number of words and l is the length of the longest word. The running time to access a word is O(l) where l is the length of the longest word. Therefore, the time to access a word in the trie can be said to be O(1).  

### **Design decisions and their reasons :** ###
1.Hash table is used to store the words from the dictionary because accessing the words become easier and can be done in O(1) time if a proper hash function is used which addresses the collision problem as well. 
Since the hash table uses perfect hashing, the space used will be O(n) when the size of the secondary hash table is chosen such that it is the square of the number of words stored in it. In case of other structures like vectors the memory used is the same as that of hash table i.e )(n). But, the added advantage of using hash table is the time required to access the words stored.  
Also, if a binary search tree is used to store the words from the dictionary, the memory used will be the same as that of hash table. But, the time required for access of a single word is O(log n) where n is the number of words in the dictionary. So, hash table is suitable considering both space and time complexity.   
2. The structure used to store the words with spelling errors is also a hash table. This is because, if the words with spelling errors are repeated in the file many times it becomes easier to store the words only once. In case of other structures such as vectors, it takes O(n) time, where n is the number of words with spelling errors to check whether a word is already stored in the vector. So, totally it takes O(n^2) time, to store all such words. But, in case of hash tables, O(1) time is required to know whether a particular word has already been stored. So, it takes O(n) time to store all the words and there will not be any repetitons. 