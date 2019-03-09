# all: create_build printer printer2 printer3 test
all: create_build timer

create_build:
	mkdir -p build

timer:
	gcc -o build/timer timer.c -I.

test:
	gcc -o build/test test.c timer.c -I.