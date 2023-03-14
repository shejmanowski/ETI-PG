#define MAX_SIZE_COLOR_NAME 10
#define MAX_NUMBER_OF_PILES 6
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<iostream>
using namespace std;

typedef struct {
	int color;
	int value;
}Card;

typedef struct {
	int numberOfCards;
	int sumOfValues;
	int pileState;
	Card** cardsOnPile;
}Pile;

typedef struct {
	Card** cardsInHand;
	Card** cardsOnDeck;
	int numberOfCardsInHand;
	int numberOfCardsOnDeck;
	int score;
	int colorResistance;		//if 0, then isn't resistant to any of colors
}Player;

typedef struct {
	int numberOfPlayers, numberOfPiles, activePlayer, explosionThreshold, numberOfColors;
	int valueOfGreens;
	int numberOfColorCards, numberOfGreenCards, numberOfAllCards;
	int numberOfColorValues;
	int isStateCorrect;
	Card** allCards;
	Player** players;
	Pile** piles;
}GameStatus;

int colorToNumber(char colorName[]), isEqual(int tab[7]), compare(const void* a, const void* b);
void printColorName(int colorNumber);

void loadGame(GameStatus* gs) {
	scanf_s("active player = %d\nplayers number = %d\nexplosion threshold = %d\n", &gs->activePlayer, &gs->numberOfPlayers, &gs->explosionThreshold);
	int getcharValue, x, value, k = 0;
	char colorName[MAX_SIZE_COLOR_NAME];
	gs->players = (Player**)malloc(sizeof(Player*) * gs->numberOfPlayers);
	//zerowanie
	for (int i = 0; i < gs->numberOfPlayers; i++) {
		int numberOfEachColorOnPlayersDeck[MAX_NUMBER_OF_PILES] = { 0, 0, 0, 0, 0, 0 };			//excluding green
		gs->players[i] = (Player*)malloc(sizeof(Player));
		gs->players[i]->cardsInHand = (Card**)malloc(sizeof(Card*));
		gs->players[i]->cardsOnDeck = (Card**)malloc(sizeof(Card*));
		gs->players[i]->numberOfCardsInHand = 0;
		gs->players[i]->numberOfCardsOnDeck = 0;
		for (int j = 0; j < 2; j++) {									//doing it two times, one for hand cards, second
			if (j == 0)													//if reading hand cards
				scanf_s("%d player hand cards:", &x);
			else														//if reading deck cards
				scanf_s("%d player deck cards:", &x);
			while (1) {
				do {
					getcharValue = getchar();
				} while (getcharValue == ' ' || getcharValue == '\t');   //deleting whitespaces
				if (getcharValue == '\n' || getcharValue == EOF) {         //stop reading given line if it is end of line or end of file
					break;
				}
				cin.unget();
				scanf_s("%d", &value);
				scanf_s("%9s", colorName, MAX_SIZE_COLOR_NAME);
				gs->numberOfAllCards++;
				if (j == 0) {		//if reading hand cards
					if (gs->players[i]->numberOfCardsInHand != 0) {			//for every card except first one, makeing the size of an array bigger
						gs->players[i]->cardsInHand = (Card**)realloc(gs->players[i]->cardsInHand, sizeof(Card*) * (gs->players[i]->numberOfCardsInHand + 1));
					}
					gs->players[i]->cardsInHand[gs->players[i]->numberOfCardsInHand] = (Card*)malloc(sizeof(Card));
					gs->players[i]->cardsInHand[gs->players[i]->numberOfCardsInHand]->color = colorToNumber(colorName);
					gs->players[i]->cardsInHand[gs->players[i]->numberOfCardsInHand]->value = value;
					gs->players[i]->numberOfCardsInHand++;
				}
				else {				//if reading deck cards
					if (gs->players[i]->numberOfCardsOnDeck != 0) {			//for every card except first one, makeing the size of an array bigger
						gs->players[i]->cardsOnDeck = (Card**)realloc(gs->players[i]->cardsOnDeck, sizeof(Card*) * (gs->players[i]->numberOfCardsOnDeck + 1));
					}
					gs->players[i]->cardsOnDeck[gs->players[i]->numberOfCardsOnDeck] = (Card*)malloc(sizeof(Card));
					gs->players[i]->cardsOnDeck[gs->players[i]->numberOfCardsOnDeck]->color = colorToNumber(colorName);
					gs->players[i]->cardsOnDeck[gs->players[i]->numberOfCardsOnDeck]->value = value;
					gs->players[i]->numberOfCardsOnDeck++;
					if (colorToNumber(colorName) != 0) {
						numberOfEachColorOnPlayersDeck[colorToNumber(colorName) - 1]++;
					}
				}
			}
		}
		int mostCommonColor = 0;
		int numberOfApperance = numberOfEachColorOnPlayersDeck[0];
		int numberOfMostCommonColors = 0;
		for (int j = 0; j < MAX_NUMBER_OF_PILES - 1; j++) {		//finding most common color
			if (numberOfEachColorOnPlayersDeck[j + 1] > numberOfApperance) {
				mostCommonColor = j + 1;
				numberOfApperance = numberOfEachColorOnPlayersDeck[j + 1];
			}
		}
		for (int j = 0; j < MAX_NUMBER_OF_PILES - 1; j++) {		//checking number of apperance of the most common color
			if (numberOfApperance == numberOfEachColorOnPlayersDeck[j]) {
				numberOfMostCommonColors++;
			}
		}
		if (numberOfMostCommonColors == 1)						//if there is only one color with given number of apperance, it is the color, the player is resistant to
			gs->players[i]->colorResistance = mostCommonColor + 1;
		else													//if there is more then one color with given number of apperance, the player isn't resistant to any color
			gs->players[i]->colorResistance = 0;
	}
	gs->piles = (Pile**)malloc(sizeof(Pile*) * MAX_NUMBER_OF_PILES);
	while (getchar() != EOF) {							//reading unitll it's end of file
		cin.unget();
		scanf_s("%d pile cards:", &gs->numberOfPiles);
		gs->piles[k] = (Pile*)malloc(sizeof(Pile));
		gs->piles[k]->cardsOnPile = (Card**)malloc(sizeof(Card*));
		gs->piles[k]->numberOfCards = 0;
		gs->piles[k]->cardsOnPile[gs->piles[k]->numberOfCards] = (Card*)malloc(sizeof(Card));
		while (1) {
			do {
				getcharValue = getchar();
			} while (getcharValue == ' ' || getcharValue == '\t');      //deleting whitespaces
			if (getcharValue == '\n' || getcharValue == EOF) {			//stop reading given line if it is end of line or end of file
				k++; //zmienic na indexofpile
				break;
			}
			cin.unget();
			scanf_s("%d", &value);
			scanf_s("%9s", colorName, MAX_SIZE_COLOR_NAME);
			if (gs->piles[k]->numberOfCards != 0) {						//for every card except first one, make the size of an array bigger
				gs->piles[k]->cardsOnPile = (Card**)realloc(gs->piles[k]->cardsOnPile, sizeof(Card*) * (gs->piles[k]->numberOfCards + 1));
			}
			gs->piles[k]->cardsOnPile[gs->piles[k]->numberOfCards] = (Card*)malloc(sizeof(Card));
			gs->piles[k]->cardsOnPile[gs->piles[k]->numberOfCards]->color = colorToNumber(colorName);
			gs->piles[k]->cardsOnPile[gs->piles[k]->numberOfCards]->value = value;
			gs->piles[k]->numberOfCards++;
		}
	}
}

