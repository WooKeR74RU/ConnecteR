#pragma once
#include "Inclusion.h"
#include "GlobalRes.h"

namespace Menu
{
	int update(GlobalRes &res);

	void draw(GlobalRes &res);
	void activate(GlobalRes &res);
	void clear();
};