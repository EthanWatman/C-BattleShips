#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "battleships.h"

int main(){ //Works
    // First declare all the necessary variables
    struct game g ; // the game

    status_message ( "Welcome to Battlship!\n\nPlayers will now take turns in placing their ships on the grid, and then\nthe battle will commence!\n") ;

    // create the game, and setup the board
    setup_game ( &g ) ;

    //now play the game!
    printf ( "Ready to play!\n" ) ;
    play_game ( &g ) ;
}

int get_coordinates ( char input[], int *x, int *y ){//Works

    char Letter;
    int Xinput, PosY, XCheck, YCheck;
    sscanf(input, "%c%d", &Letter, &Xinput);
    if(strlen(input) > 4){
        return (-1);
    }

    if(Letter == 'a' || Letter == 'b' || Letter == 'c' || Letter == 'd' || Letter == 'e' || Letter == 'f' || Letter == 'g' || Letter == 'h' || Letter == 'i' || Letter == 'j'){
        PosY = Letter - 96;
        YCheck = 1;
    }
    if(Letter == 'A' || Letter == 'B' || Letter == 'C' || Letter == 'D' || Letter == 'E' || Letter == 'F' || Letter == 'G' || Letter == 'H' || Letter == 'I' || Letter == 'J'){
        PosY = Letter - 64;
        YCheck = 1;
    }
    if(YCheck == 0){
        return(0);
    }
    if(Xinput <= 10 && Xinput > 0){
        XCheck = 1;
    }
    if(Xinput > 10 && Xinput <= 0){
        return (0);
    }
    if(XCheck == 1 && YCheck == 1){
        *y = PosY;
        *x = Xinput;
        return (1);
    }
    //return get_coordinates_o ( input, x, y ) ;
}

int clear_board ( int board[BOARD_SIZE][BOARD_SIZE]){//Works
    int i, j;

    // Loop through every element in the array and set to 0
    for(i = 0; i < BOARD_SIZE; i++){
        for(j = 0; j < BOARD_SIZE; j++){
            board[i][j] = EMPTY;
        }


    }
    return(0);
    //return clear_board_o ( board ) ;
}

int status_message ( char *message ){//Works

    char waiting_FOR_ENTER[1000];

    system("cls");

    printf("\n\n\n\n\n\n");
    printf("%s", message);
    printf("\n\n\n\n");

    printf("Press Enter to Continue");
    fgets(waiting_FOR_ENTER, 1000, stdin);
    printf("\n\n");
    //return status_message_o ( message ) ;
}

int draw_player_board ( int board[BOARD_SIZE][BOARD_SIZE], struct ship ships[MAX_SHIPS], int numships ){//Works

    int row, col;

    printf("    ");
    for(col = 0; col < BOARD_SIZE; col++){
        printf("%2d ", col+1);
    }
    printf("\n   +-------------------------------+\n");

    for (row = 0; row < BOARD_SIZE; row++){
        printf("%c  |", row+'A');

        for(col = 0; col < BOARD_SIZE; col ++){
            if(board[row][col] == EMPTY){
                printf("   ");
            }
            else if(board[row][col] == -2){
                printf(" X ");
            }
            else if(board[row][col] == -1){
                printf(" O ");
            }
            else if(board[row][col] <= numships){
                printf(" %c ", ships[board[row][col]-1].symbol);
            }

        }
        printf(" |");
            if (row == 0){
                printf("     Legend:");
            }
            if (row == 1){
                printf("     X: Hit");
            }
            if (row == 2){
                printf("     O: Miss");
            }
            else if (row < 8 && row > 2){
                printf("     %c: ", ships[row-3].symbol);
                printf(ships[row-3].name);
            }
        printf("\n");
    }
    printf("   +-------------------------------+\n");

    //return draw_player_board_o ( board, ships, numships ) ;
}

int draw_guess_board ( int board[BOARD_SIZE][BOARD_SIZE] ){ //Works

    int row, col;

    printf("    ");
    for(col = 0; col < BOARD_SIZE; col++){
        printf("%2d ", col+1);
    }
    printf("\n   +-------------------------------+\n");

    for (row = 0; row < BOARD_SIZE; row++){
        printf("%c  |", row+'A');

        for(col = 0; col < BOARD_SIZE; col ++){
            if(board[row][col] == EMPTY){
                printf("   ");
            }
            else{
                if(board[row][col] == HIT ){
                    printf(" X ");
                }
                else{
                    printf(" O ");
                }
            }
        }
        printf(" |");
            if (row == 0){
                printf("     Legend:");
            }
            if (row == 1){
                printf("     X: Hit");
            }
            if (row == 2){
                printf("     O: Miss");
            }
        printf("\n");
    }
    printf("   +-------------------------------+\n");

    //return draw_guess_board_o ( board ) ;
}

