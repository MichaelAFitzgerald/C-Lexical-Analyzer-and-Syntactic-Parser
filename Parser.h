#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include "Givens.h"

// function prototype declarations

_Bool isStatement(struct lexics *someLexics);

int whichStatement(struct lexics *someLexics);

_Bool function(struct lexics *someLexics);

_Bool header(struct lexics *someLexics);

_Bool argDecl(struct lexics *someLexics);

_Bool body(struct lexics *someLexics);

_Bool statementList(struct lexics *someLexics);

_Bool statement(struct lexics *someLexics);

_Bool whileLoop(struct lexics *someLexics);

_Bool returnFunction(struct lexics *someLexics);

_Bool assignment(struct lexics *someLexics);

_Bool expression(struct lexics *someLexics);

_Bool term(struct lexics *someLexics);

_Bool parser(struct lexics *someLexics, int numberOfLexics);

#endif