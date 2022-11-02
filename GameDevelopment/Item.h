#pragma once
#include"AnimationEffect.h"
class Item
{
public:
	Item();
	void add(int type,sf::Vector2f position);
	void update(float deltaTime);
	void draw();
	void setWindow(sf::RenderWindow *window);
	virtual ~Item();
	std::vector<AnimationEffect> vtAnimationEffect;
	std::vector<AnimationEffect > stock;
	sf::RenderWindow *window;
};

