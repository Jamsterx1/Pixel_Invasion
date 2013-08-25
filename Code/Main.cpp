#include "Feanwork\Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Ship.h"
#include "Timer.h"
using namespace Feanwork;

void startGame(Game* _game)
{
	_game->setState(GAME);
	_game->getInterface()->getInterfaceBlock(0)->setActive(false);
	_game->getInterface()->getInterfaceBlock(1)->setActive(true);
};

void quitGame(Game* _game)
{
	_game->exit();
};

int main()
{
	Game* game = new Game("Pixel Invasion", "Resources/", 1200, 800, DEFAULT);
	game->expandResources("Sprites/");
	game->loadResources("");

	std::vector<Object*> menu;
	Object* title = new Object(18, 0, 0, false);
	menu.push_back(title);

	game->addUICallback("startGame", startGame);
	game->addUICallback("quitGame", quitGame);
	game->loadUIContent("User Interface/menu.block");

	std::vector<Object*> gameObjs;
	Timer* spawnTimer = new Timer(12, game->getWidth() / 2 - 60, game->getHeight() / 2 - 60, "Resources/Animation/spawnTimer.anim", false, "spawnTimer");
	Timer* killTimer = new Timer(11, 0, game->getHeight() - 60, "Resources/Animation/killTimer.anim", true);
	Object* city = new Object(4, 0, 0, false);
	Object* city1 = new Object(4, 980, 0, false);
	Player* player = new Player(0, game->getWidth() / 2, game->getHeight() / 2, 100, killTimer);
	Object* reloadVisual = new Object(10, game->getWidth() / 2 - 120, game->getHeight() - 80, false, false);
	Enemy* enemy = new Enemy(2, 300, 450, .0f, .0f, 100, reloadVisual);
	Ship* ship = new Ship(3, 5, 0, spawnTimer, reloadVisual);
	Ship* ship2 = new Ship(3, game->getWidth() - 495, 0, spawnTimer, reloadVisual);

	gameObjs.push_back(city);
	gameObjs.push_back(city1);
	gameObjs.push_back(ship);
	gameObjs.push_back(ship2);
	gameObjs.push_back(player);
	gameObjs.push_back(enemy);
	gameObjs.push_back(reloadVisual);
	gameObjs.push_back(spawnTimer);
	gameObjs.push_back(killTimer);

	game->addCollisionCheck(player);
	game->addCollisionCheck(enemy);
	game->addCollisionCheck(ship);
	game->addCollisionCheck(ship2);
	game->setPlayer(player);

	player->switchWeapon(8, "Resources/Weapons/pistol.weapon", reloadVisual, nullptr);
	game->loadUIContent("User Interface/stats.block");
	game->getInterface()->getInterfaceBlock(1)->deactivate();
	game->getInterface()->getInterfaceBlock(1)->setPosition(0, game->getHeight() - 200);
	game->getInterface()->getInterfaceBlock(1)->setActive(false);

	enemy->setUniqueType("Enemy");
	player->setUniqueType("Player");

	game->setDebugMode(true);
	game->initMenu(menu);
	game->initGame(gameObjs);
	game->initialize();
}
