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

/**
 * Name: Ruoxin Huang and Muyang Wu
 * Date: Feb 9
 * Overview: compares the find time for dictionaries with different backends
 * Assignment number: 2
 */

/**
 * param: 
 * min_szie:the minimum size of dictionary
 * step_size: number of words we add each step
 * num_iterations: the number of iterations to run
 * dictFile: the name of the dictionary file 
 * This function compares the finding time for words that
 * do not exist in a dictionary using dictionaries with 
 * BST, Hashtable, and MWT as backend
 */
 main(int argc, char** argv){
  //check for  amount of arguments
  if (argc!=5) {
    cout<<"Invalid number of arguments." << endl;
    return -1;
  }

  //set up to load words from dictionary 
  ifstream in;
  Utils util;
  //create timer
  Timer timer;
  //get params
  int min_size =atoi(argv[1]);
  int step_size = atoi(argv[2]);
  int num_iterations = atoi(argv[3]);
  
  //check for valid input
  if (min_size<0 || step_size<0 || num_iterations <0) {
    cerr<<"Invalid input"<<'\n';
    return -1;
  }

  //start benchmarking dictionaryBST
  cout << "***Benchmarking dictionary BST***" << endl;
  int size = min_size; //save min_size
  int incr = step_size;
  for(int i = 0; i < num_iterations ; i++){
    in.open(argv[4], ios::in); //open file
    in.seekg(0, ios_base::beg); //seek to beginning
    DictionaryBST bst;
    vector<string> wordsToFind; // veector storing words we with to find
    util.load_dict(bst, in, min_size + i*step_size);
    //load 100 words into woredsToFind
    util.load_vector(wordsToFind, in, 100);
    in.close();
    long long time=0;
    //we take average of 1000 runs
    for(int i=0; i<1000; i++){
      //start timer, find the words, and add up time used
      timer.begin_timer();
      for(string w:wordsToFind){
	bst.find(w);
      }
      time += timer.end_timer();
    }
    time = time/1000;
    //print out the average time
    cout << size << "\t" << time  << endl;
    size += incr;//increment size
  }

  //do the exact same thing for DictionaryHashtable
  cout << "***Benchmarking dictionary Hashtable***" << endl;
  size = min_size;
  incr = step_size;
  for(int i = 0; i < num_iterations ; i++){
    in.open(argv[4], ios::in);
    in.seekg(0, ios_base::beg);
    DictionaryHashtable hash;
    vector<string> wordsToFind;
    util.load_dict(hash, in, min_size + i*step_size);
    util.load_vector(wordsToFind, in, 100);
    in.close();
    long long time=0;
    for(int i=0; i<1000; i++){
      timer.begin_timer();
      for(string w:wordsToFind){
        hash.find(w);
      }
      time += timer.end_timer();
    }
    time = time/1000;
    cout << size << "\t" << time  << endl;
    size += incr;
  }

  //Do the exact same thing for DicitonaryTrie
  cout << "***Benchmarking dictionary Trie***" << endl;
  size = min_size;
  incr = step_size;
  for(int i = 0; i < num_iterations ; i++){
    in.open(argv[4], ios::in);
    in.seekg(0, ios_base::beg);
    DictionaryTrie trie;
    vector<string> wordsToFind;
    util.load_dict(trie, in, min_size + i*step_size);
    util.load_vector(wordsToFind, in, 100);
    in.close();
    long long time=0;
    for(int i=0; i<1000; i++){
      timer.begin_timer();
      for(string w:wordsToFind){
        trie.find(w);
      }
      time += timer.end_timer();
    }
    time = time/1000;   
    cout << size << "\t" << time  << endl;
    size += incr;
  }

}
