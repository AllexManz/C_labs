SILENT:
full: tree clean


.SILENT:
tree: main
	gcc main.o -o tree -Llib_bst -l_bst -Wl,-rpath,lib_bst/
	valgrind --leak-check=full \
	--show-leak-kinds=all \
	-s \
	./tree


main: main.c
	gcc -c -g main.c

.SILENT:
clean:
	rm *.o

.SILENT:
make_lib:
	gcc -c -fPIC lib_bst/*.c
	gcc -shared -o lib_bst/lib_bst.so *.o
	rm *.o
