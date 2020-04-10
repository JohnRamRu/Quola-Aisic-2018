#pragma once
#include "Inventory.h"
#include "Heroes.h"
#include "Monsters.h"
#include "UpgradeBlock.h"
#include "Map.h"
#include "EnemyMap.h"
//#include <audiere.h>



class Game_manager
{
private:
	bool existLastGame = true;
	int win = -1;
	int tick = 0;

	float screen = 2.3;
	int yFlying = 49 * 8 +25;//PlayerY
	int xFlying = 89 * 8 +45;//PlayerX
	int xMove = 1;//1
	int yMove = 1;//1
	Map* mapa;
	EnemyMap* enMap[16][16];

	int xExpand = 20;// min 11 max 44
	int yExpand = 10;// min 6 max 24
public:
	Game_manager();

	void endl();
	void welcome(Hero* &hero);
	void printMainMenu();

	bool GameIsRunning = false;
	void StartGame();
	void EndGame();
	void battleStats(Hero* hero, Monster* monster);
	void winGame();
	void loseGame();
	void Menu(Inventory &inv, HANDLE out_handle, Hero* hero, UpgradeBlock &block);
	void printMaps(Inventory &inv, HANDLE out_handle, Hero* hero);
	void enemyTrigger(Inventory &inv, HANDLE out_handle, Hero* hero);

	void printEnemyOnMap();
	void settingsMap();
	void settings();
	void credits();

	//Please sempai... Don`t touch me~...
	void drawQUOLA();
	void drawAISIC();
	void drawNewGame();
	void drawContinue();
	void drawSettings();
	void drawCredits();
	void drawExitGame();
	void drawCurrentCursor(int x, int y);
	void drawOppCurrentCursor(int x, int y);
	void drawVoid(int x, int y);
	//////////////////////////


	void printInventory(Inventory &inv, HANDLE out_handle, Hero* hero);

	bool printBattle(Inventory &inv, HANDLE out_handle, Hero* hero, Monster* monster);

	void printUpgrage(HANDLE out_handle, Hero* hero, UpgradeBlock &block);
};

