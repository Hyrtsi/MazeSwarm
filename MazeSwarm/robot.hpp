#ifndef ROBOT_HPP
#define ROBOT_HPP
#include <SFML/Graphics.hpp>
#include "maze.hpp"

class Robot {

public:
	float _x, _y;
	Maze _maze;
	Robot(float x, float y, Maze maze);
	void Robot::draw(sf::RenderWindow& window);
	void Robot::moveOffset(float offsetX, float offsetY);
	void Robot::rndMovement(void);
private:
	float radius = 5.0f / 2,									//Somehow make these global?
		initVector_x = 10.0f, initVector_y = 10.0f;				//For drawing.
	sf::CircleShape circle;
};

#endif