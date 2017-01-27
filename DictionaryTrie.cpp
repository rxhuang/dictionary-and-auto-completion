#include "util.h"
#include "DictionaryTrie.h"

/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie()
{
  root = new MTNode();
  isize = 0;
}

/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{
  
  int ascii;
  MTNode* curr = root;
  for(unsigned int i=0; i<word.length(); i++){
    ascii = word.at(i)-96;
    if(ascii==-64){
      ascii=0;
    }
    if(ascii<0||ascii>27){
      return false;
    }
    if(!curr->children[ascii]){
      curr->children[ascii] = new MTNode();
    }
    curr = curr->children[ascii];
  }
  if(curr->isWord){
    return false;
  }
  curr->isWord = true;
  curr->freq = freq;
  return true;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
  int ascii;
  MTNode* curr = root;
  for(unsigned int i=0; i<word.length(); i++){
    ascii = word.at(i)-96;
    if(ascii<0||ascii>27){
      return false;
    }
    curr = curr->children[ascii];
    if(!curr){
      return false;
    }
  }
  return curr->isWord;
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
 */
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, unsigned int num_completions)
{
  std::vector<std::string> words;
  return words;
}

//Constructor for a node in multiway trie
MTNode::MTNode(void) {
  for(int i = 0; i < 27; ++i) {
    children[i] = NULL;
  }
  freq = 0;
  isWord = false;
}

/* Destructor */
DictionaryTrie::~DictionaryTrie(){}
