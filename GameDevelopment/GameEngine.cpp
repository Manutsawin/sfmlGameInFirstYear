#include "GameEngine.h"
#include"Draw.h"
#include "Collision.h"
#include "GameControl.h"
#include "SFML/Audio.hpp"
#include <iomanip> 
#include <sstream>
#include<limits>
#include"Item.h";
#include<time.h>

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

std::string GameEngine::getFormatInput(std::string input)
{
	std::string tmpString = input;
	std::swap(tmpString[1], tmpString[2]);
	return tmpString;
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
	window.setFramerateLimit(200);
	running = true;
	Result result;
	while(isRunning())
	{
		switch (scene)
		{
		case GameEngine::mainMenu :
			{
				runMainMenu(Result());
				break;
			}
			case GameEngine::pvpMode:
			{
				runPvpMode(result);
				break;
			}
			case GameEngine::highScore:
			{
				runHighScore(Result());
				break;
			}
			case GameEngine::controlSetting:
			{
				runControlSetting(Result());
				break;
			}
			case GameEngine::selectCharecter:
			{

				result = runSelectCharecter(result);
				if (result.resultString[0] == "pvpMode")
				{
						runPvpMode(result);
				}
				else if (result.resultString[0] == "mainMenu")
					this->setScene(Scene::mainMenu);
				break;
			}
			case GameEngine::setPlayerName:
			{
				result = runSetPlayerName(result);
				if (result.resultString[0] == "mainMenu")
				{
					this->setScene(Scene::mainMenu);
				}
				else if (result.resultString[0] == "selectCharecter")
				{
					this->setScene(Scene::selectCharecter);
				}
				else if (result.resultString[0] == "setTotalPlayer")
				{
					this->setScene(Scene::setTotalPlayer);
				}
				break;
			}
			case GameEngine::setTotalPlayer:
			{
				result = runSetTotalPlayer(Result());
				break;
			}
			default:
				break;
		}	
	}
	*this->exitMain = true;
}

void GameEngine::initial()
{
	std::fstream myfile;
	myfile.open("control.dat");
	if (!myfile.good())
	{
		std::cout << "create control.dat\n";
		myfile.open("control.dat", std::fstream::out);
		myfile << "<player0>\n";
		myfile << "<key name=\"keyMoveUp0\">" << std::setw(4) << 0 << "," << std::setw(4)<< 0 <<"," << std::setw(4) << 0<<"," <<std::setw(4)<<sf::Keyboard::W<<"</key>\n";
		myfile << "<key name=\"keyMoveDown0\">" << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << sf::Keyboard::S << "</key>\n";
		myfile << "<key name=\"keyMoveLeft0\">" << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << sf::Keyboard::A << "</key>\n";
		myfile << "<key name=\"keyMoveRight0\">" << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << sf::Keyboard::D << "</key>\n";
		myfile << "<key name=\"keyMoveAttack0\">" << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << sf::Keyboard::J << "</key>\n";
		myfile << "<key name=\"keyMoveJump0\">" << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << sf::Keyboard::K << "</key>\n";
		myfile << "<key name=\"keyMoveDefend0\">" << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << sf::Keyboard::L << "</key>\n";
		myfile << "</player0>\n";
		myfile << "<player1>\n";
		myfile << "<key name=\"keyMoveUp1\">" << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << sf::Keyboard::Up << "</key>\n";
		myfile << "<key name=\"keyMoveDown1\">" << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << sf::Keyboard::Down << "</key>\n";
		myfile << "<key name=\"keyMoveLeft1\">" << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << sf::Keyboard::Left << "</key>\n";
		myfile << "<key name=\"keyMoveRight1\">" << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << sf::Keyboard::Right << "</key>\n";
		myfile << "<key name=\"keyMoveAttack1\">" << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << sf::Keyboard::Numpad1 << "</key>\n";
		myfile << "<key name=\"keyMoveJump1\">" << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << sf::Keyboard::Numpad2 << "</key>\n";
		myfile << "<key name=\"keyMoveDefend1\">" << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << sf::Keyboard::Numpad3 << "</key>\n";
		myfile << "</player1>\n";
		myfile << "<player2>\n";
		myfile << "<key name=\"keyMoveUp2\">" << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << sf::Keyboard::Up << "</key>\n";
		myfile << "<key name=\"keyMoveDown2\">" << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << sf::Keyboard::Down << "</key>\n";
		myfile << "<key name=\"keyMoveLeft2\">" << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << sf::Keyboard::Left << "</key>\n";
		myfile << "<key name=\"keyMoveRight2\">" << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << sf::Keyboard::Right << "</key>\n";
		myfile << "<key name=\"keyMoveAttack2\">" << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << sf::Keyboard::Numpad1 << "</key>\n";
		myfile << "<key name=\"keyMoveJump2\">" << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << sf::Keyboard::Numpad2 << "</key>\n";
		myfile << "<key name=\"keyMoveDefend2\">" << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << sf::Keyboard::Numpad3 << "</key>\n";
		myfile << "</player2>\n";
		myfile << "<player3>\n";
		myfile << "<key name=\"keyMoveUp3\">" << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << sf::Keyboard::Up << "</key>\n";
		myfile << "<key name=\"keyMoveDown3\">" << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << sf::Keyboard::Down << "</key>\n";
		myfile << "<key name=\"keyMoveLeft3\">" << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << sf::Keyboard::Left << "</key>\n";
		myfile << "<key name=\"keyMoveRight3\">" << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << sf::Keyboard::Right << "</key>\n";
		myfile << "<key name=\"keyMoveAttack3\">" << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << sf::Keyboard::Numpad1 << "</key>\n";
		myfile << "<key name=\"keyMoveJump3\">" << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << sf::Keyboard::Numpad2 << "</key>\n";
		myfile << "<key name=\"keyMoveDefend3\">" << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << 0 << "," << std::setw(4) << sf::Keyboard::Numpad3 << "</key>\n";
		myfile << "</player3>\n";
		myfile.close();
	}
	else
	{
		std::cout << "control.dat is exist\n";
	}
	std::fstream myfile2;
	myfile2.open("highScore.dat");
	if (!myfile2.good())
	{
		myfile2.close();
		std::cout << "create highScore.dat\n";
		myfile2.open("highScore.dat", std::fstream::out);
		myfile2 << "<highScore>\n";
		myfile2 << "01name:"<<std::left <<std::setw(20)<<""<<"score:" << std::left <<std::setw(20)<<""<<"\n";
		myfile2 << "02name:" << std::left << std::setw(20) << "" << "score:" << std::left << std::setw(20) << "-1.0" << "\n";
		myfile2 << "03name:" << std::left << std::setw(20) << "" << "score:" << std::left << std::setw(20) << "-1.0" << "\n";
		myfile2 << "04name:" << std::left << std::setw(20) << "" << "score:" << std::left << std::setw(20) << "-1.0" << "\n";
		myfile2 << "05name:" << std::left << std::setw(20) << "" << "score:" << std::left << std::setw(20) << "-1.0" << "\n";
		myfile2 << "</highScore>\n";
		myfile2.close();
	}
	else
	{
		std::cout << "highScore.dat is exist\n";
	}
	
}

bool GameEngine::isRunning() {
	return running;
}

void GameEngine::setScene(Scene scene)
{
	this->scene = scene;
}

