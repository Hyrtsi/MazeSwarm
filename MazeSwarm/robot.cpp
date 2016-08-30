#include "stdafx.h"
#include "robot.hpp"
#include "maze.hpp"
#include <iostream>


const std::vector<sf::Vector2i> Robot::__directions = {
	sf::Vector2i{ 1,0 },
	sf::Vector2i{ 0,1 },
	sf::Vector2i{ -1,0 },
	sf::Vector2i{ 0,-1 }
};


Robot::Robot(float x, float y, float xOrigin, float yOrigin,
             float radius, const sf::Vector2i& direction) :
	_maze		(nullptr),
	_x			(x),
	_y			(y),
	_xOrigin	(xOrigin),
	_yOrigin	(yOrigin),
	_radius		(radius),
	_state		(STATE_INIT)
{
	circle.setPosition(xOrigin + _x, yOrigin + _y);
	circle.setRadius(_radius);
	circle.setFillColor(sf::Color(100, 250, 50));
}

//	no. no. noooooo~
//float width = 32, height = 32,
//	wallThickness = 5;

//Le Problematique:
//Grid coordinates <-> draw coordinates (*wallThickness -fold ratio)
//_x, _y are draw coordinates so everything inside [][] should be transformed with Hyyrynen transformation H(e) = e/wallThickness

void Robot::draw(sf::RenderWindow& window) const {
	//circle.setPosition(initVector_x +_x, initVector_y+_y);		//Absolute vodka
	window.draw(circle);
}

void Robot::rndMovement(void) {

	//Just a drunken hobo lost at a maze...
	//Working Ok!

	int randNum = rand() % 3;
	randNum--;
	//std::cout << randNum;
	int rnd_x, rnd_y;

	if (rand() % 1000 > 500) {
		rnd_x = randNum * 5;
		rnd_y = 0;
	}
	else {
		rnd_y = randNum * 5;
		rnd_x = 0;
	}
	moveOffset((float)rnd_x, (float)rnd_y);
}

void Robot::moveTest(void) {
	if (!_maze) return;

	//Wall recognition OK.

	float offsetY = 5;

	std::cout << "location " << _x << "," << _y << std::endl;
	std::cout << "paska" << (_y + offsetY) / 5 << std::endl;

	/*
	for (int z = 0; z < 31; z++) {
	std::cout << "isWall = " << maze._squares[1][z].isWall << std::endl;
	}
	*/


	/*
	if (!maze._squares[(_y + offsetY) / wallThickness][(_x) / wallThickness].isWall)
	{
	circle.move(0, offsetY);
	_y += offsetY;
	}
	*/
	const float wallThickness = 5.0f;
	auto& mazeSize = _maze->getSize();
	auto& square = (*_maze)((_x) / wallThickness, (_y + offsetY) / wallThickness);
	
	if ((_y + offsetY) / 5 < mazeSize.x - 1 && !square.isWall) {
		circle.move(0, offsetY);
		_y += offsetY;
	}
	else {
		//Hit a wall, time to test other side.
	}

	//std::cout << _y << std::endl;
}

