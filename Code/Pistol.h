#ifndef WEAPON_H_
#define WEAPON_H_

#include "Feanwork/Object.h"
using namespace Feanwork;

class Weapon : public Object
{
public:
	Weapon(int _resourceID, int _xPos, int _yPos, float _shootRate, int _clipSize, int _damage, sf::Vector2f _shootPoint, std::string _name = "");
	~Weapon();

	virtual bool update(Game* _game);
	virtual bool render(Game* _game);
	void collisionCallback(sf::Vector2f _depth, sf::Vector2f _normal, Object* _collision, Game* _game);
	void setOwner(Object* _owner) { mOwner = _owner; }

	int getClip() 
		{ return mClip; }

	std::string getName()
		{ return mName; }

protected:
	float		 mCounter;
	float		 mShootRate;
	int			 mClip;
	int			 mClipSize;
	int			 mDamage;
	bool		 mActive;
	sf::Vector2f mShootPoint;
	std::string  mName;
	Object*		 mOwner;
};

#endif