Result GameEngine::runMainMenu(Result result)
{
	sf::Music bgMusic;
	bgMusic.openFromFile("sound/bgm/main.ogg");
	bgMusic.setLoop(true);
	bgMusic.setVolume(50);
	bgMusic.play();
	int select = 0;
	bool exit = false;
	Draw draw;
	draw.setWindow(&window);
	Image *background = new Image("image\\bg\\main-menu-bg.jpg", sf::Vector2u(1000, 800), sf::Vector2f(0, 0));
	draw.add(background);
	sf::Font titleFont;
	if (!titleFont.loadFromFile("font\\ARMY_RUST.ttf"))
	{
		std::cout << "Error load font\\ARMY_RUST.ttf";
	}
	sf::Text *titleText = new sf::Text();
	titleText->setFont(titleFont);
	titleText->setString("Fight For Frank");
	titleText->setCharacterSize(75);
	titleText->setFillColor(sf::Color::Black);
	titleText->setPosition(180+100, 50+80);
	titleText->setOutlineColor(sf::Color(135, 36, 14));
	titleText->setOutlineThickness(2.0f);
	draw.add(titleText);
	sf::Font menuFont;
	if (!menuFont.loadFromFile("font\\bangkok_regular_v1-0.ttf"))
	{
		std::cout << "Error load font\\bangkok_regular_v1-0.ttf";
	}


	sf::Text *menuText2 = new sf::Text();
	menuText2->setFont(menuFont);
	menuText2->setString("play");
	menuText2->setCharacterSize(55);
	menuText2->setFillColor(sf::Color(99, 99, 26));
	menuText2->setPosition(310+180, 200+80);
	draw.add(menuText2);

	sf::Text *menuText3 = new sf::Text();
	menuText3->setFont(menuFont);
	menuText3->setString("high score");
	menuText3->setCharacterSize(55);
	menuText3->setFillColor(sf::Color(99, 99, 26));
	menuText3->setPosition(308+120, 250+80);
	draw.add(menuText3);

	sf::Text *menuText4 = new sf::Text();
	menuText4->setFont(menuFont);
	menuText4->setString("control setting");
	menuText4->setCharacterSize(55);
	menuText4->setFillColor(sf::Color(99, 99, 26));
	menuText4->setPosition(270+120, 300+80);
	draw.add(menuText4);

	sf::Text *menuText5 = new sf::Text();
	menuText5->setFont(menuFont);
	menuText5->setString("exit");
	menuText5->setCharacterSize(55);
	menuText5->setFillColor(sf::Color(99, 99, 26));
	menuText5->setPosition(365+120, 350+80);
	draw.add(menuText5);

	sf::Font developerFont;
	if (!developerFont.loadFromFile("font\\FC_Lamoon_Bold_ver_1.00.ttf"))
	{
		std::cout << "Error load font\\FC_Lamoon_Bold_ver_1.00.ttf";
	}
	sf::Text *developerText = new sf::Text();
	developerText->setFont(developerFont);
	developerText->setString("Developed by Kiadtisak Buangam ID 61010103");
	developerText->setCharacterSize(45);
	developerText->setFillColor(sf::Color(128, 139, 150));
	developerText->setPosition(80+100, 450+80);
	developerText->setOutlineColor(sf::Color(0, 0, 0));
	developerText->setOutlineThickness(2.0f);
	draw.add(developerText);
	sf::Event event;
	sf::Mouse mouse;
	sf::Clock clock;
	float deltaTime;
	bool pressed = false;
	window.setView(window.getDefaultView());
	std::fstream myFile;
	std::string word;
	myFile.open("control.dat");
	if (!myFile.is_open())
	{
		std::cout << "open control.dat failed\n";
	}
	
	std::string tmpNumb;
	vtKeyCode.clear();
	KeyValue tmpKey;
	while (std::getline(myFile, word))
	{
		if (word.find("\">") != std::string::npos)
		{
			
			for (int i = 0 ; i < 4; i++)
			{	
				tmpNumb = "";
				for (int j = word.find("\">") +5 * i+2; j < word.find("\">") + 5 * i + 6; j++)
				{
					tmpNumb += word[j];
				}
				switch (i)
				{
				case 0 :
					tmpKey.joyEnable = std::stoi(tmpNumb, NULL);
					break;
				case 1:
					tmpKey.joyNumb = std::stoi(tmpNumb, NULL);
					break;
				case 2:
					tmpKey.joyCode = std::stoi(tmpNumb, NULL);
					break;
				case 3:
					tmpKey.keyCode = std::stoi(tmpNumb, NULL);
					break;
				default:
					break;
				}

			}
			vtKeyCode.push_back(tmpKey);
		}
	}
	myFile.close();
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) and !pressed)
		{
			select--;
			if (select < 0)
				select = 4;
			pressed = true;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) and !pressed)
		{
			select++;
			select %= 5;
			pressed = true;
		}

		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) and !sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			pressed = false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			switch (select)
			{
			case 1:
				setScene(GameEngine::Scene::setTotalPlayer);
				exit = true;
				break;
			case 2:
				setScene(GameEngine::Scene::highScore);
				exit = true;
				break;
			case 3:
				setScene(GameEngine::Scene::controlSetting);
				exit = true;
				break;
			case 4:
				close();
				exit = true;
				break;
			default:
				break;
			}

		}
		/* mouse event*/
		else if (checkMouseCollision(menuText2))
		{
			select = 1;
		}
		else if (checkMouseCollision(menuText3))
		{
			select = 2;
		}
		else if (checkMouseCollision(menuText4))
		{
			select = 3;
		}
		else if (checkMouseCollision(menuText5))
		{
			select = 4;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			if (checkMouseCollision(menuText2))
			{
				setScene(GameEngine::Scene::setTotalPlayer);
				exit = true;
			}
			else if (checkMouseCollision(menuText3))
			{
				setScene(GameEngine::Scene::highScore);
				exit = true;
			}
			else if (checkMouseCollision(menuText4))
			{
				setScene(GameEngine::Scene::controlSetting);
				exit = true;
			}
			else if (checkMouseCollision(menuText5))
			{
				close();
				exit = true;
			}
		}
		draw.update(deltaTime);
		switch (select)
		{
		case 1:
		{
			menuText2->setOutlineColor(sf::Color::White);
			menuText2->setOutlineThickness(2.0f);
			menuText3->setOutlineThickness(0.0f);
			menuText4->setOutlineThickness(0.0f);
			menuText5->setOutlineThickness(0.0f);
			break;
		}
		case 2:
		{
			menuText3->setOutlineColor(sf::Color::White);
			menuText3->setOutlineThickness(2.0f);
			menuText2->setOutlineThickness(0.0f);
			menuText4->setOutlineThickness(0.0f);
			menuText5->setOutlineThickness(0.0f);
			break;
		}
		case 3:
		{
			menuText4->setOutlineColor(sf::Color::White);
			menuText4->setOutlineThickness(2.0f);
			menuText2->setOutlineThickness(0.0f);
			menuText3->setOutlineThickness(0.0f);
			menuText5->setOutlineThickness(0.0f);
			break;
		}
		case 4:
		{
			menuText5->setOutlineColor(sf::Color::White);
			menuText5->setOutlineThickness(2.0f);
			menuText2->setOutlineThickness(0.0f);
			menuText3->setOutlineThickness(0.0f);
			menuText4->setOutlineThickness(0.0f);
			break;
		}
		}
		draw.draw();
		window.display();
	}
	bgMusic.stop();
	return Result();
}

