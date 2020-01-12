/*
Requires ncurses library, install with: sudo apt-get install libncurses5-dev libncursesw5-dev

Compile with: gcc -o game.out adventure.c -lncurses
Run with: gnome-terminal --geometry=82x21 -e ./game.out
Or Size terminal to 82x21 or greater and then run program

Instructions:
		You have been trapped in a mysterious dungeon by an evil wizard,
		But he has accidentaly left the keys required to escape somewhere in the dungeon.
		Find your way through the mazes and secret passageways to collect all the keys and escape.

	The purpose of the game is to gather each key in order to unlock it's corresponding gate.

	The blue gate requires two seperate keys from rooms 4 and 5 to open completely

	
	Level Layout:

	|---|				|---|
	| 5 |				| 4 |
	|---|				|---|
	  |					  |
	  |					  |
	|---|     |---|     |---|
	| 2 | --- | 1 | --- | 3 |
	|---|     |---|     |---|
				|
				|
			  |---|
			  | 6 |
			  |---|

	Secret Teleporting locations(@ symbol):

	Level 2 - Green Gate Room:

 ######################################===########################################
 #                                        #                             #      #
 #                                        #                             #      #
 #                                        #       #######     #         #      #
 #                                        #       #    @#     #     #####      #
 #        #         #######################       #     #     #     #          #
 #        #                                       #     #     #     #          #
 #        #########################################     #######     #   ########
 #        #                                             #@    #     #   #
 #        #                                             #    %#     #   # 
 #        #         ###########################################     #   #
 #        #                                                         #   #      #
 #        #                                                         #   #      #
 #        #                     ###############################     #   #      #
 #        #                                                   #     #   #      #
 #        #                                                   #     #   #      #
 #        #####################################################     #   #      #
 #                            #                                                #
 #                            #                                                #
 ################################################################################

	Level 3 - Red Gate Room:

 ######################################===########################################
 #                                        #                             #@     #
 #                                        #                             #      #
 #                                        #       #######     #         #     %#
 #                                        #       #     #     #     ############
 #        #         #######################       #     #     #     #          #
 #        #                                       #     #     #     #          #
 #        #########################################     #######     #   ########
          #                   #                         #     #     #   #      #
          #                   #                         #     #     #   #      #
          #         ###########################################     #   #      #
 #        #                   #                                     #   #      #
 #        #                   #                                     #   #      #
 #        #                   # ###############################     #   #      #
 #        #                   #                               #     #   #      #
 #        #                                                   #     #   #      #
 #        #####################################################     #   #      #
 #                            #@                                               #
 #                            #                                                #
 ################################################################################

*/

#include <unistd.h>
#include <stdio.h>
#include <ncurses.h>

#define PLAYER '!'
#define EMPTY ' '
#define WALL '#'
#define Gate '='
#define Key '%'
#define EMPTY_PAIR 1
#define PLAYER_PAIR 2
#define WALL_PAIR 3
#define GreenGate_PAIR 4
#define RedGate_PAIR 5
#define RedKey_PAIR 6
#define GreenKey_PAIR 7
#define BlueKey_PAIR 8
#define BlueGate_PAIR 9

int CharacterY = 10; //Current character Y postition
int CharacterX = 40; //Current character X postition 
int Current_Level = 0; //The level the player is currently on
int HasRedKey = 0; //Red key flag
int HasGreenKey = 1; //Green key flag
int HasBlueKeyOne = 0; //Blue key one flag
int HasBlueKeyTwo = 0; //Blue key two flag
int GameOver = 0;

