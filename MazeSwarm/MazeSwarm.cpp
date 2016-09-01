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

//Discriminating out-of-bounds squares from regular: maze -> operator; robot -> getNewDirections
//If it works, document it.

int main()
{

	Robot robot(0,0);

	Maze myMaze(32, 32);

	//いいいいいいい

	// Robotics:

	auto robotId1 = myMaze.addRobot(std::move(robot));

	//std::move is used to indicate that an object t may be "moved from", i.e. allowing the efficient transfer of resources from t to another object.
	//In C++11, in addition to copy constructors, objects can have move constructors.
	
	//Gogol: move semantics, rvalue, perfect forwarding.

	//Reference back to robot:
	auto& robotRef1 = myMaze.getRobot(robotId1);

	sf::RenderWindow window(sf::VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "Help! I'm trapped in a maze factory!");


	//Test test

	//Removewall and draw OK!
	//Again, check coordinate order for comfort reasons
	//>> robot directions are OK
	//>> robot moveDirection and robot moveOffset are OK

	//robotRef1.solveMaze();





	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		//robotRef1.rndMovement();


		window.clear();
		myMaze.draw(window);
		robotRef1.solveMaze();
		robotRef1.draw(window);

		Sleep(300);				//Delay (probz ms)
		window.display();
	}

	return 0;
}


//Stash for goodies:

//for (auto& juttu : vektori) { juttu.teeJotain(); }