void Robot::solveMaze(void) {

	//First try on _single_ robot maze solving algorithm.
	//Using Hyyrynen Left Hand with a Lemon Twist Algorithm -kind of approach

	//Another aspect to maze solving would be to generate the path (f.ex a trail of directions from begin to finish)
	//and to follow this coreography step by step.
	//This is more like generating the steps on the go for greater good...

	/*
	directions.push_back(sf::Vector2i{ 1,0 });
	directions.push_back(sf::Vector2i{ 0,1 });
	directions.push_back(sf::Vector2i{ -1,0 });
	directions.push_back(sf::Vector2i{ 0,-1 });
	*/

	if (_state == STATE_INIT) {
		//Find a direction
		uint64_t index = 0;
		_direction = __directions[index];

		while (facingWall()) {
			_direction = __directions[index];
			index++;
		}
		_state = STATE_MOVING;
	}
	else if (_state == STATE_MOVING) {
		while (!facingWall()) {
			moveDirection(_direction);
		}
		if (facingWall()) {
			//Owch!
			//Get a new direction.
			//The new direction cannot be the last one since it makes the robot's metal nose hurt.

			//std::vector<sf::Vector2i> newDirections;
			//newDirections = directions;
			//newDirections.erase(std::remove(newDirections.begin(), newDirections.end(), _direction), newDirections.end());

			auto newDirections = getNewDirections(_direction);

			if (newDirections.size() > 1) {
				_state = STATE_SPLIT;		//Crossroads
				std::cout << "Arrived at crossroads..." << std::endl;
			}
			else if (newDirections.size() == 1) {
				std::cout << "Tunnel goes on" << std::endl;
				_direction = newDirections[0];
				_state = STATE_MOVING;
			}
			else std::cout << "Wtf bug man! @solveMaze moving alg" << std::endl;				//Dirty!
		}
	}
	else if (_state == STATE_SPLIT) {
		//Whole bunch of stuff happens
	}
}

bool Robot::facingWall(void) {
	if (!_maze) return;
	const float wallThickness = 5.0f;

	//Not to be called when _state == STATE_INIT
	//if (maze._squares[_y / wallThickness + _direction.y][_x / wallThickness + _direction.x].isWall) return true;
	return (*_maze)(_x / wallThickness + _direction.x, _y / wallThickness + _direction.y).isWall;
}

void Robot::moveDirection(const sf::Vector2i& direction) {
	const float wallThickness = 5.0f;	//	again, consider more flexible way of specifying this
	//Instead of "x horizontally and y vertically", you can just say "1 click to this direction"
	moveOffset(wallThickness * direction.x, wallThickness * direction.y);
}

//	I suggest using integers for maze solving and movement and floating point only for drawing
void Robot::moveOffset(float offsetX, float offsetY) {
	if (!_maze) return;

	//This function does the collision and bad things testing (or does it?)

	auto& mazeSize = _maze->getSize();

	if (_x + offsetX < 0) offsetX = 0;
	if (_y + offsetY < 0) offsetY = 0;
	if ((_x + offsetX) / 5 > mazeSize.x - 1) offsetX = mazeSize.x - 1;
	if ((_y + offsetY) / 5 > mazeSize.y - 1) offsetY = mazeSize.y - 1;

	//if (!maze._squares[(_y + offsetY) / wallThickness][(_x + offsetX) / wallThickness].isWall)	//OLD
	if (!(*_maze)((_x + offsetX) / 5.0f, (_y + offsetY) / 5.0f).isWall)	//	consider similar kind of DrawParameters than in maze? or maybe make the struct global and reuse it?
	{
		circle.move(offsetX, offsetY);
		_x += offsetX;
		_y += offsetY;
		_direction = sf::Vector2i{ (int)(offsetX / wallThickness), (int)(offsetY / wallThickness) };
	}

}

std::vector<sf::Vector2i> Robot::getNewDirections(const sf::Vector2i& lastDirection) {
	if (!_maze) return;
	const float wallThickness = 5.0f;
	
	//Returns a list of available directions excluding the last direction!
	std::vector<sf::Vector2i> tempDirections = __directions;
	tempDirections.erase(std::remove(tempDirections.begin(), tempDirections.end(), lastDirection), tempDirections.end());

	//Yet to find the possible ones from this bunch...

	std::vector<sf::Vector2i> newDirections;

	for (auto& direction : tempDirections) {
		//std::cout << "x " << _x << "y " << _y << "dir " << direction.x << direction.y << std::endl;
		//std::cout << _y / wallThickness << std::endl;
		auto& square = (*_maze)((_x / wallThickness) + direction.x, (_y / wallThickness) + direction.y);

		if (!square.isWall) {
			newDirections.push_back(direction);
		}

	}

	return newDirections;
}




/*
void Robot::setPosition(int x, int y) {
	_x = x;
	_y = y;
}
*/