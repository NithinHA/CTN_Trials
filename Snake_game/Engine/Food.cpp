#include "Food.h"

Food::Food(const Location& location) : location(location)
{
}

void Food::Draw(Board& board) const
{
	board.DrawCell(location, foodColor);
}

const Location& Food::GetLocation() const
{
	return location;
}
