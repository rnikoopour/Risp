risp: token.o scope.o parser.o eval.o risp.o
	clang++ -std=c++1z -o risp token.o scope.o parser.o eval.o risp.o

token.o: token.cpp token.hpp
	clang++ -std=c++1z -Wall -pedantic -c token.cpp 

scope.o: scope.cpp scope.hpp
	clang++ -std=c++1z -Wall -pedantic -c scope.cpp 

parser.o: parser.cpp parser.hpp token.hpp
	clang++ -std=c++1z -Wall -pedantic -c parser.cpp

eval.o: eval.cpp eval.hpp token.hpp
	clang++ -std=c++1z -Wall -pedantic -c eval.cpp

risp.o: risp.cpp token.hpp parser.hpp
	clang++ -std=c++1z -Wall -pedantic -c risp.cpp 

clean:
	rm -rf risp *.o
