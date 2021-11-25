#pragma once

#include <iostream>
#include <Windows.h>

class Utils
{
public:
	Utils();
	int GetConsoleCharLenthX() { return ConsoleCharLengthX; }
	int GetConsoleCharLenthY() { return ConsoleCharLengthY; }

	void GotoXY(int, int);
	void SetConsoleSize(int, int);
	void SetCursorVisibility(bool);
	void GetCharacterLimit();

	bool PositionEquals(COORD, COORD);

private:
	

	int ConsoleCharLengthX = 0;
	int ConsoleCharLengthY = 0;
};

