#pragma once
#include "Item.h"

class Inventory
{
protected:
	int allCount;
	int numberOfItems;
	Item** itemArr;
	void expand();
	void init(const int from);

public:

	Item* head = new Item(EqHead);
	Item* body = new Item(EqBody);
	Item* legs = new Item(EqLegs);
	Item* weapon = new Item(EqWeapon);


	Inventory();
	~Inventory();

	void addItem(const Item &item);

	void createSlot();

	void removeItem(int index);
	void deleteItem(int index);
	void teleportItem(int index, const Item &item);
	void setItem(int index, const Item &item);
	void findItem(Item* item);
	Item* getItem(int index);

	int getCount();

	void checkEquiped();
};

