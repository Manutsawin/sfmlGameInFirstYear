#include "GameEngine.h"
#include"Draw.h"
static const std::string SPRITE_PATH = "image\\sprite\\sys\\";
GameEngine::GameEngine(sf::Vector2u size, std::string title):thread(&GameEngine::runThread,this)
{
	this->size = size;
	this->title = title;
	this->style = -1;
}
GameEngine::GameEngine(sf::Vector2u size, std::string title,int32_t style) :thread(&GameEngine::runThread, this)
{
	this->size = size;
	this->title = title;
	this->style = style;
}
GameEngine::~GameEngine()
{
}
void GameEngine::run() {

	thread.launch();
}

void GameEngine::runThread() {
	if (style != -1)
	{
		if(style & sf::Style::Fullscreen)
			window.create(sf::VideoMode(1366/size.x, 800/size.y), title,sf::Style::Fullscreen);
	}
	else
		window.create(sf::VideoMode(size.x, size.y), title, sf::Style::Default);
	running = true;
	while(isRunning())
	{
		switch (scene)
		{
		case GameEngine::mainMenu :
			{
				runMainMenu();
				break;
			}
			case GameEngine::demo :
			{
				runDemo();
				break;
			}
			default:
				break;
		}	
	}
}
bool GameEngine::isRunning() {
	return running;
}
void GameEngine::setScene(Scene scene)
{
	this->scene = scene;
}

void GameEngine::runMainMenu()
{
	int select = 0;
	bool exit = false;
	Draw draw;
	draw.setWindow(&window);
	Image *background = new Image("image\\bg\\main-menu-bg.jpg", sf::Vector2u(800, 600), sf::Vector2f(0, 0));
	draw.add(background);
	sf::Font titleFont;
	if (!titleFont.loadFromFile("font\\ARMY_RUST.ttf"))
	{
		std::cout << "Error load font\\ARMY_RUST.ttf";
	}
	sf::Text *titleText = new sf::Text();
	titleText->setFont(titleFont);
	titleText->setString("Fight For Frank");
	titleText->setCharacterSize(70);
	titleText->setFillColor(sf::Color::Black);
	titleText->setPosition(180,50);
	titleText->setOutlineColor(sf::Color(135, 36, 14));
	titleText->setOutlineThickness(2.0f);
	draw.add(titleText);
	sf::Font menuFont;
	if (!menuFont.loadFromFile("font\\bangkok_regular_v1-0.ttf"))
	{
		std::cout << "Error load font\\bangkok_regular_v1-0.ttf";
	}
	sf::Text *menuText1 = new sf::Text();
	menuText1->setFont(menuFont);
	menuText1->setString("play demo");
	menuText1->setCharacterSize(50);
	menuText1->setFillColor(sf::Color::Black);
	menuText1->setPosition(290,200);
	draw.add(menuText1);

	sf::Text *menuText2 = new sf::Text();
	menuText2->setFont(menuFont);
	menuText2->setString("exit");
	menuText2->setCharacterSize(50);
	menuText2->setFillColor(sf::Color::Black);
	menuText2->setPosition(350, 250);
	draw.add(menuText2);

	sf::Event event;
	sf::Mouse mouse;
	sf::Clock clock;
	float deltaTime;
	while (!exit)
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				close();
				exit = true;
			}
			
		}
		deltaTime = clock.restart().asSeconds();
		window.clear();

		/* keyboard event */
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			select = 0;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			select = 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			if (select == 0)
			{
				setScene(GameEngine::Scene::demo);
				exit = true;
			}
			else if (select == 1)
			{
				close();
				exit = true;
			}
		}
		/* mouse event*/
		if (checkMouseCollision(menuText1))
		{
			select = 0;
		}
		else if (checkMouseCollision(menuText2))
		{
			select = 1;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			if (checkMouseCollision(menuText1))
			{
				setScene(GameEngine::Scene::demo);
				exit = true;
			}
			else if (checkMouseCollision(menuText2))
			{
				close();
				exit = true;
			}
		}
		draw.update(deltaTime);
		switch (select)
		{
			case 0:
			{
				menuText1->setOutlineColor(sf::Color::White);
				menuText1->setOutlineThickness(1.0f);
				menuText2->setOutlineThickness(0.0f);
				break;
			}
			case 1:
			{
				menuText2->setOutlineColor(sf::Color::White);
				menuText2->setOutlineThickness(1.0f);
				menuText1->setOutlineThickness(0.0f);
				break;
			}
		}
		draw.draw();
		window.display();
	}

	
}
 void GameEngine::runDemo()
{
	bool exit = false;
	Draw draw;
	draw.setWindow(&window);
	sf::Event event;
	sf::Mouse mouse;
	sf::Clock clock;
	float deltaTime;
	/* add component*/

	Image *banditImage0 = new Image(SPRITE_PATH+"bandit_0.png", sf::Vector2u(100, 100), sf::Vector2f(0.0f,0.0f));
	Image *banditImage0Mirror = new Image(SPRITE_PATH + "bandit_0_mirror.png", sf::Vector2u(100, 100), sf::Vector2f(0.0f, 0.0f));
	Animation *banditAnimation0 = new Animation(banditImage0, sf::Vector2u(10, 7), 0.15f, Animation::Mode::play);
	Animation *banditAnimation0Mirror = new Animation(banditImage0Mirror, sf::Vector2u(10, 7), 0.15f, Animation::Mode::play);
	Player *bandit = new Player("bandit", sf::Vector2u(100, 100), sf::Vector2f(window.getSize().x/2.0f, window.getSize().y/2.0f));

	bandit->addAnimation(banditAnimation0);
	bandit->addAnimation(banditAnimation0Mirror);
	bandit->setAnimationState(Player::State::stayLeft,  { 1, 0, 9, 6, 0.3f, 0 });
	bandit->setAnimationState(Player::State::stayRight, { 0, 0, 0, 3, 0.3f, 0 });
	bandit->setAnimationState(Player::State::walkRight, { 0, 0, 4, 7, 0.3f, 0 });
	bandit->setAnimationState(Player::State::walkLeft,  { 1, 0, 5, 2, 0.3f, 0 });
	bandit->setAnimationState(Player::State::jumpLeft,  { 1, 6, 9, 6, 0.15f, 1 });
	bandit->setAnimationState(Player::State::jumpRight, { 0, 6, 0, 3, 0.15f, 1 });
	bandit->setAnimationState(Player::State::jumpUpLeft,{ 1, 6, 9, 7, 0.15f , 1 });
	bandit->setAnimationState(Player::State::jumpUpRight,{ 0, 6, 0, 2, 0.15f, 1 });
	bandit->setCurrentState(Player::State::stayRight);
	bandit->setUpdateEventTime(0.005f);
	draw.add(bandit);
	while (!exit)
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				close();
				exit = true;
			}

		}
		deltaTime = clock.restart().asSeconds();
		window.clear(sf::Color::White);
		/* keyboard event */
		
		/* mouse event*/


		/* update part*/
		bandit->updateEvent(deltaTime);
		draw.update(deltaTime);

		draw.draw();
		window.display();
	}
}
bool GameEngine::checkMouseCollision(sf::Text * text)
{
	sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
	
	if (text->getGlobalBounds().contains(mousePosition))
		return true;
	else
		return false;
}
int GameEngine::close() {
	running = false;
	return 0;
}

void GameEngine::keyboardEvent(Scene scene) {
	switch (scene)
	{
		case GameEngine::mainMenu:
		{
			break;
		}
		case GameEngine::demo:
			break;
		default:
			break;
	}
}

