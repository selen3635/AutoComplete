/*
 * Name: Ziying Hu & Xiaolong Zhou
 * Login: cs100vat & cs100vcc
 * Date: Aug 22, 2016
 * File: benchdict.cpp
 */

#include "DictionaryTrie.hpp"
#include "util.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

/*
 * The main driver of the program 
 */
int main ( int argc, char* argv[] ) {

  /* check for Arguments */
  if ( argc != 5 ) {
    cout << "Invalid numbers of arguments\n"
      << "Usage: ./benchdict min_size step_size num_iterations dictfile\n";
    return -1;
  }

  /* parsing the arguments into int */
  istringstream num1 (argv[1]);
  istringstream num2 (argv[2]);
  istringstream num3 (argv[3]);

  unsigned int min;
  unsigned int step;
  unsigned int iter;

  num1 >> min;
  num2 >> step;
  num3 >> iter;

  /* open file */
  ifstream in;
  in.open( argv[4], ios::binary );

  /* check if input file was actually opened */
  if ( !in.is_open() ) {
    cout << "Invalid input file. No file was opened. Please try again.\n";
    return -1;
  }


  Timer myTime;

  /* iterating Dictionary Trie */
  cout << "DictionaryTrie" << endl;

  for ( unsigned int i = 0; i < iter; i++ ) {
    DictionaryTrie* tree = new DictionaryTrie();

    Utils::load_dict(*tree, in, min + i * step );

    if ( in.eof() )
      cout << "WARNING!!! Words in the file are fewer than required size!\n";

    long long duration = 0;
    for ( int i = 0; i < 10; i++ ) {
      myTime.begin_timer();

      tree->find("fjeikwi");
      tree->find("guemcd");
      tree->find("rjeiak");
      tree->find("jfeqiak");
      tree->find("tuwskngi");
      tree->find("jriwknc");
      tree->find("qpeemvik");
      tree->find("ejgjsoh");
      tree->find("eiqnvnoen");
      tree->find("qcnkriosj");

      duration = duration + myTime.end_timer();
    }

    long long average = duration / (long long)10;

    cout << min + i * step << "\t" << average << endl;

    delete tree;
  }

  cout << endl;

  if ( in.is_open() )
    in.close();
  in.open( argv[4], ios::binary );

  /* iterating Hash Table */
  cout << "DictionaryHashtable" << endl;

  for ( unsigned int i = 0; i < iter; i++ ) {
    DictionaryHashtable* table = new DictionaryHashtable();

    Utils::load_dict(*table, in, min + i * step );

    if ( in.eof() )
      cout << "WARNING!!! Words in the file are fewer than required size!\n";

    long long duration = 0;
    for ( int i = 0; i < 10; i++ ) {
      myTime.begin_timer();

      table->find("fjeikwi");
      table->find("guemcd");
      table->find("rjeiak");
      table->find("jfeqiak");
      table->find("tuwskngi");
      table->find("jriwknc");
      table->find("qpeemvik");
      table->find("ejgjsoh");
      table->find("eiqnvnoen");
      table->find("qcnkriosj");

      duration = duration + myTime.end_timer();
    }

    long long average = duration / (long long)10;

    cout << min + i * step << "\t" << average << endl;

    delete table;
  }

  cout << endl;

  if ( in.is_open() )
    in.close();
  in.open( argv[4], ios::binary );

  /* iterating BST */
  cout << "DictionaryBST" << endl;

  for ( unsigned int i = 0; i < iter; i++ ) {
    DictionaryBST* bst = new DictionaryBST();

    Utils::load_dict(*bst, in, min + i * step );

    if ( in.eof() )
      cout << "WARNING!!! Words in the file are fewer than required size!\n";

    long long duration = 0;
    for ( int i = 0; i < 10; i++ ) {
      myTime.begin_timer();

      bst->find("fjeikwi");
      bst->find("guemcd");
      bst->find("rjeiak");
      bst->find("jfeqiak");
      bst->find("tuwskngi");
      bst->find("jriwknc");
      bst->find("qpeemvik");
      bst->find("ejgjsoh");
      bst->find("eiqnvnoen");
      bst->find("qcnkriosj");

      duration = duration + myTime.end_timer();
    }

    long long average = duration / (long long)10;

    cout << min + i * step << "\t" << average << endl;

    delete bst;
  }

  cout << endl;

  if ( in.is_open() )
    in.close();

  return 0;
}
