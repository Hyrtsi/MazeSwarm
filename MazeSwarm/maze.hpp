#ifndef MAZE_HPP
#define MAZE_HPP


#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdint>

#include "robot.hpp"


struct Square {
	bool isWall		= false;
	bool isFinish	= false;
};


class Maze {
public:
	struct DrawParameters {
		float		xOrigin					= 10.0f;
		float		yOrigin					= 10.0f;
		float		wallThickness			= 5.0f;
		sf::Color	wallColor				(100, 5, 25);
		sf::Color	nonWallColor			(200, 100, 250);
	};

	Maze(uint64_t width, uint64_t height);

	const Square& operator()(uint64_t x, uint64_t y) const;	//	const in the end of a member function means that this member cannot modify the state of the object and therefore can be called for const objects

	//	return robot id
	uint64_t addRobot(Robot&& robot);	// && whaa? google "rvalue reference". essentially rips Robot object out of the scope it was created and transfers it into this meber function
	Robot& getRobot(uint64_t robotId);
	const Robot& getRobot(uint64_t robotId) const;

	void draw(sf::RenderWindow& window,
	          const DrawParameters& drawParams = DrawParameters());
	const sf::Vector2i& getSize(void) const;
	bool isWall(uint64_t x, uint64_t y) const;

private:
	sf::Vector2i						_size;
	std::vector<std::vector<Square>>	_squares;

	std::vector<Robot>					_robots;
};


#endif


/*
template <typename T>
using Vector2D = std::vector<std::vector<T>>;

Vector2D<int> vectorception;	//example

const unsigned xSize = 10;
const unsigned ySize = 20;
Vector2D<MSDT> vception(xSize, std::vector<MSDT>(ySize));
*/