void gameScore(GameStatus* gs) {
	for (int i = 0; i < gs->numberOfPlayers; i++) {
		gs->players[i]->score = 0;
		for (int j = 0; j < gs->players[i]->numberOfCardsOnDeck; j++) {
			if (gs->players[i]->cardsOnDeck[j]->color == 0)		//if the color of the card is green adding 2 points
				gs->players[i]->score += 2;
			else if (gs->players[i]->cardsOnDeck[j]->color != gs->players[i]->colorResistance)
				gs->players[i]->score++;
		}
	}
}

//Friday the 13th-8

void printGameScore(GameStatus* gs) {
	int* isPlayerResistantForThisColor = new int[gs->numberOfPlayers];
	int indexOfResistantPlayer = 0;
	for (int i = 0; i < gs->numberOfPlayers; i++) {
		isPlayerResistantForThisColor[i] = 0;
		if (gs->players[i]->colorResistance != 0) {
			isPlayerResistantForThisColor[i] = gs->players[i]->colorResistance;
			indexOfResistantPlayer = i;
		}
	}
	for (int i = 0; i < gs->numberOfPlayers; i++) {
		if (isPlayerResistantForThisColor[i] != 0) {
			printf("Na kolor ");
			printColorName(gs->players[i]->colorResistance);
			printf(" odporny jest gracz %d\n", indexOfResistantPlayer + 1);
		}
	}
	for (int i = 0; i < gs->numberOfPlayers; i++) {
		printf("Wynik gracza %d = %d\n", i + 1, gs->players[i]->score);
	}
	delete[] isPlayerResistantForThisColor;
}

