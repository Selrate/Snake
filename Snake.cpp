// Snake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include <cstdint>
#include <algorithm>
#include <chrono>
#include <time.h>
#include <list>
#include <iterator>
#include <vector>

#include "Utils.h"
#include "Pickup.h"

using namespace std;

// Constants
const int ScreenWidth = 500;
const int ScreenHeight = 500;



enum MoveDir
{
	None,
	Right,
	Left,
	Up,
	Down,
};


// Main function
int main()
{
	// Get and init utils
	Utils* MainUtils = new Utils;
	MainUtils->SetConsoleSize(ScreenWidth, ScreenHeight);
	MainUtils->SetCursorVisibility(false);
	MainUtils->GetCharacterLimit();

	// Init head coodinate to top-left
	COORD HeadCoord;
	HeadCoord.X = 0;
	HeadCoord.Y = 0;

	// Spawn fist head char
	cout << "A";

	// Declare move and input dir
	MoveDir SnakeDir = Right;
	MoveDir InputDir = Right;
	double MoveTimer = 0;

	// Declare length
	int SnakeLength = 5;

	// Create pickup
	Pickup* SnakePickup = new Pickup(MainUtils);

	// Declare path, and required iterators
	list<COORD> Path;
	list<COORD>::iterator it1, it2;

	// Bool indicating whether or not the player has lost
	bool Lost = false;

	// Main loop
	while (!Lost)
	{      
		auto start = chrono::steady_clock::now();

		if (_kbhit()) {
			char ch = _getch();

			switch (ch) {
			case 72:
				// Up arrow
				if(SnakeDir != Down) InputDir = Up;
				break;
			case 80:
				// Down arrow
				if (SnakeDir != Up) InputDir = Down;
				break;
			case 77:
				// Right arrow
				if (SnakeDir != Left) InputDir = Right;
				break;
			case 75:
				// Left arrow
				if (SnakeDir != Right) InputDir = Left;
				break;
			default:
				break;
			}
		}

		// Get time since start
		auto end = chrono::steady_clock::now();
		MoveTimer += chrono::duration_cast<chrono::microseconds>(end - start).count();

		// Once enough time has past, move
		if (MoveTimer >= 100000)
		{
			// Set new dir
			SnakeDir = InputDir;

			// Clear last spot
			MainUtils->GotoXY(HeadCoord.X, HeadCoord.Y);
			cout << " ";

			// Store last spot
			Path.push_front(HeadCoord);

			// Trim the back
			while (Path.size() > SnakeLength)
			{
				COORD ClearCoord = Path.back();
				MainUtils->GotoXY(ClearCoord.X, ClearCoord.Y);
				cout << " ";
				Path.pop_back();
			}

			// Get current dir, and update coordinate
			switch (SnakeDir)
			{
			case None:
				break;
			case Right:
				HeadCoord.X++;
				break;
			case Left:
				HeadCoord.X--;
				break;
			case Up:
				HeadCoord.Y--;
				break;
			case Down:
				HeadCoord.Y++;
				break;
			default:
				break;
			}

			// Clamp coordinate so it stays within console bounds
			HeadCoord.X = max(0, min(HeadCoord.X, MainUtils->GetConsoleCharLenthX()));
			HeadCoord.Y = max(0, min(HeadCoord.Y, MainUtils->GetConsoleCharLenthY()));


			// Output head character
			MainUtils->GotoXY(HeadCoord.X, HeadCoord.Y);
			cout << "A";

			// Output the tail characters
			for_each(Path.begin(), Path.end(), 
				[&](COORD& c) 
				{
					MainUtils->GotoXY(c.X, c.Y); cout << "a";

					// Check if lost
					if (c.X == HeadCoord.X && c.Y == HeadCoord.Y)
					{
						Lost = true;
					}
				});

			// Consume pickup
			if (MainUtils->PositionEquals(HeadCoord, SnakePickup->GetPosition()))
			{
				SnakePickup->NewPosition(Path);
				SnakeLength++;
			}


			// Reset timer
			MoveTimer = 0;
		}
	}

	// Ending
	system("cls");
	cout << "Game Over!";
	while (true)
	{
		_getch();
	} 
}
