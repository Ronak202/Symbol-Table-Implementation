#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol.h"

#define MAX_LINE 100

int scope_level = 0;  // To track nesting levels
void process_file(FILE *file, symbol_table **current_scope) {
    char line[MAX_LINE];

    printf("Processing file...\n");

    while (fgets(line, sizeof(line), file)) {
        process_line(line, current_scope);
    }

    printf("Processing complete.\n");
}

void process_line(char *line, symbol_table **current_scope) {
    char command[10], var[25];
    int value;
    
    if (sscanf(line, "%s %s %d", command, var, &value) == 3 && strcmp(command, "assign") == 0) {
        insert(*current_scope, var, value);
        printf("%*s[Scope %d] Assigned %s = %d\n", scope_level * 4, "", scope_level, var, value);
    } 
    else if (strcmp(line, "begin\n") == 0) {
        *current_scope = createscope(*current_scope);
        scope_level++;
        printf("%*s[Scope %d] New scope started.\n", scope_level * 4, "", scope_level);
    } 
    else if (strcmp(line, "end\n") == 0) {
        symbol_table *old_scope = *current_scope;
        *current_scope = (*current_scope)->root;
        freescope(old_scope);
        printf("%*s[Scope %d] Scope ended.\n", scope_level * 4, "", scope_level);
        scope_level--;
    } 
    else if (sscanf(line, "print %s", var) == 1) {
        int result = lookup(*current_scope, var);
        if (result != -1) {
            printf("%*s[Scope %d] %s = %d\n", scope_level * 4, "", scope_level, var, result);
        } else {
            printf("%*s[Scope %d] %s is undefined.\n", scope_level * 4, "", scope_level, var);
        }
    }
}