Result GameEngine::runPvpMode(Result result)
{
	sf::Music bgMusic;
	bgMusic.openFromFile("sound/bgm/stage1.ogg");
	bgMusic.setLoop(true);
	bgMusic.setVolume(20);
	bgMusic.play();
	GameControl gameControl;
	gameControl.setUpdateTime(0.4);
	gameControl.randomNumber = &this->randomNumber;
	Collision collision;
	bool exit = false;
	Draw draw, drawUi;
	draw.setWindow(&window);
	drawUi.setWindow(&window);
	sf::Event event;
	sf::Mouse mouse;
	sf::Clock clock;
	float deltaTime;
	sf::View view, uiView;;
	view.setSize(800.0f, 600.0f);
	view.setViewport(sf::FloatRect(0, 0.3, 1, 0.7));
	uiView.setSize(800.0f, 600.0f);
	uiView.setViewport(sf::FloatRect(0, 0, 1, 0.3));

	/* add component*/
	Image *bgFloor1_1 = new Image(BG_PATH + "cuhk\\floor3.png", sf::Vector2u(2500, 800), sf::Vector2f(0.0f, 0.0f));
	draw.add(bgFloor1_1);
	draw.setMapSize(bgFloor1_1->getSize());
	Player player;
	std::vector<Player*> vtPlayer;

	if (result.resultInt.size() != 0)
	{
		for (int i = 0; i < result.resultInt.size(); i++)
		{
			vtPlayer.push_back(player.createPlayer(Player::Charecter(result.resultInt[i])));
			vtPlayer[i]->who = "P" + std::to_string(i + 1);
			vtPlayer[i]->name = result.resultString[i + 1];
			for (int j = i * 7; j < (i + 1) * 7; j++)
			{
				std::cout << j << ":";
				if (vtKeyCode[i * 7].joyEnable == 1)
				{
					vtPlayer[i]->useJoyStick = true;
					vtPlayer[i]->setKey(Player::Key(j % 7), vtKeyCode[j].joyCode);
					vtPlayer[i]->joyNumb = vtKeyCode[j].joyNumb;
				}
				else
				{
					vtPlayer[i]->setKey(Player::Key(j % 7), sf::Keyboard::Key(vtKeyCode[j].keyCode));
				}

			}
			vtPlayer[i]->setPosition(sf::Vector2f(window.getSize().x / 2.0, window.getSize().y / 2.0));
			vtPlayer[i]->setSize(sf::Vector2u(100, 100));
			draw.add(vtPlayer[i]);
			gameControl.add(vtPlayer[i]);
		}
	}
	else
	{
		vtPlayer.push_back(player.createPlayer(Player::Charecter::bandit));
		vtPlayer[0]->setPosition(sf::Vector2f(window.getSize().x / 2.0, window.getSize().y / 2.0));
		vtPlayer[0]->setSize(sf::Vector2u(100, 100));
		draw.add(vtPlayer[0]);
		if (vtKeyCode[0].joyEnable == 1)
			vtPlayer[0]->useJoyStick = true;
		else
			vtPlayer[0]->useJoyStick = false;
		for (int i = 0; i < 7; i++)
		{
			if (vtPlayer[0]->useJoyStick == true)
				vtPlayer[0]->setKey(Player::Key(i), vtKeyCode[i].joyCode);
			else
				vtPlayer[0]->setKey(Player::Key(i), vtKeyCode[i].keyCode);
		}
		gameControl.add(vtPlayer[0]);
	}




	sf::RectangleShape uiBackground;
	uiBackground.setSize(sf::Vector2f(800, 600));
	uiBackground.setPosition(0.0f, 0.0f);
	uiBackground.setFillColor(sf::Color::Magenta);
	drawUi.add(&uiBackground);
	uiView.setCenter(uiBackground.getSize().x / 2.0, uiBackground.getSize().y / 2.0);

	std::vector<sf::RectangleShape *> hpBar, manaBar;
	sf::Font defaultFont;
	if (!defaultFont.loadFromFile("font\\bangkok_regular_v1-0.ttf"))
	{
		std::cout << "Error load font\\bangkok_regular_v1-0.ttf";
	}
	for (int i = 0; i < vtPlayer.size(); i++)
	{
		sf::RectangleShape *tmpRect = new sf::RectangleShape();
		sf::Texture *tmpTexture = new sf::Texture();
		tmpTexture->loadFromFile(SPRITE_PATH + "charecter\\" + std::to_string(vtPlayer[i]->charecter) + "bigPic.png");
		tmpRect->setTexture(tmpTexture);
		tmpRect->setSize(sf::Vector2f(200, 160));
		tmpRect->setPosition(i*100.0f + 25.0f + i * 80, 50.0f);
		tmpRect->setOutlineColor(sf::Color::Black);
		tmpRect->setOutlineThickness(5.0);
		tmpRect->setScale(1, 1.5);
		drawUi.add(tmpRect);

		sf::RectangleShape *hpTmpRect = new sf::RectangleShape();
		hpTmpRect->setSize(sf::Vector2f(50, 70));
		hpTmpRect->setFillColor(sf::Color::Red);
		hpTmpRect->setPosition(tmpRect->getPosition().x, tmpRect->getPosition().y + tmpRect->getSize().y+150);
		hpBar.push_back(hpTmpRect);
		drawUi.add(hpBar[i]);

		sf::RectangleShape *manaTmpRect = new sf::RectangleShape();
		manaTmpRect->setSize(sf::Vector2f(50, 70));
		manaTmpRect->setFillColor(sf::Color::Blue);
		manaTmpRect->setPosition(hpTmpRect->getPosition().x, hpTmpRect->getPosition().y + hpTmpRect->getSize().y+50);
		manaBar.push_back(manaTmpRect);
		drawUi.add(manaBar[i]);

	}
	sf::Text gameTimeText;
	gameTimeText.setFont(defaultFont);
	gameTimeText.setCharacterSize(50);
	gameTimeText.setScale(1,1);
	
	draw.add(&gameTimeText);

	std::stringstream tmpStream;
	long double gameTime = 0.0f;
	bool pauseGame = false;
	bool buttonPressed = false;
	bool gameOver = false;
	bool firstOver = true;
	gameControl.gameOver = &gameOver;
	gameControl.firstOver = &firstOver;
	Item item;
	item.setWindow(&window);

	gameControl.item = &item;

	Draw pauseUi;
	pauseUi.setWindow(&window);
	sf::Text title;
	title.setFont(defaultFont);
	title.setString("Game Paused");
	title.setCharacterSize(60);
	title.setFillColor(sf::Color(99, 99, 26));
	title.setPosition(400, 400);
	title.setOrigin(title.getGlobalBounds().width / 2.0, title.getGlobalBounds().height / 2.0);
	pauseUi.add(&title);

	sf::Text message;
	message.setFont(defaultFont);
	message.setString("Press 'Esc' to main menu  or  'Enter'  to resume");
	message.setCharacterSize(40);
	message.setFillColor(sf::Color::Black);
	message.setPosition(400, 400);
	message.setOrigin(message.getGlobalBounds().width / 2.0, message.getGlobalBounds().height / 2.0);
	pauseUi.add(&message);
	std::vector<std::pair<std::string, int> > winner;
	bool firstCount = true;
	while (!exit)
	{

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				pauseGame = true;
			}
			else if (event.type == sf::Event::KeyReleased and event.key.code == sf::Keyboard::Escape)
			{
				pauseGame = true;
			}
		}
		if (pauseGame == false)
		{
			deltaTime = clock.restart().asSeconds();
			gameTime += deltaTime;
			tmpStream << std::fixed << std::setprecision(2) << gameTime;
			gameTimeText.setString(tmpStream.str());
			tmpStream.str(std::string());
		}

		window.clear(sf::Color::Black);

		/* mouse event*/


		/* update part*/
		for (int i = 0; i < vtPlayer.size() and !pauseGame; i++)
		{
			vtPlayer[i]->updateEvent(deltaTime);
		}
		view.setCenter(vtPlayer[0]->getPosition().x, 500.0f);
		if (view.getCenter().x - view.getSize().x / 2.0f < 0)
		{
			view.setCenter(view.getSize().x / 2.0f, 500.0f);
		}
		if (view.getCenter().x + view.getSize().x / 2.0f > bgFloor1_1->getSize().x)
		{
			view.setCenter(bgFloor1_1->getSize().x - view.getSize().x / 2.0f, 500.0f);
		}

		if (pauseGame == false)
		{
			draw.update(deltaTime);
			gameControl.update(deltaTime);
			drawUi.update(deltaTime);
			item.update(deltaTime);
			gameTimeText.setPosition(vtPlayer[0]->getPosition().x+300, vtPlayer[0]->getPosition().y-200);
		}

		window.setView(view);

		draw.draw();
		item.draw();
		if (pauseGame == true)
		{
			title.setPosition(view.getCenter().x, 300);
			message.setPosition(title.getPosition().x, title.getPosition().y + 80);

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			{
				pauseGame = false;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) and gameOver == true)
			{
				pauseGame = false;
				exit = true;
				this->setScene(Scene::selectCharecter);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				exit = true;
				this->setScene(Scene::mainMenu);
				pauseGame = false;
			}

			if (gameOver == true)
			{
				title.setString("Game Over");
				std::string tmpString = "";
				for (int i = 0; i < winner.size(); i++)
				{
					tmpString += "player name: "+winner[i].first + "    score :" + std::to_string(winner[i].second) + "\n";
				}
				tmpString += "Press 'Esc' to main menu or 'Enter'  to play again";
				message.setString(tmpString);

			}
			else
			{
				title.setString("Game Paused");
				message.setString("Press 'Esc' to main menu  or  'Enter'  to resume");
			}
			pauseUi.draw();
		}
		window.setView(uiView);

		for (int i = 0; i < hpBar.size(); i++)
		{
			if (vtPlayer[i]->hp > 0)
				hpBar[i]->setSize(sf::Vector2f(vtPlayer[i]->hp*1.5, hpBar[i]->getSize().y));
			else
				hpBar[i]->setSize(sf::Vector2f(0, hpBar[i]->getSize().y));
			if (vtPlayer[i]->mana > 0)
				manaBar[i]->setSize(sf::Vector2f(vtPlayer[i]->mana*1.5, manaBar[i]->getSize().y));
			else
				manaBar[i]->setSize(sf::Vector2f(0, manaBar[i]->getSize().y));

		}
		drawUi.draw();

		window.display();
		if (gameOver == true and exit != true and firstOver == true)
		{
			pauseGame = true;
			firstOver = false;

			for (int i = 0; i < vtPlayer.size(); i++)
			{
				if (vtPlayer[i]->hp > 0)
				{
					winner.push_back(std::make_pair(vtPlayer[i]->name, vtPlayer[i]->score-(gameTime*2)));
					this->updateHighScore(vtPlayer[i]->name, vtPlayer[i]->score -(gameTime*2));
				}

			}

		}
		int countPlayer = 0;
		for (int i = 0; i < vtPlayer.size(); i++)
		{
			if (vtPlayer[i]->hp > 0 )
			{
				countPlayer++;
			}
		}
		if (countPlayer <= 1 and firstCount == true)
		{
			gameOver = true;
			firstOver = true;
			firstCount = false;
		}
	}
	bgMusic.stop();
	window.setView(window.getDefaultView());
	return Result();
}

Result GameEngine::runHighScore(Result result)
{
	sf::Music bgMusic;
	bgMusic.openFromFile("sound/bgm/main.ogg");
	bgMusic.setLoop(true);
	bgMusic.setVolume(50);
	bgMusic.play();
	bool exit = false;
	Draw draw;
	draw.setWindow(&window);
	sf::Event event;
	sf::Mouse mouse;
	sf::Clock clock;
	float deltaTime;
	/* add component*/
	sf::Font titleFont;
	if (!titleFont.loadFromFile("font\\bangkok_regular_v1-0.ttf"))
	{
		std::cout << "Error load font\\bangkok_regular_v1-0.ttf";
	}
	sf::Text *titleText = new sf::Text();
	titleText->setFont(titleFont);
	titleText->setString("High Score");
	titleText->setCharacterSize(50);
	titleText->setFillColor(sf::Color(99, 99, 26));
	titleText->setPosition(290, 50);
	draw.add(titleText);



	std::fstream myFile;
	std::string word;
	myFile.open("highScore.dat");
	if (myFile.is_open())
	{
		std::cout << "open control.dat success\n";
	}
	else
	{
		std::cout << "open control.dat failed\n";
	}
	std::vector < std::pair < std::string,float> > scoreList;
	std::string tmpName,tmpScore;
	while (std::getline(myFile, word))
	{
		if (word.find("name:") != std::string::npos)
		{
			tmpName = "";
			for (int i = word.find("name:") + std::string("name:").length(); i < word.find("score:"); i++)
			{
				tmpName += word[i];
			}
			tmpScore = "";
			for (int i = word.find("score:") + std::string("score:").length(); i < word.length(); i++)
			{
				tmpScore += word[i];
			}
			if (tmpScore != "                    ")
			{
				scoreList.push_back(std::make_pair(tmpName, std::stof(tmpScore, NULL)));
			}
			else
			{
				scoreList.push_back(std::make_pair(tmpName, -1));
			}
		}
	}
	myFile.close();
	sf::Text *listText[6];
	std::string strList;
	for (int i = 0; i < 5; i++)
	{
		strList = "";
		strList += std::to_string(i+1);
		strList += " .\t";
		strList += "name: ";
		if(scoreList[i].first!="                    ")
			strList += scoreList[i].first+"\t";
		else
			strList += "....................";
		strList += "score: ";
		if (scoreList[i].second != -1.0f)
		{
			strList += std::to_string(scoreList[i].second);
		}
		else
		{
			strList += "....................";
		}
		listText[i] = new sf::Text();
		listText[i]->setFont(titleFont);
		listText[i]->setString(strList);
		listText[i]->setCharacterSize(40);
		listText[i]->setFillColor(sf::Color(23, 107, 182));
		listText[i]->setPosition(125, 150 + i * 25);
		listText[i]->setOutlineColor(sf::Color::White);
		draw.add(listText[i]);
	}

	sf::Text backText;
	backText.setFont(titleFont);
	backText.setFillColor(sf::Color(99, 99, 26));
	backText.setPosition(50, 700);
	backText.setCharacterSize(60);
	backText.setOutlineColor(sf::Color::White);
	backText.setString("Back");
	draw.add(&backText);
	int choice = -1;

	while (!exit)
	{
		while (window.pollEvent(event) and !exit)
		{
			if (event.type == sf::Event::Closed)
			{
				this->setScene(Scene::mainMenu);
				exit = true;
			}
			else if (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Escape)
			{
				this->setScene(Scene::mainMenu);
				exit = true;
			}

		}
		deltaTime = clock.restart().asSeconds();
		window.clear();
		/* keyboard event */

		/* mouse event*/

		draw.update(deltaTime);
		/* update part*/

		draw.draw();
		if (checkMouseCollision(&backText))
		{
			backText.setOutlineThickness(3.0);
			backText.setOutlineColor(sf::Color::White);
			choice = 0;
		}
		else
		{
			backText.setOutlineThickness(0.0f);
			choice = -1;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (choice == 0)
			{
				this->setScene(GameEngine::mainMenu);
				exit = true;
			}
		}
		window.display();
	}
	bgMusic.stop();
	return Result();
}

