#include "Game.h"

vector<vector<pair<int, int>>> desk;

pair<int, int> town(int n)
{
	int sz = desk.size() - 2;
	if (n < sz)
		return make_pair(0, n + 1);
	if (n >= sz && n < 2 * sz)
		return make_pair(n + 1 - sz, desk.size() - 1);
	if (n >= 2 * sz && n < 3 * sz)
		return make_pair(desk.size() - 1, 3 * sz - n);
	if (n >= 3 * sz)
		return make_pair(4 * sz - n, 0);
}
int town(const pair<int, int> &n)
{
	int sz = desk.size() - 2;
	if (n.first == 0)
		return n.second;
	if (n.second == desk.size() - 1)
		return n.first + sz;
	if (n.first == desk.size() - 1)
		return 2 * sz - n.second;
	if (n.second == 0)
		return 3 * sz - n.first;
}

bool onField(int x, int y)
{
	if (x >= 0 && x < desk.size() && y >= 0 && y < desk.size())
		return 1;
	return 0;
}

vector<vector<vector<bool>>> ways;

bool trans(int x, int y, int way)
{
	if (ways[desk[x][y].first][desk[x][y].second][way])
		return 1;
	return 0;
}

unsigned int timer = 0;
vector<vector<int>> used;

void dfs(int x, int y)
{
	used[x][y] = timer;
	if (trans(x, y, 0))
		if (onField(x - 1, y) && used[x - 1][y] != timer)
			dfs(x - 1, y);
	if (trans(x, y, 1))
		if (onField(x, y + 1) && used[x][y + 1] != timer)
			dfs(x, y + 1);
	if (trans(x, y, 2))
		if (onField(x + 1, y) && used[x + 1][y] != timer)
			dfs(x + 1, y);
	if (trans(x, y, 3))
		if (onField(x, y - 1) && used[x][y - 1] != timer)
			dfs(x, y - 1);
}

vector<Sprite> towns;
Texture* town_on;
Texture* town_off;

bool ñheckOnce = 0;

int check(GlobalRes &res)
{
	if (!ñheckOnce)
	{
		ñheckOnce = 1;
		used.resize(res.N + 2, vector<int>(res.N + 2));
		desk.resize(res.N + 2, vector<pair<int, int>>(res.N + 2));
		for (int i = 0; i < res.N * 4; i++)
		{
			pair<int, int> tmp = town(i);
			if (i < res.N || i >= 2 * res.N && i < 3 * res.N)
				desk[tmp.first][tmp.second] = make_pair(1, 1);
			if (i >= 3 * res.N || i >= res.N && i < 2 * res.N)
				desk[tmp.first][tmp.second] = make_pair(1, 0);
		}

		towns.resize(4 * res.N);
		town_on = new Texture();
		town_on->loadFromFile("textures/" + res.tex_lnk + "/town-on.jpg");
		town_off = new Texture();
		town_off->loadFromFile("textures/" + res.tex_lnk + "/town-off.jpg");
		for (int i = 0; i < 4 * res.N; i++)
		{
			pair<int, int> tmp = town(i);
			int x, y, left = res.resolution.first - res.resolution.second;
			if (tmp.first == 0)
			{
				towns[i].rotate(180);
				x = left + res.ln + tmp.second * res.Sz + (tmp.second + 1) * res.cl;
				y = res.ln + res.cl;
			}
			if (tmp.first == res.N + 1)
			{
				x = left + res.ln + (tmp.second - 1) * res.Sz + (tmp.second + 1) * res.cl;
				y = res.ln + res.N * res.Sz + (res.N + 2) * res.cl;
			}
			if (tmp.second == 0)
			{
				towns[i].rotate(90);
				x = left + res.cl + res.ln;
				y = res.ln + (tmp.first - 1) * res.Sz + (tmp.first + 1) * res.cl;
			}
			if (tmp.second == res.N + 1)
			{
				towns[i].rotate(270);
				x = left + res.ln + res.N * res.Sz + (res.N + 2) * res.cl;
				y = res.ln + tmp.first * res.Sz + (tmp.first + 1) * res.cl;
			}
			towns[i].setPosition(x, y);
			if (res.relations[i])
				towns[i].setTexture(*town_on);
			else
				towns[i].setTexture(*town_off);
		}
	}
	for (int i = 0; i < res.N; i++)
		for (int j = 0; j < res.N; j++)
			desk[i + 1][j + 1] = make_pair(res.Field[i][j].getType(), res.Field[i][j].getRotateStep());
	for (int i = 1; i < res.N + 1; i++)
	{
		for (int j = 1; j < res.N + 1; j++)
		{
			if (trans(i, j, 0))
				if (!trans(i - 1, j, 2))
					return 1;
			if (trans(i, j, 1))
				if (!trans(i, j + 1, 3))
					return 1;
			if (trans(i, j, 2))
				if (!trans(i + 1, j, 0))
					return 1;
			if (trans(i, j, 3))
				if (!trans(i, j - 1, 1))
					return 1;
		}
	}
	for (int i = 0; i < res.relations.size(); i++)
	{
		if (res.relations[i])
		{
			pair<int, int> tmp = town(i);
			timer++;
			dfs(tmp.first, tmp.second);
			break;
		}
	}
	for (int i = 0; i < res.N * 4; i++)
	{
		pair<int, int> tmp = town(i);
		if (res.relations[i])
		{
			if (used[tmp.first][tmp.second] != timer)
				return 1;
		}
		else
		{
			if (used[tmp.first][tmp.second] == timer)
				return 1;
		}
	}
	return 2;
}

