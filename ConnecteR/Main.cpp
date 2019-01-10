#include "Inclusion.h"
#include "GlobalRes.h"
#include "Game.h"
#include "Menu.h"

void center(Text &text, const Sprite &sprite)
{
	int x = sprite.getPosition().x, y = sprite.getPosition().y;
	x += sprite.getLocalBounds().width / 2 - text.getLocalBounds().width / 2 - text.getLocalBounds().left;
	y += sprite.getLocalBounds().height / 2 - text.getLocalBounds().height / 2 - text.getLocalBounds().top;
	text.setPosition(x, y);
}

Texture* but;
Texture* but_sel;
bool select(GlobalRes &res, Sprite &sprite, bool &sel)
{
	if (IntRect(sprite.getGlobalBounds()).contains(Mouse::getPosition(res.window)))
	{
		if (!sel)
		{
			sprite.setTexture(*but_sel);
			sel = 1;
		}
		if (Mouse::isButtonPressed(Mouse::Left))
			return 1;
	}
	else
	{
		if (sel)
		{
			sprite.setTexture(*but);
			sel = 0;
		}
	}
	return 0;
}

int main()
{
	srand(time(0));

	GlobalRes res;
	res.resolution = make_pair(720, 720);
	res.window.create(VideoMode(res.resolution.first, res.resolution.second), "ConnecteR", Style::Close);
	{
		Image icon;
		icon.loadFromFile("textures/icons/icon32.jpg");
		res.window.setIcon(32, 32, icon.getPixelsPtr());
	}

	double gray = 125;
	bool flag = 1;

	res.loadMap("maps/start.txt");

	Menu::activate(res);
	Game::activate(res);

	Font font;
	font.loadFromFile("fonts/headplane.ttf");
	Text text;
	text.setFont(font);
	text.setCharacterSize(100);
	text.setString("PASSED");

	bool press3 = 0, press4 = 0, press5 = 0, pressR = 0;

	bool sel = 0;
	but = new Texture();
	but->loadFromFile("textures/btn_600x150.jpg");
	but_sel = new Texture();
	but_sel->loadFromFile("textures/btn_600x150-selected.jpg");
	Sprite passed;
	passed.setTexture(*but);
	int x = (res.resolution.first - passed.getLocalBounds().width) / 2;
	int y = res.resolution.second / 3 - passed.getLocalBounds().height / 2;
	passed.setPosition(x, y);
	center(text, passed);

	int curType = 0;
	//0 - Menu
	//1 - Game
	//2 - Pass screen
	//3 - Exit
	while (1)
	{
		if (curType == 0)
		{
		//Menu/////////////////////////////////////////////////////////////////

			curType = Menu::update(res);

			res.window.clear(Color(gray, gray, gray, 255));
			Menu::draw(res); 
			res.window.display();

		//Menu/////////////////////////////////////////////////////////////////
		}

		if (curType == 1)
		{
		//Game/////////////////////////////////////////////////////////////////

			if (!Keyboard::isKeyPressed(Keyboard::Num3) && press3)
			{
				Game::clear();
				res.loadMap("maps/map_1.txt");
			}
			if (!Keyboard::isKeyPressed(Keyboard::Num4) && press4)
			{
				Game::clear();
				res.loadMap("maps/map_2.txt");
			}
			if (!Keyboard::isKeyPressed(Keyboard::Num5) && press5)
			{
				Game::clear();
				res.loadMap("maps/map_3.txt");
			}
			if (!Keyboard::isKeyPressed(Keyboard::R) && pressR)
			{
				Game::taskGen(res, res.N);

				Game::clear();
				res.loadMap("maps/gen.txt");
			}

			press3 = Keyboard::isKeyPressed(Keyboard::Num3);
			press4 = Keyboard::isKeyPressed(Keyboard::Num4);
			press5 = Keyboard::isKeyPressed(Keyboard::Num5);
			pressR = Keyboard::isKeyPressed(Keyboard::R);

			curType = Game::update(res);

			res.window.clear(Color(gray, gray, gray, 255));
			Game::draw(res);
			res.window.display();

		//Game/////////////////////////////////////////////////////////////////
		}

		if (curType == 2)
		{
		//Pass screen//////////////////////////////////////////////////////////
			
			if (select(res, passed, sel))
			{
				curType = 1;

				Game::clear();
				res.loadMap("maps/start.txt");

				continue;
			}

			res.window.clear(Color(gray, gray, gray, 255));
			
			Game::draw(res);
			res.window.draw(passed);
			res.window.draw(text);

			res.window.display();

		//Pass screen//////////////////////////////////////////////////////////
		}

		if (flag)
		{
			gray += 0.002;
			if (gray > 185)
				flag = 0;
		}
		else
		{
			gray -= 0.002;
			if (gray < 125)
				flag = 1;
		}

		Event event;
		while (curType == 3 || res.window.pollEvent(event))
		{
			if (curType == 3 || event.type == Event::Closed)
			{
				res.window.close();
				return 0;
			}
		}
	}

}