Result GameEngine::runControlSetting(Result result)
{
		sf::Music bgMusic;
		bgMusic.openFromFile("sound/bgm/main.ogg");
		bgMusic.setLoop(true);
		bgMusic.setVolume(50);
		bgMusic.play();
		std::fstream myFile;
		std::string word;
		myFile.open("control.dat");
		if (myFile.is_open())
		{
			std::cout << "open control.dat success\n";
		}
		else
		{
			std::cout << "open control.dat failed\n";
		}
		std::string tmpNumb;
		vtKeyCode.clear();
		KeyValue tmpKey;
		while (std::getline(myFile, word))
		{
			if (word.find("\">") != std::string::npos)
			{

				for (int i = 0; i < 4; i++)
				{
					tmpNumb = "";
					for (int j = word.find("\">") + 5 * i + 2; j < word.find("\">") + 5 * i + 6; j++)
					{
						tmpNumb += word[j];
					}
					switch (i)
					{
					case 0:
						tmpKey.joyEnable = std::stoi(tmpNumb, NULL);
						break;
					case 1:
						tmpKey.joyNumb = std::stoi(tmpNumb, NULL);
						break;
					case 2:
						tmpKey.joyCode = std::stoi(tmpNumb, NULL);
						break;
					case 3:
						tmpKey.keyCode = std::stoi(tmpNumb, NULL);
						break;
					default:
						break;
					}

				}
				vtKeyCode.push_back(tmpKey);
			}
		}
		myFile.close();
		bool exit = false;
		Draw draw;
		draw.setWindow(&window);
		sf::Event event;
		sf::Mouse mouse;
		sf::Clock clock;
		float deltaTime;
		/* add component*/
		sf::Font menuFont;
		if (!menuFont.loadFromFile("font\\bangkok_regular_v1-0.ttf"))
		{
			std::cout << "Error load font\\bangkok_regular_v1-0.ttf";
		}
		sf::Text *menuText1 = new sf::Text();
		menuText1->setFont(menuFont);
		menuText1->setString("Control Setting");
		menuText1->setCharacterSize(50);
		menuText1->setFillColor(sf::Color(99, 99, 26));
		menuText1->setPosition(290, 50);
		draw.add(menuText1);
		std::string tmpKeyStr;
		sf::Text *keyCode[30],*keyValue[30];
		for (int i = 0; i < 28; i++)
		{
			keyCode[i] = new sf::Text();	
			keyCode[i]->setFont(menuFont);
			if(vtKeyCode[i].joyEnable == false)
				keyCode[i]->setString(this->keyToStr(sf::Keyboard::Key(vtKeyCode[i].keyCode)));
			else
				keyCode[i]->setString(this->joyKeyToStr(vtKeyCode[i].joyCode));
			keyCode[i]->setCharacterSize(25);
			keyCode[i]->setFillColor(sf::Color(99, 99, 26));
			if(i<14)
				keyCode[i]->setPosition(150+100, 170+i*25 + (i / 7) * 130);
			else
				keyCode[i]->setPosition(750, 160 + (i % 14) * 25 + (i % 14) / 7 * 180 - (i / 21 * 50));
			keyCode[i]->setOutlineColor(sf::Color::White);
			draw.add(keyCode[i]);

			keyValue[i] = new sf::Text();
			keyValue[i]->setFont(menuFont);
			tmpKeyStr = "";
			switch (i%7)
			{
			case 0:
				tmpKeyStr = "       Up : ";
				break;
			case 1:
				tmpKeyStr = "  Down : ";
				break;
			case 2:
				tmpKeyStr = "     Left : ";
				break;
			case 3:
				tmpKeyStr = "   Right : ";
				break;
			case 4:
				tmpKeyStr = " Attack : ";
				break;
			case 5:
				tmpKeyStr = "   Jump : ";
				break;
			case 6:
				tmpKeyStr = "Defend : ";
				break;
			}
			keyValue[i]->setString(tmpKeyStr);
			keyValue[i]->setCharacterSize(25);
			keyValue[i]->setFillColor(sf::Color(23, 107, 182));
			if(i<14)
				keyValue[i]->setPosition(100+30, 150+20 + i *25+i/7*130);
			else
				keyValue[i]->setPosition(200+435, 160 + (i % 14) * 25 + (i % 14) / 7 * 180 - (i / 21 * 50));
			draw.add(keyValue[i]);
		}
		sf::Text *playerNo[4],*controllerType[4];
		for (int i = 0; i < 4; i++)
		{	
			playerNo[i] = new sf::Text();
			playerNo[i]->setFont(menuFont);
			playerNo[i]->setCharacterSize(35);
			if(i<2)
				playerNo[i]->setPosition(100, 120+i*400 - (i / 1) * 100);
			else
				playerNo[i]->setPosition(100+500, 115 + (i%2) * 400-(i/3*100));
			playerNo[i]->setString("PLayer"+std::to_string(i)+" :");
			draw.add(playerNo[i]);

		}
		for (int i = 0; i < 4; i++)
		{
			controllerType[i] = new sf::Text;
			controllerType[i]->setFont(menuFont);
			controllerType[i]->setCharacterSize(30);
			controllerType[i]->setFillColor(sf::Color(99, 99, 26));
			if(i<2)
				controllerType[i]->setPosition(100+130, 125+i*100 +(i/1)*200);
			else
				controllerType[i]->setPosition(500+200+40, 120 + (i%2) * 100+(i/3)*200);
			controllerType[i]->setString((vtKeyCode[i*7].joyEnable) ? "Joystick" : "Keyboard");
			controllerType[i]->setOutlineColor(sf::Color::White);
			draw.add(controllerType[i]);
		}

		

		int lastSelect = -1;
		bool checkSelect = false,isSetKey = false;

		sf::Text backText;
		backText.setFont(menuFont);
		backText.setFillColor(sf::Color(99, 99, 26));
		backText.setPosition(50, 700);
		backText.setCharacterSize(60);
		backText.setOutlineColor(sf::Color::White);
		backText.setString("Back");
		draw.add(&backText);
		int choice = -1;

		while (!exit)
		{
			while (window.pollEvent(event) and !exit)
			{
				if (event.type == sf::Event::Closed)
				{
					this->setScene(Scene::mainMenu);
					exit = true;
				}
				else if (event.type == sf::Event::MouseButtonPressed and event.mouseButton.x)
				{
					if ( lastSelect != -1)
					{
						window.clear();
						keyCode[lastSelect]->setString("...");
						draw.draw();
						window.display();
						isSetKey = true;
						while (isSetKey)
						{
							while (window.pollEvent(event))
							{
								if (vtKeyCode[lastSelect].joyEnable == false)
								{
									if (event.type == sf::Event::KeyPressed)
									{
										keyCode[lastSelect]->setString(keyToStr(event.key.code));
										vtKeyCode[lastSelect].keyCode = event.key.code;
										isSetKey = false;
										break;
									}
									else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
									{
										isSetKey = false;
										keyCode[lastSelect]->setString(keyToStr(sf::Keyboard::Key(vtKeyCode[lastSelect].keyCode))		);
										break;
									}

								}
								else
								{
									if (event.type == sf::Event::JoystickButtonPressed)
									{
										keyCode[lastSelect]->setString(joyKeyToStr(event.joystickButton.button));
										vtKeyCode[lastSelect].joyCode = event.joystickButton.button;
										vtKeyCode[lastSelect].joyNumb = event.joystickButton.joystickId;
										std::cout << event.joystickButton.joystickId << "\n";
										isSetKey = false;
										break;
									}
									else if (event.type == sf::Event::JoystickMoved)
									{
										float joyPosition = event.joystickMove.position;
										std::cout << event.joystickMove.joystickId << "\n";
										if (event.joystickMove.axis == sf::Joystick::PovY)
										{
											if (joyPosition > 0)
											{
												keyCode[lastSelect]->setString(joyKeyToStr(-1));
												vtKeyCode[lastSelect].joyCode = -1;
												vtKeyCode[lastSelect].joyNumb = event.joystickButton.joystickId;
											}
											else
											{
												keyCode[lastSelect]->setString(joyKeyToStr(-2));
												vtKeyCode[lastSelect].joyCode = -2;
												vtKeyCode[lastSelect].joyNumb = event.joystickButton.joystickId;
											}
											
											
										}
										else if (event.joystickMove.axis == sf::Joystick::PovX)
										{
											if (joyPosition > 0)
											{
												keyCode[lastSelect]->setString(joyKeyToStr(-4));
												vtKeyCode[lastSelect].joyCode = -4;
												vtKeyCode[lastSelect].joyNumb = event.joystickButton.joystickId;
											}
											else
											{
												keyCode[lastSelect]->setString(joyKeyToStr(-3));
												vtKeyCode[lastSelect].joyCode = -3;
												vtKeyCode[lastSelect].joyNumb = event.joystickButton.joystickId;
											}
										}
										isSetKey = false;
										break;
									}
									else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
									{
										isSetKey = false;
										keyCode[lastSelect]->setString(joyKeyToStr(vtKeyCode[lastSelect].joyCode));
										break;
									}
							
								}
								

							}
						}
					}
					for (int i = 0; i < 4; i++)
					{
						if (checkMouseCollision(controllerType[i]))
						{
							if (controllerType[i]->getString() == "Keyboard")
							{
								controllerType[i]->setString("Joystick");
								for (int j = i*7; j < i*7+7; j++)
								{
									vtKeyCode[j].joyEnable = true;
									keyCode[j]->setString(joyKeyToStr(vtKeyCode[j].joyCode));
								}
							}
							else
							{
								controllerType[i]->setString("Keyboard");
								for (int j = i*7; j < i*7+7; j++)
								{
									vtKeyCode[j].joyEnable = false;
									keyCode[j]->setString(keyToStr(sf::Keyboard::Key(vtKeyCode[j].keyCode)));
								}
							}
							window.clear();
							draw.draw();
							window.display();
							while (sf::Mouse::isButtonPressed(sf::Mouse::Left));
						}
					}
					
				}
				else if (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Escape)
				{
					this->setScene(Scene::mainMenu);
					exit = true;
				}
				

			}
			deltaTime = clock.restart().asSeconds();
			window.clear();
			/* keyboard event */

			/* mouse event*/
			checkSelect = false;
			for (int i = 0; i < vtKeyCode.size(); i++)
			{
				if (this->checkMouseCollision(keyCode[i]))
				{
					keyCode[i]->setOutlineThickness(2.0f);
					if (lastSelect != -1 and lastSelect != i)
					{
						keyCode[lastSelect]->setOutlineThickness(0.0f);
					}
					lastSelect = i;
					checkSelect = true;
				}

			}
			if (!checkSelect)
			{
				if (lastSelect != -1)
				{
					keyCode[lastSelect]->setOutlineThickness(0.0f);
					lastSelect = -1;
				}
			}
			for (int i = 0; i < 4; i++)
			{
				if (checkMouseCollision(controllerType[i]))
				{
					controllerType[i]->setOutlineThickness(2.0f);
				}
				else
				{
					controllerType[i]->setOutlineThickness(0.0f);
				}
			}

			draw.update(deltaTime);
			/* update part*/

			draw.draw();

			if (checkMouseCollision(&backText))
			{
				backText.setOutlineThickness(3.0);
				backText.setOutlineColor(sf::Color::White);
				choice = 0;
			}
			else
			{
				backText.setOutlineThickness(0.0f);
				choice = -1;
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (choice == 0)
				{
					this->setScene(GameEngine::mainMenu);
					exit = true;
				}
			}

			window.display();
		}
		bgMusic.stop();
		std::ofstream myfile;
		myfile.open("control.dat", std::ofstream::out | std::ofstream::trunc);
		myfile << "<player0>\n";
		myfile << "<key name=\"keyMoveUp0\">" << std::setw(4) << vtKeyCode[0].joyEnable << "," << std::setw(4) << vtKeyCode[0].joyNumb << "," << std::setw(4) << vtKeyCode[0].joyCode << "," << std::setw(4) << vtKeyCode[0].keyCode << "</key>\n";
		myfile << "<key name=\"keyMoveDown0\">" << std::setw(4) << vtKeyCode[1].joyEnable << "," << std::setw(4) << vtKeyCode[1].joyNumb << "," << std::setw(4) << vtKeyCode[1].joyCode << "," << std::setw(4) << vtKeyCode[1].keyCode << "</key>\n";
		myfile << "<key name=\"keyMoveLeft0\">" << std::setw(4) << vtKeyCode[2].joyEnable << "," << std::setw(4) << vtKeyCode[2].joyNumb << "," << std::setw(4) << vtKeyCode[2].joyCode << "," << std::setw(4) << vtKeyCode[2].keyCode << "</key>\n";
		myfile << "<key name=\"keyMoveRight0\">" << std::setw(4) << vtKeyCode[3].joyEnable << "," << std::setw(4) << vtKeyCode[3].joyNumb << "," << std::setw(4) << vtKeyCode[3].joyCode << "," << std::setw(4) << vtKeyCode[3].keyCode << "</key>\n";
		myfile << "<key name=\"keyMoveAttack0\">" << std::setw(4) << vtKeyCode[4].joyEnable << "," << std::setw(4) << vtKeyCode[4].joyNumb << "," << std::setw(4) << vtKeyCode[4].joyCode << "," << std::setw(4) << vtKeyCode[4].keyCode << "</key>\n";
		myfile << "<key name=\"keyMoveJump0\">" << std::setw(4) << vtKeyCode[5].joyEnable << "," << std::setw(4) << vtKeyCode[5].joyNumb << "," << std::setw(4) << vtKeyCode[5].joyCode << "," << std::setw(4) << vtKeyCode[5].keyCode<< "</key>\n";
		myfile << "<key name=\"keyMoveDefend0\">" << std::setw(4) << vtKeyCode[6].joyEnable << "," << std::setw(4) << vtKeyCode[6].joyNumb << "," << std::setw(4) << vtKeyCode[6].joyCode << "," << std::setw(4) << vtKeyCode[6].keyCode << "</key>\n";
		myfile << "</player0>\n";
		myfile << "<player1>\n";
		myfile << "<key name=\"keyMoveUp1\">" << std::setw(4) << vtKeyCode[7].joyEnable << "," << std::setw(4) << vtKeyCode[7].joyNumb << "," << std::setw(4) << vtKeyCode[7].joyCode << "," << std::setw(4) << vtKeyCode[7].keyCode << "</key>\n";
		myfile << "<key name=\"keyMoveDown1\">" << std::setw(4) << vtKeyCode[8].joyEnable << "," << std::setw(4) << vtKeyCode[8].joyNumb << "," << std::setw(4) << vtKeyCode[8].joyCode << "," << std::setw(4) << vtKeyCode[8].keyCode << "</key>\n";
		myfile << "<key name=\"keyMoveLeft1\">" << std::setw(4) << vtKeyCode[9].joyEnable << "," << std::setw(4) << vtKeyCode[9].joyNumb << "," << std::setw(4) << vtKeyCode[9].joyCode << "," << std::setw(4) << vtKeyCode[9].keyCode << "</key>\n";
		myfile << "<key name=\"keyMoveRight1\">" << std::setw(4) << vtKeyCode[10].joyEnable << "," << std::setw(4) << vtKeyCode[10].joyNumb << "," << std::setw(4) << vtKeyCode[10].joyCode << "," << std::setw(4) << vtKeyCode[10].keyCode << "</key>\n";
		myfile << "<key name=\"keyMoveAttack1\">" << std::setw(4) << vtKeyCode[11].joyEnable << "," << std::setw(4) << vtKeyCode[11].joyNumb << "," << std::setw(4) << vtKeyCode[11].joyCode << "," << std::setw(4) << vtKeyCode[11].keyCode << "</key>\n";
		myfile << "<key name=\"keyMoveJump1\">" << std::setw(4) << vtKeyCode[12].joyEnable << "," << std::setw(4) << vtKeyCode[12].joyNumb << "," << std::setw(4) << vtKeyCode[12].joyCode << "," << std::setw(4) << vtKeyCode[12].keyCode << "</key>\n";
		myfile << "<key name=\"keyMoveDefend1\">" << std::setw(4) << vtKeyCode[13].joyEnable << "," << std::setw(4) << vtKeyCode[13].joyNumb << "," << std::setw(4) << vtKeyCode[13].joyCode << "," << std::setw(4) << vtKeyCode[13].keyCode << "</key>\n";
		myfile << "</player1>\n";
		myfile << "<player2>\n";
		myfile << "<key name=\"keyMoveUp2\">" << std::setw(4) << vtKeyCode[14].joyEnable << "," << std::setw(4) << vtKeyCode[14].joyNumb << "," << std::setw(4) << vtKeyCode[14].joyCode << "," << std::setw(4) << vtKeyCode[14].keyCode << "</key>\n";
		myfile << "<key name=\"keyMoveDown2\">" << std::setw(4) << vtKeyCode[15].joyEnable << "," << std::setw(4) << vtKeyCode[15].joyNumb << "," << std::setw(4) << vtKeyCode[15].joyCode << "," << std::setw(4) << vtKeyCode[15].keyCode << "</key>\n";
		myfile << "<key name=\"keyMoveLeft2\">" << std::setw(4) << vtKeyCode[16].joyEnable << "," << std::setw(4) << vtKeyCode[16].joyNumb << "," << std::setw(4) << vtKeyCode[16].joyCode << "," << std::setw(4) << vtKeyCode[16].keyCode << "</key>\n";
		myfile << "<key name=\"keyMoveRight2\">" << std::setw(4) << vtKeyCode[17].joyEnable << "," << std::setw(4) << vtKeyCode[17].joyNumb << "," << std::setw(4) << vtKeyCode[17].joyCode << "," << std::setw(4) << vtKeyCode[17].keyCode << "</key>\n";
		myfile << "<key name=\"keyMoveAttack2\">" << std::setw(4) << vtKeyCode[18].joyEnable << "," << std::setw(4) << vtKeyCode[18].joyNumb << "," << std::setw(4) << vtKeyCode[18].joyCode << "," << std::setw(4) << vtKeyCode[18].keyCode << "</key>\n";
		myfile << "<key name=\"keyMoveJump2\">" << std::setw(4) << vtKeyCode[19].joyEnable << "," << std::setw(4) << vtKeyCode[19].joyNumb << "," << std::setw(4) << vtKeyCode[19].joyCode << "," << std::setw(4) << vtKeyCode[19].keyCode << "</key>\n";
		myfile << "<key name=\"keyMoveDefend2\">" << std::setw(4) << vtKeyCode[20].joyEnable << "," << std::setw(4) << vtKeyCode[20].joyNumb << "," << std::setw(4) << vtKeyCode[20].joyCode << "," << std::setw(4) << vtKeyCode[20].keyCode << "</key>\n";
		myfile << "</player2>\n";
		myfile << "<player3>\n";
		myfile << "<key name=\"keyMoveUp3\">" << std::setw(4) << vtKeyCode[21].joyEnable << "," << std::setw(4) << vtKeyCode[21].joyNumb << "," << std::setw(4) << vtKeyCode[21].joyCode << "," << std::setw(4) << vtKeyCode[21].keyCode << "</key>\n";
		myfile << "<key name=\"keyMoveDown3\">" << std::setw(4) << vtKeyCode[22].joyEnable << "," << std::setw(4) << vtKeyCode[22].joyNumb << "," << std::setw(4) << vtKeyCode[22].joyCode << "," << std::setw(4) << vtKeyCode[22].keyCode << "</key>\n";
		myfile << "<key name=\"keyMoveLeft3\">" << std::setw(4) << vtKeyCode[23].joyEnable << "," << std::setw(4) << vtKeyCode[23].joyNumb << "," << std::setw(4) << vtKeyCode[23].joyCode << "," << std::setw(4) << vtKeyCode[23].keyCode << "</key>\n";
		myfile << "<key name=\"keyMoveRight3\">" << std::setw(4) << vtKeyCode[24].joyEnable << "," << std::setw(4) << vtKeyCode[24].joyNumb << "," << std::setw(4) << vtKeyCode[24].joyCode << "," << std::setw(4) << vtKeyCode[24].keyCode << "</key>\n";
		myfile << "<key name=\"keyMoveAttack3\">" << std::setw(4) << vtKeyCode[25].joyEnable << "," << std::setw(4) << vtKeyCode[25].joyNumb << "," << std::setw(4) << vtKeyCode[25].joyCode << "," << std::setw(4) << vtKeyCode[25].keyCode << "</key>\n";
		myfile << "<key name=\"keyMoveJump3\">" << std::setw(4) << vtKeyCode[26].joyEnable << "," << std::setw(4) << vtKeyCode[26].joyNumb << "," << std::setw(4) << vtKeyCode[26].joyCode << "," << std::setw(4) << vtKeyCode[26].keyCode << "</key>\n";
		myfile << "<key name=\"keyMoveDefend3\">" << std::setw(4) << vtKeyCode[27].joyEnable << "," << std::setw(4) << vtKeyCode[27].joyNumb << "," << std::setw(4) << vtKeyCode[27].joyCode << "," << std::setw(4) << vtKeyCode[27].keyCode << "</key>\n";
		myfile << "</player3>\n";
		myfile.close();
		bgMusic.stop();
		return Result();
}

