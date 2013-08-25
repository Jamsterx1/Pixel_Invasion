#include "CoinPickup.h"
#include "Feanwork/Random.h"
#include "Feanwork/Game.h"
#include "Weapon.h"
#include "Player.h"

CoinPickup::CoinPickup(int _resourceID, float _xPos, float _yPos) :
	Object(_resourceID, _xPos, _yPos, true)
{
}

CoinPickup::~CoinPickup()
{
}

bool CoinPickup::update(Game* _game)
{
	sf::Vector2f direction;
	direction.x = _game->getPlayer()->getPosition().x - mX;
	direction.y = _game->getPlayer()->getPosition().y - mY;

	float normal = sqrt(direction.x * direction.x + direction.y * direction.y);
	direction.x /= normal;
	direction.y /= normal;

	sf::Vector2f velocity;
	velocity.x = (direction.x * _game->getDelta() * 10.f) * 25.f;
	velocity.y = (direction.y * _game->getDelta() * 10.f) * 25.f;

	Random* random = Random::get_singleton();
	float r = random->rand_range(100.f, 250.f);
	velocity.x * r;
	velocity.y * r;

	addPosition(velocity.x, velocity.y);
	Object::update(_game);
	return true;
}

bool CoinPickup::render(Game* _game)
{
	Object::render(_game);
	return true;
}

void CoinPickup::collisionCallback(sf::Vector2f _depth, sf::Vector2f _normal, Object* _collision, Game* _game)
{
	if(_collision->getUniqueType() == "Player")
	{
		static_cast<Player*>(_game->getPlayer())->addScore(50, _game);
		destroy();
	}
}
