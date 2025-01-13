CC=gcc
CFLAGS=-Wall -Wextra -Werror
GCOVFLAGS=-fprofile-arcs -ftest-coverage
HEADER=s21_string.h
TESTS=project.out
SOURCES_ALL:=$(wildcard *.c)
SOURCES_FUN:=$(shell find . -not -name "s21_string_test.c" -name "*.c")
OBJECTS:=$(patsubst %.c,%.o,$(SOURCES_ALL))
OBJ_LIBRARY:=$(patsubst %.c,%.o,$(SOURCES_FUN))
UNAME:=$(shell uname -s)
ifeq ($(UNAME),Linux)
	LDFLAGS=-lcheck -lsubunit -lm -lrt -lpthread
	OPEN_CM=xdg-open
endif
ifeq ($(UNAME),Darwin)
	LDFLAGS=-lcheck
	OPEN_CM=open
endif

all : test s21_string.a gcov_report

check : s21_string_test.check
	checkmk clean_mode=1 s21_string_test.check > s21_string_test.c

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

test : check $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TESTS) $(LDFLAGS)
	./$(TESTS)

s21_string.a : $(OBJ_LIBRARY) $(HEADER)
	ar rcs s21_string.a $(OBJ_LIBRARY)
	ranlib s21_string.a

gcov_report : check
	$(CC) $(GCOVFLAGS) $(SOURCES_ALL) $(LDFLAGS) -o report.out
	./report.out
	gcov -f $(SOURCES_FUN)
	lcov -t "gcov_report" -o Coverage_Report.info -c -d .
	genhtml -o ./report Coverage_Report.info
	$(OPEN_CM) ./report/index-sort-f.html

rebuild : clean all

clean :  
	rm -f *.o *.a *.gcno *.gcda *.info *.out *.gcov
	rm -rf ./report
