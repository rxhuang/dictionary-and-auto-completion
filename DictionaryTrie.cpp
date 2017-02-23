#include "util.h"
#include "DictionaryTrie.h"
#include <iostream>
#include <stack>
using namespace std;

/**
 * Name: Ruoxin Huang and Muyang Wu
 * Date: Feb 9
 * Overview: implements a dictionary using MWT as backend
 * Assignment number: 2
 */

/* Create a new Dictionary that uses a  back end */
DictionaryTrie::DictionaryTrie()
{
  //create a dummy root node so we can have 27 children
  root = new MTNode();
}

/* Destructor */
DictionaryTrie::~DictionaryTrie()
{
  deleteAll(root);
}

//Constructor for a node in multiway trie
MTNode::MTNode(void) {
  for(int i = 0; i < 27; ++i) {//27 children, 1 for each letter and 1 for spacebar
    children[i] = NULL;
  }
  freq = 0; //frequency of the node
  isWord = false; //whether the node is a word
}

/* Getter method for a node in the Trie.
 * param: word is the string of the node
 * param add is whether to add nodes when paths does not exist
 */
MTNode* DictionaryTrie::getNode(std::string word, bool add){
  int ascii;//The child position of the letter
  MTNode* curr = root;
  for(unsigned int i=0; i<word.length(); i++){ //for each letter in the word
    ascii = word.at(i)-96; //-96 so that a goes to 1 and z goes to 27
    if(ascii==-64){ // space bar goes to 0
      ascii=0;
    }
    if(ascii<0||ascii>27){ //if out of range
      cerr << "invalid character in word" << endl;
      return NULL;
    }
    //if no child of such value exists and we wish to add, then we create a node
    if(!curr->children[ascii]&&add){
      curr->children[ascii] = new MTNode();
    }
    if(!curr->children[ascii]&&(!add)){ // if we do not want to add, we return NULL
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
  //get the node with the given word, if node doesn`t exist, create it
  MTNode* curr = getNode(word, true);

  if(curr==NULL){//if word contains symbols other than a-z and space
    return false;
  }
  if(curr->isWord){ //if the word is already in the trie, only update freqyency
    if(curr->freq<freq){
      curr->freq = freq;
    }
    return false;
  }

  curr->isWord = true; //set isWord to true
  curr->str = word; //set word
  curr->freq = freq;//set freq
  return true;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) 
{
  //get the node for the given word and do not create any new nodes
  MTNode* curr = getNode(word,false);
  if(curr==NULL){//if node does not exist in the tree
    return false;
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
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix
							    , unsigned int num_completions)
{
  std::vector<std::string> words;// vector to return
  std::vector<MTNode*> sortedCompletions;// vector to return

  //if prefix is empty, print error message and return empty vector
  if(prefix.length()==0){
    cerr<< "Invalid Input. Please retry with correct input"<<std::endl;
    return words;
  }
  // Let curr point to last letter of prefix without adding any nodes
  MTNode* curr = getNode(prefix, false);
  //if curr does not exist in the tree, return empty vector
  if(curr==NULL){return words;
  }

  //use helper method to perform BFS and get a vector of all possible completion
  //sorted by frequency
  sortedCompletions = predictCompletionsHelper(curr);

  if(num_completions > sortedCompletions.size())//return as many valid completions as possible
    num_completions = sortedCompletions.size();
  for(unsigned int i=0; i<num_completions;i++){//we only add num_completions
    //number of words to the final vector we return
    words.insert(words.begin()+i,sortedCompletions[i]->str);
  }
  return words;
}


/* Helper method for predictCompletions
 * param: pointer to the last letter of the prefix
 * return: a vector of all possible completion sorted by frequency
 * uses breadth first search to get all possible completion and sorts them and
 */
std::vector<MTNode*> DictionaryTrie::predictCompletionsHelper(MTNode* curr){
  std::stack<MTNode*> stack;// stack used during BFS
  std::vector<MTNode*> search;// vector used to sort completion according to frequency
  MTNode* n; // pointer to top of stack
  bool add = false; //bool indicatingf whether or not we have already added the node
  stack.push(curr); //push last letter of prefix into stack
  while(!stack.empty()){
    n = stack.top();
    stack.pop(); //pop stack and let n point to the item poped
    if(n->isWord){ //if n is a word
      add = false;
      if(search.size()==0){ //if the vector we are adding to is empty
	search.push_back(n);
	add = true; //we added n, so set n to true
      }
      else{ // if the vector we are adding to is not empty
	for(unsigned int i=0; i<search.size();i++){ //compare the frequency of
	  //n to all existing words in the vector
	  if(search[i]->freq<n->freq){ //if n has larger frequency than a word,
	    //put in front of the word
	    search.insert(search.begin()+i,n);
	    add = true;
	    break;
	  }
	}
      }
      if(!add){//if we have not added n, n is amller than all words in the
	//vector, so add it to the end
	search.push_back(n);
      }
    }
    for(unsigned int i=0; i<27; i++){//for all existing children of n, push to
      //stack(part of or BFS
      if(n->children[i]){
	stack.push(n->children[i]);
      }
    }
  }//We will end up with a vector(search) containing all possible completions
  //sorted with largest frequency at the beginning and we return it
  return search;
}


/* Helper method for Destructor */
void DictionaryTrie::deleteAll(MTNode* n){
  if (n==NULL)
    return;
  for(int i=0; i<27;i++){
    if (n->children[i])
      deleteAll(n->children[i]);
  }
  delete n;
  return;
}
