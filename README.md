# WinProg
Window desktop program built in C..

# Command
```
# compile
gcc -o output.exe menu_one.c
# compile resource (mingw)
windres res.rc -O coff -o my.res
# or
windres 4_menu_one.rc 4_menu_one.o
gcc 4_menu_one.c 4_menu_one.o
```

# REF
http://www.winprog.org/tutorial/start.html