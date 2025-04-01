#ifndef parsing_h
#define parsing_h

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpc.h"

/* jika menggunakan macOS */
#ifdef __APPLE__
#include <editline/readline.h>
/* editline/history.h  tidak dibutuhkan di macOS karena sudah digabung di readline.h */
#else
#include <editline/readline.h>
#include <editline/history.h>
#endif

int  number_of_nodes(mpc_ast_t* t);

long eval_op(long x, char* op, long y);

long eval(mpc_ast_t* t);

mpc_err_t* readGrammar(
    mpc_parser_t* Number,
    mpc_parser_t* Operator, 
    mpc_parser_t* Expr, 
    mpc_parser_t* Lispy);

#ifdef __cplusplus
}
#endif

#endif