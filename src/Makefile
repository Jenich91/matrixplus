PROJECTNAME=s21_matrix_oop
.PHONY: all clean test $(PROJECTNAME).a gcov_report linter cppcheck style_check
SHELL := /bin/bash

CC = g++
SRC = s21_matrix_oop.cpp
OBJS = $(SRC:.cpp=.o)
CFLAGS = -std=c++17 -lstdc++ -Wall -Werror -Wextra
EXTRAWARN_FLAGS = -Wpedantic -Wshadow -Wuninitialized 
DEBUG_FLAG = -g
MAIN_SRC = main.cpp
GCOVFLAG = --coverage
LIB_NAME = s21_matrix_oop.a
TEST_SRCS = test.cpp
LDFLAGS += -lgtest

OS := $(shell uname)
ifeq ($(OS), Linux)
LDFLAGS += -lgtest_main -lpthread
LCOV=$(shell which lcov)
GENHTML=$(shell which genhtml)
endif

ifeq ($(OS),Darwin)
BREW := ${HOME}/homebrew/brew/bin/brew
ifeq ($(shell test -e $(BREW) && echo -n yes),yes)
LCOV=$(shell which lcov)
GENHTML=$(shell which genhtml)
else
LCOV=/opt/goinfre/$(USER)/brew/bin/lcov
GENHTML=/opt/goinfre/$(USER)/brew/bin/genhtml
endif
endif

all: clean $(LIB_NAME)

$(LIB_NAME): $(OBJS)
	ar rcs $(LIB_NAME) $(OBJS)

$(OBJS):
	$(CC) $(CFLAGS) $(SRC) -c -o $@

clean:
	rm -rf *.o *.a *.gcno test ./report ./*.dSYM test.info *.out *.gcda gcov_report *.info
	@clear

test: clean $(PROJECTNAME).a
	$(CC) $(CFLAGS) $(TEST_SRCS) $(LIB_NAME) -I./ -L./ $(LDFLAGS) -o test.out 
	./test.out

gcov_report: clean test
	$(CC) $(CFLAGS) $(GCOVFLAG) $(CFLAGS) $(TEST_SRCS) $(SRC) -I./ -L./ $(LDFLAGS) -o gcov.out
	./gcov.out
	$(LCOV) -c -d . -o coverage.info
	$(GENHTML) coverage.info -o gcov_report

.IGNORE: linter
linter:
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extensions=cpp *.cpp *.h
	rm -rf CPPLINT.cfg

cppcheck:
	cppcheck --enable=all --language=c++ --std=c++17 --suppress=missingIncludeSystem --suppress=unsafeClassCanLeak test.cpp *.cpp *.h

style_check: linter cppcheck

debug: $(PROJECTNAME).a
	$(CC) $(CFLAGS) $(TEST_SRCS) $(LIB_NAME) -I./ -L./ $(LDFLAGS) -o debug.out

check: clean debug style_check
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./debug.out
else
	valgrind -q --tool=memcheck --leak-check=full --leak-resolution=med ./debug.out
endif
