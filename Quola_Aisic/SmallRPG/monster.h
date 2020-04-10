#pragma once
#include "creature.h"
#include "Utils.h"

class Monster : public Creature
{
protected:
	int damage;
	int dropID=0;
	int mobLevel = 1;
	string sAttack;
	Drop drop;
	string mPic[25];
	EnemyType type = WispT;

public:
	Monster(int health, std::string name);
	int getDropID() { return dropID; }
	int getMobLevel() { return mobLevel; }
	virtual Drop getDrop() = 0;
	virtual void dropItem(Inventory &inv) = 0;
	
	EnemyType getType();
	string getAttack();
	~Monster();
	virtual void attack(Creature* enemy) = 0;
};

