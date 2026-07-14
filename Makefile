
all: SnakeSearch.exe

SnakeSearch.exe: SnakeSearch.c BoardFuncs.c
	gcc SnakeSearch.c BoardFuncs.c -o SnakeSearch.exe

run: SnakeSearch.exe
	./SnakeSearch.exe

clean: 
	del SnakeSearch.exe