void Level_1(){
	attron(COLOR_PAIR(WALL_PAIR));
	int y, x;
	Current_Level = 1;
	
	//BASIC STRUCTURE
	//Top Wall
	mvhline(1, 1, WALL, 80);
	
	//Bottom Wall
	mvhline(20, 1, WALL, 38);
	mvhline(20, 42, WALL, 80);

	//Left Wall
	mvvline(1, 1, WALL, 8);
	mvvline(12, 1, WALL, 8);

	//Right Wall
	mvvline(1, 79, WALL, 8);
	mvvline(12, 79, WALL, 8);

	attroff(COLOR_PAIR(WALL_PAIR));

	//Blue Gates
	if (HasBlueKeyOne == 0){ //First Gate
		attron(COLOR_PAIR(BlueGate_PAIR));
		mvhline(19, 39, Gate, 3);
		attroff(COLOR_PAIR(BlueGate_PAIR));
	}

	if (HasBlueKeyTwo == 0){ //Second Gate
		attron(COLOR_PAIR(BlueGate_PAIR));
		mvhline(20, 39, Gate, 3);
		attroff(COLOR_PAIR(BlueGate_PAIR));
	}

}

void Level_2(){
	int y, x;
	Current_Level = 2;

	//Draws green gate when user doesn't have key 
	if (HasGreenKey == 0){
		attron(COLOR_PAIR(GreenGate_PAIR));
		mvhline(1, 39, Gate, 3);
		attroff(COLOR_PAIR(GreenGate_PAIR));
	}

	attron(COLOR_PAIR(WALL_PAIR));
	//Top Wall
	mvhline(1, 1, WALL, 38);
	mvhline(1, 42, WALL, 80);
	
	//Bottom Wall
	mvhline(20, 1, WALL, 80);

	//Left Wall
	mvvline(1, 1, WALL, 20);

	//Right Wall
	mvvline(1, 79, WALL, 8);
	mvvline(12, 79, WALL, 8);

	//Maze
	mvhline(8, 72, WALL, 7); //1
	mvvline(8, 72, WALL, 10); //2
	mvvline(6, 68, WALL, 12); //3
	mvvline(2, 72, WALL, 4); //4
	mvhline(5, 68, WALL, 4); //5
	mvvline(14, 62, WALL, 4); //6
	mvhline(17, 10, WALL, 53); //7
	mvhline(14, 32, WALL, 30); //8
	mvhline(11, 20, WALL, 43); //9
	mvvline(17, 30, WALL, 3); //10
	mvvline(4, 62, WALL, 7); //11
	mvvline(6, 10, WALL, 11); //12
	mvhline(6, 20, WALL, 22); //15
	mvvline(2, 42, WALL, 5); //16
	mvhline(8, 10, WALL, 40); //17
	mvvline(4, 50, WALL, 5); //18
	mvvline(4, 56, WALL, 8); //19
	mvhline(8, 56, WALL, 7); //20
	mvhline(4, 50, WALL, 6); //21
	
	attroff(COLOR_PAIR(WALL_PAIR));

	//Print Red key
	if (HasRedKey == 0){
		attron(COLOR_PAIR(RedKey_PAIR));
		mvhline(10, 61, Key, 1);
		attroff(COLOR_PAIR(RedKey_PAIR));
	}
	
}

