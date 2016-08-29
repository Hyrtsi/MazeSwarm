#ifndef MAZE_HPP
#define MAZE_HPP
#include <SFML/Graphics.hpp>
#include "square.hpp"

class Maze {

public:
	int _shit = 777;					//TEST
	std::vector<std::vector<class Square>> _squares;

	Maze(int width, int height);
	void Maze::draw(sf::RenderWindow& window, std::vector<std::vector<class Square>> _squares);
	sf::Vector2i getSize(void);
private:
	int _width, _height;
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