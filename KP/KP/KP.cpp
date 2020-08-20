#include <iostream>
#include "Map.h"
#include "PathFinder.h"

int main(int argc, const char* argv[])
{
	if (argc < 6)
		return -1;

	Point start = { atoi(argv[2]), atoi(argv[3]) };
	Point end = { atoi(argv[4]), atoi(argv[5]) };

	Map* map = new Map(argv[1]);
	PathFinder* pathFinder = new PathFinder(map);

	std::cout << "Trying to find path between (" 
		<< start.X << " " <<start.Y << ") and ("
		<< end.X << " " << end.Y << ")...\n";
	auto path = pathFinder->GetPath(start, end);

	if (path.size() == 0)
		std::cout << "No path generated.\n";
	else
	{
		std::cout << "Created path with " << path.size() << " nodes.\n";

		map->DrawMapWithPath("out.map", path, start, end);
		std::cout << "Succesfully written to out.map\n";
	}

	delete pathFinder;
	delete map;
}