#pragma once
#include "hero.h"
#include "monster.h"
#include "Game_manager.h"

class Arena
{
private:
	int win = -1;
public:
	Arena();

	void battle(Hero* hero, Monster* monster);
	void battleStats(Hero* hero, Monster* monster);


};
