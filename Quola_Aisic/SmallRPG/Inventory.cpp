#include "Inventory.h"



Inventory::Inventory()
{
	allCount = 100;
	numberOfItems = 0;
	itemArr = new Item*[allCount];
	head = new Item();
	body = new Item();
	legs = new Item();
	weapon = new Item();
}

Inventory::~Inventory()
{
	for (int i = 0; i < this->allCount; i++)
	{
		delete this->itemArr[i];
	}
	delete[] itemArr;
}

void Inventory::deleteItem(int index)
{
	if (this->itemArr[index]->getType() != clear) {

		this->itemArr[index]->setCount(this->itemArr[index]->getCount() - 1);

		//use stats...

		if (this->itemArr[index]->getCount() <= 0)
		{
			for (int i = index; i < this->numberOfItems - 1; i++)
			{
				this->itemArr[i] = this->itemArr[i + 1];
			}
			this->itemArr[numberOfItems] = new Item();

		}
	}
}

void Inventory::expand()
{
	this->allCount *= 2;

	Item** tempArr = new Item*[allCount];
	for (int i = 0; i < numberOfItems; i++)
	{
		tempArr[i] = new Item(*itemArr[i]);
	}

	for (int i = 0; i < numberOfItems; i++)
	{
		delete this->itemArr[i];
	}
	delete[] this->itemArr;

	this->init(this->numberOfItems);
}

int Inventory::getCount() { return numberOfItems; }

void Inventory::init(const int from)
{
	for (int i = from; i < allCount; i++)
	{
		this->itemArr[i] = new Item();
	}
}

void Inventory::createSlot()
{
	if (this->numberOfItems >= this->allCount)
	{
		expand();
	}
	this->itemArr[this->numberOfItems++] = new Item();
}

void Inventory::removeItem(int index)
{
	for (int i = 0; i < this->numberOfItems; i++)
	{
		if (i == index)this->itemArr[i] = new Item();
	}
}

void Inventory::addItem(const Item &item)
{
	Item* temp = new Item(item);
	bool b = false;
	for (int i = 0; i < this->numberOfItems; i++)
	{
		if (this->itemArr[i]->getName() == temp->getName())
		{
			this->itemArr[i]->setCount(this->itemArr[i]->getCount() + temp->getCount());
			b = false;
			i = this->numberOfItems;
		}
		else
		{
			b = true;
		}
	}


	for (int i = 0; i < this->numberOfItems && b; i++)
	{
		if (this->itemArr[i]->getType() == clear)
		{
			this->itemArr[i] = new Item(item);
			i = this->numberOfItems;
		}
	}
	delete temp;
}

Item* Inventory::getItem(int index)
{
	for (int i = 0; i < this->numberOfItems; i++)
	{
		if (i == index)return this->itemArr[i];
	}
}

void Inventory::teleportItem(int index, const Item &item)
{
	for (int i = 0; i < index; i++)
	{
		if (this->itemArr[i]->getType() == clear)
		{
			this->itemArr[i] = new Item(item);
			i = index;
		}
	}
}

void Inventory::setItem(int index, const Item &item)
{
	for (int i = 0; i < this->numberOfItems; i++)
	{
		if (i == index)this->itemArr[i] = new Item(item);
	}
}

void Inventory::findItem(Item* item)
{
	for (int i = 0; i < this->numberOfItems; i++)
	{
		if (this->itemArr[i]->getName() == item->getName()) this->itemArr[i] = item;
	}
}

void Inventory::checkEquiped()
{
	bool headB = false;
	bool bodyB = false;
	bool legsB = false;
	bool weaponB = false;

	for (int i = 0; i < this->numberOfItems; i++)
	{

		if (this->itemArr[i]->getType() == EqHead)
		{
			headB = true;
		}
		else if (this->itemArr[i]->getType() == EqBody)
		{
			bodyB = true;
		}
		else if (this->itemArr[i]->getType() == EqLegs)
		{
			legsB = true;
		}
		else if (this->itemArr[i]->getType() == EqWeapon)
		{
			weaponB = true;
		}
	}

	if (!headB)
	{
		head = new Item(EqHead);
	}
	if (!bodyB)
	{
		body = new Item(EqBody);
	}
	if (!legsB)
	{
		legs = new Item(EqLegs);
	}
	if (!weaponB)
	{
		weapon = new Item(EqWeapon);
	}

}