# myTetris
Tetris clone from scratch written in C++. Just a fun way to learn the basics of game dev, the c++ language, and SDL2. My first larger C++ project!


## Goals
My main goal was to make a working marathon tetris game that uses the SDL2 library to render graphics. I am happy to say I achieved that goal. It was an amazing feeling to show my friends the running version and watch them actually be able to get into a flow state playing tetris on a program I had written!

My other main goals for this project were educational and creative. I wanted to practice C++, learn the basics of game development and the SDL2 graphics library for C++, and practice object oriented programming. Thus, this project uses an object oriented approach even to achieve things that would more straight-forwardly be done with a procedural approach.

## How to play
The basic game is marathon tetris.
Use the arrow keys to move the falling piece, X and Z to rotate, and SPACE to hold. Clear lines to increase your score!

## Features I want to add one day
1. Add levels and scoring.
2. Create a menu system.

## Graphics
All graphics are drawn with the Simple Direct Media Layer library ([SDL website](https://www.libsdl.org/)). I used [Lazy Foo's guide](http://lazyfoo.net/tutorials/SDL/index.php) to orient myself with the library.

## Game Loop
The basic Game Loop's design logic is taken from the youtuber [Let's Make Games](https://www.youtube.com/channel/UCAM9ZPgEIdeHAsmG50wqL1g), though the implementation is my own. I.e., I watched their tutorials before writing the basic game loop in main.cpp. Thank you for the helpful guide! The contents of the handleEvents(), update(), and render() functions are written by myself with the aid of SDL2's online documentation. The design and implementation of the class heirarchy are my own.
