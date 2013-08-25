#include "Ship.h"
#include "Feanwork/Game.h"
#include "Feanwork/Random.h"
#include "Enemy.h"
#include "Timer.h"
#include "Player.h"

Ship::Ship(int _resourceID, float _xPos, float _yPos, Object* _timer, Object* _visual) :
	Object(_resourceID, _xPos, _yPos, true)
{
	mSpawnTime = .0f;
	mTimer	   = _timer;
	mVisual	   = _visual;
}

Ship::~Ship()
{
}

bool Ship::update(Game* _game)
{
	if(mSpawnTime < 7.1f && mSpawnTime > 6.9f)
		static_cast<Timer*>(mTimer)->reset();
	if(mSpawnTime >= 10.f)
	{
		mSpawnTime = .0f;
		Player* player = static_cast<Player*>(_game->getPlayer());
		int s = (int)player->getDifficulty();
		spawn(s, _game);
	}
	else
		mSpawnTime += _game->getDelta();

	Object::update(_game);
	return true;
}

bool Ship::render(Game* _game)
{
	Object::render(_game);
	return true;
}

void Ship::collisionCallback(sf::Vector2f _depth, sf::Vector2f _normal, Object* _collision, Game* _game)
{
}

std::vector<Object*> Ship::spawn(int _amount, Game* _game)
{
	std::vector<Object*> objects;
	for(int i = 0; i < _amount; i++)
	{
		Random* random = Random::get_singleton();
		float xRand = random->rand_range(-0.2f, 0.2f);
		float yRand = random->rand_range(0.3f, 0.4f);

		Player* player = static_cast<Player*>(_game->getPlayer());
		Enemy* newEnemy = new Enemy(2, (float)(mX + 196), (float)(mY + 193), xRand, yRand, 100 + (int)(player->getDifficulty() * 1.5f), mVisual);
		newEnemy->setUniqueType("Enemy");
		newEnemy->ignore(_game->getPlayer());
		_game->pushObject(newEnemy);
		_game->getPlayer()->ignore(newEnemy);
		_game->addCollisionCheck(newEnemy);
		objects.push_back(newEnemy);
	}
	return objects;
}
