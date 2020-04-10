#pragma once
#include "creature.h"
#include "Inventory.h"
using namespace std;

enum HeroType { none = 0, hStrength, hAgility, hIntelligence };
//enum eHeroes {};
//!!!!!!!!!!!!!!!!!!!enum baff {};

class Hero : public Creature
{
private:
	int experience = 0;
	int level = 1;
	int nextExperience = 120;
	int upPluses = 3;/*0*/

protected:
	double strength;
	double agility;
	double intelligence;

	double st_plus;
	double ag_plus;
	double in_plus;

	int hit = 0;//for battleLog (Special Attack)

	int mana;
	int maxMana;
	double atc = 0;//attack
	int plusAtk = 0;
	int baseHP;
	int baseMP;
	HeroType type;
	int baseAttack;
	int gold = 0;

	string firstATK;
	string ultATK;

	////
	string hPic[25] = {
	"            |,|||||||,|            \n",
	"          ,|||||||||||||,          \n",
	"         ,|||||||||||||||,         \n",
	"        ||||||       ||||,,        \n",
	"        ,|||||||   ||||||,,        \n",
	"        ||||    | |    ||,|        \n",
	"         ,,     |||     ,,         \n",
	"         ,,|||||| ||||||,.         \n",
	"          |,,||,,|,,||,,|          \n",
	"            ,,,,,,,,,,,            \n",
	"          |,..|.....|..,|          \n",
	"           ,,.,|| ||,.,,           \n",
	"           ,| ,|,,,|, ,,           \n",
	"          |,.   |,,   .,|          \n",
	"           ,| ,|||||. |,           \n",
	"          |,,,.,,|,..,,,|          \n",
	"          |.,|,|   |,|,.|          \n",
	"          ||  ,|   |,  ||          \n",
	"             ||.   .||             \n",
	"             ||,   ,||             \n",
	"              ,|   |,              \n",
	"              ,|   |,              \n",
	"             |,.   .,|             \n",
	"             |..   ..|             \n",
	"             |,|   |,|             \n"
	};//

public:
	Hero(double strength, double agility, double intelligence, int baseHP, int baseMP,
		int baseAttack, double st_plus, double ag_plus, double in_plus, HeroType type, string name);
	//type = 1-strength, 2-agility, 3-intelligence

	virtual bool specialAttack(Creature* enemy) = 0;

	void levelup();

	void updateStats();
	void getStats();
	void getSAI();

	string getFirst();
	string getUlt();

	void setFirst(string first);
	void setUlt(string ult);

	int getType();
	void setType(HeroType type);

	int getMana();
	void setMana(int mana);

	int getMaxMana();
	void setMaxMana(int mana);

	int getExp();
	void setExp(int exp);

	int getMaxExp();
	void setMaxExp(int exp);

	int getArmor();
	void setArmor(int armor);

	int getLevel();

	int getStrength();
	void setStrength(double strength);

	int getAgility();
	void setAgility(double agility);

	int getIntelligence();
	void setIntelligence(double intelligence);

	int getGold();
	void setGold(int gold);

	int getHit();
	void setHit(int hit);

	double getAtk();
	void setAtk(int atc);

	int getPlusAtk();
	void setPlusAtk(int plusAtk);

	int getUpPluses();
	void setUpPluses(int upPluses);

	//virtual void choiceToAttack(Creature* enemy) = 0;

};
