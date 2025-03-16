#include "symbol.h"

//hash function
unsigned int hash(char *word)
{
    unsigned hash=0;
    int i=0;
    while(word[i]!='\0')
    {
        hash=(hash*31)+word[i];
        i++;
    }
    return hash%table_size;
}
// creating a symbol table for new scope 
//when begin appear
symbol_table *createscope(symbol_table *parent)
{
    symbol_table* retval=NULL;
    symbol_table *newscope=(symbol_table *)malloc(sizeof(symbol_table));
    if(!newscope) 
    {
        printf("Memory Allocation failed!!!\n");
        retval=NULL;
    }
    else
    {
        for(int i=0;i<table_size;i++)
        {
            newscope->table[i]=NULL;
        }
        newscope->root=parent;
        retval=newscope;
    }
    return retval;
}
// inserting element in symbol table
void insert(symbol_table* scope,char* word,int value)
{
    unsigned int index=hash(word);
    ele* newele=(ele*)malloc(sizeof(ele));
    if(!newele)
    {
        printf("Memory Allocation failed!!!\n");
    }
    else
     {
        strcpy(newele->name,word);
        newele->value=value;
        newele->next=scope->table[index];//handle collision
        scope->table[index]=newele;
     }
}
// lookup variable in current scope if not found look in outer scope
int lookup(symbol_table *scope,char *target)
{
    symbol_table* current=scope;
    int retval=-1;
    unsigned int index=hash(target);
    int flag=1;
    while(current&&flag==1) // not null
    {
         ele* temp=current->table[index]; //first element in current scope
         while(temp&&flag==1) // not null
         {
             if(strcmp(temp->name,target)==0)// target found
             {
                 retval=temp->value;
                 flag=0;

             }
             temp=temp->next;
         }
         current=current->root; // goto outer scope
    }
    if(flag==1)
    {
        printf("Variable '%s' not found\n", target);
        retval=-1;
    }
    return retval;
}
// free current scope when end appear
void freescope(symbol_table* scope)
{
    for(int i=0;i<table_size;i++)
    {
        ele* temp=scope->table[i];
        while(temp)
        {
            ele* delete=temp;
            temp=temp->next;
            free(delete);
        }
    }
    free(scope);
}