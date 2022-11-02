#include "Image.h"
#include<iostream>

Image::Image() {

}
Image::Image(std::string texturePath, sf::Vector2u size, sf::Vector2f position)
{	
	this->size = size;
	this->position = position;
	sf::Texture *tmpTexture = new sf::Texture();
	sf::Sprite *tmpSprite = new sf::Sprite();
	this->texturePath = texturePath;
	if (!tmpTexture->loadFromFile(texturePath))
	{
		std::cout << "Error load image" << std::endl;
	}
	texture = tmpTexture;
	sprite = tmpSprite;
	sprite->setTexture(*texture);
	sprite->setPosition(position);
	sprite->setScale(sf::Vector2f(size.x /float(texture->getSize().x)  ,  size.y / float(texture->getSize().y) ));
}


Image::~Image()
{
}

std::string Image::getTexturePath()
{
	return this->texturePath;
}

sf::Vector2u Image::getSize()
{
	return size;
}

sf::Vector2f Image::getPosition()
{
	return position;
}

sf::Texture * Image::getTexture()
{
	return texture;
}

sf::Sprite* Image::getSprite()
{
	return sprite;
}

Image Image::getClone()
{
	Image tmpImage = Image(this->texturePath, this->size, this->position);
	return tmpImage;

}


void Image::setSize(sf::Vector2u size)
{
	this->size = size;
	this->sprite->setScale(sf::Vector2f(size.x / float(texture->getSize().x), size.y / float(texture->getSize().y)));
}

void Image::setPosition(sf::Vector2f position)
{
	this->position = position;
	this->sprite->setPosition(position);
}
