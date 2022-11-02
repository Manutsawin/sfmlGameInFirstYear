#pragma once
#include<SFML/Graphics.hpp>
#include <map>
#include<math.h>
#include<iostream>

class Collision
{
public:
	enum Check
	{
		Down, TopRight ,TopLeft
	};

public:

	static bool CollisionCheck( sf::Sprite *Object1, sf::Sprite *Object2,Check check, float *x = 0 ,float *y = 0,float *sloap = 0);


	/// Test for a collision between two sprites by comparing the alpha values of overlapping pixels
	/// Supports scaling and rotation
	/// AlphaLimit: The threshold at which a pixel becomes "solid". If AlphaLimit is 127, a pixel with
	/// alpha value 128 will cause a collision and a pixel with alpha value 126 will not.
	/// This functions creates bitmasks of the textures of the two sprites by
	/// downloading the textures from the graphics card to memory -> SLOW!
	/// You can avoid this by using the "CreateTextureAndBitmask" function
	static bool PixelPerfectTest(const sf::Sprite *Object1, const sf::Sprite *Object2, sf::Uint8 alphaLimit = 0);

	/// Replaces Texture::loadFromFile
	/// Load an imagefile into the given texture and create a bitmask for it
	/// This is much faster than creating the bitmask for a texture on the first run of "PixelPerfectTest"
	/// The function returns false if the file could not be opened for some reason
	static bool CreateTextureAndBitmask(sf::Texture *LoadInto, const std::string Filename);

	/// Test for collision using circle collision dection
	/// Radius is averaged from the dimensions of the sprite so
	/// roughly circular objects will be much more accurate
	static bool CircleTest(const sf::Sprite *Object1, const sf::Sprite *Object2);

	/// Test for bounding box collision using the Separating Axis Theorem
	/// Supports scaling and rotation
	static bool BoundingBoxTest(const sf::Sprite *Object1, const sf::Sprite *Object2);


	virtual ~Collision();


private:
	static sf::Vector2f GetSpriteCenter(const sf::Sprite *Object);
	static sf::Vector2f GetSpriteSize(const sf::Sprite *Object);

	class bitmaskmanager {

		virtual ~bitmaskmanager();
		sf::Uint8 getpixel(const sf::Uint8* mask, const sf::Texture* tex, unsigned int x, unsigned int y);
		sf::Uint8* getmask(const sf::Texture* tex);
		sf::Uint8* createmask(const sf::Texture* tex, const sf::Image& img);
	};

	class OrientedBoundingBox // Used in the BoundingBoxTest
	{
	public:
		OrientedBoundingBox(const sf::Sprite *Object);
		// Calculate the four points of the OBB from a transformed (scaled, rotated...) sprit
		void ProjectOntoAxis(const sf::Vector2f& Axis, float& Min, float& Max);
		// Project all four points of the OBB onto the given axis and return the dotproducts of the two outermost points
		sf::Vector2f Points[4];
	private:
	};


};

