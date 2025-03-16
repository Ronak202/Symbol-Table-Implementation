#include <stdio.h>
#include <stdlib.h>
#include "symbol.h"

int main() {
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        printf("Error opening file!\n");
        return 1;
    }

    symbol_table *current_scope = createscope(NULL);
    
    process_file(file, &current_scope);  // Pass file pointer instead of "input.txt"

    fclose(file);
    freescope(current_scope);
    
    return 0;
}