void makeEasyMove(GameStatus* gs) {
	int valueOfCardToMove = gs->players[gs->activePlayer - 1]->cardsInHand[0]->value;
	int colorOfCardToMove = gs->players[gs->activePlayer - 1]->cardsInHand[0]->color;
	gs->players[gs->activePlayer - 1]->cardsInHand++;
	gs->players[gs->activePlayer - 1]->numberOfCardsInHand--;
	if (colorOfCardToMove == 0) {		//if the card to move is green, moving it to fist pile
		gs->piles[0]->cardsOnPile = (Card**)realloc(gs->piles[0]->cardsOnPile, sizeof(Card*) * (gs->piles[0]->numberOfCards + 1));
		gs->piles[0]->cardsOnPile[gs->piles[0]->numberOfCards] = (Card*)malloc(sizeof(Card));
		gs->piles[0]->cardsOnPile[gs->piles[0]->numberOfCards]->color = colorOfCardToMove;
		gs->piles[0]->cardsOnPile[gs->piles[0]->numberOfCards]->value = valueOfCardToMove;
		gs->piles[0]->numberOfCards++;
	}
	else {								//if the card isn't green, cosider other cases
		for (int i = 0; i < gs->numberOfPiles; i++) {			
			if (gs->piles[i]->cardsOnPile[0]->color == colorOfCardToMove) {			//if there is pile of given color, moving it to this pile
				gs->piles[i]->cardsOnPile = (Card**)realloc(gs->piles[i]->cardsOnPile, sizeof(Card*) * (gs->piles[i]->numberOfCards + 1));
				gs->piles[i]->cardsOnPile[gs->piles[i]->numberOfCards] = (Card*)malloc(sizeof(Card));
				gs->piles[i]->cardsOnPile[gs->piles[i]->numberOfCards]->color = colorOfCardToMove;
				gs->piles[i]->cardsOnPile[gs->piles[i]->numberOfCards]->value = valueOfCardToMove;
				gs->piles[i]->numberOfCards++;
				return;
			}
		}
		for (int i = 0; i < gs->numberOfPiles; i++) {
			if (gs->piles[i]->numberOfCards == 0) {									//if there is not pile of given color, moving it to first empty pile
				gs->piles[i]->cardsOnPile = (Card**)realloc(gs->piles[0]->cardsOnPile, sizeof(Card*) * (gs->piles[i]->numberOfCards + 1));
				gs->piles[i]->cardsOnPile[gs->piles[i]->numberOfCards] = (Card*)malloc(sizeof(Card));
				gs->piles[i]->cardsOnPile[gs->piles[i]->numberOfCards]->color = colorOfCardToMove;
				gs->piles[i]->cardsOnPile[gs->piles[i]->numberOfCards]->value = valueOfCardToMove;
				gs->piles[i]->numberOfCards++;
				break;
			}
		}
	}
}

void printStateAfterMove(GameStatus* gs) {
	printf("active player = %d\nplayers number = %d\nexplosion threshold = %d\n", (gs->activePlayer % gs->numberOfPlayers) + 1, gs->numberOfPlayers, gs->explosionThreshold);
	for (int i = 0; i < gs->numberOfPlayers; i++) {
		printf("%d player hand cards:", i + 1);
		for (int j = 0; j < gs->players[i]->numberOfCardsInHand; j++) {
			printf(" %d ", gs->players[i]->cardsInHand[j]->value);
			printColorName(gs->players[i]->cardsInHand[j]->color);
		}
		printf("\n");
		printf("%d player deck cards:", i + 1);
		for (int j = 0; j < gs->players[i]->numberOfCardsOnDeck; j++) {
			printf(" %d ", gs->players[i]->cardsOnDeck[j]->value);
			printColorName(gs->players[i]->cardsOnDeck[j]->color);
		}
		printf("\n");
	}
	for (int i = 0; i < gs->numberOfPiles; i++) {
		printf("%d pile cards:", i + 1);
		for (int j = 0; j < gs->piles[i]->numberOfCards; j++) {
			printf(" %d ", gs->piles[i]->cardsOnPile[j]->value);
			printColorName(gs->piles[i]->cardsOnPile[j]->color);
		}
		printf("\n");
	}
}

void checkAndHandleExplosion(GameStatus* gs) {
	int indexOfPileThatExploded = 0, pileShouldExplode = 0;
	for (int i = 0; i < gs->numberOfPiles; i++) {
		int valuesSum = 0;
		for (int j = 0; j < gs->piles[i]->numberOfCards; j++) {
			valuesSum += gs->piles[i]->cardsOnPile[j]->value;
		}
		if (valuesSum >= gs->explosionThreshold) {
			indexOfPileThatExploded = i;
			pileShouldExplode = 1;
			break;
		}
	}
	if (!pileShouldExplode) {
		return;
	}
	if (gs->players[gs->activePlayer - 1]->numberOfCardsOnDeck == 0) {		
		gs->players[gs->activePlayer - 1]->cardsOnDeck = (Card**)realloc(gs->players[gs->activePlayer - 1]->cardsOnDeck, sizeof(Card*) * gs->piles[indexOfPileThatExploded]->numberOfCards);
	}
	for (int i = 0; i < gs->piles[indexOfPileThatExploded]->numberOfCards; i++) {
		gs->players[gs->activePlayer - 1]->cardsOnDeck[i] = (Card*)malloc(sizeof(Card));
		gs->players[gs->activePlayer - 1]->cardsOnDeck[i]->value = gs->piles[indexOfPileThatExploded]->cardsOnPile[i]->value;
		gs->players[gs->activePlayer - 1]->cardsOnDeck[i]->color = gs->piles[indexOfPileThatExploded]->cardsOnPile[i]->color;
		gs->players[gs->activePlayer - 1]->numberOfCardsOnDeck++;
	}
	for (int i = 0; i < gs->piles[indexOfPileThatExploded]->numberOfCards; i++) {
		free(gs->piles[indexOfPileThatExploded]->cardsOnPile[i]);
	}
	gs->piles[indexOfPileThatExploded]->numberOfCards = 0;
}

