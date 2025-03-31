#include <stdio.h>
#include <stdlib.h>

/* jika menggunakan macOS */
#ifdef __APPLE__
#include <editline/readline.h>
/* editline/history.h  tidak dibutuhkan di macOS karena sudah digabung di readline.h */
#else
#include <editline/readline.h>
#include <editline/history.h>
#endif

int main(int argc, char** argv) {
    puts("Lispy versi 0.0.1");
    puts("Tekan CTRL+C untuk keluar\n");

    while(1) {
        char* input = readline(">>> ");
        add_history(input);
        printf("Anda memasukan perintah %s\n", input);
        free(input);
    }

    return 0;
}