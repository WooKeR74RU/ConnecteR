#include "Menu.h"

void text_options(Text &text, const Font &font, int char_size, const string &s)
{
	text.setFont(font);
	text.setCharacterSize(char_size);
	text.setString(s);
}

void text_center(Text &text, const Sprite &sprite)
{
	int x = sprite.getPosition().x, y = sprite.getPosition().y;
	x += sprite.getLocalBounds().width / 2 - text.getLocalBounds().width / 2 - text.getLocalBounds().left;
	y += sprite.getLocalBounds().height / 2 - text.getLocalBounds().height / 2 - text.getLocalBounds().top;
	text.setPosition(x, y);
}

Sprite spr_play, spr_options, spr_exit;
Texture* button;
Texture* button_sel;
bool sel1, sel2, sel3;

Text text_1, text_2, text_3;
Font font;

bool buttonSelect(GlobalRes &res, Sprite &sprite, bool &select)
{
	if (IntRect(sprite.getGlobalBounds()).contains(Mouse::getPosition(res.window)))
	{
		if (!select)
		{
			sprite.setTexture(*button_sel);
			select = 1;
		}
		if (Mouse::isButtonPressed(Mouse::Left))
			return 1;
	}
	else
	{
		if (select)
		{
			sprite.setTexture(*button);
			select = 0;
		}
	}
	return 0;
}

int Menu::update(GlobalRes &res)
{
	if (buttonSelect(res, spr_play, sel1))
		return 1;
	if (buttonSelect(res, spr_options, sel2))
	{
		
	}
	if (buttonSelect(res, spr_exit, sel3))
		return 3;
	return 0;
}

void Menu::draw(GlobalRes &res)
{
	res.window.draw(spr_play);
	res.window.draw(text_1);
	res.window.draw(spr_options);
	res.window.draw(text_2);
	res.window.draw(spr_exit);
	res.window.draw(text_3);
}

void Menu::activate(GlobalRes &res)
{
	button = new Texture();
	button->loadFromFile("textures/btn_400x100.jpg");
	button_sel = new Texture();
	button_sel->loadFromFile("textures/btn_400x100-selected.jpg");

	spr_play.setTexture(*button);
	spr_options.setTexture(*button);
	spr_exit.setTexture(*button);

	int cl, x, y;
	cl = (res.resolution.second - 3 * spr_play.getLocalBounds().height) / 4;
	x = (res.resolution.first - spr_play.getLocalBounds().width) / 2;
	y = cl;
	spr_play.setPosition(x, y);
	y = 2 * cl + spr_play.getLocalBounds().height;
	spr_options.setPosition(x, y);
	y = 3 * cl + 2 * spr_play.getLocalBounds().height;
	spr_exit.setPosition(x, y);

	font.loadFromFile("fonts/headplane.ttf");
	text_options(text_1, font, 28, "Start");
	text_center(text_1, spr_play);
	text_options(text_2, font, 28, "Disabled");
	text_center(text_2, spr_options);
	text_options(text_3, font, 28, "Exit");
	text_center(text_3, spr_exit);
}

void Menu::clear()
{
	sel1 = sel2 = sel3 = 0;
}