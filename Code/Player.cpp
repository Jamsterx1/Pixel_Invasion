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
	if(mX > _game->getWidth())
		mX = _game->getWidth() - mAABB.width;
	else if(mX > _game->getWidth())
		mX = _game->getWidth() - mAABB.width;
	else if(mX > _game->getWidth())
		mX = _game->getWidth() - mAABB.width;
	else if(mX > _game->getWidth())
		mX = _game->getWidth() - mAABB.width;

	Animation::update(_game);
	Object::update(_game);
	return true;
}

bool Player::render(Game* _game)
{
	if(mWeaponAbove)
	{
		Object::render(_game);
		_game->getWindow()->draw(mWeapon);
	}

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
}

void Player::switchWeapon(int _resourceID, float _shootRate, int _clipSize, std::string _name)
{
	mWeapon = new Weapon(_resourceID, mX, mY, _shootRate, _clipSize, _name);
}
