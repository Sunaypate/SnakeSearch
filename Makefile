CFLAGS = -Wall -Wextra -Werror

OBJS =  BoardFuncs.o SnakeLogic.o SnakeAlgs.o
BUILD_OBJS = $(addprefix build/, $(OBJS))

INLCUDE = BoardFuncs.h SnakeLogic.h SnakeAlgs.h DataStructs.h
INLCUDE_OBJS = $(addprefix include/, $(INLCUDE))

.PHONY: all run quickSim replay clean 

all: bin/SnakeSearch.exe

bin/SnakeSearch.exe: $(BUILD_OBJS) build/SnakeSearch.o
	gcc $(CFLAGS) $(BUILD_OBJS) build/SnakeSearch.o -o bin/SnakeSearch.exe

bin/BotTester.exe: $(BUILD_OBJS) build/BotTester.o
	gcc $(CFLAGS) $(BUILD_OBJS) build/BotTester.o -o bin/BotTester.exe

bin/SeedPlayer.exe: $(BUILD_OBJS) build/SeedPlayer.o
	gcc $(CFLAGS) $(BUILD_OBJS) build/SeedPlayer.o -o bin/SeedPlayer.exe

build/SnakeSearch.o: src/SnakeSearch.c $(INLCUDE_OBJS)
	gcc $(CFLAGS) -c src/SnakeSearch.c -o build/SnakeSearch.o

build/BotTester.o: src/BotTester.c $(INLCUDE_OBJS)
	gcc $(CFLAGS) -c src/BotTester.c -o build/BotTester.o

build/SeedPlayer.o: src/SeedPlayer.c $(INLCUDE_OBJS)
	gcc $(CFLAGS) -c src/SeedPlayer.c -o build/SeedPlayer.o


build/BoardFuncs.o: src/BoardFuncs.c include/BoardFuncs.h include/DataStructs.h
	gcc $(CFLAGS) -c src/BoardFuncs.c -o build/BoardFuncs.o

build/SnakeLogic.o: src/SnakeLogic.c include/SnakeLogic.h include/BoardFuncs.h include/DataStructs.h
	gcc $(CFLAGS) -c src/SnakeLogic.c -o build/SnakeLogic.o

build/SnakeAlgs.o: src/SnakeAlgs.c include/SnakeAlgs.h include/DataStructs.h
	gcc $(CFLAGS) -c src/SnakeAlgs.c -o build/SnakeAlgs.o


run: bin/SnakeSearch.exe
	bin/SnakeSearch.exe

quickSim: bin/BotTester.exe
	bin/BotTester.exe 200000 4

replay: bin/SeedPlayer.exe
	bin/SeedPlayer.exe

clean: 
	del /q build\*
	del /q bin\*