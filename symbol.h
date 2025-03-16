#ifndef symbol_h
#define symbol_h
#define table_size 100
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct element {
    char name[25];
    int value;
    struct element* next;
} ele;

typedef struct symbol_table {
    ele *table[table_size];
    struct symbol_table *root;//previous scope
} symbol_table;

// Function declarations
unsigned int hash(char *word);
symbol_table *createscope(symbol_table *parent);
void insert(symbol_table* scope, char* word, int value);
int lookup(symbol_table *scope, char *target);
void freescope(symbol_table* scope);
void process_file(FILE *file, symbol_table **current_scope);
void process_line(char *line, symbol_table **current_scope);
#endif