void Level_3(){
	int y, x;
	Current_Level = 3;

	//Draws red gate when user doesn't have key 
	if (HasRedKey == 0){
		attron(COLOR_PAIR(RedGate_PAIR));
		mvhline(1, 39, Gate, 3);
		attroff(COLOR_PAIR(RedGate_PAIR));
	}

	//Start wall colour
	attron(COLOR_PAIR(WALL_PAIR));

	//Top Wall
	mvhline(1, 1, WALL, 38);
	mvhline(1, 42, WALL, 80);
	
	//Bottom Wall 
	mvhline(20, 1, WALL, 80);

	//Left Wall
	mvvline(1, 1, WALL, 8);
	mvvline(12, 1, WALL, 8);

	//Right Wall
	mvvline(1, 79, WALL, 20);
	
	//Maze
	mvvline(8, 30, WALL, 8);

	//Maze
	mvhline(8, 72, WALL, 7); //1
	mvvline(8, 72, WALL, 10); //2
	mvvline(6, 68, WALL, 12); //3
	mvvline(2, 72, WALL, 4); //4
	mvhline(5, 68, WALL, 4); //5
	mvvline(14, 62, WALL, 4); //6
	mvhline(17, 10, WALL, 53); //7
	mvhline(14, 32, WALL, 30); //8
	mvhline(11, 20, WALL, 43); //9
	mvvline(17, 30, WALL, 3); //10
	mvvline(4, 62, WALL, 7); //11
	mvvline(6, 10, WALL, 11); //12
	mvhline(6, 20, WALL, 22); //15
	mvvline(2, 42, WALL, 5); //16
	mvhline(8, 10, WALL, 40); //17
	mvvline(4, 50, WALL, 5); //18
	mvvline(4, 56, WALL, 8); //19
	mvhline(8, 56, WALL, 7); //20
	mvhline(4, 50, WALL, 6); //21

	mvhline(5,72, WALL, 7); //Line forming box fromm line 4

	attroff(COLOR_PAIR(WALL_PAIR)); //Stop wall colour

	//Print Green key
	if (HasGreenKey == 0){
		attron(COLOR_PAIR(GreenKey_PAIR));
		mvhline(4, 78, Key, 1);
		attroff(COLOR_PAIR(RedKey_PAIR));
	}
}

void Level_4(){
	Current_Level = 4;
	attron(COLOR_PAIR(WALL_PAIR));

	//Top Wall
	mvhline(1, 1, WALL, 80);
	
	//Bottom Wall
	mvhline(20, 1, WALL, 38);
	mvhline(20, 42, WALL, 80);

	//Left Wall
	mvvline(1, 1, WALL, 20);

	//Right Wall
	mvvline(1, 79, WALL, 20);
	
	//Maze
	mvhline(8, 72, WALL, 7); //1
	mvvline(8, 72, WALL, 10); //2
	mvvline(6, 68, WALL, 12); //3
	mvvline(2, 72, WALL, 4); //4
	mvhline(5, 68, WALL, 4); //5
	mvvline(14, 62, WALL, 4); //6
	mvhline(17, 10, WALL, 53); //7
	mvhline(14, 32, WALL, 30); //8
	mvhline(11, 20, WALL, 43); //9
	mvvline(17, 43, WALL, 3); //10
	mvvline(4, 62, WALL, 7); //11
	mvvline(6, 10, WALL, 11); //12
	mvhline(6, 20, WALL, 22); //15
	mvvline(2, 42, WALL, 5); //16
	mvhline(8, 10, WALL, 40); //17
	mvvline(4, 50, WALL, 5); //18
	mvvline(4, 56, WALL, 8); //19
	mvhline(8, 56, WALL, 7); //20
	mvhline(4, 50, WALL, 6); //21

	attroff(COLOR_PAIR(WALL_PAIR));

	//Print blue key one
	if (HasBlueKeyOne == 0){
		attron(COLOR_PAIR(BlueKey_PAIR));
		mvhline(9, 73, Key, 1);
		attroff(COLOR_PAIR(BlueKey_PAIR));
	}
}