Result GameEngine::runSelectCharecter(Result result)
{
	std::vector<Player*> vtPlayer;
	Player player;
	sf::Music bgMusic;
	bgMusic.openFromFile("sound/bgm/stage1.ogg");
	bgMusic.setLoop(true);
	bgMusic.setVolume(20);
	bgMusic.play();
	int totalPlayer = result.resultString.size() - 1;
	for (int i = 0; i < 4; i++)
	{
		vtPlayer.push_back(player.createPlayer(Player::Charecter::bandit));
		for (int j = i * 7; j < (i + 1) * 7; j++)
		{
			if (vtKeyCode[i * 7].joyEnable == 1)
			{
				vtPlayer[i]->useJoyStick = true;
				vtPlayer[i]->setKey(Player::Key(j % 7), vtKeyCode[j].joyCode);
				vtPlayer[i]->joyNumb = vtKeyCode[j].joyNumb;
			}
			else
			{
				vtPlayer[i]->setKey(Player::Key(j % 7), sf::Keyboard::Key(vtKeyCode[j].keyCode));
			}

		}

	}
	
	std::vector <std::vector<int>> vtCharecterMap;
	int count = 0;
	for (int i = 0; i < 3; i++) 
	{
		vtCharecterMap.push_back(std::vector<int>());
	}
	for (int i = 0; i < vtCharecterMap.size(); i++)
	{
		for (int j = 0; j < 10; j++)
		{
			vtCharecterMap[i].push_back(count++);
		}
	}
	std::string name[5];
	for (int i = 0; i < totalPlayer; i++)
	{
		name[i] = result.resultString[i+1];
	}


	bool exit = false;
	Draw draw;
	draw.setWindow(&window);
	sf::Event event;
	sf::Mouse mouse;
	sf::Clock clock;
	float deltaTime;
	/* add component*/
	sf::Font menuFont;
	if (!menuFont.loadFromFile("font\\bangkok_regular_v1-0.ttf"))
	{
		std::cout << "Error load font\\bangkok_regular_v1-0.ttf";
	}
	sf::Text title;
	title.setFont(menuFont);
	title.setString("Select Charecter");
	title.setCharacterSize(50);
	title.setFillColor(sf::Color(99, 99, 26));
	title.setPosition(350, 50);
	draw.add(&title);
	
	sf::Text nameP[5];
	for (int i = 0; i < totalPlayer; i++)
	{
		nameP[i].setFont(menuFont);
		nameP[i].setString(name[i]);
		nameP[i].setCharacterSize(30);
		nameP[i].setFillColor(sf::Color(23, 107, 182));
		nameP[i].setPosition(i * 230 + 50, 115);
		draw.add(&nameP[i]);
	}


	sf::Texture smallTexture[31], bigTexture[31];
	for (int i = 0; i < 30; i++)
	{
		smallTexture[i].loadFromFile(SPRITE_PATH+"charecter\\"+std::to_string(i)+"smallPic.png");
		bigTexture[i].loadFromFile(SPRITE_PATH + "charecter\\"+std::to_string(i) + "bigPic.png");
	}
	
	sf::Sprite bigShowP[5];
	sf::Vector2i select[5];
	for (int i = 0; i < totalPlayer; i++)
	{
		select[i] = { i,0 };
		bigShowP[i].setTexture(bigTexture[select[i].x]);
		bigShowP[i].setPosition(i*230+50, 150.0f);
		bigShowP[i].setScale(1.8f, 1.8f);
		draw.add(&bigShowP[i]);

	}
	
	std::vector < std::vector < sf::Sprite > > vtSmall;
	sf::Sprite tmpSprite;
	for (int i = 0; i < 3; i++)
	{
		vtSmall.push_back(std::vector<sf::Sprite>());
		for (int j = 0; j < 10; j++)
		{
			tmpSprite.setTexture(smallTexture[vtCharecterMap[i][j]]);
			tmpSprite.setScale(2,2);
			tmpSprite.setPosition(95*j+38, 400+100*i+50);	
			vtSmall[i].push_back(tmpSprite);
		}
		
		
	}
	

	sf::Text p[5];
	for (int i = 0; i < totalPlayer; i++)
	{
		p[i].setFont(menuFont);
		p[i].setCharacterSize(25);
		p[i].setString("P"+std::to_string(i+1));
		draw.add(&p[i]);
	}



	for (int i = 0; i < vtSmall.size(); i++)
	{
		for (int j = 0; j < vtSmall[i].size(); j++)
		{
			draw.add(&vtSmall[i][j]);
		}
	}
	std::vector<bool> pressed;
	for (int i = 0; i < totalPlayer; i++)
	{
		pressed.push_back(false);
	}
	Result tmpResult;
	while (!exit)
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				this->setScene(Scene::setPlayerName);
				exit = true;
				tmpResult.resultString.push_back("setPlayerName");
				tmpResult.resultInt.push_back(totalPlayer);
				return tmpResult;

			}
			else if (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Escape)
			{
				this->setScene(Scene::setPlayerName);
				exit = true;
				tmpResult.resultString.push_back("setPlayerName");
				tmpResult.resultInt.push_back(totalPlayer);
				return tmpResult;
			}
			else if (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Enter)
			{
				this->setScene(Scene::pvpMode);
				tmpResult.resultString.push_back("pvpMode");
				exit = true;
				for (int i = 0; i < totalPlayer; i++)
				{
					tmpResult.resultString.push_back(name[i]);
					tmpResult.resultVector2i.push_back(select[i]);
					tmpResult.resultInt.push_back(vtCharecterMap[select[i].y][select[i].x]);
				}
				return tmpResult;
			}

		}
		deltaTime = clock.restart().asSeconds();
		window.clear();
		/* keyboard event */

		/* mouse event*/
	
		for (int i = 0; i < totalPlayer; i++)
		{
			if (getFormatInput(vtPlayer[i]->getInput()) == "1000000" and !pressed[i])
			{
				select[i].y--;
				if (select[i].y < 0)
					select[i].y = vtSmall.size() - 1;
				pressed[i] = true;
			}
			else if (getFormatInput(vtPlayer[i]->getInput()) == "0100000" and !pressed[i])
			{
				select[i].y++;
				select[i].y %= vtSmall.size();
				pressed[i] = true;
			}
			else if (getFormatInput(vtPlayer[i]->getInput()) == "0010000" and !pressed[i])
			{
				select[i].x--;
				if (select[i].x < 0)
					select[i].x = vtSmall[select[i].y].size() - 1;
				pressed[i] = true;
			}
			else if (getFormatInput(vtPlayer[i]->getInput()) == "0001000" and !pressed[i])
			{
				select[i].x++;
				select[i].x %= vtSmall[select[i].y].size();
				pressed[i] = true;
			}
			if (getFormatInput(vtPlayer[i]->getInput()) == "0000000")
			{
				pressed[i] = false;
			}
		}
		


		for (int i = 0; i < vtSmall.size(); i++)
		{
			for (int j = 0; j < vtSmall[i].size(); j++)
			{
				bool ckSelect = false;
				for (int k = 0; k < totalPlayer; k++)
				{
					if (i == select[k].y and j == select[k].x)
					{
						vtSmall[i][j].setColor(sf::Color(vtSmall[i][j].getColor().r, vtSmall[i][j].getColor().g, vtSmall[i][j].getColor().b, 255));
						p[k].setPosition(vtSmall[i][j].getPosition().x, vtSmall[i][j].getPosition().y+k*25);
						bigShowP[k].setTexture(bigTexture[vtCharecterMap[select[k].y][select[k].x]]);
						ckSelect = true;
					}
				}
				
				if(ckSelect == false)
				{
					vtSmall[i][j].setColor(sf::Color(vtSmall[i][j].getColor().r, vtSmall[i][j].getColor().g, vtSmall[i][j].getColor().b, 180));
				}
				
			}
		}
	/*	std::cout << "GameEngine::slScene->";
		std::cout << select[0].x << "," << select[0].y;
		std::cout << select[1].x << "," << select[1].y << "\n";
*/
		draw.update(deltaTime);
		/* update part*/

		draw.draw();
		window.display();
	}
	for (int i = 0; i < totalPlayer; i++)
	{
		tmpResult.resultString.push_back(name[i]);
		tmpResult.resultVector2i.push_back(select[i]);
		tmpResult.resultInt.push_back(vtCharecterMap[select[i].y][select[i].x]);
	}
	bgMusic.stop();
	return tmpResult;
}

