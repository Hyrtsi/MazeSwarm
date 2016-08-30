// MazeSwarm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "maze.hpp"
#include "robot.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "windows.h"

#define WINDOWWIDTH 800
#define WINDOWHEIGHT 600

//To do:
//float vs int with robot
//Advice Lehdari
//User controls for funs?
//What the robot sees?
//Aalto Multi-Robot Learning Experience A* (pun)
//cre8 to constructor of Maze


int main()
{

	Maze creationalgorithm(Maze maze);		//Forward declaration
	Maze myMaze(32, 32);
	sf::RenderWindow window(sf::VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "Hello mom!");

	myMaze.fillWithWalls();
	myMaze = creationalgorithm(myMaze);
	Robot robot(0, 0);



	// ¤¤¤¤¤¤¤¤¤¤¤
	//Just testing step by step...

	robot.solveMaze(myMaze);
	robot.solveMaze(myMaze);
	robot.solveMaze(myMaze);
	//robot.solveMaze(myMaze);
	//robot.solveMaze(myMaze);

	// ¤¤¤¤¤¤¤¤¤¤¤¤¤¤


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		myMaze.draw(window);
		robot.draw(window);
		//robot.solveMaze(myMaze);

		Sleep(30);				//Delay (probz ms)
		window.display();
	}

	return 0;
}


//Stash for goodies:

//for (auto& juttu : vektori) { juttu.teeJotain(); }