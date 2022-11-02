#include "Player.h"


Player::Player()
{
}


Player::Player(std::string name, sf::Vector2u size, sf::Vector2f position)
{
	this->charecter = Charecter::unknow;
	this->name = name;
	this->size = size;
	this->who = name;
	if (!whoFont.loadFromFile("font\\bangkok_regular_v1-0.ttf"))
	{
		std::cout << "Error load font\\bangkok_regular_v1-0.ttf";
	}
	whoText.setFont(whoFont);
	whoText.setCharacterSize(25);
	whoText.setString(who);
	whoText.setFillColor(sf::Color::Black);
	scoreText.setFont(whoFont);
	scoreText.setCharacterSize(25);
	scoreText.setString("0");
	scoreText.setFillColor(sf::Color::Black);
	this->position = position;
	totalTime = 0.0f;
	this->moveSpeed = 1.0;
	keyMoveLeft = sf::Keyboard::Key::A;
	keyMoveRight = sf::Keyboard::D;
	keyMoveUp = sf::Keyboard::W;
	keyMoveDown = sf::Keyboard::S;
	keyJump = sf::Keyboard::K;
	keyAttack = sf::Keyboard::J;
	keyDefend = sf::Keyboard::L;
	joyKeyMoveLeft = -1;
	joyKeyMoveRight = -2;
	joyKeyMoveUp = -3;
	joyKeyMoveDown = -4;
	joyKeyJump = 0;
	joyKeyAttack = 2;
	joyKeyDefend = 1;
	this->updateEventTime = 0.0f;
	this->face = Face::right;
	this->jumpTime = 2.0f;
	this->specialState = false;
	this->jumpHeight = 50;
	this->hitPoint = 0;
	this->mapSize = { 2000,500 };
	this->useJoyStick = false;
	this->joyNumb = 0;
	FsmState[0].outputState = State::stayRight;
	FsmState[0].waitTime = 0.005f;
	FsmState[0].nextState["default"] = 0;
	FsmState[0].nextState["0000000"] = 0;
	FsmState[0].nextState["0001000"] = 2;
	FsmState[0].nextState["0100000"] = 1;
	FsmState[0].nextState["1000000"] = 8;
	FsmState[0].nextState["1001000"] = 9;
	FsmState[0].nextState["0010000"] = 10;
	FsmState[0].nextState["0011000"] = 11;
	FsmState[0].nextState["1100000"] = 5;
	FsmState[0].nextState["0110000"] = 7;
	FsmState[0].nextState["0000100"] = 14;
	FsmState[0].nextState["0000010"] = 17;
	FsmState[0].nextState["0000001"] = 21;

	FsmState[1].outputState = State::stayLeft;
	FsmState[1].waitTime = 0.005f;
	FsmState[1].nextState["default"] = 1;
	FsmState[1].nextState["0000000"] = 1;
	FsmState[1].nextState["0100000"] = 3;
	FsmState[1].nextState["0001000"] = 0;
	FsmState[1].nextState["1000000"] = 4;
	FsmState[1].nextState["1100000"] = 5;
	FsmState[1].nextState["0010000"] = 6;
	FsmState[1].nextState["0110000"] = 7;
	FsmState[1].nextState["1001000"] = 9;
	FsmState[1].nextState["0011000"] = 11;
	FsmState[1].nextState["0000100"] = 12;
	FsmState[1].nextState["0000010"] = 16;
	FsmState[1].nextState["0000001"] = 20;
	FsmState[1].nextState["0000001"] = 20;


	FsmState[2].outputState = State::walkRight;
	FsmState[2].waitTime = 0.005f;
	FsmState[2].nextState["default"] = 0;
	FsmState[2].nextState["0000000"] = 0;
	FsmState[2].nextState["0001000"] = 2;
	FsmState[2].nextState["1000000"] = 8;
	FsmState[2].nextState["0001010"] = 19;


	FsmState[3].outputState = State::walkLeft;
	FsmState[3].waitTime = 0.005f;
	FsmState[3].nextState["default"] = 1;
	FsmState[3].nextState["0000000"] = 1;
	FsmState[3].nextState["0100000"] = 3;
	FsmState[3].nextState["1000000"] = 4;
	FsmState[3].nextState["1100000"] = 5;
	FsmState[3].nextState["0010000"] = 6;
	FsmState[3].nextState["0110000"] = 7;
	FsmState[3].nextState["0100010"] = 18;

	FsmState[4].outputState = State::walkUpLeft;
	FsmState[4].waitTime = 0.005f;
	FsmState[4].nextState["default"] = 1;
	FsmState[4].nextState["0000000"] = 1;
	FsmState[4].nextState["1000000"] = 4;
	FsmState[4].nextState["1100000"] = 5;
	FsmState[4].nextState["0010000"] = 6;
	FsmState[4].nextState["0110000"] = 7;

	FsmState[5].outputState = State::walkUpAndLeft;
	FsmState[5].waitTime = 0.005f;
	FsmState[5].nextState["default"] = 1;
	FsmState[5].nextState["0000000"] = 1;
	FsmState[5].nextState["1000000"] = 4;
	FsmState[5].nextState["1100000"] = 5;
	FsmState[5].nextState["0010000"] = 6;
	FsmState[5].nextState["0110000"] = 7;
	FsmState[5].nextState["0100000"] = 1;

	FsmState[6].outputState = State::walkDownLeft;
	FsmState[6].waitTime = 0.005f;
	FsmState[6].nextState["default"] = 1;
	FsmState[6].nextState["0000000"] = 1;
	FsmState[6].nextState["0010000"] = 6;
	FsmState[6].nextState["0110000"] = 7;

	FsmState[7].outputState = State::walkDownAndLeft;
	FsmState[7].waitTime = 0.005f;
	FsmState[7].nextState["default"] = 1;
	FsmState[7].nextState["0000000"] = 1;
	FsmState[7].nextState["0010000"] = 6;
	FsmState[7].nextState["0110000"] = 7;
	FsmState[7].nextState["0100000"] = 1;

	FsmState[8].outputState = State::walkUpRight;
	FsmState[8].waitTime = 0.005f;
	FsmState[8].nextState["default"] = 0;
	FsmState[8].nextState["0000000"] = 0;
	FsmState[8].nextState["1000000"] = 8;
	FsmState[8].nextState["1001000"] = 9;
	FsmState[8].nextState["0010000"] = 10;
	FsmState[8].nextState["0101000"] = 11;

	FsmState[9].outputState = State::walkUpAndRight;
	FsmState[9].waitTime = 0.005f;
	FsmState[9].nextState["default"] = 0;
	FsmState[9].nextState["0000000"] = 0;
	FsmState[9].nextState["1001000"] = 9;
	FsmState[9].nextState["0010000"] = 10;
	FsmState[9].nextState["0011000"] = 11;

	FsmState[10].outputState = State::walkDownRight;
	FsmState[10].waitTime = 0.005f;
	FsmState[10].nextState["default"] = 0;
	FsmState[10].nextState["0000000"] = 0;
	FsmState[10].nextState["0010000"] = 10;
	FsmState[10].nextState["0011000"] = 11;

	FsmState[11].outputState = State::walkDownAndRight;
	FsmState[11].waitTime = 0.005f;
	FsmState[11].nextState["default"] = 0;
	FsmState[11].nextState["0000000"] = 0;
	FsmState[11].nextState["0011000"] = 11;
	FsmState[11].nextState["0010000"] = 10;

	FsmState[12].outputState = State::attackLeft0;
	FsmState[12].waitTime = 0.4f;
	FsmState[12].nextState["default"] = 1;
	FsmState[12].nextState["0000100"] = 13;

	FsmState[13].outputState = State::attackLeft1;
	FsmState[13].waitTime = 0.4f;
	FsmState[13].nextState["default"] = 1;

	FsmState[14].outputState = State::attackRight0;
	FsmState[14].waitTime = 0.4f;
	FsmState[14].nextState["default"] = 0;
	FsmState[14].nextState["0000100"] = 15;

	FsmState[15].outputState = State::attackRight1;
	FsmState[15].waitTime = 0.4f;
	FsmState[15].nextState["default"] = 0;

	FsmState[16].outputState = State::jumpUpLeft;
	FsmState[16].waitTime = 0.999f;
	FsmState[16].nextState["default"] = 1;

	FsmState[17].outputState = State::jumpUpRight;
	FsmState[17].waitTime = 0.999f;
	FsmState[17].nextState["default"] = 0;

	FsmState[18].outputState = State::jumpLeft;
	FsmState[18].waitTime = 0.999f;
	FsmState[18].nextState["default"] = 1;

	FsmState[19].outputState = State::jumpRight;
	FsmState[19].waitTime = 0.999f;
	FsmState[19].nextState["default"] = 0;

	FsmState[20].outputState = State::defendLeft;
	FsmState[20].waitTime = 0.8f;
	FsmState[20].nextState["default"] = 1;

	FsmState[21].outputState = State::defendRight;
	FsmState[21].waitTime = 0.8f;
	FsmState[21].nextState["default"] = 0;

	FsmState[22].outputState = State::skillRight0;
	FsmState[22].waitTime = 0.8f;
	FsmState[22].nextState["default"] = 0;

	FsmState[23].outputState = State::skillLeft0;
	FsmState[23].waitTime = 0.8f;
	FsmState[23].nextState["default"] = 1;

	currentFsmState = FsmState[0];
	specialState = false;
	groundPosition.x = -999;
	hp = 100.0f;
	mana = 100.0f;
	attackPoint = 4.0f;
	protectPoint = 0.0f;
	score = 0.0f;
	winner = false;
}

