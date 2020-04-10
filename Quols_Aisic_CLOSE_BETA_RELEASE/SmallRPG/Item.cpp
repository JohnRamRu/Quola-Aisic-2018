#include "Item.h"



Item::Item()
{
	this->name = "";//EMPTY
	this->buyValue = 0;
	this->sellValue = 0;
	this->type = clear;
	this->biograthy = "";
	this->count = 0;
	this->pluses = no;
	this->iPluses = 0;
}

Item::Item(Type type)
{
	this->name = "No";//EMPTY
	this->buyValue = 0;
	this->sellValue = 0;
	this->type = type;
	this->biograthy = "No";
	this->count = 1;
	this->pluses = no;
	this->iPluses = 0;
}

Item::Item(std::string name, int count, int buyValue, int sellValue,
	Type type, Plus pluses, int iPluses, std::string bio)
{
	this->name = name;
	this->buyValue = buyValue;
	this->sellValue = sellValue;
	this->type = type;
	this->biograthy = bio;
	this->count = count;
	this->pluses = pluses;
	this->iPluses = iPluses;

}

Plus Item::getPluses() { return pluses; }

int Item::getIPluses() { return iPluses; }

int Item::getCount() { return count; }

void Item::setCount(int count) { this->count = count; }

std::string Item::getName() { return name; }

int Item::getBuyValue() { return buyValue; }

int Item::getSellValue() { return sellValue; }

int Item::getType() { return type; }

void Item::setType(Type type) { this->type = type; }

std::string Item::getBio() { return biograthy; }

Item::~Item()
{
}

