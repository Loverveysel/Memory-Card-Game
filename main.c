#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void showCards(int cards[6][6],bool cardsAreKnown[6][6]);

int main() {
	int cards[6][6]; // It will hold the board.
	int numbers[36]; // It will hold the cards.
	int numbersSize =0;// for determining the numbers array size.
	time_t t; // In order to succesfully work rand() method.
  
	srand((unsigned) time(&t));
  //Fill the cards array. It includes 18 pairs numbers.
	for(int i = 0; i<6; i++) {
		for(int j = 0; j<6; j++) {
			int numMatch = 0;
			int number = rand() % 19 + 10;
			int z = 0;
			while(true) {
				if(number == numbers[z]) {
					numMatch++;
					if(numMatch == 2) {
						z = -1;
						number = rand() % 19 + 10;
						numMatch = 0;
					}
				}
				if(z == 36) {
					cards[i][j] = number;
					numbers[numbersSize] = number;
					numbersSize++;
					break;
				}
				z++;
			}
		}
	}

	bool cardsAreKnown[6][6];// Holds the which cards are opened and which are not opened.
	bool isItWon = false;
	bool validCard = false;

  //In the start, it makes all cards are not opened.
	for(int i = 0; i<6; i++) {
		for(int j = 0; j<6; j++) {
			cardsAreKnown[i][j] = false;
		}
	}
  
	int i1, j1;
	int i2, j2;

	int score = 0;
	int openedCardsCount = 0;

	printf("Score : %d\n\n", score);

  showCards(cards, cardsAreKnown);
	
  while(isItWon == false) {
    //Rows and cols input
		printf("Please Enter Your First Card's Row and Col : ");
	  scanf("%d %d", &i1, &j1);
		printf("Please Enter Your Second Card's Row and Col :  ");
		scanf("%d %d", &i2, &j2);
		printf("\n");

    //Check the inpt is valid or not valid
		if(i1>0&&i2>0&&i1<7&&i2<7&&j1>0&&j2>0&&j1<7&&j2<7&&(i1!=i2||j1!=j2)) {
			validCard = true;
		}

    //Check the inpt is valid or not valid
		if(cardsAreKnown[i1-1][j1-1] == true || cardsAreKnown[i2-1][j2-1] == true ||validCard == false) {
			printf("Invalid card. Please enter the valid card...\n\n");
		} else {
			validCard = false;

      //Shows the input
			cardsAreKnown[i1- 1][j1- 1] = true;
			cardsAreKnown[i2- 1][j2- 1] = true;

			showCards(cards,cardsAreKnown);

      //Checks the input was true or not
			if(cards[i1 - 1][j1- 1] == cards[i2- 1][j2- 1]) {
				cardsAreKnown[i1- 1][j1- 1] = true;
				cardsAreKnown[i2- 1][j2- 1] = true;
				score+=3;
			} else {
				cardsAreKnown[i1- 1][j1- 1] = false;
				cardsAreKnown[i2- 1][j2- 1] = false;
				score--;
			}

      //Checks the user is won or not
			openedCardsCount = 0;
			for(int i = 0; i<6; i++) {
				for(int j = 0; j<6; j++) {
					if(cardsAreKnown[i][j] == false) {
						continue;
					} else {
						openedCardsCount++;
					}
				}
			}
			if(openedCardsCount == 36) {
				printf("You won... Bravo!\n\n");
				printf("Score : %d", score);
				return 0;
			}
			printf("Score : %d\n\n", score);
		}
	}
}

//Printing the board
void showCards(int cards[6][6], bool cardsAreKnown[6][6]) {
	for(int i = 0; i<6; i++) {
		for(int j = 0; j<6; j++) {
			if(cardsAreKnown[i][j]) {
				printf("| %d |", cards[i][j]);
			} else {
				printf("| XX |");
			}
		}
		printf("\n\n");
	}
	printf("\n");
}
