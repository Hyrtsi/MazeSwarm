#include "stdafx.h"
#include "robot.hpp"
#include <iostream>

Robot::Robot(float x, float y, Maze maze) {
	_x = x;
	_y = y;
	_maze = maze;
	circle.setPosition(initVector_x + _x, initVector_y + _y);
}

//functions


void Robot::moveOffset(float offsetX, float offsetY) {
	if (_x + offsetX < 0) offsetX = 0;
	if (_y + offsetY < 0) offsetY = 0;
	if (!_maze._squares[_x + offsetX][_y + offsetY].isWall) circle.move(offsetX, offsetY);
	
}



void Robot::draw(sf::RenderWindow& window) {
	circle.setRadius(radius);
	circle.setFillColor(sf::Color(100, 250, 50));
	//circle.setPosition(initVector_x +_x, initVector_y+_y);
	window.draw(circle);
}

void Robot::rndMovement(void) {

	int randNum = rand() % 2;
	int rnd_x, rnd_y;

	if (rand() % 1000 > 500) {
		rnd_x = randNum * 5;
		rnd_y = 0;
	}
	else {
		rnd_y = randNum * 5;
		rnd_x = 0;
	}
	moveOffset((float) rnd_x, (float) rnd_y);
}





/*
void Robot::setPosition(int x, int y) {
	_x = x;
	_y = y;
}
*/