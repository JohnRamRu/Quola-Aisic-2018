#include "creature.h"


Creature::Creature(int health, std::string name)
{
	this->health = health;
	this->maxHealth = health;
	this->name = name;
}

double Creature::getArmor() { return armor; }
void Creature::setArmor(double armor) { this->armor = armor; }

int Creature::getHealth() { return health; }
int Creature::getMaxHealth() { return maxHealth; }

void Creature::setHealth(int health) { this->health = health; }
void Creature::setMaxHealth(int health) { this->maxHealth = maxHealth; }

std::string Creature::getName() { return name; }
void Creature::setName(std::string name) { this->name = name; }