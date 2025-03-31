#include <stdio.h>
#include <stdlib.h>
#include <editline/readline.h>

int main(int argc, char** argv) {
    puts("Lispy versi 0.0.1");
    puts("Tekan CTRL+C untuk keluar\n");

    while(1) {
        char* input = readline("Lispy> ");
        add_history(input);
        printf("Nama Anda adalah %s", input);
        free(input);
    }

    return 0;
}