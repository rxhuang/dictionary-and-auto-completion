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

/*
void testFind() {
  //Initialize words
  vector<std::string> words;
  vector<string>::iterator wit;
  vector<string>::iterator wen;
  //initialize nonwords
  set<string> nope;
  set<string>::iterator nit;
  set<string>::iterator nen;

  //Initialize data structures
  DictionaryBST d_bst;
  DictionaryHashtable d_ht;
  DictionaryTrie dt;
  int t_bst, t_ht, tt;

  words.push_back("harry");
  words.push_back("sriram");
  words.push_back("cse");
  words.push_back("crucio");
  words.push_back("autocomplete");

  cout << "Inserting into Dictionaries..." << endl;

  wit = words.begin();
  wen = words.end();

  for(; wit != wen; ++wit)
    {
      cout << "Inserting: \"" << *wit << "\"... ";
      t_bst = d_bst.insert(*wit);
      t_ht = d_ht.insert(*wit);
      tt = dt.insert(*wit, 24);
      //cout << t_bst << " " << t_ht << " "<< tt << "... ";
      if(!t_bst)
        {
          cout << "failed for DictionaryBST... ";
        }
      if(!t_ht)
        {
          cout << "failed for DictionaryHashset... ";
        }
      if(!tt)
        {
          cout << "failed for DictionaryTrie... ";
        }
      if(t_bst && t_ht && tt)
        {
          cout << "PASSED! :D ";
        }
      if(dt.getNode("harry")->freq==24){
	cout << "passed freq!!!!!!";
      }
      cout << endl;
    }
  cout << endl;

  cout << "Finding words in Dictionaries..." << endl;

  wit = words.begin();
  wen = words.end();
  for(; wit != wen; ++wit)
    {
      cout << "Finding: \"" << *wit << "\"... ";
      t_bst = d_bst.find(*wit);
      t_ht = d_ht.find(*wit);
      tt = dt.find(*wit);
      if(!t_bst)
        {
          cout << "failed for DictionaryBST... ";
        }
      if(!t_ht)
        {
          cout << "failed for DictionaryHashset... ";
        }
      if(!tt)
        {
          cout << "failed for DictionaryTrie... ";
        }
      if(t_bst && t_ht && tt)
        {
          cout << "PASSED! :D ";
        }
      cout << endl;
    }

  return 0;
}*/


int main(int argc, char** argv)
{
  /*
  //Initialize words
  vector<std::string> words;
  vector<string>::iterator wit;
  vector<string>::iterator wen;
  //initialize nonwords
  set<string> nope;
  set<string>::iterator nit;
  set<string>::iterator nen;

  //Initialize data structures
  DictionaryBST d_bst;
  DictionaryHashtable d_ht;
  DictionaryTrie dt;
  int t_bst, t_ht, tt;

  words.push_back("harry");
  words.push_back("sriram");
  words.push_back("cse");
  words.push_back("crucio");
  words.push_back("autocomplete");

  cout << "Inserting into Dictionaries..." << endl;

  wit = words.begin();
  wen = words.end();

  for(; wit != wen; ++wit)
    {
      cout << "Inserting: \"" << *wit << "\"... ";
      t_bst = d_bst.insert(*wit);
      t_ht = d_ht.insert(*wit);
      tt = dt.insert(*wit, 1);
      //cout << t_bst << " " << t_ht << " "<< tt << "... ";
      if(!t_bst)
	{
	  cout << "failed for DictionaryBST... ";
	}
      if(!t_ht)
	{
	  cout << "failed for DictionaryHashset... ";
	}
      if(!tt)
	{
	  cout << "failed for DictionaryTrie... ";
	}
      if(t_bst && t_ht && tt)
	{
	  cout << "PASSED! :D ";
	}
      cout << endl;
    }

  cout << endl << "Re-inserting elements that were just inserted into Dictionaries..." << endl;

  wit = words.begin();
  wen = words.end();
  for(; wit != wen; ++wit)
    {
      cout << "Inserting: \"" << *wit << "\"... ";
      t_bst = d_bst.insert(*wit);
      t_ht = d_ht.insert(*wit);
      tt = dt.insert(*wit, 0);
      if(t_bst)
        {
          cout << "failed for DictionaryBST... ";
        }
      if(t_ht)
        {
          cout << "failed for DictionaryHashset... ";
        }
      if(tt)
        {
          cout << "failed for DictionaryTrie... ";
        }
      if(!t_bst && !t_ht && !tt)
        {
          cout << "PASSED! :D ";
        }
      cout << endl;
    }
  cout << endl;
/*You are supposed to add more test cases in this file */

  vector<string> words;
  Utils test;
  DictionaryTrie trie;
  ifstream file;
  file.open("freq_dict.txt");
  test.load_vector(words,file);
  test.load_dict(trie,file);

  //testFind();
  
  vector<string> completions;
  completions = trie.predictCompletions("face", 10);
  for(int i = 0; i < 10 ; i ++){
    cout << completions[i] << endl;
  }
  return 0;
}
