#include "Bullet.h"
#include "Feanwork/Game.h"
#include "Enemy.h"

Bullet::Bullet(int _resourceID, int _xPos, int _yPos, sf::Vector2f _velocity, int _damage, EMITTERTYPE _type) :
	Object(_resourceID, _xPos, _yPos, true),
	mEmitter(sf::Vector2f(_xPos, _yPos), sf::Vector2f(.0f, .0f), _type, false)
{
	mCounter = .0f;
	mLife    = 6.f;
	mDamage  = _damage;
	mEmitter.parseParticleFile("Particles/bleed.particle");
}

Bullet::~Bullet()
{
}

bool Bullet::update(Game* _game)
{
	mCounter += _game->getDelta();
	if(mCounter >= mLife)
		destroy();

	addPosition(mVelocity.x, mVelocity.y);
	Object::update(_game);
	return true;
}

bool Bullet::render(Game* _game)
{
	return true;
}

void Bullet::collisionCallback(sf::Vector2f _depth, sf::Vector2f _normal, Object* _collision, Game* _game)
{
	_game->addEmitter(&mEmitter);
	destroy();
}
