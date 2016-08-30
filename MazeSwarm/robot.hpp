#ifndef ROBOT_HPP
#define ROBOT_HPP

#include <SFML/Graphics.hpp>


class Maze;		//	Forward declaration for member pointer


class Robot {
public:
	friend class Maze;	//	Allow Maze access to private members so it can assign itself to _maze pointer

	Robot(float x, float y, float xOrigin = 10.0f, float yOrigin = 10.0f,
	      float radius = 2.5f, const sf::Vector2i& direction = sf::Vector2i(0, 0));
	
	void draw(sf::RenderWindow& window) const;
	void rndMovement(void);									//Mostly useless (For testing drunkard behavior)
	void moveTest(void);
	void solveMaze(void);

private:
	enum State {							//Used to describe the current action. Yes-yes or no-no?
		STATE_INIT,
		STATE_MOVING,
		STATE_SPLIT,
		STATE_FINISH,
		STATE_WAIT
	};

	const Maze*		_maze;
	float			_x;
	float			_y;

	float			_xOrigin;
	float			_yOrigin;
	float			_radius;

	sf::Vector2i	_direction{ 0, 0 };							//Direction is really {x,y}
	State			_state;

	sf::CircleShape circle;

	static const std::vector<sf::Vector2i>	__directions;

	bool facingWall(void);
	void moveDirection(const sf::Vector2i& direction);
	void moveOffset(float offsetX, float offsetY);

	std::vector<sf::Vector2i> getNewDirections(const sf::Vector2i& lastDirection);
};

#endif