#ifndef ENEMY_H_
#define ENEMY_H_

#include "Feanwork/Object.h"
#include "Feanwork/Animation.h"
using namespace Feanwork;

enum AISTATE
{
	AISTATE_Pursue = 0,
	AISTATE_Attack,
};

class Enemy : public Object, public Animation
{
public:
	Enemy(int _resourceID, float _xPos, float _yPos, float _xVel, float _yVel, int _maxHealth, Object* _visual);
	~Enemy();

	bool update(Game* _game);
	bool render(Game* _game);
	void collisionCallback(sf::Vector2f _depth, sf::Vector2f _normal, Object* _collision, Game* _game);
	void damage(int _amount, Game* _game);

	void setReloadVisual(Object* _visual)
		{ mReloadVisual = _visual; }

	int getHealth()
		{ return mHealth; }

protected:
	int		mHealth;
	int		mHealthMax;
	float	mVelocityX;
	float	mVelocityY;
	AISTATE mAIState;
	Object*	mReloadVisual;
};

#endif