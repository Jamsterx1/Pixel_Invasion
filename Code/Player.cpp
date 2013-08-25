#include "Player.h"
#include "Feanwork/Game.h"
#include "Timer.h"
#include <sstream>
#include <fstream>

void reset(Game* _game)
{
	static_cast<Player*>(_game->getPlayer())->resetPlayer(_game);
	for(auto& i: _game->getObjects())
	{
		if(i->getUniqueType() == "Enemy" || i->getUniqueType() == "Weapon")
			i->destroy();
		else if(i->getUniqueType() == "spawnTimer")
		{
			Timer* t = static_cast<Timer*>(i);
			t->reset();
			t->setRound(0);
		}
	}

	static_cast<Text*>(_game->getInterface()->getInterface(2, "waveText"))->setString("Wave: 1");
	static_cast<Text*>(_game->getInterface()->getInterface(2, "scoreText"))->setString("Score: 0");
	static_cast<Text*>(_game->getInterface()->getInterface(2, "gameOverText"))->setString("");
	static_cast<Text*>(_game->getInterface()->getInterface(2, "replayText"))->setString("");
	static_cast<Text*>(_game->getInterface()->getInterface(2, "highscoreText"))->setString("");
}

Player::Player(int _resourceID, float _xPos, float _yPos, int _maxHealth, Object* _timer) :
	Object(_resourceID, _xPos, _yPos, false),
	Animation(this, "Resources/Animation/player.anim")
{
	mHealth	     = _maxHealth;
	mHealthMax   = _maxHealth;
	mLose	     = false;
	mTimer		 = _timer;
	mScore       = 0;
	mDifficulty	 = 1.0f;
	mHighScore	 = 0;
}

Player::~Player()
{
}

bool Player::update(Game* _game)
{
	// Input
	if(!mLose)
	{
		bool idle = true;
		if(_game->keyPressed("w"))
		{
			idle = false;
			sf::Vector2f movement(.0f, -.2f * (_game->getDelta() * 1000.f));
			addPosition(movement.x, movement.y);
		}
		else if(_game->keyPressed("s"))
		{
			idle = false;
			sf::Vector2f movement(.0f,  .2f * (_game->getDelta() * 1000.f));
			addPosition(movement.x, movement.y);
		}

		if(_game->keyPressed("a"))
		{
			idle = false;
			sf::Vector2f movement(-.3f  * (_game->getDelta() * 1000.f), .0f);
			addPosition(movement.x, movement.y);
		}
		else if(_game->keyPressed("d"))
		{
			idle = false;
			sf::Vector2f movement( .3f  * (_game->getDelta() * 1000.f), .0f);
			addPosition(movement.x, movement.y);
		} 

		if(idle == true)
			Animation::changeAnim("idle");
		else
			Animation::changeAnim("forward");

		// Keep player in boundaries
		if(mX < .0f && (mY + mAABB.height * 2) > _game->getHeight())
		{
			mX = .0f;
			mY = (float)(_game->getHeight() - (mAABB.height * 2));
		}
		else if((mX + mAABB.width * 2) > _game->getWidth() && (mY + mAABB.height * 2) > _game->getHeight())
		{
			mX = (float)(_game->getWidth() - mAABB.width * 2);
			mY = (float)(_game->getHeight() - (mAABB.height * 2));
		}
		else if(mY < 350)
			mY = 350.f;
		else if((mX + mAABB.width * 2) > _game->getWidth())
			mX = (float)(_game->getWidth() - mAABB.width * 2);
		else if(mX < .0f)
			mX = .0f;
		else if((mY + mAABB.height * 2) > _game->getHeight())
			mY = (float)(_game->getHeight() - mAABB.height * 2);
		else if(mY < .0f)
			mY = .0f;

		if(mWeapon)
		{
			mWeapon->setPosition(mX, mY);
			mWeapon->update(_game);
		}
	}
	else if(mLose)
	{
		stringstream ss;
		stringstream ss2;
		stringstream ss3;
		stringstream ss4;
		ss << "GAME OVER!";
		ss2 << "Press the right mouse button to play again";
		ss3 << "Highscore: " << mScore;
		ss4 << "Personal Best: " << mHighScore;

		if(mScore > mHighScore)
		{
			saveHighScore("Resources/player.stats");
			mHighScore = mScore;
			ss4.clear();
			ss4 << "Personal Best: " << mHighScore;
		}

		static_cast<Text*>(_game->getInterface()->getInterface(2, "gameOverText"))->setString(ss.str());
		static_cast<Text*>(_game->getInterface()->getInterface(2, "replayText"))->setString(ss2.str());
		static_cast<Text*>(_game->getInterface()->getInterface(2, "highscoreText"))->setString(ss3.str());
		static_cast<Text*>(_game->getInterface()->getInterface(2, "personalText"))->setString(ss4.str());

		if(_game->mousePressed("right"))
			reset(_game);
	}

	stringstream ss;
	ss << "Health: " << mHealth;
	static_cast<Text*>(_game->getInterface()->getInterface(2, "healthText"))->setString(ss.str());

	if(static_cast<Timer*>(mTimer)->hasLooped() || mHealth < 0)
	{
		stringstream ss2;
		ss2 << "Lose Status: " << 1;
		static_cast<Text*>(_game->getInterface()->getInterface(2, "loseText"))->setString(ss2.str());
		mLose = true;
	}

	Animation::update(_game);
	Object::update(_game);
	return true;
}

