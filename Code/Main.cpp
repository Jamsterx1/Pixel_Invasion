#include "Feanwork\Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Ship.h"
using namespace Feanwork;

int main()
{
	Game* game = new Game("Pixel Invasion", "Resources/", 1200, 800, DEFAULT);
	game->expandResources("Sprites/");
	game->loadResources("");

	std::vector<Object*> objects;
	Object* city = new Object(4, 0, 0, false);
	Object* city1 = new Object(4, 980, 0, false);
	Player* player = new Player(0, game->getWidth() / 2, game->getHeight() / 2, 100);
	Enemy* enemy = new Enemy(2, 300, 450, .0f, .0f, 100);
	Ship* ship = new Ship(3, 5, 0);
	Ship* ship2 = new Ship(3, game->getWidth() - 495, 0);
	objects.push_back(city);
	objects.push_back(city1);
	objects.push_back(ship);
	objects.push_back(ship2);
	objects.push_back(player);
	objects.push_back(enemy);
	
	player->switchWeapon(5, 0.2f, -1, "Fists");
	game->addCollisionCheck(player);
	game->setPlayer(player);

	game->setDebugMode(true);
	game->initMenu(objects);
	game->initialize();
}
