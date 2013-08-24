#ifndef BULLET_H_
#define BULLET_H_

#include "Feanwork/Object.h"
#include "Feanwork/Emitter.h"
using namespace Feanwork;

class Bullet : public Object
{
public:
	Bullet(int _resourceID, int _xPos, int _yPos, sf::Vector2f _velocity, float _damage, EMITTERTYPE _type);
	~Bullet();

	bool update(Game* _game);
	bool render(Game* _game);
	void collisionCallback(sf::Vector2f _depth, sf::Vector2f _normal, Object* _collision, Game* _game);
	void setOwner(Object* _owner) { mOwner = _owner; }

	int getDamage()
		{ return (int)mDamage; }

protected:
	float		 mLifeCounter;
	float		 mLife;
	float		 mDamage;
	Emitter		 mEmitter;
	sf::Vector2f mVelocity;
	Object*		 mOwner;
};

#endif