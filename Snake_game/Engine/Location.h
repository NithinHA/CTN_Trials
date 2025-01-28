#pragma once

struct Location {
	int x;
	int y;

	void Add(const Location& location) {
		x += location.x;
		y += location.y;
	}

	bool operator == (const Location& rhs) const {
		return x == rhs.x && y == rhs.y;
	}

	Location& operator + (const Location& other) {
		Location result { x + other.x, y + other.y };
		return result;
	}

	Location& operator = (const Location& other) {
		if (this != &other)
		{
			x = other.x;
			y = other.y;
		}
		return *this;
	}

};

static constexpr Location LOCATION_ZERO = { 0,0 };