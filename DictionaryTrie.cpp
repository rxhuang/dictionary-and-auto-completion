#include "util.h"
#include "DictionaryTrie.h"
#include <iostream>
#include <stack>

using namespace std;
/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie()
{
  root = new MTNode();
}

MTNode* DictionaryTrie::getNode(std::string word){
  int ascii;//The child position of the letter
  MTNode* curr = root;
  for(unsigned int i=0; i<word.length(); i++){ //for each letter in the word
    ascii = word.at(i)-96; //-96 so that a goes to 1 and z goes to 27
    if(ascii==-64){ // space bar goes to 0
      ascii=0;
    }
    if(ascii<0||ascii>27){ //if out of range
      return NULL;
    }
    if(!curr->children[ascii]){ //if no child of such value exists
      return NULL;
    }
    curr = curr->children[ascii]; //move down the trie
  }
  return curr; 
}

/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{
  
  int ascii; //child position of a letter
  MTNode* curr = root;
  for(unsigned int i=0; i<word.length(); i++){//for each letter in the word
    ascii = word.at(i)-96;  //-96 so that a goes to 1 and z goes to 27
    if(ascii==-64){ //space bar goes to 0
      ascii=0;
    }
    if(ascii<0||ascii>27){ //if out of range
      return false;
    }
    if(!curr->children[ascii]){ //if no such child exists, create one
      curr->children[ascii] = new MTNode();
    }
    curr = curr->children[ascii]; //move 1 level down the trie
  }
  if(curr->isWord){ //if the word is already in the trie, only update freqyency
    if(curr->freq<freq){
      curr->freq = freq;
    }
    return false;
  }
  curr->isWord = true; //set isWord to true
  curr->str = word;
  curr->freq = freq;//set freq
  return true;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
  int ascii;
  MTNode* curr = root;
  for(unsigned int i=0; i<word.length(); i++){//for each letter in the word
    ascii = word.at(i)-96;//-96 so that a goes to 1 and z goes to 27
    if(ascii==-64){//space bar goes to 0
      ascii=0;
    }
    if(ascii<0||ascii>27){//if out of range
      return false;
    }
    if(!curr->children[ascii]){ //if no such child exists, return false
      return false;
    }
    curr = curr->children[ascii];
  }
  return curr->isWord; //if the node exist, check if it is a word node
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
  int ascii;
  MTNode* curr = root;
  if(prefix.length()==0){ //if prefix is empty, print error message and return empty vector
    std::cout<< "Invalid Input. Please retry with correct input"<<std::endl;
    return words;
  }

  for(unsigned int i=0; i<prefix.length(); i++){//for each letter in the prefix
    ascii = prefix.at(i)-96;//-96 so that a goes to 1 and z goes to 27
    if(ascii==-64){//space bar goes to 0
      ascii=0;
    }
    if(ascii<0||ascii>27){//if out of range, print error message
      std::cout<< "Invalid Input. Please retry with correct input"<<std::endl;
      return words;
    }
    if(!curr->children[ascii]){ //if no such child exists, return empty vector
      return words;
    }
    curr = curr->children[ascii];
  }
  return predictCompletionsHelper(curr, num_completions);
}

std::vector<std::string> DictionaryTrie::predictCompletionsHelper(MTNode* curr, unsigned int num_completions){
  std::vector<std::string> words;
  std::stack<MTNode*> stack;
  std::vector<MTNode*> search;
  MTNode* n;
  bool add = false;
  stack.push(curr);
  while(!stack.empty()){
    n = stack.top();
    stack.pop();
    if(n->isWord){
      add = false;
      if(search.size()==0){
	search.push_back(n);
	add = true;
      }
      for(unsigned int i=0; i<search.size();i++){
	if(search[i]->freq<n->freq){
	  search.insert(search.begin()+i,n);
	  add = true;
          break;
	}
      }
      if(!add){
	search.push_back(n);
      }
    }
    for(unsigned int i=0; i<27; i++){
      if(n->children[i]){
	stack.push(n->children[i]);
      }
    }
  }
    

    for(unsigned int i=0; i<search.size();i++){
      words.insert(words.begin()+i,n->str);
    }
    return words;
}



//Constructor for a node in multiway trie
MTNode::MTNode(void) {
  for(int i = 0; i < 27; ++i) {//27 children, 1 for each letter and 1 for spacebar
    children[i] = NULL;
  }
  freq = 0; //frequency of the node
  isWord = false; //whether the node is a word
}

/* Destructor */
DictionaryTrie::~DictionaryTrie(){}
