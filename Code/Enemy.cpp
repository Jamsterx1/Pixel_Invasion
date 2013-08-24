#include "Enemy.h"
#include "Feanwork/Game.h"
#include "Bullet.h"

Enemy::Enemy(int _resourceID, float _xPos, float _yPos, float _xVel, float _yVel, int _maxHealth) :
	Object(_resourceID, _xPos, _yPos, true),
	Animation(this, "Resources/Animation/enemy.anim", .05f)
{
	mHealth	   = _maxHealth;
	mHealthMax = _maxHealth;
	mVelocityX = _xVel;
	mVelocityY = _yVel;
}

Enemy::~Enemy()
{
}

bool Enemy::update(Game* _game)
{
	if(mHealth <= 0)
		destroy();

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
	if(_collision->getUniqueType() == "Bullet")
	{
		Bullet* bullet = static_cast<Bullet*>(_collision);
		damage(bullet->getDamage());
	}
}

void Enemy::damage(int _amount)
{
	mHealth -= _amount;	
}
