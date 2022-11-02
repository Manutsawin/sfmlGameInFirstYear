#pragma once
#include<vector>
#include"Image.h"
#include"Animation.h"
#include"Player.h"
#include<algorithm>
class Draw
{
public:
	Draw();
	~Draw();
	void add(Animation *animation);
	void add(Image *image);
	void add(sf::Text* text);
	void add(Player *player);
	void add(sf::Sprite *sprite);
	void add(sf::RectangleShape *rect);
	void update(float deltaTime);
	void draw();
	void setMapSize(sf::Vector2u size);
	void setWindow(sf::RenderWindow *window);
	void clear();
private:
	std::vector<sf::Sprite*> content;
	std::vector<sf::RectangleShape*> contentRect;
	std::vector<sf::Text*> textContent;
	std::vector<Animation*> animationContent;
	std::vector<Player *> playerContent;
	sf::RenderWindow *window;
	sf::Vector2u mapSize;
};

