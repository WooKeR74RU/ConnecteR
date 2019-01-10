#include "Puzzle.h"

void Puzzle::rotateNext()
{
	body.rotate(90);
	if (rotateStep == 0)
		body.setPosition(body.getPosition().x + Sz, body.getPosition().y);
	if (rotateStep == 1)
		body.setPosition(body.getPosition().x, body.getPosition().y + Sz);
	if (rotateStep == 2)
		body.setPosition(body.getPosition().x - Sz, body.getPosition().y);
	if (rotateStep == 3)
		body.setPosition(body.getPosition().x, body.getPosition().y - Sz);
	rotateStep++;
	if (rotateStep > 3)
		rotateStep = 0;
}
void Puzzle::rotatePrev()
{
	body.rotate(-90);
	if (rotateStep == 0)
		body.setPosition(body.getPosition().x, body.getPosition().y + Sz);
	if (rotateStep == 1)
		body.setPosition(body.getPosition().x - Sz, body.getPosition().y);
	if (rotateStep == 2)
		body.setPosition(body.getPosition().x, body.getPosition().y - Sz);
	if (rotateStep == 3)
		body.setPosition(body.getPosition().x + Sz, body.getPosition().y);
	rotateStep--;
	if (rotateStep < 0)
		rotateStep = 3;
}
void Puzzle::select()
{
	if (selected)
		body.setTexture(pict);
	else
		body.setTexture(pictSel);
	selected = !selected;
}
void Puzzle::setRotateStep(int step)
{
	while (rotateStep != step)
		rotateNext();
}
void Puzzle::setOptions(int _type, int x, int y, int _Sz, int rtSt, string &_tex_lnk)
{
	Sz = _Sz;
	tex_lnk = _tex_lnk;
	setType(_type);
	body.setPosition(x, y);
	rect = IntRect(x, y, Sz, Sz);
	setRotateStep(rtSt);
	selected = 0;
}
void Puzzle::setType(int _type)
{
	type = _type;
	if (type == 0)
		setTexture("textures/" + tex_lnk + "/empty.jpg");
	if (type == 1)
		setTexture("textures/" + tex_lnk + "/line.jpg");
	if (type == 2)
		setTexture("textures/" + tex_lnk + "/turn.jpg");
	if (type == 3)
		setTexture("textures/" + tex_lnk + "/fork.jpg");
	if (type == 4)
		setTexture("textures/" + tex_lnk + "/cross.jpg");
}
void Puzzle::setTexture(string link)
{
	pict.loadFromFile(link);
	link = link.substr(0, link.size() - 4) + "-selected.jpg";
	pictSel.loadFromFile(link);
	if (selected)
		body.setTexture(pictSel);
	else
		body.setTexture(pict);
}
int Puzzle::getRotateStep()
{
	return rotateStep;
}
Sprite Puzzle::getSprite()
{
	return body;
}
IntRect Puzzle::getRect()
{
	return rect;
}
int Puzzle::getType()
{
	return type;
}

void swap(Puzzle &a, Puzzle &b)
{
	int tmp = a.getRotateStep();
	a.setRotateStep(b.getRotateStep());
	b.setRotateStep(tmp);
	tmp = a.getType();
	a.setType(b.getType());
	b.setType(tmp);
}