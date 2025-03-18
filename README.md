# CSCE 4430
# Term Project 1
# Brooke Mesch
# Sara Nurdil
To compile and run the project together with the parser enter the following commands in this order (Linux):
```
flex lexer.l
gcc lex.yy.c -o lexer
gcc parser.c -o parser
./lexer input.txt | ./parser
```

# Jude Qubbaj


This project is a lexical analyzer implemented using Flex. It tokenizes simple arithmetic expressions consisting of integers, operators, and parentheses. Before running the lexer, ensure your input.txt file(s) already exist. The output is printed to the console, redirect as needed. 

To Run:

Windows: 
Open cmd
Run the following commands: 
flex lexer.l
gcc.lex.yy.c -o lexer.exe
lexer.exe input.txt

Linux/Mac
Open the terminal
Run the following commands:
flex lexer.l
gcc.lex.yy.c -o lexer
./lexer input.txt