void Player::addAnimation(Animation * animation)
{
	vtAnimation.push_back(animation);
}

void Player::addAnimationEffect(AnimationEffect animationEffect)
{
	vtAnimationEffect.push_back(animationEffect);
}


void Player::increaseHitPoint(float point)
{
	this->hitPoint += point;
	this->score = hitPoint;
}

void Player::setAnimationState(State state, ANIMATION_STATE animationState)
{
	this->animationState[state] = animationState;
}



void Player::setCurrentState(State state)
{
	this->state = state;
	setCurrentAnimation(state);
}

void Player::setCurrentAnimation(State state)
{
	currentAnimation = vtAnimation[animationState[state].indexAnimation];
	currentAnimation->setScene(sf::Vector3i(animationState[state].row, animationState[state].startColumn, animationState[state].endColumn));
	currentAnimation->setPosition(position);
	currentAnimation->setSize(this->size);
	currentAnimation->getSprite()->setOrigin(currentAnimation->getRect().width/2.0f, currentAnimation->getRect().height);
	currentAnimation->setSwitchTime(animationState[state].switchTime);
	currentSprite = currentAnimation->getSprite();
}

void Player::setHitPoint(float hitPoint)
{
	this->hitPoint = hitPoint;
}

void Player::setJumpTime(float jumpTime)
{
	this->jumpTime = jumpTime;
}

