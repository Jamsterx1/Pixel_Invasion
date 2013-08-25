#include "WeaponPickup.h"
#include "Feanwork/Random.h"
#include "Feanwork/Game.h"
#include "Weapon.h"
#include "Player.h"

WeaponPickup::WeaponPickup(float _xPos, float _yPos, Object* _reloadVisual) :
	Object(0, _xPos, _yPos, true),
	Animation(this, "Resources/Animation/pickup.anim", 0.5f, true)
{
	Random* random = Random::get_singleton();
	mReloadVisual = _reloadVisual;
	mRandom = (int)random->rand_range(13, 15);

	if(mRandom == 13)
	{
		mFile = "Resources/Weapons/fireballLauncher.weapon";
		Object::switchID(mRandom);
	}
	else if(mRandom == 14)
	{
		mFile = "Resources/Weapons/pistol.weapon";
		Object::switchID(mRandom);
	}
	else if(mRandom == 15)
	{
		mFile = "Resources/Weapons/shotgun.weapon";
		Object::switchID(mRandom);
	}
}

WeaponPickup::~WeaponPickup()
{
}

bool WeaponPickup::update(Game* _game)
{
	Animation::update(_game);
	Object::update(_game);
	return true;
}

bool WeaponPickup::render(Game* _game)
{
	Object::render(_game);
	return true;
}

void WeaponPickup::collisionCallback(sf::Vector2f _depth, sf::Vector2f _normal, Object* _collision, Game* _game)
{
	if(_collision->getUniqueType() == "Player")
	{
		int r = 8;
		// TODO: set weapon according to random

		Weapon* weapon = new Weapon(r, 0.f, 0.f, mFile, mReloadVisual);
		static_cast<Player*>(_game->getPlayer())->switchWeapon(weapon, _game);
		destroy();
	}
}
