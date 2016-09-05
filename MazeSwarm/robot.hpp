#ifndef ROBOT_HPP
#define ROBOT_HPP

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <time.h>

struct Branch {
	sf::Vector2i				arriveDirection;
	std::vector<sf::Vector2i>	directions;
	bool						terminate = false;
};

class Maze;

class Robot {
public:
	friend class Maze;


	Robot(float x, float y, float xOrigin = 10.0f, float yOrigin = 10.0f,
			float radius = 2.5f, const sf::Vector2i& direction = sf::Vector2i(0,0));


	void draw(sf::RenderWindow& window) const;
	void moveTest(void);							//Mostly useless.
	void solveMaze(void);


private:
	enum State {
		STATE_INIT,
		STATE_MOVING,
		STATE_SPLIT,
		STATE_FINISH,
		STATE_WAIT
	};

	//const Maze*								_maze;			// OLD for Const squares
	Maze*									_maze;				// NEW for editing
	float									_x;
	float									_y;

	float									_xOrigin;
	float									_yOrigin;
	float									_radius;

	sf::Vector2i							_direction{ 0, 0 };				//Direction is {x,y}
	State									_state;
	std::vector<Branch>	_branches;								//Collection of _branchDirections
	sf::CircleShape circle;

	static const std::vector<sf::Vector2i>	__directions;

	bool facingWall(void);										//Turns out this function is almost useless. solveMaze -> init is OK use
	bool atFinish(void);

	void moveDirection(const sf::Vector2i& direction);
	void moveOffset(float offsetX, float offsetY);

	std::vector<sf::Vector2i> getNewDirections(sf::Vector2i lastDirection);
};

#endif