//Friday the 13th-7b

void cauldornExplosion(GameStatus* gs) {
	loadGame(gs);
	makeEasyMove(gs);
	checkAndHandleExplosion(gs);
	printStateAfterMove(gs);
}

//Friday the 13th-7a

void easyMove(GameStatus* gs) {
	loadGame(gs);
	makeEasyMove(gs);
	printStateAfterMove(gs);
}

//Friday the 13th-6

void checkState(GameStatus* gs) {
	scanf_s("active player = %d\nplayers number = %d\nexplosion threshold = %d\n",&gs->activePlayer, &gs->numberOfPlayers, &gs->explosionThreshold);
	int x;
	char a[MAX_SIZE_COLOR_NAME];
	int getcharValue;
	gs->players = new Player * [gs->numberOfPlayers];
	gs->numberOfAllCards = 0;
	for (int i = 0; i < gs->numberOfPlayers; i++) {
		gs->players[i] = new Player;
		gs->players[i]->numberOfCardsInHand = 0;
		gs->players[i]->numberOfCardsOnDeck = 0;
		for (int j = 0; j < 2; j++) {	//doing it two times, one for hand cards, second
			if (j == 0) {		//if reading hand cards
				scanf_s("%d player hand cards:", &x);
			}
			else {				//if reading deck cards
				scanf_s("%d player deck cards:", &x);
			}
			while (1) {
				do {
					getcharValue = getchar();
				} while (getcharValue == ' ' || getcharValue == '\t');		//deleting whitespaces
				if (getcharValue == '\n' || getcharValue == EOF) {			//stop reading given line if it is end of line or end of file
					break;
				}
				cin.unget();
				scanf_s("%d", &x);
				gs->numberOfAllCards++;
				if (j == 0) {		//if reading hand cards
					gs->players[i]->numberOfCardsInHand++;
				}
				else {				//if reading deck cards
					gs->players[i]->numberOfCardsOnDeck++;
				}
				scanf_s("%9s", a, 10);
			}
		}
	}
	int indexOfPile = 0;
	gs->piles = new Pile * [MAX_NUMBER_OF_PILES];
	int previusColor[MAX_NUMBER_OF_PILES], areColorsOnPileSame[MAX_NUMBER_OF_PILES] = { 1, 1, 1, 1, 1, 1 };
	int stateIsOk = 1;
	while (getchar() != EOF) {		//wczytywanie danych do koñca pliku
		gs->piles[indexOfPile] = new Pile;
		gs->piles[indexOfPile]->numberOfCards = 0;
		gs->piles[indexOfPile]->sumOfValues = 0;
		cin.unget();
		scanf_s("%d pile cards:", &gs->numberOfPiles);
		while (1) {
			do {
				getcharValue = getchar();
			} while (getcharValue == ' ' || getcharValue == '\t');		//deleting whitespaces
			if (getcharValue == '\n' || getcharValue == EOF) {			//stop reading given line if it is end of line or end of file
				break;
			}
			cin.unget();
			scanf_s("%d", &x);
			gs->numberOfAllCards++;
			gs->piles[indexOfPile]->numberOfCards++;
			gs->piles[indexOfPile]->sumOfValues += x;
			scanf_s("%9s", a, MAX_SIZE_COLOR_NAME);
			if (gs->piles[indexOfPile]->numberOfCards == 1) {
				previusColor[indexOfPile] = colorToNumber(a);
			}
			else {
				if (previusColor[indexOfPile] != colorToNumber(a) && previusColor[indexOfPile] != 0 && colorToNumber(a) != 0) {
					areColorsOnPileSame[indexOfPile] = 0;
				}
			}
		}
		indexOfPile++;
	}
	for (int i = 0; i < gs->activePlayer - 1; i++) {
		gs->players[i]->numberOfCardsInHand++;
	}
	if (gs->numberOfAllCards % gs->numberOfPlayers != 0) {
		for (int i = 0; i < gs->numberOfAllCards % gs->numberOfPlayers; i++) {
			gs->players[i]->numberOfCardsInHand--;
		}
	}
	for (int i = 0; i < gs->numberOfPlayers - 1; i++) {
		if (gs->players[i]->numberOfCardsInHand != gs->players[i + 1]->numberOfCardsInHand) {
			printf("The number of players cards on hand is wrong\n");
			stateIsOk = 0;
			break;
		}
	}
	for (int i = 0; i < gs->numberOfPiles; i++) {
		if (!areColorsOnPileSame[i]) {
			printf("Two different colors were found on the %d pile\n", i + 1);
			stateIsOk = 0;
		}
	}
	for (int i = 0; i < gs->numberOfPiles; i++) {
		if (gs->piles[i]->sumOfValues >= gs->explosionThreshold) {
			printf("Pile number %d should explode earlier\n", i + 1);
			stateIsOk = 0;
		}
	}
	if (stateIsOk) {
		printf("Current state of the game is ok");
	}
}

