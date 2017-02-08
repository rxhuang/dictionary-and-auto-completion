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


int main(int argc, char** argv){
  //check for  amount of arguments
  if (argc!=5) {
    cout<<"Invalid number of arguments." << endl;
    return -1;
  }

  ifstream in;
  Utils util;
  Timer timer;
  int min_size =atoi(argv[1]);
  int step_size = atoi(argv[2]);
  int num_iterations = atoi(argv[3]);
  //check for valid input
  if (min_size<0 || step_size<0 || num_iterations <0) {
    cerr<<"Invalid input"<<'\n';
    return -1;
  }

  cout << "***Benchmarking dictionary BST***" << endl;
  int size = min_size;
  int incr = step_size;
  for(int i = 0; i < num_iterations ; i++){
    in.open(argv[4], ios::in);
    in.seekg(0, ios_base::beg);
    DictionaryBST bst;
    vector<string> wordsToFind;
    util.load_dict(bst, in, min_size + i*step_size);
    util.load_vector(wordsToFind, in, 100);
    in.close();
    vector<string> lexicon;
    timer.begin_timer();
    for(string w:wordsToFind){
      bst.find(w);
    }
    long long time = timer.end_timer();
    cout << size << "\t" << time  << endl;
    size += incr;
  }

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
    vector<string> lexicon;
    timer.begin_timer();
    for(string w:wordsToFind){
      hash.find(w);
    }
    long long time = timer.end_timer();
    cout << size << "\t" << time  << endl;
    size += incr;
  }

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
    vector<string> lexicon;
    timer.begin_timer();
    for(string w:wordsToFind){
      trie.find(w);
    }
    long long time = timer.end_timer();
    cout << size << "\t" << time  << endl;
    size += incr;
  }

}
