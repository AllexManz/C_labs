SILENT:
full: graph clean


.SILENT:
graph: main
	gcc -g main.o vertex.o edge.o graph.o algo.o -o graph
	valgrind --leak-check=full \
	--show-leak-kinds=all \
	-s \
	./graph

main:
	gcc -c -g main.c vertex.c edge.c graph.c algo.c


.SILENT:
clean:
	rm *.o

.SILENT:
make_lib:
	gcc -c -fPIC lib_avl/*.c
	gcc -shared -o lib_avl/lib_avl.so *.o
	rm *.o

