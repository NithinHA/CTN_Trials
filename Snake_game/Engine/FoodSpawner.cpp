#include "FoodSpawner.h"

FoodSpawner::FoodSpawner()
{
}

void FoodSpawner::Update(std::mt19937 rng, const Board& board, const Snake& snake)
{
	if (food.size() < MinFoodOnBoard) {
		SpawnFood(rng, board, snake);
	}
}

const std::vector<Food>& FoodSpawner::GetAllFood() const
{
	return food;
}

void FoodSpawner::DestroyFood(Food& foodInstance)
{
	food.erase(std::remove(food.begin(), food.end(), foodInstance), food.end());
}

void FoodSpawner::SpawnFood(std::mt19937 rng, const Board& board, const Snake& snake)
{
	Location& location = FindRandomLocationForFood(rng, board, snake);
	Food foodInstance(location);
	food.push_back(foodInstance);
}

Location& FoodSpawner::FindRandomLocationForFood(std::mt19937 rng, const Board& board, const Snake& snake) {
	std::uniform_int_distribution<int> xDist(0, board.GetGridWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, board.GetGridHeight() - 1);
	Location foodLocation;
	do {
		foodLocation.x = xDist(rng);
		foodLocation.y = yDist(rng);
	} while (snake.IsCollidingWithBody(foodLocation, true) || DoesFoodExistAtLocation(foodLocation));

	return foodLocation;
}

bool FoodSpawner::DoesFoodExistAtLocation(const Location& loc)
{
	for (size_t i = 0; i < food.size(); i++)
	{
		if (food[i].GetLocation() == loc)
			return true;
	}
	return false;
}
