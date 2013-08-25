#ifndef WEAPON_H_
#define WEAPON_H_

#include "Feanwork/Object.h"
using namespace Feanwork;

class Weapon : public Object
{
public:
	Weapon(int _resourceID, int _xPos, int _yPos, std::string _weapon, Object* _reloadVisual = nullptr);
	~Weapon();

	virtual bool update(Game* _game);
	virtual bool render(Game* _game);
	void collisionCallback(sf::Vector2f _depth, sf::Vector2f _normal, Object* _collision, Game* _game);
	void setOwner(Object* _owner) { mOwner = _owner; }
	void parseWeapon(std::string _weaponFile);

	int getClip() 
		{ return mClip; }

	std::string getName()
		{ return mName; }

	float getDamage()
		{ return mDamage; }

	void decreaseDamage()
		{ mDamage -= 0.1f; }

protected:
	float		 mCounter;
	float		 mShootRate;
	float		 mReloadCount;
	float		 mReloadTime;
	bool		 mReload;
	int			 mLastClip;
	int			 mClip;
	int			 mClipSize;
	int			 mClipCapacity;
	float		 mDamage;
	bool		 mActive;
	sf::Vector2f mShootPoint;
	std::string  mName;
	Object*		 mOwner;
	Object*		 mReloadVisual;
};

#endif