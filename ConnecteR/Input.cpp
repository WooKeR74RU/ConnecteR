#include "Input.h"

int Input::pressed()
{
	static unsigned int reloadLbm = 0;
	static bool reloadRbm = 0;
	static bool grip = 0;

	if (Mouse::isButtonPressed(Mouse::Left))
	{
		reloadLbm++;
		if (reloadLbm == 750)
		{
			grip = 1;
			return 3;
		}
	}
	else
	{
		if (!grip)
		{
			if (reloadLbm)
			{
				reloadLbm = 0;
				return 1;
			}
		}
		else
		{
			reloadLbm = 0;
			grip = 0;
		}
	}

	if (Mouse::isButtonPressed(Mouse::Right))
		reloadRbm = 1;
	else
	{
		if (reloadRbm)
		{
			reloadRbm = 0;
			return 2;
		}
	}

	return 0;
}
pair<int, int> Input::selected(GlobalRes &res)
{
	for (int i = 0; i < res.N; i++)
		for (int j = 0; j < res.N; j++)
			if (res.Field[i][j].getRect().contains(Mouse::getPosition(res.window)))
				return make_pair(i, j);
	return make_pair(-1, -1);
}