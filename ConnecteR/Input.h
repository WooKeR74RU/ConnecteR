#pragma once
#include "Inclusion.h"
#include "GlobalRes.h"

namespace Input
{
	int pressed();
	pair<int, int> getTileUnderCursor(GlobalRes &res);
}