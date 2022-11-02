#include "Collision.h"
#include<string.h>

class bitmaskmanager
{
public:
	~bitmaskmanager() {
		std::map<const sf::Texture*, sf::Uint8*>::const_iterator end = bitmasks.end();
		for (std::map<const sf::Texture*, sf::Uint8*>::const_iterator iter = bitmasks.begin(); iter != end; iter++)
			delete[] iter->second;
	}

	sf::Uint8 getpixel(const sf::Uint8* mask, const sf::Texture* tex, unsigned int x, unsigned int y) {
		if (x > tex->getSize().x || y > tex->getSize().y)
			return 0;

		return mask[x + y * tex->getSize().x];
	}

	sf::Uint8* getmask(const sf::Texture* tex) {
		sf::Uint8* mask;
		std::map<const sf::Texture*, sf::Uint8*>::iterator pair = bitmasks.find(tex);
		if (pair == bitmasks.end())
		{
			sf::Image img = tex->copyToImage();
			mask = createmask(tex, img);
		}
		else
			mask = pair->second;

		return mask;
	}

	sf::Uint8* createmask(const sf::Texture* tex, const sf::Image& img) {
		sf::Uint8* mask = new sf::Uint8[tex->getSize().y*tex->getSize().x];

		for (unsigned int y = 0; y < tex->getSize().y; y++)
		{
			for (unsigned int x = 0; x < tex->getSize().x; x++)
				mask[x + y * tex->getSize().x] = img.getPixel(x, y).a;
		}

		bitmasks.insert(std::pair<const sf::Texture*, sf::Uint8*>(tex, mask));

		return mask;
	}
private:
	std::map<const sf::Texture*, sf::Uint8*> bitmasks;
};
bitmaskmanager bitmasks;

//pixelperfecttest
bool Collision::PixelPerfectTest(const sf::Sprite *object1, const sf::Sprite *object2, sf::Uint8 alphalimit) {
	sf::FloatRect intersection;
	if (object1->getGlobalBounds().intersects(object2->getGlobalBounds(), intersection)) {
		sf::IntRect o1subrect = object1->getTextureRect();
		sf::IntRect o2subrect = object2->getTextureRect();

		sf::Uint8* mask1 = bitmasks.getmask(object1->getTexture());
		sf::Uint8* mask2 = bitmasks.getmask(object2->getTexture());

		// loop through our pixels
		for (int i = intersection.left; i < intersection.left + intersection.width; i++) {
			for (int j = intersection.top; j < intersection.top + intersection.height; j++) {

				sf::Vector2f o1v = object1->getInverseTransform().transformPoint(i, j);
				sf::Vector2f o2v = object2->getInverseTransform().transformPoint(i, j);

				// make sure pixels fall within the sprite's subrect
				if (o1v.x > 0 && o1v.y > 0 && o2v.x > 0 && o2v.y > 0 &&
					o1v.x < o1subrect.width && o1v.y < o1subrect.height &&
					o2v.x < o2subrect.width && o2v.y < o2subrect.height) {

					if (bitmasks.getpixel(mask1, object1->getTexture(), (int)(o1v.x) + o1subrect.left, (int)(o1v.y) + o1subrect.top) > alphalimit &&
						bitmasks.getpixel(mask2, object2->getTexture(), (int)(o2v.x) + o2subrect.left, (int)(o2v.y) + o2subrect.top) > alphalimit)
						return true;
				}
			}
		}
	}
	return false;
}

//createtextureandbitmask
bool Collision::CreateTextureAndBitmask(sf::Texture *loadinto, const std::string filename)
{
	sf::Image img;
	if (!img.loadFromFile(filename))
		return false;
	if (!loadinto->loadFromImage(img))
		return false;

	bitmasks.createmask(loadinto, img);
	return true;
}


//CircleTest
bool Collision::CircleTest(const sf::Sprite *Object1, const sf::Sprite *Object2)
{
	sf::Vector2f Obj1Size = GetSpriteSize(Object1);
	sf::Vector2f Obj2Size = GetSpriteSize(Object2);
	float Radius1 = (Obj1Size.x + Obj1Size.y) / 4;
	float Radius2 = (Obj2Size.x + Obj2Size.y) / 4;

	sf::Vector2f Distance = GetSpriteCenter(Object1) - GetSpriteCenter(Object2);
	return (Distance.x * Distance.x + Distance.y * Distance.y <= (Radius1 + Radius2) * (Radius1 + Radius2));
}
sf::Vector2f Collision::GetSpriteCenter(const sf::Sprite *Object)
{
	sf::FloatRect AABB = Object->getGlobalBounds();
	return sf::Vector2f(AABB.left + AABB.width / 2.f, AABB.top + AABB.height / 2.f);
}
sf::Vector2f Collision::GetSpriteSize(const sf::Sprite *Object)
{
	sf::IntRect OriginalSize = Object->getTextureRect();
	sf::Vector2f Scale = Object->getScale();
	return sf::Vector2f(OriginalSize.width*Scale.x, OriginalSize.height*Scale.y);
}

