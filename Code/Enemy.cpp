#include "Enemy.h"
#include "Feanwork/Game.h"
#include "Feanwork/Random.h"
#include "Bullet.h"
#include "Player.h"
#include "WeaponPickup.h"
#include "HealthPickup.h"
#include "CoinPickup.h"
#include "Timer.h"
#include <sstream>

Enemy::Enemy(int _resourceID, float _xPos, float _yPos, float _xVel, float _yVel, int _maxHealth, Object* _visual) :
	Object(_resourceID, _xPos, _yPos, true),
	Animation(this, "Resources/Animation/enemy.anim", .05f)
{
	mHealth		  = _maxHealth;
	mHealthMax	  = _maxHealth;
	mVelocityX	  = _xVel;
	mVelocityY	  = _yVel;
	mAIState	  = AISTATE_Pursue;
	mReloadVisual = _visual;
}

Enemy::~Enemy()
{
}

bool Enemy::update(Game* _game)
{
	if(mHealth <= 0)
	{
		Emitter* newEmitter = new Emitter(sf::Vector2f(mX, mY), sf::Vector2f(.0f, -1.f), EMITTERTYPE_Directional, false);
		newEmitter->parseParticleFile("Resources/Particles/plus10.particle");
		_game->addEmitter(newEmitter);
		
		Random* random = Random::get_singleton();
		int rand = (int)random->rand_range(1, 250);
		Timer* t = NULL;
		for(auto& i: _game->getObjects())
			if(i->getUniqueType() == "spawnTimer")
				t = static_cast<Timer*>(i);

		if(rand >= 190 && rand <= 219)
		{
			WeaponPickup* pickup = new WeaponPickup(14, mX, mY, mReloadVisual);
			_game->pushObject(pickup);
		}
		else if(rand >= 220 && rand <= 240)
		{
			WeaponPickup* pickup = new WeaponPickup(15, mX, mY, mReloadVisual);
			_game->pushObject(pickup);
		}
		else if(rand >= 241 && t->getRound() > 40)
		{
			WeaponPickup* pickup = new WeaponPickup(13, mX, mY, mReloadVisual);
			_game->pushObject(pickup);
		}

		HealthPickup* pickup = new HealthPickup(19, mX, mY);
		_game->pushObject(pickup);

		int coinRand = (int)random->rand_range(1, 4);
		for(int i = 0; i < coinRand; i++)
		{
			CoinPickup* pickup = new CoinPickup(20, mX, mY + (45 * i));
			_game->pushObject(pickup);
		}

		// Score
		Player* player = static_cast<Player*>(_game->getPlayer());
		sf::Vector2f playerPositon = _game->getPlayer()->getPosition();
		double distance = sqrt((playerPositon.x - mX) * (playerPositon.x - mX) + (playerPositon.y - mY) * (playerPositon.y - mY));

		float scoreRand = random->rand_range(0.3f, 0.7f);
		player->addScore((int)(1000 - distance * scoreRand), _game);

		// Destroy
		destroy();
	}

	if(mAIState == AISTATE_Pursue)
	{
		sf::Vector2f direction;
		direction.x = _game->getPlayer()->getPosition().x - mX /** 0.8f*/;
		direction.y = _game->getPlayer()->getPosition().y - mY /** 0.8f*/;

		float normal = sqrt(direction.x * direction.x + direction.y * direction.y);
		direction.x /= normal;
		direction.y /= normal;

		mVelocityX = (direction.x * _game->getDelta() * 10.f) * .6f;
		mVelocityY = (direction.y * _game->getDelta() * 10.f) * .6f;

		Random* random = Random::get_singleton();
		mVelocityX += random->rand_range(-.5f, .5f);
		mVelocityY += random->rand_range(-.5f, .5f);

		sf::Vector2f distance;
		distance.x = _game->getPlayer()->getPosition().x - mX;
		distance.y = _game->getPlayer()->getPosition().y - mY;

		if(abs(distance.x) < 25.f && abs(distance.y) < 25.f)
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
		player->damage(1);

		if(abs(distance.x) > 25.f && abs(distance.y) > 25.f)
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
		damage(bullet->getDamage(), _game);
	}
}

void Enemy::damage(int _amount, Game* _game)
{
	mHealth -= _amount;	
}
