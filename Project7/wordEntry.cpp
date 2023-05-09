#ifndef WORDENTRY_CPP
#define WORDENTRY_CPP

#include <string>
#include "wordEntry.h"
using namespace std;

// function that returns the word that was read
string TextEntry::Key() const
{
  return word;
}
#endif