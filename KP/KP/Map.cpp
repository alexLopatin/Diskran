#include "Map.h"


Map::Map(std::string filePath)
{
	std::ifstream* inFile = new std::ifstream(filePath);

	ValidateType(*inFile);
	GetSize(*inFile);

	_topology = new int* [_width];
	for (int i = 0; i < _width; i++)
		_topology[i] = new int[_height];

	ReadTopology(*inFile);

	delete inFile;
}

void Map::ValidateType(std::ifstream& stream)
{
	std::string header, value;
	stream >> header >> value;
	if (header == "type")
		if (value != "octile")
			throw(-2);
}

void Map::GetSize(std::ifstream& stream)
{
	std::string header;
	stream >> header >> _width;
	stream >> header >> _height;
}

void Map::ReadTopology(std::ifstream& stream)
{
	std::string header;
	stream >> header;
	if (header != "map")
		throw(-2);

	char val;

	for (int x = 0; x < _width; x++)
		for (int y = 0; y < _height; y++)
		{
			stream >> val;
			if (val == '\n')
				throw(-5);
			_topology[x][y] = (val == '.' || val == 'G');
		}
}

bool Map::CanPass(int x, int y)
{
	return _topology[x][y];
}

int Map::GetWidth()
{
	return _width;
}

int Map::GetHeight()
{
	return _height;
}

void Map::DrawMapWithPath(std::string filePath, std::vector<Point> path, Point start, Point end)
{
	std::ofstream* inFile = new std::ofstream(filePath, std::ofstream::trunc);

	*inFile << _width << " " << _height << '\n';

	for (unsigned int i = 0; i < path.size(); i++)
	{
		_topology[path[i].X][path[i].Y] = 2;
	}

	_topology[start.X][start.Y] = 3;
	_topology[end.X][end.Y] = 3;

	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			if(_topology[x][y] == 3)
				*inFile << '+';
			else
			if (_topology[x][y] == 2)
				*inFile << '6';
			else
				*inFile << (CanPass(x, y) ? '.' : '@');
		}
		*inFile << '\n';
	}
}