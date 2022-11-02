#pragma once
#include<SFML/Graphics.hpp>
#include<string>
class Image
{
public:
	Image();
	Image(std::string texturePath,sf::Vector2u size,sf::Vector2f position);
	virtual ~Image();
	std::string getTexturePath();
 	sf::Vector2u getSize();
	sf::Vector2f getPosition();
	sf::Texture* getTexture();
	sf::Sprite* getSprite();
	Image getClone();
	void setSize(sf::Vector2u size);
	void setPosition(sf::Vector2f position);
public:
	std::string texturePath;
	sf::Vector2u size;
	sf::Vector2f position;
	sf::Texture *texture;
	sf::Sprite *sprite;
};

