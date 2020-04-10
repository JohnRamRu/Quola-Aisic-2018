#include "hero.h"



Hero::Hero(double strength, double agility, double intelligence, int baseHP, int baseMP,
	int baseAttack, double st_plus, double ag_plus, double in_plus,
	HeroType type, string name) : Creature::Creature(strength*18.07f + baseHP, name)
{
	this->strength = strength;
	this->intelligence = intelligence;
	this->agility = agility;
	this->armor = agility * 0.161f;
	//Creature::health = this->strength*18.07f+baseHP;
	this->mana = intelligence * 1.493 + baseMP;
	this->maxMana = intelligence * 1.493 + baseMP;

	this->baseHP = baseHP;
	this->baseMP = baseMP;
	this->baseAttack = baseAttack;
	this->st_plus = st_plus;
	this->ag_plus = ag_plus;
	this->in_plus = in_plus;
	this->type = type;

	switch (type)
	{
	case 1:
		this->atc = strength + baseAttack + this->plusAtk;
		break;
	case 2:
		this->atc = agility + baseAttack + this->plusAtk;
		break;
	case 3:
		this->atc = intelligence + baseAttack + this->plusAtk;
		break;
	}
}
void Hero::levelup()
{
	while (this->experience >= this->nextExperience)
	{
		this->strength += this->st_plus;
		this->agility += this->ag_plus;
		this->intelligence += this->in_plus;
		level++;
		this->experience = this->experience - this->nextExperience;
		this->nextExperience = level * 125.5;
		this->upPluses = this->upPluses + 1;

		updateStats();
		printf("----------------------\n\n");
		printf("       LEVEL UP!\n");
		printf("\n  You got a upgrade point!\n");
		getSAI();
		getStats();
		printf("----------------------\n\n");
	}
}
void Hero::updateStats()
{

	this->armor = agility * 0.2f;
	this->maxHealth = this->strength * 22.5f + baseHP;
	this->maxMana = intelligence * 15.2f + baseMP;

	if (this->mana >= this->maxMana)this->mana = this->maxMana;
	if (this->health >= this->maxHealth)this->health = this->maxHealth;

	switch (type)
	{
	case 1:
		this->atc = this->strength + this->baseAttack + this->plusAtk;
		break;
	case 2:
		this->atc = this->agility + this->baseAttack + this->plusAtk;
		break;
	case 3:
		this->atc = this->intelligence + this->baseAttack + this->plusAtk;
		break;
	default:
		break;
	}
}
void Hero::getStats()
{
	printf("===========================\n");
	printf("%s statistic:\n", name.c_str());//name
	printf("ATK: %.0f-%.0f\n", atc, atc + 10);
	printf("Health: %d\n", health);
	printf("Mana: %d\n", mana);
	printf("Armor: %.0f\n", armor);
	printf("Upgrade points: %d\n", upPluses);
	printf("===========================\n\n");
}
void Hero::getSAI()
{
	printf("===========================\n");
	printf("%s has:\n", name.c_str());//name
	printf("Level: %d \n", level);
	printf("Experience: %d/%d \n", experience, nextExperience);
	printf("Strength: %.0f \n", strength);
	printf("Agility: %.0f \n", agility);
	printf("Intelligence: %.0f \n", intelligence);
	printf("===========================\n\n");
}

string Hero::getFirst() { return firstATK; }
string Hero::getUlt() { return ultATK; }

void Hero::setFirst(string first) { this->firstATK = first; }
void Hero::setUlt(string ult) { this->ultATK = ult; }

int Hero::getType() { return type; }
void Hero::setType(HeroType type) { this->type = type; }

int Hero::getMana() { return mana; }
void Hero::setMana(int mana) { this->mana = mana; }

int Hero::getExp() { return experience; }
void Hero::setExp(int exp) { this->experience = exp; }

int Hero::getMaxExp() { return nextExperience; }
void Hero::setMaxExp(int exp) { this->nextExperience = exp; }

int Hero::getMaxMana() { return maxMana; }
void Hero::setMaxMana(int maxMana) { this->maxMana = maxMana; }

int Hero::getArmor() { return armor; }
void Hero::setArmor(int armor) { this->armor = armor; }

int Hero::getLevel() { return level; }

int Hero::getStrength() { return strength; }
void Hero::setStrength(double strength) { this->strength = strength; }

int Hero::getAgility() { return agility; }
void Hero::setAgility(double agility) { this->agility = agility; }

int Hero::getIntelligence() { return intelligence; }
void Hero::setIntelligence(double intelligence) { this->intelligence = intelligence; }

int Hero::getGold() { return gold; }
void Hero::setGold(int gold) { this->gold = gold; }

int Hero::getHit() { return hit; }
void Hero::setHit(int hit) { this->hit = hit; }

double Hero::getAtk() { return atc; }
void Hero::setAtk(int atc) { this->atc = atc; }

int Hero::getPlusAtk() { return plusAtk; }
void Hero::setPlusAtk(int plusAtk) { this->plusAtk = plusAtk; }

int Hero::getUpPluses() { return upPluses; }
void Hero::setUpPluses(int upPluses) { this->upPluses = upPluses; }
