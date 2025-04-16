// Yağız Akkaya 2584597
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


#define BOARDSIZE 10
#define MAX_TRAP_VALUE 5



int rollDice() { // Roll a regular die
    return rand() % 6 + 1;
}

int decide_starter(){ //Decide who start first
    int computer,player,bigger=0;
    player=rollDice();
    computer=rollDice();
    printf("\nYou rolled the dice and got %d!\n", player);
    printf("Computer rolled the dice and got %d!\n", computer);
    while(computer==player){
        printf("Dices are equal!");
        player=rollDice();
        computer=rollDice();
        printf("\nYou rolled the dice and got %d!\n", player);
        printf("Computer rolled the dice and got %d!\n", computer);
    }
    if(player>computer){
        bigger=1;
        return bigger;
    }
    if(computer>player){
        bigger=2;
        return bigger;
    }
}

void initializeBoards(char board[BOARDSIZE][BOARDSIZE], char startingPoint) { // Initialize game boards
    for (int i = 0; i < BOARDSIZE; i++) {
        for (int j = 0; j < BOARDSIZE; j++) {
            board[i][j] = ' ';
        }
    }
    board[startingPoint == 'P' ? 0 : BOARDSIZE - 1][startingPoint == 'P' ? 0 : BOARDSIZE - 1] = startingPoint;
}

int checkTrapIndex(int row, int col) { // Possible trap indexes around the board

    int possible_Indexes[32][2] = {
            {0,0},{0,1},{0,2},{0,3},{0,4},{0,5},{0,6},{0,7},{0,8},{0,9},
            {1,9},{2,9},{3,9},{4,9},{5,9},{6,9},{7,9},{8,9},{9,9},
            {9,8},{9,7},{9,6},{9,5},{9,4},{9,3},{9,2},{9,1},{9,0},
            {8,0},{7,0},{6,0},{5,0},{4,0},{3,0},{2,0},{1,0}
    };

    for (int i = 0; i < 32; i++) {
        if (row == possible_Indexes[i][0] && col == possible_Indexes[i][1])
            return 1;
    }

    return 0;
}

void generateTrapIndex(int *row, int *col) { // Generate random trap index
    do {
        *row = rand() % BOARDSIZE;
        *col = rand() % BOARDSIZE;
    } while (!checkTrapIndex(*row, *col));
}


int generateTrapValue() { // Generate random trap value
    return rand() % MAX_TRAP_VALUE + 1;
}

void displayBoard(char playerBoard[BOARDSIZE][BOARDSIZE], char computerBoard[BOARDSIZE][BOARDSIZE],int beginner) { // Display the board for  player and computer
    if (beginner == 1) {
        printf("\n----Player Board----\n   ");
        for (int i = 0; i < BOARDSIZE; i++) {
            printf("%d ", i);
        }
        printf("\n");
        for (int i = 0; i < BOARDSIZE; i++) {
            printf("%d  ", i);
            for (int j = 0; j < BOARDSIZE; j++) {
                printf("%c ", playerBoard[i][j]);
            }
            printf("\n");
        }
        printf("\n----Computer Board----\n   ");
        for (int i = 0; i < BOARDSIZE; i++) {
            printf("%d ", i);
        }
        printf("\n");
        for (int i = 0; i < BOARDSIZE; i++) {
            printf("%d  ", i);
            for (int j = 0; j < BOARDSIZE; j++) {
                printf("%c ", computerBoard[i][j]);
            }
            printf("\n");
        }
    }

    if (beginner == 2) {
        printf("\n----Computer Board----\n   ");
        for (int i = 0; i < BOARDSIZE; i++) {
            printf("%d ", i);
        }
        printf("\n");
        for (int i = 0; i < BOARDSIZE; i++) {
            printf("%d  ", i);
            for (int j = 0; j < BOARDSIZE; j++) {
                printf("%c ", computerBoard[i][j]);
            }
            printf("\n");
        }
        printf("\n----Player Board----\n   ");
        for (int i = 0; i < BOARDSIZE; i++) {
            printf("%d ", i);
        }
        printf("\n");
        for (int i = 0; i < BOARDSIZE; i++) {
            printf("%d  ", i);
            for (int j = 0; j < BOARDSIZE; j++) {
                printf("%c ", playerBoard[i][j]);
            }
            printf("\n");
        }
    }
}

