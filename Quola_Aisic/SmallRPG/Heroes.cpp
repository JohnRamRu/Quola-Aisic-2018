#include "Heroes.h"


Wizard::Wizard(std::string name) : Hero(7, 2, 10, 70, 120, 10, 5.8f, 1.4f, 7.3f, hIntelligence, name)
{
	setFirst("Launch fireball!");
	setUlt("METEOR!!");
	setType(hIntelligence);

	setPic(hPic);
}

void Wizard::attack(Creature* enemy) {
	hit = RPGUtils::getRandom(atc, atc + 10.0f);
	//printf("You launch fireball!\nDamage: %d\n\n", hit);
	enemy->setHealth(enemy->getHealth() - hit);
}

bool Wizard::specialAttack(Creature* enemy)
{
	int mana_cost = 50;
	bool b = true;
	if (mana >= mana_cost)
	{
		hit = 40 * (1 + (intelligence* 0.07f));
		mana = mana - mana_cost;
		//printf("You cast Meteor!\nDamage: %d\n\n", hit);

		enemy->setHealth(enemy->getHealth() - hit);
	}
	else
	{
		b = false;
		//printf("!NOT ENOUGH MANA! You lose you turn!\n\n");
	}
	return b;
}



Warrior::Warrior(std::string name) : Hero(11, 5, 3, 100, 50, 13, 6.5f, 2.5f, 2.1f, hStrength, name)
{
	setFirst("Hit by sword!");
	setUlt("HOLY LIGHT!!");
	setType(hStrength);

	setPic(hPic);
}

void Warrior::attack(Creature* enemy) {
	hit = RPGUtils::getRandom(atc, atc + 10.0f);
	//printf("Sword hit!\nDamage: %d\n\n", hit);
	enemy->setHealth(enemy->getHealth() - hit);
}

bool Warrior::specialAttack(Creature* enemy)
{
	int mana_cost = 40;
	bool b = true;
	if (mana >= mana_cost)
	{
		hit = 55 * (1 + (intelligence* 0.07f));
		mana = mana - mana_cost;
		//printf("Dissecting hit!\nDamage: %d\n\n", hit);

		enemy->setHealth(enemy->getHealth() - hit);
	}
	else
	{
		b = false;
		//printf("!NOT ENOUGH MANA! You lose you turn!\n\n");
	}
	return b;
}



Archer::Archer(std::string name) : Hero(7, 12, 5, 80, 60, 15, 3.7f, 8.5f, 3.4f, hAgility, name)
{
	setFirst("Fire arrow");
	setUlt("ARROW HAILRAIN!!");
	setType(hAgility);

	setPic(hPic);
}

void Archer::attack(Creature* enemy) {
	hit = RPGUtils::getRandom(atc, atc + 10.0f);
	//printf("Bow shot!\nDamage: %d\n\n", hit);
	enemy->setHealth(enemy->getHealth() - hit);
}

bool Archer::specialAttack(Creature* enemy)
{
	int mana_cost = 50;
	bool b = true;
	if (mana >= mana_cost)
	{
		hit = 65 * (1 + (intelligence* 0.07f));
		mana = mana - mana_cost;
		//printf("Arrows hailstorm!\nDamage: %d\n\n", hit);

		enemy->setHealth(enemy->getHealth() - hit);
	}
	else
	{
		b = false;
		//sprintf("!NOT ENOUGH MANA! You lose you turn!\n\n");
	}
	return b;
}