#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <set>
#include <cstdlib>
#include "util.h"
#include "DictionaryTrie.h"
#include "DictionaryBST.h"
#include "DictionaryHashtable.h"
#include <algorithm>
#include <iterator>
#define LETTERS 26
using namespace std;

/* Name: Ruoxin Huang and Muyang Wu
   Date: Feb 9
   Overview: compares performances or 2 hash functions
   Assignment number: 2
*/


/* This is a hash function for strings that
   adds up the ascii code for each letter in 
   the string
*/
int hashFunction1(string word, int tableSize) { 
  int sum=0; //create sum variable
  for (unsigned int i=0; i<word.length(); i++ ) //for each character in the word
    sum += word.at(i); //add the ascii code to sum
  return sum % tableSize; //return the sum mod by table size
}

/* This is a hash function for strings that breaks the string into groups of 2 
   letters. For each group, it sums up the ascii code of the first letter with 
   256 times the asci code of the second letter. The hash value is the total 
   sum across all groups and mod by the table size.
*/
long hashFunction2(string word, int tableSize) {
  int intLength = word.length()/2; //get the number groups of 4 characters
  long sum = 0; //create sum varaible
  for (int j = 0; j < intLength; j++) { // for each group of 4 characters
    long mult = 1;
    for (unsigned int i=0; i<2; i++ ){ //for each character in the group
      sum += word.at(j*2+i)*mult; //add the ascii code to sum multiplied by mult
      mult *= 256; //increase multiplier
    }
  }

  //repeat the above process for the last character if string has odd number
  //of characters
  if(word.length()%2==1){
    sum += word.at(word.length()-1);
  }

  return(sum % tableSize); //return the sum mod by table size
}


/* main function takes in a file name and num_words
   which is the number of words we should hash
   The function compares 2 hash functions` performances
*/
int main(int argc, char** argv){
  
  //test the correctness of both hasfunctions
  string s1 = "aaabbb";
  string s2 = "hijklmn";
  string s3 = "the road ahead";
  //cout<<hashFunction1(s1,100)<<"and"<<hashFunction2(s1,100)<<endl;
  //cout<<hashFunction1(s2,100)<<"and"<<hashFunction2(s2,100)<<endl;
  //cout<<hashFunction1(s3,100)<<"and"<<hashFunction2(s3,100)<<endl;

  //check if correct number of argyements
  if (argc!=3) {
    cout<<"Invalid number of arguments." << endl;
    return -1;
  }

  //set up ifstream and utils
  ifstream in;
  Utils util;
  //save arguements 
  string dictFile = argv[1];
  int num_words = atoi(argv[2]);
  //initialize table size to be twice the number of words
  int tableSize = 2*num_words;


  
  vector<string> words;//create vector containing the words
  //create vector representing number of collisions at each slot 
  vector<int> collisions(tableSize,0);
  //create vector representing number of slots containing specific number of collisions
  vector<int> collisionCount(tableSize,0);
  //load num_words strings into vector words
  in.open(dictFile, ios::in);
  in.seekg(0, ios_base::beg);
  util.load_vector(words, in, num_words);
  in.close();
  //for each string, add 1 to corresponding slot of collisions vector
  for(string w: words){
    collisions[hashFunction1(w, tableSize)] += 1;
  }
  //print statements
  cout << "Printing the statistics for hashFunction1 with hash table size " 
  << tableSize << endl;
  cout << "#hits" << "\t" << "#slots receiving the #hits" << endl;
  //for each unique number of collisions, put number of slots having such number of collisions
  //in the vector cillisionCount
  for(int i=0; i<num_words; i++){
    for(int x: collisions){
      if(x==i){//if number of collision is equal to a specific number(ie 0,1,2,...)
	collisionCount[i] += 1; //plus one to the number of slots having such number of collisisons
      }
    }
  }
  int totalCollision=0;//initialize variable for total number of collisions
  int worstCaseFind=0;//initialize variable for worst case steps to find a word
  int wordsLeft = tableSize;//variable used to calculate total collision
  //print out the collision number corresponding to slots having that number of collisions
  for(int i=0; i<num_words; i++){
    if(collisionCount[i]!=0){
      //if exist higher number of collision, update worstCaseFind
      if(worstCaseFind<i){
	worstCaseFind = i;
      }
      //print collision number
      cout << i << "\t" << collisionCount[i] << endl;
      if(i>0){
	wordsLeft -= collisionCount[i-1];
      }
      if(wordsLeft>0)
	totalCollision += wordsLeft*i;//update total collision      
    }
  }
  //print average collision and worst case find
  double averageCollision = totalCollision/(double)num_words;
  cout << "The average number of steps for a successful search for hash function 1 would be "
       << averageCollision << endl;
  cout << "The worst case steps that would be needed to find a word is " << worstCaseFind << endl;
  
  //do the same for hasFunction2
  vector<string> words2;//create vector containing the words
  //create vector representing number of collisions at each slot
  vector<int> collisions2(tableSize,0);
  //create vector representing number of slots containing specific number of collisions
  vector<int> collisionCount2(tableSize,0);
  //load num_words strings into vector words
  in.open(dictFile, ios::in);
  in.seekg(0, ios_base::beg);
  util.load_vector(words2, in, num_words);
  in.close();
  //for each string, add 1 to corresponding slot of collisions vector
  for(string w: words2){
    collisions2[hashFunction2(w, tableSize)] += 1;
  }
  //print statements
  cout << "Printing the statistics for hashFunction2" << endl;
  cout << "#hits" << "\t" << "#slots receiving the #hits" << endl;
  //for each unique number of collisions, put number of slots having such number of collisions
  //in the vector cillisionCount
  for(int i=0; i<num_words; i++){
    for(int x: collisions2){
      if(x==i){//if number of collision is equal to a specific number(ie 0,1,2,...)
        collisionCount2[i] += 1; //plus one to the number of slots having such number of collisisons
      }
    }
  }

  //reset variables
  totalCollision=0;
  worstCaseFind=0;
  wordsLeft = tableSize;
  //print out the collision number corresponding to slots having that number of collisions
  for(int i=0; i<num_words; i++){
    if(collisionCount2[i]!=0){
      //if exist higher number of collision, update worstCaseFind
      if(worstCaseFind<i){
        worstCaseFind = i;
      }
      //print collision number
      cout << i << "\t" << collisionCount2[i] << endl;
      if(i>0){
        wordsLeft -= collisionCount2[i-1];
      }
      if(wordsLeft>0)
        totalCollision += wordsLeft*i;//update total collision
    }
  }
  //print average collision and worst case find
  averageCollision = totalCollision/(double)num_words;
  cout << "The average number of steps for a successful search for hash function 1 would be "
       << averageCollision << endl;
  cout << "The worst case steps that would be needed to find a word is " << worstCaseFind << endl;

  return 0;
}
