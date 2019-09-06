/*****************************************************************
//
//  NAME:        Trey Sumida
//
//  HOMEWORK:    Project 2
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        November 18, 2018
//
//  FILE:        llist.cpp
//
//  DESCRIPTION:
//   This file contains the definitions of the functions in the
//   class llist
//
****************************************************************/

#include <iomanip>
#include <iostream>
#include <fstream>
#include <string.h>
#include "llist.h"
#define DEBUG
using namespace std;

/****************************************************************
//
//  FUNCTION NAME:  llist
//
//  DESCRIPTION:    Constructor for the class llist
//
//  PARAMETERS:     
//
//  RETURN VALUES:  None
//
****************************************************************/

llist :: llist()
{
    start = NULL;
    strcpy(filename, "database.txt");
}

/****************************************************************
//
//  FUNCTION NAME:  llist
//
//  DESCRIPTION:    Constructor for the class llist
//
//  PARAMETERS:     file (char[]) : name of the file the database is stored in
//
//  RETURN VALUES:  None
//
****************************************************************/

llist :: llist(char file[])
{
    start = NULL;
    strcpy(filename, file);
    readfile();
}

/****************************************************************
//
//  FUNCTION NAME:  ~llist
//
//  DESCRIPTION:    Destructor function for the class llist
//
//  PARAMETERS:     None
//
//  RETURN VALUES:  None
//
****************************************************************/

llist :: ~llist()
{
    writefile();
    cleanup();
}

/****************************************************************
//
//  FUNCTION NAME:  writefile
//
//  DESCRIPTION:    Writes a record database to a file
//
//  PARAMETERS:     
//
//  RETURN VALUES:  0 : success
//                 -1 : failed to write
//
****************************************************************/

void llist :: writefile()
{
    record * temp = start;
    if(temp!= NULL)
    { 
        ofstream file;
        file.open(filename);

        while(temp != NULL)
        {
            file << (*temp).accountno << "\n";
            file << (*temp).name << "\n";
            file << (*temp).address << "\n";
            file << "\n";
            temp = (*temp).next;
        }
        file.close();
    }
    #ifdef DEBUG
        cout << "writefile was called\n";
    #endif
}

/****************************************************************
//
//  FUNCTION NAME:  readfile
//
//  DESCRIPTION:    Reads a database from a file
//
//  PARAMETERS:     None
//
//  RETURN VALUES:  0 : success
//                 -1 : failed
//
****************************************************************/

int llist :: readfile()
{
    int read;
    int accno;
    string name;
    string address;
    string temp;
    char name2[25];
    char address2[80];

    read = 0;
    ifstream file;
    file.open(filename);
    
    while(file >> accno)
    {
        file.ignore();
        getline(file, name);
        getline(file, address);
        while(!getline(file, temp))
        {
            address = address + "\n" + temp;
        }
        strcpy(name2, name.c_str());
        strcpy(address2, address.c_str());
        addRecord(accno, name2, address2);
    }
        
    #ifdef DEBUG
        cout << "readfile was called\n";
    #endif
    return read;
}

/****************************************************************
//
//  FUNCTION NAME:  reverse
//
//  DESCRIPTION:    A function to reverse the list
//
//  PARAMETERS:     start (record *) : current record being looked at
//
//  RETURN VALUES:  record * : Returns the necessary record to reverse the list
//
****************************************************************/

record * llist :: reverse(record * start)
{
    record * temp;
    
    if(start->next == NULL)
    {
        return start;
    }
    else
    {
        temp = reverse(start->next);
        start->next->next = start;
        start->next = NULL;
        return temp;
    }
    #ifdef DEBUG
        cout << "reverse was called with the parameter record * " << start << "\n";
    #endif
}

/****************************************************************
//
//  FUNCTION NAME:  cleanup
//
//  DESCRIPTION:    Function to clean up any memory leaks
//
//  PARAMETERS:     None
//
//  RETURN VALUES:  None
//
****************************************************************/

void llist :: cleanup()
{
    #ifdef DEBUG
        cout << "cleanup was called\n";
    #endif
}

/****************************************************************
//
//  FUNCTION NAME:  addRecord
//
//  DESCRIPTION:    A function to add a record to the database
//
//  PARAMETERS:     count (int) : The account number being added
//                  name (char[]) : The name of the account
//                  address[] : The address of the account
//
//  RETURN VALUES:  0 : success
//                 -1 : failed
//
****************************************************************/