void Player::setJumpHeight(float jumpHeight)
{
	this->jumpHeight = jumpHeight;
}

void Player::setKey(Key key, sf::Keyboard::Key keyValue)
{
	switch (key) {
	case Key::keyMoveLeftValue:
	{
		keyMoveLeft = keyValue;
		break;
	}
	case Key::keyMoveRightValue:
	{
		keyMoveRight = keyValue;
		break;
	}
	case Key::keyMoveUpValue:
	{
		keyMoveUp = keyValue;
		break;
	}
	case Key::keyMoveDownValue:
	{
		keyMoveDown = keyValue;
		break;
	}
	case Key::keyAttackValue:
	{
		keyAttack = keyValue;
		break;
	}
	case Key::keyJumpValue:
	{
		keyJump = keyValue;
		break;
	}
	case Key::keyDefendValue:
	{
		keyDefend = keyValue;
		break;
	}
	default:
		break;
	}
}

void Player::setKey(Key key, int joyButton)
{
	switch (key) {
	case Key::keyMoveLeftValue:
	{
		joyKeyMoveLeft = joyButton;
		break;
	}
	case Key::keyMoveRightValue:
	{
		joyKeyMoveRight = joyButton;
		break;
	}
	case Key::keyMoveUpValue:
	{
		joyKeyMoveUp = joyButton;
		break;
	}
	case Key::keyMoveDownValue:
	{
		joyKeyMoveDown = joyButton;
		break;
	}
	case Key::keyAttackValue:
	{
		joyKeyAttack = joyButton;
		break;
	}
	case Key::keyJumpValue:
	{
		joyKeyJump = joyButton;
		break;
	}
	case Key::keyDefendValue:
	{
		joyKeyDefend = joyButton;
		break;
	}
	default:
		break;
	}
}

void Player::setMapSize(sf::Vector2u size)
{
	this->mapSize = size;
}

void Player::setSize(sf::Vector2u size)
{
	this->size = size;
	this->currentAnimation->setSize(this->size);
}

void Player::setUpdateEventTime(float updateEventTime)
{
	this->updateEventTime = updateEventTime;
}

void Player::setMoveSpeed(float moveSpeed)
{
	this->moveSpeed = moveSpeed;
}

void Player::setPosition(sf::Vector2f position)
{
	this->position = position;
	this->getCurrentAnimation()->setPosition(position);
}

