#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H
#include <string.h>
#define MAX_LAST_NAME_SIZE 16

#define BST
#define AVL

/* TODO: After modifying the original version, uncomment the following
 * line to set OPT properly */
// #define OPT 1
typedef struct __FULL_PHONE_BOOK_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
    struct __FULL_PHONE_BOOK_ENTRY *pNext;
} full_entry;

#ifndef BST
typedef struct __PHONE_BOOK_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    struct __PHONE_BOOK_ENTRY *pNext;
    struct __FULL_PHONE_BOOK_ENTRY *fullEntry;
}entry;
#endif

#ifdef BST
typedef struct __BST_PHONE_BOOK{
    char lastName[MAX_LAST_NAME_SIZE];
    struct __BST_PHONE_BOOK *pR;
    struct __BST_PHONE_BOOK *pL;
    struct __FULL_PHONE_BOOK_ENTRY *fullEntry;
#ifdef AVL
    int level;
#endif
}entry;
#endif


entry *findName(char lastname[], entry *pHead);
entry *append(char lastName[], entry *e);

#ifdef HASH
#define HASH_TABLE_SIZE 1000
entry *hash_table[HASH_TABLE_SIZE];
#endif

#endif
