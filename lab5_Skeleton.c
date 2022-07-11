//
// APS105 Lab 5 
//
// Program for maintaining a personal phone book.
//
// Uses a linked list to hold the phone book entries.
//
// Author: <Michael Nguyen>
// Student Number: <1007503989>
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

//**********************************************************************
// Linked List Definitions
//  Define your linked list node and pointer types
//  here for use throughout the file.
//
//   ADD STATEMENT(S) HERE

typedef struct node{
    char* lname;
    char* fname;
    char* address;
    char* phone;
    struct node* next;
}Node;

typedef struct llist{
    Node* head;
}LinkedList;

//**********************************************************************
// Linked List Function Declarations
//
// Functions that modify the linked list.
//   Declare your linked list functions here.
//
//   ADD STATEMENT(S) HERE

LinkedList* initlist();
Node* newNode();
void insertNode(LinkedList* book, Node* newnode);
void deleteNode (char* lname,LinkedList* book);
void checkPhoneNum(char* phonenum, LinkedList* book);
void checkFamilyName(char* familyname,LinkedList* book);
void printNode();
void printList(LinkedList*book);
void deleteBook(LinkedList* book);

//**********************************************************************
// Support Function Declarations
//

void safegets (char s[], int arraySize);        // gets without buffer overflow
void familyNameDuplicate (char familyName[]);   // marker/tester friendly
void familyNameFound (char familyName[]);       //   functions to print
void familyNameNotFound (char familyName[]);    //     messages to user
void familyNameDeleted (char familyName[]);
void phoneNumberFound (char phoneNumber[]);
void phoneNumberNotFound (char phoneNumber[]);
void printPhoneBookEmpty (void);
void printPhoneBookTitle (void);

//**********************************************************************
// Program-wide Constants
//

const int MAX_LENGTH = 1023;
const char NULL_CHAR = '\0';
const char NEWLINE = '\n';

//**********************************************************************
// Main Program
//

int main (void)
{
    const char bannerString[]
        = "Personal Phone Book Maintenance Program.\n\n";
    const char commandList[]
        = "Commands are I (insert), D (delete), S (search by name),\n"
          "  R (reverse search by phone #), P (print), Q (quit).\n";

    // Declare linked list head.
    //   ADD STATEMENT(S) HERE TO DECLARE LINKED LIST HEAD.
    
    LinkedList* book = initlist();

    // announce start of program
    printf("%s",bannerString);
    printf("%s",commandList);

    char response;
    char input[MAX_LENGTH+1];
    do
    {
        printf("\nCommand?: ");
        safegets(input,MAX_LENGTH+1);
        // Response is first char entered by user.
        // Convert to uppercase to simplify later comparisons.
        response = toupper(input[0]);
        
        if (response == 'I')
        {
            // Insert an phone book entry into the linked list.
            // Maintain the list in alphabetical order by family name.
            //   ADD STATEMENT(S) HERE
            
            printf("  family name: ");
            char* lname = (char*)malloc(MAX_LENGTH + 1);
            safegets(lname, MAX_LENGTH);
            printf("  first name: ");
            char* fname = (char*)malloc(MAX_LENGTH + 1);
            safegets(fname, MAX_LENGTH);
            printf("  address: ");
            char* address = (char*)malloc(MAX_LENGTH + 1);
            safegets(address, MAX_LENGTH);
            printf("  phone number: ");
            char* phonenum = (char*)malloc(MAX_LENGTH + 1);
            safegets(phonenum, MAX_LENGTH);
            Node* newnode = newNode(fname,lname,address,phonenum);

            insertNode(book,newnode);

        }
        else if (response == 'D')
        {
            // Delete an phone book entry from the list.

            printf("\nEnter family name for entry to delete: ");

            //   ADD STATEMENT(S) HERE
            char* lname = (char*)malloc(MAX_LENGTH + 1);
            deleteNode(lname,book);

        }
        else if (response == 'S')
        {
            // Search for an phone book entry by family name.

            printf("\nEnter family name to search for: ");

            //   ADD STATEMENT(S) HERE
            char familyname[MAX_LENGTH + 1];
            safegets(familyname, MAX_LENGTH);  
            checkFamilyName(familyname,book);

        }
        else if (response == 'R')
        {
            // Search for an phone book entry by phone number.

            printf("\nEnter phone number to search for: ");
            
            //   ADD STATEMENT(S) HERE

            char phonenum[MAX_LENGTH + 1];
            safegets(phonenum, MAX_LENGTH);
            checkPhoneNum(phonenum,book);
        }
        else if (response == 'P')
        {
            // Print the phone book.
            //   ADD STATEMENT(S) HERE
            printList(book);
        }
        else if (response == 'Q')
        {
            ; // do nothing, we'll catch this below
        }
        else
        {
            // do this if no command matched ...
            printf("\nInvalid command.\n%s\n",commandList);
        }
    } while (response != 'Q');

    // Delete the whole phone book linked list.
    //   ADD STATEMENT(S) HERE
    deleteBook(book);
    // Print the linked list to confirm deletion.
    //   ADD STATEMENT(S) HERE
    printList(book);
    return 0;
}

