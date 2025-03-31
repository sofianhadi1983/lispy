#include <stdio.h>
#include <stdlib.h>
#include "mpc.h"

/* jika menggunakan macOS */
#ifdef __APPLE__
#include <editline/readline.h>
/* editline/history.h  tidak dibutuhkan di macOS karena sudah digabung di readline.h */
#else
#include <editline/readline.h>
#include <editline/history.h>
#endif

int main(int argc, char** argv) {
    mpc_parser_t* Number    = mpc_new("number");
    mpc_parser_t* Operator  = mpc_new("operator");
    mpc_parser_t* Expr      = mpc_new("expr");
    mpc_parser_t* Lispy     = mpc_new("lispy");

    mpca_lang(MPCA_LANG_DEFAULT,
        "                                                                                              \
           number   : /-?[0-9]+/ ;                                                                     \
           operator : '+' | '-' | '*' | '/' | '%' | /tambah/ | /kurang/ | /kali/ | /bagi/ | /modulo/;  \
           expr     : <number> | '(' <operator> <expr>+ ')' ;                                          \
           lispy    :  /^/ <operator> <expr>+ /$/ ;                                                    \
        ", 
        Number, Operator, Expr, Lispy);
        
    puts("Lispy versi 0.0.1");
    puts("Tekan CTRL+C untuk keluar\n");
    
    while(1) {
        char* input = readline(">>> ");
        add_history(input);
        
        mpc_result_t r;
        if (mpc_parse("<stdin>", input, Lispy, &r)) {
            mpc_ast_print(r.output);
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