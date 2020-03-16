#include "Tokenizer.h"

int globalNumLex;

// checks to see if the lexeme is one of:
// (, ), [, ], =, ;, or ,
// and returns the associated token label
int getStructureToken(char singleChar) {
    if (singleChar == '(') {
        return LEFT_PARENTHESIS;
    }
    else if (singleChar == ')') {
        return RIGHT_PARENTHESIS;
    }
    else if (singleChar == '{') {
        return LEFT_BRACKET;
    }
    else if (singleChar == '}') {
        return RIGHT_BRACKET;
    }
    else if (singleChar == '=') {
        return EQUAL;
    }
    else if (singleChar == ',') {
        return COMMA;
    }
    else if (singleChar == ';') {
        return EOL;
    }
    else {
        return FALSE;
    }
}

// checks to see if the passed lexeme is one of:
// +, *, %
_Bool isSingleBinopToken(char singleChar) {
    if (singleChar == '+') {
        return TRUE;
    }
    else if (singleChar == '*') {
        return TRUE;
    }
    else if (singleChar == '%') {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

// checks to see if the passed lexeme is one of:
// while, return, int, void
// and returns the associated token label
int getKeywordToken(char *lexeme) {
    if (strcmp(lexeme, (char *) "while") == 0) {
        return WHILE_KEYWORD;
    }
    else if (strcmp(lexeme, (char *) "return") == 0) {
        return RETURN_KEYWORD;
    }
    else if (strcmp(lexeme, (char *) "int") == 0) {
        return VARTYPE;
    }
    else if (strcmp(lexeme, (char *) "void") == 0) {
        return VARTYPE;
    }
    else {
        return FALSE;
    }
}

// given a lexeme, will find out what token category
// the lexeme belongs to
int getTokenLabel(char *lexeme) {
    int label;

    label = getKeywordToken(lexeme);
    if (label != FALSE) {
        return label;
    }

    if (strcmp(lexeme, "==") == 0) {
        return BINOP;
    }
    else if (strcmp(lexeme, "!=") == 0) {
        return BINOP;
    }

    if (validNumber(lexeme)) {
        return NUMBER;
    }

    if (validIdentifier(lexeme)) {
        return IDENTIFIER;
    }

    return FALSE;
}

// given a lexeme, will find out what token category
// the lexeme belongs to
int getSingleTokenLabel(char singleChar) {
    int label;

    if (isSingleBinopToken(singleChar)) {
        return BINOP;
    }

    label = getStructureToken(singleChar);
    if (label != FALSE) {
        return label;
    }
    return FALSE;
}

// will check the current character passed,
// returning true if the character denotes the end of the lexeme being built
_Bool isStopChar(char singleChar) {
    int structureLabel = getStructureToken(singleChar);

    if (structureLabel != FALSE) {
        return TRUE;
    }
    else if (isSingleBinopToken(singleChar) == TRUE) {
        return TRUE;
    }
    else if (singleChar == ' ') {
        return TRUE;
    }
    else if (singleChar == '!') {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

// this function should create a lexic struct and pass it to the returnLexic pointer
void createLexLexic(char *foundLex, struct lexics *lexPointer) {
    int tokenLabel = getTokenLabel(foundLex);

    lexPointer->token = tokenLabel;
    strcpy(lexPointer->lexeme, foundLex);

    printf("\nCreated lex lexics lexeme: %s\n", lexPointer->lexeme);
    printf("\nCreated lex lexics token: %d\n", lexPointer->token);
}

// this function should create a lexic struct and pass it to the returnLexic pointer
void createCharLexic(char singleChar, struct lexics *lexPointer) {
    char singleStupid[2] = "\0";
    singleStupid[0] = singleChar;

    //char *singleStupid = &singleChar;
    int tokenLabel = getSingleTokenLabel(singleChar);

    lexPointer->token = tokenLabel;
    strcpy(lexPointer->lexeme, singleStupid);

    printf("\nCreated char lexics lexeme: %s\n", lexPointer->lexeme);
    printf("\nCreated char lexics token: %d\n", lexPointer->token);
}

// the big one, the nasty one
// you can do it!
_Bool tokenizer(struct lexics *aLex, int *numLex, FILE *inf) {
    // declaring the variables used in this function
    // there are a lot
    // check to make sure all of these are used
    int i, tempIndex;
    size_t length, lexLength;
    _Bool endOfLexeme, charLex, doubleChar;
    char tempLex[MY_CHAR_MAX];
    char input[LEXEME_MAX];
    char lexeme[LEXEME_MAX];
    char doubleLex[LEXEME_MAX];

    globalNumLex = 0;

    // read the file info and store it in input
    while (fgets(input, MY_CHAR_MAX, inf) != NULL) {

        // get the length of the input file and initialize variables
        length = strlen(input);
        tempIndex = 0;

        //  read the input file until we have a completed lexeme
        for (i = 0; i < length; i++) {
            endOfLexeme = FALSE;
            charLex = FALSE;

            char currentChar = input[i];

            // handler if the input has a null terminator or newline
            // potentially refactor this to be included in isStopChar()
            if (currentChar == '\0' || currentChar == '\n' || currentChar == '\t') {
                lexLength = strlen(lexeme);
                if (lexLength > 0) {
                    endOfLexeme = TRUE;
                }
                strcpy(tempLex, "");
            }
                // if the currentChar is a character that denotes the end
                // of the currently built lexeme
            else if (isStopChar(currentChar) == TRUE) {
                if (currentChar != ' ' ) {
                    charLex = TRUE;
                }

                lexLength = strlen(lexeme);
                if (lexLength > 0) {
                    endOfLexeme = TRUE;
                    strcpy(tempLex, "");
                    tempIndex = 0;
                }

                // handler for when currentChar is '=' or '!'
                // will check to see if the token is EQUAL or BINOP
                if (currentChar == '=' || currentChar == '!') {
                    char nextChar = input[i + 1];
                    if (nextChar == '=') {
                        doubleLex[0] = currentChar;
                        doubleLex[1] = nextChar;
                        doubleLex[2] = '\0';

                        doubleChar = TRUE;
                        charLex = FALSE;
                        i++;
                    }
                }
            }
                // otherwise, just add the currentChar to the lexeme string
            else {
                tempLex[tempIndex] = currentChar;
                tempLex[tempIndex + 1] = '\0';

                strcpy(lexeme, tempLex);
                tempIndex++;
            }

            // tokenize the lexeme
            if (endOfLexeme) {
                createLexLexic(lexeme, &aLex[globalNumLex]);
                globalNumLex++;
                endOfLexeme = FALSE;
                strcpy(lexeme, "");
            }
            // tokenize the doubleBinop
            if (doubleChar) {
                createLexLexic(doubleLex, &aLex[globalNumLex]);
                globalNumLex++;
                doubleChar = FALSE;
                strcpy(doubleLex, "");
            }
            // tokenize the singular character
            if (charLex) {
                // if we get a lexeme that goes wrong or isn't correct
                createCharLexic(currentChar, &aLex[globalNumLex]);
                globalNumLex++;
                charLex = FALSE;
            }

        }
    }
    printf("\nThe value of globalNumLex is: %d\n", globalNumLex);
    *numLex = globalNumLex;
    return TRUE;
}