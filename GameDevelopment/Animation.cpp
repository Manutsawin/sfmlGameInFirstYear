#include "Animation.h"

Animation::Animation()
{

}
Animation::Animation(Image *image, sf::Vector2u numbScene, float switchTime, Mode mode)
{
	this->image = image;
	image->getSprite()->scale(numbScene.x, numbScene.y);
	this->image->getTexture()->setRepeated(true);
	this->image->getTexture()->setSmooth(true);
	setPosition(image->getPosition());
	this->numbScene = numbScene;
	this->switchTime = switchTime;
	this->mode = mode;
	mRect.width = image->getTexture()->getSize().x / numbScene.x;
	mRect.height = image->getTexture()->getSize().y / numbScene.y;
	mRect.left = 0;
	mRect.top = 0;
	row = 0;
	startColumn = 0;
	endColumn = numbScene.x;
	currentScene.x = startColumn;
	currentScene.y = row;
	totalTime = 0;
}

void Animation::update(float deltaTime)
{
	this->currentScene.y = row;
	if (mode == Mode::play)
	{
		
		totalTime += deltaTime;
		if (totalTime >= switchTime)
		{
			if (endColumn > startColumn)
			{
				currentScene.x++;
				if (currentScene.x > endColumn)
				{
					currentScene.x = startColumn;
				}
			}
			else
			{
				if (currentScene.x > endColumn)
					currentScene.x--;
				else
					currentScene.x = startColumn;
				
			}
			totalTime -= switchTime;
		}
		mRect.left = currentScene.x * mRect.width;
		mRect.top = currentScene.y * mRect.height;
	}
	this->getSprite()->setTextureRect(mRect);
}

void Animation::changeMode(Mode mode)
{
	this->mode = mode;
}


Animation::~Animation()
{

}

sf::Sprite * Animation::getSprite()
{
	return image->getSprite();
}


sf::Vector2f Animation::getPosition()
{
	return position;
}

float Animation::getSwitchTime()
{
	return this->switchTime;
}

float Animation::getStartColumn()
{
	return this->startColumn;
}

float Animation::getTotalTime()
{
	return this->totalTime;
}

void Animation::setSize(sf::Vector2u size)
{
	this->image->setSize(size);
	this->image->getSprite()->scale(numbScene.x, numbScene.y);
}

void Animation::setMode(Mode mode)
{
	this->mode = mode;
}

void Animation::setPosition(sf::Vector2f position)
{
	this->position = position;
	this->image->setPosition(position);
}

void Animation::setScene(sf::Vector3i indexScene3d)
{
	this->row = indexScene3d.x;
	this->startColumn = indexScene3d.y;
	this->currentScene.y = this->row;
	this->currentScene.x = this->startColumn;
	this->endColumn = indexScene3d.z;
}

void Animation::setSwitchTime(float switchTime)
{
	this->switchTime = switchTime;
}

void Animation::move(sf::Vector2f xy)
{
	this->getSprite()->move(xy);
	position = this->getSprite()->getPosition();
}

Animation Animation::getClone()
{
	Animation tmpAnimation(&this->image->getClone(), this->numbScene, this->switchTime, this->mode);
	tmpAnimation.setScene({this->row,this->startColumn,this->endColumn});
	tmpAnimation.image->sprite = this->image->sprite;
	return tmpAnimation;
}



sf::Vector2u Animation::getCurrentScene() {
	return this->currentScene;
}

uint16_t Animation::getEndColumn() {
	return this->endColumn;
}

sf::IntRect Animation::getRect()
{
	return this->mRect;
}

