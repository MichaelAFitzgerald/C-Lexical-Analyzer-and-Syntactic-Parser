#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdio.h>
#include <string.h>
#include "Givens.h"

// function prototype declarations

int getStructureToken(char singleChar);

_Bool isSingleBinopToken(char singleChar);

int getKeywordToken(char *lexeme);

int getTokenLabel(char *lexeme);

_Bool isStopChar(char singleChar);

void createLexLexic(char *foundLex, struct lexics *lexPointer);

void createCharLexic(char singleChar, struct lexics *lexPointer);

_Bool tokenizer(struct lexics *aLex, int *numLex, FILE *inf);

#endif