#include "Timer.h"
#include "Feanwork/Game.h"

Timer::Timer(int _resourceID, float _xPos, float _yPos, std::string _anim, bool _active) :
	Object(_resourceID, _xPos, _yPos, false, _active),
	Animation(this, _anim, 1.0f, false)
{
}

Timer::~Timer()
{
}

bool Timer::update(Game* _game)
{
	Object::update(_game);
	Animation::update(_game);

	if(Animation::hasLooped())
		Object::setActive(false);

	return true;
}

bool Timer::render(Game* _game)
{
	Object::render(_game);
	return true;
} 

void Timer::collisionCallback(sf::Vector2f _depth, sf::Vector2f _normal, Object* _collision, Game* _game)
{
}

void Timer::reset()
{
	Animation::mCurrentFrame = 0;
	Animation::mStepCount    = .0f;
	Animation::resetLooped();
	ANIMATION& anim = Animation::mAnimations[Animation::mCurrentAnim];
	Animation::mHook->setRect(anim[0]);
	Object::setActive(true);
}
