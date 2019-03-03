# all: create_build printer printer2 printer3 test
all: create_build test

create_build:
	mkdir -p build

test:
	gcc -o build/test test.c threads_gui.c `pkg-config --cflags gtk+-2.0 --libs` -I.