#pragma once
#include "Inclusion.h"
#include "GlobalRes.h"
#include "Puzzle.h"
#include "Input.h"

namespace Game
{
	int update(GlobalRes &res);
	void taskGen(GlobalRes &res, int N);

	void draw(GlobalRes &res);
	void activate(GlobalRes &res);
	void clear();
}