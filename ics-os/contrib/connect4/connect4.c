/*
	CMSC 125: T-9L
	PANGILINAN, MOESHA DANE
	RUZ, JULIANNE MARIE

	CONNECT-FOUR
	FINAL PRESENTATION

*/

#include "../../sdk/dexsdk.h"
#include "../../sdk/time.h"


/* PROTOTYPES */
void mainMenu();
void getChoice(char *choice);
void startGame();
void initializeGrid();
void dropDisc(char player, int *noOfMoves);
void printGrid();
void checkGrid(char player, int *winner);
void aboutGame();
void instruction_panel();
void exitGame();

void printBoard();
void printDisc(int xCoord, int yCoord, int r, int c);
void erase(int x, int y, int w, int h);
void decorDisc(int x, int y, int color);
void borderDisc(int x, int y);
void fillDisc(int x, int y, int r, int c);


/* CONSTANTS*/
#define row 6
#define col 7
#define fullGrid 6*7
#define pattern 4

#define empty '0'
#define player1 '1'
#define player2 '2'
#define winningPattern '-'

#define reset 'r'
#define start 's'
#define exit 'x'
#define about 'a'
#define back 'b'
#define instruction 'i'

#define xPos 55 
#define yPos 15
#define YELLOW 54
#define RED 36
#define GRAY 56
#define WHITE 63
#define ROYAL_BLUE 1


/* GLOBAL VARIABLES */
char grid[row][col];
char input;


/* MAIN */
int main() {
	mainMenu();
	return 0;
}

/* FUNCTIONS */
void mainMenu(){
	char choice;
	set_graphics(VGA_320X200X256);
	do {
		erase(1,1,400,220);
		getChoice(&choice);
		if (choice==start){
			startGame();
		}else if (choice==about) {
			aboutGame();
		}else if (choice == exit) {
			exitGame();
		} else if (choice == instruction) {
			instruction_panel();
		} else {
			erase(1,1,400,220);
			write_text("Error: please make a",40,40,WHITE,0);
			write_text("valid choice.",40,80,WHITE,0);
			delay(50);
		}
	} while (choice != exit);
	set_graphics(VGA_TEXT80X25X16);
	clrscr();
}


void getChoice(char *choice) {
	decorDisc(220,40,YELLOW);
	write_text("CONNECT FOUR",110,40,WHITE,1);
	decorDisc(80,40,RED);
	write_text("[S] Start",40,130,WHITE,0);
	write_text("[X] Exit",160,130,WHITE,0);
	write_text("[A] About",40,160,WHITE,0); 
	write_text("[I] Instruction",160,160,WHITE,0);   
	*choice = getch();
}

void startGame() {
	int totalMoves = 0, movesP1 = 0, movesP2 = 0, winner = 0;
	/* Start Game */
	erase(1,1,400,220);
	initializeGrid();
	while(fullGrid != totalMoves || winner == 0){
		dropDisc(player1, &movesP1);
		checkGrid(player1, &winner);
		if (winner != 0) {
			printf("winner1\n");
			break;
		}
		dropDisc(player2, &movesP2);
		checkGrid(player2, &winner);
		if (winner != 0) {
			printf("winner2\n");
			break;
		}
		totalMoves=movesP1+movesP2;
		printf("Total moves: %d\n", totalMoves);
	}
	if(winner==0 && fullGrid == totalMoves) {
		printf("It's a tie!\n");
	}
}

void initializeGrid() {
	int i, j;
	for(i = 0; i < row; i++) {
		for(j = 0; j < col; j++) {
			grid[i][j]= empty;
		}
	}
}

