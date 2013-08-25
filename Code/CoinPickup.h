#ifndef COINPICKUP_H_
#define COINPICKUP_H_

#include "Feanwork/Animation.h"
#include "Feanwork/Object.h"
using namespace Feanwork;

class CoinPickup : public Object
{
public:
	CoinPickup(int _resourceID, float _xPos, float _yPos);
	~CoinPickup();

	bool update(Game* _game);
	bool render(Game* _game);
	void collisionCallback(sf::Vector2f _depth, sf::Vector2f _normal, Object* _collision, Game* _game);

protected:
};

#endif
