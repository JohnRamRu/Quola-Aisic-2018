#pragma once
#include "hero.h"

class Wizard : public Hero
{
public:
	Wizard(std::string name);

	void attack(Creature* enemy);
	bool specialAttack(Creature* enemy);

};
class Warrior : public Hero
{
public:
	Warrior(std::string name);

	void attack(Creature* enemy);
	bool specialAttack(Creature* enemy);

};
class Archer : public Hero
{
public:
	Archer(std::string name);

	void attack(Creature* enemy);
	bool specialAttack(Creature* enemy);
};
