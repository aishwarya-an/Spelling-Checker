Spelling checker  
===============  

Checks the spelling of words in a file and suggests new words in case of spelling errors.  

---  

Introduction :  
-------------  
A spelling checker basically takes in a file as input and checks the spelling of the words in the file. The operations performed by this library are :  
1. Checking the spelling of the words in the file.  
2. Printing the words with spelling errors.  
3. In case of spelling errors, suggesting new words obtained by adding a new alphabet to the word or removing an alphabet from the word or exchanging two adjacent letters in the word or replacing a letter in the word by another letter.  

Description of the interface :  
-----------------------------  
This library will use a class to represent spelling checkers as objects. The functions offered by this class are :  
  1. spelling_checker(string dictionary_name);  
  This is the constructor of the class which constructs an object of the spelling checker class. The parameter passed is the filename which contains the dictionary of words. Its running time is O(n) where n is the number of words in the dictionary.  
  2. void check(string filename);  
  This function takes in a filename as argument and checks the spelling of the words in the file. It then stores the words with wrong spelling in a private member. Its running time is O(n) where n is the number of words in the file.  
  3. void print_errors();  
  This function prints the errors found in the file which is passed as an argument to the check() function. The errors are stored in a private member and this function just prints those words. Its running time is O(n) where n is the number of words in the file.  
  4. void suggest_words();  
  This function suggests new words for each word with spelling error. For each word with spelling error, the new words are obtained by adding a new alphabet to the word or removing an alphabet from the word or exchanging two adjacent letters in the word. Its running time is O(mk) where m is the number of words with wrong spelling and k is the length of the longest word.  
  5. ~spelling_checker();  
  This is the destructor which frees the memory dynamically allocated while constructing the object.  

Description of internal implementation :  
----------------------------------------  
The data structures used are hash tables. A hash table is used to store the words from the dictionary. Another hash table is used to store the words (of the file checked) with spelling errors. A proper hash function is used to store the words from the dictionary in the hash table such that accessing the words can be done in O(1) time. In case of collisions while inserting the words, the method of double hashing is used.  

Design decisions and their reasons :   
------------------------------------   
1.Hash table is used to store the words from the dictionary because accessing the words become easier and can be done in O(1) time if a proper hash function is used which addresses the collision problem as well.  
Double hashing is used in case of collisions because it minimizes repeated collisions and the effects of clustering. Unlike linear probing and quadratic probing, the interval depends on the data, so that even values mapping to the same location have different bucket sequences. Since, linear probing is inefficient in case of too many collisions and double hashing fails in inserting although the table has free fields, double hashing is used.  
Since, double hashing is used in case of collisions, there will not be too many free spaces in the hash table. Therefore, the memory used is theta(n) where n is the number of words in the dictionary. In case of other structures like vectors the memory used is the same as that of hash table i.e theta(n). But, the added advantage of using hash table is the time required to access the words stored.  
Also, if a binary search tree is used to store the words from the dictionary, the memory used will be the same as that of hash table. But, the time required for access of a single word is O(log n) where n is the number of words in the dictionary. So, hash table is suitable considering both space and time complexity.  
2. The structure used to store the words with spelling errors is also a hash table. This is because, if the words with spelling errors are repeated in the file many times it becomes easier to store the words only once. In case of other structures such as vectors, it takes O(n) time, where n is the number of words with spelling errors to check whether a word is already stored in the vector. So, totally it takes O(n^2) time, to store all such words. But, in case of hash tables, O(1) time is required to know whether a particular word has already been stored. So, it takes O(n) time to store all the words and there will not be any repetitons.   
2. While suggesting the new words in place of the words with spelling errors, the new words are obtained by adding a new alphabet to the word or removing an alphabet from the word or exchanging two adjacent letters in the word or replacing a letter in the word by another letter.  