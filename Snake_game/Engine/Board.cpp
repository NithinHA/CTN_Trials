#include "Board.h"
#include <assert.h>

Board::Board(Graphics& gfx) : gfx(gfx) {}

void Board::DrawCell(const Location& location, Color c)
{
	assert(location.x >= 0);
	assert(location.x < width);
	assert(location.y >= 0);
	assert(location.y < height);

	const int offsetX = xOffset + borderWidth * borderPadding + cellPadding;
	const int offsetY = yOffset + borderWidth * borderPadding + cellPadding;

	gfx.DrawRectDim(location.x * dimension + offsetX, location.y * dimension + offsetY, dimension - cellPadding * 2, dimension - cellPadding * 2, c);
	DrawBorder();
}

int Board::GetGridWidth() const
{
	return width;
}

int Board::GetGridHeight() const
{
	return height;
}

void Board::DrawBorder()
{
	const int top = yOffset;
	const int bottom = top + (borderWidth + borderPadding) * 2 + dimension * height;
	const int left = xOffset;
	const int right = left + (borderHeight + borderPadding) * 2 + dimension * width;

	// --
	gfx.DrawRect(left, top, right, top + borderWidth, borderColor);
	// |
	gfx.DrawRect(left, top, left + borderWidth, bottom, borderColor);
	// __
	gfx.DrawRect(left, bottom - borderWidth, right, bottom, borderColor);
	//   |
	gfx.DrawRect(right - borderWidth, top, right, bottom, borderColor);
}
