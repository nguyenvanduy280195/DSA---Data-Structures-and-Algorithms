all: pokemon_legend

pokemon_legend: main.o pokemon_legend.o
	g++ -std=gnu++11 main.o pokemon_legend.o -o pokemon_legend

main.o: main.cpp
	g++ -std=gnu++11 -c main.cpp

pokemon_legend.o: pokemon_legend.cpp
	g++ -std=gnu++11 -c pokemon_legend.cpp    

clean:
	rm *o pokemon_legend
