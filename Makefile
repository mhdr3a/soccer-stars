CC := g++
FLAGS += --std=c++11 -l SDL2 -l SDL2_image -l SDL2_ttf -l SDL2_mixer

all: soccerStars.out

soccerStars.out: main.o rsdl.o vector2d.o piece.o soccerstars.o
	$(CC) main.o rsdl.o vector2d.o piece.o soccerstars.o $(FLAGS) -o soccerStars.out

main.o: RSDL/src/rsdl.hpp Vector2D.hpp Piece.hpp SoccerStars.hpp main.cpp
	$(CC) -c --std=c++11 main.cpp -o main.o

rsdl.o: RSDL/src/rsdl.hpp RSDL/src/rsdl.cpp
	$(CC) -c --std=c++11 RSDL/src/rsdl.cpp -o rsdl.o

vector2d.o: RSDL/src/rsdl.hpp Vector2D.hpp Vector2D.cpp
	$(CC) -c --std=c++11 Vector2D.cpp -o vector2d.o

piece.o: RSDL/src/rsdl.hpp Vector2D.hpp Piece.hpp Piece.cpp
	$(CC) -c --std=c++11 Piece.cpp -o piece.o

soccerstars.o: RSDL/src/rsdl.hpp Vector2D.hpp Piece.hpp SoccerStars.hpp SoccerStars.cpp
	$(CC) -c --std=c++11 SoccerStars.cpp -o soccerstars.o

.PHONY: clean
clean:
	rm -r *.o