.SILENT:
full: memory clean


.SILENT:
memory: main
	gcc main.o -o memory -Llib_mem -l_mem -Wl,-rpath,lib_mem/
	valgrind ./memory --leak-check=full \
	--show-leak-kinds=all \
	-s \


main: main.c
	gcc -c -g -DMEMORY main.c

.SILENT:
clean:
	rm *.o

.SILENT:
make_lib:
	gcc -c -fPIC lib_mem/*.c
	gcc -shared -o lib_mem/lib_mem.so *.o
	rm lib_mem/*.o
