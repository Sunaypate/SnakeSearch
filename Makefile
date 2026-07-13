
all: SnakeSearch.exe

SnakeSearch.exe: SnakeSearch.c
	gcc SnakeSearch.c -o SnakeSearch.exe

run: SnakeSearch.exe
	./SnakeSearch.exe

clean: 
	del SnakeSearch.exe