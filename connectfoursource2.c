#include "connectfourheader.h"

int main(void) {
    welcomeScreen();
    playGame();
    return 0;
}

void welcomeScreen(void) {
    printf("  CCCC    OOOO    N   N   N   N  EEEE   CCCC   TTTTT   FFFFF   OOOO    U    U   RRRR\n");
    printf(" C    C  O    O   NN  N   NN  N  EE    C         T     F      O    O   U    U   R   R\n");
    printf(" C       O    O   N N N   N N N  EEEE  C         T     FFF    O    O   U    U   RRRR\n");
    printf(" C    C  O    O   N  NN   N  NN  EE    C         T     F      O    O   U    U   R R\n");
    printf("  CCCC    OOOO    N   N   N   N  EEEE   CCCC     T     F       OOOO     UUUU    R   R\n");
    printf("\n");
    printf("CONNECT FOUR GAME RULES:\n");
    printf("1. The board is 6 rows and 7 columns.\n");
    printf("2. The player with the yellow discs goes first.\n");
    printf("3. Players drop 1 disc in the grid at a time.\n");
    printf("4. Players alternate turns.\n");
    printf("5. Once a player has four discs in a row vertically, horizontally, or diagonally, they have won the game.\n");
}

void playGame(void) {
    struct Player yellow;
    struct Player red;
    char board[ROW][COL];
    int currentPlayer = YELLOW;
    int loop = FALSE;

    printf("Player Yellow, please enter your name: ");
    scanf("%s", yellow.playerName);
    yellow.playerNum = YELLOW;
    yellow.numDisc = DISC;
    yellow.playerChar = 'Y';

    printf("Player Red, please enter your name: ");
    scanf("%s", red.playerName);
    red.playerNum = RED;
    red.numDisc = DISC;
    red.playerChar = 'R';

    printf("%s and %s, let's play Connect Four!\n", yellow.playerName, red.playerName);

    initializeBoard(board);
    displayBoard(board); // initial display board

    while (!gameOver(board, yellow, red)) {
        if (currentPlayer == YELLOW) {
            makeMove(&yellow, board);
            currentPlayer = RED;
        } else if (currentPlayer == RED) {
            makeMove(&red, board);
            currentPlayer = YELLOW;
        }

        loop++;

        displayStats(yellow);
        displayStats(red);
        displayBoard(board); // board after each move
    }

    displayGameOver();
    displayStats(yellow);
    displayStats(red);
}

void initializeBoard(char board[ROW][COL]) {
    for (int row = 0; row < ROW; row++) {
        for (int col = 0; col < COL; col++) {
            board[row][col] = SPACE;
        }
    }
}

void displayBoard(char board[ROW][COL]) {
    printf("  A   B   C   D   E   F   G\n");
    printf("+---+---+---+---+---+---+---+\n");
    for (int row = 0; row < ROW; row++) {
        for (int col = 0; col < COL; col++) {
            printf("| %c ", board[row][col]);
        }
        printf("|\n+---+---+---+---+---+---+---+\n");
    }
}

void makeMove(struct Player *player, char board[ROW][COL]) {
    char move[TWO];
    int valid = FALSE;
    int colIndex;

    while (!valid) {
        printf("%s, enter your move (A-G): ", player->playerName);
        scanf("%s", move);

        int length = (int)strlen(move);

        if (length == ONE) {
            colIndex = getMoveCol(move);

            if (colIndex != INVALID && isColFull(move, board) == FALSE) {
                valid = TRUE;
            } else {
                printf("Invalid move. Please enter a valid and non-full column (A-G).\n");
            }
        } else {
            printf("Invalid move. Please enter a single character (A-G).\n");
        }
    }

    updateBoard(move, board, player);
}

void displayStats(struct Player player) {
    printf("*************** \%s\ Statistics ***************\n", player.playerName);
    printf("Player Number: %d\n", player.playerNum);
    printf("Player Character: %c\n", player.playerChar);
    printf("Remaining Disks: %d\n", player.numDisc);
}



int gameOver(char board[ROW][COL], struct Player yellow, struct Player red) {
    if (yellow.numDisc == 0 || red.numDisc == 0 || checkWin(board)) {
        return TRUE;
    }
    return FALSE;
}

int getMoveCol(char move[TWO]) {
    char colChar = toupper(move[0]);

    if (colChar >= 'A' && colChar <= 'G') {
        int colIndex = colChar - 'A';
        return colIndex;
    } else {
        return INVALID;
    }
}

int isColFull(char move[TWO], char board[ROW][COL]) {
    int colIndex = getMoveCol(move);

    for (int row = 0; row < ROW; row++) {
        if (board[row][colIndex] == SPACE) {
            return FALSE;  // not full
        }
    }

    return TRUE;  // is full
}

void updateBoard(char move[TWO], char board[ROW][COL], struct Player *player) {
    int colIndex = getMoveCol(move);

    for (int row = ROW - 1; row >= 0; row--) {
        if (board[row][colIndex] == SPACE) {
            board[row][colIndex] = player->playerChar;
            player->numDisc--;

            // update the board
            // checking win con
            break;
        }
    }
}

int checkWin(char board[ROW][COL]);

int checkHorizontal(char board[ROW][COL]) {
    for (int row = 0; row < ROW; row++) {
        for (int col = 0; col <= COL - FOUR; col++) {
            if (board[row][col] != SPACE &&
                board[row][col] == board[row][col + 1] &&
                board[row][col] == board[row][col + 2] &&
                board[row][col] == board[row][col + 3]) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

int checkVertical(char board[ROW][COL]) {
    for (int row = 0; row <= ROW - FOUR; row++) {
        for (int col = 0; col < COL; col++) {
            if (board[row][col] != SPACE &&
                board[row][col] == board[row + 1][col] &&
                board[row][col] == board[row + 2][col] &&
                board[row][col] == board[row + 3][col]) {
                return TRUE;
            }
        }
    }
    return FALSE;
}

int checkDiagonal(char board[ROW][COL]) {
    // top left bottom right
    for (int row = 0; row <= ROW - FOUR; row++) {
        for (int col = 0; col <= COL - FOUR; col++) {
            if (board[row][col] != SPACE &&
                board[row][col] == board[row + 1][col + 1] &&
                board[row][col] == board[row + 2][col + 2] &&
                board[row][col] == board[row + 3][col + 3]) {
                return TRUE;
            }
        }
    }

    // bottom left top right
    for (int row = ROW - 1; row >= THREE; row--) {
        for (int col = 0; col <= COL - FOUR; col++) {
            if (board[row][col] != SPACE &&
                board[row][col] == board[row - 1][col + 1] &&
                board[row][col] == board[row - 2][col + 2] &&
                board[row][col] == board[row - 3][col + 3]) {
                return TRUE;
            }
        }
    }

    return FALSE;
}

int checkWin(char board[ROW][COL]) {
    if (checkHorizontal(board) || checkVertical(board) || checkDiagonal(board)) {
        return TRUE;
    }
    return FALSE;
}

void displayGameOver(void) {
    printf("****************************************\n");
    printf("****                                ****\n");
    printf("****            GAME OVER!          ****\n");
    printf("****          CONNECT FOUR!         ****\n");
    printf("****                                ****\n");
    printf("****************************************\n");
}

