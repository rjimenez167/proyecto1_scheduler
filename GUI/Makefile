all: create_build printer printer2 printer3

create_build:
	mkdir -p build

printer:
	gcc -o build/printer printer.c `pkg-config --cflags gtk+-2.0 --libs`


printer2:
	gcc -o build/printer2 printer2.c `pkg-config --cflags gtk+-2.0 --libs`

printer3:
	gcc -o build/printer3 printer3.c `pkg-config --cflags gtk+-2.0 --libs`