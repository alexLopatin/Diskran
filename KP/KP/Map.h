#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <tuple>
#include <vector>
#include "Point.h"
class Map
{
	void ValidateType(std::ifstream& stream);
	void GetSize(std::ifstream& stream);
	void ReadTopology(std::ifstream& stream);
	int** _topology;
	int _width;
	int _height;
public:
	int GetWidth();
	int GetHeight();
	Map(std::string filePath);
	bool CanPass(int x, int y);
	void DrawMapWithPath(std::string filePath, std::vector<Point> path, Point start, Point end);
	~Map()
	{
		for (int i = 0; i < GetWidth(); i++)
			delete _topology[i];
		delete _topology;
	}
};

