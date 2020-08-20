#pragma once
#include <vector>
struct Point
{
	int X;
	int Y;
};

constexpr bool operator<(const std::pair<int, Point>& _Left, const std::pair<int, Point>& _Right) {
	return _Left.first > _Right.first;
}