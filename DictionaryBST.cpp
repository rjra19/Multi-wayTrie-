/*
 * Names: Ramiz Alhaddad, Sanshit Sagar
 * Date: May 4th 2017
 * Description: This file just calls the c++ implementation of the 
 * binary search tree, and encases it in a wrapper. 
 * PA2
 */

#include "util.h"
#include "DictionaryBST.h"
#include <set>

  
  std::set<std::string> bst;
  std::set<std::string>::iterator it;


/*Empty Constructor for the BST*/ 

DictionaryBST::DictionaryBST(){  
}

/* 
 * Parameters: None
 * Returns: True or false if inserted correctly 
 * Create a new Dictionary that uses a BST back end */
bool DictionaryBST::insert(std::string word)
{
  it = bst.find(word);
  if(it != bst.end()){
    return false;
  } 
  else{
    bst.insert(it,word);
    return true;
  }
}

/*
 * Finds the given word in the BST
 * Parameters: The word that is to be found in the BST
 * Returns: True if word is in the dictionary, and false otherwise */
bool DictionaryBST::find(std::string word) const
{
  if(bst.find(word) != bst.end()){
    return true;
  }
  else{
    return false;

  }
}

/* Empty Destructor for the BST. Nothing allocated on the heap*/
DictionaryBST::~DictionaryBST(){
}
