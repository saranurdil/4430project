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

ASTNode* expression();
ASTNode* expression_suffix(ASTNode* left);
ASTNode* term();
ASTNode* term_suffix(ASTNode* left);
ASTNode* factor();

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
    ASTNode* term_node = term();
    return expression_suffix(term_node);
}

// GRAMMAR: <term> -> <factor> <term_suffix>
ASTNode* term(){
    ASTNode* factor_node = factor();
    return term_suffix(factor_node);
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
        int value = atoi(current_token);
        ASTNode* node = create_node(NODE_INTEGER, value, NULL, NULL);
        get_next_token();
        return node;
    }
    //check if current token is and integer
}

// GRAMMAR: <term_suffix> -> * <factor> <term_suffix> | / <factor> <term_suffix> | ε
ASTNode* term_suffix(ASTNode* left){
    //check if current token is * or /
    if(strcmp(current_token_type, "multiple_operator") == 0){
        get_next_token();
        ASTNode* factor_node = factor();
        ASTNode* new_node = create_node(NODE_MULTIPLY, 0, left, factor_node);
        return term_suffix(new_node);
    }
    else if (strcmp(current_token_type, "divide_operator") == 0){
        get_next_token();
        ASTNode* factor_node = factor();
        ASTNode* new_node = create_node(NODE_DIVIDE, 0, left, factor_node);
        return term_suffix(new_node);
    }
    return left;
}

// GRAMMAR: <expression_suffix> -> + <term> <expression_suffix> | - <term> <expression_suffix> | ε
ASTNode* expression_suffix(ASTNode* left){
    //check if current token is + or -
    if(strcmp(current_token_type, "add_operator") == 0){
        get_next_token();
        ASTNode* factor_node = term();
        ASTNode* new_node = create_node(NODE_ADD, 0, left, factor_node);
        return expression_suffix(new_node);
    }
    else if (strcmp(current_token_type, "subtract_operator") == 0){
        get_next_token();
        ASTNode* factor_node = term();
        ASTNode* new_node = create_node(NODE_SUBTRACT, 0, left, factor_node);
        return expression_suffix(new_node);
    }
}

void print_tree(ASTNode* node){

    //if the tree is empty
    if (node == NULL){
        printf("Empty tree.\n");
        return;
    }

    int indent_counter = 1;
    for(int i = 0; i < indent_counter; i++){

        switch(node->type){
            case NODE_INTEGER:
                printf("%d (int)\n", node->value);
                break;
            case NODE_ADD:
                break;
            case NODE_DIVIDE:
                break;
            case NODE_MULTIPLY:
                break;
            case NODE_SUBTRACT:
                break;
        }
    }

}
int main(){
    get_next_token();
    ASTNode* root = expression();
    print_tree(root);

    return 0;

}
