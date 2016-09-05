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

// *** To do: ***


//Map-maker
// > make a choice: editor or auto-cre8
//File type for mazes
//Test with some dummy mazes

//Output information about branches?


//VARIABLE AVAILABILITY
//>> wallThickness! pls



//Place a finish to a difficult location? Is the diagonal corner often difficult?
//Implement finish dynamics to solveMaze or similar

//Create one or many set of rules (return to beginning after finding finish etc)

// Multirobot, robot-to-robot data sharing = new solver approach (or upd8 existing)

//float vs int with robot (warnings)
//User controls for funs?
//What the robot sees?

//Possible uses for a robot swarm:
// > making a map of the terrain
// > finding a target located at a specific place (such as finish flag)
// > finding a moving target
// > estimating the width and height or other properties of the map

//Current restrictions and assumptions:
// > That the maze branches are not connected (fancy graph theory term here)
// > That there are no isolated branches
// > That there is one and only one route from point a to point b

//Note that the algorithm can be modified to pass these boundaries



//Discriminating out-of-bounds squares from regular: maze -> operator; robot -> getNewDirections
//If it works, document it.






int main()
{

	/*
	std::cout << "Enter true/false (1/0): ";
	bool userInput;
	std::cin >> userInput;

	if (userInput) {
		Maze shitMaze(64, 64);
		shitMaze.editor();
	}
	*/

	Robot robot(0,0);

	Maze myMaze(32, 32);

	//いいいいいいい

	// Robotics:

	auto robotId1 = myMaze.addRobot(std::move(robot));

	//std::move is used to indicate that an object t may be "moved from", i.e. allowing the efficient transfer of resources from t to another object.
	//In C++11, in addition to copy constructors, objects can have move constructors.
	
	//Gogol: move semantics, rvalue, perfect forwarding.

	auto& robotRef1 = myMaze.getRobot(robotId1);				//Reference back to robot

	sf::RenderWindow window(sf::VideoMode(WINDOWWIDTH, WINDOWHEIGHT), "Help! I'm trapped in a maze factory!");




	bool escapeEditor = false;				//To turn maze editing on/off. Assign to key?

	while (window.isOpen())
	{


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) escapeEditor = true;
		}


		window.clear();

		myMaze.draw(window);

		if (!escapeEditor) {
			myMaze.editor(event, window);
		}
		else if (escapeEditor) {
			robotRef1.solveMaze();
			robotRef1.draw(window);
		}

		Sleep(40);				//Delay (probz ms)
		window.display();

	}

	return 0;
}


//Stash for goodies:

//for (auto& juttu : vektori) { juttu.teeJotain(); }