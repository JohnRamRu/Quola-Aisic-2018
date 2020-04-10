#pragma once
#include "hero.h"
#include "monster.h"

class Arena
{
private:
	int win = -1;
public:
	Arena(){}

	void battle(Hero* hero, Monster* monster)
	{
		printf("############################\n");
		printf("       %s появился!\n", monster->getName().c_str());
		printf("%s:\nHP: %d\n", monster->getName().c_str(), monster->getHealth());
		printf("############################\n");
		printf("%s:\nHP: %d\nMP: %d\n", hero->getName().c_str(), hero->getHealth(), hero->getMana());
		printf("############################\n\n");
		while (monster->getHealth() > 0 && hero->getHealth() > 0)
		{
			hero->choiceToAttack(monster);
			monster->attack(hero);
			battleStats(hero, monster);
		}

		if (monster->getHealth() <= 0)win = 1;
		
		if (hero->getHealth() <= 0)win = 0;


		if (win == 1)
		{
			printf("===============================\n");
			printf("            YOU WIN\n");
			printf("===============================\n\n");
			hero->setExp(hero->getExp() + monster->getDrop().getDExp());
			if(monster->getDrop().getDType()==HP_POTION) hero->setHealth(hero->getHealth()+(monster->getDrop().getDGrade()*10));
            if(monster->getDrop().getDType()==MP_POTION) hero->setMana(hero->getMana()+(monster->getDrop().getDGrade()*10));
			
			if (hero->getExp() >= hero->getMaxExp())hero->levelup();

			delete monster;
			win = -1;
		}
		else if(win == 0){
			printf("*******************************\n");
			printf("            YOU DIE\n");
			printf("*******************************\n\n");
			win = -1;
		}
	}
	void battleStats(Hero* hero, Monster* monster)
	{
		printf("%s:\nHP: %d\nMP: %d\n\n", hero->getName().c_str(), hero->getHealth(), hero->getMana());
		printf("%s:\nHP: %d\n\n", monster->getName().c_str(), monster->getHealth());
	}

};
