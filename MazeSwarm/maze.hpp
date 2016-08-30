#ifndef MAZE_HPP
#define MAZE_HPP
#include <SFML/Graphics.hpp>
#include "square.hpp"

class Maze {

public:
	Maze(int width, int height);
	void Maze::draw(sf::RenderWindow& window);
	sf::Vector2i Maze::getSize(void);
	bool Maze::isWall(int x, int y);
	void Maze::removeWall(int x, int y);
	void Maze::fillWithWalls(void);
private:
	int _width, _height;
	std::vector<std::vector<class Square>> _squares;
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