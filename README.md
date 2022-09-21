# myTetris
Tetris clone from scratch written in C++. Just a fun way to learn the basics of game dev, the c++ language, and SDL2. My first larger C++ project!


## Goals
My goals with this project were both educational and creative. I wanted to practice C++, learn the basics of game development and SDL2 graphics library for C++, and learn object oriented programming philosophy. Thus, this project uses an object oriented approach even to achieve things that would more straight-forwardly be done with a procedural approach. My desire to do this comes from my interest in the fascinating C++ language; as my education mostly consisted of programming in C and my university only offered one undergraduate class on OOP while I was there, I wanted to explore the OOP capabilities of C++.

My other goal of creating a working marathon tetris game that uses the SDL2 library to render graphics was also achieved. It was an amazing feeling to show my friends the running version and watch them actually be able to get into a flow state playing tetris on a program I had written!

## How to play
The basic game is marathon tetris.
Use the arrow keys to move the falling piece, X and Z to rotate, and SPACE to hold. Clear lines to increase your score!

## Features I want to add one day
1. Add levels and scoring
2. Create a menu system.

## Graphics
All graphics are drawn with the Simple Direct Media Layer library ([SDL website](https://www.libsdl.org/)).

## Game Loop
The basic Game Loop's design logic is taken from the youtuber [Let's Make Games](https://www.youtube.com/channel/UCAM9ZPgEIdeHAsmG50wqL1g), though the implimentation is my own. I.e., I watched their tutorials before making the basic gameloop in main.cpp. Than you for the helpful guide! The contents of the handleEvents(), update(), and render() functions are written by myself with the aid of SDL2's online documentation. The design and implementation of the class heirarchy are my own.
