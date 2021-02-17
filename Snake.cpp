/*
	Made by- Tanmay Garg
	Date - 13/5/2020

	Tested on CMD and Powershell.
	Application is not stable in windows, works fine in Linux.

	Debugged in VS Code
*/

#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
bool gameOver;
const int horizontalLength = 40;
const int height = 40;
int x, y, eatX, eatY, score;
int tailX[200], tailY[200];
int snake;
//making enum for easy-key access
enum directionSnake
{
	STOP = 0,
	LEFT,
	RIGHT,
	UP,
	DOWN
};
directionSnake drn;
void Setup()
{
	gameOver = false;
	drn = STOP;
	x = horizontalLength / 2;
	y = height / 2;
	eatX = rand() % horizontalLength;
	eatY = rand() % height;
	score = 0;
}
//print glitch in windows! -- Linux test works fine!
void Draw()
{
	system("cls");
	for (int i = 0; i < horizontalLength + 2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < horizontalLength; j++)
		{
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "O";
			else if (i == eatY && j == eatX)
				cout << "F";
			else
			{
				bool print = false;
				for (int k = 0; k < snake; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}

			if (j == horizontalLength - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < horizontalLength + 2; i++)
		cout << "#";
	cout << endl;
	cout << "Score:" << score << endl;
}

void Input()
{
	if (_kbhit())//in-built
	{
		switch (_getch())
		{
		case 'a':
			drn = LEFT;
			break;
		case 'd':
			drn = RIGHT;
			break;
		case 'w':
			drn = UP;
			break;
		case 's':
			drn = DOWN;
			break;
		case 'x':
			gameOver = true;
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
	for (int i = 1; i < snake; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (drn)
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
	default:
		break;
	}

	if (x >= horizontalLength)
		x = 0;
	else if (x < 0)
		x = horizontalLength - 1;
	if (y >= height)
		y = 0;
	else if (y < 0)
		y = height - 1;

	for (int i = 0; i < snake; i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;

	if (x == eatX && y == eatY)
	{
		score += 10;
		eatX = rand() % horizontalLength;
		eatY = rand() % height;
		snake++;
	}
}
//driver code
int main()
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(10);
	}
	return 0;
}