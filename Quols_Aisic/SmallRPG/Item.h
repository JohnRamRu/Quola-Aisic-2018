#pragma once

#include <iostream>
#include <string>
#include "stdlib.h"
#include "stdio.h"
using namespace std;


enum Type { thing = 0, weapon, head, body, legs, clear, EqWeapon, EqHead, EqBody, EqLegs, potion };
enum Plus { no = 0, strength, agility, intelligence, hp, mp, attack };

//list <int> ListOfItems{1, 2};



class Item
{
private:
	std::string name;
	int buyValue;
	int sellValue;
	Type type;
	std::string biograthy;
	Plus pluses;
	int iPluses = 0;

	int count;
public:


	Item();
	Item(Type type);
	Item(std::string name, int count, int buyValue, int sellValue,
		Type type, Plus pluses, int iPluses, std::string bio);
	


	virtual ~Item();

	Plus getPluses();
	int getIPluses();

	int getCount();
	void setCount(int count);

	std::string getName();
	int getBuyValue();
	int getSellValue();
	std::string getBio();

	int getType();
	void setType(Type type);
	//STATS?
};

