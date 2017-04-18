risp: risp.o token.o environment.hpp
	clang++ -o risp risp.o token.o

risp.o: risp.cpp
	clang++ -std=c++1z -Wall -pedantic -c risp.cpp 

token.o: token.hpp token.cpp
	clang++ -std=c++1z -Wall -pedantic -c token.cpp 

clean:
	rm -rf risp.o token.o
