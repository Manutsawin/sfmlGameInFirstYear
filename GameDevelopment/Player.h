#pragma once
#include"Animation.h"
#include<iostream>
#include"AnimationEffect.h"
static const std::string SPRITE_PATH = "image\\sprite\\sys\\";
static const std::string BG_PATH = "image\\bg\\sys\\";
class Player
{
public:
	enum State {
		stayLeft,stayRight,walkLeft, walkUpLeft,walkUpAndLeft,walkDownLeft,walkDownAndLeft,walkRight,walkUpRight,walkUpAndRight, walkDownRight,walkDownAndRight,
		jumpLeft,jumpRight,jumpUpLeft, jumpUpRight,attackRight0, attackRight1, attackRight2,attackLeft0, attackLeft1,attackLeft2,defendLeft,defendRight,
		skillRight0,skillLeft0
	};
	enum Key {
		keyMoveUpValue,keyMoveDownValue,keyMoveLeftValue,keyMoveRightValue,keyAttackValue,keyJumpValue,keyDefendValue
	};
	enum Face {
		left,right
	};
	enum  Charecter
	{
		unknow=-1,bandit=0,bandit0b,bat,davis,deep,dennis,firen,firzen,freeze,henry,hunter,hunter0b,
		jack,jack0b,jan,john,julian, justin, justin0b,knight,knight0b,louis,mark,mark0b,monk,monk0b,rudolf,sorcerer,sorceror0b,woody

	};
	struct ANIMATION_STATE {
		uint16_t indexAnimation;
		uint16_t row;
		uint16_t startColumn;
		uint16_t endColumn;
		float switchTime;
		float useTime;
	};

	struct FSM_STATE {
		State outputState;
		float  waitTime;
		std::map<std::string, int> nextState;
	};
	
	Player();
	Player(std::string name,sf::Vector2u size,sf::Vector2f position);
	void addAnimation(Animation *animation);
	void addAnimationEffect(AnimationEffect animationEffect);
	void increaseHitPoint(float point);
	void setAnimationState(State state , ANIMATION_STATE animationState);
	void setCurrentState(State state);
	void setCurrentAnimation(State state);
	void setHitPoint(float hitPoint);
	void setJumpTime(float jumpTime);
	void setJumpHeight(float jumpHeight);
	void setKey(Key key, sf::Keyboard::Key keyValue);
	void setKey(Key key, int joyButton);
	void setMapSize(sf::Vector2u size);
	void setMoveSpeed(float moveSpeed);
	void setPosition(sf::Vector2f position);
	void setSize(sf::Vector2u size);	
	void setUpdateEventTime(float updateEventTime);
	void update(float deltaTime);
	void updateEvent(float deltaTime);
	void move(sf::Vector2f xy);	
	Animation *getCurrentAnimation();
	int getHitPoint();
	std::string getInput();
	sf::Vector2f getPosition();
	sf::Vector2u getSize();
	Player::State getCurrentState();
	sf::Sprite *getCurrentSprite();
	Player* createPlayer(Charecter charecter);
	virtual ~Player();
public:
	std::string name;
	std::string who;
	sf::Text whoText;
	sf::Text scoreText;
	sf::Font whoFont;
	sf::Vector2u size;
	sf::Sprite *currentSprite;
	sf::Vector2f position;
	State state;
	std::vector<Animation*> vtAnimation;
	std::map<State, ANIMATION_STATE> animationState;
	std::vector<AnimationEffect> vtAnimationEffect;
	std::vector<AnimationEffect> vtDisplayEffect;
	Animation *currentAnimation;
	float totalTime;
	float updateEventTime;
	float jumpTime;
	float jumpHeight;
	float moveSpeed;
	sf::Vector2f groundPosition;
	sf::Vector2u mapSize;
	sf::Keyboard::Key keyMoveLeft;
	sf::Keyboard::Key keyMoveRight;
	sf::Keyboard::Key keyMoveUp;
	sf::Keyboard::Key keyMoveDown;
	sf::Keyboard::Key keyJump;
	sf::Keyboard::Key keyAttack;
	sf::Keyboard::Key keyDefend;
	int joyNumb;
	int joyKeyMoveLeft;
	int joyKeyMoveRight;
	int joyKeyMoveUp;
	int joyKeyMoveDown;
	int joyKeyJump;
	int joyKeyAttack;
	int joyKeyDefend;
	Face face;
	bool specialState;
	sf::Clock jumpClock;
	FSM_STATE currentFsmState;
	FSM_STATE FsmState[30];
	std::map<State, FSM_STATE> stateEvent;
	float hitPoint;
	float hp;
	float mana;
	float attackPoint;
	float protectPoint;
	double score;
	bool useJoyStick;
	Charecter charecter;
	bool winner;
};