//**********************************************************************
// Support Function Definitions

// Function to get a line of input without overflowing target char array.
void safegets (char s[], int arraySize)
{
    int i = 0, maxIndex = arraySize-1;
    char c;
    while (i < maxIndex && (c = getchar()) != NEWLINE)
    {
        s[i] = c;
        i = i + 1;
    }
    s[i] = NULL_CHAR;
}

// Function to call when user is trying to insert a family name
// that is already in the book.
void familyNameDuplicate (char familyName[])
{
    printf("\nAn entry for <%s> is already in the phone book!\n"
           "New entry not entered.\n",familyName);
}

// Function to call when a family name was found in the phone book.
void familyNameFound (char familyName[])
{
    printf("\nThe family name <%s> was found in the phone book.\n",
             familyName);
}

// Function to call when a family name was not found in the phone book.
void familyNameNotFound (char familyName[])
{
    printf("\nThe family name <%s> is not in the phone book.\n",
             familyName);
}

// Function to call when a family name that is to be deleted
// was found in the phone book.
void familyNameDeleted (char familyName[])
{
    printf("\nDeleting entry for family name <%s> from the phone book.\n",
             familyName);
}

// Function to call when a phone number was found in the phone book.
void phoneNumberFound (char phoneNumber[])
{
    printf("\nThe phone number <%s> was found in the phone book.\n",
             phoneNumber);
}

// Function to call when a phone number was not found in the phone book.
void phoneNumberNotFound (char phoneNumber[])
{
    printf("\nThe phone number <%s> is not in the phone book.\n",
             phoneNumber);
}

// Function to call when printing an empty phone book.
void printPhoneBookEmpty (void)
{
    printf("\nThe phone book is empty.\n");
}

// Function to call to print title when whole phone book being printed.
void printPhoneBookTitle (void)
{
    printf("\nMy Personal Phone Book: \n");
}

//**********************************************************************
// Add your functions below this line.
//   ADD STATEMENT(S) HERE

LinkedList* initlist(){
    LinkedList* list = (LinkedList*)malloc(sizeof(LinkedList));
    list -> head = NULL;
    return list;
}

Node* newNode(char* fname, char* lname, char* address, char* phonenum){
    Node* node = (Node*)malloc(sizeof(Node));
    node->address = address;
    node->fname = fname;
    node->lname = lname;
    node->phone = phonenum;
    node->next = NULL;
    return node;
}

void insertNode(LinkedList* book, Node* newnode){
    
    if (book->head == NULL){
        book->head = newnode;
    }

    else if (strcmp(newnode->lname,book->head->lname) < 0){
        newnode->next = book->head;
        book->head = newnode;
    }
    
    else{
        Node* on = book->head;
        
        while ((strcmp(on->lname,newnode->lname) != 0) && on->next != NULL && strcmp(newnode->lname,on->next->lname) >= 0){
            on = on->next;
        }
        if (strcmp(on->lname,newnode->lname) == 0){
            familyNameDuplicate(on->lname);
            return;
        }
        newnode->next = on->next;
        on->next = newnode;
    }
}

void deleteNode (char* lname,LinkedList* book){
    if (book->head == NULL){
        familyNameNotFound(lname);
        return;
    }
    Node* on = book->head;
    
    while ((strcmp(on->lname,lname) != 0) && on->next != NULL && (strcmp(on->next->lname,lname) != 0)){
        on = on->next;
    }

    if (strcmp(on->lname,lname) == 0){
        Node* temp = on;
        free(temp);
        book->head = NULL;
    }
    else if (strcmp(on->next->lname,lname) == 0){
        Node* temp = on->next;
        on->next = on->next->next;
        free(temp);
        familyNameDeleted(lname);
    }
    else{
        familyNameNotFound(lname);
    }
}

void checkFamilyName(char* familyname,LinkedList* book){
    Node* on = book->head;
    while (on != NULL){
        if (strcmp(on->lname,familyname) == 0){
            familyNameFound(familyname);
            printNode(on);
            return;
        }
        on = on->next;
    }
    familyNameNotFound(familyname);
}

void checkPhoneNum(char* phonenum,LinkedList* book){
    Node* on = book->head;
    while (on != NULL){
        if (strcmp(on->phone,phonenum) == 0){
            phoneNumberFound(phonenum);
            printNode(on);
            return;
        } 
        on = on->next;
    }
    phoneNumberNotFound(phonenum);
}

void printNode(Node* on){
    printf("\n%s\n%s\n%s\n%s\n",on->lname, on->fname, on->address, on->phone);
}

void printList(LinkedList* book){
    Node* on = book->head;
    while (on != NULL){
        printNode(on);
        on = on->next;
    }
    printf("\n");
}

void deleteBook(LinkedList* book){
    Node* on = book->head;
    while (on != NULL){
        Node* temp = on;
        free(temp->address);
        free(temp->fname);
        free(temp->lname);
        free(temp->phone);
        free(temp);
        on = on->next;
    }
    free(book);
}