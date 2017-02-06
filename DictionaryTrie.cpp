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

/* Getter method for a node in the Trie, used for testing
 * param: the string of the node
 */
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
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix
    , unsigned int num_completions)
{
  std::vector<std::string> words;
  int ascii;
  MTNode* curr = root;
  if(prefix.length()==0){ //if prefix is empty, print error message and return 
    //empty vector
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
  }//End of for loop, curr should point to last letter of prefix
  return predictCompletionsHelper(curr, num_completions); //use helper method
}

/* Helper method for predictCompletions
 * param: pointer to the last letter of the prefix and the number of completions
 * wanted
 * return: same as predictCompletions
 * uses breadth first search to get all possible completion and sorts them and
 * returns required number of completions in a vector
 */
std::vector<std::string> DictionaryTrie::predictCompletionsHelper(MTNode* curr, 
    unsigned int num_completions){
  std::vector<std::string> words;//the vector we will return
  std::stack<MTNode*> stack;// stack used during BFS
  std::vector<MTNode*> search;// vector used to sort completion according to frequency
  MTNode* n; // pointer to top of stack
  bool add = false; //bool indicatingf whether or not we have already added the node
  stack.push(curr); //push last letter of prefix into stack
  while(!stack.empty()){ 
    n = stack.top(); 
    stack.pop(); //pop stack and let n point to the item poped
    if(n->isWord){ //if n is a word
      add = false; //set add to false
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
  //sorted with largest frequency at the beginning
    
    if(num_completions > search.size())//return as many valid num completions as possible
      num_completions = search.size();
    for(unsigned int i=0; i<num_completions;i++){//we only add num_completions 
      //number of words to the final vector we return
      words.insert(words.begin()+i,search[i]->str);
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
