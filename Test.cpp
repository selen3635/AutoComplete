#include "DictionaryTrie.hpp"
#include <iostream>
#include <fstream>
#include <algorithm>
//#include "util.hpp"

using namespace std;

int main()
{
  /* check for insert */
  DictionaryTrie * dTrie = new DictionaryTrie();
  
  /* insert an empty word */
  if(!dTrie->insert("",2))
    cout<<"1empty word \n";
  
  /* insert empty freq */
  if(!dTrie->insert("ads",0))
    cout<<"2empty freq \n";
  
  /* both empty */ 
  if(!dTrie->insert("",0))
    cout<<"3both empty \n";
  
  /* find nothing */
  if(!dTrie->find("sdsd"))
    cout<<"4empty root \n";
  
  /* nothing put */
  if(!dTrie->find(""))
    cout<<"5empty input \n";

  /* insert a normal word */
  dTrie->insert("cool",2);
  if(dTrie->find("cool"))
    cout<<"6find cool \n";
  
  cout << dTrie->insert("apple",5) << endl;
  cout << dTrie->insert("appla",6) << endl;
  if(dTrie->find("apple"))
    cout<<"7find apple \n";
  if(dTrie->find("appla"))
    cout<<"8find appla \n";
  if(!dTrie->find("b"))
    cout<<"9cannot find b \n";
  if(!dTrie->find("applb"))
    cout<<"10cannot find applb \n";
  
  if(dTrie->insert("i",1))
  {
    if(dTrie->insert("just",2))
    {
     if(dTrie->insert("met",3))
    {
      if(dTrie->insert("this",2))
      {
        if(dTrie->insert("is",2))
        {

          if(dTrie->insert("crazy",2))
          {

             if(dTrie->insert("call",2))
             {
 cout << dTrie->insert("call", 2)<<endl; 
cout << "aaaaaaaaaaaaaaaaaa" << endl; 
               if(!dTrie->insert("call",2))
               {
               if(!dTrie->insert("crazy",3))
               {
               if(!dTrie->insert("is",4))
               {
             
               if(!dTrie->insert("this",2))
               {
             
               if(!dTrie->insert("met",2))
               {
               if(!dTrie->insert("just",2))
               {
             
               if(!dTrie->insert("i",2))
               {
                 cout<<"win!!!! \n";
               }
               }
             
               }
               }
               }
             
               }
             
               }
             }
          }
        }

      }
    }
    }
  }  
  //std::ifstream in;
  //in.open("dictionary/freq_dict.txt", ios::binary); 
  //Utils::load_dict(dTrie, in, 10);
  return 0; 
}
