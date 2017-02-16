/**
 *  CSE 100 PA3 C++ Autocomplete
 *  Authors: Jor-el Briones, Christine Alvarado
 */

/**
 * Name: Ruoxin Huang and Muyang Wu
 * Date: Feb 9
 * Overview: header file for DictionaryTrie
 * Assignment number: 2
 */
#ifndef DICTIONARY_TRIE_H
#define DICTIONARY_TRIE_H

#include <vector>
#include <string>

//Node calss for a multiway trie
class MTNode{
public:

  unsigned int freq; // the frequency of the word
  bool isWord; // whether the node is a word node or not
  std::string str; //the string the node stores
  MTNode* children[27]; // 27 children for each node, one for each letter and one for space bar.
  MTNode();// MTNode constructor
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
  
  /* Create a new Dictionary that uses a Trie back end */
  DictionaryTrie();

  MTNode* getNode(std::string word);
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

  /* Destructor */
  ~DictionaryTrie();

private:
  //pointer to root node
  MTNode* root;
  // Add your own data members and methods here
  static void deleteAll(MTNode* n);
  
  std::vector<std::string> predictCompletionsHelper(MTNode* curr, unsigned int num_completions);
};

#endif // DICTIONARY_TRIE_H
