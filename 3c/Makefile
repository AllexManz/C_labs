.SILENT:
full: hash clean


.SILENT:
hash: main
	gcc -lreadline main.o -o hash -Llib_hash -l_hash -Wl,-rpath,lib_hash/
	valgrind --leak-check=full \
	./hash


main: main.c
	gcc -c -g -DHASH main.c

.SILENT:
clean:
	rm *.o

.SILENT:
make_lib:
	gcc -c -fPIC lib_hash/*.c
	gcc -shared -o lib_hash/lib_hash.so *.o
	rm *.o
