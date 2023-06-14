SILENT:
full: avl_tree clean


.SILENT:
avl_tree: main
	gcc -g main.o -o avl_trees -Llib_avl -l_avl -Wl,-rpath,lib_avl/
	valgrind --leak-check=full \
	--show-leak-kinds=all \
	-s \
	./avl_trees

main:
	gcc -c -g main.c


.SILENT:
clean:
	rm *.o

.SILENT:
make_lib:
	gcc -c -fPIC lib_avl/*.c
	gcc -shared -o lib_avl/lib_avl.so *.o
	rm *.o