void Player::update(float deltaTime)
{
	currentAnimation->update(deltaTime);
}

void Player::updateEvent(float deltaTime) {
	this->whoText.setString(this->who);
	this->whoText.setPosition(this->position.x-whoText.getGlobalBounds().width/2.0,this->position.y);
	this->scoreText.setPosition(whoText.getPosition().x,whoText.getPosition().y+whoText.getGlobalBounds().height);
	this->scoreText.setString(std::to_string(this->score));
	this->totalTime += deltaTime;
	float newY,newX;
	getCurrentAnimation()->changeMode(Animation::Mode::play);
	switch (getCurrentState())
	{
	case State::jumpUpRight:
	case State::jumpUpLeft:
		if (this->getPosition().y < groundPosition.y)
		{
			if(getCurrentAnimation()->getCurrentScene().x == getCurrentAnimation()->getEndColumn())
				getCurrentAnimation()->changeMode(Animation::Mode::pause);
		}
		jumpTime = jumpClock.getElapsedTime().asSeconds();
		newY = jumpHeight * 4 * jumpTime + 0.5*-8 * jumpHeight*jumpTime*jumpTime;
		this->setPosition(sf::Vector2f(getPosition().x, groundPosition.y - newY));
		if (this->getPosition().y > groundPosition.y)
		{
			this->setPosition(sf::Vector2f(getPosition().x, groundPosition.y));
			getCurrentAnimation()->changeMode(Animation::Mode::play);
		}
		break;
	case State::jumpLeft:
		if (this->getPosition().y < groundPosition.y)
		{
			if (getCurrentAnimation()->getCurrentScene().x == getCurrentAnimation()->getEndColumn())
				getCurrentAnimation()->changeMode(Animation::Mode::pause);
		}
		jumpTime = jumpClock.getElapsedTime().asSeconds();
		newY = jumpHeight * 4 * jumpTime + 0.5*-8 * jumpHeight*jumpTime*jumpTime;
		newX = jumpHeight * jumpTime;
		this->setPosition(sf::Vector2f(groundPosition.x - newX, groundPosition.y - newY));
		if (this->getPosition().y > groundPosition.y)
		{
			this->setPosition(sf::Vector2f(getPosition().x, groundPosition.y));
			getCurrentAnimation()->changeMode(Animation::Mode::play);
		}
		break;
	case State::jumpRight:
		if (this->getPosition().y < groundPosition.y)
		{
			if (getCurrentAnimation()->getCurrentScene().x == getCurrentAnimation()->getEndColumn())
				getCurrentAnimation()->changeMode(Animation::Mode::pause);
		}
		jumpTime = jumpClock.getElapsedTime().asSeconds();
		newY = jumpHeight * 4 * jumpTime + 0.5*-8 * jumpHeight*jumpTime*jumpTime;
		newX = jumpHeight * jumpTime;
		this->setPosition(sf::Vector2f(groundPosition.x + newX, groundPosition.y - newY));
		if (this->getPosition().y > groundPosition.y)
		{
			this->setPosition(sf::Vector2f(getPosition().x, groundPosition.y));
			getCurrentAnimation()->changeMode(Animation::Mode::play);
		}
		break;
	case State::defendLeft:
		if (this->getInput() == "0000000")
		{
			specialState = false;
			this->totalTime = currentFsmState.waitTime + 1;
		}
		else if (this->getInput() == "0100101" or this->getInput() == "0100100")
		{
			specialState = false;
			this->totalTime = currentFsmState.waitTime + 1;
			currentFsmState = FsmState[23];
			this->setCurrentState(currentFsmState.outputState);
		}
		else if (this->getInput() == "0001101" or this->getInput() == "0001100")
		{
			specialState = false;
			this->totalTime = currentFsmState.waitTime + 1;
			currentFsmState = FsmState[22];
			this->setCurrentState(currentFsmState.outputState);
		}
		if (getCurrentAnimation()->getCurrentScene().x == getCurrentAnimation()->getEndColumn())
			getCurrentAnimation()->changeMode(Animation::Mode::pause);
		break;
		break;
	case State::defendRight:
		if (this->getInput() == "0000000")
		{
			specialState = false;
			this->totalTime = currentFsmState.waitTime + 1;
		}
		else if (this->getInput() == "0001101" or this->getInput() == "0001100")
		{
			specialState = false;
			this->totalTime = currentFsmState.waitTime + 1;
			currentFsmState = FsmState[22];
			this->setCurrentState(currentFsmState.outputState);
		}
		else if (this->getInput() == "0100101" or this->getInput() == "0100100")
		{
			specialState = false;
			this->totalTime = currentFsmState.waitTime + 1;
			currentFsmState = FsmState[23];
			this->setCurrentState(currentFsmState.outputState);
		}
		if (getCurrentAnimation()->getCurrentScene().x == getCurrentAnimation()->getEndColumn())
			getCurrentAnimation()->changeMode(Animation::Mode::pause);
		break;
	default:
		break;
	}
	if (this->totalTime >= currentFsmState.waitTime)
	{
		groundPosition = this->getPosition();
		jumpClock.restart();
		if (getInput() == "0000000")
		{
			specialState = true;
		}
		switch (getCurrentState())
		{
		case State::walkLeft:
			this->move(sf::Vector2f(-1.0f,0.0f));
			break;
		case State::walkRight:
			this->move(sf::Vector2f(1.0f, 0.0f));
			break;
		case State::walkUpLeft:
			this->move(sf::Vector2f(0.0f, -1.0f));
			break;
		case State::walkUpAndLeft:
			this->move(sf::Vector2f(-1.0f, -1.0f));
			break;
		case State::walkDownLeft:
			this->move(sf::Vector2f(0.0f, 1.0f));
			break;
		case State::walkDownAndLeft:
			this->move(sf::Vector2f(-1.0f, 1.0f));
			break;
		case State::walkUpRight:
			this->move(sf::Vector2f(0.0f, -1.0f));
			break;
		case State::walkUpAndRight:
			this->move(sf::Vector2f(1.0f, -1.0f));
			break;
		case State::walkDownRight:
			this->move(sf::Vector2f(0.0f, 1.0f));
			break;
		case State::walkDownAndRight:
			this->move(sf::Vector2f(1.0f, 1.0f));
			break;
		case State::attackLeft0:
		case State::attackLeft1:
		{
			this->move(sf::Vector2f(-1.0f, 0.0f));
			break;
		}
		case State::attackRight0:
		case State::attackRight1:
		{
			this->move(sf::Vector2f(1.0f, 0.0f));
			break;
		}
		case State::skillRight0:
			if (this->mana >= vtAnimationEffect[0].useManaPoint)
			{
				vtAnimationEffect[0].setDirection({ 1.0f, 0.0f });
				vtAnimationEffect[0].sprite.setPosition(this->position.x, this->position.y - this->size.y / 1.125);
				vtDisplayEffect.push_back(vtAnimationEffect[0]);
				this->mana -= vtAnimationEffect[0].useManaPoint;
			}
			break;
		case State::skillLeft0:
			if (this->mana >= vtAnimationEffect[1].useManaPoint)
			{
				vtAnimationEffect[1].setDirection({ -1.0f, 0.0f });
				vtAnimationEffect[1].sprite.setPosition(this->position.x - this->size.x, this->position.y - this->size.y + 10);
				vtDisplayEffect.push_back(vtAnimationEffect[1]);
				this->mana -= vtAnimationEffect[1].useManaPoint;
			}
			break;
		default:
			break;
		}
		if (currentFsmState.nextState.count(getInput()) > 0)
		{
			if ( FsmState[currentFsmState.nextState[getInput()]].outputState == State::attackLeft0 || FsmState[currentFsmState.nextState[getInput()]].outputState == State::attackRight0 || FsmState[currentFsmState.nextState[getInput()]].outputState == State::jumpUpLeft|| FsmState[currentFsmState.nextState[getInput()]].outputState == State::defendLeft || FsmState[currentFsmState.nextState[getInput()]].outputState == State::defendRight)
			{
				if (specialState == true)
				{
					currentFsmState = FsmState[currentFsmState.nextState[getInput()]];
					specialState = false;
				}
		
			}
			else
			{
				currentFsmState = FsmState[currentFsmState.nextState[getInput()]];
			}
			/*std::cout << getCurrentState();
			std::cout << " , " << getInput() << "\n";*/
		}
		else
		{
			
			if ( FsmState[currentFsmState.nextState["default"]].outputState == State::attackLeft0 || FsmState[currentFsmState.nextState["default"]].outputState == State::attackRight0 || FsmState[currentFsmState.nextState["default"]].outputState == State::jumpUpLeft || FsmState[currentFsmState.nextState["deault"]].outputState == State::defendLeft || FsmState[currentFsmState.nextState["deault"]].outputState == State::defendRight)
			{
				if (specialState == true)
				{
					currentFsmState = FsmState[currentFsmState.nextState["default"]];
					specialState = false;
				}
			
			}
			else
			{
				currentFsmState = FsmState[currentFsmState.nextState["default"]];
			}
			/*std::cout << getCurrentState();
			std::cout << " , " << "Default\n";*/
			
		}
		if(currentFsmState.outputState != getCurrentState())
			this->setCurrentState(currentFsmState.outputState);
		totalTime = 0.0f;
		
	}

}
void Player::move(sf::Vector2f xy)
{
	currentAnimation->move(xy);
	this->position = currentAnimation->getPosition();
}