int place_ship ( int board[BOARD_SIZE][BOARD_SIZE], int xpos, int ypos, int size, int dir, int num ){//Works

    int x = xpos, y = ypos, i;

    for(i = 0; i < size; i++){
        if(x < 1 || x > BOARD_SIZE || y < 1 || y > BOARD_SIZE || board[y-1][x-1] != EMPTY){
            return 0;
        }

        if (dir == UP){
            y--;
        }
        if (dir == DOWN){
            y++;
        }
        if (dir == LEFT){
            x--;
        }
        else if (dir == RIGHT){
            x++;
        }
    }

    x = xpos;
    y = ypos;
    for(i = 0; i < size; i++){
        board[y-1][x-1] = num;
        if (dir == UP){
            y--;
        }
        if (dir == DOWN){
            y++;
        }
        if (dir == LEFT){
            x--;
        }
        else if (dir == RIGHT){
            x++;
        }
    }
    return 1;
    //return place_ship_o ( board, xpos, ypos, size, dir, num ) ;
}

int check_sunk ( int board[BOARD_SIZE][BOARD_SIZE], struct ship ships[MAX_SHIPS], int numships ){ //Works
    int i, j, shipHitCounter, x, y;

    for(i = 0; i < numships; i++){
        if(ships[i].status == ALIVE){
            shipHitCounter = 0;
            x = ships[i].x;
            y = ships[i].y;

            for(j = 0; j < ships[i].size; j++){
                if(board[y-1][x-1] == MISS){
                    return (0);
                }
                if(board[y-1][x-1] == HIT){
                    shipHitCounter++;
                }
                if (ships[j].direction == UP){
                    y--;
                }
                else if (ships[j].direction == DOWN){
                    y++;
                }
                else if (ships[j].direction == LEFT){
                    x--;
                }
                else if (ships[j].direction == RIGHT){
                    x++;
                }
            }
            printf("%d", shipHitCounter);
            printf("%d", ships[i].size);
            if(ships[i].size == shipHitCounter){
                ships[i].status = SUNK;
                return (i+1);
            }
        }
    }

    return (0);
    //return check_sunk_o ( board, ships, numships ) ;
}

int game_over ( struct game *g ){ //Works
    int i, p1SUNK = 0, p2SUNK = 0;

    for(i = 0; i < g->numships; i++){
        if(g-> p1ships[i].status == SUNK){
            p1SUNK++;
        }
        if(g-> p2ships[i].status == SUNK){
            p2SUNK++;
        }
    }

    if(p1SUNK == g->numships){
        return (2);
    }
    if(p2SUNK == g->numships){
        return (1);
    }
    else{
        return 0;
    }

    //return game_over_o ( g ) ;
}

int place_all_ships ( struct ship ships[MAX_SHIPS], int board[BOARD_SIZE][BOARD_SIZE], int numships, int comp ){ //Works

    int n = 0, v;
    char input[10], dir[10];
    int restart;
    char restartString[] = "restart\n";

    while( n < numships){
        system("cls");
        printf("Placing Ships\n\n");
        draw_player_board(board, ships, n);
        printf("Now placing the %s (size %d)\n", ships[n].name, ships[n].size);

        printf("Please enter coordinates for starting point of ship (eg D6) or \"restart\" to start over: ");
        fgets(input, sizeof(input), stdin);

        restart = strcmp(restartString, input);

        if(restart == 0){
            printf("Player Board Restart\n");
            n = 0;
            clear_board(board);
        }

        v = get_coordinates(input, &ships[n].x, &ships[n].y);
        if(v == 1){
            printf("Enter Direction: ");
            fgets(dir, 10, stdin);
            if(dir[0] == 'u' || dir[0] == 'U'){
                ships[n].direction = UP;
            }
            else if(dir[0] == 'r' || dir[0] == 'R'){
                ships[n].direction = RIGHT;
            }
            else if(dir[0] == 'd' || dir[0] == 'D'){
                ships[n].direction = DOWN;
            }
            else if(dir[0] == 'l' || dir[0] == 'L'){
                ships[n].direction = LEFT;
            }

            if (place_ship(board, ships[n].x, ships[n].y, ships[n].size, ships[n].direction, n + 1) == 1){
                printf("\n\nShip Placed\n\n");
                n++;
            }
            else{
                system("cls");
                printf("\n\nInValid, try again!\n\n");
            }
        }

    }
    //Enter direction of ship. (U)p, (D)own, (L)eft or (R)ight:
    // Note: comment out the line below once you have written your version.
    return (0);
    //return place_all_ships_o ( ships, board, numships, comp ) ;
}

