#pragma once
#include "Board.h"

class Snake {

private:
	class Segment {
	public:
		void InitHead(const Location& location);
		void InitBody();
		
		void Follow(const Segment& next);
		void MoveBy(const Location& delta);
		void Draw(Board& board);
		const Location& GetLocation() const;

		static void FixBoardOverflow(const Board& board, Location& inputLocation);
	private:
		Color GetRandomDarkGreenShade();
		Location location;
		Color color;
	};

public:
	Snake(const Location& loc);
	void MoveBy(const Location& delta);
	void Grow();
	void Draw(Board& board);
	
	Location GetNextHeadLocation(const Board& board, const Location& delta) const;
	bool IsCollidingWithBody(const Location& target, bool includeLastSegment) const;


private:
	static constexpr Color headColor = Colors::Yellow;
	static constexpr Color bodyColor{ 255,255,255 };
	static constexpr int maxElements = 100;
	Segment segments[maxElements];
	int currentSegmentCount = 1;
};