void dropDisc(char player, int *noOfMoves){
	int repeat = 1, colIndex;
	char inputCol;
	int rowIndex = row - 1;
	char pString[20]="";
	char cString[20]="";
	char mString[20]="";
	char stringText[100]="";
	do{
		memset(&pString[0], 0, sizeof(pString));
		memset(&cString[0], 0, sizeof(cString));
		memset(&mString[0], 0, sizeof(mString));
		memset(&stringText[0], 0, sizeof(stringText));
		erase(1,1,400,220);
		printBoard();
		sprintf(pString,"%c",player);
		strcat(stringText, "Your turn, Player ");
		strcat(stringText, pString);
		strcat(stringText, ": ");
		write_text(stringText,55,170,WHITE,32);
		inputCol = (char)getch();
		if(inputCol==back){
			mainMenu();
		}else if(inputCol==reset){
			startGame();
		}else if(inputCol<=(48+col) && inputCol>48){
			inputCol = inputCol - 48;
			colIndex = inputCol - 1;
			do{
				if(grid[rowIndex][colIndex] == empty) {
					grid[rowIndex][colIndex] = player;
					printGrid();
					printBoard();
					delay(10);
					repeat = 0;
					break;
				}else if(grid[0][colIndex] != empty) {
					erase(1,1,400,220);
					sprintf(cString,"%d",inputCol);
					memset(&stringText[0], 0, sizeof(stringText));
						strcat(stringText, "ERROR: Player ");
						strcat(stringText, pString);
					write_text(stringText,40,10,WHITE,1);
					memset(&stringText[0], 0, sizeof(stringText));
						strcat(stringText, "Column ");
						strcat(stringText, cString);
						strcat(stringText, " is FULL!");
					write_text(stringText,40,30,WHITE,1);
					delay(50);
					printf("ERROR: Player %c, column %c is FULL.\n", player, inputCol);
					break;
				}else{
					rowIndex = rowIndex - 1;
				}
			}while(rowIndex>=0);
		}else{
			erase(1,1,400,220);
			sprintf(cString,"%d",inputCol);
			memset(&stringText[0], 0, sizeof(stringText));
				strcat(stringText, "ERROR: Player ");
				strcat(stringText, pString);
			write_text(stringText,40,10,WHITE,1);
			memset(&stringText[0], 0, sizeof(stringText));
				strcat(stringText, "INVALID input!");
			write_text(stringText,40,30,WHITE,1);
			delay(50);
			printf("ERROR: Player %c, column %c is OUT OF BOUNDS.\n", player, inputCol);
		}
	}while(repeat == 1);
	*noOfMoves=*noOfMoves+1;
	printf("NOTE: Player %c, number of moves: %i \n", player, *noOfMoves);		
}


void printGrid(){
	int i, j;
	for(i = 0; i < row; i++) {
		for(j = 0; j < col; j++) {
			printf("%c ", grid[i][j]);
		}
		printf("\n");
	}
}

void checkGrid(char player, int *winner){
	int i, j;

	/* VERTICAL */
	for(i = 0; i <= (row-pattern); i++) {
		for(j = 0; j < col; j++) {
			if (grid[i][j]==player && grid[i+1][j]==player && grid[i+2][j]==player && grid[i+3][j]==player) {
				printf("VERTICAL: ");
				printf("Player %c wins!\n", player);
				*winner = 1;	
			}
		}
	}

	/* HORIZONTAL -> - */
	for(i = 0; i < row; i++) {
		for(j = 0; j <= (col-pattern); j++) {
			if (grid[i][j]==player && grid[i][j+1]==player && grid[i][j+2]==player && grid[i][j+3]==player) {
				printf("HORIZONTAL: ");
				printf("Player %c wins!\n", player);	
				*winner = 1;
			}
		}
	}

	/* LEFT DIAGONAL -> \ */
	for(i = 0; i <= (row-pattern); i++) {
		for(j = 0; j <= (col-pattern); j++) {
			if (grid[i][j]==player && grid[i+1][j+1]==player && grid[i+2][j+2]==player && grid[i+3][j+3]==player) {
				printf("LEFT DIAGONAL ");
				printf("Player %c wins!\n", player);
				*winner = 1;
			}
		}
	}

	/* RIGHT DIAGONAL -> / */
	for(i = (row-pattern); i >= 0; i--) {
		for(j = (col-pattern); j >= 0; j--) {
			if (grid[i][j]==player && grid[i+1][j+1]==player && grid[i+2][j+2]==player && grid[i+3][j+3]==player) {
				printf("RIGHT DIAGONAL ");
				printf("Player %c wins!\n", player);
				*winner = 1;
			}
		}
	}
}