bool outside(int x, int y)
{
	if (x == 0 || y == 0 || x == desk.size() - 1 || y == desk.size() - 1)
		return 1;
	return 0;
}

void Game::taskGen(GlobalRes &res, int N)
{
	res.N = N;

	ofstream fout;
	fout.open("maps/gen.txt");

	Game::clear();
	desk.resize(res.N + 2, vector<pair<int, int>>(res.N + 2));
	used.resize(res.N + 2, vector<int>(res.N + 2));
	vector<vector<vector<bool>>> require(res.N + 2, vector<vector<bool>>(res.N + 2, vector<bool>(4)));
	vector<vector<vector<bool>>> notRequire(res.N + 2, vector<vector<bool>>(res.N + 2, vector<bool>(4)));

	for (int x = 1; x < require.size() - 1; x++)
	{
		for (int y = 1; y < require.size() - 1; y++)
		{
			vector<vector<int>> options(5);
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					bool cancel = 0;
					for (int k = 0; k < 4; k++)
					{
						if (require[x][y][k] && !ways[i][j][k] || notRequire[x][y][k] && ways[i][j][k])
						{
							cancel = 1;
							break;
						}
					}
					if (!cancel)
					{
						options[i].push_back(j);
					}
				}
			}

			int rnd;
			do
				rnd = rand() % 5;
			while (options[rnd].empty());

			desk[x][y] = make_pair(rnd, options[rnd][rand() % options[rnd].size()]);

			if (!outside(x - 1, y))
			{
				if (trans(x, y, 0))
					require[x - 1][y][2] = 1;
				else
					notRequire[x - 1][y][2] = 1;
			}
			if (!outside(x, y + 1))
			{
				if (trans(x, y, 1))
					require[x][y + 1][3] = 1;
				else
					notRequire[x][y + 1][3] = 1;
			}
			if (!outside(x + 1, y))
			{
				if (trans(x, y, 2))
					require[x + 1][y][0] = 1;
				else
					notRequire[x + 1][y][0] = 1;
			}
			if (!outside(x, y - 1))
			{
				if (trans(x, y, 3))
					require[x][y - 1][1] = 1;
				else
					notRequire[x][y - 1][1] = 1;
			}
		}
	}

	vector<int> chips(5), relations, topRel;
	for (int x = 1; x < desk.size() - 1; x++)
	{
		for (int y = 1; y < desk.size() - 1; y++)
		{
			chips[desk[x][y].first]++;
			if (used[x][y])
				continue;
			timer++;
			dfs(x, y);
			relations.clear();
			for (int i = 0; i < 4 * res.N; i++)
			{
				pair<int, int> tmp = town(i);
				if (used[tmp.first][tmp.second] == timer)
					relations.push_back(i);
			}
			if (relations.size() > topRel.size())
				topRel = relations;
		}
	}

	fout << res.N << endl;
	for (int i = 0; i < 5; i++)
		fout << chips[i] << ' ';
	fout << endl << topRel.size() << endl;
	for (int i = 0; i < topRel.size(); i++)
		fout << topRel[i] << ' ';
	fout << endl << endl;
	for (int i = 1; i < desk.size() - 1; i++)
	{
		for (int j = 1; j < desk.size() - 1; j++)
			fout << "(" << desk[i][j].first << ", " << desk[i][j].second << ") ";
		fout << endl;
	}
}