void loadAllCards(GameStatus* gs) {
	scanf_s("active player = 1\nplayers number = %d\n", &gs->numberOfPlayers);
	int value, getcharValue, k = 0;
	char a[10];
	gs->allCards = (Card**)malloc(sizeof(Card*));
	for (int i = 0; i < gs->numberOfPlayers; i++) {
		for (int j = 0; j < 2; j++) {
			if (j == 0) {
				scanf_s("%d player hand cards:", &value);
			}
			else {
				scanf_s("%d player deck cards:", &value);
			}
			while (1) {
				do {
					getcharValue = getchar();
				} while (getcharValue == ' ' || getcharValue == '\t');
				if (getcharValue == '\n' || getcharValue == EOF) {
					break;
				}
				cin.unget();
				scanf_s("%d", &value);
				scanf_s("%9s", a, MAX_SIZE_COLOR_NAME);
				if (k != 0) {
					gs->allCards = (Card**)realloc(gs->allCards, sizeof(Card*) * (k + 1));
				}
				gs->allCards[k] = (Card*)malloc(sizeof(Card));
				gs->allCards[k]->color = colorToNumber(a);
				gs->allCards[k]->value = value;
				k++;
				if (colorToNumber(a) == 0) {
					gs->numberOfGreenCards++;
					gs->valueOfGreens = value;
				}
				else {
					gs->numberOfColorCards++;
				}
			}
		}
	}
	while (getchar() != EOF) {
		cin.unget();
		scanf_s("%d pile cards:", &gs->numberOfPiles);
		while (1) {
			do {
				getcharValue = getchar();
			} while (getcharValue == ' ' || getcharValue == '\t');
			if (getcharValue == '\n' || getcharValue == EOF) {
				break;
			}
			cin.unget();
			scanf_s("%d", &value);
			scanf_s("%9s", a, MAX_SIZE_COLOR_NAME);
			if (k != 0) {
				gs->allCards = (Card**)realloc(gs->allCards, sizeof(Card*) * (k + 1));
			}
			gs->allCards[k] = (Card*)malloc(sizeof(Card));
			gs->allCards[k]->color = colorToNumber(a);
			gs->allCards[k]->value = value;
			k++;
		}
	}
	gs->numberOfAllCards = k;
}

//Friday the 13th-5

void checkColorValues(GameStatus* gs) {
	loadAllCards(gs);
	gs->numberOfColors = gs->numberOfPiles;
	int* numberOfEachColorCard = new int[gs->numberOfColors];
	int* indexOfEachColorCardValue = new int[gs->numberOfColors];
	for (int i = 0; i < gs->numberOfColors; i++) {
		indexOfEachColorCardValue[i] = 0;
	}
	for (int i = 0; i < gs->numberOfColors; i++) {
		numberOfEachColorCard[i] = 0;
	}
	for (int i = 0; i < gs->numberOfAllCards; i++) {
		if (gs->allCards[i]->color > 0) {
			numberOfEachColorCard[gs->allCards[i]->color - 1]++;
		}
	}
	int** valuesOfEachColorCard = new int* [gs->numberOfColors];
	for (int i = 0; i < gs->numberOfColors; i++) {
		valuesOfEachColorCard[i] = new int[numberOfEachColorCard[i]];
	}
	for (int i = 0; i < gs->numberOfAllCards; i++) {
		if (gs->allCards[i]->color > 0) {
			valuesOfEachColorCard[gs->allCards[i]->color - 1][indexOfEachColorCardValue[gs->allCards[i]->color - 1]] =
				gs->allCards[i]->value;
			indexOfEachColorCardValue[gs->allCards[i]->color - 1] ++;
		}
	}
	for (int i = 0; i < gs->numberOfColors; i++) {
		qsort(valuesOfEachColorCard[i], numberOfEachColorCard[i], sizeof(int), compare);
	}
	int isNumberOfValuesEqual = 1;
	for (int i = 0; i < gs->numberOfColors - 1; i++) {
		if (numberOfEachColorCard[i] != numberOfEachColorCard[i + 1]) {
			isNumberOfValuesEqual = 0;
			break;
		}
	}
	if (!isNumberOfValuesEqual) {
		printf("The values of cards of all colors are not identical:\n");
		for (int i = 0; i < gs->numberOfColors; i++) {
			printColorName(i + 1);
			printf(" cards values: ");
			for (int j = 0; j < numberOfEachColorCard[i]; j++) {
				printf("%d ", valuesOfEachColorCard[i][j]);
			}
			printf("\n");
		}
	}
	else {
		int areValuesEqual = 1;
		for (int i = 0; i < gs->numberOfColors - 1; i++) {
			for (int j = 0; j < numberOfEachColorCard[i]; j++) {
				if (valuesOfEachColorCard[i][j] != valuesOfEachColorCard[i + 1][j]) {
					areValuesEqual = 0;
					break;
				}
			}
			if (!areValuesEqual) {
				break;
			}
		}
		if (!areValuesEqual) {
			printf("The values of cards of all colors are not identical:\n");
			for (int i = 0; i < gs->numberOfColors; i++) {
				printColorName(i + 1);
				printf(" cards values: ");
				for (int j = 0; j < numberOfEachColorCard[i]; j++) {
					printf("%d ", valuesOfEachColorCard[i][j]);
				}
				printf("\n");
			}
		}
		else {
			printf("The values of cards of all colors are identical:\n");
			for (int i = 0; i < numberOfEachColorCard[0]; i++) {
				printf("%d ", valuesOfEachColorCard[0][i]);
			}
		}
	}

	delete[] indexOfEachColorCardValue;
	delete[] numberOfEachColorCard;
}

