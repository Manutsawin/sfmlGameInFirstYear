#pragma once
#include<SFML/Graphics.hpp>
#include<string>
#include<iostream>
#include<fstream>
#include"AnimationEffect.h"
#include"Result.h"
#include<random>
class GameEngine
{
public:
	enum Scene
	{
		mainMenu,controlSetting,pvpMode,highScore,selectCharecter,setPlayerName,setTotalPlayer
	};
	struct KeyValue{
		bool joyEnable;
		int joyNumb;
		int joyCode;
		int keyCode;
	};
	GameEngine(sf::Vector2u size, std::string title);
	GameEngine(sf::Vector2u size, std::string title, int32_t style);
	void run();
	int close();
	void runThread();
	void initial();
	bool isRunning();
	void setScene(Scene scene);
	Result runMainMenu(Result result);
	Result runPvpMode(Result result);
	Result runHighScore(Result result);
	Result runControlSetting(Result result);
	Result runSelectCharecter(Result result);
	Result runSetPlayerName(Result result);
	Result runSetTotalPlayer(Result result);
	bool checkMouseCollision(sf::Text *text);
	float computeDistance(sf::Vector2f point1, sf::Vector2f point2);
	sf::Vector2f compareXY(sf::Vector2f point1, sf::Vector2f point2);
	std::string keyToStr(sf::Keyboard::Key key);
	std::string joyKeyToStr(int joyButton);
	void updateHighScore(std::string name, float score);
	unsigned long long  getAndSetRandom(unsigned long long randomNumber,bool choice);
	virtual ~GameEngine();
	std::string getFormatInput(std::string input);
public:
	sf::RenderWindow window;
	std::string title;
	uint32_t style;
	sf::Vector2u size;
	bool running;
	sf::Thread thread;
	Scene scene;
	std::vector<KeyValue> vtKeyCode;
	unsigned long long randomNumber;
	bool *exitMain;
};
/*scene templete*/

	//bool exit = false;
	//Draw draw;
	//draw.setWindow(&window);
	//sf::Event event;
	//sf::Mouse mouse;
	//sf::Clock clock;
	//float deltaTime;
	///* add component*/
	//while (!exit)
	//{
	//while (window.pollEvent(event))
	//{
	//	if (event.type == sf::Event::Closed)
	//	{
	//		close();
	//		exit = true;
	//	}
	//	else if (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Escape)
	//	{
	//		this->setScene(Scene::mainMenu);
	//		exit = true;
	//	}

	//}
	//deltaTime = clock.restart().asSeconds();
	//window.clear();
	///* keyboard event */

	///* mouse event*/

	//draw.update(deltaTime);
	///* update part*/

	//draw.draw();
	//window.display();
	//}


