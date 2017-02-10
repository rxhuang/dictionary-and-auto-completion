#include "util.h"
#include "DictionaryHashtable.h"

/**
 * Name: Ruoxin Huang and Muyang Wu
 * Date: Feb 9
 * Overview: implements a dictionary using hashtable as backend
 * Assignment number: 2
 */


/* Create a new Dictionary that uses a Hashset back end */
DictionaryHashtable::DictionaryHashtable()
{
  table = new std::unordered_set<std::string>;
}

/* Insert a word into the dictionary. */
bool DictionaryHashtable::insert(std::string word)
{
  return table->insert(word).second;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryHashtable::find(std::string word) const
{
  return table->find(word) != table->end();
}

/* Destructor */
DictionaryHashtable::~DictionaryHashtable()
{
  delete table;
}
