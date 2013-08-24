#ifndef WEAPON_H_
#define WEAPON_H_

#include "Feanwork/Object.h"
using namespace Feanwork;

class Weapon : public Object
{
public:
	Weapon(int _resourceID, int _xPos, int _yPos, float _shootRate, int _clipSize, std::string _name = "");
	~Weapon();

	bool update(Game* _game);
	bool render(Game* _game);
	void collisionCallback(sf::Vector2f _depth, sf::Vector2f _normal, Object* _collision, Game* _game);

	int getClip() 
		{ return mClip; }

	std::string getName()
		{ return mName; }

protected:
	float		mCounter;
	float		mShootRate;
	int			mClip;
	int			mClipSize;
	bool		mActive;
	std::string mName;
};

#endif