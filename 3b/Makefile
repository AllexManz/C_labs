SILENT:
full: table_external clean


.SILENT:
table_external: main
	gcc main.o -o table_ext -Llib_table -l_table -Wl,-rpath,lib_table/
	valgrind --leak-check=full \
	--show-leak-kinds=all \
	-s \
	./table_ext

main:
	gcc -c -g main.c


.SILENT:
clean:
	rm *.o

.SILENT:
make_lib:
	gcc -c -fPIC lib_table/*.c
	gcc -shared -o lib_table/lib_table.so *.o
	rm *.o
