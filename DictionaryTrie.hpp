/**
 *  CSE 100 PA3 C++ Autocomplete
 *  Authors: Jor-el Briones, Christine Alvarado
 */

#ifndef DICTIONARY_TRIE_HPP
#define DICTIONARY_TRIE_HPP

#include <vector>
#include <string>
#include <queue>


/**
  * The class for TTNode for trie
  */
class TTNode
{
  public:
    unsigned int ifreqs;
    unsigned char symbol;
    TTNode* left; // pointer to left child
    TTNode* mid; // pointer to middle child
    TTNode* right; // pointer to right child
    bool end;
    std::string iword;
    unsigned int subfreqs;

    /* default constructor */
    TTNode( int count, unsigned char symbol, TTNode* left = 0, 
        TTNode* mid = 0, TTNode* right = 0, bool end = false, 
        std::string word = "", 
        int subfreqs = 0) 
      : ifreqs(count), symbol(symbol), left(left), mid(mid), right(right), 
      end(end), iword(word), subfreqs(subfreqs) { }



};


/**
  * A 'function class' for use as the Compare class that uses subfreqs in a 
  * priority_queue<TTNode*>.
  */
class TTNodeSubComp {
  public:
    bool operator()(TTNode*& lhs, TTNode*& rhs) const {
      return lhs->subfreqs < rhs->subfreqs;
    }
};


/**
  * A 'function class' for use as the Compare class in a priority queue
  * that uses ifreqs as priority_queue<TTNode*>
  */
class TTNodeIComp {
  public:
    bool operator() ( TTNode*& lhs, TTNode*& rhs ) const {
      return lhs->ifreqs < rhs->ifreqs;
    }
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
  DictionaryTrie() : root(0) { }

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

  /** a method to delete all node on the tree */
  void deleteAll(TTNode* n);

private:
  // Add your own data members and methods here
  TTNode* root;
};



#endif // DICTIONARY_TRIE_HPP
