#include "stdafx.h"
#include "maze.hpp"
#include <iostream>
#include <vector>

//For _squares, [y][x] is the order. This might be a bad idea...
//Called outside maze, (x, y) is the order. The fuzz is only under the hood.

Maze::Maze(uint64_t width, uint64_t height) :
		_size	(width, height),
		_squares(_size.x, std::vector<Square>(_size.y))
{
	creationalgorithm();
}

const Square& Maze::operator()(uint64_t x, uint64_t y) const {
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
	if (location.y <= _size.x - 3) neighbors.push_back(sf::Vector2i{ location.x, location.y + 2 });	//Check?
	if (location.x <= _size.y - 3) neighbors.push_back(sf::Vector2i{ location.x + 2, location.y });		//Check?

	for (auto& neighbor : neighbors) {
		if (std::find(unvisited.begin(), unvisited.end(), neighbor) != unvisited.end()) {					//if neighbor in unvisited
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

	for (int i = 0; i < _size.y / 2; i++) {
		for (int j = 0; j < _size.x / 2; j++) {
			unvisited.push_back(sf::Vector2i{ 2 * i,2 * j });
		}
	}										//Note: unvisited consists of (0,0), (0,2), (0,4), ..., (2,0),..

	current = initialCell;					//Make the initial cell the current cell and mark it as visited

	while (unvisited.size() > 0) {

		removeWall(current.x, current.y);
		unvisited.erase(std::remove(unvisited.begin(), unvisited.end(), current), unvisited.end());		//erease-remove idiom

		unvNeighbors = getNeighbors(current, unvisited);		//Now, unvNeighbors should contain neighbors for "current" that are unvisited

		if (!unvNeighbors.empty()) {							//If the current cell has any neighbours which have not been visited:
																//Choose randomly one of the unvisited neighbours
			int RandIndex = rand() % unvNeighbors.size();		//Number between 0 and nNeighbors-1 (?)
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
}


void Maze::draw(sf::RenderWindow& window, const DrawParameters& drawParams) {

	for (int i = 0; i < _size.x; i++) {
		float x = drawParams.xOrigin + i*drawParams.wallThickness;
		for (int j = 0; j < _size.y; j++) {
			float y = drawParams.yOrigin + j*drawParams.wallThickness;
			const Square& square = _squares[i][j];

			sf::RectangleShape tile(sf::Vector2f(drawParams.wallThickness, drawParams.wallThickness));
			tile.setFillColor(square.isWall ? drawParams.wallColor : drawParams.nonWallColor);
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


/*


sf::Vector2i data{ 20, 20 };
sf::Vector3i foo{ 1,1,1 };

std::vector<std::vector<int>> vectorception;
std::vector<std::vector<std::vector<int>>> vector3;

//std::cout << mysquare.isWall;
//mysquare.isWall = true;
//std::cout << mysquare.isWall;




std::vector<class Square> vtest;
std::vector<std::vector<std::vector<class Square>>> maze;
std::vector<int>(3, 6);		//=={6,6,6}
std::vector<std::vector<int>>(100, std::vector<int>(100, 60));
std::vector<class Square>(100, Square());	//square has no constructor arguments


if (_squares[0][0].isWall) {
sf::RectangleShape tile(sf::Vector2f(wallThickness, wallThickness));
tile.setFillColor(sf::Color(50, 50, 250));
tile.setPosition(initVector_x + x, initVector_y + y);
window.draw(tile);
}



*/