Step_Player(char board[BOARDSIZE][BOARDSIZE], int position[2], int diceRoll, int trapRow, int trapCol, int trapValue,char player){
    int stepsRemaining = diceRoll;
    int winner = 0;
    while (stepsRemaining > 0 && !winner) {
            if (position[0] == 0 && position[1] < BOARDSIZE - 1) {
                position[1]++;
            } else if (position[1] == BOARDSIZE - 1 && position[0] < BOARDSIZE - 1) {
                position[0]++;
            } else if (position[0] == BOARDSIZE - 1 && position[1] > 0) {
                position[1]--;
            } else if (position[1] == 0 && position[0] > 0) {
                position[0]--;
            }
        stepsRemaining--;

        if (position[0] == trapRow && position[1] == trapCol) {
            stepsRemaining -= trapValue;
            printf("Trapped at index %d %d! %d forward - %d backward = %d steps.\n", trapRow, trapCol, diceRoll, trapValue, diceRoll - trapValue);
            if (stepsRemaining < 0) {
                stepsRemaining = 0;
            }
        }

        if (!winner) {
            board[position[0]][position[1]] = player;
        }

        if (player == 'P' && position[0] == 0 && position[1] == 0) {
            winner = 1;
        }

    }
    return winner;
}
Step_computer(char board[BOARDSIZE][BOARDSIZE], int position[2], int diceRoll, int trapRow, int trapCol, int trapValue,char player){
    int stepsRemaining = diceRoll;
    int winner = 0;
    while (stepsRemaining > 0 && !winner) {
        if (position[0] == BOARDSIZE - 1 && position[1] > 0) {
            position[1]--;
        } else if (position[1] == 0 && position[0] > 0) {
            position[0]--;
        } else if (position[0] == 0 && position[1] < BOARDSIZE - 1) {
            position[1]++;
        } else if (position[1] == BOARDSIZE - 1 && position[0] < BOARDSIZE - 1) {
            position[0]++;
        }
        stepsRemaining--;

        if (position[0] == trapRow && position[1] == trapCol) {
            stepsRemaining -= trapValue;
            printf("Trapped at index %d %d! %d forward - %d backward = %d steps.\n", trapRow, trapCol, diceRoll, trapValue, diceRoll - trapValue);
            if (stepsRemaining < 0) {
                stepsRemaining = 0;
            }
        }

        if (!winner) {
            board[position[0]][position[1]] = player;
        }

        if (player == 'C' && position[0] == BOARDSIZE - 1 && position[1] == BOARDSIZE - 1) {
            winner = 1;
        }

    }
    return winner;

}


int main() {
    srand(time(NULL));
    char playAgain;

    do {
        int roundNumber = 1,beginner;
        char playerBoard[BOARDSIZE][BOARDSIZE], computerBoard[BOARDSIZE][BOARDSIZE];
        int player_TrapRow, player_TrapCol, Computer_TrapRow, Computer_TrapCol,Computer_TrapValue,player_TrapValue;;
        int player_Position[2] = {0, 0}, computerPosition[2] = {BOARDSIZE - 1, BOARDSIZE - 1};
        printf("Welcome to the Circle Game! :)\nLet^s get started!\n\n");
        initializeBoards(playerBoard, 'P');
        initializeBoards(computerBoard, 'C');
        printf("----Player----\n");
        int validInput = 0;
        while (!validInput) {
            printf("Enter trap index (row col):");
            if (scanf("%d %d", &player_TrapRow, &player_TrapCol) != 2) {
                printf("Error: Invalid input. Please enter two integers.\n");
                while (getchar() != '\n');
            } else if (!checkTrapIndex(player_TrapRow, player_TrapCol)) {
                printf("The trap index should be placed around the board.\n");
            } else {
                validInput = 1;
            }
        }

        player_TrapValue = generateTrapValue();
        printf("Generated trap value: %d\n", player_TrapValue);

        printf("----Computer----\n");
        generateTrapIndex(&Computer_TrapRow, &Computer_TrapCol);
        Computer_TrapValue = generateTrapValue();
        printf("Generated trap index (row col): %d %d\n", Computer_TrapRow, Computer_TrapCol);
        printf("Generated trap value: %d\n", Computer_TrapValue);
        beginner=decide_starter();
        printf("\n----Initial Boards----\n");
        displayBoard(playerBoard, computerBoard,beginner);
        while (1) {
            int playerDice, computerDice;
            printf("\n----Round %d----\n", roundNumber);
                playerDice = rollDice();
                computerDice = rollDice();
                printf("\nYou rolled the dice and got %d!\n", playerDice);
                printf("Computer rolled the dice and got %d!\n", computerDice);

            if (Step_Player(playerBoard, player_Position, playerDice, player_TrapRow, player_TrapCol, player_TrapValue, 'P')) {
                if (player_Position[0] == computerPosition[0] && player_Position[1] == computerPosition[1]) {
                    printf("It's a tie!\n");
                    break;
                }
                displayBoard(playerBoard, computerBoard,beginner);
                printf("You won!!!\n");
                break;
            }

            if (Step_computer(computerBoard, computerPosition, computerDice, Computer_TrapRow, Computer_TrapCol, Computer_TrapValue, 'C')) {
                if (player_Position[0] == computerPosition[0] && player_Position[1] == computerPosition[1]) {
                    printf("It's a tie!\n");
                    break;
                }
                displayBoard(playerBoard, computerBoard,beginner);
                printf("Computer won!!!\n");
                break;
            }
            displayBoard(playerBoard, computerBoard,beginner);
            roundNumber++;
        }
        printf("Would you like to play again (Y/N)? ");
        scanf(" %c", &playAgain);
    } while (playAgain == 'Y' || playAgain == 'y');

    printf("Byeeee!\n");
    return 0;
}



//I mistakenly wrote a single step function instead of two different functions, Step Player and Step Computer. Since there was little time left, I had to get some help from AI to fix it instead of starting the whole code from scratch.