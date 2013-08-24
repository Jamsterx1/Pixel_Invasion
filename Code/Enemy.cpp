#include "Enemy.h"
#include "Feanwork/Game.h"

Enemy::Enemy(int _resourceID, float _xPos, float _yPos, float _xVel, float _yVel, int _maxHealth) :
	Object(_resourceID, _xPos, _yPos, true),
	Animation(this, "Resources/Animation/enemy.anim", .05f)
{
	mHealth	   = _maxHealth;
	mHealthMax = _maxHealth;
	mDead	   = false;
	mVelocityX = _xVel;
	mVelocityY = _yVel;
}

Enemy::~Enemy()
{
}

bool Enemy::update(Game* _game)
{
	Animation::update(_game);
	addPosition(mVelocityX * (_game->getDelta() * 1000.f), mVelocityY * (_game->getDelta() * 1000.f));
	Object::update(_game);
	return true;
}

bool Enemy::render(Game* _game)
{
	Object::render(_game);
	return true;
}

void Enemy::collisionCallback(sf::Vector2f _depth, sf::Vector2f _normal, Object* _collision, Game* _game)
{
	//addPosition(_depth.x * _normal.x, _depth.y * _normal.y);
}
