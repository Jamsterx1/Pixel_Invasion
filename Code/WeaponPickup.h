#ifndef WEAPONPICKUP_H_
#define WEAPONPICKUP_H_

#include "Feanwork/Animation.h"
#include "Feanwork/Object.h"
using namespace Feanwork;

class WeaponPickup : public Object, public Animation
{
public:
	WeaponPickup(float _xPos, float _yPos, Object* _reloadVisual);
	~WeaponPickup();

	bool update(Game* _game);
	bool render(Game* _game);
	void collisionCallback(sf::Vector2f _depth, sf::Vector2f _normal, Object* _collision, Game* _game);

protected:
	Object*		mReloadVisual;
	std::string mFile;
	int			mRandom;
};

#endif