int llist :: addRecord(int accno, char name[], char address[])
{
    record * temp = new record;
    record * tempprev = new record;
    record * newrec = new record;
    int added;
    added = -1;
    
    (*newrec).accountno = accno;
    strcpy((*newrec).name, name);
    strcpy((*newrec).address, address);

    if(start == NULL)
    {
        strcpy((*temp).address, address);
        strcpy((*temp).name, name);
        (*temp).accountno = accno;
        (*temp).next = NULL;
        start = temp;
        added = 0;
    }
    else
    {   
        temp = start;
        if((*newrec).accountno < (*temp).accountno)
        {
            (*newrec).next = temp;
            start = newrec;
            added = 0;
        }
        else if ((*newrec).accountno > (*temp).accountno)
        {
            while (temp != NULL && (*newrec).accountno > (*temp).accountno)
            {
                tempprev = temp;
                temp = (*temp).next;
            }
            (*newrec).next = (*tempprev).next;
            (*tempprev).next = newrec;
            added = 0;
        }
        else
        {
            (*newrec).next = (*temp).next;
            (*temp).next = newrec;
            added = 0;
        }
    }
    #ifdef DEBUG
        cout << "addRecord was called with the parameters\n";
        cout << "int " << accno << "\n";
        cout << "char[] " << name << "\n";
        cout << "char[] " << address << "\n";
    #endif
return added;
}

/****************************************************************
//
//  FUNCTION NAME:  printRecord
//
//  DESCRIPTION:    A function that prints the information of an account
//
//  PARAMETERS:     accno (int) : number of the account being printed
//
//  RETURN VALUES:  0 : success
//                 -1 : failed
//
****************************************************************/

int llist :: printRecord(int accno)
{
    record * temp;
    int printed;
    
    printed = -1;
    temp = start;
    
    while(temp != NULL)
    {
        if((*temp).accountno == accno)
        {
            cout << "Account number: " << (*temp).accountno << "\n";
            cout << "Name: " << (*temp).name << "\n";
            cout << "Address: " << (*temp).address << "\n";
            temp = (*temp).next;
            printed = 0;
        }
        else
        {
            temp = (*temp).next;
        }
    }
    #ifdef DEBUG
        cout << "print was called with the parameter\n";
        cout << "int " << accno << "\n";
    #endif
return printed;
}

/****************************************************************
//
//  FUNCTION NAME:  operator<<
//
//  DESCRIPTION:    A function that prints the entire database
//
//  PARAMETERS:     out (ostream&) : stream being stored
//                  temp (llist&) : llist that wants to be printed
//
//  RETURN VALUES:  ostream& : out stream with print values
//
****************************************************************/

std::ostream& operator<<(ostream& out, const llist& temp)
{
    record * temp2;
    temp2 = temp.start;
    if(temp2 == NULL)
    {
        out << "Database is empty\n";
    }
    else
    {
        while(temp2 != NULL)
        {  
            out << "Account Number: " << (*temp2).accountno  << "\n";
            out << "Name: " << (*temp2).name << "\n";
            out << "Address: " << (*temp2).address << "\n";
            temp2 = (*temp2).next;
        }
    }
    #ifdef DEBUG
        cout << "printall was called with the paramenters:\n";
        cout << "ostream& " << &out << "\n";
        cout << "llist& " << &temp << "\n";
    #endif
return out;
}
 
/****************************************************************
//
//  FUNCTION NAME:  deleteRecord
//
//  DESCRIPTION:    Deletes a record in the account
//
//  PARAMETERS:     accno (int) : number of the account being deleted
//
//  RETURN VALUES:  0 : success
//                 -1 : failed
//
****************************************************************/

int llist :: deleteRecord(int accno)
{
    int deleted;
    record * temp;
    record * prevrec;

    deleted = -1;
    temp = start;
    prevrec = start;

    while(temp != NULL)
    {
        if(temp == start)
        { 
            if((*temp).accountno == accno)
            {
                start = (*temp).next;
                temp = (*temp).next;
                deleted = 0;
            }
            else
            {
                prevrec = temp;
                temp = (*temp).next;
            }
        }   
        else
        {
            if((*temp).accountno == accno)
            {
                (*prevrec).next = (*temp).next;
                temp = (*prevrec).next;
                deleted = 0;
            }
            else
            {
                prevrec = temp;
                temp = (*temp).next;
            }
        }
    }
    #ifdef DEBUG
        cout << "deleteRecord was called with the parameter:\n";
        cout << "int " << accno << "\n";
    #endif
return deleted;
}

/****************************************************************
//
//  FUNCTION NAME:  reverse()
//
//  DESCRIPTION:    Reverses the database
//
//  PARAMETERS:     None
//
//  RETURN VALUES:  void
//
****************************************************************/

void llist :: reverse()
{
    start = reverse(start);
    #ifdef DEBUG
        cout << "reverse was called\n";
    #endif
}
