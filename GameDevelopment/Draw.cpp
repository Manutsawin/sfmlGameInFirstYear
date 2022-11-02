#include "Draw.h"
#include<SFML/Graphics.hpp>


Draw::Draw()
{

}



void Draw::add(Animation *animation)
{
	content.push_back(animation->getSprite());
	animationContent.push_back(animation);
}

void Draw::add(Image *image)
{
	content.push_back(image->getSprite());
}

void Draw::add(sf::Text * text)
{
	textContent.push_back(text);
}

void Draw::add(Player * player)
{
	playerContent.push_back(player);
}

void Draw::add(sf::Sprite * sprite)
{
	content.push_back(sprite);
}

void Draw::add(sf::RectangleShape * rect)
{
	contentRect.push_back(rect);
}



void Draw::update(float deltaTime)
{

	for (int i = 0;i < animationContent.size();i++)
	{
		animationContent[i]->update(deltaTime);
	}
	for (int i = 0;i < playerContent.size();i++)
	{
		playerContent[i]->update(deltaTime);
		for (int j = 0; j < playerContent[i]->vtDisplayEffect.size(); j++)
		{
			playerContent[i]->vtDisplayEffect[j].update(deltaTime);
			if (playerContent[i]->vtDisplayEffect[j].sprite.getPosition().x < 0 or playerContent[i]->vtDisplayEffect[j].sprite.getPosition().x>this->mapSize.x)
			{
				playerContent[i]->vtDisplayEffect.erase(playerContent[i]->vtDisplayEffect.begin() + j);
			}
		}
	}
}

void Draw::draw()
{
	
	for (int i = 0;i < content.size();i++)
	{
		window->draw(*content[i]);
	}
	for (int i = 0; i < contentRect.size(); i++)
	{
		window->draw(*contentRect[i]);
	}
	Player *tmp;
	for (int i = 0; i < playerContent.size(); i++)
	{
		for (int j = i + 1; j < playerContent.size(); j++)
		{
			if (playerContent[j]->getPosition().y < playerContent[i]->getPosition().y)
			{
				tmp = playerContent[i];
				playerContent[i] = playerContent[j];
				playerContent[j] = tmp;
			}
		}
	}
	for (int i = 0;i < playerContent.size();i++)
	{
		window->draw(*playerContent[i]->getCurrentAnimation()->getSprite());
		window->draw(playerContent[i]->whoText);
		for (int j = 0; j < playerContent[i]->vtDisplayEffect.size(); j++)
		{
			window->draw(playerContent[i]->vtDisplayEffect[j].sprite);
		}
	}
	for (int i = 0;i < textContent.size();i++)
	{
		window->draw(*textContent[i]);
	}
}

void Draw::setMapSize(sf::Vector2u size)
{
	this->mapSize = size;
}

void Draw::setWindow(sf::RenderWindow * window)
{
	this->window = window;
}

void Draw::clear()
{
	content.clear();
	animationContent.clear();
}



Draw::~Draw()
{

}