Result GameEngine::runSetPlayerName(Result result)
{
	Result tmpResult;
	bool exit = false;
	sf::Music bgMusic;
	bgMusic.openFromFile("sound/bgm/stage1.ogg");
	bgMusic.setLoop(true);
	bgMusic.setVolume(20);
	bgMusic.play();
	Draw draw;
	draw.setWindow(&window);
	sf::Event event;
	sf::Mouse mouse;
	sf::Clock clock;
	float deltaTime;
	/* add component*/
	sf::Font menuFont;
	if (!menuFont.loadFromFile("font\\bangkok_regular_v1-0.ttf"))
	{
		std::cout << "Error load font\\bangkok_regular_v1-0.ttf";
	}
	sf::Text title;
	title.setFont(menuFont);
	title.setString("Set Player Name");
	title.setCharacterSize(50);
	title.setFillColor(sf::Color(99, 99, 26));
	title.setPosition(350, 50);
	draw.add(&title);
	int totalPlayer = result.resultInt[0];
	sf::Text displayPlayer[5], namePlayer[5];
	for (int i = 0; i < totalPlayer; i++)
	{
		displayPlayer[i].setFont(menuFont);
		displayPlayer[i].setString("player"+std::to_string(i)+": ");
		displayPlayer[i].setCharacterSize(40);
		displayPlayer[i].setFillColor(sf::Color(23, 107, 182));
		displayPlayer[i].setPosition(200 + 35, 200+i*40);
		draw.add(&displayPlayer[i]);
	}
	
	for (int i = 0; i < totalPlayer; i++)
	{
		namePlayer[i].setFont(menuFont);
		namePlayer[i].setString("click to edit");
		namePlayer[i].setCharacterSize(40);
		namePlayer[i].setFillColor(sf::Color(99, 99, 26));
		namePlayer[i].setPosition(200 + 35+125, 200+i*40);
		namePlayer[i].setOutlineColor(sf::Color::White);
		draw.add(&namePlayer[i]);
	}
	

	sf::Text doneText, backText;
	doneText.setFont(menuFont);
	backText.setFont(menuFont);
	backText.setFillColor(sf::Color(99, 99, 26));
	doneText.setFillColor(sf::Color(99, 99, 26));
	backText.setPosition(50, 700);
	doneText.setPosition(800, 700);
	backText.setCharacterSize(60);
	doneText.setCharacterSize(60);
	backText.setOutlineColor(sf::Color::White);
	doneText.setOutlineColor(sf::Color::White);
	backText.setString("Back");
	doneText.setString("Done");
	draw.add(&backText);
	draw.add(&doneText);

	int select = -1,choice = -1;
	std::string tmpInput;
	while (!exit)
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				exit = true;
				this->setScene(Scene::mainMenu);
				tmpResult.resultString.push_back("setTotalPlayer");
				bgMusic.stop();
				return tmpResult;
			}
			else if (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Escape)
			{
				this->setScene(Scene::mainMenu);
				exit = true;
				tmpResult.resultString.push_back("setTotalPlayer");
				bgMusic.stop();
				return tmpResult;
			}
			else if (event.type == sf::Event::MouseButtonPressed and event.mouseButton.x)
			{
				if (select != -1)
				{
					
					bool isSetKey = true;
					if (namePlayer[select].getString().toAnsiString() != "click to edit")
					{
						tmpInput = namePlayer[select].getString().toAnsiString();
					}
					else
					{
						tmpInput = "";
						namePlayer[select].setString(".............");
					}
					window.clear();
					draw.draw();
					window.display();
					while (isSetKey)
					{
						while (window.pollEvent(event) and isSetKey)
						{
							if (event.type == sf::Event::TextEntered)
							{
								if (event.text.unicode == '\b')
								{
									if (tmpInput.length() > 0)
									{
										tmpInput.pop_back();
										namePlayer[select].setString(tmpInput);
									}
									else
									{
										namePlayer[select].setString("...............");
									}
										
								}
								else if (event.text.unicode < 128 and tmpInput.length()<20)
								{
									tmpInput += static_cast<char>(event.text.unicode);
									namePlayer[select].setString(tmpInput);
								}
							}
							if (event.type == sf::Event::MouseButtonPressed or sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
							{
								int countSpace = 0;
								for (auto i : tmpInput)
								{
									if (i == ' ')
										countSpace++;
								}
								if (tmpInput.length() > 0)
								{
									isSetKey = false;
									if (countSpace == tmpInput.length())
									{
										namePlayer[select].setString("click to edit");
									}
									std::cout << countSpace << " , " << tmpInput.length() << "\n";
								}
								else
								{
									std::cout << countSpace << " , " << tmpInput.length() << "\n";
									isSetKey = false;
									namePlayer[select].setString("click to edit");
								}

							}
						}
						window.clear();
						draw.draw();
						window.display();
					}
				}
			}
				deltaTime = clock.restart().asSeconds();
				window.clear();
				/* keyboard event */

				/* mouse event*/

				draw.update(deltaTime);
				/* update part*/
				bool checkSelect = false;
				for (int i = 0; i < totalPlayer; i++)
				{
					if (checkMouseCollision(&namePlayer[i]))
					{
						namePlayer[i].setOutlineThickness(3.0);
						namePlayer[i].setOutlineColor(sf::Color::White);
						select = i;
						checkSelect = true;
					}
					else
					{
						namePlayer[i].setOutlineThickness(0.0);
						namePlayer[i].setOutlineColor(sf::Color::White);
					}
				}
				
				if (checkSelect == false)
				{
					select = -1;
				}
				

				if (checkMouseCollision(&backText))
				{
					backText.setOutlineThickness(3.0);
					doneText.setOutlineThickness(0.0);
					backText.setOutlineColor(sf::Color::White);
					doneText.setOutlineColor(sf::Color::White);

					choice = 0;
				}
				else if (checkMouseCollision(&doneText))
				{
					doneText.setOutlineThickness(0.0);
					doneText.setOutlineThickness(3.0);
					backText.setOutlineColor(sf::Color::White);
					doneText.setOutlineColor(sf::Color::White);
					choice = 1;
				}
				else
				{
					backText.setOutlineThickness(0.0);
					doneText.setOutlineThickness(0.0);
					backText.setOutlineColor(sf::Color::White);
					doneText.setOutlineColor(sf::Color::White);
					choice = -1;
				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (choice == 0)
					{
						tmpResult.resultString.push_back("setTotalPlayer");
						bgMusic.stop();
						return tmpResult;
					}
					else if (choice == 1)
					{
						
						bool ck = false;
						for (int i = 0; i < totalPlayer; i++)
						{
							if (namePlayer[i].getString().toAnsiString() == "click to edit")
							{
								namePlayer[i].setOutlineColor(sf::Color::Red);
								namePlayer[i].setOutlineThickness(3.0);
								doneText.setOutlineThickness(3.0);
								doneText.setOutlineColor(sf::Color::Red);
								ck = true;
							}
						}
						if (ck == false)
						{
							tmpResult.resultString.push_back("selectCharecter");
							for (int i = 0; i < totalPlayer; i++)
							{	
								tmpResult.resultString.push_back(namePlayer[i].getString().toAnsiString());
							}
							bgMusic.stop();
							return tmpResult;
						}
					}
				}
				draw.draw();
				window.display();
				
		}
	}	
	tmpResult.resultString.push_back("selectCharecter");
	tmpResult.resultString.push_back(namePlayer[0].getString().toAnsiString());
	tmpResult.resultString.push_back(namePlayer[1].getString().toAnsiString());
	bgMusic.stop();
	return tmpResult;
}

