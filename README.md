# Symbol-Table-Implementation
A compiler records the variable names used in the source program along with its attributes and stores it in a data structure called a symbol table.
# Symbol Table Implementation

## Overview
This project implements a **symbol table** using **hashing and linked lists** to store variables in different scopes. The implementation supports nested scopes and allows inserting, looking up, and printing variables. The program reads commands from an input file (`input.txt`) and executes them accordingly.

## Features
- **Supports Nested Scopes**: Each `begin` creates a new scope, and `end` removes it.
- **Variable Assignments**: Variables can be assigned values using `assign`.
- **Variable Lookup**: `print` retrieves the variable's value, checking outer scopes if needed.
- **Proper Indentation**: Displays scope levels for structured output.

## File Structure
```
├── symbol.h            # Header file with function declarations
├── function.c          # Contains symbol table functions (insert, lookup, etc.)
├── texttofunction.c    # Reads input file and processes commands
├── main.c              # Main entry point of the program
├── input.txt           # Input file with commands
├── Makefile            # Makefile for compilation
├── README.md           # Documentation (this file)
```

### **1. Provide Input**
The program reads commands from `input.txt`. Example input:
```
begin
    assign a 1
    assign b 2
    begin
        assign a 3
        assign c 4
        print b
        begin
            assign c 5
            print b
            print a
            print c
        end
        print a
        print c
    end
    print a
```

### **2. Expected Output**
```
[Scope 1] New scope started.
    [Scope 1] Assigned a = 1
    [Scope 1] Assigned b = 2
    [Scope 2] New scope started.
        [Scope 2] Assigned a = 3
        [Scope 2] Assigned c = 4
        [Scope 2] b = 2
        [Scope 3] New scope started.
            [Scope 3] Assigned c = 5
            [Scope 3] b = 2
            [Scope 3] a = 3
            [Scope 3] c = 5
        [Scope 3] Scope ended.
        [Scope 2] a = 3
        [Scope 2] c = 4
    [Scope 2] Scope ended.
    [Scope 1] a = 1
```
