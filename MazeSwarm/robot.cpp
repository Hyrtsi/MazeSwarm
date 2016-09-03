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
	_maze(nullptr),
	_x(x),
	_y(y),
	_xOrigin(xOrigin),
	_yOrigin(yOrigin),
	_radius(radius),
	_state(STATE_INIT)
{
	circle.setPosition(xOrigin + _x, yOrigin + _y);
	circle.setRadius(_radius);
	circle.setFillColor(sf::Color(100, 250, 50));
}

//Grid coordinates <-> draw coordinates (*wallThickness -fold ratio)
//_x, _y are draw coordinates so everything inside [][] should be transformed with Hyyrynen transformation H(e) = e/wallThickness

void Robot::draw(sf::RenderWindow& window) const {
	window.draw(circle);
}

void Robot::moveTest(void) {
	//Mostly useless.
	if (!_maze) return;
	float offsetY = 5;
	const float wallThickness = 5.0f;
	auto& square = (*_maze)((_x) / wallThickness, (_y + offsetY) / wallThickness);
	circle.move(0, offsetY);
}



void Robot::solveMaze(void) {

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
		moveDirection(_direction);
		
		auto newDirections = getNewDirections(_direction);

		if (newDirections.size() > 1) {
			//std::cout << "Arrived at crossroads, coordinates: " << _x << " " << _y << std::endl;
			
			//Calling .back() to empty container causes weird behavior...? Does this actually call it since the size == 0 is first?

			if (_branches.size() == 0 || _branches.back().terminate == false) {					//Does this cause error? Logic: coming to cr without terminate == it's new
				//Never been here before

				Branch branch;
				branch.arriveDirection = _direction;
				branch.directions = newDirections;
				_branches.push_back(branch);
				std::cout << "New branch, amount of branches: " << _branches.size() << std::endl;
			}
			_state = STATE_SPLIT;

		}
		else if (newDirections.size() == 1) {
			//std::cout << "Tunnel goes on" << std::endl;
			_direction = newDirections[0];
			_state = STATE_MOVING;
		}
		else {
			//std::cout << "At the end of the branch" << std::endl;
			//Reached a dead end, returning back to crossroads

			_direction.x *= -1;
			_direction.y *= -1;
			_branches.back().terminate = true;												//TEST

		}

		//moveDirection(_direction);
	}
	else if (_state == STATE_SPLIT) {

		//Upon arriving to crossroads, we have to find out whether the robot has already been here or not.
		//If it was needed (first visit), new branch has already been made at STATE_MOVE

		//Current logic for cr:
		//Make a new branch or not (must be done at move)
		//Select random direction from branches.back().directions
		//Remove that specific dir
		//set terminate to false (as we're moving to another branch in the current cr)
		//goto move		
		
		srand(time(NULL));						//This must be here?


		std::vector<sf::Vector2i> branchDirections = _branches.back().directions;

		if (branchDirections.size() > 0) {

			// Select a random direction from the possible branch directions - {2,3} possibles
			// Remove the direction so that we don't use the same twice
			// After that, go and adventure at the selected branch

			int randIndex = rand() % branchDirections.size();
			_direction = branchDirections[randIndex];
			branchDirections.erase(std::remove(branchDirections.begin(), branchDirections.end(), _direction), branchDirections.end());	//erase-remove idiom

			_branches.back().directions = branchDirections;				//This is not smooth...?
			_branches.back().terminate = false;								//TEST TEST
		}
		else {
			// Visited every branch, time to terminate the branch and go back
			_direction.x = -1 * _branches.back().arriveDirection.x;
			_direction.y = -1 * _branches.back().arriveDirection.y;
			_branches.pop_back();
			std::cout << "Removed branch, amount of branches: " << _branches.size() << std::endl;
			//How does this affect setting [-1].terminate = false???
			//I think no bad..?
			//The removal could also happen at arrival but this might be OK.


			_branches.back().terminate = true;								//Transfers the message: this subbranch was no-go
		}
		_state = STATE_MOVING;
	}
}





bool Robot::facingWall(void) {
	if (!_maze) return false;
	const float wallThickness = 5.0f;

	//Not to be called when _state == STATE_INIT
	//Actually, there is no OB problem. With direction, maybe since dir = {0,0}
	return (*_maze)(_x / wallThickness + _direction.x, _y / wallThickness + _direction.y).isWall;
}



void Robot::moveDirection(const sf::Vector2i& direction) {
	const float wallThickness = 5.0f;	//	again, consider more flexible way of specifying this
	//Instead of "x horizontally and y vertically", you can just say "1 click to this direction"
	moveOffset(wallThickness * direction.x, wallThickness * direction.y);
}


void Robot::moveOffset(float offsetX, float offsetY) {

	if (!_maze) return;
	
	const float wallThickness = 5.0f;

	auto& mazeSize = _maze->getSize();

	if (_x + offsetX < 0) offsetX = 0;
	if (_y + offsetY < 0) offsetY = 0;
	if ((_x + offsetX) / 5 > mazeSize.x - 1) offsetX = mazeSize.x - 1;
	if ((_y + offsetY)  /5 > mazeSize.y - 1) offsetY = mazeSize.y - 1;

	if (!(*_maze)((_x + offsetX) / wallThickness, (_y + offsetY) / wallThickness).isWall)	//	consider similar kind of DrawParameters than in maze? or maybe make the struct global and reuse it?
	{
		circle.move(offsetX, offsetY);
		_x += offsetX;
		_y += offsetY;
		_direction = sf::Vector2i{ (int)(offsetX / wallThickness), (int)(offsetY / wallThickness) };
	}
	
}


std::vector<sf::Vector2i> Robot::getNewDirections(sf::Vector2i lastDirection) {
	//Returns a list of available directions excluding the inverse of last direction!
	//Does the argument really have to be const?
	if (!_maze) return std::vector<sf::Vector2i>();
	
	const float wallThickness = 5.0f;

	//Idea: only remove the inv of last dir if _state != STATE_RETURN ?
	
	//Inverse the last direction:

	sf::Vector2i removeDirection = lastDirection;		//Somehow I feel that it wouldn't be safe to edit lastDirection but rather create this new guy.
	removeDirection.x *= -1;
	removeDirection.y *= -1;


	std::vector<sf::Vector2i> tempDirections = __directions;
	tempDirections.erase(std::remove(tempDirections.begin(), tempDirections.end(), removeDirection), tempDirections.end());
	
	//Yet to find the possible ones from this bunch...

	std::vector<sf::Vector2i> newDirections;

	for (auto& direction : tempDirections) {

		auto& square = (*_maze)((_x / wallThickness) + direction.x, (_y / wallThickness) + direction.y);

		//We have to discriminate out of bounds squares and regular somehow...
		//And the way is: for ob square,	isWall = true, isFinish = true

		if (!square.isWall) {
			newDirections.push_back(direction);
		}
	}

	return newDirections;
}



//auto& mazeSize = _maze->getSize();