void Level_5(){
	Current_Level = 5;
	attron(COLOR_PAIR(WALL_PAIR));

	//Top Wall
	mvhline(1, 1, WALL, 80);
	
	//Bottom Wall
	mvhline(20, 1, WALL, 38);
	mvhline(20, 42, WALL, 80);

	//Left Wall
	mvvline(1, 1, WALL, 20);

	//Right Wall
	mvvline(1, 79, WALL, 20);

	//Maze
	mvhline(8, 72, WALL, 7); //1
	mvvline(8, 72, WALL, 10); //2
	mvvline(6, 68, WALL, 12); //3
	mvvline(2, 72, WALL, 4); //4
	mvhline(5, 68, WALL, 4); //5
	mvvline(14, 62, WALL, 4); //6
	mvhline(17, 10, WALL, 53); //7
	mvhline(14, 32, WALL, 30); //8
	mvhline(11, 20, WALL, 43); //9
	mvvline(17, 30, WALL, 3); //10
	mvvline(4, 62, WALL, 7); //11
	mvvline(6, 10, WALL, 11); //12
	mvhline(6, 20, WALL, 22); //15
	mvvline(2, 42, WALL, 5); //16
	mvhline(8, 10, WALL, 40); //17
	mvvline(4, 50, WALL, 5); //18
	mvvline(4, 56, WALL, 8); //19
	mvhline(8, 56, WALL, 7); //20
	mvhline(4, 50, WALL, 6); //21
	
	attroff(COLOR_PAIR(WALL_PAIR));

	//Print blue key two
	if (HasBlueKeyTwo == 0){
		attron(COLOR_PAIR(BlueKey_PAIR));
		mvhline(5, 40, Key, 1);
		attroff(COLOR_PAIR(BlueKey_PAIR));
	}
}

void Level_6(){
	//you win
	mvaddstr(10,38, "WINNER");
	refresh();
}

void Level_Selector(int side){
	if (Current_Level == 0){
		Level_1();
	} 
	if (Current_Level == 1){ //Level 1 -> 2
		if (side == 4){
			erase();
			Level_2();
			CharacterY = 10;
			CharacterX = 78;
		}
	}

	if (Current_Level == 1){ //Level 1 -> 3
		if (side == 2){
			erase();
			Level_3();
			CharacterY = 10;
			CharacterX = 2;
		}
	}

	if (Current_Level == 3){ //Level 3 -> 1
		if (side == 4){
			erase();
			Level_1();
			CharacterY = 10;
			CharacterX = 78;
		}
	}

	if (Current_Level == 2){ //Level 2 -> 1
		if (side == 2){
			erase();
			Level_1();
			CharacterY = 10;
			CharacterX = 2;
		}
	}

	if (Current_Level == 3){ //Level 3 -> 4
		if (side == 1){
			erase();
			Level_4();
			CharacterY = 19;
			CharacterX = 40;
		}
	}

	if (Current_Level == 4){ //Level 4 -> 3
		if (side == 3){
			erase();
			Level_3();
			CharacterY = 2;
			CharacterX = 40;
		}
	}

	if (Current_Level == 2){ //Level 2 -> 5 
		if (side ==  1){
			erase();
			Level_5();
			CharacterY = 19;
			CharacterX = 40;
		}
	}

	if (Current_Level == 5){ //Level 5 -> 2
		if (side == 3){
			erase();
			Level_2();
			CharacterY = 2;
			CharacterX = 40;
		}
	}

	if (Current_Level == 1) {
		if (side == 3){
			GameOver = 1;
			erase();
			Level_6();
			CharacterY = 10;
			CharacterX = 40;
		}
	}
}

void Boundary_Checker(){
	if (CharacterX == 1){ //Check Left side
		Level_Selector(4);
	} 
	if (CharacterX == 79){
		Level_Selector(2); //Check Right Side
	}
	if (CharacterY == 1){ //Check Top side
		Level_Selector(1);
	} 
	if (CharacterY == 20){ //Check Bottom side
		Level_Selector(3);
	} 

	//SPECIAL DETECTIONS:
	
	//Level 2 Red Key Room:
	if ((Current_Level == 2) && (CharacterY == 5) && (CharacterX == 55)){ //Outside -> Red Room
		CharacterX = 57;
		CharacterY = 10;
	}
	if ((Current_Level == 2) && (CharacterY == 9) && (CharacterX == 57)){ //Red Room -> Outside
		CharacterX = 54;
		CharacterY = 5;
	}
	if ((Current_Level == 2) && (CharacterY == 10) && (CharacterX == 61)){ //If user is on red key coords
		HasRedKey = 1;
	}

	//Level 3 Green Key Room:
	if ((Current_Level == 3) && (CharacterY == 18) && (CharacterX == 31)){ //Outside -> Red Room
		CharacterX = 73;
		CharacterY = 4;
	}
	if ((Current_Level == 3) && (CharacterY == 2) && (CharacterX == 73)){ //Red Room -> Outside
		CharacterX = 31;
		CharacterY = 19;
	}
	if ((Current_Level == 3) && (CharacterY == 4) && (CharacterX == 78)){ //If user is on green key coords
		HasGreenKey = 1;
	}

	//Level 4 Blue Key One Detection
	if ((Current_Level == 4) && (CharacterY == 9) && (CharacterX == 73)){
		HasBlueKeyOne = 1;
	}

	//Level 5 Blue Key Two Detection
	if ((Current_Level == 5) && (CharacterY == 5) && (CharacterX == 40)){
		HasBlueKeyTwo = 1;
	}
}

