#include "Feanwork\Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Ship.h"
#include "Timer.h"
using namespace Feanwork;

void startGame(Game* _game)
{
	_game->setState(GAME);

	std::vector<Object*> gameObjs;
	Timer* spawnTimer = new Timer(12, _game->getWidth() / 2 - 30, _game->getHeight() / 2 - 60, "Resources/Animation/spawnTimer.anim", false, "spawnTimer");
	Timer* killTimer = new Timer(11, 0, _game->getHeight() - 60, "Resources/Animation/killTimer.anim", true);
	Object* city = new Object(4, 0, 0, false);
	Object* city1 = new Object(4, 980, 0, false);
	Player* player = new Player(0, _game->getWidth() / 2, _game->getHeight() / 2, 100, killTimer);
	Object* reloadVisual = new Object(10, _game->getWidth() / 2 - 120, _game->getHeight() - 80, false, false);
	Enemy* enemy = new Enemy(2, 300, 450, .0f, .0f, 100, reloadVisual);
	Ship* ship = new Ship(3, 5, 0, spawnTimer, reloadVisual);
	Ship* ship2 = new Ship(3, _game->getWidth() - 495, 0, spawnTimer, reloadVisual);

	gameObjs.push_back(city);
	gameObjs.push_back(city1);
	gameObjs.push_back(ship);
	gameObjs.push_back(ship2);
	gameObjs.push_back(player);
	gameObjs.push_back(enemy);
	gameObjs.push_back(reloadVisual);
	gameObjs.push_back(spawnTimer);
	gameObjs.push_back(killTimer);

	_game->addCollisionCheck(player);
	_game->addCollisionCheck(enemy);
	_game->addCollisionCheck(ship);
	_game->addCollisionCheck(ship2);
	_game->setPlayer(player);

	player->switchWeapon(8, "Resources/Weapons/pistol.weapon", reloadVisual, nullptr);
	_game->loadUIContent("User Interface/stats.block");
	_game->getInterface()->getInterfaceBlock(1)->deactivate();
	_game->getInterface()->getInterfaceBlock(1)->setPosition(4, _game->getHeight() - 400);
	_game->getInterface()->getInterfaceBlock(1)->setActive(false);

	_game->getInterface()->getInterfaceBlock(0)->setActive(false);
	_game->getInterface()->getInterfaceBlock(1)->setActive(true);
	_game->changeMusic("Audio/game.ogg", true);
	_game->setVolume(70.f);

	std::vector<Object*> shipSpawn;
	shipSpawn = ship->spawn(4, _game);
	for(auto& i: shipSpawn)
		gameObjs.push_back(i);

	std::vector<Object*> shipSpawn2;
	shipSpawn2 = ship2->spawn(4, _game);
	for(auto& i: shipSpawn2)
		gameObjs.push_back(i);

	enemy->setUniqueType("Enemy");
	player->setUniqueType("Player");
	_game->initGame(gameObjs);
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
	game->changeMusic("Audio/menu.ogg", true);

	//game->setDebugMode(true);
	game->initMenu(menu);
	game->initialize();
}
