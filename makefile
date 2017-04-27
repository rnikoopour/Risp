CC = clang++
FLAGS = -std=c++1z -Wall -pedantic
OBJS = token.o scope.o parser.o eval.o risp.o
TEST_OBJS = test/tests-main.o test/tests-token.o

all: risp tests
default: risp
test: tests

risp: token.o scope.o parser.o eval.o risp.o
	$(CC) $(FLAGS) $(OBJS) -o risp 

token.o: token.cpp token.hpp
	$(CC) $(FLAGS) -c token.cpp 

scope.o: scope.cpp scope.hpp
	$(CC) $(FLAGS) -c scope.cpp 

parser.o: parser.cpp parser.hpp token.hpp
	$(CC) $(FLAGS) -c parser.cpp

eval.o: eval.cpp eval.hpp token.hpp
	$(CC) $(FLAGS) -c eval.cpp

risp.o: risp.cpp token.hpp parser.hpp
	$(CC) $(FLAGS) -c risp.cpp 

tests-main.o: test/tests-main.cpp
	$(CC) $(FLAGS) -o test/tests-main.o -c test/tests-main.cpp

tests-token.o: test/tests-token.cpp
	$(CC) $(FLAGS) -o test/tests-token.o -c test/tests-token.cpp

tests: test/tests-main.o test/tests-token.o
	$(CC) $(FLAGS) $(TEST_OBJS) -o test/tests

clean:
	rm -rf risp test/tests *.o test/*.o
