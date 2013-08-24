#include "Ship.h"
#include "Feanwork/Game.h"
#include "Feanwork/Random.h"
#include "Enemy.h"

Ship::Ship(int _resourceID, float _xPos, float _yPos) :
	Object(_resourceID, _xPos, _yPos, true)
{
	mSpawnTime = .0f;
}

Ship::~Ship()
{
}

bool Ship::update(Game* _game)
{
	if(mSpawnTime >= 10.f)
	{
		mSpawnTime = .0f;
		Enemy* enemies[4];

		for(unsigned i = 0; i < 4; i++)
		{
			Random* random = Random::get_singleton();
			float xRand = random->rand_range(-0.2f, 0.2f);
			float yRand = random->rand_range(0.3f, 0.4f);

			enemies[i] = new Enemy(2, mX + 196, mY + 193, xRand, yRand, 100);
			_game->pushObject(enemies[i]);
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