#ifndef ENEMY_H_
#define ENEMY_H_

#include "Feanwork/Object.h"
#include "Feanwork/Animation.h"
using namespace Feanwork;

class Enemy : public Object, public Animation
{
public:
	Enemy(int _resourceID, float _xPos, float _yPos, float _xVel, float _yVel, int _maxHealth);
	~Enemy();

	bool update(Game* _game);
	bool render(Game* _game);
	void collisionCallback(sf::Vector2f _depth, sf::Vector2f _normal, Object* _collision, Game* _game);

protected:
	int   mHealth;
	int   mHealthMax;
	float mVelocityX;
	float mVelocityY;
	bool  mDead;
};

#endif