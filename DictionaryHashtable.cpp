#include "util.h"
#include "DictionaryHashtable.h"

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
  return *(table->find(word)) == word;
}

/* Destructor */
DictionaryHashtable::~DictionaryHashtable()
{
  delete table;
}
