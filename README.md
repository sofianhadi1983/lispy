# lispy
Belajar bahasa C dengan membuat interpreter Lisp.

## Pustaka yang dibutuhkan
`main.c` memerlukan dua pustaka berikut untuk edit perintah dan menyimpan histori perintah.

```
#include <editline/readline.h>
#include <editline/history.h>
```

khusus di sistem operasi `Mac OS`, hanya perlu memasukan satu pustaka saja karena dua fungsi yang dibutuhkan sudah digabung jadi satu di `readline.h`

```
#include <editline/readline.h>
```

selain itu, program ini membutuhkan pustaka grammar.
```
curl -O https://raw.githubusercontent.com/orangeduck/mpc/refs/heads/master/mpc.h
curl -O https://raw.githubusercontent.com/orangeduck/mpc/refs/heads/master/mpc.c
```

deklarasikan `mpc` dengan statement `#include "mpc.h"`.

## Cara kompilasi dan run
```
cc -std=c99 -Wall main.c -o main.out -ledit
```
flag `-ledit` menginstruksikan kompiler untuk memakai pustaka `libedit` yang mengandung dua perintah yang dibutuhkan oleh `parsing.c` yaitu `readline` dan `add_history`.

di sistem operasi `Linux` bisa diinstall menggunakan perintah berikut:
```
sudo apt-get install libedit-dev
```

jika menyertakan pustaka `mpc`, maka perintahnya menjadi berikut:
`Linux dan Mac`
```
cc -std=c99 -Wall parsing.c mpc.c -ledit -lm -o parsing.out
```

`Windows`
```
cc -std=c99 -Wall parsing.c mpc.c -o parsing
```

atau cukup menggunakan perintah
```
make # untuk build project
./parsing.out # untuk run lispy
make clean # untuk menghapus executable hasil kompilasi
```

tampilan akan seperti ini:
```
user@Users-MacBook-Pro lispy % ./parsing.out 
Lispy versi 0.0.1
Tekan CTRL+C untuk keluar

>>> + 1 2 6
9
>>> + 6 (* 2 9)
24
>>> / (* 10 2) (+ 4 2)
3
>>> modulo 10 3
1
>>> 
```

## Cara mendefinisikan grammar
Tulis grammar di file `lispy.grammar`. 