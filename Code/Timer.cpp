#include "Timer.h"
#include "Feanwork/Game.h"
#include <sstream>

Timer::Timer(int _resourceID, float _xPos, float _yPos, std::string _anim, bool _active, std::string _name) :
	Object(_resourceID, _xPos, _yPos, false, _active),
	Animation(this, _anim, 1.0f, false)
{
	mName	  = _name;
	mRound	  = 0;
	mRoundSet = false;
}

Timer::~Timer()
{
}

bool Timer::update(Game* _game)
{
	Object::update(_game);
	Animation::update(_game);

	if(mName == "spawnTimer" && !mRoundSet && Animation::hasLooped())
	{
		mRound++;
		stringstream ss;
		ss << "Wave: " << mRound;
		static_cast<Text*>(_game->getInterface()->getInterface(0, "waveText"))->setString(ss.str());
		mRoundSet = true;
	}

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
	mRoundSet = false;
}
