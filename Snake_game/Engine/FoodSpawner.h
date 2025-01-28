#pragma once
#include "Board.h"
#include "Food.h"
#include <random>

class FoodSpawner
{
public:
	FoodSpawner();
	void Update(std::mt19937 rng, const Board& board, const Snake& snake);
	const std::vector<Food>& GetAllFood() const;
	void DestroyFood(Food& food);

private:
	void SpawnFood(std::mt19937 rng, const Board& board, const Snake& snake);
	Location& FindRandomLocationForFood(std::mt19937 rng, const Board& board, const Snake& snake);
	bool DoesFoodExistAtLocation(const Location& loc);

	std::vector<Food> food;
	static constexpr int MinFoodOnBoard = 4;
};

