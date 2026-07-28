#include "SnakeAlg.h"

#include "DataStructs.h"
#include <stdio.h>
#include <stdbool.h>

typedef enum relativePositon {
	BEFORE,
	AT,
	PAST
} Target;

char simpleMove(gameData gameInfo, Snake* snakeHead) {
	Coor appleLoc = *(gameInfo.appleLocation);
	Target aboveApple;
	Target leftApple;
	
	if (snakeHead->Row < appleLoc.Row) {
		aboveApple = BEFORE;
	}
	else if (snakeHead->Row > appleLoc.Row) {
		aboveApple = PAST;
	}
	else {
		aboveApple = AT;
	}

	if (snakeHead->Column < appleLoc.Column) {
		leftApple = BEFORE;
	}
	else if (snakeHead->Column > appleLoc.Column) {
		leftApple = PAST;
	}
	else {
		leftApple = AT;
	}
	
	switch (aboveApple) {
		case (BEFORE):
			return 's';
		break;

		case (AT):
			switch (leftApple) {
				case (BEFORE):
					return 'd';
				break;

				case (PAST):
					return 'a';
				break;
			}
		break;

		case (PAST):
			return 'w';
		break;
	}
}