//Friday the 13th-4b

void checkColorCards(GameStatus* gs) {
	scanf_s("active player = 1\nplayers number = %d\n", &gs->numberOfPlayers);
	int value, getcharValue, numberOfColorValues[7] = { 0, 0, 0, 0, 0, 0, 0 };
	char a[MAX_SIZE_COLOR_NAME];
	for (int i = 0; i < gs->numberOfPlayers; i++) {
		for (int j = 0; j < 2; j++) {
			if (j == 0) {
				scanf_s("%d player hand cards:", &value);
			}
			else {
				scanf_s("%d player deck cards:", &value);
			}
			while (1) {
				do {
					getcharValue = getchar();
				} while (getcharValue == ' ' || getcharValue == '\t');
				if (getcharValue == 10 || getcharValue == EOF) {
					break;
				}
				cin.unget();
				scanf_s("%d", &value);
				scanf_s("%9s", a, MAX_SIZE_COLOR_NAME);
				if (strcmp(a, "green") != 0) {
					numberOfColorValues[colorToNumber(a)]++;
				}				
			}
		}
	}
	while (getchar() != EOF) {
		cin.unget();
		scanf_s("%d pile cards:", &gs->numberOfPiles);
		while (1) {
			do {
				getcharValue = getchar();
			} while (getcharValue == ' ' || getcharValue == '\t');
			if (getcharValue == 10 || getcharValue == EOF) {
				break;
			}
			cin.unget();
			scanf_s("%d", &value);
			scanf_s("%9s", a, MAX_SIZE_COLOR_NAME);
			if (strcmp(a, "green") != 0) {
				numberOfColorValues[colorToNumber(a)]++;
			}
		}
	}
	if (isEqual(numberOfColorValues)) {
		printf("The number cards of all colors is equal: %d", numberOfColorValues[1]);
	}
	else {
		printf("At least two colors with a different number of cards were found:\n");
		for (int i = 1; i < 7; i++) {
			if (numberOfColorValues[i] != 0) {
				printColorName(i);
				printf(" cards are %d\n", numberOfColorValues[i]);
			}
		}
	}
}

//Friday the 13th-4a

