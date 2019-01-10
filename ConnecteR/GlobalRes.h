#pragma once
#include "Inclusion.h"
#include "Puzzle.h"
class GlobalRes
{
private:
	void clearMap();
public:
	RenderWindow window;
	pair<int, int> resolution;
	int Sz, ln, N, cl;
	string tex_lnk;
	vector<vector<Puzzle>> Field;
	vector<bool> relations;

	void loadMap(string link);
};