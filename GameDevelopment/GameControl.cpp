#include "GameControl.h"


GameControl::GameControl()
{
	this->updateTime = 0.0f;
	this->totalTime = 0.0f;
	this->gameOver = new bool;
	*this->gameOver = false;
	this->randomItemTime = 5.0f;
	this->totalRandomItemTime = 0.0f;
}

void GameControl::add(Player * player)
{
	vtPlayer.push_back(player);
}

void GameControl::add(AnimationEffect *animationEffect)
{
	vtAnimationEffect.push_back(animationEffect);
}

void GameControl::update(float deltaTime)
{
	Player::State aState, bState;
	sf::Vector2f aPosition, bPosition;
	sf::Sprite tmpSprite;
	this->totalTime += deltaTime;
	this->totalRandomItemTime += deltaTime;
	if (this->totalRandomItemTime >= this->randomItemTime)
	{
		sf::Vector2f tmpPosition = sf::Vector2f(*this->randomNumber % 900+50, *this->randomNumber % 700+50);
		if (((int)tmpPosition.y) % 10 > 5)
		{
			std::cout << "droped ";
			std::cout << tmpPosition.x << " , " << tmpPosition.y << "\n";
			item->add(((int)tmpPosition.x)%2, tmpPosition);
		}
		else
		{
			std::cout << "not droped\n";
		}
		
		this->totalRandomItemTime = 0.0f;
	}
	if (totalTime >= updateTime)
	{
		//update player
		for (int i = 0; i < vtPlayer.size();i++)
		{
			for (int j = i + 1; j < vtPlayer.size(); j++)
			{
				aState = vtPlayer[i]->getCurrentState();
				bState = vtPlayer[j]->getCurrentState();
				aPosition = vtPlayer[i]->getPosition();
				bPosition = vtPlayer[j]->getPosition();
				if (std::abs(compareXY(aPosition, bPosition).x) <= 60 and std::abs(compareXY(aPosition, bPosition).y) <= 12)
				{
					
					if ((aState == Player::State::attackLeft0 or aState == Player::State::attackLeft1) and compareXY(aPosition,bPosition).x>0 and bState != Player::defendRight)
					{
						vtPlayer[i]->increaseHitPoint(vtPlayer[j]->attackPoint);
						vtPlayer[j]->hp -= vtPlayer[i]->attackPoint;
					}
					else if((aState == Player::State::attackRight0 or aState == Player::State::attackRight1) and compareXY(aPosition, bPosition).x < 0 and bState != Player::defendLeft)
					{
						vtPlayer[i]->increaseHitPoint(vtPlayer[j]->attackPoint);
						vtPlayer[j]->hp -= vtPlayer[i]->attackPoint;
					}
					if ((bState == Player::State::attackLeft0 or bState == Player::State::attackLeft1) and compareXY(aPosition, bPosition).x < 0 and aState != Player::defendLeft)
					{
						vtPlayer[j]->increaseHitPoint(vtPlayer[j]->attackPoint);
						vtPlayer[i]->hp -= vtPlayer[j]->attackPoint;
					}
					else if((bState == Player::State::attackRight0 or bState == Player::State::attackRight1) and compareXY(aPosition, bPosition).x > 0 and aState != Player::defendRight)
					{
						vtPlayer[j]->increaseHitPoint(vtPlayer[j]->attackPoint);
						vtPlayer[i]->hp -= vtPlayer[j]->attackPoint;
					}
				}
			}
			
		}
		totalTime = 0.0f;
	}
	
	for (int i = 0; i < vtPlayer.size(); i++)
	{
		if (vtPlayer[i]->hp <= 0)
		{
			*this->firstOver = true;
		}
		for (int j = 0; j < vtPlayer[i]->vtDisplayEffect.size(); j++)
		{
			//std::cout << "GameControl::update->";
			aPosition = vtPlayer[i]->vtDisplayEffect[j].sprite.getPosition();
		
			for (int k=0 ; k < vtPlayer.size() ; k++)
			{	
				bPosition = vtPlayer[k]->getPosition();
				if (i == k)
					continue;
				std::cout << Collision::PixelPerfectTest(&vtPlayer[i]->vtDisplayEffect[j].sprite, vtPlayer[k]->getCurrentSprite()) << ":";
				if (Collision::PixelPerfectTest(&vtPlayer[i]->vtDisplayEffect[j].sprite, vtPlayer[k]->getCurrentSprite()) and compareXY(aPosition,bPosition).y < 0 and std::abs(compareXY(aPosition, bPosition).y) >= 50 and std::abs(compareXY(aPosition, bPosition).y) <= 110)
				{
					//std::cout << "Collision true";
					vtPlayer[i]->increaseHitPoint(vtPlayer[i]->vtDisplayEffect[j].attackPoint);
					vtPlayer[k]->hp -= vtPlayer[i]->vtDisplayEffect[j].attackPoint;
					/*if(vtPlayer[i]->vtDisplayEffect.size()>0)
					vtPlayer[i]->vtDisplayEffect.erase(vtPlayer[i]->vtDisplayEffect.begin() + j);*/
				}
		
			}
			//std::cout << "\n";
		}
		for (int j = 0 ; j < item->vtAnimationEffect.size(); j++)
		{

			if (Collision::PixelPerfectTest(vtPlayer[i]->getCurrentSprite(), &item->vtAnimationEffect[j].sprite) and (vtPlayer[i]->state == Player::State::attackLeft0 or vtPlayer[i]->state == Player::State::attackRight0))
			{
				switch(item->vtAnimationEffect[j].type )
				{
				case 0:
					if (vtPlayer[i]->mana + 20 <= 100)
					{
						vtPlayer[i]->mana += 20;
						vtPlayer[i]->score += 15;
					}
					else
						vtPlayer[i]->mana = 100;
					break;
				case 1:
					if (vtPlayer[i]->hp + 20 <= 100)
					{
						vtPlayer[i]->score += 15;
						vtPlayer[i]->hp += 20;
					}
					else
						vtPlayer[i]->hp = 100;
					break;
				}

				item->vtAnimationEffect.erase(item->vtAnimationEffect.begin() + j);
			}
			else
			{
				//std::cout << "not Collision\n";
			}
		}
		
	}
	
}

void GameControl::setUpdateTime(float updateTime)
{
	this->updateTime = updateTime;
}

sf::Vector2f GameControl::compareXY(sf::Vector2f a, sf::Vector2f b)
{
	return sf::Vector2f(a.x - b.x, a.y - b.y);
}


GameControl::~GameControl()
{
}
