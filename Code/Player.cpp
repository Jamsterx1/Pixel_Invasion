#include "Player.h"
#include "Feanwork/Game.h"

Player::Player(int _resourceID, float _xPos, float _yPos, int _maxHealth) :
	Object(_resourceID, _xPos, _yPos, false),
	Animation(this, "Resources/Animation/player.anim")
{
	mHealth	     = _maxHealth;
	mHealthMax   = _maxHealth;
	mDead	     = false;
	mWeaponAbove = true;
}

Player::~Player()
{
}

bool Player::update(Game* _game)
{
	// Input
	if(_game->keyPressed("w"))
	{
		sf::Vector2f movement(.0f, -.2f * (_game->getDelta() * 1000.f));
		addPosition(movement.x, movement.y);
	}
	else if(_game->keyPressed("s"))
	{
		sf::Vector2f movement(.0f,  .2f * (_game->getDelta() * 1000.f));
		addPosition(movement.x, movement.y);
	}

	if(_game->keyPressed("a"))
	{
		sf::Vector2f movement(-.2f  * (_game->getDelta() * 1000.f), .0f);
		addPosition(movement.x, movement.y);
	}
	else if(_game->keyPressed("d"))
	{
		sf::Vector2f movement( .2f  * (_game->getDelta() * 1000.f), .0f);
		addPosition(movement.x, movement.y);
	}

	// Keep player in boundaries
	if(mX < .0f && (mY + mAABB.height * 2) > _game->getHeight())
	{
		mX = .0f;
		mY = _game->getHeight() - (mAABB.height * 2);
	}
	else if((mX + mAABB.width * 2) > _game->getWidth() && (mY + mAABB.height * 2) > _game->getHeight())
	{
		mX = _game->getWidth() - mAABB.width * 2;
		mY = _game->getHeight() - (mAABB.height * 2);
	}
	else if((mX + mAABB.width * 2) > _game->getWidth())
		mX = _game->getWidth() - mAABB.width * 2;
	else if(mX < .0f)
		mX = .0f;
	else if((mY + mAABB.height * 2) > _game->getHeight())
		mY = _game->getHeight() - mAABB.height * 2;
	else if(mY < .0f)
		mY = .0f;

	if(mWeapon)
		mWeapon->update(_game);

	Animation::update(_game);
	Object::update(_game);
	return true;
}

bool Player::render(Game* _game)
{
	if(mWeapon)
	{
		if(mWeaponAbove)
		{
			Object::render(_game);
			_game->getWindow()->draw(mWeapon->getSprite());
		}
		else if(!mWeaponAbove)
		{
			_game->getWindow()->draw(mWeapon->getSprite());
			Object::render(_game);
		}
	}
	else
		Object::render(_game);

	return true;
}

void Player::collisionCallback(sf::Vector2f _depth, sf::Vector2f _normal, Object* _collision, Game* _game)
{
	addPosition(_depth.x * _normal.x, _depth.y * _normal.y);
}

void Player::switchWeapon(Weapon* _weapon)
{
	mWeapon = _weapon;
	mWeapon->setOwner(this);
}

void Player::switchWeapon(int _resourceID, float _shootRate, int _clipSize, int _damage, sf::Vector2f _shootPoint, std::string _name)
{
	mWeapon = new Weapon(_resourceID, mX, mY, _shootRate, _clipSize, _damage, _shootPoint, _name);
	mWeapon->setOwner(this);
}
