#ifndef PLAYER_H_
#define PLAYER_H_

#include "Weapon.h"
#include "Feanwork/Object.h"
#include "Feanwork/Animation.h"
using namespace Feanwork;

class Player : public Object, public Animation
{
public:
	Player(int _resourceID, float _xPos, float _yPos, int _maxHealth);
	~Player();

	bool update(Game* _game);
	bool render(Game* _game);
	void collisionCallback(sf::Vector2f _depth, sf::Vector2f _normal, Object* _collision, Game* _game);

	void switchWeapon(Weapon* _weapon);
	void switchWeapon(int _resourceID, float _shootRate, int _clipSize, std::string _name);

protected:
	int		mHealth;
	int		mHealthMax;
	bool    mDead;
	Weapon* mWeapon;
	bool	mWeaponAbove;
};

#endif