void aboutGame() {
	char goBack;
	erase(1,1,400,220);
	write_text("WELCOME TO CONNECT-X", 40, 40, WHITE, 1);
    write_text("This is also called Connect", 40, 70, WHITE, 20);
    write_text("Four. It's a connection game.", 40, 80, WHITE, 20);
  	write_text("The players choose their", 40, 90, WHITE, 20);
  	write_text("colors and take turns in", 40, 100, WHITE, 20);
  	write_text("placing discs on the grid.", 40, 110, WHITE, 20);
    write_text("The first one to form", 40, 120, WHITE, 20);
    write_text("a line of four discs wins.", 40, 130, WHITE, 20);
	write_text("GO BACK TO MAIN MENU [B]: ", 40, 160, WHITE, 20);
	goBack = (char)getch();
	if(goBack==back){
		erase(1,1,400,220);
	}else{
		printf("ERROR: Please enter a valid input.\n");
		aboutGame();
	}

}

void instruction_panel() {
	char goBack;
	erase(1,1,400,220);
	write_text("INSTRUCTIONS", 40, 40, WHITE, 1);
	write_text("Use the numbers to choose", 40, 70, WHITE, 20);
	write_text("which column to put your", 40, 80, WHITE, 20);
	write_text("disc in. Get four in a row", 40, 90, WHITE, 20);
	write_text("to win!", 40, 100, WHITE, 20);
	write_text("GO BACK TO MAIN MENU [B]: ", 40, 160, WHITE, 20);
	goBack = (char)getch();
	if (goBack == back) {
		erase(1,1,400,220);
	} else {
		printf("ERROR: Please enter a valid input.\n");
		instruction_panel();
	}
}

void exitGame() {
	printf("\nGOODBYE\n");
	write_text("GOODBYE",180,90,WHITE,0);
	delay(50);
}


void printBoard(){
	int i, j, xCoord, yCoord, iCoord;
	char number[20]="";	
	xCoord = xPos;
	yCoord = yPos;
	iCoord = xPos+1;

	for(i=0; i < row; i++, yCoord += 25){
		for(j=0; j < col; j++, xCoord += 30) {
			printDisc(xCoord, yCoord, i, j);
		}
		xCoord = xPos;
	}

	write_text("  1  2   3  4  5   6  7", 45, 5, WHITE, 32);
	write_text("[B] Back",55,180,WHITE,0);
	write_text("[R] Reset",159,180,WHITE,0);
}

void printDisc(int xCoord, int yCoord, int r, int c){ // prints a disc
	borderDisc(xCoord, yCoord);
	fillDisc(xCoord, yCoord, r, c);
}

void erase(int x, int y, int w, int h){ // covers area with black rectangle
	int i,j;
	for (i = y;i <= (y + h); i++) {
		for (j = x; j <= (x + w); j++) {
			write_pixel(j,i,100);
      	}
   	}
}

void decorDisc(int x, int y, int color){ // prints the start page decorative discs
	int i;
	for (i=9;i<14;i++)write_pixel(i+x,1+y,color);
	for (i=7;i<16;i++)write_pixel(i+x,2+y,color);
	for (i=5;i<18;i++)write_pixel(i+x,3+y,color);
	for (i=4;i<19;i++)write_pixel(i+x,4+y,color);
	for (i=3;i<20;i++)write_pixel(i+x,5+y,color);
	for (i=3;i<20;i++)write_pixel(i+x,6+y,color);
	for (i=2;i<21;i++)write_pixel(i+x,7+y,color);
	for (i=2;i<21;i++)write_pixel(i+x,8+y,color);
	for (i=1;i<22;i++)write_pixel(i+x,9+y,color);
	for (i=1;i<22;i++)write_pixel(i+x,10+y,color);
	for (i=1;i<22;i++)write_pixel(i+x,11+y,color);
	for (i=1;i<22;i++)write_pixel(i+x,12+y,color);
	for (i=1;i<22;i++)write_pixel(i+x,13+y,color);
	for (i=2;i<21;i++)write_pixel(i+x,14+y,color);
	for (i=2;i<21;i++)write_pixel(i+x,15+y,color);
	for (i=3;i<20;i++)write_pixel(i+x,16+y,color);
	for (i=3;i<20;i++)write_pixel(i+x,17+y,color);
	for (i=4;i<19;i++)write_pixel(i+x,18+y,color);
	for (i=5;i<18;i++)write_pixel(i+x,19+y,color);
	for (i=7;i<16;i++)write_pixel(i+x,20+y,color);
	for (i=9;i<14;i++)write_pixel(i+x,21+y,color);
}