bool Player::render(Game* _game)
{
	if(mWeapon)
	{
		_game->getWindow()->draw(mWeapon->getSprite());
		Object::render(_game);
	}
	else
		Object::render(_game);

	return true;
}

void Player::collisionCallback(sf::Vector2f _depth, sf::Vector2f _normal, Object* _collision, Game* _game)
{
	addPosition(_depth.x * _normal.x, _depth.y * _normal.y);
}

void Player::switchWeapon(Weapon* _weapon, Game* _game)
{
	mWeapon = _weapon;
	mWeapon->setPosition(mX, mY);
	mWeapon->setOwner(this);

	if(_game)
	{
		stringstream ss;
		ss << mWeapon->getName();
		static_cast<Text*>(_game->getInterface()->getInterface(2, "weaponText"))->setString(ss.str());
	}
}

void Player::switchWeapon(int _resourceID, std::string _weapon, Object* _reloadVisual, Game* _game)
{
	mWeapon = new Weapon(_resourceID, mX, mY, _weapon, _reloadVisual);
	mWeapon->setOwner(this);

	if(_game)
	{
		stringstream ss;
		ss << mWeapon->getName();
		static_cast<Text*>(_game->getInterface()->getInterface(2, "weaponText"))->setString(ss.str());
	}
}

Weapon* Player::getWeapon()
{
	return mWeapon;
}

void Player::resetTimer()
{
	static_cast<Timer*>(mTimer)->reset();
}

void Player::resetPlayer(Game* _game)
{
	mHealth		= mHealthMax;
	mScore		= 0;
	mLose		= false;
	mDifficulty	= 1.0f;
	static_cast<Timer*>(mTimer)->reset();
}

void Player::addScore(int _score, Game* _game)
{
	mScore += _score;
	stringstream ss;
	ss << "Score: " << mScore;
	static_cast<Text*>(_game->getInterface()->getInterface(2, "scoreText"))->setString(ss.str());
}

void Player::saveHighScore(std::string _location)
{
	std::ofstream stream(_location);
	if(!stream.is_open())
		return;

	stream.write((char*)&mScore, sizeof(int));
	stream.close();
}

int Player::loadHighScore(std::string _location, Game* _game)
{
	std::ifstream stream(_location);
	if(!stream.is_open())
		return -1;

	stream.read((char*)&mHighScore, sizeof(int));
	stringstream ss;
	ss << "Personal Best: " << mHighScore;
	static_cast<Text*>(_game->getInterface()->getInterface(2, "personalText"))->setString(ss.str());

	stream.close();
	return mHighScore;
}
