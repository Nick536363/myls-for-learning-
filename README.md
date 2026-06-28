# Own LS written in C

## About

This project represents own written LS command for UNIX systems in the POSIX standard for educational purposes. 
It has no practical application because this project is educational only.


## Installation

To install and compile this project you'll need **Git**, **GCC** and **make**.

1. Download the repository
```bash
git clone https://github.com/Nick536363/myls-for-learning-
```
2. Change working directory
```bash
cd myls-for-learning-
```
3. Compile project using **make** or use **GCC** insted.
```bash
make
```


## Usage

Basically this program works just like LS, but has few flags and some restrictions.

You can list files in your current working directory just by running programm

```bash
$ ./myls 
myls.h
TODO.txt
mylib.c
testdir
Makefile
README.md
myls
myls.c
$ 
```

You could also choose the file or directory to be printed. Just type it in argument


```bash
$ ./myls /
boot
proc
run
bin
lost+found
lib
home
dev
tmp
lib64
opt
root
sbin
var
etc
usr
mnt
sys
$
```

You also can use 3 flags to get more information of files. 
These flags are **-a**, **-l** and **-f**. 

Using the first one (**-a**) will show files that start with dot - hidden files.

Second one (**-l**) will show extra informations like permissions for this file, or size of it.

The last one (**-f**) just prints the full path of the file instead of it's name.

```bash
$ ./myls -a
myls.h
TODO.txt
mylib.c
.
.gitignore
testdir
Makefile
README.md
myls
..
myls.c
.git
$
```

```bash
$ ./myls -l
133     -rw-r--r--      myls.h
308     -rw-------      TODO.txt
2647    -rw-r--r--      mylib.c
4096    drwxr-xr-x      testdir
67      -rw-r--r--      Makefile
1506    -rw-r--r--      README.md
20816   -rwxr-xr-x      myls
544     -rw-r--r--      myls.c
Total:
8 files
30117 bytes
$
```

```bash
$ ./myls -f
./myls.h
./TODO.txt
./mylib.c
./testdir
./Makefile
./README.md
./myls
./myls.c
$
```


## Notes

The programm accepts 1 file max with flags, so you can't type multiple files in arguments like that.

```bash
./myls my_dir / /home/user # The programm will list files in my_dir and end up
```