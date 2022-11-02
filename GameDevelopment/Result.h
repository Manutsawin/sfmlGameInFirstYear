#pragma once
#include<vector>
#include<SFML/Graphics.hpp>
class Result
{
public:
	Result();
	virtual ~Result();
public:
	std::vector<int> resultInt;
	std::vector<std::string> resultString;
	std::vector<sf::Vector2i> resultVector2i;

};

