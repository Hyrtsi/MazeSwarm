#include "stdafx.h"
#include "maze.hpp"
#include <iostream>
#include <vector>

//For _squares, [y][x] is the order.

Maze::Maze(int width, int height) {

	_width = width;
	_height = height;
	_shit = 666;		//TEST

	Square initSquare;
	initSquare.isWall = true;			//We want to init the maze with walls for the alg that does carving.
	static std::vector<std::vector<class Square>> _squares (width, std::vector<class Square>(height, initSquare));		//Use typedef?

	_shit++;			//Test

	//std::cout << "paska " << _squares[1][2].isWall << std::endl; //Test, runs OK!


	/*
	for (int j = 0; j < _height; j++) {
		for (int i = 0; i < _width; i++) {
			_squares[i][j] = initSquare;
		}
	}		//Loop OK!

	//##############################
	// OR:

	Square mysquare;
	mysquare.isWall = true;

	std::vector<class Square> v1;
	for (int i = 0; i < _width; i++) v1.push_back(mysquare);			//size = 6 itc OK

	std::vector<std::vector<class Square>> v2;
	for (int i = 0; i < _height; i++) v2.push_back(v1);					//OK

	_squares = v2;
	*/
}



//Or:

//Maze::Maze (int width, int height) : _width(width), _height(height) { }

sf::Vector2i getSize(void) {
	//Returns the width and height of the maze.
	//Does not do shit.
	//sf::Vector2i sizeVector(_width, _height);
	sf::Vector2i sizeVector;
	return(sizeVector);
}

void Maze::draw(sf::RenderWindow& window, std::vector<std::vector<class Square>> _squares) {
	
	float x = 0.0f, y = 0.0f,
		initVector_x = 10.0f, initVector_y = 10.0f,
		wallThickness = 5.0f;

	//std::cout << "paska " << _shit << std::endl;		//TEST

	//std::cout << "paska " << _squares[1][2].isFinish << std::endl;		//¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤

	//std::cout << "sq " << _squares.size() << std::endl;


	for (int j = 0; j < _height; j++) {
		x = 0.0f;
		for (int i = 0; i < _width; i++) {
			Square square = _squares[j][i];		//Fill order?
			//std::cout << "Current square: " << square.isWall << std::endl;

			sf::RectangleShape tile(sf::Vector2f(wallThickness, wallThickness));
			if (square.isWall) {
				tile.setFillColor(sf::Color(100, 5, 25));

			}
			else if (!square.isWall) {
				tile.setFillColor(sf::Color(200, 100, 250));
			}
			tile.setPosition(initVector_x + x, initVector_y + y);
			window.draw(tile);
			x += wallThickness;
		}
		y += wallThickness;
	}			//This seems OK, passed one test



	/*
	if (_squares[0][0].isWall) {
	sf::RectangleShape tile(sf::Vector2f(wallThickness, wallThickness));
	tile.setFillColor(sf::Color(50, 50, 250));
	tile.setPosition(initVector_x + x, initVector_y + y);
	window.draw(tile);
	}
	*/
}




/*


sf::Vector2i data{ 20, 20 };
sf::Vector3i foo{ 1,1,1 };

std::vector<std::vector<int>> vectorception;
std::vector<std::vector<std::vector<int>>> vector3;

//std::cout << mysquare.isWall;
//mysquare.isWall = true;
//std::cout << mysquare.isWall;




std::vector<class Square> vtest;
std::vector<std::vector<std::vector<class Square>>> maze;
std::vector<int>(3, 6);		//=={6,6,6}
std::vector<std::vector<int>>(100, std::vector<int>(100, 60));
std::vector<class Square>(100, Square());	//square has no constructor arguments

*/