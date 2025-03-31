# lispy
Belajar bahasa C dengan membuat interpreter Lisp.

## Catatan khusus
`main.c` memerlukan dua librari berikut untuk edit perintah dan menyimpan histori perintah.

```
#include <editline/readline.h>
#include <editline/history.h>
```

khusus di sistem operasi `Mac OS`, hanya perlu memasukan satu librari saja karena dua fungsi yang dibutuhkan sudah digabung jadi satu di `readline.h`

```
#include <editline/readline.h>
```
## Cara kompilasi
```
cc -std=c99 -Wall main.c -o main
```
