#pragma once
#include "Board.h"
#include "Snake.h"
#include <random>

class Food
{
public:
	Food(const Location& location);
	void Draw(Board& board) const;
	const Location& GetLocation() const;
	bool operator == (const Food& rhs) {
		return location == rhs.GetLocation();
	}
	Food& operator=(const Food& other)
	{
		if (this != &other)
		{
			location = other.location;
		}
		return *this;
	}

private:
	Location location;
	static constexpr Color foodColor = Colors::Red;
};

