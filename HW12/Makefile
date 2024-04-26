all: build_dir temp_stat_cli

build_dir:
	mkdir -p build

temp_stat_cli: main.o temp_lib.o csv_reader.o
	gcc -o build/temp_stat_cli build/main.o build/temp_lib.o build/csv_reader.o

main.o: main.c
	gcc -c -o build/main.o main.c

temp_lib.o: temp_api.c
	gcc -c -o build/temp_lib.o temp_api.c

csv_reader.o: csv_reader.c
	gcc -c -o build/csv_reader.o csv_reader.c


clean:
	rm -rf build/*.o build/temp_stat_cli
