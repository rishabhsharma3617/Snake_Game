

#include <iostream>
#include <conio.h>
#include <string>
#include <windows.h>
using namespace std;
/* variables are declared here */
bool end_game;
bool turn_off;
const int width_play = 20;
const int height_play = 20;
int x, y;
int fruitX, fruitY; 
int score;
int tailX[400], tailY[400], nTail;


enum eDirection {STOP, LEFT, RIGHT, UP, DOWN};

eDirection dir;

void init_Game()
{
	system("cls");
	cout << "\n!!!!!!!!!!!!!!!WELCOME TO THE SNAKELAND!!!!!!!!!!!"
	     << "\n\n             Press 's' to Start!"
	     << "\n\n             Press 'q' to Quit"
	     << "\n\n             Your Previous Score: " << score << endl;
}

void fruit_init()
{
	fruitX = rand() % width_play;
	fruitY = rand() % height_play;
}
void Setup() 
{
	end_game = false;
	turn_off = false;
	dir = STOP;
	x = width_play / 2;
	y = height_play / 2;
	fruit_init();
	score = 0;
	nTail = 0;
}
void Draw()
{
	system("cls");                         
	/////////////////////function to create the boundary///////////////////////////
	for (int i = 0; i < width_play + 2; i++) 
	{
		cout << "#";
	}
	cout << endl;
	
	for (int i = 0; i < height_play; i++) 
	{
		for (int j = 0; j < width_play; j++) 
		{
			if (j == 0) 
				cout << "#";
			
			if (i == y && j == x) 
				cout << "O";
			
			else if (i == fruitY && j == fruitX) 
				cout << "F";
		
			else 
			{
				
				bool print = false;
				for (int k = 0; k < nTail; k++) 
				{
					if (tailX[k] == j && tailY[k] == i) 
					{
						cout << "o";
						print = true;
					}		
				}
				if(!print)
					cout << " ";
			}
			
			if (j == width_play - 1) 
				cout << "#";
		}
		cout << endl;
	}
	for (int i = 0; i < width_play + 2; i++) {
		cout << "#";
	}
	cout << endl;
	cout << "Score: " << score << endl;
}
void Input()
{
	if (_kbhit()) {
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'x':
			turn_off = true;
			break;
		}
	}
}
void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;

	for (int i = 1; i < nTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;

	}

	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}
	if (x > width_play || x < 0 || y > height_play || y < 0) {
		turn_off= true;
		init_Game();
	}

	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == x && tailY[i] == y)
			turn_off = true;
	}

	if (x == fruitX && y == fruitY) {
		score++;
		nTail++;
		fruit_init();
	}
}
/* main function starts here*/
int main()
{
	do {
		init_Game();
		string btn;
		cin >> btn;
		if (btn == "s")
		{
			Setup();
			while (!turn_off)
			{
				Draw();
				Input();
				Logic();
				Sleep(100);
			}
		}
	
		else if (btn == "q")
			turn_off = true;
	} while (turn_off == false);

    return 0;
}

