#include "Weapon.h"
#include "Feanwork/Game.h"
#include "Bullet.h"

Weapon::Weapon(int _resourceID, int _xPos, int _yPos, float _shootRate, int _clipSize, int _damage, sf::Vector2f _shootPoint, std::string _name) :
	Object(_resourceID, _xPos, _yPos, false)
{
	mCounter   = 0.f;
	mShootRate = _shootRate;
	mClip	   = _clipSize;
	mClipSize  = _clipSize;
	mDamage	   = _damage;
	mName	   = _name;
	mActive    = true; /* NOTE: do i need this? */
	mOwner	   = NULL;
}

Weapon::~Weapon()
{
}

bool Weapon::update(Game* _game)
{
	int clip = 1;
	if(mClipSize > 0)
		clip = mClip;

	if(mActive && mCounter >= mShootRate && clip > 0)
	{
		if(_game->mousePressed("left"))
		{
			// launch bullets
			Bullet* bullet = new Bullet(7, mX + mShootPoint.x, mY + mShootPoint.y, sf::Vector2f(.0f, 1.f), mDamage, EMITTERTYPE_Circle);
			ignore(bullet);
			mOwner->ignore(bullet);
			_game->pushObject(bullet);

			// update weapon
			mClip--;
			mCounter = 0.f;
		}
	}
	else if(mActive)
		mCounter += _game->getDelta();

	mX = mOwner->getPosition().x;
	mY = mOwner->getPosition().y;
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
