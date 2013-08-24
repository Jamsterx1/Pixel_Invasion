#include "Bullet.h"
#include "Feanwork/Game.h"
#include "Enemy.h"

Bullet::Bullet(int _resourceID, int _xPos, int _yPos, sf::Vector2f _velocity, int _damage, EMITTERTYPE _type) :
	Object(_resourceID, _xPos, _yPos, true),
	mEmitter(sf::Vector2f(_xPos, _yPos), sf::Vector2f(.0f, .0f), _type, true)
{
	mLifeCounter = .0f;
	mLife        = 6.f;
	mDamage      = _damage;
	mVelocity    = _velocity;
	mEmitter.parseParticleFile("Resources/Particles/bleed.particle");
}

Bullet::~Bullet()
{
}

bool Bullet::update(Game* _game)
{
	Object::update(_game);
	mLifeCounter += _game->getDelta();
	addPosition(mVelocity.x * (_game->getDelta() * 1000.f), mVelocity.y * (_game->getDelta() * 1000.f));

	if(mLifeCounter >= mLife)
		destroy();

	return true;
}

bool Bullet::render(Game* _game)
{
	Object::render(_game);
	return true;
}

void Bullet::collisionCallback(sf::Vector2f _depth, sf::Vector2f _normal, Object* _collision, Game* _game)
{
	Emitter* emitter = &mEmitter;
	emitter->setPosition(mX, mY);
	_game->addEmitter(&mEmitter);
	destroy();
}
