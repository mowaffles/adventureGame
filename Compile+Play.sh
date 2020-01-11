#!/bin/bash

printf "\n\n This program requires the ncurses library to function\n\n"
sleep .2

gcc -o game.out adventure.c -lncurses

gnome-terminal --geometry=82x21 -e ./game.out
