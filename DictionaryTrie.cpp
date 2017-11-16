/*
 * Name: Ziying Hu & Xiaolong Zhou
 * Login: cs100vat & cs100vcc
 * Date: Aug 22, 2016
 * File: DictionaryTrie.cpp
 */

#include "util.hpp"
#include "DictionaryTrie.hpp"

/* Create a new Dictionary that uses a Trie back end */
//DictionaryTrie::DictionaryTrie(){}

/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{
  /* if it is empty string return false */
  if ( word.empty() || freq == 0)
    return false;

  /* create a root */
  if ( root == nullptr ) {

    /* if the word has only one character */
    if ( word.length() == 1 ) {
      root = new TTNode(freq, word[0], 0, 0, 0, true, word, freq);
      return true;
    }
    /* if the word has more than one character */
    else {
      root = new TTNode(0, word[0], 0, 0, 0, false, "", freq);
      TTNode* curNode = root;
    
      /* to add the rest of the word behind the middle of the root */
      for ( unsigned int i = 1; i < word.length(); i++ ) {

        /* if this is not the end of the word, then create appropriate node */
        if (i != word.length() - 1)
          curNode->mid = new TTNode(0, word[i], 0, 0, 0, false, "", freq);
        else
          curNode->mid = new TTNode(freq, word[i], 0, 0, 0, true, word, freq);

        curNode = curNode->mid;

      } // end of for
      
      return true;
    }

  }


  /* The case that the trie has a root already */
  TTNode* curNode = root;

  /* insert the word with the tree has its root */
  for ( unsigned int i = 0; i < word.length(); i++ ) {
  
    bool stop = false;

    /* if the first character has found its place but the middle was occupied*/
    if ( curNode->mid != 0 && i > 0 ) {
      if ( curNode->subfreqs < freq )
        curNode->subfreqs = freq;
      curNode = curNode->mid;
    }
    /* if the first character was inserted and the middle was blank */
    else if ( curNode->mid == 0 && i > 0 ) {
      /* insert the new node based on whether its the last character */
      if (i != word.length() - 1)  
        curNode->mid = new TTNode(0, word[i], 0, 0, 0, false, "", freq);
      else {
        curNode->mid = new TTNode(freq, word[i], 0, 0, 0, true, word, freq);
        if ( curNode->subfreqs < freq )
          curNode->subfreqs = freq;
        return true;
      }
      if ( curNode->subfreqs < freq )
        curNode->subfreqs = freq;
    
      /* update the curNode and set the boolean to not run the while loop */
      curNode = curNode->mid;
      stop = true;

    }

    /* the while loop to find the right position to insert */
    while ( !stop ) {

      /* if the word is smaller than the current symbol */
      if ( word[i] < curNode->symbol ) {

        /* if the left is not null and the symbol is not equal */
        if (curNode->left != 0  && curNode->left->symbol != word[i]) { 
          if ( curNode->subfreqs < freq )
            curNode->subfreqs = freq;
          curNode = curNode->left;
        }
        /* if the left is not null but the symbol is already created */
        else if (curNode->left != 0 && curNode->left->symbol == word[i]) {
          if ( curNode->subfreqs < freq )
            curNode->subfreqs = freq;
          curNode = curNode->left;
          /* if it is the end of word and it is not inserted before */
          if ( (i == (word.length() - 1)) && curNode->end == false) {
            if ( curNode->subfreqs < freq )
              curNode->subfreqs = freq;
            curNode->iword = word;
            curNode->ifreqs = freq;
            curNode->end = true;
            return true;
          }

          stop = true;
        }
        /* if the left is null */
        else {

          /* insert the new node at the left whether it is the last character*/
          if (i != word.length() - 1)  
            curNode->left = new TTNode(0, word[i], 0, 0, 0, false, "", freq);
          else {
            curNode->left = new TTNode(freq, word[i], 0, 0, 0, true, word, 
                freq);
            if ( curNode->subfreqs < freq )
              curNode->subfreqs = freq;
            return true;
          }

          if ( curNode->subfreqs < freq )
            curNode->subfreqs = freq;
          curNode = curNode->left;
          stop = true;

        }
      
      }
      /* if the symbol is larger than the current symbol */
      else if ( curNode->symbol < word[i] ) {

        /* if the right is not null and the symbol is not the same */
        if ( curNode->right != 0 && curNode->right->symbol != word[i]) {
          if ( curNode->subfreqs < freq )
            curNode->subfreqs = freq;
          curNode = curNode->right;
        }
        /* if the right is not null and the symbol is the same */
        else if (curNode->right != 0 && curNode->right->symbol == word[i]) {
          if ( curNode->subfreqs < freq )
            curNode->subfreqs = freq;
          curNode = curNode->right;
          /* if its the end and the word is not inserted before */
          if ( (i == (word.length() - 1)) && curNode->end == false) {
            if ( curNode->subfreqs < freq )
              curNode->subfreqs = freq;
            curNode->iword = word;
            curNode->ifreqs = freq;
            curNode->end = true;
            return true;
          }

          stop = true;
        }
        /* if the right is null */
        else {

          /* insert the new node at the right if it is the last character */
          if (i != word.length() - 1)  
            curNode->right = new TTNode(0, word[i], 0, 0, 0, false, "", freq);
          else {
            curNode->right = new TTNode(freq, word[i], 0, 0, 0, true, word, 
                freq);
            if ( curNode->subfreqs < freq )
              curNode->subfreqs = freq;
            return true;
          }

          if ( curNode->subfreqs < freq )
            curNode->subfreqs = freq;
          curNode = curNode->right;
          stop = true;

        }
    
      }
      /* if the symbol is the same */
      else {
        /* if its the end and the word is not inserted before */
        if ( (i == (word.length() - 1)) && curNode->end == false) {
          if ( curNode->subfreqs < freq )
            curNode->subfreqs = freq;
          curNode->iword = word;
          curNode->ifreqs = freq;
          curNode->end = true;
          return true;
        }
        if ( i != word.length() - 1 && curNode->subfreqs < freq )
          curNode->subfreqs = freq;
        stop = true;

      }

    } // end of while
  }// end of for

  return false;

}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
  /* invalid case for find */
  if ( root == 0 || word.empty() )
    return false;

  TTNode* curNode = root;

  bool found = true;

  /* for loop to find each character in the word */
  for(unsigned int i =  0; i < word.length(); i ++ ) {

    found = true;
    while(found) {

      /* if the word is less than the current symbol */
      if(  word[i] < curNode->symbol){

        /* if current does not have left then word not found */
        if(curNode->left == nullptr)
          return false;
        else
          curNode = curNode->left;

      }
      /* if the word is larger than the current symbol */
      else if( curNode->symbol < word[i]) {

        /* if current does not have right then word not found */
        if(curNode->right == nullptr ) 
          return false;
        else
          curNode = curNode->right;
      }
      /* if the word is the same */
      else{

        /* if it is the end */
        if( i == word.length() -1)
          found = false;
        else {

          /* if the current does not have mid then word not found */
          if(curNode->mid == nullptr)
            return false;
          else{
            curNode = curNode->mid;
            found = false;
          }
        }
      }

    }//end of loop

  }//end of for
  
  return curNode->end;

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
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, 
    unsigned int num_completions)
{
  
  std::vector<std::string> words;
  
  /* invalid case to return words */
  if (num_completions <= 0 || prefix.empty() || root == 0)
    return words;

  /* loop through the trie to find prefix in the trie */
  TTNode* curNode = root;
  for ( unsigned int i = 0; i < prefix.length(); i++ ) {
  
    bool found = false;
    while ( !found ) {

      /* if the prefix is less than current symbol */
      if ( prefix[i] < curNode->symbol) {
        if (curNode->left == 0)
          return words;
        else
          curNode = curNode->left;
      }
      /* if the prefix is larger than current symbol */
      else if ( curNode->symbol < prefix[i] ) {
        if (curNode->right == 0)
          return words;
        else
          curNode = curNode->right;
      }
      /* if the prefix is the same */
      else {
        /* if it is the end */
        if ( i == prefix.length() - 1 )
          found = true;
        else {
          if ( curNode->mid == 0 )
            return words;
          else {
            curNode = curNode->mid;
            found = true;
          }
        }
      }
    }// end of while
  }// end of for


  /* give the suggestion based on the curNode pointing to the last prefix
  character */
  std::priority_queue<TTNode*, std::vector<TTNode*>, TTNodeSubComp> subQ;
  std::priority_queue<TTNode*, std::vector<TTNode*>, TTNodeIComp> iQ;

  unsigned int count = 0;

  /* if curNode does not have mid child */
  if ( curNode->mid == 0 ) {
    if ( curNode->end == true )
      words.push_back(prefix);
    return words;
  }

  /* if the prefix word itself is a word and larger than others */
  if ( curNode->end == true && curNode->ifreqs >= curNode->mid->subfreqs && 
      curNode->ifreqs >= curNode->mid->ifreqs ) {
    words.push_back(prefix);
    count++;
    if ( count == num_completions )
      return words;
  }
  else if ( curNode->end == true ) {
    iQ.push(curNode);
  }

  curNode = curNode->mid;

  if ( curNode->end == true && curNode->ifreqs >= curNode->subfreqs ) {
    //if ( curNode->left != 0 || curNode->right != 0 ||curNode->mid != 0 ) {
      //words.push_back(curNode->iword);
      //count++;
      //if ( count == num_completions )
        //return words;
   // }
  }
  else if ( curNode->end == true ) {
    iQ.push(curNode);
  }


  bool usingI = false;

  while ( count < num_completions ) {
    if ( usingI ) {
      words.push_back( curNode->iword );
      count++;
      if ( !iQ.empty() && !subQ.empty() ) {
        if ( iQ.top()->ifreqs >= subQ.top()->subfreqs ) {
          curNode = iQ.top();
          iQ.pop();
          usingI = true;
        }
        else {
          curNode = subQ.top();
          subQ.pop();
          if ( curNode->ifreqs != curNode->subfreqs )
            iQ.push(curNode);
          usingI = false;
        }
      }
      else if ( iQ.empty() && !subQ.empty() ) {
        curNode = subQ.top();
        subQ.pop();
        if ( curNode->ifreqs != curNode->subfreqs )
          iQ.push(curNode);
        usingI = false;
      }
      else if ( !iQ.empty() && subQ.empty() ) {
        curNode = iQ.top();
        iQ.pop();
        usingI = true;
      }
      else
        break;
    }
    
    else {
      if ( curNode->ifreqs == curNode->subfreqs ) {
        if ( curNode->left != 0 )
          subQ.push(curNode->left);
        if ( curNode->right != 0 )
          subQ.push(curNode->right);
        if ( curNode->mid != 0 )
          subQ.push(curNode->mid);

        words.push_back(curNode->iword);
        count++;
        if ( !iQ.empty() && !subQ.empty() ) {
          if ( iQ.top()->ifreqs >= subQ.top()->subfreqs ) {
            curNode = iQ.top();
            iQ.pop();
            usingI = true;
          }
          else {
            curNode = subQ.top();
            subQ.pop();
            if ( curNode->ifreqs != curNode->subfreqs )
              iQ.push(curNode);
            usingI = false;
          }
        }
        else if ( iQ.empty() && !subQ.empty() ) {
          curNode = subQ.top();
          subQ.pop();
          if ( curNode->ifreqs != curNode->subfreqs )
            iQ.push(curNode);          
          usingI = false;
        }
        else if ( !iQ.empty() && subQ.empty() ) {
          curNode = iQ.top();
          iQ.pop();
          usingI = true;
        }   
        else
          break;
      }

      else if ( curNode->left != 0 && 
          curNode->left->subfreqs == curNode->subfreqs ) {

        bool skip = false;
        if (curNode->right != 0)
          subQ.push( curNode->right );
        if (curNode->mid != 0)
          subQ.push( curNode->mid );
        if ( curNode->left->end && curNode->left->ifreqs != curNode->subfreqs )
          iQ.push(curNode->left);
        else if ( curNode->left->end && 
             curNode->left->ifreqs == curNode->subfreqs ) {
          words.push_back ( curNode->left->iword );
          count++;
          curNode = curNode->left;
          if ( curNode->left != 0 )
            subQ.push( curNode->left);
          if (curNode->right != 0)
            subQ.push( curNode->right);
          if (curNode->mid != 0)
            subQ.push(curNode->mid);
          if ( !iQ.empty() && !subQ.empty() ) {
            if ( iQ.top()->ifreqs >= subQ.top()->subfreqs ) {
              curNode = iQ.top();
              iQ.pop();
              usingI = true;
            }
            else {
              curNode = subQ.top();
              subQ.pop();
              if ( curNode->ifreqs != curNode->subfreqs )
                iQ.push(curNode);
              usingI = false;
            }
          }
          else if ( iQ.empty() && !subQ.empty() ) {
            curNode = subQ.top();
            subQ.pop();
            if ( curNode->ifreqs != curNode->subfreqs )
              iQ.push(curNode);
            usingI = false;
          }
          else if ( !iQ.empty() && subQ.empty() ) {
            curNode = iQ.top();
            iQ.pop();
            usingI = true;
          }
          else
            break;
          skip = true;
        }
        if ( !skip ) 
          curNode = curNode->left;
      }
      else if ( curNode->right != 0 && 
          curNode->right->subfreqs == curNode->subfreqs ) {

        bool skip = false;
        if (curNode->left != 0)
          subQ.push( curNode->left );
        if (curNode->mid != 0)
          subQ.push( curNode->mid );
        if (curNode->right->end && curNode->right->ifreqs != curNode->subfreqs)
          iQ.push(curNode->right);
        else if ( curNode->right->end && 
             curNode->right->ifreqs == curNode->subfreqs ) {
          words.push_back ( curNode->right->iword );
          count++;
          curNode = curNode->right;
          if ( curNode->left != 0 )
            subQ.push( curNode->left);
          if (curNode->right != 0)
            subQ.push( curNode->right);
          if (curNode->mid != 0)
            subQ.push(curNode->mid);
          if ( !iQ.empty() && !subQ.empty() ) {
            if ( iQ.top()->ifreqs >= subQ.top()->subfreqs ) {          

              curNode = iQ.top();
              iQ.pop();
              usingI = true;
            }
            else {          

              curNode = subQ.top();
              subQ.pop();
              if ( curNode->ifreqs != curNode->subfreqs )
                iQ.push(curNode);
              usingI = false;
            }
          }
          else if ( iQ.empty() && !subQ.empty() ) {          
            curNode = subQ.top();
            subQ.pop();
            if ( curNode->ifreqs != curNode->subfreqs )
                iQ.push(curNode);
            usingI = false;
          }
          else if ( !iQ.empty() && subQ.empty() ) {

            curNode = iQ.top();
            iQ.pop();
            usingI = true;
          }
          else
            break;
          skip = true;
        }
        if ( !skip ) 
          curNode = curNode->right;

      }
      else if ( curNode->mid != 0 && 
          curNode->mid->subfreqs == curNode->subfreqs ) {

        bool skip = false;
        if (curNode->right != 0)
          subQ.push( curNode->right );
        if (curNode->left != 0)
          subQ.push( curNode->left );
        if ( curNode->mid->end && curNode->mid->ifreqs != curNode->subfreqs)
          iQ.push(curNode->mid);
        else if ( curNode->mid->end && 
             curNode->mid->ifreqs == curNode->subfreqs ) {
          words.push_back ( curNode->mid->iword );
          count++;
          curNode = curNode->mid;          
          if ( curNode->left != 0 )
            subQ.push( curNode->left);
          if (curNode->right != 0)
            subQ.push( curNode->right);
          if (curNode->mid != 0)
            subQ.push(curNode->mid);
          if ( !iQ.empty() && !subQ.empty() ) {
            if ( iQ.top()->ifreqs >= subQ.top()->subfreqs ) {
              curNode = iQ.top();
              iQ.pop();
              usingI = true;
            }
            else {
              curNode = subQ.top();
              subQ.pop();
              if ( curNode->ifreqs != curNode->subfreqs )
                iQ.push(curNode);
              usingI = false;
            }
          }
          else if ( iQ.empty() && !subQ.empty() ) {
            curNode = subQ.top();
            subQ.pop();
            if ( curNode->ifreqs != curNode->subfreqs )
              iQ.push(curNode);
            usingI = false;
          }
          else if ( !iQ.empty() && subQ.empty() ) {
            curNode = iQ.top();
            iQ.pop();
            usingI = true;
          }
          else
            break;
          skip = true;
        }
        if ( !skip ) 
          curNode = curNode->mid;
      } 

    }  // end of !usingI else



  }// end of while

  for( unsigned int i = 0; i < words.size(); i++ ) {
    std::cout<<words[i]<<std::endl;
  }
  return words;

}

/* Destructor */
DictionaryTrie::~DictionaryTrie(){
  deleteAll(root);
  root = nullptr;
  return;
}

/** a function to delete all node on the tree */
void DictionaryTrie::deleteAll( TTNode* n ) {

  /** base case */
  if ( n == nullptr ) return;
  /* recursively call to delete all node */
  deleteAll(n->left);
  deleteAll(n->mid);
  deleteAll(n->right);
  delete n;
  n = 0;

}
