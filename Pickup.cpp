#include "Pickup.h"

Pickup::Pickup(Utils* _utils)
{
	MainUtils = _utils;

	// Get list of first coord to pass
	list<COORD> FirstList;
	COORD ZeroPoint;
	ZeroPoint.X = 0;
	ZeroPoint.Y = 0;
	FirstList.push_back(ZeroPoint);

	NewPosition(FirstList);
}

void Pickup::NewPosition(list<COORD> _blacklist)
{
	// Loop until empty position is found
	bool DoLoop = false;
	do
	{
		// Generate new pos (don't need to clear since head char overrites)
		Position.X = rand() % MainUtils->GetConsoleCharLenthX();
		Position.Y = rand() % MainUtils->GetConsoleCharLenthY();

		// Make sure position isn't in blacklist
		for_each(_blacklist.begin(), _blacklist.end(),
			[&](COORD& c)
			{
				// Check if lost
				if (c.X == Position.X && c.Y == Position.Y)
				{
					DoLoop = true;
				}
			});
	} while (DoLoop);


	// Place new character
	MainUtils->GotoXY(Position.X, Position.Y);
	cout << "b";
}
