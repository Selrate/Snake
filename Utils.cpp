#include "Utils.h"

using namespace std;

Utils::Utils()
{
}

void Utils::GetCharacterLimit()
{
	// Get character limit
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
	{
		// an error occourred
		cerr << "Cannot determine console size." << endl;
	}
	else
	{
		ConsoleCharLengthX = csbi.srWindow.Right - csbi.srWindow.Left;
		ConsoleCharLengthY = csbi.srWindow.Bottom - csbi.srWindow.Top;
	}
}

void Utils::GotoXY(int _x, int _y)
{
	// Set position to given coord
	COORD coord;
	coord.X = _x;
	coord.Y = _y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Utils::SetConsoleSize(int _x, int _y)
{
	// Get handle to console
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);

	// Resize console to square
	MoveWindow(console, r.left, r.top, _x, _y, TRUE);
}

void Utils::SetCursorVisibility(bool _visible)
{
	// Hide cursor
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = _visible;
	SetConsoleCursorInfo(out, &cursorInfo);
}

bool Utils::PositionEquals(COORD _p1, COORD _p2)
{
	return (_p1.X == _p2.X && _p1.Y == _p2.Y);
}