void checkGreenCards(GameStatus* gs) {
	scanf_s("active player = 1\nplayers number = %d\n", &gs->numberOfPlayers);
	int x, getcharValue;
	char a[MAX_SIZE_COLOR_NAME];
	gs->numberOfGreenCards = 0;
	for (int i = 0; i < gs->numberOfPlayers; i++) {
		for (int j = 0; j < 2; j++) {
			if (j == 0) {
				scanf_s("%d player hand cards:", &x);
			}
			else {
				scanf_s("%d player deck cards:", &x);
			}
			while (1) {
				do {
					getcharValue = getchar();
				} while (getcharValue == ' ' || getcharValue == '\t');
				if (getcharValue == '\n' || getcharValue == EOF) {
					break;
				}
				cin.unget();
				scanf_s("%d", &x);
				scanf_s("%9s", a, MAX_SIZE_COLOR_NAME);
				if (strcmp(a, "green") == 0) {
					if (gs->numberOfGreenCards == 0) {
						gs->valueOfGreens = x;
						gs->numberOfGreenCards++;
					}
					else {
						if (x != gs->valueOfGreens) {
							printf("Different green cards values occurred");
							return;
						}
						else {
							gs->numberOfGreenCards++;
						}
					}
				}
			}
		}
	}
	while (getchar() != EOF) {
		cin.unget();
		scanf_s("%d pile cards:", &gs->numberOfPiles);
		while (1) {
			do {
				getcharValue = getchar();
			} while (getcharValue == ' ' || getcharValue == '\t');
			if (getcharValue == '\n' || getcharValue == EOF) {
				break;
			}
			cin.unget();
			scanf_s("%d", &x);
			scanf_s("%9s", a, MAX_SIZE_COLOR_NAME);
			if (strcmp(a, "green") == 0) {
				if (gs->numberOfGreenCards == 0) {
					gs->valueOfGreens = x;
					gs->numberOfGreenCards++;
				}
				else {
					if (x != gs->valueOfGreens) {
						printf("Different green cards values occurred");
						return;
					}
					else {
						gs->numberOfGreenCards++;
					}
				}
			}
		}
	}
	if (gs->numberOfGreenCards == 0) {
		printf("Green cards does not exist");
	}
	else {
		printf("Found %d green cards, all with %d value", gs->numberOfGreenCards, gs->valueOfGreens);
	}
}

void loadGameA(GameStatus* gs) {
	scanf_s("active player = 1\nplayers number = %d\n", &gs->numberOfPlayers);
	int x;
	char a[MAX_SIZE_COLOR_NAME];
	int getcharValue;
	gs->players = new Player* [gs->numberOfPlayers];
	for (int i = 0; i < gs->numberOfPlayers; i++) {
		gs->players[i] = new Player;
		gs->players[i]->numberOfCardsInHand = 0;
		gs->players[i]->numberOfCardsOnDeck = 0;
		for (int j = 0; j < 2; j++) {
			if (j == 0) {
				scanf_s("%d player hand cards:", &x);
			}
			else {
				scanf_s("%d player deck cards:", &x);
			}
			while (1) {
				do {
					getcharValue = getchar();
				} while (getcharValue == ' ' || getcharValue == '\t');
				if (getcharValue == '\n' || getcharValue == EOF) {
					break;
				}
				cin.unget();
				scanf_s("%d", &x);
				if (j == 0) {
					gs->players[i]->numberOfCardsInHand++;
				}
				else {
					gs->players[i]->numberOfCardsOnDeck++;
				}
				scanf_s("%9s", a, MAX_SIZE_COLOR_NAME);
			}
		}
	}
}

void loadGameB(GameStatus* gs) {
	loadGameA(gs);
	int getcharValue, x, i = 0;
	char a[MAX_SIZE_COLOR_NAME];

	gs->piles = new Pile* [MAX_NUMBER_OF_PILES];
	while (getchar() != EOF) {
		gs->piles[i] = new Pile;
		gs->piles[i]->numberOfCards = 0;
		cin.unget();
		scanf_s("%d pile cards:", &gs->numberOfPiles);
		while (1) {
			do {
				getcharValue = getchar();
			} while (getcharValue == ' ' || getcharValue == '\t');
			if (getcharValue == '\n' || getcharValue == EOF) {
				break;
			}
			cin.unget();
			scanf_s("%d", &x);
			gs->piles[i]->numberOfCards++;
			scanf_s("%9s", a, MAX_SIZE_COLOR_NAME);
		}
		i++;
	}
}

void generateDeck(GameStatus* gs) {
	scanf_s("%d %d %d %d", &gs->numberOfColors, &gs->numberOfGreenCards, &gs->valueOfGreens, &gs->numberOfColorValues );
	int numberOfAllCards = gs->numberOfColors * gs->numberOfColorValues + gs->numberOfGreenCards;
	Card* p = new Card[numberOfAllCards];
	gs->allCards = new Card * [numberOfAllCards];
	int* values = new int[gs->numberOfColorValues];
	for (int i = 0; i < gs->numberOfColorValues; i++) {
		scanf_s("%d", &values[i]);
	}
	int k = 0;
	for (int i = 0; i < gs->numberOfGreenCards; i++) {
		p->value = gs->valueOfGreens;
		p->color = 0;
		gs->allCards[k] = p;
		k++;
		p++;
	}
	for (int i = 0; i < gs->numberOfColors; i++) {
		for (int j = 0; j < gs->numberOfColorValues; j++) {
			p->value = values[j];
			p->color = i + 1;
			gs->allCards[k] = p;
			k++;
			p++;
		}
	}
	delete[] values;
}