int setup_game ( struct game *g ){ //Works

    FILE *infile;
    char symb;
    char shipname[20];
    char buffer[1000];
    int shipsize;


    infile = fopen("ships.txt", "r");
    if(infile == NULL){
        printf("Cannot open ships.txt file for reading");
        exit(-1);
    }

    g->numships = 0 ;

    while(g->numships < MAX_SHIPS && !feof (infile )){

        fgets( buffer, 1000, infile);
        printf("Read this line of text from file: %s", buffer);

        if ( sscanf (buffer, "%c %s %d", &symb, shipname, &shipsize) == 3 ){

            printf("Ship info: %c %s %d\n", symb, shipname, shipsize);
            g->p1ships[g->numships].symbol = symb;
            g->p1ships[g->numships].size = shipsize;
            strcpy ( g->p1ships[g->numships].name,  shipname ) ;
            g->p1ships[g->numships].status = ALIVE ;

            g->p2ships[g->numships].symbol = symb;
            strcpy ( g->p2ships[g->numships].name, shipname ) ;
            g->p2ships[g->numships].size = shipsize;
            g->p2ships[g->numships].status = ALIVE ;

            printf("Successfully read ship %d \n", g->numships);
            g->numships++;
        }
        else{
            printf("Invalid line in file, ignoring it: %s", buffer);
        }

    }

    if(g->numships == 0){
        exit(-1);
    }

    clear_board( g->p1board);
    clear_board( g->p1guesses);
    clear_board( g->p2board);
    clear_board( g->p2guesses);

    status_message("Player 1 will now place their ships.\nPlayer 2 no one likes you, thats why your second\n");
    place_all_ships( g->p1ships, g->p1board, g->numships, 0);
    status_message("Player 2 will now place their ships.\nPlayer 1 look away you legend\n");
    place_all_ships( g->p2ships, g->p2board, g->numships, 0);
    g->turn = 1;

    // Note: comment out the line below once you have written your version.
    //return setup_game_o ( g ) ;

}

