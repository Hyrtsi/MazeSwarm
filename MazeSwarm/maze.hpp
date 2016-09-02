#ifndef MAZE_HPP
#define MAZE_HPP


#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdint>
#include <time.h>

#include "robot.hpp"


struct Square {
	bool isWall = true;
	bool isFinish = false;
	Square(bool isWall = true, bool isFinish = false) : isWall(isWall), isFinish(isFinish) {}
};


class Maze {
public:
	struct DrawParameters {
		float		xOrigin = 10.0f;
		float		yOrigin = 10.0f;
		float		wallThickness = 5.0f;
		sf::Color	wallColor = sf::Color(25, 15, 25);
		sf::Color	nonWallColor = sf::Color(125, 25, 125);
	};


	Maze(uint64_t width, uint64_t height);

	const Square& operator()(uint64_t x, uint64_t y) const;

	uint64_t addRobot(Robot&& robot);
	Robot& getRobot(uint64_t robotId);
	const Robot& getRobot(uint64_t robotId) const;

	std::vector<sf::Vector2i> getNeighbors(sf::Vector2i location,
		std::vector<sf::Vector2i> unvisited);
	void creationalgorithm(void);

	void draw(sf::RenderWindow& window,
		const DrawParameters& drawParams = DrawParameters());
	const sf::Vector2i& getSize(void) const;
	bool isWall(uint64_t x, uint64_t y) const;

	void removeWall(uint64_t x, uint64_t y);		// am I useful?	Changed to uint64_t

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