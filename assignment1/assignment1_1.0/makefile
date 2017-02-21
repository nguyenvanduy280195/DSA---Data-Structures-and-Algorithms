all: pokemon

pokemon: main.o pokemon.o
	g++ main.o pokemon.o -o pokemon

main.o: main.cpp
	g++ -c main.cpp

pokemon.o: pokemon.cpp
	g++ -c pokemon.cpp    

clean:
	rm *o pokemon
