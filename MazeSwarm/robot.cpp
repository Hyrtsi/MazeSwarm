#include "stdafx.h"
#include "robot.hpp"
#include <iostream>

Robot::Robot(float x, float y) {
	_x = x;
	_y = y;
	circle.setPosition(initVector_x + _x, initVector_y + _y);
}

float width = 32, height = 32,
	wallThickness = 5;

//Le Problematique:
//Grid coordinates <-> draw coordinates (*wallThickness -fold ratio)

void Robot::moveOffset(float offsetX, float offsetY, Maze maze) {
	if (_x + offsetX < 0) offsetX = 0;
	if (_y + offsetY < 0) offsetY = 0;
	if ((_x + offsetX)/5 > width - 1) offsetX = width - 1;
	if ((_y + offsetY)/5 > height - 1) offsetY = height - 1;

	if (!maze._squares[(_y + offsetY)/wallThickness][(_x + offsetX) / wallThickness].isWall)
	{
		circle.move(offsetX, offsetY);
		_x += offsetX;
		_y += offsetY;
	}
	
}


void Robot::draw(sf::RenderWindow& window) {
	circle.setRadius(radius);
	circle.setFillColor(sf::Color(100, 250, 50));
	//circle.setPosition(initVector_x +_x, initVector_y+_y);
	window.draw(circle);
}

void Robot::rndMovement(Maze maze) {

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
	moveOffset((float) rnd_x, (float) rnd_y, maze);
}



void Robot::moveTest(Maze maze) {

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

	if ((_y + offsetY) / 5 < width - 1 && maze._squares[(_y + offsetY) / wallThickness][(_x) / wallThickness].isWall == false) {
		circle.move(0, offsetY);
		_y += offsetY;
	}
	else {
		//Hit a wall, time to test other side.
	}

	//std::cout << _y << std::endl;
}


/*
void Robot::setPosition(int x, int y) {
	_x = x;
	_y = y;
}
*/