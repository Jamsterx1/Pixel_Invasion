#include "Timer.h"
#include "Feanwork/Game.h"
#include "Player.h"
#include <sstream>

Timer::Timer(int _resourceID, float _xPos, float _yPos, std::string _anim, bool _active, std::string _name) :
	Object(_resourceID, _xPos, _yPos, false, _active),
	Animation(this, _anim, 1.0f, false)
{
	mName	  = _name;
	mRound	  = 0;
	mRoundSet = false;
	Object::setUniqueType(_name);
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
		static_cast<Text*>(_game->getInterface()->getInterface(2, "waveText"))->setString(ss.str());
		mRoundSet = true;
		Weapon* wep = static_cast<Player*>(_game->getPlayer())->getWeapon();
		wep->decreaseDamage();
		static_cast<Player*>(_game->getPlayer())->addDifficulty(0.2f);
	}
	else if(mName == "killTimer" && Animation::hasLooped())
	{
		stringstream ss;
		ss << "Lose Status: " << 1;
		static_cast<Text*>(_game->getInterface()->getInterface(2, "loseText"))->setString(ss.str());
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
