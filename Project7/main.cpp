// USING LATE PASS #1
// Programmer: Dakota Ponder
// File: main.cpp
// Due: 11/23/22
// Description: This program will read in a file of data and store it
// in a binary search tree. It will then display the concurrence of words
// in the file and the number of times they occur.

#include "BST.h"
#include "wordEntry.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
using namespace std;


// converts the file to a text file
ofstream logFile;

// function prototypes
void PrintHeader();
void PrintItem(TextEntry &AnItem);
bool ReadFile(const string &fileName, char *&buffer, int &length);
void ArrangeContents(char *&buffer);
char *GetNextWord(char *buffer, string &word, int &lineNumber);


// function that prints a header for the program
void PrintHeader() {
  cout << endl << endl;
  cout << "---------------- ------------ "
          "-------------------------------------------\n";
  cout << "Word                Frequency Occurs on Lines                       "
          "     \n";
  cout << "---------------- ------------ "
          "-------------------------------------------\n";

  logFile << endl << endl;
  logFile << "---------------- ------------ "
             "-------------------------------------------\n";
  logFile << "Word                Frequency Occurs on Lines                    "
             "        \n";
  logFile << "---------------- ------------ "
             "-------------------------------------------\n";
}

// name: PrintItem
void PrintItem(TextEntry &AnItem) {
  string buffer = "";
  char tempIntegerHolder[20];
  list<int>::iterator i = AnItem.lineNumbers.begin();

  cout << left << setw(16) << AnItem.word.substr(0, 16) << " ";
  cout << right << setw(12) << AnItem.frequency << "      ";
  if (AnItem.frequency > 0) {
    cout << *i;
    i++;
    for (; i != AnItem.lineNumbers.end(); i++) {
      cout << ", ";
      cout << *i;
    }
    cout << endl;
  }

  return;
}

// function that reads the file and parses the words
bool ReadFile(const string &fileName, char *&buffer, int &length) {
  bool success = false;

  ifstream input;

  // open the file for reading in binary mode 
  // opened the file in binary mode to avoid problems with carriage returns
  // and line feeds. 
  input.open(fileName.c_str(), ios::binary);

  // if the file opened successfully
  if (input) {
    
    // use seekg to find the length of the file by seeking to the end 
    input.seekg(0, ios::end);
    
    // get the length of the file with tellg 
    // tellg returns the current position in the file
    length = input.tellg();
    
    // go to the beginning of the file
    input.seekg(0, ios::beg);

    // allocate memory:
    buffer = new char[length];

    if (buffer) {
      
      // read the file into the buffer as a block of data 
      input.read(buffer, length);
      success = true;
    }
    // close the file
    input.close();
  }

  return success;
}


// function that parses the buffer for words
void ArrangeContents(char *&buffer) {
  if (buffer) {
    // curLoc points to cur read location in buffer
    // curWrite points to cur write location in buffer
    // lastWrite points to the lastWrite write location in buffer
    char *curLoc = buffer;
    char *curWrite = buffer;
    char *lastWrite = NULL;


    // for the next word in the buffer 
    // write the word to the curWrite write location
    for (; *curLoc; curLoc++) {
      
      // convert to lower case if upper case
      // then copy 
      if (*curLoc <= 'Z' && *curLoc >= 'A') {
        *curWrite = tolower(*curLoc);  
        lastWrite = curWrite;
        curWrite++;
      }

      // if lower case, copy it 
      else if (*curLoc <= 'z' && *curLoc >= 'a') {
        *curWrite = *curLoc;
        lastWrite = curWrite;
        curWrite++;
      }

      
      // if buffer is a new line, check if last char was a space
      // if so, overwrite the space
      // if not, copy the char 
      else if (*curLoc == '\n') {
        if (lastWrite && *lastWrite == ' ') {
          *lastWrite = *curLoc;
        } else {
          *curWrite = *curLoc;
          lastWrite = curWrite;
          curWrite++;
        }
      }

      
      // else copy over a space instead of the char 
      else {
        if (lastWrite && *lastWrite != ' ' && *lastWrite != '\n') {
          *curWrite = ' ';
          lastWrite = curWrite;
          curWrite++;
        }
      }
    }
    if (*lastWrite == ' ' || *lastWrite == '\n') {
      *lastWrite = 0;
    }
    *curWrite = 0;
  }
}


