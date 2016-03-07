#include <stdlib.h>

#include "phonebook_opt.h"

#ifdef HASH
int hash31(char *s)
{
    unsigned value = 0;
    for (; (*s) !='\0'; s++)
        value = (value << 5) - (value + (*s));
    return value % HASH_TABLE_SIZE;
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
#ifdef HASH
    int hash_num = hash31(lastname);
    entry *t = hash_table[hash_num]; 
    while (t != NULL) {
        if (strcasecmp(lastname, t->lastName) == 0)
            return t;
        t = t->pNext;
    }
    return NULL;
#endif
#ifdef BST
    while(pHead!=NULL){
        if(strcmp(pHead->lastName,lastname) > 0 )
            pHead = pHead->pL;
        else if(strcmp(pHead->lastName,lastname) < 0 )
            pHead = pHead->pR;
        else
            return pHead;
    }
    return NULL;
#endif

}

#ifdef AVL
entry *newnode(char lastName[]){
    entry *e = (entry *)malloc(sizeof(entry));
    strcpy(e->lastName,lastName);
    e->pL=NULL;
    e->pR=NULL;
    e->level=1;
    return e;
}

// A utility function to get height of the tree
int height(entry *e)
{
    if (e == NULL)
        return 0;
    return e->level;
}

// A utility function to get maximum of two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}

int getBalance(entry *e){
    if(e==NULL) return 0;
    return (height(e->pL) - height(e->pR));
}

entry *rightRotate(entry *e){
    entry *x = e->pL;
    entry *y = x->pR;

    //Perform rotation
    x->pR = e;
    e->pL = y;
    //Update level
    e->level = max(height(e->pL),height(e->pR))+1;
    x->level = max(height(x->pL),height(x->pR))+1;
    //return new root
    return x;
}

entry *leftRotate(entry *e){
    entry *x = e->pR;
    entry *y = x->pL;

    //Perform rotation
    x->pL = e;
    e->pR = y;
    //Update level
    e->level = max(height(e->pL),height(e->pR))+1;
    x->level = max(height(x->pL),height(x->pR))+1;
    //return new root
    return x;
}


entry *insert(char lastName[],entry *e){
    // 1.  Perform the normal BST rotation
    if(e==NULL) return(newnode(lastName));
    if(strcasecmp(lastName,e->lastName) < 0)
        e->pL = insert(lastName,e->pL);
    else
        e->pR = insert(lastName,e->pR);
    // 2. Get height of this ancestor node
    e->level = max(height(e->pL), height(e->pR)) + 1;
    /* 3. Get the balance factor of this ancestor node to check whether
     *        this node became unbalanced */
    int balance = getBalance(e);

    // If this node becomes unbalanced, then there are 4 cases
    // Left Left Case (LL case)
    if(balance > 1 && (strcasecmp(lastName,e->pL->lastName) < 0))
        return rightRotate(e);
    // Right Right Case
    if (balance < -1 && (strcasecmp(lastName,e->pR->lastName) > 0 ))
        return leftRotate(e);
    // Left Right Case
    if(balance > 1 && (strcasecmp(lastName,e->pL->lastName) > 0))
    {
        e->pL =  leftRotate(e->pL);
        return rightRotate(e);
    }
    // Right Left Case
    if (balance < -1 && (strcasecmp(lastName,e->pR->lastName) > 0 ))
    {
        e->pR = rightRotate(e->pR);
        return leftRotate(e);
    }
    /* return the (unchanged) node pointer */
    return e;
}
#endif

entry *append(char lastName[], entry *e)
{
#ifdef NOMAL
    e->pNext = (entry *) malloc(sizeof(entry));
    e = e->pNext;
    strcpy(e->lastName, lastName);
    e->pNext = NULL;
    return e;
#endif
#ifdef AVL
    return e = insert(lastName,e);
#endif
#ifdef HASH
    int hash_num = hash31(lastName);
    entry *tmp = (entry *)malloc(sizeof(entry));
    strcpy(tmp->lastName,lastName);
    if(hash_table[hash_num]==NULL){
        hash_table[hash_num] = tmp;
        return e;
    }
    else{
        tmp->pNext = hash_table[hash_num];
        hash_table[hash_num] = tmp;
        return e;
    }
#endif

#ifdef BST
    if(e==NULL){
        e = (entry *)malloc(sizeof(entry));
        strcpy(e->lastName,lastName);
        e->pR = NULL;
        e->pL = NULL;
        return e;
    }
    entry *t,*tmp = e;
    while(tmp!=NULL){
        if(strcasecmp(tmp->lastName,lastName) < 0 ){
            t = tmp;
            tmp = tmp->pR;
        }
        else if(strcasecmp(tmp->lastName,lastName) > 0 ){
            t = tmp;
            tmp = tmp->pL;
        }
    }
    if(strcasecmp(t->lastName,lastName) > 0){
        tmp = (entry *)malloc(sizeof(entry));
        strcpy(tmp->lastName,lastName);
        t->pL = tmp;
    }
    else{
        tmp = (entry *)malloc(sizeof(entry));
        strcpy(tmp->lastName,lastName);
        t->pR = tmp;
    }
    return e;
#endif

}
