/*
 * Names: Ramiz Alhaddad, Sanshit Sagar
 * Date: May 4th 2017
 * Description: This file just calls the c++ implementation of the 
 * binary search tree, and encases it in a wrapper. 
 * PA2
 */

#include "util.h"
#include "DictionaryTrie.h"
#include <unordered_map>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;


/* Constructor that 
 * creates a new Dictionary that uses a 
 * trie for its back end 
 * Parameters: None
 * Returns: None
 */

int minimum = 0; 

DictionaryTrie::DictionaryTrie(){
	int numLetters =27;     //number of letters for each node.
	root = new Node();      //create a node.
	//create number and a character 
	//unorderd map and save the chars 
	//and thier corresponding ints into it 
	for(int i =0; i<numLetters;i++){
		char curr = char(97 + i);
		Number[curr] = i;            // add integers into the number map
		Character[i] = (int)(curr);  //add elements into the character map
	}
	Number[' '] = 26;             //add a space int to the map
	Character[26] = ' ';          
}

/*Constructor for the node 
 * that creates an array with 27 characters
 * Parameters: None
 * Returns: None
 */
Node::Node(){
	int numLetters =27;           //number of characters.
	//push null elements to the vector
	for(int i =0; i<numLetters; i++){
		vector.push_back(NULL); 
	}
	endWord = false;              //set endWord flag
	freqNode = 1;                 //set frequency of word
}

bool DictionaryTrie::checkValid(std::string word) const {
for(size_t i=0; i<word.length(); i++) {
if((word[i]!=' ') && (word[i] <'a' || word[i] > 'z')) {
	return false; 
	}
}
return true; 
}

Node* DictionaryTrie::insertHelp(std::string word, Node* currNode) 
{
for(size_t i=0; i<word.length();i++){
		char currWord = (char)word[i];      //create a char for each element
		int index = Number[currWord];           //get its index
		if(currNode ->vector[index] == NULL){
			currNode->vector[index] = new Node();    //insert a node
		}
		currNode = currNode->vector[index];      //go to the next node    
	}
	return currNode; 
}
/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) 
 * Parameters: word to be inserted, and freq of the word
 * */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{
	if(word.length() <=0) 
		{
		return false;
		}
	Node* currNode = root;                //create a root node
	bool valid = checkValid(word); 
	if(valid==false) 
		{
		return false; 
		}
	currNode = insertHelp(word, currNode); 
	if(currNode->endWord == true)
		{ 
		return false; 
		}
	currNode -> freqNode = freq;                 //assign frequency into the
	currNode->endWord = true;   
	return true;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
	std::unordered_map<char,int> Number2;
   	int numLetters= 26; 

	/*Since find is a const method, and the unordered map isn't, 
	 * we have to create a new local variable for it. 
	 */  
	for(int i =0; i< numLetters;i++){
		char curr = char(97 +i);
		Number2[curr] = i;
		Number2[' '] = 26;    
	}
	//if the element is not found. 
	if(word.length() ==0 || root == NULL){
		return false;
	}

	Node* currNode = root;
	int index;
	size_t count = 0;

	for(int i= 0; i<numLetters; i++){
		char currWord = (char)word[i];
		index = Number2[currWord];
		if(currNode->vector[index]== NULL){
			if((count == word.length()) && (currNode->endWord == true)){
				return true;
			}
			return false;
		}
		count++;
		currNode = currNode->vector[index];   
	}
	bool returner = currNode->endWord; 
	return returner;
}

/* Return up to num_completions of the most frequent completions
 * of the prefix, such that the completions are words in the dictionary.
 * These completions should be listed from most frequent to least.
 * If there are fewer than num_completions legal completions, this
 * function returns a vector with as many completions as possible.
 * If no completions exist, then the function returns a vector of size 0.
 * The prefix itself might be included in the returned words if the prefix
 * is a word (and is among the num_completions most frequent completions
 * of the prefix)
 * Parameters are the prefix for which the completions are to be found, 
 * and the number of top completions that are to be returned.
 */
std::vector<std::string> DictionaryTrie::predictCompletions(
		std::string prefix, unsigned int num_completions)

{
	std::vector<std::string> words;
  
	/*Error Conditions*/ 
	if((prefix.length() ==0) || (root == NULL) || (!(num_completions>0)) ){
		return words;
	}
  
	std:: queue <pair<Node*,std::string>> Tree;
	std::priority_queue<std::pair<Node*,std::string>,
		std::vector<std::pair<Node*,std::string>>,ComparePriority> tops;  
	Node* currNode = root;
	int index;
	/*Reach the last word of the prefix */ 
	for(size_t i = 0; i < prefix.length(); i++){
		if((prefix[i]!= ' ')&& (prefix[i] < 'a' || prefix[i]> 'z')){
			cout<< "Invalid Input. Please retry with correct input" 
			<< endl;
			return words;
		}
		char currWord = (char)prefix[i];
		index = Number[currWord];
		currNode = currNode -> vector[index];
	}
	
	Node* node = currNode; 
	std::pair<Node*,std::string> curr(node,prefix);
	Tree.push(curr);
	while(Tree.empty() == false){
		curr = Tree.front();
		Tree.pop(); 
		if(curr.first->endWord == true){
			tops.push(curr);
			//cout << " curr.." << curr.first->freqNode << curr.
			//second << endl;
		} 
		size_t index1= 0;

		while(index1 < (curr.first->vector.size())){
			if((curr.first->vector[index1]) != nullptr){
				std::pair<Node*,std::string> child (curr.first->
				vector[index1],curr.second + Character[index1]);
				Tree.push(child);
			}  
			index1++;
		}
	}    
	size_t counter;
	for(size_t i=0; i < num_completions; i++){
		counter = 0;
		if(counter<tops.size()) {
			//          cout << "second.." << tops.top().second << 
			//          endl;
			words.push_back(tops.top().second); 
			tops.pop();
			counter ++;
		}
	}
	return words;
}


/* Destructor for the method
 * Parameters: None
 * Returns: Nothing 
 */
DictionaryTrie::~DictionaryTrie(){
	deleteNodes(root);
}

/*Helper for the destructor
 * Returns: Nothing
 * Parameters: Node to be deleted
 */ 

void DictionaryTrie::deleteNodes(Node * n){
	int number = 27;
	if(n != NULL){
		int i = 0; 
		while(i < number){
			if(n->vector[i] != NULL){
				deleteNodes( n->vector[i]);

			}
			i++;
		}
		delete n;
	}
}
Node::~Node(){


}