void dealCards(GameStatus* gs) {
	scanf_s("%d ", &gs->numberOfPlayers);
	generateDeck(gs);
	int numberOfAllCards = gs->numberOfGreenCards + gs->numberOfColors * gs->numberOfColorValues;
	gs->players = new Player * [gs->numberOfPlayers];
	for (int i = 0; i < gs->numberOfPlayers; i++) {
		gs->players[i] = new Player;
		gs->players[i]->cardsInHand = new Card * [(numberOfAllCards / gs->numberOfPlayers) + 1];
		for (int j = 0; j < (numberOfAllCards / gs->numberOfPlayers) + 1; j++) {
			gs->players[i]->cardsInHand[j] = new Card;
		}
	}
	int k = 0;
	for (int i = 0; i < numberOfAllCards; i++) {
		gs->players[i % gs->numberOfPlayers]->cardsInHand[k] = gs->allCards[i];
		if (i % gs->numberOfPlayers == gs->numberOfPlayers - 1) {
			k++;
		}
	}
}

//Friday the 13th-1

void printDeck(GameStatus* gs) {
	generateDeck(gs);
	int k = 0;
	for (int i = 0; i < gs->numberOfGreenCards; i++) {
		printf_s("%d ", gs->allCards[k]->value);
		printColorName(0);
		printf_s(" ");
		k++;
	}
	for (int i = 0; i < gs->numberOfColors; i++) {
		for (int j = 0; j < gs->numberOfColorValues; j++) {
			printf_s("%d ", gs->allCards[k]->value);
			printColorName(i + 1);
			printf_s(" ");
			k++;
		}
	}
}

//Friday the 13th-2

void printDeal(GameStatus* gs) {
	dealCards(gs);
	int numberOfAllCards = gs->numberOfGreenCards + gs->numberOfColors * gs->numberOfColorValues;
	printf_s("active player = 1\nplayers number = %d\n", gs->numberOfPlayers);
	for (int i = 0; i < gs->numberOfPlayers; i++) {
		printf_s("%d player hand cards:", i + 1);
		for (int j = 0; j < numberOfAllCards / gs->numberOfPlayers + 1; j++) {
			if (gs->players[i]->cardsInHand[j]->value > 0) {
				printf_s(" %d ", gs->players[i]->cardsInHand[j]->value);
				printColorName(gs->players[i]->cardsInHand[j]->color);
			}
		}
		printf_s("\n%d player deck cards:\n", i + 1);
	}
	for (int i = 0; i < gs->numberOfColors; i++) {
		printf_s("%d pile cards:\n", i + 1);
	}

}

//Fiday the 13th-3a

void printLoadedGameA(GameStatus* gs) {
	for (int i = 0; i < gs->numberOfPlayers; i++) {
		printf("%d player has %d cards on hand\n", i + 1, gs->players[i]->numberOfCardsInHand);
		printf("%d player has %d cards in front of him\n", i + 1, gs->players[i]->numberOfCardsOnDeck);
	}
}

//Friday the 13th-3b

void printLoadedGameB(GameStatus* gs) {
	printLoadedGameA(gs);
	for (int i = 0; i < gs->numberOfPiles; i++) {
		printf("there are %d cards on %d pile\n", gs->piles[i]->numberOfCards, i + 1);
	}
}

//small functions commonly used

void printColorName(int colorNumber) {
	switch (colorNumber) {
	case 0:
		printf_s("green");
		break;
	case 1:
		printf_s("blue");
		break;
	case 2:
		printf_s("red");
		break;
	case 3:
		printf_s("violet");
		break;
	case 4:
		printf_s("yellow");
		break;
	case 5:
		printf_s("white");
		break;
	case 6:
		printf_s("black");
		break;
	}
}

int colorToNumber(char colorName[]) {
	if (strcmp(colorName, "green") == 0) {
		return 0;
	}
	else if (strcmp(colorName, "blue") == 0) {
		return 1;
	}
	else if (strcmp(colorName, "red") == 0) {
		return 2;
	}
	else if (strcmp(colorName, "violet") == 0) {
		return 3;
	}
	else if (strcmp(colorName, "yellow") == 0) {
		return 4;
	}
	else if (strcmp(colorName, "white") == 0) {
		return 5;
	}
	else {
		return 6;
	}
}

int isEqual(int tab[7]) {
	for (int i = 1; i < 6; i++) {
		if (tab[i] != tab[i + 1] && tab[i] != 0 && tab[i + 1] != 0) {
			return 0;
		}
	}
	return 1;
}

int compare(const void* a, const void* b) {
	int _a = *(int*)a;
	int _b = *(int*)b;
	if (_a < _b) return -1;
	else if (_a == _b) return 0;
	else return 1;
}

int main() {
	GameStatus gs;
	//printDeck(&gs);
	//printDeal(&gs);
	//loadGameA(&gs);
	//printLoadedGameA(&gs);
	//loadGameB(&gs);
	//printLoadedGameB(&gs);
	//checkGreenCards(&gs);
	//checkColorCards(&gs);
	//checkColorValues(&gs);
	//checkState(&gs);
	//easyMove(&gs);
	//cauldornExplosion(&gs);
	return 0;
}