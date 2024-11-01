#ifndef BATTLESHIPS_H
#define BATTLESHIPS_H

#define MAX_SHIPS 10
#define BOARD_SIZE 10

// empty square
#define EMPTY 0
#define MISS -1
#define HIT -2

// direction constants
#define UP 1
#define RIGHT 2
#define DOWN 3
#define LEFT 4

#define ALIVE 0
#define SUNK 1

struct ship {
    char name[20] ; // name of the ship, "Carrier", etc
    char symbol ;   // symbol on screen to represent ship
    int size ;      // length of this ship
    int x, y ;      // coordinates of the first square of the ship in LOGICAL coordinates (1-BOARDSIZE, NOT 0-BOARDSIZE-1)
    int direction ; // which direction the ship points
    int status ;    // 0 for alive, 1 for sunk
};

// board arrays are filled with either 0 for empty squares
// or the number corresponding to the ship that is there for non-empty squares

// the guesses arrays are filled with 0s for squares that haven't been guessed yet
// and 1s for squares that have been guessed already, whether empty or not

struct game {

    // the actual number of ships in the game for each player. Depensd on how many are read from ships.txt
    int numships ;

    struct ship p1ships[MAX_SHIPS] ;
    struct ship p2ships[MAX_SHIPS] ;

    // these arrays hold the board for each player, with all their ships on it. Not
    // STRICTLY necessary, as all of this information could be gained from the ships array of each player
    int p1board[BOARD_SIZE][BOARD_SIZE] ;
    int p2board[BOARD_SIZE][BOARD_SIZE] ;

    // these are two arrays that hold the GUESSES that each player has made so far.
    // They contain zero if that square hasn't been guessed, 1 for a miss, 2 for a hit.
    int p1guesses[BOARD_SIZE][BOARD_SIZE] ;
    int p2guesses[BOARD_SIZE][BOARD_SIZE] ;
    int turn ;
    int p1human ;
    int p2human ;
};

// clears the screen and displays a single message in the middle(ish). User must press enter to continue
int status_message ( char *message ) ;

int get_coordinates ( char *input, int *x, int *y ) ;

int clear_board ( int board[BOARD_SIZE][BOARD_SIZE] ) ;



// initiates the supplied structure with a new game, reading from the "ships.txt" file as necessary
// to get the relevant parameters for the game. Then asks players (or computer) to setup their ships in
// starting positions
int setup_game ( struct game *g ) ;

// places the 'n' ships in the supplied ship array on the supply board array.
// if comp = 0, the player will be asked to place them. If non-zero, the computer will place them randomly
int place_all_ships ( struct ship ships[MAX_SHIPS], int board[BOARD_SIZE][BOARD_SIZE], int n, int comp ) ;

// Places the SINGLE ship supplied onto the given board. Returns 1 if the ship can be placed successfully,
// or 0 if it either is out of bounds or hits another ship.
// If the ship is placed, the given number will be put in all positions on the board where the ship lies.
int place_ship ( int board[BOARD_SIZE][BOARD_SIZE], int xpos, int ypos, int size, int dir, int num ) ;

// draws the player's board, with all ships displayed.
int draw_player_board ( int board[BOARD_SIZE][BOARD_SIZE], struct ship ships[MAX_SHIPS], int numships ) ;

int draw_guess_board ( int board[BOARD_SIZE][BOARD_SIZE] ) ;

// plays the game until it is over (all ships sunk on one team)
int play_game ( struct game *g ) ;

// Returns 0 if neither player has yet won the game (all ships sunk), or 1/2 if player 1/2 has won, by sinking
// all of the opponents ships.
int game_over ( struct game *g ) ;

// checks if any ships have been sunk by the last shot. Does this by checking the board for each ship in
// the ships array. If all of that ships squares are HIT, but it was not previous marked as SUNK, then
// it is now marked as SUNK and it's ship number (1-MAX_SHIPS) is returned. If no ships has changed from
// ALIVE to SUNK, 0 is returned.
int check_sunk ( int board[BOARD_SIZE][BOARD_SIZE], struct ship ships[MAX_SHIPS], int numships ) ;


// clears the screen and displays a single message in the middle(ish). User must press enter to continue
int status_message_o ( char *message ) ;

int get_coordinates_o ( char *input, int *x, int *y ) ;

int clear_board_o ( int board[BOARD_SIZE][BOARD_SIZE] ) ;


// Supplied versions of these functions (in object file)
int setup_game_o ( struct game *g ) ;
int place_all_ships_o ( struct ship ships[MAX_SHIPS], int board[BOARD_SIZE][BOARD_SIZE], int n, int comp ) ;
int place_ship_o ( int board[BOARD_SIZE][BOARD_SIZE], int xpos, int ypos, int size, int dir, int num ) ;
int draw_player_board_o ( int board[BOARD_SIZE][BOARD_SIZE], struct ship ships[MAX_SHIPS], int numships ) ;
int draw_guess_board_o ( int board[BOARD_SIZE][BOARD_SIZE] ) ;
int play_game_o ( struct game *g ) ;
int game_over_o ( struct game *g ) ;
int check_sunk_o ( int board[BOARD_SIZE][BOARD_SIZE], struct ship ships[MAX_SHIPS], int numships ) ;
int check_sunk_o ( int board[BOARD_SIZE][BOARD_SIZE], struct ship ships[MAX_SHIPS], int numships ) ;

#endif // BATTLESHIPS_H
