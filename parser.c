#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//node type options
typedef enum {
    NODE_INTEGER, 
    NODE_ADD,
    NODE_SUBTRACT,
    NODE_MULTIPLY,
    NODE_DIVIDE
} NodeType;

//Node struct
typedef struct ASTNode {
    NodeType type;
    int value; //equals to zero for non-integer type nodes
    struct ASTNode* left;
    struct ASTNode* right;
} ASTNode;

char current_token[100];
char current_token_type[100];

//function that creates new nodes for a tree
ASTNode* create_node(NodeType type, int value, ASTNode* left, ASTNode* right){

    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode)); //allocate memory for the node
    node->type = type; //set node type (i.e integer, add, subtract, etc)
    node->value = value; //set node value (i.e 15, +, /, -, etc)
    node->left = left; //set node's left child
    node->right = right; //set node's right child

    return node;
}

// Function to get the next token from the lexer output
void get_next_token() {
    if(scanf("%90[^,],%90s", current_token, current_token_type) != 2){ //scan for the token (e.g 2) and its type (e.g. integer)
        // if scanf did not succeed, clear the current token and its type
        strcpy(current_token, "");
        strcpy(current_token_type, "");
    }
}

// GRAMMAR: <expression> -> <term> <expression_suffix>
ASTNode* expression(){
    //cal term()
    //call expression_suffix()
}

// GRAMMAR: <term> -> <factor> <term_suffix>
ASTNode* term(){
    //call factor()
    //call term_suffix()
}

// GRAMMAR: <factor> -> ( <expression> ) | <integer>
ASTNode* factor(){
    //check if current token is "(" -> call expression()
    if(strcmp(current_token_type, "left_paren") == 0){
        get_next_token(); //move to the next token (which is the beginning of our expression)
        ASTNode* inner_expr = expression(); //call expression

        get_next_token(); 
        return inner_expr;
    }
    else if (strcmp(current_token_type, "integer") == 0){
        int value = current_token;
        ASTNode* node = create_node(NODE_INTEGER, value, NULL, NULL);
        get_next_token();
        return node;
    }
    //check if current token is and integer
}

// GRAMMAR: <term_suffix> -> * <factor> <term_suffix> | / <factor> <term_suffix> | ε
ASTNode* term_suffix(){
    //check if current token is *
    //check if current token is /
}

// GRAMMAR: <expression_suffix> -> + <term> <expression_suffix> | - <term> <expression_suffix> | ε
ASTNode* expression_suffix(){
    //check if current token is +
    //check if current token is -
}

int main(){
    get_next_token();

}
