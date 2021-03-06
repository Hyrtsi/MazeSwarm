#include "stdafx.h"
#include "maze.hpp"
#include <iostream>
#include <algorithm>

int height = 32, width = 32;		//Future: get these from a maze function...

std::vector<sf::Vector2i> getNeighbors(sf::Vector2i location, std::vector<sf::Vector2i> unvisited) {
	
	std::vector<sf::Vector2i> neighbors;
	std::vector<sf::Vector2i> unvNeighbors;

	//Returns the neighbor cells for a desired location.

	if (location.x >= 2) neighbors.push_back(sf::Vector2i{ location.x - 2, location.y });
	if (location.y >= 2) neighbors.push_back(sf::Vector2i{ location.x, location.y - 2 });
	if (location.y <= height - 3) neighbors.push_back(sf::Vector2i{ location.x, location.y + 2 });	//Check?
	if (location.x <= width - 3) neighbors.push_back(sf::Vector2i{ location.x + 2, location.y });		//Check?

	for (auto& neighbor : neighbors) {
		if (std::find(unvisited.begin(), unvisited.end(), neighbor) != unvisited.end()) {					//if neighbor in unvisited
			unvNeighbors.push_back(neighbor);
		}
	}

	return unvNeighbors;
}


Maze creationalgorithm(Maze maze) {

	//Only accepts even x even mazes?
	//Fix this or not?
	//This is recursive backtracker algorithm.

	sf::Vector2i rndNeighbor;
	std::vector<sf::Vector2i> unvNeighbors;
	std::vector<sf::Vector2i> unvisited;
	std::vector<sf::Vector2i> stack;
	sf::Vector2i current;
	sf::Vector2i initialCell = { 0,0 };
	int mean_x = 0;
	int mean_y = 0;

	for (int i = 0; i < height/2; i++) {
		for (int j = 0; j < width/2; j++) {
			unvisited.push_back(sf::Vector2i{ 2 * i,2 * j });
		}
	}		//Note: unvisited consists of (0,0), (0,2), (0,4), ..., (2,0),..

	//Make the initial cell the current cell and mark it as visited

	current = initialCell;

	while (unvisited.size() > 0) {

		maze.removeWall(current.x, current.y);
		unvisited.erase(std::remove(unvisited.begin(), unvisited.end(), current), unvisited.end());		//erease-remove idiom

		unvNeighbors = getNeighbors(current, unvisited);
		
		//Now, unvNeighbors should contain neighbors for "current" that are unvisited

		if (!unvNeighbors.empty()) {						//If the current cell has any neighbours which have not been visited:
			//Choose randomly one of the unvisited neighbours
			int RandIndex = rand() % unvNeighbors.size();		//Number between 0 and nNeighbors-1 (?)
			rndNeighbor = unvNeighbors[RandIndex];
			stack.push_back(current);							//Push the current cell to the stack

			//Remove the wall between the current cell and the chosen cell

			mean_x = (current.x + rndNeighbor.x) / 2;
			mean_y = (current.y + rndNeighbor.y) / 2;
			//maze._squares[mean_x][mean_y].isWall = false;					//x y or y x?
			maze.removeWall(mean_x, mean_y);

			//Make the chosen cell the current cell and mark it as visited
			current = rndNeighbor;

		}
		else if (!stack.empty()) {
			//Pop a cell from the stack
			//Make it the current cell

			current = stack.back();
			stack.pop_back();
		}
	}
	return maze;
}