std::string Player::getInput()
{
	std::string input;
	if (useJoyStick == false)
	{
		input += std::to_string(sf::Keyboard::isKeyPressed(keyMoveUp));
		input += std::to_string(sf::Keyboard::isKeyPressed(keyMoveLeft));
		input += std::to_string(sf::Keyboard::isKeyPressed(keyMoveDown));
		input += std::to_string(sf::Keyboard::isKeyPressed(keyMoveRight));
		input += std::to_string(sf::Keyboard::isKeyPressed(keyAttack));
		input += std::to_string(sf::Keyboard::isKeyPressed(keyJump));
		input += std::to_string(sf::Keyboard::isKeyPressed(keyDefend));
	}
	else
	{
		switch (joyKeyMoveUp)
		{
			case -1:
				if (sf::Joystick::getAxisPosition(joyNumb, sf::Joystick::Axis::PovY) > 50.0f)
					input += "1";
				else
					input += "0";
				break;
			case -2:
				if (sf::Joystick::getAxisPosition(joyNumb, sf::Joystick::Axis::PovY) < -50.0f)
					input += "1";
				else
					input += "0";
				break;
			case -3:
				if (sf::Joystick::getAxisPosition(joyNumb, sf::Joystick::Axis::PovX) < -50.0f)
					input += "1";
				else
					input += "0";
				break;
			case -4:
				if (sf::Joystick::getAxisPosition(joyNumb, sf::Joystick::Axis::PovX) > 50)
					input += "1";
				else
					input += "0";
				break;
			default:
				input += std::to_string(sf::Joystick::isButtonPressed(joyNumb, joyKeyMoveUp));
				break;
		}
		switch (joyKeyMoveLeft)
		{
		case -1:
			if (sf::Joystick::getAxisPosition(joyNumb, sf::Joystick::Axis::PovY) > 50)
				input += "1";
			else
				input += "0";
			break;
		case -2:
			if (sf::Joystick::getAxisPosition(joyNumb, sf::Joystick::Axis::PovY) <-50)
				input += "1";
			else
				input += "0";
			break;
		case -3:
			if (sf::Joystick::getAxisPosition(joyNumb, sf::Joystick::Axis::PovX) < -50)
				input += "1";
			else
				input += "0";
			break;
		case -4:
			if (sf::Joystick::getAxisPosition(joyNumb, sf::Joystick::Axis::PovX) > 50)
				input += "1";
			else
				input += "0";
			break;
		default:
			input += std::to_string(sf::Joystick::isButtonPressed(joyNumb, joyKeyMoveDown));
			break;
		}
		switch (joyKeyMoveDown)
		{
		case -1:
			if (sf::Joystick::getAxisPosition(joyNumb, sf::Joystick::Axis::PovY) > 50)
				input += "1";
			else
				input += "0";
			break;
		case -2:
			if (sf::Joystick::getAxisPosition(joyNumb, sf::Joystick::Axis::PovY) < -50)
				input += "1";
			else
				input += "0";
			break;
		case -3:
			if (sf::Joystick::getAxisPosition(joyNumb, sf::Joystick::Axis::PovX) < -50)
				input += "1";
			else
				input += "0";
			break;
		case -4:
			if (sf::Joystick::getAxisPosition(joyNumb, sf::Joystick::Axis::PovX) > 50)
				input += "1";
			else
				input += "0";
			break;
		default:
			input += std::to_string(sf::Joystick::isButtonPressed(joyNumb, joyKeyMoveLeft));
			break;
		}
		switch (joyKeyMoveRight)
		{
		case -1:
			if (sf::Joystick::getAxisPosition(joyNumb, sf::Joystick::Axis::PovY) > 50)
				input += "1";
			else
				input += "0";
			break;
		case -2:
			if (sf::Joystick::getAxisPosition(joyNumb, sf::Joystick::Axis::PovY) < -50)
				input += "1";
			else
				input += "0";
			break;
		case -3:
			if (sf::Joystick::getAxisPosition(joyNumb, sf::Joystick::Axis::PovX) < -50)
				input += "1";
			else
				input += "0";
			break;
		case -4:
			if (sf::Joystick::getAxisPosition(joyNumb, sf::Joystick::Axis::PovX) > 50)
				input += "1";
			else
				input += "0";
			break;
		}
		switch (joyKeyAttack)
		{
		case -1:
			if (sf::Joystick::getAxisPosition(joyNumb, sf::Joystick::Axis::PovY) > 50)
				input += "1";
			else
				input += "0";
			break;
		case -2:
			if (sf::Joystick::getAxisPosition(joyNumb, sf::Joystick::Axis::PovY) < -50)
				input += "1";
			else
				input += "0";
			break;
		case -3:
			if (sf::Joystick::getAxisPosition(joyNumb, sf::Joystick::Axis::PovX) < -50)
				input += "1";
			else
				input += "0";
			break;
		case -4:
			if (sf::Joystick::getAxisPosition(joyNumb, sf::Joystick::Axis::PovX) > 50)
				input += "1";
			else
				input += "0";
			break;
		default:
			input += std::to_string(sf::Joystick::isButtonPressed(joyNumb, joyKeyAttack));
			break;
		}
		switch (joyKeyJump)
		{
		case -1:
			if (sf::Joystick::getAxisPosition(joyNumb, sf::Joystick::Axis::PovY) > 50)
				input += "1";
			else
				input += "0";
			break;
		case -2:
			if (sf::Joystick::getAxisPosition(joyNumb, sf::Joystick::Axis::PovY) < -50)
				input += "1";
			else
				input += "0";
			break;
		case -3:
			if (sf::Joystick::getAxisPosition(joyNumb, sf::Joystick::Axis::PovX) < -50)
				input += "1";
			else
				input += "0";
			break;
		case -4:
			if (sf::Joystick::getAxisPosition(joyNumb, sf::Joystick::Axis::PovX) > 50)
				input += "1";
			else
				input += "0";
			break;
		default:
			input += std::to_string(sf::Joystick::isButtonPressed(joyNumb, joyKeyJump));
			break;
		}
		switch (joyKeyDefend)
		{
		case -1:
			if (sf::Joystick::getAxisPosition(joyNumb, sf::Joystick::Axis::PovY) > 50)
				input += "1";
			else
				input += "0";
			break;
		case -2:
			if (sf::Joystick::getAxisPosition(joyNumb, sf::Joystick::Axis::PovY) < -50)
				input += "1";
			else
				input += "0";
			break;
		case -3:
			if (sf::Joystick::getAxisPosition(joyNumb, sf::Joystick::Axis::PovX) < -50)
				input += "1";
			else
				input += "0";
			break;
		case -4:
			if (sf::Joystick::getAxisPosition(joyNumb, sf::Joystick::Axis::PovX) > 50)
				input += "1";
			else
				input += "0";
			break;
		default:
			input += std::to_string(sf::Joystick::isButtonPressed(joyNumb, joyKeyDefend));
			break;
		}
	}
	//std::cout << input << ": "<< sf::Joystick::getAxisPosition(joyNumb,sf::Joystick::PovY) << ": " << sf::Joystick::getAxisPosition(joyNumb, sf::Joystick::PovX)  <<"\n";
	return input;
}

