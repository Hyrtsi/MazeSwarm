#include "stdafx.h"
#include "maze.hpp"
#include <iostream>
#include <vector>

//EDITED:
//Square has now a third property, isVisited. Hope it didn't break anything...
//To draw the trajectory for each robot, square can not be const? Testing...

Maze::Maze(uint64_t width, uint64_t height) :
		_size	(width, height),
		_squares(_size.x, std::vector<Square>(_size.y))
{
	creationalgorithm();
}

/*
const Square& Maze::operator()(uint64_t x, uint64_t y) const {
	if (x >= 0 && y >= 0 && x < _size.x && y < _size.y) return _squares[x][y];
	return Square(true, true);									//Try #1: discriminate OB-case with a paradox.
}
*/


Square& Maze::operator()(uint64_t x, uint64_t y) {
	if (x >= 0 && y >= 0 && x < _size.x && y < _size.y) return _squares[x][y];
	return Square(true, true);									//Try #1: discriminate OB-case with a paradox.
}

uint64_t Maze::addRobot(Robot && robot) {
	_robots.push_back(robot);
	_robots.back()._maze = this;
	return _robots.size() - 1;
}

Robot& Maze::getRobot(uint64_t robotId) {
	return _robots[robotId];
}

const Robot& Maze::getRobot(uint64_t robotId) const {
	return _robots[robotId];
}

std::vector<sf::Vector2i> Maze::getNeighbors(sf::Vector2i location, std::vector<sf::Vector2i> unvisited) {

	//Returns the neighbor cells for a desired location.

	std::vector<sf::Vector2i> neighbors;
	std::vector<sf::Vector2i> unvNeighbors;

	if (location.x >= 2) neighbors.push_back(sf::Vector2i{ location.x - 2, location.y });
	if (location.y >= 2) neighbors.push_back(sf::Vector2i{ location.x, location.y - 2 });
	if (location.y <= _size.x - 3) neighbors.push_back(sf::Vector2i{ location.x, location.y + 2 });
	if (location.x <= _size.y - 3) neighbors.push_back(sf::Vector2i{ location.x + 2, location.y });

	for (auto& neighbor : neighbors) {
		if (std::find(unvisited.begin(), unvisited.end(), neighbor) != unvisited.end()) {
			unvNeighbors.push_back(neighbor);
		}
	}

	return unvNeighbors;
}

void Maze::creationalgorithm(void) {

	//Creates meaningful content for only mean _size.x, _size.y

	//This is recursive backtracker algorithm btw.

	sf::Vector2i rndNeighbor;
	std::vector<sf::Vector2i> unvNeighbors;
	std::vector<sf::Vector2i> unvisited;
	std::vector<sf::Vector2i> stack;
	sf::Vector2i current;
	sf::Vector2i initialCell = { 0,0 };
	int mean_x = 0;
	int mean_y = 0;

	_squares[0][0].isVisited = true;		//Not very elegant


	srand(time(NULL));											//Comment for always the same maze.


	for (int i = 0; i < _size.y / 2; i++) {
		for (int j = 0; j < _size.x / 2; j++) {
			unvisited.push_back(sf::Vector2i{ 2 * i,2 * j });
		}
	}															//Note: unvisited consists of (0,0), (0,2), (0,4), ..., (2,0),..

	current = initialCell;										//Make the initial cell the current cell and mark it as visited

	while (unvisited.size() > 0) {

		removeWall(current.x, current.y);
		unvisited.erase(std::remove(unvisited.begin(), unvisited.end(), current), unvisited.end());		//erease-remove idiom

		unvNeighbors = getNeighbors(current, unvisited);		//Now, unvNeighbors should contain neighbors for "current" that are unvisited

		if (!unvNeighbors.empty()) {							//If the current cell has any neighbours which have not been visited:
																
			int RandIndex = rand() % unvNeighbors.size();		//Choose randomly one of the unvisited neighbours
			rndNeighbor = unvNeighbors[RandIndex];
			stack.push_back(current);							//Push the current cell to the stack
																//Remove the wall between the current cell and the chosen cell
			mean_x = (current.x + rndNeighbor.x) / 2;
			mean_y = (current.y + rndNeighbor.y) / 2;
			removeWall(mean_x, mean_y);

			current = rndNeighbor;								//Make the chosen cell the current cell and mark it as visited

		}
		else if (!stack.empty()) {
			//Pop a cell from the stack
			//Make it the current cell

			current = stack.back();
			stack.pop_back();
		}
	}

	//Add finish:

	//First try: manual

	_squares[_size.x - 2][_size.y - 2].isFinish = true;
}

void Maze::editor(sf::Event& event, sf::RenderWindow& window, const DrawParameters& drawParams) {

	if (event.type == sf::Event::MouseButtonPressed)
	{
		int x = (event.mouseButton.x - drawParams.xOrigin) / drawParams.wallThickness;
		int y = (event.mouseButton.y - drawParams.yOrigin) / drawParams.wallThickness;
		
		if (event.mouseButton.button == sf::Mouse::Right)
		{
			_squares[x][y].isWall = false;
			_squares[x][y].isFinish = false;
			//std::cout << "the right button was pressed" << std::endl;
			//std::cout << "mouse x: " << event.mouseButton.x << std::endl;
			//std::cout << "mouse y: " << event.mouseButton.y << std::endl;
		}
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			_squares[x][y].isWall = true;
			_squares[x][y].isFinish = false;
			//std::cout << "the left button was pressed" << std::endl;
			//std::cout << "mouse x: " << event.mouseButton.x << std::endl;
			//std::cout << "mouse y: " << event.mouseButton.y << std::endl;
		}
		if (event.mouseButton.button == sf::Mouse::Middle) {
			_squares[x][y].isFinish = true;
			_squares[x][y].isWall = false;
		}
	}




}



void Maze::draw(sf::RenderWindow& window, const DrawParameters& drawParams) {

	for (int i = 0; i < _size.x; i++) {
		float x = drawParams.xOrigin + i*drawParams.wallThickness;
		for (int j = 0; j < _size.y; j++) {
			float y = drawParams.yOrigin + j*drawParams.wallThickness;
			const Square& square = _squares[i][j];

			sf::RectangleShape tile(sf::Vector2f(drawParams.wallThickness, drawParams.wallThickness));
			//tile.setFillColor(square.isWall ? drawParams.wallColor : drawParams.nonWallColor);

			if (square.isVisited) {
				tile.setFillColor(drawParams.visitedColor);
			}
			else {
				if (square.isWall) tile.setFillColor(drawParams.wallColor);
				else if (!square.isWall) tile.setFillColor(drawParams.nonWallColor);
			}
			if (square.isFinish) tile.setFillColor(drawParams.finishColor);
			tile.setPosition(x, y);

			window.draw(tile);
		}
	}
}



const sf::Vector2i& Maze::getSize(void) const {
	//Returns the width and height of the maze.
	return _size;
}

bool Maze::isWall(uint64_t x, uint64_t y) const {
	//Includes boundary check.
	if (x >= 0 && y >= 0 && x < _size.x && y < _size.y)
		return _squares[y][x].isWall;								// Double check order

	return false;
}

void Maze::removeWall(uint64_t x, uint64_t y) {
	_squares[y][x].isWall = false;
}