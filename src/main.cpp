#include <iostream>
#include <cmath>

#include <SFML/Graphics.hpp>

#include "unit.h"

int hit = -1;

bool in_box(const sf::Event &e, sf::FloatRect b)
{
	if (e.mouseMove.x > b.left && e.mouseMove.y > b.top && e.mouseMove.x < b.left + b.width && e.mouseMove.y < b.top + b.height)
		return true;

	return false;
}

void squares_hover(sf::Event &e, sf::RectangleShape *squares)
{
	if (hit != -1)
	{
		if (!in_box(e, squares[hit].getGlobalBounds()))
			squares[hit].setFillColor(sf::Color::Transparent);
		else
		{
			return;
		}
	}

	for (int i = 0; i < 25; ++i)
	{
		if (in_box(e, squares[i].getGlobalBounds()))
		{
			hit = i;
			squares[hit].setFillColor(sf::Color(100, 100, 100, 100));
			return;
		}
	}

	hit = -1;
}

int main()
{
	sf::Vector2u win_size(800, 600);
	sf::Vector2f size({float(win_size.x) / 5, float(win_size.y) / 5});
	sf::Vector2f halfsize(size.x / 2, size.y / 2);

	sf::RectangleShape squares[NumUnits];
	for (int y = 0; y < 5; ++y)
	{
		for (int x = 0; x < 5; ++x)
		{
			int idx = x * 5 + y;
			squares[idx].setSize(size);
			squares[idx].setPosition({y * size.x, x * size.y});
			squares[idx].setFillColor(sf::Color::Transparent);
			squares[idx].setOutlineThickness(1);
			squares[idx].setOutlineColor(sf::Color(25, 25, 25));
		}
	}

	sf::Font font;
	font.loadFromFile("8bitOperatorPlus8-Regular.ttf");
	sf::Text names[NumUnits];

	sf::RectangleShape nameboxes[NumUnits];
	for (int y = 0; y < 5; ++y)
	{
		for (int x = 0; x < 5; ++x)
		{
			int idx = x * 5 + y;
			names[idx].setFont(font);
			names[idx].setString(kUnitNames[idx]);
			names[idx].setCharacterSize(20);
			sf::Vector2f nsize(size.x / 1.3, size.y / 5);
			names[idx].setPosition(squares[idx].getPosition() + sf::Vector2f{2, (size.y - nsize.y)});
			nameboxes[idx].setSize(nsize);
			nameboxes[idx].setPosition(squares[idx].getPosition() + sf::Vector2f{0, size.y - nsize.y});
			nameboxes[idx].setFillColor(sf::Color(30, 30, 30, 200));
		}
	}

	sf::Texture unit_textures[NumUnits];
	sf::Sprite unit_sprites[NumUnits];

	for (int i = 0; i < NumUnits; ++i)
	{
		if (!unit_textures[i].loadFromFile("units/" + kUnitTextures[i]))
			return 1;

		unit_sprites[i].setTexture(unit_textures[i]);
		unit_sprites[i].setTextureRect(sf::IntRect(0, 0, 48, 32));

		unit_sprites[i].setPosition(squares[i].getPosition() +
			halfsize -
			sf::Vector2f{24, 16});
	}

	sf::RenderWindow win(sf::VideoMode(800, 600), "King's Bounty: The Conquerors Quests - Units", sf::Style::Titlebar | sf::Style::Close);
	win.setFramerateLimit(60);

	bool quit = false;
	while (!quit)
	{
		sf::Event e;
		while (win.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
				quit = true;
			else if (e.type == sf::Event::KeyPressed)
			{
				if (e.key.code == sf::Keyboard::Q)
					quit = true;
			}
			else if (e.type == sf::Event::MouseMoved)
			{
				squares_hover(e, squares);
			}
		}

		win.clear(sf::Color(40, 40, 40));

		for (int i = 0; i < 25; ++i)
		{
			win.draw(squares[i]);
		}

		for (int i = 0; i < NumUnits; ++i)
		{
			win.draw(unit_sprites[i]);
		}

		if (hit != -1)
		{
			win.draw(nameboxes[hit]);
			win.draw(names[hit]);
		}

		win.display();
	}

	return 0;
}
