#in the name of Allah

all:
	gcc src/main.c  `pkg-config --cflags gtk4` `pkg-config --libs gtk4` -o bin/main

