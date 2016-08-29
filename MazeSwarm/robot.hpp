#ifndef ROBOT_HPP
#define ROBOT_HPP
#include <SFML/Graphics.hpp>
#include "maze.hpp"

class Robot {

	enum State {							//Used to describe the current action. Yes-yes or no-no?
		STATE_INIT,
		STATE_MOVING,
		STATE_SPLIT,
		STATE_FINISH,
		STATE_WAIT
	};

public:
	float _x, _y;
	Robot(float x, float y);
	sf::Vector2i _direction{ 0, 0 };							//Direction is really {x,y}
	State _state;
	void Robot::draw(sf::RenderWindow& window);
	void Robot::rndMovement(Maze maze);									//Mostly useless (For testing drunkard behavior)
	void Robot::moveTest(Maze maze);
	void Robot::solveMaze(Maze maze);
private:
	float radius = 5.0f / 2,									//Somehow make these global?
		initVector_x = 10.0f, initVector_y = 10.0f;				//For drawing.
	sf::CircleShape circle;
	bool Robot::facingWall(Maze maze);
	void Robot::moveDirection(sf::Vector2i direction, Maze maze);
	void Robot::moveOffset(float offsetX, float offsetY, Maze maze);
	std::vector<sf::Vector2i> Robot::getDirections(void);
	std::vector<sf::Vector2i> Robot::getNewDirections(Maze maze, sf::Vector2i lastDirection);
};

#endif