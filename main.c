#include <stdio.h>

static char input[2048];

int main(int argc, char** argv) {
    puts("Lispy versi 0.0.1");
    puts("Tekan CTRL+C untuk keluar\n");

    while(1) {
        fputs("lispy> ", stdout);
        fgets(input, 2048, stdin);
        printf("Nama Anda adalah %s", input);
    }

    return 0;
}