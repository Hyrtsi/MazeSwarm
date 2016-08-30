#include "stdafx.h"
#include "robot.hpp"
#include <iostream>

Robot::Robot(float x, float y) {
	_x = x;
	_y = y;
	circle.setPosition(initVector_x + _x, initVector_y + _y);
	_state = STATE_INIT;
}

float width = 32, height = 32,
	wallThickness = 5;

//Le Problematique:
//Grid coordinates <-> draw coordinates (*wallThickness -fold ratio)
//_x, _y are draw coordinates so everything inside [][] should be transformed with Hyyrynen transformation H(e) = e/wallThickness

void Robot::moveOffset(float offsetX, float offsetY, Maze maze) {

	//This function does the collision and bad things testing (or does it?)

	if (_x + offsetX < 0) offsetX = 0;
	if (_y + offsetY < 0) offsetY = 0;
	if ((_x + offsetX)/5 > width - 1) offsetX = width - 1;
	if ((_y + offsetY)/5 > height - 1) offsetY = height - 1;

	//if (!maze._squares[(_y + offsetY) / wallThickness][(_x + offsetX) / wallThickness].isWall)	//OLD
	if (maze.isWall((_x + offsetX) / wallThickness, (_y + offsetY) / wallThickness) == false)
	{
		circle.move(offsetX, offsetY);
		_x += offsetX;
		_y += offsetY;
		_direction = sf::Vector2i{ (int)(offsetX / wallThickness), (int) (offsetY / wallThickness) };
	}
	
}


void Robot::draw(sf::RenderWindow& window) {
	circle.setRadius(radius);
	circle.setFillColor(sf::Color(100, 250, 50));
	//circle.setPosition(initVector_x +_x, initVector_y+_y);		//Absolute vodka
	window.draw(circle);
}



void Robot::moveDirection(sf::Vector2i direction, Maze maze) {
	//Instead of "x horizontally and y vertically", you can just say "1 click to this direction"
	moveOffset((float) wallThickness * direction.x, (float) wallThickness * direction.y, maze);
}

void Robot::solveMaze(Maze maze) {

	//First try on _single_ robot maze solving algorithm.
	//Using Hyyrynen Left Hand with a Lemon Twist Algorithm -kind of approach

	//Another aspect to maze solving would be to generate the path (f.ex a trail of directions from begin to finish)
	//and to follow this coreography step by step.
	//This is more like generating the steps on the go for greater good...

	std::vector<sf::Vector2i> directions = getDirections();
	/*
	directions.push_back(sf::Vector2i{ 1,0 });
	directions.push_back(sf::Vector2i{ 0,1 });
	directions.push_back(sf::Vector2i{ -1,0 });
	directions.push_back(sf::Vector2i{ 0,-1 });
	*/

	if (_state == STATE_INIT) {
		//Find a direction
		int index = 0;
		_direction = directions[index];

		while (facingWall(maze)) {
			_direction = directions[index];
			index++;
		}
		_state = STATE_MOVING;
	}
	else if (_state == STATE_MOVING) {
		while (!facingWall(maze)) {
			moveDirection(_direction, maze);
		}
		//if (facingWall(maze)) {			//not needed


		//Owch!
		//Get a new direction.
		//The new direction cannot be the last one since it makes the robot's metal nose hurt.

		//std::vector<sf::Vector2i> newDirections;
		//newDirections = directions;
		//newDirections.erase(std::remove(newDirections.begin(), newDirections.end(), _direction), newDirections.end());

		std::vector<sf::Vector2i> newDirections = getNewDirections(maze, _direction);


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

		//}
	}
	else if (_state == STATE_SPLIT) {
		//Whole bunch of stuff happens
	}


}

std::vector<sf::Vector2i> Robot::getDirections(void) {
	//Returns a list of all directions.
	std::vector<sf::Vector2i> directions;
	directions.push_back(sf::Vector2i{ 1,0 });
	directions.push_back(sf::Vector2i{ 0,1 });
	directions.push_back(sf::Vector2i{ -1,0 });
	directions.push_back(sf::Vector2i{ 0,-1 });
	return directions;
}

std::vector<sf::Vector2i> Robot::getNewDirections(Maze maze, sf::Vector2i lastDirection) {
	//Returns a list of available directions excluding the last direction!
	std::vector<sf::Vector2i> tempDirections = getDirections();
	tempDirections.erase(std::remove(tempDirections.begin(), tempDirections.end(), lastDirection), tempDirections.end());

	//Yet to find the possible ones from this bunch...

	std::vector<sf::Vector2i> newDirections;



	for (auto& direction : tempDirections) {
		//std::cout << "x " << _x << "y " << _y << "dir " << direction.x << direction.y << std::endl;
		//std::cout << _y / wallThickness << std::endl;
		
		if (maze.isWall((_x / wallThickness) + direction.x, (_y / wallThickness) + direction.y) == false) {
			newDirections.push_back(direction);
		}

	}

	return newDirections;
}

bool Robot::facingWall(Maze maze) {
	//Not to be called when _state == STATE_INIT
	if (maze.isWall(_x / wallThickness + _direction.x, _y / wallThickness + _direction.y)) return true;
	//if (maze._squares[_y / wallThickness + _direction.y][_x / wallThickness + _direction.x].isWall) return true;
	else return false;
}


void Robot::rndMovement(Maze maze) {

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
	moveOffset((float)rnd_x, (float)rnd_y, maze);
}

void Robot::moveTest(Maze maze) {

	//Wall recognition OK.

	float offsetY = 5;

	//std::cout << "location " << _x << "," << _y << std::endl;
	//std::cout << "paska" << (_y + offsetY) / 5 << std::endl;

	/*
	for (int z = 0; z < 31; z++) {
	std::cout << "isWall = " << maze._squares[1][z].isWall << std::endl;
	}
	*/

	moveDirection(sf::Vector2i{ 0,1 }, maze);
	
	/*
	if ((_y + offsetY) / 5 < width - 1 && maze.isWall((_x) / wallThickness, (_y + offsetY) / wallThickness) == false) {
		circle.move(0, offsetY);
		_y += offsetY;
	}
	else {
		//Hit a wall, time to test other side.
	}
	*/
}


/*
void Robot::setPosition(int x, int y) {
	_x = x;
	_y = y;
}
*/