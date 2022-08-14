all:
	gcc -c unit_test.c s21_string.c
	ar rc libtest.a s21_string.o
	ranlib libtest.a
	gcc unit_test.o -L. -ltest -lcheck -o rezult -lm -lrt -lpthread -lsubunit
	rm *.o 
	rm *.a