int Game::update(GlobalRes &res)
{
	static pair<int, int> select, swapped;
	static bool selected = 0;
	static int pressType;

	pressType = Input::pressed();
	if (pressType)
	{
		select = Input::selected(res);
		if (select == make_pair(-1, -1))
			return 1;
	}
	if (!selected)
	{
		if (pressType == 1)
			res.Field[select.first][select.second].rotateNext();
		if (pressType == 2)
			res.Field[select.first][select.second].rotatePrev();
		if (pressType == 3)
		{
			swapped = select;
			res.Field[swapped.first][swapped.second].select();
			selected = 1;
		}
	}
	else
	{
		if (pressType == 1 || pressType == 3)
		{
			swap(res.Field[swapped.first][swapped.second], res.Field[select.first][select.second]);
			res.Field[swapped.first][swapped.second].select();
			selected = 0;
		}
	}
	return check(res);
}

void Game::draw(GlobalRes &res)
{
	for (int i = 0; i < res.Field.size(); i++)
		for (int j = 0; j < res.Field.size(); j++)
			res.window.draw(res.Field[i][j].getSprite());
	for (int i = 0; i < 4 * res.N; i++)
		res.window.draw(towns[i]);
}

void Game::activate(GlobalRes &res)
{
	ways.resize(5, vector<vector<bool>>(4, vector<bool>(4)));
	{
		//Line
		ways[1][0][1] = 1;
		ways[1][0][3] = 1;
		ways[1][1][0] = 1;
		ways[1][1][2] = 1;
		ways[1][2][1] = 1;
		ways[1][2][3] = 1;
		ways[1][3][0] = 1;
		ways[1][3][2] = 1;
		//Line

		//Turn
		ways[2][0][1] = 1;
		ways[2][0][2] = 1;
		ways[2][1][2] = 1;
		ways[2][1][3] = 1;
		ways[2][2][3] = 1;
		ways[2][2][0] = 1;
		ways[2][3][0] = 1;
		ways[2][3][1] = 1;
		//Turn

		//Fork
		ways[3][0][3] = 1;
		ways[3][0][0] = 1;
		ways[3][0][1] = 1;
		ways[3][1][0] = 1;
		ways[3][1][1] = 1;
		ways[3][1][2] = 1;
		ways[3][2][1] = 1;
		ways[3][2][2] = 1;
		ways[3][2][3] = 1;
		ways[3][3][2] = 1;
		ways[3][3][3] = 1;
		ways[3][3][0] = 1;
		//Fork

		//Cross
		ways[4][0][0] = 1;
		ways[4][0][1] = 1;
		ways[4][0][2] = 1;
		ways[4][0][3] = 1;
		ways[4][1][0] = 1;
		ways[4][1][1] = 1;
		ways[4][1][2] = 1;
		ways[4][1][3] = 1;
		ways[4][2][0] = 1;
		ways[4][2][1] = 1;
		ways[4][2][2] = 1;
		ways[4][2][3] = 1;
		ways[4][3][0] = 1;
		ways[4][3][1] = 1;
		ways[4][3][2] = 1;
		ways[4][3][3] = 1;
		//Cross
	}
}

void Game::clear()
{
	used.clear();
	timer = 0;
	desk.clear();
	towns.clear();
	ñheckOnce = 0;
}