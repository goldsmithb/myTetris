# myTetris
Tetris clone from scratch written in c++. Just a fun way to learn the basics of game dev, the c++ language, and SDL2.

## Base Game
The basic game is nothing special: just marathon tetris.
Use the arrow keys to move the falling piece, X and Z to rotate, and SPACE to hold. Clear lines to increase your score!

## TODOs
1. Finish the base game!
2. Create my own artwork rather than just draw rectangles and outlines for the tetris blocks.
3. Create a menu system.
4. Add fun graphics:
   - blocks explode during line clears.
   - special animation for getting a tetris.
   - block colors change based on level.
5. Add some sort of twist to make it more than just a tetris clone (TBD :3)

## Graphics
Right now, all graphics are drawn with SDL.

## Game Loop
The basic Game Loop design is taken from the youtuber [Let's Make Games](https://www.youtube.com/channel/UCAM9ZPgEIdeHAsmG50wqL1g) -- i.e., I followed their tutorials to make the basic gameloop in main.cpp. Thanks for the helpful guide! However, the contents of the handleEvents(), update(), and render() functions are written by myself with help from online documentation for SDL2, as is the design and implementation of the class heirarchy.
