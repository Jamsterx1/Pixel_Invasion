#ifndef HEALTHPICKUP_H_
#define HEALTHPICKUP_H_

#include "Feanwork/Animation.h"
#include "Feanwork/Object.h"
using namespace Feanwork;

class HealthPickup : public Object, public Animation
{
public:
	HealthPickup(int _resourceID, float _xPos, float _yPos);
	~HealthPickup();

	bool update(Game* _game);
	bool render(Game* _game);
	void collisionCallback(sf::Vector2f _depth, sf::Vector2f _normal, Object* _collision, Game* _game);

protected:
};

#endif