int play_game ( struct game *g ){ //Works (Cant print ship name, random numbers due to check_sunk function)

    int winner, i;
    int x, y, shipsunk;
    int hit = 0;

    int swap = 0;
    int p1swap = 1, callSwap1 = 0;
    int p2swap = 1, callSwap2 = 0;
    char Letter, shipname[20];;
    int SwapInput;
    char swp[] = "swap\n";

    int windStrength = 0;
    int windDirSet = 0;
    char windDir = 'N';
    int ShotOffBoard = 0;

    char Buffer[1000];
    char waiting_FOR_ENTER[1000];
    char message[1000];
    int ValidCoords;

    g->turn = 1;

    int (*playerboard)[BOARD_SIZE];
    int (*opponentboard)[BOARD_SIZE];
    int (*playersguesses)[BOARD_SIZE];

    struct ships *playerships;
    struct ships *opponentships;
    printf("Game function called\n");


    while((winner = game_over(g)) == 0){
        hit = 0;
        //random wind strength
        windStrength = rand() % 4;
        if (windStrength == 3){
            windStrength = 0;
        }
        //random dir
        windDirSet = rand() % 4;
        if(windDirSet == 0){
            windDir = 'N';
        } else if (windDirSet == 1){
            windDir = 'E';
        } else if (windDirSet == 2){
            windDir = 'S';
        } else if (windDirSet == 3){
            windDir = 'W';
        }


        if( g->turn == 1 && swap == 0){
            printf("Turn player 1\n");
            playerboard = g->p1board;
            playersguesses = g->p1guesses;
            opponentboard = g->p2board;
            playerships = g->p1ships;
            opponentships = g->p2ships;
        } else if ( g->turn == 1 && swap == 0){
            playerboard = g->p2board;
            playersguesses = g->p2guesses;
            opponentboard = g->p1board;
            playerships = g->p2ships;
            opponentships = g->p1ships;
        }

        if( g->turn == 1 && swap == 1){
            playerboard = g->p2board;
            playersguesses = g->p2guesses;
            opponentboard = g->p1board;
            playerships = g->p2ships;
            opponentships = g->p1ships;
        } else if ( g->turn == 2 && swap == 1){
            playerboard = g->p1board;
            playersguesses = g->p1guesses;
            opponentboard = g->p2board;
            playerships = g->p1ships;
            opponentships = g->p2ships;
        } else if ( g->turn == 1 && swap == 0){
            playerboard = g->p1board;
            playersguesses = g->p1guesses;
            opponentboard = g->p2board;
            playerships = g->p1ships;
            opponentships = g->p2ships;
        } else if( g->turn == 2 && swap == 0){
            playerboard = g->p2board;
            playersguesses = g->p2guesses;
            opponentboard = g->p1board;
            playerships = g->p2ships;
            opponentships = g->p1ships;
        }

        system("cls");
        printf("Player %d, Your Ships Are:\n", g->turn);
        draw_player_board(playerboard, playerships, g->numships );
        printf("\nGuess Board: \n");
        draw_guess_board(playersguesses);
        if(g->turn == 1){
                printf("Player %d, please enter your target coordinate (eg A8) or swap boards (%d remaining) - Wind Strength %d, to the %c): ", g->turn, p1swap, windStrength, windDir);
                callSwap2 = 0;
                callSwap1 = 1;
        } else{
                printf("Player %d, please enter your target coordinate (eg A8) or swap boards (%d remaining) - Wind Strength %d, to the %c): ", g->turn, p2swap, windStrength, windDir);
                callSwap1 = 0;
                callSwap2 = 1;
        }

        fgets ( Buffer, 1000, stdin ) ;
        SwapInput = strcmp(Buffer, swp);
        if(SwapInput == 0){
            if(callSwap1 == 1 && p1swap > 0){
                if(swap == 0){
                    swap = 1;
                    system("cls");
                    printf("\n\nYou stole player %d board!\n\nNew board is as follows:\n\n", g->turn%2 + 1);
                    draw_player_board(opponentboard, playerships, g->numships );
                    printf("\n\nPress Enter to Continue");
                    fgets(waiting_FOR_ENTER, 1000, stdin);

                    system("cls");
                    printf("\n\nPlayer %d, please look away\n\n", g->turn);
                    printf("Press Enter to Continue");
                    fgets(waiting_FOR_ENTER, 1000, stdin);

                    system("cls");
                    printf("\n\nPlayer %d, your turn!\n\n", g->turn%2 + 1);
                    printf("Press Enter to Continue");
                    fgets(waiting_FOR_ENTER, 1000, stdin);
                    g->turn = g->turn%2 + 1;
                }
                else{
                    swap = 0;
                    system("cls");
                    printf("\n\nYou stole player %d board!\n\nNew board is as follows:\n\n", g->turn%2 + 1);
                    draw_player_board(playerboard, playerships, g->numships );
                    printf("\n\nPress Enter to Continue");
                    fgets(waiting_FOR_ENTER, 1000, stdin);

                    system("cls");
                    printf("\n\nPlayer %d, please look away\n\n", g->turn);
                    printf("Press Enter to Continue");
                    fgets(waiting_FOR_ENTER, 1000, stdin);

                    system("cls");
                    printf("\n\nPlayer %d, your turn!\n\n", g->turn%2 + 1);
                    printf("Press Enter to Continue");
                    fgets(waiting_FOR_ENTER, 1000, stdin);
                    g->turn = g->turn%2 + 1;
                }
                p1swap--;
            }
            else if(callSwap2 == 1 && p2swap > 0){
                if(swap == 0){
                    swap = 1;
                    system("cls");
                    printf("\n\nYou stole player %d board!\n\nNew board is as follows:\n\n", g->turn%2 + 1);
                    draw_player_board(playerboard, playerships, g->numships );
                    printf("\n\nPress Enter to Continue");
                    fgets(waiting_FOR_ENTER, 1000, stdin);

                    system("cls");
                    printf("\n\nPlayer %d, please look away\n\n", g->turn);
                    printf("Press Enter to Continue");
                    fgets(waiting_FOR_ENTER, 1000, stdin);

                    system("cls");
                    printf("\n\nPlayer %d, your turn!\n\n", g->turn%2 + 1);
                    printf("Press Enter to Continue");
                    fgets(waiting_FOR_ENTER, 1000, stdin);
                    g->turn = g->turn%2 + 1;
                }
                else{
                    swap = 0;
                    system("cls");
                    printf("\n\nYou stole player %d board!\n\nNew board is as follows:\n\n", g->turn%2 + 1);
                    draw_player_board(playerboard, playerships, g->numships );
                    printf("\n\nPress Enter to Continue");
                    fgets(waiting_FOR_ENTER, 1000, stdin);

                    system("cls");
                    printf("\n\nPlayer %d, please look away\n\n", g->turn);
                    printf("Press Enter to Continue");
                    fgets(waiting_FOR_ENTER, 1000, stdin);

                    system("cls");
                    printf("\n\nPlayer %d, your turn!\n\n", g->turn%2 + 1);
                    printf("Press Enter to Continue");
                    fgets(waiting_FOR_ENTER, 1000, stdin);
                    g->turn = g->turn%2 + 1;
                }
                p2swap--;
            }
            else{
                system("cls");
                printf("\n\nNo Swaps Left, Try Again!\n\n");

                printf("Press Enter to Continue");
                fgets(waiting_FOR_ENTER, 1000, stdin);
            }
        }
        if(SwapInput != 0){

            ValidCoords = get_coordinates ( Buffer, &x, &y ) ;
            x = x - 1;
            y = y - 1;
            if(windStrength == 0){
                printf("No Wind");
            }
            else if(windDir == 'N'){
                y = y - windStrength;
                if(y < 0){
                    printf("shot off board");
                    ShotOffBoard = 1;
                }
            }
            else if(windDir == 'E'){
                x = x + windStrength;
                if(x > BOARD_SIZE){
                    printf("shot off board");
                    ShotOffBoard = 1;
                }
            }
            else if(windDir == 'S'){
                y = y + windStrength;
                if(y > BOARD_SIZE){
                    printf("shot off board");
                    ShotOffBoard = 1;
                }
            }
            else if(windDir == 'W'){
                x = x - windStrength;
                if(x < 0){
                    printf("shot off board");
                    ShotOffBoard = 1;
                }
            }
            if(ShotOffBoard == 1){
                system("cls");
                printf("\n\nYou missed!\n\nShot wasnt even on board, remember to account for wind!!\n\n");
                printf("Press Enter to Continue");
                fgets(waiting_FOR_ENTER, 1000, stdin);

                if (winner == 0){
                    system("cls");
                    printf("\n\nPlayer %d, please look away\n\n", g->turn);
                    printf("Press Enter to Continue");
                    fgets(waiting_FOR_ENTER, 1000, stdin);

                    system("cls");
                    printf("\n\nPlayer %d, your turn!\n\n", g->turn%2 + 1);
                    printf("Press Enter to Continue");
                    fgets(waiting_FOR_ENTER, 1000, stdin);
                    g->turn = g->turn%2 + 1;
                }
            }
            else if(ValidCoords == 1 && ShotOffBoard == 0){
                system("cls");
                if(opponentboard[y][x] == EMPTY){
                    playersguesses[y][x] = MISS;
                    opponentboard[y][x] = MISS;
                    system("cls");
                    printf("\n\nYou missed!\n\n");
                    printf("Press Enter to Continue");
                    fgets(waiting_FOR_ENTER, 1000, stdin);
                }
                else{
                    system("cls");
                    printf("\n\nHIT!\nYou hit their ship\n");
                    opponentboard[y][x] = HIT;
                    playersguesses[y][x] = HIT;

                    hit = 1;

                    shipsunk = check_sunk(opponentboard, opponentships, g->numships );
                    if ( shipsunk != 0){
                        if(g->turn == 1){
                            strcpy ( g->p2ships[shipsunk-1].name,  shipname ) ;
                        } else{
                            strcpy ( g->p1ships[shipsunk-1].name,  shipname ) ;
                        }

                        printf("\nYou sunk opponents ship!\n");
                    }
                    printf("\nPress Enter to Continue");
                    fgets(waiting_FOR_ENTER, 1000, stdin);
                }
                if (winner == 0){
                    system("cls");
                    printf("\n\nPlayer %d, please look away\n\n", g->turn);
                    printf("Press Enter to Continue");
                    fgets(waiting_FOR_ENTER, 1000, stdin);

                    system("cls");
                    printf("\n\nPlayer %d, your turn!\n\n", g->turn%2 + 1);
                    if(hit = 1){
                        printf("Oponent hit your ship, now is your time for revenge!\n\n");
                        hit = 0;
                    }
                    printf("Press Enter to Continue");
                    fgets(waiting_FOR_ENTER, 1000, stdin);
                    g->turn = g->turn%2 + 1;
                }
            }
            else{
                system("cls");
                printf("\n\nInvalid Position, Try again\n");
                printf("Press Enter to Continue");
                fgets(waiting_FOR_ENTER, 1000, stdin);
            }
        }
    }

    if( winner == 1){
        printf("\n\nPlayer 1 Wins");
    }
    else if (winner == 2){
        printf("\n\nPlayer 2 Wins");
    }
    else{
        printf("\n\nNobody Wins");
    }

    // Note: comment out the line below once you have written your version.
    //return play_game_o ( g  ) ;

}
