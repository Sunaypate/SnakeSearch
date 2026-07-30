OBJS =  BoardFuncs.o SnakeLogic.o SnakeAlg.o
BUILD_OBJS = $(addprefix build/, $(OBJS))


all: SnakeSearch.exe

SnakeSearch.exe: $(BUILD_OBJS) build/SnakeSearch.o
	gcc $(BUILD_OBJS) build/SnakeSearch.o -o SnakeSearch.exe

BotTester.exe: $(BUILD_OBJS) build/BotTester.o
	gcc $(BUILD_OBJS) build/BotTester.o -o BotTester.exe

build/SnakeSearch.o: SnakeSearch.c BoardFuncs.h SnakeLogic.h SnakeAlg.h DataStructs.h
	gcc -c SnakeSearch.c -o build/SnakeSearch.o

build/BotTester.o: BotTester.c BoardFuncs.h SnakeLogic.h SnakeAlg.h DataStructs.h
	gcc -c BotTester.c -o build/BotTester.o

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
	del *.exe