Result GameEngine::runSetTotalPlayer(Result result)
{
	Result tmpResult;
	bool exit = false;
	Draw draw;
	sf::Music bgMusic;
	bgMusic.openFromFile("sound/bgm/stage1.ogg");
	bgMusic.setLoop(true);
	bgMusic.setVolume(20);
	bgMusic.play();
	draw.setWindow(&window);
	sf::Event event;
	sf::Mouse mouse;
	sf::Clock clock;
	float deltaTime;
	/* add component*/
	sf::Font menuFont;
	if (!menuFont.loadFromFile("font\\bangkok_regular_v1-0.ttf"))
	{
		std::cout << "Error load font\\bangkok_regular_v1-0.ttf";
	}
	sf::Text title;
	title.setFont(menuFont);
	title.setString("Select Mode");
	title.setCharacterSize(50);
	title.setFillColor(sf::Color(99, 99, 26));
	title.setPosition(370, 50);
	draw.add(&title);

	sf::Text menu[3];
	
	for (int i = 0; i < 3; i++)
	{
		menu[i].setFont(menuFont);
		menu[i].setString("Mode " + std::to_string(i+2) +" players");
		menu[i].setCharacterSize(50);
		menu[i].setFillColor(sf::Color(99, 99, 26));
		menu[i].setPosition(345, 80*i+350);
		draw.add(&menu[i]);
	}
	sf::Text backText;
	backText.setFont(menuFont);
	backText.setFillColor(sf::Color(99, 99, 26));
	backText.setPosition(450, 700);
	backText.setCharacterSize(60);
	backText.setOutlineColor(sf::Color::White);
	backText.setString("Back");
	draw.add(&backText);
	int choice = -1;
	while (!exit)
	{
		while (window.pollEvent(event) and !exit)
		{
			if (event.type == sf::Event::Closed)
			{
				this->setScene(Scene::mainMenu);
				exit = true;
			}
			else if (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Escape)
			{
				this->setScene(Scene::mainMenu);
				exit = true;
			}
		

		}	
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (checkMouseCollision(&menu[0]))
			{
				tmpResult.resultInt.push_back(2);
				this->setScene(Scene::setPlayerName);
				exit = true;
			}
			else if (checkMouseCollision(&menu[1]))
			{
				tmpResult.resultInt.push_back(3);
				this->setScene(Scene::setPlayerName);
				exit = true;
			}
			else if (checkMouseCollision(&menu[2]))
			{
				tmpResult.resultInt.push_back(4);
				this->setScene(Scene::setPlayerName);
				exit = true;
			}
		}

		for (int i = 0; i < 3; i++)
		{

			if (checkMouseCollision(&menu[i]))
			{
				menu[i].setOutlineColor(sf::Color::White);
				menu[i].setOutlineThickness(3.0f);
			}
			else
			{
				menu[i].setOutlineThickness(0.0f);
			}
		}
		window.clear();
		draw.draw();

		if (checkMouseCollision(&backText))
		{
			backText.setOutlineThickness(3.0);
			backText.setOutlineColor(sf::Color::White);
			choice = 0;
		}
		else
		{
			backText.setOutlineThickness(0.0f);
			choice = -1;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (choice == 0)
			{
				this->setScene(GameEngine::mainMenu);
				exit = true;
			}
		}
		window.display();

	}
	bgMusic.stop();
	return tmpResult;
}

bool GameEngine::checkMouseCollision(sf::Text * text)
{
	sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
	
	if (text->getGlobalBounds().contains(mousePosition))
		return true;
	else
		return false;
}

float GameEngine::computeDistance(sf::Vector2f point1, sf::Vector2f point2)
{
	return std::sqrt((point1.x-point2.x)*(point1.x - point2.x)+ (point1.y - point2.y)*(point1.y - point2.y));
}

sf::Vector2f GameEngine::compareXY(sf::Vector2f point1, sf::Vector2f point2)
{
	return sf::Vector2f(std::abs(point1.x-point2.x), std::abs(point1.y - point2.y));
}

