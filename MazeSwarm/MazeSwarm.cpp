// MazeSwarm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "maze.hpp"
#include "robot.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "windows.h"

//Use local, extern to share _square to every function?
//Static?

int main()
{
	


	Maze creationalgorithm(Maze maze);		//Forward declaration

	sf::RenderWindow window(sf::VideoMode(400, 400), "Hello mom!");

	Maze myMaze(32, 32);





	// ¤¤¤¤¤¤¤¤¤ Piece of shitty code

	Square initSquare;
	initSquare.isWall = true;			//We want to init the maze with walls for the alg that does carving.
	
	std::vector<class Square> v1;
	for (int i = 0; i < 32; i++) v1.push_back(initSquare);

	std::vector<std::vector<class Square>> v2;
	for (int i = 0; i < 32; i++) v2.push_back(v1);

	myMaze._squares = v2;

	// ¤¤¤¤¤¤¤¤ End of shitty code


	//std::cout << "paskafff " << myMaze._squares.size() << std::endl;

	myMaze = creationalgorithm(myMaze); //TEST
	Robot robot(0, 0, myMaze);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		//std::cout << "paska" << myMaze._shit << std::endl;

		//std::cout << "paska" << myMaze._squares[1][2].isWall << std::endl;

		window.clear();
		myMaze.draw(window, myMaze._squares);
		robot.draw(window);

		robot.rndMovement();
		Sleep(30);
		window.display();
	}

	return 0;
}


//Stash for goodies:

//for (auto& juttu : vektori) { juttu.teeJotain(); }

/*
sf::Vector2i c1{ 0,0 };
sf::Vector2i c2{ 1, 2 };

std::vector<sf::Vector2i> list;

list.push_back(c1);
list.push_back(c2);

*/