all: build_dir temp_stat_cli

debug: CCFLAGS += -DDEBUG -g
debug: build_dir temp_stat_cli

build_dir:
	mkdir -p build

temp_stat_cli: main.o temp_lib.o
	gcc $(CCFLAGS) -o build/temp_stat_cli build/main.o build/temp_lib.o

main.o: main.c
	gcc $(CCFLAGS) -c -o build/main.o main.c

temp_lib.o: temp_api.c
	gcc $(CCFLAGS) -c -o build/temp_lib.o temp_api.c

clean:
	rm -rf build/*.o build/temp_stat_cli
