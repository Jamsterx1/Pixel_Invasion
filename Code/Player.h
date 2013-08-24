#ifndef PLAYER_H_
#define PLAYER_H_

#include "Weapon.h"
#include "Feanwork/Object.h"
#include "Feanwork/Animation.h"
using namespace Feanwork;

class Player : public Object, public Animation
{
public:
	Player(int _resourceID, float _xPos, float _yPos, int _maxHealth, Object* _timer);
	~Player();

	bool update(Game* _game);
	bool render(Game* _game);
	void collisionCallback(sf::Vector2f _depth, sf::Vector2f _normal, Object* _collision, Game* _game);

	void switchWeapon(Weapon* _weapon);
	void switchWeapon(int _resourceID, std::string _weapon, Object* _reloadVisual);
	void resetTimer();

protected:
	int		mHealth;
	int		mHealthMax;
	bool    mDead;
	Weapon* mWeapon;
	Object* mTimer;
};

#endif