int move_okay(int y, int x){ //Using code from here: https://www.zcfy.cc/article/creating-an-adventure-game-in-the-terminal-with-ncurses
    int testch;

    //return true if the space is okay to move into

    testch = mvinch(y, x);
    return (((testch & A_CHARTEXT) == Key) || ((testch & A_CHARTEXT) == EMPTY));
}

int main(){
	printf("\\");
	int ch;
	
	initscr();			/* Start curses mode 		  */

	cbreak();
	noecho();
	keypad(stdscr, TRUE);	//Allows keypad presses to be detected

	Level_Selector(0);

	
	start_color(); //Initialise All colour stuff
	init_pair(PLAYER_PAIR, COLOR_YELLOW, COLOR_BLACK);
	init_pair(WALL_PAIR, COLOR_WHITE, COLOR_BLACK);
	init_pair(GreenGate_PAIR, COLOR_YELLOW, COLOR_GREEN);
	init_pair(RedGate_PAIR, COLOR_YELLOW, COLOR_RED);
	init_pair(RedKey_PAIR, COLOR_YELLOW, COLOR_RED);
	init_pair(GreenKey_PAIR, COLOR_YELLOW, COLOR_GREEN);
	init_pair(BlueGate_PAIR, COLOR_YELLOW, COLOR_BLUE);
	init_pair(BlueKey_PAIR, COLOR_YELLOW, COLOR_BLUE);

	do{
		attron(COLOR_PAIR(PLAYER_PAIR));
		mvaddch(CharacterY,CharacterX,PLAYER);
		attroff(COLOR_PAIR(PLAYER_PAIR));
		move(CharacterY, CharacterX);
		refresh();			/* Print it on to the real screen */
		
		ch = getch();			/* Wait for user input */
		
		switch(ch){
		case KEY_UP:
			if ((CharacterY>0) && (move_okay(CharacterY-1, CharacterX))){
				mvaddch(CharacterY, CharacterX, EMPTY); //Makes old position empty space
				CharacterY = CharacterY -1;
			}
			break;
		case KEY_DOWN:
			if ((CharacterY<LINES-1) && (move_okay(CharacterY+1,CharacterX))){
				mvaddch(CharacterY, CharacterX, EMPTY); //Makes old position empty space
				CharacterY = CharacterY + 1;
			}
			break;
		case KEY_RIGHT:
			if ((CharacterX<COLS-1) && (move_okay(CharacterY,CharacterX+1))){
				mvaddch(CharacterY, CharacterX, EMPTY); //Makes old position empty space
				CharacterX = CharacterX + 1;
			}
			break;
		case KEY_LEFT:
			if ((CharacterX>0) && (move_okay(CharacterY, CharacterX-1))){
				mvaddch(CharacterY, CharacterX, EMPTY); //Makes old position empty space
				CharacterX = CharacterX - 1;
			}
			break;
		}

		Boundary_Checker();

	} while((ch!='q') && (ch != 'Q') && (GameOver == 0));

	if (GameOver == 1){
		sleep(10); //Pause on winning screen before exiting ncurses
	}

	endwin();
}