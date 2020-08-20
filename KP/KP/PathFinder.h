#pragma once
#include "Map.h"
#include <vector>
#include <queue>
#include "Point.h"

class PathFinder
{
	Map* _map;
	bool AStar(Point start, Point end);
	Point GetParent(Point child);
	void SetParent(Point child, Point parent);
	Point** _parent;
public:
	PathFinder(Map* map);
	std::vector<Point> GetPath(Point start, Point end);
};

