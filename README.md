# CSCE 4430 - Term Project 1
## By Brooke Mesch, Sara Nurdil, and Jude Qubbaj

## Project Description
This project is a lexical analyzer implemented using Flex. It tokenizes simple arithmetic expressions consisting of integers, operators, and parentheses. Before running the lexer, ensure your input.txt file(s) already exist. The output is printed to the console, redirect as needed. 

## Compilation Instructions
### 1. Compile the Lexer
**Linux/macOS:**
flex lexer.l gcc les.yy.c -o lexer

**Windows:**
flex lexer.l gcc lex.yy.c -o lexer.exe

### 2. Compile the Parser
**Linux/macOS:**
gcc parser.c -o parser

**Windows:**
gcc parser.c -o parser.exe

## Execution Instructions
### 3. Run the Lexer
Run the lexer to tokenize the input file:
**Linux/macOS:**
./lexer input.txt > tokens.txt 
**Windows:**
 lexer.exe input.txt > tokens.txt 

### 4. Run the Parser
Parse the tokenized output to construct the Abstract Syntax Tree:
**Linux/macOS:**
./parser < tokens.txt

**Windows:**
parser.exe < tokens.txt

## To compile and run the project together with the parser enter the following commands in this order (Linux):
```

flex lexer.l
gcc lex.yy.c -o lexer
gcc parser.c -o parser
./lexer input.txt | ./parser
```
