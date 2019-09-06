#ifndef llist_h
#define llist_h

#include "record.h"
#include <iostream>

using namespace std;

class llist
{
  private:
    record * start;
    char filename[16];
    int readfile();
    void writefile();
    record * reverse(record *);
    void cleanup();


  public:
    llist();
    llist(char[]);
    ~llist();
    int addRecord(int, char[], char[]);
    int printRecord(int);
    friend std::ostream& operator<<(ostream&, const llist&);
    int deleteRecord(int);
    void reverse();
};

#endif /* llist_h */