// function that gets the next word from the buffer and returns it
char *GetNextWord(char *buffer, string &word, int &lineNumber) {
  static char const *keys = " \n";
  if (buffer) {
    char *newWord = NULL;
    size_t i = 0, position = 0;

    while (*buffer == ' ') {
      buffer++;
    }

    while (*buffer == '\n') {
      lineNumber++;
      buffer++;
    }

    // find the position of the next space or newline or the end of the buffer
    position = strcspn(buffer, keys);

    // create a new substring to temporarily hold the new word.
    newWord = new char[position + 1]; // +1 for the null terminator
    // newWord = (char *)malloc(position + 1);

    // copy the newWord using strncpy
    strncpy(newWord, buffer, position);

    // add a null terminator to the end of the newWord to make it a string
    newWord[position] = 0;

    // copy the newWord into word
    word = newWord;

    // update buffer to point to the next word
    buffer += position;

    // free the memory allocated for newWord
    delete[] newWord;
    // free(newWord);
  }

  return buffer;
}


// main function
int main() {

  // contents will hold the contents of the file
  // pointToLocation will point to a location in contents for the next word read
  char *contents = NULL, *pointToLocation = NULL;

  // length specifies the length of the contents
  // currentlineNumber specifies the current line number
  int length = 0, currentlineNumber = 1;

  // userInput will hold user input
  // word will hold the current word

  string userInput;
  string word;

  // binary search tree that holds word records
  BinarySearchTree wordTree;

  // used for updating and adding
  TextEntry userEntry;
  bool success;  // used for checking if a word was added or updated

  // display the welcome message to match program output
  cout << "This program will read a file and create a list of word frequency\n";
  cout << "and line numbers.\n\n";

  // while the contents of the file are not read, keep asking for a file name
  while (!contents) {
    cout << "Please enter the name of the file to read:  ";

    // get the file name from the user
    getline(cin, userInput);

    // read the file and store the contents in contents
    ReadFile(userInput, contents, length);

    // if the file was not read, display an error message
    if (!contents) {
      cout << "\nSorry, but the file " << userInput << " was inaccessible.\n\n";
    }
  }

  // convert the file into a .log file
  // this is done by replacing all non-alphanumeric characters with spaces
  // we need to do this because we want to count the frequency of words
  // and not the frequency of characters
  userInput = userInput + ".log";

  // open the logfile for output
  logFile.open(userInput.c_str());

  // arrange the contents for parsing
  ArrangeContents(contents);

  //
  pointToLocation = contents;
  currentlineNumber = 1;


  // as long pointToLocation is not pointing to a null terminator
  // keep inserting and updating entries in the binarysearch tree
  while (*pointToLocation) {

    // get the next word in the contents
    pointToLocation = GetNextWord(pointToLocation, word, currentlineNumber);

    // try to get the word from the search tree
    wordTree.SearchTreeRetrieve(word, userEntry, success);

    // if successful
    if (success) {

      // update list of linenumbers if necessary
      if (userEntry.lastLine != currentlineNumber) {
        userEntry.lineNumbers.push_back(currentlineNumber);
        userEntry.lastLine = currentlineNumber;
      }

      // increment the frequency of the word
      userEntry.frequency++;

      // delete the word userEntry because we are going to update it
      wordTree.SearchTreeDelete(word, success);

      if (success) {
        // insert the new copy into the tree
        wordTree.SearchTreeInsert(userEntry, success);
      }

      // clear up the userEntry
      userEntry.word = "";
      userEntry.lineNumbers.clear();
      userEntry.frequency = 0;
      userEntry.lastLine = 0;
    }

    // if not successful, insert a new userEntry
    else {
      // since the word doesn't exist in the tree
      // insert it into the tree
      userEntry.frequency = 1;
      userEntry.lastLine = currentlineNumber;
      userEntry.lineNumbers.push_back(currentlineNumber);
      userEntry.word = word;
      wordTree.SearchTreeInsert(userEntry, success);

      // clear up the userEntry
      userEntry.word = "";
      userEntry.lineNumbers.clear();
      userEntry.frequency = 0;
      userEntry.lastLine = 0;
    }
  }

  // print the words to match program requirements
  PrintHeader();
  wordTree.InorderTraverse(PrintItem);

 // exit message
  cout << "\n\nThank you for using our program.\n\n";

  // clean up the memory
  if (logFile)
    // close the log file
    logFile.close();
  delete[](contents);

  return 0;
}
