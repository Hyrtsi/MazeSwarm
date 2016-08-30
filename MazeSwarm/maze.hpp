#ifndef MAZE_HPP
#define MAZE_HPP


#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdint>

#include "robot.hpp"


struct Square {
	bool isWall = true;
	bool isFinish = false;
};


class Maze {
public:
	struct DrawParameters {
		float		xOrigin = 10.0f;
		float		yOrigin = 10.0f;
		float		wallThickness = 5.0f;
		sf::Color	wallColor = sf::Color(255, 5, 100);
		sf::Color	nonWallColor = sf::Color(100, 50, 50);
	};


	Maze(uint64_t width, uint64_t height);

	const Square& operator()(uint64_t x, uint64_t y) const;

	uint64_t addRobot(Robot&& robot);
	Robot& getRobot(uint64_t robotId);
	const Robot& getRobot(uint64_t robotId) const;

	void draw(sf::RenderWindow& window,
		const DrawParameters& drawParams = DrawParameters());
	const sf::Vector2i& getSize(void) const;
	bool isWall(uint64_t x, uint64_t y) const;

	void removeWall(int x, int y);		// am I useful?	Change to uint64_t ???
	//void fillWithWalls(void);			// am I useful?

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