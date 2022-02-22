# myTetris
My own Tetris from scratch written in c++. Just a fun way to learn basic game dev, the c++ language, and SDL2.

## Base Game
The basic game is nothing special: just marathon tetris.
Use the arrow keys to move the falling piece, X and Z to rotate, and SPACE to hold. Clear lines to increase your score!

## Graphics
Right now, all graphics are drawn with SDL.

## Game Loop
The basic Game Loop design is taken from the youtuber [Let's Make Games](https://www.youtube.com/channel/UCAM9ZPgEIdeHAsmG50wqL1g) -- i.e., I followed their tutorials to make the basic gameloop in main.cpp. Thanks for the helpful guide! However, the contents of the handleEvents(), update(), and render() functions are written by myself with help from online documentation for SDL2, as is the design and implementation of the class heirarchy.
