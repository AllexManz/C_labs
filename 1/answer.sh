gcc -c -g main.c
gcc -c -g functions.c


gcc functions.o main.o -o ans.out

valgrind --leak-check=full \
	 --show-leak-kinds=all\
	 -s\
	 ./ans.out
