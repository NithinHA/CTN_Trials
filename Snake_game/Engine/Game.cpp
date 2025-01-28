/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	board(gfx),
	rng(std::random_device()()),
	snake({ 2,2 }),
	foodSpawner()
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (!isGameStarted) {
		isGameStarted = wnd.kbd.KeyIsPressed(VK_RETURN);
		return;
	}

	if (isGameOver) {
		if(wnd.kbd.KeyIsPressed(VK_RETURN))
			isGameOver = false;
		return;
	}

	HandleSnakeMovement();

	foodSpawner.Update(rng, board, snake);
	snakeMoveCounter++;
	if (snakeMoveCounter >= snakeMovementPeriod) {
		Location nextHeadLocation = snake.GetNextHeadLocation(board, snakeMovementDelta);
		if (HasSnakeConsumedAFood(nextHeadLocation)) {
			snake.Grow();
			foodConsumeCount++;
			if (snakeMovementPeriod > minSnakeMovementPeriod)
				snakeMovementPeriod = maxSnakeMovementPeriod - foodConsumeCount / foodConsumptionForSpeedIncrease;
		}

		//Location& nextHeadLocation = nextHeadLocation;
		if (snake.IsCollidingWithBody(nextHeadLocation, false)) {
			isGameOver = true;
		}

		snakeMoveCounter = 0;
		snake.MoveBy(snakeMovementDelta);
	}
}

void Game::HandleSnakeMovement() {
	Location target = snakeMovementDelta;
	if (wnd.kbd.KeyIsPressed(VK_UP)) {
		target = { 0,-1 };
	}
	else if (wnd.kbd.KeyIsPressed(VK_DOWN)) {
		target = { 0,1 };
	}
	else if (wnd.kbd.KeyIsPressed(VK_LEFT)) {
		target = { -1,0 };
	}
	else if (wnd.kbd.KeyIsPressed(VK_RIGHT)) {
		target = { 1,0 };
	}
	
	if (snakeMovementDelta + target == LOCATION_ZERO)
		return;

	snakeMovementDelta = target;
}

bool Game::HasSnakeConsumedAFood(Location& nextHeadLocation) {
	for each (Food food in foodSpawner.GetAllFood())
	{
		if (nextHeadLocation == food.GetLocation()) {
			foodSpawner.DestroyFood(food);
			return true;
		}
	}
	return false;
}

void Game::ComposeFrame()
{
	if (!isGameStarted) {
		SpriteCodex::DrawTitle(350, 265, gfx);
		return;
	}

	snake.Draw(board);
	auto& allFood = foodSpawner.GetAllFood();
	for (size_t i = 0; i < allFood.size(); i++)
	{
		allFood[i].Draw(board);
	}

	if (isGameOver) {
		SpriteCodex::DrawGameOver(290, 225, gfx);
	}
}
