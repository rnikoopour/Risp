risp: token.o parser.o risp.o
	clang++ -o risp token.o parser.o risp.o

token.o: token.hpp token.cpp
	clang++ -std=c++1z -Wall -pedantic -c token.cpp 

parser.o: parser.hpp parser.cpp
	clang++ -std=c++1z -Wall -pedantic -c parser.cpp 

risp.o: risp.cpp environment.hpp parser.hpp
	clang++ -std=c++1z -Wall -pedantic -c risp.cpp 

clean:
	rm -rf risp *.o
