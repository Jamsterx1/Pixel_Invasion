#include "Feanwork\Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Ship.h"
#include "Timer.h"
using namespace Feanwork;

int main()
{
	Game* game = new Game("Pixel Invasion", "Resources/", 1200, 800, DEFAULT);
	game->expandResources("Sprites/");
	game->loadResources("");

	std::vector<Object*> objects;
	Timer* spawnTimer = new Timer(12, game->getWidth() / 2 - 60, game->getHeight() / 2 - 60, "Resources/Animation/spawnTimer.anim");
	Timer* killTimer = new Timer(11, 0, game->getHeight() - 60, "Resources/Animation/killTimer.anim", true);
	Object* city = new Object(4, 0, 0, false);
	Object* city1 = new Object(4, 980, 0, false);
	Player* player = new Player(0, game->getWidth() / 2, game->getHeight() / 2, 100, killTimer);
	Enemy* enemy = new Enemy(2, 300, 450, .0f, .0f, 100);
	Ship* ship = new Ship(3, 5, 0, spawnTimer);
	Ship* ship2 = new Ship(3, game->getWidth() - 495, 0, spawnTimer);
	Object* reloadVisual = new Object(10, game->getWidth() / 2 - 120, game->getHeight() - 80, false, false);
	
	objects.push_back(city);
	objects.push_back(city1);
	objects.push_back(ship);
	objects.push_back(ship2);
	objects.push_back(player);
	objects.push_back(enemy);
	objects.push_back(reloadVisual);
	objects.push_back(spawnTimer);
	objects.push_back(killTimer);

	player->switchWeapon(8, "Resources/Weapons/pistol.weapon", reloadVisual);
	game->addCollisionCheck(player);
	game->addCollisionCheck(enemy);
	game->addCollisionCheck(ship);
	game->addCollisionCheck(ship2);
	game->setPlayer(player);
	enemy->setUniqueType("Enemy");

	game->setDebugMode(true);
	game->initMenu(objects);
	game->initialize();
}
