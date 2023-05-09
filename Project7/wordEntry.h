#ifndef WORD_ENTRY_H
#define WORD_ENTRY _H

#include <string>
#include <list>
using namespace std;

// struct that holds the word and the line numbers of the word in the text
struct TextEntry
{
  string word;
  int frequency;
  list<int> lineNumbers;
  int lastLine;

  // constructor for the Key
  string Key() const;

};




#endif