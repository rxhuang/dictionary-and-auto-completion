#include "util.h"
#include "DictionaryBST.h"

/* Name: Ruoxin Huang and Muyang Wu
   Date: Feb 9
   Overview: implements a dictionary using BST as backend
   Assignment number: 2
*/


/* Create a new Dictionary that uses a BST back end */
DictionaryBST::DictionaryBST(){
  tree = new std::set<std::string>;
}

/* Insert a word into the dictionary. */
bool DictionaryBST::insert(std::string word)
{
  return tree->insert(word).second;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryBST::find(std::string word) const
{
  //if the find iterator does not point to end
  return tree->find(word) != tree->end();
}

/* Destructor */
DictionaryBST::~DictionaryBST()
{
  delete tree; 
}
