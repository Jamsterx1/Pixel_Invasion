#include "Enemy.h"
#include "Feanwork/Game.h"
#include "Feanwork/Random.h"
#include "Bullet.h"
#include "Player.h"

Enemy::Enemy(int _resourceID, float _xPos, float _yPos, float _xVel, float _yVel, int _maxHealth) :
	Object(_resourceID, _xPos, _yPos, true),
	Animation(this, "Resources/Animation/enemy.anim", .05f)
{
	mHealth	   = _maxHealth;
	mHealthMax = _maxHealth;
	mVelocityX = _xVel;
	mVelocityY = _yVel;
	mAIState   = AISTATE_Pursue;
}

Enemy::~Enemy()
{
}

bool Enemy::update(Game* _game)
{
	if(mHealth <= 0)
		destroy();

	if(mAIState == AISTATE_Pursue)
	{
		sf::Vector2f direction;
		direction.x = _game->getPlayer()->getPosition().x - mX * 0.8f;
		direction.y = _game->getPlayer()->getPosition().y - mY * 0.8f;

		float normal = sqrt(direction.x * direction.x + direction.y * direction.y);
		direction.x /= normal;
		direction.y /= normal;

		mVelocityX = direction.x * _game->getDelta() * 10.f;
		mVelocityY = direction.y * _game->getDelta() * 10.f;

		Random* random = Random::get_singleton();
		mVelocityX += random->rand_range(-.5f, .5f);
		mVelocityY += random->rand_range(-.5f, .5f);

		sf::Vector2f distance;
		distance.x = _game->getPlayer()->getPosition().x - mX;
		distance.y = _game->getPlayer()->getPosition().y - mY;

		if(abs(distance.x) < 50.f && abs(distance.y) < 50.f)
			mAIState = AISTATE_Attack;
	}
	else if(mAIState == AISTATE_Attack)
	{
		mVelocityX = 0.f;
		mVelocityY = 0.f;

		sf::Vector2f distance;
		Player* player = static_cast<Player*>(_game->getPlayer());
		distance.x = (player->getPosition().x + player->getAABB().width) - (mX + mAABB.width);
		distance.y = (player->getPosition().y + player->getAABB().height) - (mY + mAABB.height);

		if(abs(distance.x) > 50.f && abs(distance.y) > 50.f)
			mAIState = AISTATE_Pursue;
	}

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
