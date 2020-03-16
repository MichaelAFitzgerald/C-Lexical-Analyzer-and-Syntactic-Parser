#include "Parser.h"

// global variable declarations
int lexIndex;

// function declarations

// helper function to determine if the statement function should be called
_Bool isStatement(struct lexics *someLexics) {
    if (someLexics[lexIndex].token == WHILE_KEYWORD) {
        return TRUE;
    }
    else if (someLexics[lexIndex].token == RETURN_KEYWORD) {
        return TRUE;
    }
    else if (someLexics[lexIndex].token == IDENTIFIER) {
        return TRUE;
    }
    else if (someLexics[lexIndex].token == LEFT_BRACKET) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

// helper function to determine which of the functions should be called through statement
int whichStatement(struct lexics *someLexics) {
    if (someLexics[lexIndex].token == WHILE_KEYWORD) {
        return WHILE_KEYWORD;
    }
    else if (someLexics[lexIndex].token == RETURN_KEYWORD) {
        return RETURN_KEYWORD;
    }
    else if (someLexics[lexIndex].token == IDENTIFIER) {
        return IDENTIFIER;
    }
    else if (someLexics[lexIndex].token == LEFT_BRACKET) {
        return LEFT_BRACKET;
    }
    else {
        return FALSE;
    }
}

_Bool function(struct lexics *someLexics) {
    if (header(someLexics)) {
        if (body(someLexics)) {
            return TRUE;
        }
        else {
            return FALSE;
        }
    }
    else {
        return FALSE;
    }
}

_Bool header(struct lexics *someLexics) {

    // consume VARTYPE token
    if (someLexics[lexIndex].token == VARTYPE) {
        lexIndex++;
    }
    else {
        return FALSE;
    }

    // consume IDENTIFIER token
    if (someLexics[lexIndex].token == IDENTIFIER) {
        lexIndex++;
    }
    else {
        return FALSE;
    }

    // consume LEFT_PARENTHESIS token
    if (someLexics[lexIndex].token == LEFT_PARENTHESIS) {
        lexIndex++;
    }
    else {
        return FALSE;
    }

    // while loop to get all arg-decl
    while (someLexics[lexIndex].token == VARTYPE) {
        if (argDecl(someLexics)) {

        }
        else {
            return FALSE;
        }
    }

    // consume RIGHT_PARENTHESIS
    if (someLexics[lexIndex].token == RIGHT_PARENTHESIS) {
        lexIndex++;
    }
    else {
        return FALSE;
    }

    return TRUE;
}

_Bool argDecl(struct lexics *someLexics) {
    // consume VARTYPE token
    if (someLexics[lexIndex].token == VARTYPE) {
        lexIndex++;
    }
    else {
        return FALSE;
    }

    // consume IDENTIFIER token
    if (someLexics[lexIndex].token == IDENTIFIER) {
        lexIndex++;
    }
    else {
        return FALSE;
    }

    // while loop to continue the argDecl
    while (someLexics[lexIndex].token == COMMA) {
        // consume COMMA token
        if (someLexics[lexIndex].token == COMMA) {
            lexIndex++;
        }
        else {
            return FALSE;
        }

        // consume VARTYPE token
        if (someLexics[lexIndex].token == VARTYPE) {
            lexIndex++;
        }
        else {
            return FALSE;
        }

        // consume IDENTIFIER token
        if (someLexics[lexIndex].token == IDENTIFIER) {
            lexIndex++;
        }
        else {
            return FALSE;
        }
    }

    return TRUE;
}

_Bool body(struct lexics *someLexics) {

    // consume LEFT_BRACKET token
    if (someLexics[lexIndex].token == LEFT_BRACKET) {
        lexIndex++;
    }
    else {
        return FALSE;
    }

    // while loop for statementList
    // create helper function to figure out if loop needs to continue
    while (isStatement(someLexics)) {
        if (statementList(someLexics) == FALSE) {
            // do something here?
            return FALSE;
        }
    }

    // consume RIGHT_BRACKET token
    if (someLexics[lexIndex].token == RIGHT_BRACKET) {
        lexIndex++;
    }
    else {
        return FALSE;
    }

    return TRUE;
}

_Bool statementList(struct lexics *someLexics) {
    // first statement call
    if (statement(someLexics) == FALSE) {
        // do something here?
        return FALSE;
    }

    // while loop for subsequent statement calls
    // create helper function to handle the boolean?
    while (isStatement(someLexics)) {
        if (statement(someLexics) == FALSE) {
            // do something here?
            return FALSE;
        }
    }

    return TRUE;
}

_Bool statement(struct lexics *someLexics) {
    // get the value of lexIndex at the beginning of the function
    // in case one of the subsequent calls changes the value and I need to return
    int holdIndex = lexIndex;

    // perhaps creating a helper function to determine which function to call
    // instead of just calling them all in order?

    int chooseStatement = whichStatement(someLexics);

    if (chooseStatement == FALSE) {
        return FALSE;
    }
    else if (chooseStatement == WHILE_KEYWORD) {
        if (whileLoop(someLexics)) {
            return TRUE;
        }
        else {
            return FALSE;
        }
    }
    else if (chooseStatement == RETURN_KEYWORD) {
        if (returnFunction(someLexics)) {
            return TRUE;
        }
        else {
            return FALSE;
        }
    }
    else if (chooseStatement == IDENTIFIER) {
        if (assignment(someLexics)) {
            return TRUE;
        }
        else {
            return FALSE;
        }
    }
    else if (chooseStatement == LEFT_BRACKET) {
        if (body(someLexics)) {
            return TRUE;
        }
        else {
            return FALSE;
        }
    }
}

_Bool whileLoop(struct lexics *someLexics) {
    // consume WHILE token
    if (someLexics[lexIndex].token == WHILE_KEYWORD) {
        lexIndex++;
    }
    else {
        return FALSE;
    }

    // consume LEFT_PARENTHESIS token
    if (someLexics[lexIndex].token == LEFT_PARENTHESIS) {
        lexIndex++;
    }
    else {
        return FALSE;
    }

    // call expression function
    if (expression(someLexics) == FALSE) {
        // do something here?
        return FALSE;
    }

    // consume RIGHT_PARENTHESIS token
    if (someLexics[lexIndex].token == RIGHT_PARENTHESIS) {
        lexIndex++;
    }
    else {
        return FALSE;
    }

    // call statement function
    if (statement(someLexics) == FALSE) {
        // do something here?
        return FALSE;
    }

    return TRUE;
}

_Bool returnFunction(struct lexics *someLexics) {
    // consume RETURN token
    if (someLexics[lexIndex].token == RETURN_KEYWORD) {
        lexIndex++;
    }
    else {
        return FALSE;
    }

    // call expression function
    if (expression(someLexics) == FALSE) {
        // do something here
        return FALSE;
    }

    // consume EOL token
    if (someLexics[lexIndex].token == EOL) {
        lexIndex++;
    }
    else {
        return FALSE;
    }

    return TRUE;
}

_Bool assignment(struct lexics *someLexics) {
    // consume IDENTIFIER token
    if (someLexics[lexIndex].token == IDENTIFIER) {
        lexIndex++;
    }
    else {
        return FALSE;
    }

    // consume EQUAL token
    if (someLexics[lexIndex].token == EQUAL) {
        lexIndex++;
    }
    else {
        return FALSE;
    }

    // call expression function
    if (expression(someLexics) == FALSE) {
        return FALSE;
    }

    // consume EOL token
    if (someLexics[lexIndex].token == EOL) {
        lexIndex++;
    }
    else {
        return FALSE;
    }

    return TRUE;
}

_Bool expression(struct lexics *someLexics) {
    // call term function
    if (term(someLexics)) {
        // while loop for additional BINOP term
        while (someLexics[lexIndex].token == BINOP) {
            // consume BINOP token
            lexIndex++;

            // call term function
            if (term(someLexics) == FALSE) {
                return FALSE;
            }
        }
    }
    else {
        // consume LEFT_PARENTHESIS token
        if (someLexics[lexIndex].token == LEFT_PARENTHESIS) {
            lexIndex++;
        }
        else {
            return FALSE;
        }

        // call expression function
        if (expression(someLexics) == FALSE) {
            return FALSE;
        }

        // consume RIGHT_PARENTHESIS token
        if (someLexics[lexIndex].token == RIGHT_PARENTHESIS) {
            lexIndex++;
        }
        else {
            return FALSE;
        }
    }

    return TRUE;
}

_Bool term(struct lexics *someLexics) {
    // consume IDENTIFIER token
    if (someLexics[lexIndex].token == IDENTIFIER) {
        lexIndex++;
        return TRUE;
    }
    // consume NUMBER token
    else if (someLexics[lexIndex].token == NUMBER) {
        lexIndex++;
        return TRUE;
    }
    else {
        return FALSE;
    }
}

// parser declaration, everything else is called from here
_Bool parser(struct lexics *someLexics, int numberOfLexics) {
    lexIndex = 0;

    if (function(someLexics)) {
        if (lexIndex == numberOfLexics) {
            return TRUE;
        }
        else {
            return FALSE;
        }
    }
    else {
        return FALSE;
    }
}