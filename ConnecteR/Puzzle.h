#pragma once
#include "Inclusion.h"

class Puzzle
{
private:
	Sprite body;
	Texture pict, pictSel;
	string tex_lnk;
	int Sz;
	IntRect rect;
	int type;
	int rotateStep;
	bool selected;
	void setTexture(string link);
public:
	void setOptions(int _type, int x, int y, int _Sz, int rtSt, string &_tex_lnk);
	void setType(int _type);
	void setRotateStep(int step);
	Sprite getSprite();
	IntRect getRect();
	int getType();
	int getRotateStep();
	void rotateNext();
	void rotatePrev();
	void select();
};

void swap(Puzzle &a, Puzzle &b);