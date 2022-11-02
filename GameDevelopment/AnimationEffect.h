#pragma once
#include<string>
#include<SFML/Graphics.hpp>
class AnimationEffect
{
public:
	AnimationEffect();
	AnimationEffect(std::string imagePath,sf::Vector2u numbScene,float switchTime);
	virtual ~AnimationEffect();
	void update(float deltaTime);
	void draw(sf::RenderWindow &window);
	void setDirection(sf::Vector2f direction);
	void setMoveTime(float moveTime);
	void setSize(sf::Vector2u size);
	void setAttackPoint(float atkPoint);
	void setUseManaPoint(float useManaPoint);
public:
	bool visible;

	float moveTime;
	float switchTime;
	float totalMoveTime;
	float totalTime;
	float attackPoint;
	float useManaPoint;
	int type;
	sf::IntRect mRect;
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2f direction;
	sf::Vector2u currentScene;
	sf::Vector2u numbScene;


};

