#include <stdlib.h>

#include "phonebook_opt.h"

#ifdef _HASH
int hash31(char *s)
{
    unsigned value = 0;
    for (; (*s) !='\0'; s++)
        value = (value << 5) - (value + (*s));
    return value % MAX_HASH_SIZE;
}
#endif


/* FILL YOUR OWN IMPLEMENTATION HERE! */
entry *findName(char lastname[], entry *pHead)
{
#ifdef NOMAL
    while (pHead != NULL) {
        if (strcasecmp(lastname, pHead->lastName) == 0)
            return pHead;
        pHead = pHead->pNext;
    }
    /* TODO: implement */
    return NULL;
#endif
#ifdef _HASH
    int hash_num = hash31(lastname);
    entry *t = hash_table[hash_num]; 
    while (t != NULL) {
        if (strcasecmp(lastname, t->lastName) == 0)
            return t;
        t = t->pNext;
    }
    return NULL;
#endif
#ifdef _BST
#endif

}

entry *append(char lastName[], entry *e)
{
#ifdef NOMAL
    e->pNext = (entry *) malloc(sizeof(entry));
    e = e->pNext;
    strcpy(e->lastName, lastName);
    e->pNext = NULL;
    return e;
#endif
#ifdef _HASH
    int hash_num = hash31(lastName);
    entry *tmp = (entry *)malloc(sizeof(entry));
    strcpy(t->lastName,lastName);
    if(hash_table[num]==NULL){
	hash_table[hash_num] = tmp;
	return NULL;
    }
    else{
	t->pNext = hash_table[hash_num];
	hash_table[hash_num] = t;
	return NULL;
    }
#endif
}
