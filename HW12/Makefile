all: build_dir temp_stat_cli

build_dir:
	mkdir -p build

temp_stat_cli: main.o temp_lib.o
	gcc -o build/temp_stat_cli build/main.o build/temp_lib.o

main.o: main.c temp_api.h
	gcc  -c -o build/main.o main.c

temp_lib.o: temp_api.c
	gcc  -c -o build/temp_lib.o temp_api.c

clean:
	rm -rf build/*.o build/temp_stat_cli

