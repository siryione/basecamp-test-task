FileSearcher.a: src/FileSearcher.cpp
	g++ -std=c++20 -pthread -c src/FileSearcher.cpp  
	ar rvs FileSearcher.a FileSearcher.o
	rm FileSearcher.o

main: src/main.cpp src/FileSearcher.hpp FileSearcher.a  
	g++ -std=c++20 -pthread -o src/FileSearcher src/main.cpp FileSearcher.a
	bash -c "mv src/FileSearcher ."

clean: 
	rm FileSearcher
