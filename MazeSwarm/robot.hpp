#ifndef ROBOT_HPP
#define ROBOT_HPP
#include <SFML/Graphics.hpp>
#include "maze.hpp"

class Robot {

public:
	float _x, _y;
	Robot(float x, float y);
	void Robot::draw(sf::RenderWindow& window);
	void Robot::moveOffset(float offsetX, float offsetY, Maze maze);
	void Robot::rndMovement(Maze maze);
	void Robot::moveTest(Maze maze);
private:
	float radius = 5.0f / 2,									//Somehow make these global?
		initVector_x = 10.0f, initVector_y = 10.0f;				//For drawing.
	sf::CircleShape circle;
};

#endif