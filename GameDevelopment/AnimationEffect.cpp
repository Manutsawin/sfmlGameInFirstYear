#include "AnimationEffect.h"



AnimationEffect::AnimationEffect()
{
}

AnimationEffect::AnimationEffect(std::string imagePath, sf::Vector2u numbScene, float switchTime)
{
	this->texture.loadFromFile("image\\sprite\\sys\\charecter\\" + imagePath);
	this->texture.setRepeated(true);
	this->texture.setSmooth(true);
	this->sprite.setTexture(this->texture);
	this->numbScene = numbScene;
	this->switchTime = switchTime;
	this->totalMoveTime = 0.0f;
	this->totalTime = 0.0f;
	this->mRect.width = texture.getSize().x / this->numbScene.x;
	this->mRect.height = texture.getSize().y / this->numbScene.y;
	this->mRect.top = 0;
	this->mRect.left = 0;
	currentScene.x = 0;
	currentScene.y = 0;
	this->sprite.setTextureRect(mRect);
	this->visible = true;
	this->moveTime = 0.01;
	this->direction = { 0.0f,0.0f };
	this->attackPoint = 10.0f;
	this->useManaPoint = 5.0f;
}


AnimationEffect::~AnimationEffect()
{
}

void AnimationEffect::update(float deltaTime)
{
	this->totalTime += deltaTime;
	this->totalMoveTime += deltaTime;
	if (this->totalTime >= deltaTime)
	{
		currentScene.x++;
		if (currentScene.x >= numbScene.x)
		{
			currentScene.x = 0;
		}
		this->totalTime -= this->switchTime;
	}
	this->mRect.top = mRect.height * currentScene.y;
	this->mRect.left = mRect.width * currentScene.x;
	this->sprite.setTextureRect(mRect);

	if (this->totalMoveTime >= moveTime)
	{
		this->sprite.move(direction);
		this->totalMoveTime -= moveTime;
	}
}

void AnimationEffect::draw(sf::RenderWindow & window)
{
	window.draw(this->sprite);
}

void AnimationEffect::setDirection(sf::Vector2f direction)
{
	this->direction = direction;
}

void AnimationEffect::setMoveTime(float moveTime)
{
	this->moveTime = moveTime;
}

void AnimationEffect::setSize(sf::Vector2u size)
{
	this->sprite.setScale(sf::Vector2f(size.x /float(texture.getSize().x)*numbScene.x, size.y / float(texture.getSize().y)*numbScene.y));
}

void AnimationEffect::setAttackPoint(float atkPoint)
{
	this->attackPoint = atkPoint;
}

void AnimationEffect::setUseManaPoint(float useManaPoint)
{
	this->useManaPoint = useManaPoint;
}