std::string GameEngine::keyToStr(sf::Keyboard::Key key)
{
		if (key >= sf::Keyboard::A and key <= sf::Keyboard::Z)
		{
			return std::string("")+(char)('A' + key);
		}
		char keyStr[10];
		switch (key) {
		case sf::Keyboard::Key::Escape: sprintf_s(keyStr, "Escape"); break;
		case sf::Keyboard::Key::LControl: sprintf_s(keyStr, "LControl"); break;
		case sf::Keyboard::Key::LShift: sprintf_s(keyStr, "LShift"); break;
		case sf::Keyboard::Key::LAlt: sprintf_s(keyStr, "LAlt"); break;
		case sf::Keyboard::Key::LSystem: sprintf_s(keyStr, "LSystem"); break;
		case sf::Keyboard::Key::RControl: sprintf_s(keyStr, "RControl"); break;
		case sf::Keyboard::Key::RShift: sprintf_s(keyStr, "RShift"); break;
		case sf::Keyboard::Key::RAlt: sprintf_s(keyStr, "RAlt"); break;
		case sf::Keyboard::Key::RSystem: sprintf_s(keyStr, "RSystem"); break;
		case sf::Keyboard::Key::Menu: sprintf_s(keyStr, "Menu"); break;
		case sf::Keyboard::Key::LBracket: sprintf_s(keyStr, "LBracket"); break;
		case sf::Keyboard::Key::RBracket: sprintf_s(keyStr, "RBracket"); break;
		case sf::Keyboard::Key::SemiColon: sprintf_s(keyStr, ";"); break;
		case sf::Keyboard::Key::Comma: sprintf_s(keyStr, ","); break;
		case sf::Keyboard::Key::Period: sprintf_s(keyStr, "."); break;
		case sf::Keyboard::Key::Quote: sprintf_s(keyStr, "\'"); break;
		case sf::Keyboard::Key::Slash: sprintf_s(keyStr, "/"); break;
		case sf::Keyboard::Key::BackSlash: sprintf_s(keyStr, "\\"); break;
		case sf::Keyboard::Key::Tilde: sprintf_s(keyStr, "~"); break;
		case sf::Keyboard::Key::Equal: sprintf_s(keyStr, "="); break;
		case sf::Keyboard::Key::Dash: sprintf_s(keyStr, "-"); break;
		case sf::Keyboard::Key::Space: sprintf_s(keyStr, "Space"); break;
		case sf::Keyboard::Key::Return: sprintf_s(keyStr, "Return"); break;
		case sf::Keyboard::Key::Backspace: sprintf_s(keyStr, "Backspace"); break;
		case sf::Keyboard::Key::Tab: sprintf_s(keyStr, "Tab"); break;
		case sf::Keyboard::Key::PageUp: sprintf_s(keyStr, "Page Up"); break;
		case sf::Keyboard::Key::PageDown: sprintf_s(keyStr, "Page Down"); break;
		case sf::Keyboard::Key::End: sprintf_s(keyStr, "End"); break;
		case sf::Keyboard::Key::Home: sprintf_s(keyStr, "Home"); break;
		case sf::Keyboard::Key::Insert: sprintf_s(keyStr, "Insert"); break;
		case sf::Keyboard::Key::Delete: sprintf_s(keyStr, "Delete"); break;
		case sf::Keyboard::Key::Add: sprintf_s(keyStr, "+"); break;
		case sf::Keyboard::Key::Subtract: sprintf_s(keyStr, "-"); break;
		case sf::Keyboard::Key::Multiply: sprintf_s(keyStr, "*"); break;
		case sf::Keyboard::Key::Divide: sprintf_s(keyStr, "/"); break;
		case sf::Keyboard::Key::Left: sprintf_s(keyStr, "Left"); break;
		case sf::Keyboard::Key::Right: sprintf_s(keyStr, "Right"); break;
		case sf::Keyboard::Key::Up: sprintf_s(keyStr, "UP"); break;
		case sf::Keyboard::Key::Down: sprintf_s(keyStr, "Down"); break;
		case sf::Keyboard::Key::Numpad0: sprintf_s(keyStr, "Numpad0"); break;
		case sf::Keyboard::Key::Numpad1: sprintf_s(keyStr, "Numpad1"); break;
		case sf::Keyboard::Key::Numpad2: sprintf_s(keyStr, "Numpad2"); break;
		case sf::Keyboard::Key::Numpad3: sprintf_s(keyStr, "Numpad3"); break;
		case sf::Keyboard::Key::Numpad4: sprintf_s(keyStr, "Numpad4"); break;
		case sf::Keyboard::Key::Numpad5: sprintf_s(keyStr, "Numpad5"); break;
		case sf::Keyboard::Key::Numpad6: sprintf_s(keyStr, "Numpad6"); break;
		case sf::Keyboard::Key::Numpad7: sprintf_s(keyStr, "Numpad7"); break;
		case sf::Keyboard::Key::Numpad8: sprintf_s(keyStr, "Numpad8"); break;
		case sf::Keyboard::Key::Numpad9: sprintf_s(keyStr, "Numpad9"); break;
		case sf::Keyboard::Key::F1: sprintf_s(keyStr, "F1"); break;
		case sf::Keyboard::Key::F2: sprintf_s(keyStr, "F2"); break;
		case sf::Keyboard::Key::F3: sprintf_s(keyStr, "F3"); break;
		case sf::Keyboard::Key::F4: sprintf_s(keyStr, "F4"); break;
		case sf::Keyboard::Key::F5: sprintf_s(keyStr, "F5"); break;
		case sf::Keyboard::Key::F6: sprintf_s(keyStr, "F6"); break;
		case sf::Keyboard::Key::F7: sprintf_s(keyStr, "F7"); break;
		case sf::Keyboard::Key::F8: sprintf_s(keyStr, "F8"); break;
		case sf::Keyboard::Key::F9: sprintf_s(keyStr, "F9"); break;
		case sf::Keyboard::Key::F10: sprintf_s(keyStr, "F10"); break;
		case sf::Keyboard::Key::F11: sprintf_s(keyStr, "F11"); break;
		case sf::Keyboard::Key::F12: sprintf_s(keyStr, "F12"); break;
		case sf::Keyboard::Key::F13: sprintf_s(keyStr, "F13"); break;
		case sf::Keyboard::Key::F14: sprintf_s(keyStr, "F14"); break;
		case sf::Keyboard::Key::F15: sprintf_s(keyStr, "F15"); break;
		case sf::Keyboard::Key::Pause: sprintf_s(keyStr, "Paues"); break;
		default:
			sprintf_s(keyStr, "-1");
		}
		return std::string(keyStr);
}

std::string GameEngine::joyKeyToStr(int joyButton)
{
	std::string tmp;
	switch (joyButton)
	{
	case -1:
		tmp = "Up";
		break;
	case -2:
		tmp = "Down";
		break;
	case -3:
		tmp = "Left";
		break;
	case -4:
		tmp = "Right";
		break;
	case 0:
		tmp = "A";
		break;
	case 1:
		tmp = "B";
		break;
	case 2:
		tmp = "X";
		break;
	case 3:
		tmp = "Y";
		break;
	default:
		tmp = "-1";
		break;
	}
	return tmp;
}

void GameEngine::updateHighScore(std::string name, float score)
{
	std::fstream myFile;
	std::string word;
	myFile.open("highScore.dat");
	if (myFile.is_open())
	{
		std::cout << "open control.dat success\n";
	}
	else
	{
		std::cout << "open control.dat failed\n";
	}
	
	std::vector<std::pair<std::string,float> > vtHighScore;
	std::string tmpName,tmpFloat;
	while (std::getline(myFile, word))
	{
		if (word.find("name") != std::string::npos)
		{
			tmpName = "";
			tmpFloat = "";
			for (int i = 0; i < 20; i++)
			{
				tmpName  += word[word.find("name:") + std::string("name:").length()+i] ;
			}
			for (int i = word.find("score:")+std::string("score:").length(); i < word.length(); i++)
			{
				tmpFloat += word[i];
			}	
			float result;
			if (tmpFloat != "                    ")
			{
				result = std::stof(tmpFloat, NULL);
			}
			else
			{
				result = -1.0;
			}
			vtHighScore.push_back(std::make_pair(tmpName, result));
		}
		
	}
	myFile.close();
	vtHighScore.push_back(std::make_pair(name, score));
	for (int i = 0; i < vtHighScore.size(); i++)
	{
		for (int j = i + 1; j < vtHighScore.size(); j++)
		{
			if (vtHighScore[j].second > vtHighScore[i].second)
			{
				std::swap(vtHighScore[i], vtHighScore[j]);
			}
		}
	}
	for (int i = 0; i < vtHighScore.size(); i++)
	{
		std::cout << vtHighScore[i].first << " , " << vtHighScore[i].second<<"\n";
	}
	std::ofstream myfile2;
	myfile2.open("highScore.dat", std::ofstream::out | std::ofstream::trunc);
	myfile2 << "<highScore>\n";
	myfile2 << "01name:" << std::left << std::setw(20) << vtHighScore[0].first << "score:" << std::left << std::setw(20) << vtHighScore[0].second << "\n";
	myfile2 << "02name:" << std::left << std::setw(20) << vtHighScore[1].first << "score:" << std::left << std::setw(20) << vtHighScore[1].second << "\n";
	myfile2 << "03name:" << std::left << std::setw(20) << vtHighScore[2].first << "score:" << std::left << std::setw(20) << vtHighScore[2].second << "\n";
	myfile2 << "04name:" << std::left << std::setw(20) << vtHighScore[3].first << "score:" << std::left << std::setw(20) << vtHighScore[3].second << "\n";
	myfile2 << "05name:" << std::left << std::setw(20) << vtHighScore[4].first << "score:" << std::left << std::setw(20) << vtHighScore[4].second << "\n";
	myfile2 << "</highScore>\n";
	myfile2.close();


	
}

unsigned long long GameEngine::getAndSetRandom(unsigned long long randomNumber,bool choice)
{
	sf::Mutex mutex;
	mutex.lock();
	if (choice == true)
	{
		return this->randomNumber;
	}
	else
	{
		this->randomNumber = randomNumber;
		return 0;
	}
	mutex.unlock();
	return 0;
}

int GameEngine::close() {
	running = false;
	return 0;
}
