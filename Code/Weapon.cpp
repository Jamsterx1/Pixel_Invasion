#include "Weapon.h"
#include "Feanwork/Game.h"

Weapon::Weapon(int _resourceID, int _xPos, int _yPos, float _shootRate, int _clipSize, std::string _name) :
	Object(_resourceID, _xPos, _yPos, false)
{
	mCounter   = 0.f;
	mShootRate = _shootRate;
	mClip	   = _clipSize;
	mClipSize  = _clipSize;
	mName	   = _name;
	mActive    = true; /* NOTE: do i need this? */
}

Weapon::~Weapon()
{
}

bool Weapon::update(Game* _game)
{
	if(mActive && mCounter >= mShootRate && mClip > 0)
	{
		if(_game->mousePressed("left"))
		{
			// launch bullets


			// update weapon
			mClip--;
			mCounter = 0.f;
		}
	}
	else if(mActive)
		mCounter += _game->getDelta();

	Object::update(_game);
	return true;
}

bool Weapon::render(Game* _game)
{
	return true;
}

void Weapon::collisionCallback(sf::Vector2f _depth, sf::Vector2f _normal, Object* _collision, Game* _game)
{
}
