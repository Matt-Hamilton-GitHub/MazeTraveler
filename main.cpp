
#include <iostream>
#include <cmath>

#include <vector>
using namespace std;

const int worldsize = 8;
const int neighbors = 4;
enum Type{B,O,D,U,V};

Type world[worldsize][worldsize] = 
	{ 
		{B,B,B,U,B,U,B,U},
		{O,U,U,U,B,U,U,U}, 
		{B,B,B,U,B,U,B,U}, 
		{B,B,B,U,B,U,B,U}, 
		{B,U,U,U,B,U,B,U},
		{U,U,B,B,B,U,B,D},
		{B,U,B,U,B,U,B,B},
		{B,U,U,U,U,U,B,B} 
	};

struct Location
{
	int row, col;
};
bool travel(Location location, vector<Location>& path)
{
	static int drow[]{ 0,-1, 0, 1 };
	static int dcol[]{ 1, 0,-1, 0 };

	int row = location.row;
	int col = location.col;
	if (row < 0 || col < 0 ||
		worldsize <= row || worldsize <= col ||
		world[row][col] == B ||	world[row][col] == V)
		return false;

	if (world[row][col] == D)
	{
		world[row][col] = V;
		path.push_back(location);
		return true;
	}

	world[row][col] = V;
	path.push_back(location);

	for (int n = 0; n < neighbors; ++n)
	{
		Location newlocation;
		newlocation.row = row + drow[n];
	    newlocation.col = col + dcol[n];
		if (travel(newlocation, path))
			return true;
	}
	path.pop_back();
	return false;
}
int main()
{
	vector<Location> path;
	Location origin;
	origin.row = 1;
	origin.col = 0;
	if (travel(origin, path))
	{
		cout << path.size() << " steps from origin to destination" << endl;
		for (int idx = 0; idx < path.size() - 1; ++idx)
			cout << '(' << path[idx].row << ',' << path[idx].col << ")->" << endl;
		cout << '(' << path[path.size() - 1].row << ',' << path[path.size() - 1].col << ')' << endl;
	}
	else
		cout << "A path from the origin to the destination does not exist" << endl;
}    