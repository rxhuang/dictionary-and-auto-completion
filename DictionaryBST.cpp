#include "util.h"
#include "DictionaryBST.h"

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
  return *(tree->find(word)) == word;
}

/* Destructor */
DictionaryBST::~DictionaryBST()
{
  delete tree; 
}
