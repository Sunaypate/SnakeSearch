
all: SnakeSearch.exe

SnakeSearch.exe: SnakeSearch.o BoardFuncs.o SnakeLogic.o
	gcc SnakeSearch.o BoardFuncs.o SnakeLogic.o -o SnakeSearch.exe

SnakeSearch.o: SnakeSearch.c BoardFuncs.h SnakeLogic.h DataStructs.h
	gcc -c SnakeSearch.c -o SnakeSearch.o

BoardFuncs.o: BoardFuncs.c BoardFuncs.h DataStructs.h
	gcc -c BoardFuncs.c -o BoardFuncs.o

SnakeLogic.o: SnakeLogic.c SnakeLogic.h BoardFuncs.h DataStructs.h
	gcc -c SnakeLogic.c -o SnakeLogic.o

run: SnakeSearch.exe
	./SnakeSearch.exe

clean: 
	del SnakeSearch.exe
	del *.o