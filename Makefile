# all: create_build printer printer2 printer3 test
all: create_build test

create_build:
	mkdir -p build
	cp threads_setup.csv build/threads_setup.csv

test:
	gcc -o  build/main main.c threads/context_list.c