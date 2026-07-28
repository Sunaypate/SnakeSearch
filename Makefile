OBJS = SnakeSearch.o BoardFuncs.o SnakeLogic.o SnakeAlg.o
BUILD_OBJS = $(addprefix build/, $(OBJS))


all: SnakeSearch.exe

SnakeSearch.exe: $(BUILD_OBJS)
	gcc $(BUILD_OBJS) -o SnakeSearch.exe

build/SnakeSearch.o: SnakeSearch.c BoardFuncs.h SnakeLogic.h DataStructs.h
	gcc -c SnakeSearch.c -o build/SnakeSearch.o

build/BoardFuncs.o: BoardFuncs.c BoardFuncs.h DataStructs.h
	gcc -c BoardFuncs.c -o build/BoardFuncs.o

build/SnakeLogic.o: SnakeLogic.c SnakeLogic.h BoardFuncs.h DataStructs.h
	gcc -c SnakeLogic.c -o build/SnakeLogic.o

build/SnakeAlg.o: SnakeAlg.c SnakeAlg.h DataStructs.h
	gcc -c SnakeAlg.c -o build/SnakeAlg.o

run: SnakeSearch.exe
	./SnakeSearch.exe

clean: 
	del /q /f build\*
	del SnakeSearch.exe