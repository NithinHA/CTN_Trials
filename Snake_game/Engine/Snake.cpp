#include "Snake.h"
#include <assert.h>

Snake::Snake(const Location& loc)
{
	segments[0].InitHead(loc);
}

void Snake::MoveBy(const Location& delta) {
	for (size_t i = currentSegmentCount - 1; i > 0; i--)
	{
		segments[i].Follow(segments[i - 1]);
	}
	segments[0].MoveBy(delta);
}

void Snake::Grow()
{
	if (currentSegmentCount < maxElements) {
		segments[currentSegmentCount].InitBody();
		currentSegmentCount++;
	}
}

void Snake::Draw(Board& board)
{
	for (size_t i = 0; i < currentSegmentCount; i++)
	{
		segments[i].Draw(board);
	}
}

Location Snake::GetNextHeadLocation(const Board& board, const Location& delta) const
{
	Location result = segments[0].GetLocation();
	result.Add(delta);

	Segment::FixBoardOverflow(board, result);

	/*if (result.x >= board.GetGridWidth())
		result.x = 0;
	else if (result.x < 0)
		result.x = board.GetGridWidth() - 1;

	if (result.y >= board.GetGridHeight())
		result.y = 0;
	else if (result.y < 0)
		result.y = board.GetGridHeight() - 1;*/
	return result;
}

bool Snake::IsCollidingWithBody(const Location& target, bool includeLastSegment) const
{
	int end = includeLastSegment ? currentSegmentCount : currentSegmentCount - 1;
	for (size_t i = 0; i < end; i++)
	{
		if (target == segments[i].GetLocation())
			return true;
	}
	return false;
}

void Snake::Segment::InitHead(const Location& location) {
	this->location = location;
	color = Snake::headColor;
}

void Snake::Segment::InitBody() {
	color = GetRandomDarkGreenShade();
}

Color Snake::Segment::GetRandomDarkGreenShade() {
	unsigned char r = rand() % 56;			// random (0-55)
	unsigned char g = 100 + rand() % 156;	// random (100-255)
	unsigned char b = rand() % 56;			// random (0-55)
	return Color{ r, g, b };
}

void Snake::Segment::Follow(const Segment& nextSegment) {
	location = nextSegment.location;
}

void Snake::Segment::MoveBy(const Location& delta) {
	assert(abs(delta.x) + abs(delta.y) == 1);
	location.Add(delta);
}

void Snake::Segment::Draw(Board& board) {
	FixBoardOverflow(board, location);
	board.DrawCell(location, color);
}

void Snake::Segment::FixBoardOverflow(const Board& board, Location& inputLocation) {
	
	if (inputLocation.x >= board.GetGridWidth())
		inputLocation.x = 0;
	else if (inputLocation.x < 0)
		inputLocation.x = board.GetGridWidth() - 1;

	if (inputLocation.y >= board.GetGridHeight())
		inputLocation.y = 0;
	else if (inputLocation.y < 0)
		inputLocation.y = board.GetGridHeight() - 1;
}

const Location& Snake::Segment::GetLocation() const
{
	return location;
}
