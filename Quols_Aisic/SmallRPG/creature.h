#pragma once
#include "Utils.h"
using namespace std;

class Creature
{
protected:
	int health;
	int maxHealth;
	double armor;
	string name = "NONE";
	string pic[25];//25*40
public:
	Creature(int health, std::string name);

	double getArmor();
	void setArmor(double armor);

	int getHealth();
	int getMaxHealth();

	void setHealth(int health);
	void setMaxHealth(int health);

	std::string getName();
	void setName(std::string name);

	string getPic(int index) { return pic[index]; }
	void setPic(string pic[])
	{
		for (int i = 0; i < 25; i++)
		{
			this->pic[i] = pic[i];
		}
	}

	virtual void attack(Creature* enemy) = 0;
};
