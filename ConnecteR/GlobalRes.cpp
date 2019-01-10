#include "GlobalRes.h"

int push(vector<int> &Rand)
{
	while (1)
	{
		int adr = rand() % Rand.size();
		if (!Rand[adr])
			continue;
		else
		{
			Rand[adr]--;
			return adr;
		}
	}
}

void GlobalRes::loadMap(string link)
{
	clearMap();
	ifstream fin;
	fin.open(link);
	fin >> N;

	switch (N)
	{
	case 3:
		cl = 3;
		Sz = 216;
		ln = 27;
		tex_lnk = "216pix";
		break;
	case 4:
		cl = 3;
		Sz = 160;
		ln = 30;
		tex_lnk = "160pix";
		break;
	case 5:
		cl = 2;
		Sz = 134;
		ln = 17;
		tex_lnk = "134pix";
		break;
	default:
		cl = 2;
		Sz = 134;
		ln = 17;
		tex_lnk = "134pix";
	}

	vector<int> Rand(5);
	for (int i = 0; i < 5; i++)
		fin >> Rand[i];
	relations.clear();
	relations.resize(N * 4);
	int n, tmp;
	fin >> n;
	for (int i = 0; i < n; i++)
	{
		fin >> tmp;
		relations[tmp] = 1;
	}
	Field.clear();
	Field.resize(N, vector<Puzzle>(N));
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			int x, y, left = resolution.first - resolution.second;
			x = left + ln + j * Sz + (j + 2) * cl;
			y = ln + i * Sz + (i + 2) * cl;
			Field[i][j].setOptions(push(Rand), x, y, Sz, rand() % 4, tex_lnk);
		}
	}
	fin.close();
}

void GlobalRes::clearMap()
{
	N = 0;
	Field.clear();
	relations.clear();
}