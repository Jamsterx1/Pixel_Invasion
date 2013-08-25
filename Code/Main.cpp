#include "Feanwork\Game.h"
#include "Player.h"
#include "Enemy.h"
#include "Ship.h"
#include "Timer.h"
#include <sstream>
using namespace Feanwork;

void toggleMusic(Game* _game)
{
	if(_game->getMusic()->getStatus() == sf::Music::Playing)
		_game->getMusic()->pause();
	else if(_game->getMusic()->getStatus() == sf::Music::Paused)
		_game->getMusic()->play();
}

void startGame(Game* _game)
{
	_game->setState(GAME);

	std::vector<Object*> gameObjs;
	Timer* spawnTimer = new Timer(12, (float)_game->getWidth() / 2.f - 60, (float)_game->getHeight() / 2.f - 40, "Resources/Animation/spawnTimer.anim", false, "spawnTimer");
	Timer* killTimer = new Timer(11, 0.f, (float)_game->getHeight() - 60.f, "Resources/Animation/killTimer.anim", true);
	Object* city = new Object(4, 0.f, 0.f, false);
	Object* city1 = new Object(4, 980.f, 0.f, false);
	Player* player = new Player(0, (float)_game->getWidth() / 2.f, (float)_game->getHeight() / 2.f, 100, killTimer);
	Object* reloadVisual = new Object(10, (float)_game->getWidth() / 2.f - 120, (float)_game->getHeight() - 80.f, false, false);
	Ship* ship = new Ship(3, 5.f, 0.f, spawnTimer, reloadVisual);
	Ship* ship2 = new Ship(3, (float)_game->getWidth() - 495.f, 0.f, spawnTimer, reloadVisual);
	Object* crosshair = new Object(27, 0.f, 0.f, false);

	gameObjs.push_back(city);
	gameObjs.push_back(city1);
	gameObjs.push_back(ship);
	gameObjs.push_back(ship2);
	gameObjs.push_back(player);
	gameObjs.push_back(reloadVisual);
	gameObjs.push_back(spawnTimer);
	gameObjs.push_back(killTimer);
	gameObjs.push_back(crosshair);

	_game->addCollisionCheck(player);
	_game->addCollisionCheck(ship);
	_game->addCollisionCheck(ship2);
	_game->setPlayer(player);
	_game->setCursor(crosshair);

	player->switchWeapon(8, "Resources/Weapons/pistol.weapon", reloadVisual, nullptr);
	_game->loadUIContent("User Interface/stats.block");
	_game->loadUIContent("User Interface/music.block");
	_game->getInterface()->getInterfaceBlock(2)->setPosition(4, _game->getHeight() - 400);
	_game->getInterface()->getInterfaceBlock(3)->setPosition(_game->getWidth() - 50, _game->getHeight() - 50);

	_game->getInterface()->getInterfaceBlock(0)->setActive(false);
	_game->getInterface()->getInterfaceBlock(2)->setActive(true);
	_game->getInterface()->getInterfaceBlock(3)->setActive(true);
	player->setHighScore(player->loadHighScore("Resources/player.stats", _game));
	_game->changeMusic("Audio/game.ogg", true);
	_game->setVolume(15.f);

	std::vector<Object*> shipSpawn;
	shipSpawn = ship->spawn(1, _game);
	for(auto& i: shipSpawn)
		gameObjs.push_back(i);

	std::vector<Object*> shipSpawn2;
	shipSpawn2 = ship2->spawn(1, _game);
	for(auto& i: shipSpawn2)
		gameObjs.push_back(i);

	player->setUniqueType("Player");
	_game->initGame(gameObjs);
};

void gotoInstructions(Game* _game)
{
	_game->setState(INSTRUCTIONS);
	_game->getInterface()->getInterfaceBlock(0)->setActive(false);
	_game->getInterface()->getInterfaceBlock(1)->setActive(true);
}

void gotoMenu(Game* _game)
{
	_game->setState(MENU);
	_game->getInterface()->getInterfaceBlock(0)->setActive(true);
	_game->getInterface()->getInterfaceBlock(1)->setActive(false);
}

void quitGame(Game* _game)
{
	_game->exit();
};

int main(int argc, const char* argv[])
{
	Game* game = new Game("Pixel Invasion", "Resources/", 1200, 800, DEFAULT);
	game->expandResources("Sprites/");
	game->loadResources("");

	std::vector<Object*> menu;
	Object* title = new Object(18, 0, 0, false);
	menu.push_back(title);

	std::vector<Object*> instructions;
	Object* inst = new Object(28, .0f, .0f, false);
	instructions.push_back(inst);

	game->addUICallback("startGame", startGame);
	game->addUICallback("quitGame", quitGame);
	game->addUICallback("toggleMusic", toggleMusic);
	game->addUICallback("gotoInstructions", gotoInstructions);
	game->addUICallback("gotoMenu", gotoMenu);
	game->loadUIContent("User Interface/menu.block");
	game->changeMusic("Audio/menu.ogg", true);
	game->setVolume(15.f);

	game->loadUIContent("User Interface/instructions.block");
	game->getInterface()->getInterfaceBlock(1)->setPosition(0, 700);
	game->getInterface()->getInterfaceBlock(1)->setActive(false);

	stringstream ss;
	ss << "Developed by Jamie Massey. #LD27";
	static_cast<Text*>(game->getInterface()->getInterface(0, "creditText"))->setString(ss.str());

	stringstream ss2;
	ss2 << "Source Code for both Game and Framework available";
	static_cast<Text*>(game->getInterface()->getInterface(0, "infoText"))->setString(ss2.str());

	stringstream ss3;
	ss3 << "at www.github.com/Jamsterx1, thanks for playing:";
	static_cast<Text*>(game->getInterface()->getInterface(0, "infoText2"))->setString(ss3.str());

	game->addSound("pistol", "Resources/Audio/pistol.wav");
	game->addSound("shotgun", "Resources/Audio/shotgun.wav");
	game->addSound("fireball", "Resources/Audio/fireball.wav");
	game->addSound("reload", "Resources/Audio/reload.wav");

	//game->setDebugMode(true);
	game->initMenu(menu);
	game->initInstructions(instructions);
	game->initialize();
}
