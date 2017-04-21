risp: token.o parser.o risp.o
	clang++ -std=c++1z -o risp token.o parser.o risp.o

token.o: token.cpp token.hpp
	clang++ -std=c++1z -Wall -pedantic -c token.cpp 

parser.o: parser.cpp parser.hpp token.hpp
	clang++ -std=c++1z -Wall -pedantic -c parser.cpp

risp.o: risp.cpp token.hpp parser.hpp
	clang++ -std=c++1z -Wall -pedantic -c risp.cpp 

clean:
	rm -rf risp *.o
