/*
 *Names: Ramiz Alhaddad, Sanshit Sagar
 *Date: May 4th 2017
 *Description: This file just calls the c++ implementation of the 
 *binary search tree, and encases it in a wrapper. 
 *PA2
 */

#include "util.h"
#include "DictionaryHashtable.h"
#include <unordered_set>

std::unordered_set<std::string> hashTable;
std::unordered_set<std::string>::iterator itT; 

/* Empty Constructor that 
 * Creates a new Dictionary that uses a Hashset back end */
DictionaryHashtable::DictionaryHashtable(){}

/* Insert a word into the dictionary. 
 * Returns: True if inserts, false else
 * Parameters: word to be inserted into HT
 * */
bool DictionaryHashtable::insert(std::string word)
{
  itT = hashTable.find(word);
  if(itT != hashTable.end()){
    return false;
  }  
  else{
    hashTable.insert(word);
    return true;
  }
}

/* 
 * Finds a word in the dictionary
 * Parameters: Word to be found in the dictionary
 * Return true if word is in the dictionary, and false otherwise */
bool DictionaryHashtable::find(std::string word) const
{
  itT = hashTable.find(word);
  if(itT != hashTable.end()){
    return true;
  }
  else{

    return false;
  }   
}

/* Empty Destructor
 * Nothing Allocated on the heap */
DictionaryHashtable::~DictionaryHashtable(){}
