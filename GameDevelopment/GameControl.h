#pragma once
#include"Player.h"
#include"AnimationEffect.h"
#include"Collision.h"
#include"Item.h"
class GameControl
{
public:
	GameControl();
	void add(Player *player);
	void add(AnimationEffect *animationEffect);
	void update(float deltaTime);
	void setUpdateTime(float updateTime);
	sf::Vector2f compareXY(sf::Vector2f a,sf::Vector2f b);
	virtual ~GameControl();
public:
	std::vector<Player*> vtPlayer;
	std::vector<AnimationEffect*> vtAnimationEffect;
	float totalTime;
	float updateTime;
	bool *gameOver;
	bool *firstOver;
	Item *item;
	float randomItemTime;
	float totalRandomItemTime;
	unsigned long long *randomNumber;
};

