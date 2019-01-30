/**
 *  CSE 100 PA3 C++ Autocomplete
 *  Authors: Jor-el Briones, Christine Alvarado
 */

#ifndef DICTIONARY_TRIE_H
#define DICTIONARY_TRIE_H

#include <vector>
#include <string>
#include <unordered_map>

class Node
{
public:
  Node();
  ~Node();
  std::vector<Node*> vector;
  int freqNode;
  bool endWord; 
  
};
/**
 *  The class for a dictionary ADT, implemented as a trie
 *  You may implement this class as either a mulit-way trie
 *  or a ternary search trie, but you must use one or the other.
 *
 */
class DictionaryTrie
{
public:
  std::unordered_map<char,int> Number;
  std::unordered_map<int,char> Character;
  Node* root;
  /* Create a new Dictionary that uses a Trie back end */
  DictionaryTrie();

  /* Insert a word with its frequency into the dictionary.
   * Return true if the word was inserted, and false if it
   * was not (i.e. it was already in the dictionary or it was
   * invalid (empty string) */
  bool insert(std::string word, unsigned int freq);

  /* Return true if word is in the dictionary, and false otherwise */
  bool find(std::string word) const;

  /* Return up to num_completions of the most frequent completions
   * of the prefix, such that the completions are words in the dictionary.
   * These completions should be listed from most frequent to least.
   * If there are fewer than num_completions legal completions, this
   * function returns a vector with as many completions as possible.
   * If no completions exist, then the function returns a vector of size 0.
   * The prefix itself might be included in the returned words if the prefix
   * is a word (and is among the num_completions most frequent completions
   * of the prefix)
   */
  std::vector<std::string>
  
  predictCompletions(std::string prefix, unsigned int num_completions);
  Node* insertHelp(std::string word, Node* currNode);  
  bool checkValid(std::string word) const; 
  /* Destructor */
  ~DictionaryTrie();

private:
  // Add your own data members and methods here
  void deleteNodes(Node*);
};
class ComparePriority {

  public:
    bool operator() (std::pair<Node*,std::string>&left, std::pair<Node*,std::string>&right) const{
      return (left.first) ->freqNode < (right.first)->freqNode;
    }     

};

/*class {

  public:
    bool operator()t{
      return;
    }

};*/
/*class Node{
  
  public: 
    Node();
    ~Node();
    std::vector<*Node> vec;
    

}*/
#endif // DICTIONARY_TRIE_H