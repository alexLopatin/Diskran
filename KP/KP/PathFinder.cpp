#include "PathFinder.h"
PathFinder::PathFinder(Map* map)
{
	_map = map;
	
	_parent = new Point * [_map->GetWidth()];
	for (int i = 0; i < _map->GetWidth(); i++)
		_parent[i] = new Point[_map->GetHeight()];
}

Point PathFinder::GetParent(Point child)
{
	return _parent[child.X][child.Y];
}

void PathFinder::SetParent(Point child, Point parent)
{
	_parent[child.X][child.Y] = parent;
}

std::vector<Point> PathFinder::GetPath(Point start, Point end)
{
	std::vector<Point> path(0);

	Point current = end;

	if (AStar(start, end))
	{
		do
		{
			path.push_back(current);
			current = GetParent(current);
		} while (!(current.X == start.X && current.Y == start.Y));
		path.push_back(current);
	}

	std::reverse(path.begin(), path.end());

	return path;
}

bool PathFinder::AStar(Point start, Point end)
{
	int** g = new int * [_map->GetWidth()];
	for (int i = 0; i < _map->GetWidth(); i++)
	{
		g[i] = new int[_map->GetHeight()];
		for (int j = 0; j < _map->GetHeight(); j++)
			g[i][j] = 1000 * 1000 * 1000;
	}
		

	bool** U = new bool* [_map->GetWidth()];
	for (int i = 0; i < _map->GetWidth(); i++)
	{
		U[i] = new bool[_map->GetHeight()];
		for (int j = 0; j < _map->GetHeight(); j++)
			U[i][j] = 0;
	}

	auto pushU = [&](Point p)
	{
		U[p.X][p.Y] = true;
	};

	auto existsU = [&](Point p)
	{
		return U[p.X][p.Y];
	};

	auto h = [&](Point p)
	{
		return std::max(std::abs(p.X - end.X), std::abs(p.Y - end.Y));
	};

	auto f = [&](Point p)
	{
		return g[p.X][p.Y] + h(p);
	};

	//std::priority_queue<std::pair<int, Point>> Q;
	std::vector< std::pair<int, Point> > Q;
	
	auto addOrUpdate = [&](Point p)
	{

		for(unsigned int i = 0; i < Q.size(); i++)
			if (p.X == Q[i].second.X && p.Y == Q[i].second.Y)
			{
				Q[i].first = f(p);
				std::make_heap(Q.begin(), Q.end());
				return;
			}

		Q.push_back(std::make_pair(f(p), p));
		std::push_heap(Q.begin(), Q.end());
	};
	
	auto metric = [](Point a, Point b)
	{
		return std::abs(a.X - b.X) + std::abs(a.Y - b.Y);
	};

	g[start.X][start.Y] = 0;
	addOrUpdate(start);

	bool succeded = 0;

	while (Q.size() != 0)
	{
		Point current = Q.front().second;
		if (current.X == end.X && current.Y == end.Y)
		{
			succeded = 1;
			break;
		}

		pushU(current);

		std::pop_heap(Q.begin(), Q.end());
		Q.pop_back();
		
		for(int x = std::max(current.X - 1, 0); x <= std::min(current.X + 1, _map->GetWidth() - 1); x++)
			for (int y = std::max(current.Y - 1, 0); y <= std::min(current.Y + 1, _map->GetHeight() - 1); y++)
			{
				Point v = { x,y };

				if ((current.X == x && current.Y == y) || !_map->CanPass(x, y))
					continue;

				int tentativeScore = g[current.X][current.Y] + 1;
				if (tentativeScore < g[x][y])
				{
					SetParent(v, current);
					g[x][y] = tentativeScore;
					addOrUpdate(v);
				}
			}
	}

	for (int i = 0; i < _map->GetWidth(); i++)
		delete g[i];
	delete g;

	for (int i = 0; i < _map->GetWidth(); i++)
		delete U[i];
	delete U;

	return succeded;
}