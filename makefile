CC = /usr/bin/clang++
FLAGS = -std=c++1z -Wall -pedantic
GENERAL_DEPS = token.o scope.o parser.o eval.o
RISP_DEPS = $(GENERAL_DEPS) risp.o
RISP_OBJS = $(GENERAL_DEPS) risp.o
TESTS_DEPS =  $(GENERAL_DEPS) tests-token.o tests-parser.o tests-main.o
TESTS_OBJS =  $(GENERAL_DEPS) test/tests-token.o test/tests-parser.o test/tests-main.o

all : risp tests

risp : $(RISP_DEPS)
	$(CC) $(FLAGS) $(RISP_OBJS) -o risp 

token.o : token.cpp token.hpp
	$(CC) $(FLAGS) -c token.cpp 

scope.o : scope.cpp scope.hpp
	$(CC) $(FLAGS) -c scope.cpp 

parser.o : parser.cpp parser.hpp
	$(CC) $(FLAGS) -c parser.cpp

eval.o : eval.cpp eval.hpp
	$(CC) $(FLAGS) -c eval.cpp

risp.o : risp.cpp
	$(CC) $(FLAGS) -c risp.cpp 

tests-main.o : test/tests-main.cpp
	$(CC) $(FLAGS) -o test/tests-main.o -c test/tests-main.cpp

tests-token.o : test/tests-token.cpp
	$(CC) $(FLAGS) -o test/tests-token.o -c test/tests-token.cpp

tests-parser.o : test/tests-parser.cpp
	$(CC) $(FLAGS) -o test/tests-parser.o -c test/tests-parser.cpp

tests : $(TESTS_DEPS) 
	$(CC) $(FLAGS) $(TESTS_OBJS) -o test/tests

clean :
	rm -rf risp test/tests *.o test/*.o
