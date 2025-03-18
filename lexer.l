%{
#include <stdio.h>
#include <stdlib.h>
%}

/* Define token patterns */
DIGIT       [0-9]
INTEGER     {DIGIT}+
WHITESPACE  [ \t\n]+

%%


{INTEGER}   { printf("%s,integer\n", yytext); }
"+"     { printf("%s,add_operator\n", yytext); }
"-"     { printf("%s,subtract_operator\n", yytext); }
"*"     { printf("%s,multiply_operator\n", yytext); }
"/"     { printf("%s,divide_operator\n", yytext); }

"("         { printf("%s,left_paren\n", yytext); }
")"         { printf("%s,right_paren\n", yytext); }
{WHITESPACE}    ; /* Ignore whitespace */

.       { printf("Error: Unrecognized token %s\n", yytext);}

%%

int main(int argc, char **argv) {
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            perror("Could not open file");
            return 1;
        }
        yyin = file;
    }
    yylex();
    return 0;
}

int yywrap() { return 1; }
