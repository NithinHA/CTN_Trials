#pragma once
#include "Graphics.h"
#include "Location.h"

class Board {

public:
	Board(Graphics& gfx);
	void DrawCell(const Location& location, Color c);
	int GetGridWidth() const;
	int GetGridHeight() const;

	void DrawBorder();

private:
	static constexpr int dimension = 20;
	static constexpr int width = 32;
	static constexpr int height = 24;
	static constexpr int cellPadding = 1;

	static constexpr int borderWidth = 5;
	static constexpr int borderHeight = 5;
	static constexpr int borderPadding = 2;
	static constexpr Color borderColor = Colors::Gray;

	static constexpr int xOffset = 20;
	static constexpr int yOffset = 20;
public:
	Graphics& gfx;

};