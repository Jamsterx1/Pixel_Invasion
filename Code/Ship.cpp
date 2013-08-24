#include "Ship.h"
#include "Feanwork/Game.h"
#include "Feanwork/Random.h"
#include "Enemy.h"
#include "Timer.h"

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
	if(mSpawnTime < 7.2f && mSpawnTime > 6.8f)
		static_cast<Timer*>(mTimer)->reset();
	if(mSpawnTime >= 10.f)
	{
		mSpawnTime = .0f;
		Enemy* enemies[4];

		for(unsigned i = 0; i < 4; i++)
		{
			Random* random = Random::get_singleton();
			float xRand = random->rand_range(-0.2f, 0.2f);
			float yRand = random->rand_range(0.3f, 0.4f);

			enemies[i] = new Enemy(2, mX + 196, mY + 193, xRand, yRand, 100, mVisual);
			enemies[i]->setUniqueType("Enemy");
			enemies[i]->ignore(_game->getPlayer());
			_game->pushObject(enemies[i]);
			_game->getPlayer()->ignore(enemies[i]);
			_game->addCollisionCheck(enemies[i]);
		}
		std::cout << "Spawn"; // Spawn stuff
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
