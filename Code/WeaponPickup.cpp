#include "WeaponPickup.h"
#include "Feanwork/Random.h"
#include "Feanwork/Game.h"
#include "Weapon.h"
#include "Player.h"

WeaponPickup::WeaponPickup(int _chosenID, float _xPos, float _yPos, Object* _reloadVisual) :
	Object(0, _xPos, _yPos, true),
	Animation(this, "Resources/Animation/pickup.anim", 0.1f, true)
{
	mReloadVisual  = _reloadVisual;
	mCounter	   = .0f;
	mChosenID	   = _chosenID;

	if(mChosenID == 14)
	{
		mFile = "Resources/Weapons/pistol.weapon";
		Object::switchID(mChosenID);
	}
	else if(mChosenID == 15)
	{
		mFile = "Resources/Weapons/shotgun.weapon";
		Object::switchID(mChosenID);
	}
	else if(mChosenID == 13)
	{
		mFile = "Resources/Weapons/fireballLauncher.weapon";
		Object::switchID(mChosenID);
	}
}

WeaponPickup::~WeaponPickup()
{
}

bool WeaponPickup::update(Game* _game)
{
	mCounter += _game->getDelta();
	if(mCounter >= 25.f)
		destroy();

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
		int r = 0;
		if(mChosenID == 13)
			r = 21;
		else if(mChosenID == 14)
			r = 8;
		else if(mChosenID == 15)
			r = 22;

		Weapon* weapon = new Weapon(r, 0.f, 0.f, mFile, mReloadVisual);
		static_cast<Player*>(_game->getPlayer())->switchWeapon(weapon, _game);
		destroy();
	}
}
