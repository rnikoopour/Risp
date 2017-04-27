CC = /usr/bin/clang++
FLAGS = -std=c++1z -Wall -pedantic
RISP_OBJS = token.o scope.o parser.o eval.o risp.o
TEST_OBJS = test/tests-main.o test/tests-token.o token.o

all : risp tests

risp : token.o scope.o parser.o eval.o risp.o
	$(CC) $(FLAGS) $(RISP_OBJS) -o risp 

token.o : token.cpp token.hpp
	$(CC) $(FLAGS) -c token.cpp 

scope.o : scope.cpp scope.hpp
	$(CC) $(FLAGS) -c scope.cpp 

parser.o : parser.cpp parser.hpp token.hpp
	$(CC) $(FLAGS) -c parser.cpp

eval.o : eval.cpp eval.hpp token.hpp
	$(CC) $(FLAGS) -c eval.cpp

risp.o : risp.cpp token.hpp parser.hpp
	$(CC) $(FLAGS) -c risp.cpp 

tests-main.o : test/tests-main.cpp
	$(CC) $(FLAGS) -o test/tests-main.o -c test/tests-main.cpp

tests-token.o : token.o
	$(CC) $(FLAGS) -o test/tests-token.o -c test/tests-token.cpp

tests : tests-token.o tests-main.o
	$(CC) $(FLAGS) $(TEST_OBJS) -o test/tests

clean :
	rm -rf risp test/tests *.o test/*.o
