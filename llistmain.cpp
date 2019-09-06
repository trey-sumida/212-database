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
//  DATE:        November 22, 2018
//
//  FILE:        llistmain.cpp
//
//  DESCRIPTION:
//   This file contains the user-interface function for the database
//
****************************************************************/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstring>
#include <climits>
#include "llist.h"

using namespace std;

/****************************************************************
//
//  FUNCTION NAME:  getaddress
//
//  DESCRIPTION:    A function to obtain the users address
//
//  PARAMETERS:     address (char[]) : Array to store the user address
//                  size (int) : size of the address array
//
//  RETURN VALUES:  Void
//
****************************************************************/

void getaddress(char address[], int size)
{
    char temp[100];
    bool more;
    int i;
 
    i = 0;
    more = true;
    cin.ignore();
    cout << "Enter your address: ";
    cin.get(address, size - 1);
    while(more)
    {
        cin.ignore();
        cin.get(temp, 99);
        if(temp[0] == '\n' || temp[0] == '\0')
        {
            more = false;
        }
        else
        {
            int len = strlen(address);
            while(i < len)
            {
                i++;
            }
            address[i] = '\n';
            strcat(address, temp);
        }
    }
    cin.ignore();
}

/****************************************************************
//
//  FUNCTION NAME:  main
//
//  DESCRIPTION:    A userinterface function for the database
//
//  PARAMETERS:     None
//
//  RETURN VALUES:  0 : success
//                 -1 : function failed
//
****************************************************************/

int main()
{
    ifstream file;
    int accountNo;
    char name[50];
    char address[100];
    char menu[20];
    char add[] = "add";
    char quit[] = "quit";
    char printall[] = "printall";
    char print[] = "print";
    char del[] = "delete";
    char rev[] = "reverse";
    char filename[] = "database.txt";
    bool run;
    int length;
    llist *llist1;

    run = true;
    length = 99;
    file.open(filename);
    if(!file)
    {
        llist1 = new llist();
    }
    else
    {
        llist1 = new llist(filename);
    }

    while (run)
    {
        cout << "Please type one of the following commands: \n";
        cout << "Type 'add' to add a new record \n";
        cout << "Type 'print' to print information about a record\n";
        cout << "Type 'printall' to print all records in the database\n";
        cout << "Type 'delete' to delete a record \n";
        cout << "Type 'reverse' to reverse order of the database\n";
        cout << "Type 'quit' to exit the program\n";
        cin.get(menu, 20);

        if(strcmp(menu, quit) == 0)
        {
            run = false;
            cout << "Exiting the program\n";
        }
        else if(strcmp(menu, add) == 0)
        {
            cout << "Please enter your account number: ";
            cin >> accountNo;
            cin.ignore();
            cout << "Please enter your name: ";
            cin.get(name, 50);
            getaddress(address, length);
            
            if(llist1->addRecord(accountNo, name, address) == 0)
            {
                cout << "Successfully added account " << accountNo << " to the database \n";
            }
        }
        else if(strcmp(menu, print) == 0)
        {
             cout << "Please enter your account number: ";
             cin >> accountNo;
             cin.ignore();
             if(llist1->printRecord(accountNo) == -1)
             {
                 cout << "ERROR: Record not found\n";
             }
        }
        else if(strcmp(menu, printall) == 0)
        {
             cout << *llist1;
        }
        else if(strcmp(menu, del) == 0)
        {
            cout << "Please enter your account number: ";
            cin >> accountNo;
            cin.ignore();
            if(llist1->deleteRecord(accountNo) == 0)
            {
                cout << "Successfully deleted account " << accountNo << "\n";
            }
            else
            {
                cout << "Account " << accountNo << " not found\n";
            }
        }
        else if(strcmp(menu, rev) == 0)
        {
            llist1->reverse();
        }        
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
delete llist1;
return 0;
}
