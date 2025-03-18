#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern int yylex();
extern char* yytext;
int current_token;

// struct for a tree node
typedef struct TreeNode {
    char* value;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

TreeNode* createNode(char* value) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->value = strdup(value);
    node->left = NULL;
    node->right = NULL;
    return node;
}

//GRAMMAR FUNCTIONS:

TreeNode* expression(){
    
}
TreeNode* expression_suffix(){

}
TreeNode* term(){

}
TreeNode* term_suffix(){

}
TreeNode* factor(){

}
TreeNode* integer(){

}
TreeNode* integer_suffix(){

}
TreeNode* digit(){

}