void borderDisc(int x, int y){ // prints disc border
	int i;
	for (i=8;i<15;i++)write_pixel(i+x,0+y,56);
	for (i=6;i<17;i++)write_pixel(i+x,1+y,56);
	for (i=4;i<19;i++)write_pixel(i+x,2+y,56);
	for (i=3;i<20;i++)write_pixel(i+x,3+y,56);
	for (i=2;i<21;i++)write_pixel(i+x,4+y,56);
	for (i=2;i<21;i++)write_pixel(i+x,5+y,56);
	for (i=1;i<22;i++)write_pixel(i+x,6+y,56);
	for (i=1;i<22;i++)write_pixel(i+x,7+y,56);
	for (i=0;i<23;i++)write_pixel(i+x,8+y,56);
	for (i=0;i<23;i++)write_pixel(i+x,9+y,56);
	for (i=0;i<23;i++)write_pixel(i+x,10+y,56);
	for (i=0;i<23;i++)write_pixel(i+x,11+y,56);
	for (i=0;i<23;i++)write_pixel(i+x,12+y,56);
	for (i=0;i<23;i++)write_pixel(i+x,13+y,56);
	for (i=0;i<23;i++)write_pixel(i+x,14+y,56);
	for (i=1;i<22;i++)write_pixel(i+x,15+y,56);
	for (i=1;i<22;i++)write_pixel(i+x,16+y,56);
	for (i=2;i<21;i++)write_pixel(i+x,17+y,56);
	for (i=2;i<21;i++)write_pixel(i+x,18+y,56);
	for (i=3;i<20;i++)write_pixel(i+x,19+y,56);
	for (i=4;i<19;i++)write_pixel(i+x,20+y,56);
	for (i=6;i<17;i++)write_pixel(i+x,21+y,56);
	for (i=8;i<15;i++)write_pixel(i+x,22+y,56);
}

void fillDisc(int x, int y, int r, int c){ // updates disc color
	int i;
	int color;

	switch(grid[r][c]){ //sets the bulb's color
		case player1: color = YELLOW; break;
		case player2: color = RED; break;
		case empty: color = GRAY; break;
	}

	for (i=9;i<14;i++)write_pixel(i+x,1+y,color);
	for (i=7;i<16;i++)write_pixel(i+x,2+y,color);
	for (i=5;i<18;i++)write_pixel(i+x,3+y,color);
	for (i=4;i<19;i++)write_pixel(i+x,4+y,color);
	for (i=3;i<20;i++)write_pixel(i+x,5+y,color);
	for (i=3;i<20;i++)write_pixel(i+x,6+y,color);
	for (i=2;i<21;i++)write_pixel(i+x,7+y,color);
	for (i=2;i<21;i++)write_pixel(i+x,8+y,color);
	for (i=1;i<22;i++)write_pixel(i+x,9+y,color);
	for (i=1;i<22;i++)write_pixel(i+x,10+y,color);
	for (i=1;i<22;i++)write_pixel(i+x,11+y,color);
	for (i=1;i<22;i++)write_pixel(i+x,12+y,color);
	for (i=1;i<22;i++)write_pixel(i+x,13+y,color);
	for (i=2;i<21;i++)write_pixel(i+x,14+y,color);
	for (i=2;i<21;i++)write_pixel(i+x,15+y,color);
	for (i=3;i<20;i++)write_pixel(i+x,16+y,color);
	for (i=3;i<20;i++)write_pixel(i+x,17+y,color);
	for (i=4;i<19;i++)write_pixel(i+x,18+y,color);
	for (i=5;i<18;i++)write_pixel(i+x,19+y,color);
	for (i=7;i<16;i++)write_pixel(i+x,20+y,color);
	for (i=9;i<14;i++)write_pixel(i+x,21+y,color);
}
