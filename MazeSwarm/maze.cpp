#include "stdafx.h"
#include "maze.hpp"
#include <iostream>
#include <vector>

//For _squares, [y][x] is the order. This might be a bad idea...

Maze::Maze(uint64_t width, uint64_t height) :
	_size	(width, height),
	_squares(_size.x, std::vector<Square>(_size.y))
{}

const Square& Maze::operator()(uint64_t x, uint64_t y) const {
	return _squares[x][y];
}

void Maze::addRobot(Robot && robot) {
	_robots.push_back(robot);
	_robots.back()._maze = this;
}

bool Maze::isWall(uint64_t x, uint64_t y) const {
	//Includes boundary check.
	if (x >= 0 && y >= 0 && x < _size.x && y < _size.y)
		return _squares[x][y].isWall;

	return false;
}

const sf::Vector2i& Maze::getSize(void) const {
	//Returns the width and height of the maze.
	return _size;
}

void Maze::draw(sf::RenderWindow& window, const DrawParameters& drawParams) {
	for (int i = 0; i < _size.x; i++) {
		float x = drawParams.xOrigin + i*drawParams.wallThickness;
		for (int j = 0; j < _size.y; j++) {
			float y = drawParams.yOrigin + j*drawParams.wallThickness;
			const Square& square = _squares[i][j];

			sf::RectangleShape tile(sf::Vector2f(wallThickness, wallThickness));
			tile.setFillColor(square.isWall ? drawParams.wallColor : drawParams.nonWallColor);
			tile.setPosition(x, y);
			
			window.draw(tile);
		}
	}
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

*/


