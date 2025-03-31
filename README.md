# lispy
Belajar bahasa C dengan membuat interpreter Lisp.

## Catatan khusus
`main.c` memerlukan dua pustaka berikut untuk edit perintah dan menyimpan histori perintah.

```
#include <editline/readline.h>
#include <editline/history.h>
```

khusus di sistem operasi `Mac OS`, hanya perlu memasukan satu pustaka saja karena dua fungsi yang dibutuhkan sudah digabung jadi satu di `readline.h`

```
#include <editline/readline.h>
```
## Cara kompilasi
```
cc -std=c99 -Wall main.c -o main.out -ledit
```
flag `-ledit` menginstruksikan kompiler untuk memakai pustaka `libedit` yang mengandung dua perintah yang dibutuhkan oleh `main.c` yaitu `readline` dan `add_history`.

di sistem operasi `Linux` bisa diinstall menggunakan perintah berikut:
```
sudo apt-get install libedit-dev
```
