SNAKE GAME written using SDL2 and SDL2_ttf libraries
by Tomas Baublys
font used: "SummerDreamSans" by Letterhend Studio
compiled and tested using 13.2.0 version of the gcc compiler, using C99 standart
version 2.0, last modified 1/25/2024

To compile on Windows go to this folder and run:

gcc -o snake.exe *.c -ISDL2\x86_64-w64-mingw32\include -ISDL2\x86_64-w64-mingw32ttf\include -LSDL2\x86_64-w64-mingw32\lib -LSDL2\x86_64-w64-mingw32ttf\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf

If you are getting undefined reference to ... errors, change the local path to an absolute path

gcc -o snake.exe *.o -I(Absolute path to this folder)SDL2\x86_64-w64-mingw32\include -I(Absolute path to this folder)SDL2\x86_64-w64-mingw32ttf\include -L(Absolute path to this folder)SDL2\x86_64-w64-mingw32\lib -L(Absolute path to this folder)SDL2\x86_64-w64-mingw32ttf\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_ttf