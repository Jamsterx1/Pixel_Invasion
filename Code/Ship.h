#ifndef SHIP_H_
#define SHIP_H_

#include "Feanwork/Object.h"
#include "Feanwork/Animation.h"
using namespace Feanwork;

class Ship : public Object
{
public:
	Ship(int _resourceID, float _xPos, float _yPos, Object* _timer, Object* _visual);
	~Ship();

	bool update(Game* _game);
	bool render(Game* _game);
	void collisionCallback(sf::Vector2f _depth, sf::Vector2f _normal, Object* _collision, Game* _game);

protected:
	float   mSpawnTime;
	Object* mTimer;
	Object* mVisual;
};

#endif