Animation * Player::getCurrentAnimation()
{
	return currentAnimation;
}

int Player::getHitPoint()
{
	return this->hitPoint;
}

sf::Vector2f Player::getPosition()
{
	return this->position;
}

sf::Vector2u Player::getSize()
{
	return this->size;
}

Player::State Player::getCurrentState()
{
	return this->state;
}

sf::Sprite * Player::getCurrentSprite()
{
	return this->currentSprite;
}

Player* Player::createPlayer(Charecter charecter)
{
	Image *playerImage = new Image(SPRITE_PATH + "charecter\\" +std::to_string(charecter)+".png", sf::Vector2u(150, 150), sf::Vector2f(100.0f, 100.0f));
	Image *playerImageMirror = new Image(SPRITE_PATH + "charecter\\" + std::to_string(charecter) + "mirror.png", sf::Vector2u(150, 150), sf::Vector2f(0.0f, 0.0f));
	Animation *playerAnimation0 = new Animation(playerImage, sf::Vector2u(10, 7), 0.15f, Animation::Mode::play);
	Animation *playerAnimationMirror = new Animation(playerImageMirror, sf::Vector2u(10, 7), 0.15f, Animation::Mode::play);
	Player *player = new Player("player", sf::Vector2u(150, 150), sf::Vector2f(250.0f, 700.0f));
	player->addAnimation(playerAnimation0);
	player->addAnimation(playerAnimationMirror);
	player->setAnimationState(Player::State::stayLeft, { 1, 0, 9, 6, 0.15f, 0.005f });
	player->setAnimationState(Player::State::stayRight, { 0, 0, 0, 3, 0.15f, 0.005f });
	player->setAnimationState(Player::State::walkRight, { 0, 0, 4, 7, 0.15f, 0.005f });
	player->setAnimationState(Player::State::walkRight, { 0, 0, 4, 7, 0.15f, 0.005f });
	player->setAnimationState(Player::State::walkUpRight, { 0, 0, 4, 7, 0.15f, 0.005f });
	player->setAnimationState(Player::State::walkUpAndRight, { 0, 0, 4, 7, 0.15f, 0.005f });
	player->setAnimationState(Player::State::walkDownRight, { 0, 0, 4, 7, 0.15f, 0.005f });
	player->setAnimationState(Player::State::walkDownAndRight, { 0, 0, 4, 7, 0.15f, 0.005f });
	player->setAnimationState(Player::State::walkLeft, { 1, 0, 5, 2, 0.15f, 0.005f });
	player->setAnimationState(Player::State::walkLeft, { 1, 0, 5, 2, 0.15f, 0.005f });
	player->setAnimationState(Player::State::walkUpAndLeft, { 1, 0, 5, 2, 0.15f, 0.005f });
	player->setAnimationState(Player::State::walkUpLeft, { 1, 0, 5, 2, 0.15f, 0.005f });
	player->setAnimationState(Player::State::walkDownLeft, { 1, 0, 5, 2, 0.15f, 0.005f });
	player->setAnimationState(Player::State::walkDownAndLeft, { 1, 0, 5, 2, 0.15f, 0.005f });
	player->setAnimationState(Player::State::jumpLeft, { 1, 6, 9, 7, 0.125f, 0.999 });
	player->setAnimationState(Player::State::jumpRight, { 0, 6, 0, 2, 0.125f, 0.999 });
	player->setAnimationState(Player::State::jumpUpLeft, { 1, 6, 9, 7, 0.15f , 0.999 });
	player->setAnimationState(Player::State::jumpUpRight, { 0, 6, 0, 2, 0.15f, 0.999 });
	player->setAnimationState(Player::State::attackRight0, { 0, 1, 0, 1, 0.2f, 0.4f });
	player->setAnimationState(Player::State::attackRight1, { 0, 1, 2, 3, 0.2f, 0.4f });
	player->setAnimationState(Player::State::attackRight2, { 0, 1, 4, 5, 0.2f, 0.4f });
	player->setAnimationState(Player::State::attackLeft0, { 1, 1, 9, 8, 0.2f, 0.4f });
	player->setAnimationState(Player::State::attackLeft1, { 1, 1, 7, 6, 0.2f, 0.4f });
	player->setAnimationState(Player::State::attackLeft2, { 1, 1, 5, 4, 0.2f, 0.4f });
	player->setAnimationState(Player::State::defendLeft, { 1, 5, 3, 2, 0.2f, 0.4f });
	player->setAnimationState(Player::State::defendRight, { 0, 5, 6, 7, 0.2f, 0.4f });
	player->setCurrentState(Player::State::stayRight);
	player->setJumpHeight(200.0);
	player->setUpdateEventTime(0.0f);
	player->charecter = charecter;

	AnimationEffect *powerBall = new AnimationEffect(std::to_string(charecter) + "skill0.png", { 4,3 }, 0.1f);
	powerBall->setMoveTime(0.0);
	powerBall->setSize({ 100,100 });
	powerBall->setAttackPoint(0.1f);
	powerBall->setUseManaPoint(10.0f);
	player->vtAnimationEffect.push_back(*powerBall);
	AnimationEffect *powerBallMirror = new AnimationEffect(std::to_string(charecter) + "skill0mirror.png", { 4,3 }, 0.1f);
	powerBallMirror->setSize({ 100,100 });
	powerBallMirror->setMoveTime(0.0);
	powerBallMirror->setAttackPoint(0.1f);
	powerBallMirror->setUseManaPoint(10.0f);
	player->vtAnimationEffect.push_back(*powerBallMirror);
	return player;
}


Player::~Player()
{

}
