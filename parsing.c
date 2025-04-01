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
mpc_err_t* readGrammar(mpc_parser_t* Number, mpc_parser_t* Operator, mpc_parser_t* Expr, mpc_parser_t* Lispy);

int main(int argc, char** argv) {
    mpc_parser_t* Number    = mpc_new("number");
    mpc_parser_t* Operator  = mpc_new("operator");
    mpc_parser_t* Expr      = mpc_new("expr");
    mpc_parser_t* Lispy     = mpc_new("lispy");

    mpc_err_t* err = readGrammar(Number, Operator, Expr, Lispy);
    
    if (err != NULL) {
        mpc_err_print(err);
        mpc_err_delete(err);
        mpc_cleanup(4, Number, Operator, Expr, Lispy);
        return 1;
    }
        
    puts("Lispy versi 0.0.1");
    puts("Tekan CTRL+C untuk keluar\n");
    
    while(1) {
        char* input = readline(">>> ");
        add_history(input);
        
        mpc_result_t r;
        if (mpc_parse("<stdin>", input, Lispy, &r)) {
            // mpc_ast_print(r.output);
            long result = eval(r.output);
            printf("%li\n", result);
            mpc_ast_delete(r.output);
        } else {
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        }

        free(input);
    }

    mpc_cleanup(4, Number, Operator, Expr, Lispy);
    return 0;
}

int  number_of_nodes(mpc_ast_t* t) {
    if (t->children_num == 0) return 1;
    if (t->children_num >= 1) {
        int total = 1;
        for (int i = 0; i < t->children_num; i++) {
            total += number_of_nodes(t->children[i]);
        }
        return total;
    }
    return 0;
}

long eval_op(long x, char* op, long y) {
    if (strcmp(op, "+") == 0 || strcmp(op, "tambah") == 0) return x + y;
    if (strcmp(op, "-") == 0 || strcmp(op, "kurang") == 0) return x - y;
    if (strcmp(op, "/") == 0 || strcmp(op, "bagi") == 0) return x / y;
    if (strcmp(op, "*") == 0 || strcmp(op, "kali") == 0) return x * y;
    if (strcmp(op, "%") == 0 || strcmp(op, "modulo") == 0) return x % y;
    return 0;
}

mpc_err_t* readGrammar(
    mpc_parser_t* Number, 
    mpc_parser_t* Operator, 
    mpc_parser_t* Expr,
    mpc_parser_t* Lispy) {
        
    return mpca_lang_contents(
        MPCA_LANG_DEFAULT, 
        "lispy.grammar", 
        Number, Operator, Expr, Lispy);
}

long eval(mpc_ast_t* t) {
    if (strstr(t->tag, "number")) {
        return atoi(t->contents);
    }

    char* op = t->children[1]->contents;
    long x = eval(t->children[2]);
    int i = 3;
    while (strstr(t->children[i]->tag, "expr")) {
        x = eval_op(x, op, eval(t->children[i]));
        i++;
    }

    return x;
}
