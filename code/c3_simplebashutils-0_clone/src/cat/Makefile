CFLAGS:=-Wall -Werror -Wextra -std=c11

all: s21_cat

s21_cat: s21_cat.c
	gcc $(CFLAGS) s21_cat.c -o s21_cat

style:
	cppcheck  *.c
	cp ../../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../../materials/linters/cpplint.py --extension=c *.c

clean:
	rm s21_cat

rebuild: clean all