# myTetris
Tetris clone from scratch written in C++. Just a fun way to learn the basics of game dev, the c++ language, and SDL2. My first C++ project :,)

## How to play
The basic game is marathon tetris.
Use the arrow keys to move the falling piece, X and Z to rotate, and SPACE to hold. Clear lines to increase your score!

## TODOs
1. Use templates instead of drawing with rectangles
2. Add levels
3. Create a menu system.
4. Add more interesting graphics:

## Graphics
Right now, all graphics are drawn with SDL.

## Game Loop
The basic Game Loop design is taken from the youtuber [Let's Make Games](https://www.youtube.com/channel/UCAM9ZPgEIdeHAsmG50wqL1g) -- i.e., I followed their tutorials to make the basic gameloop in main.cpp. Thanks for the helpful guide! However, the contents of the handleEvents(), update(), and render() functions are written by myself with help from online documentation for SDL2, as is the design and implementation of the class heirarchy.