//OrientedBoundingBox
Collision::OrientedBoundingBox::OrientedBoundingBox(const sf::Sprite *Object) // Calculate the four points of the OBB from a transformed (scaled, rotated...) sprite
{
	sf::Transform trans = Object->getTransform();
	sf::IntRect local = Object->getTextureRect();
	Points[0] = trans.transformPoint(0.f, 0.f);
	Points[1] = trans.transformPoint(local.width, 0.f);
	Points[2] = trans.transformPoint(local.width, local.height);
	Points[3] = trans.transformPoint(0.f, local.height);
}
void Collision::OrientedBoundingBox::ProjectOntoAxis(const sf::Vector2f& Axis, float& Min, float& Max) // Project all four points of the OBB onto the given axis and return the dotproducts of the two outermost points
{
	Min = (Points[0].x*Axis.x + Points[0].y*Axis.y);
	Max = Min;
	for (int j = 1; j < 4; j++)
	{
		float Projection = (Points[j].x*Axis.x + Points[j].y*Axis.y);

		if (Projection < Min)
			Min = Projection;
		if (Projection > Max)
			Max = Projection;
	}
}
bool Collision::BoundingBoxTest(const sf::Sprite *Object1, const sf::Sprite *Object2) {
	Collision::OrientedBoundingBox OBB1(Object1);
	Collision::OrientedBoundingBox OBB2(Object2);
	// Create the four distinct axes that are perpendicular to the edges of the two rectangles
	sf::Vector2f Axes[4] = {

		sf::Vector2f(OBB1.Points[1].x - OBB1.Points[0].x,
		OBB1.Points[1].y - OBB1.Points[0].y),
		sf::Vector2f(OBB1.Points[1].x - OBB1.Points[2].x,
		OBB1.Points[1].y - OBB1.Points[2].y),
		sf::Vector2f(OBB2.Points[0].x - OBB2.Points[3].x,
		OBB2.Points[0].y - OBB2.Points[3].y),
		sf::Vector2f(OBB2.Points[0].x - OBB2.Points[1].x,
		OBB2.Points[0].y - OBB2.Points[1].y)
	};

	for (int i = 0; i < 4; i++) // For each axis...
	{
		float MinOBB1, MaxOBB1, MinOBB2, MaxOBB2;

		// ... project the points of both OBBs onto the axis ...
		OBB1.ProjectOntoAxis(Axes[i], MinOBB1, MaxOBB1);
		OBB2.ProjectOntoAxis(Axes[i], MinOBB2, MaxOBB2);

		// ... and check whether the outermost projected points of both OBBs overlap.
		// If this is not the case, the Separating Axis Theorem states that there can be no collision between the rectangles
		if (!((MinOBB2 <= MaxOBB1) && (MaxOBB2 >= MinOBB1)))
			return false;
	}
	return true;
}

Collision::~Collision()
{

}

bool Collision::CollisionCheck( sf::Sprite *Object1,sf::Sprite *Object2, Check check ,float *x, float *y,float *slop)
{
	if (check == Down) {
		Object1->move(0.0f, 1.0f);
		bool check =  Collision::PixelPerfectTest(Object1, Object2);
		Object1->move(0.0f,-1.0f);
		return check;
	}
	if (check == TopRight || check == TopLeft)
	{
		int n;
		if (check == TopRight) n = 1;
		if (check == TopLeft) n = -1;

		sf::Vector2f befor, after;
		befor = Object1->getPosition();
		float r = 25.0;
		bool check = false;
		for (int y = r-3; y >= -r+3; y--) {
			Object1->move(n*sqrtf(powf(r,2)-powf(y,2)), -y );
			if (Collision::PixelPerfectTest(Object1, Object2))
			{
				check = true;
				after = Object1->getPosition();
				Object1->move(n*-sqrtf(powf(r, 2) - powf(y, 2)), y);
				break;
			}
			Object1->move(n*-sqrtf(powf(r, 2) - powf(y, 2)), y);
		}
		if (check)
		{
			*slop = (after.y - befor.y) / (after.x - befor.x);
			*y = (*slop * (*x - (after.x - befor.x))) + (after.y - befor.y);
		}
		return check;
	}
}