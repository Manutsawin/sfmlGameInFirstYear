#pragma once
#include "Image.h"
class Animation
{
public:
	enum Mode{
		play,pause
	};
	Animation();
	Animation(Image *image,sf::Vector2u numbScene,float switchTime,Mode mode);
	void update(float deltaTime);
	void changeMode(Mode mode);
	virtual ~Animation();
	sf::Vector2u getCurrentScene();
	uint16_t getEndColumn();
	sf::IntRect getRect();
	sf::Vector2f getPosition();
	sf::Sprite* getSprite();
	float getSwitchTime();
	float getStartColumn();
	float getTotalTime();
	void setSize(sf::Vector2u size);
	void setMode(Mode mode);
	void setPosition(sf::Vector2f position);
	void setScene(sf::Vector3i indexScene3d);
	void setSwitchTime(float switchTime);
	void move(sf::Vector2f xy);
	Animation getClone();
public:
	Image *image;
	sf::Vector2u numbScene;
	sf::IntRect mRect;
	sf::Vector2u currentScene;
	sf::Vector2f position;
	float switchTime;
	float totalTime;
	Mode mode;
	uint16_t row;
	uint16_t startColumn;
	uint16_t endColumn;
};

