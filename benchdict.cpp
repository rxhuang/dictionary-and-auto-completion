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
  string dictfile = argv[4];
  //check for valid input
  if (min_size<0 || step_size<0 || num_iterations <0) {
    err<<"Invalid input"<<'\n';
    return -1;
  }
  //check for valid file
  in.open(dictfile, ios::in);
  if (!in.is_open()) {
    std::cout<<"Invalid input file. \n";
    return -1;
  }

  in.seekg(0, ios_base::end);
  //check for empty file
  unsigned int len = in.tellg();
  if (len==0) {
    cout<<"file is empty." << endl;
    return -1;
  }
  in.seekg(0, ios_base::beg);
  //read line by line to find out the number of words in dict
  in.unsetf(std::ios_base::skipws);
  unsigned word_count = std::count(istream_iterator<char>(in),istream_iterator<char>(), '\n');
  in.close();

  cout << "***Benchmarking dictionary BST***" << endl;
  for(int i = 0; i < num_iterations ; i++){
    in.open(argv[4], ios::in);
    in.seekg(0, ios_base::beg);
    DictionaryBST bst = new DictionaryBST();
    if((int)word_count < min_size*step_size){
      cout << "Dict size too small." << endl;
      util.load_dict(*bst, in, word_count);
    }
    else
      util.load_dict(bst, in, min_size + i*step_size);
    in.close();
    int test[num_iterations];
    for(int i = 0; i < num_iterations ; i++){
      timer.begin_timer();
    }


  }
}
