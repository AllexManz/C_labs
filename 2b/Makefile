.SILENT:
lab2_list: main.o_list
	gcc main.o process.o -o lab2_list -Lstack_list -l_list -Wl,-rpath,stack_list/
	valgrind ./lab2_list --leak-check=full \
	--show-leak-kinds=all \
	-s \

.SILENT:
lab2_vector: main.o_vector
	gcc main.o process.o -o lab2_vector -Lstack_vector -l_vector -Wl,-rpath,stack_vector/
	valgrind ./lab2_vector --leak-check=full \
	--show-leak-kinds=all \
	-s \

main.o_list: main.c
	gcc -c -g -DLIST main.c process.c

main.o_vector: main.c
	gcc -c -g -DVECTOR main.c process.c

.SILENT:
clean:
	rm *.o
