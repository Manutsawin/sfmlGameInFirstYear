#include "Item.h"
#include<iostream>
#include<string>

Item::Item()
{
	for (int i = 0; i < 2; i++)
	{
		
		stock.push_back(* new AnimationEffect("item" + std::to_string(i)+".png", { 10,4 }, 0.3));
	}
}

void Item::add(int type,sf::Vector2f position)
{
	stock[type].sprite.setPosition(position);
	stock[type].type = type;
	vtAnimationEffect.push_back(stock[type]);
}

void Item::update(float deltaTime)
{
	for (int i = 0; i < vtAnimationEffect.size(); i++)
	{
		vtAnimationEffect[i].update(deltaTime);
	}
}

void Item::draw()
{
	//std::cout << vtAnimationEffect.size() << "\n";
	for (int i = 0; i < vtAnimationEffect.size(); i++)
	{
		window->draw(vtAnimationEffect[i].sprite);
	}
}


void Item::setWindow(sf::RenderWindow * window)
{
	this->window = window;
}

Item::~Item()
{
}
