#include "HealthPickup.h"
#include "Feanwork/Random.h"
#include "Feanwork/Game.h"
#include "Weapon.h"
#include "Player.h"

HealthPickup::HealthPickup(int _resourceID, float _xPos, float _yPos) :
	Object(_resourceID, _xPos, _yPos, true),
	Animation(this, "Resources/Animation/pickup.anim", 0.1f, true)
{
}

HealthPickup::~HealthPickup()
{
}

bool HealthPickup::update(Game* _game)
{
	sf::Vector2f direction;
	direction.x = _game->getPlayer()->getPosition().x - mX;
	direction.y = _game->getPlayer()->getPosition().y - mY;

	float normal = sqrt(direction.x * direction.x + direction.y * direction.y);
	direction.x /= normal;
	direction.y /= normal;

	sf::Vector2f velocity;
	velocity.x = (direction.x * _game->getDelta() * 10.f) * 2.5f;
	velocity.y = (direction.y * _game->getDelta() * 10.f) * 2.5f;

	addPosition(velocity.x, velocity.y);

	Animation::update(_game);
	Object::update(_game);
	return true;
}

bool HealthPickup::render(Game* _game)
{
	Object::render(_game);
	return true;
}

void HealthPickup::collisionCallback(sf::Vector2f _depth, sf::Vector2f _normal, Object* _collision, Game* _game)
{
	if(_collision->getUniqueType() == "Player")
	{
		static_cast<Player*>(_game->getPlayer())->addHealth(10);
		destroy();
	}
}
