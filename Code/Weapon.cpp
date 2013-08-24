#include "Weapon.h"
#include "Feanwork/Game.h"
#include "Feanwork/Parser.h"
#include "Bullet.h"
#include "Player.h"

Weapon::Weapon(int _resourceID, int _xPos, int _yPos, std::string _weapon, Object* _reloadVisual) :
	Object(_resourceID, _xPos, _yPos, false)
{
	mCounter      = .0f;
	parseWeapon(_weapon);
	mActive       = true; /* NOTE: do i need this? */
	mOwner	      = NULL;
	mReloadCount  = .0f;
	mReloadVisual = _reloadVisual;
}

Weapon::~Weapon()
{
}

bool Weapon::update(Game* _game)
{
	int clip = 1;
	if(mClipSize > 0)
		clip = mClip;

	mCounter += _game->getDelta();
	if(mActive && mCounter >= mShootRate && clip > 0)
	{
		if(_game->mousePressed("left"))
		{
			// launch bullets
			EventManager* evm = EventManager::getSingleton();
			sf::Vector2i mousePosition = evm->getMousePos(_game);

			bool canShoot = false;
			if(mousePosition.y < mOwner->getPosition().y + mOwner->getAABB().height)
				canShoot = true;

			if(canShoot)
			{
				sf::View view = _game->getCamera();
				sf::Vector2f mousePosTrans = _game->getWindow()->mapPixelToCoords(mousePosition, view);
				sf::Vector2f shootPoint(mX + mShootPoint.x - 8, mY + mShootPoint.y);

				sf::Vector2f delta(mousePosTrans.x - shootPoint.x, mousePosTrans.y - shootPoint.y);
				float angle = atan2(delta.y, delta.x);
				float power = 500.f;

				Bullet* bullet = new Bullet(7, shootPoint.x, shootPoint.y, sf::Vector2f(cos(angle) * power, sin(angle) * power), mDamage, EMITTERTYPE_Circle);
				bullet->setUniqueType("Bullet");
				bullet->setOwner(mOwner);
				ignore(bullet);
				mOwner->ignore(bullet);
				_game->pushObject(bullet);
				static_cast<Player*>(mOwner)->changeAnim("forward");

				// update weapon
				mClip--;
				mCounter = 0.f;
			}
		}
	}

	mReloadCount += _game->getDelta();
	if(_game->keyPressed("r"))
	{
		mReload = true;
		mClip = 0;
		if(mReloadVisual)
			mReloadVisual->setActive(true);
	}

	if(mReload && mReloadCount > mReloadTime)
	{
		mClip		 = mClipSize;
		mReloadCount = .0f;
		mReload		 = false;

		if(mReloadVisual)
			mReloadVisual->setActive(false);
	}

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

void Weapon::parseWeapon(std::string _weaponFile)
{
	Parser p(_weaponFile);
	std::string keyword = "";

	while((keyword = p.getNextKeyword()) != "")
	{
		if(keyword == "Name")
			mName = p.getString(0);
		else if(keyword == "ShootRate")
			mShootRate = p.getFloat(0);
		else if(keyword == "ClipSize")
		{
			mClipSize = p.getInt(0);
			mClip     = p.getInt(0);
		}
		else if(keyword == "Damage")
			mDamage = p.getInt(0);
		else if(keyword == "ShootPoint")
		{
			mShootPoint.x = p.getFloat(0);
			mShootPoint.y = p.getFloat(1);
		}
		else if(keyword == "ReloadTime")
			mReloadTime = p.getFloat(0);
	}
}
