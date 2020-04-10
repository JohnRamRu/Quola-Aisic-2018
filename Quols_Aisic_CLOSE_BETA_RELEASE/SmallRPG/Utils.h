#pragma once
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <windows.h>
#include "Inventory.h"

enum DropType { NONE = 0, HP_POTION, MP_POTION };
enum DropGrade { NOT = 0, SMALL, MEDIUM, LARGE };

enum EnemyType
{
	WispT = 0,
	AgrostiniT,
	BearT,
	CockatriceT,
	DragonT,
	EntT,
	FerralT,
	GoblinT,
	HydraT,
	SirenT, //I
	JarryT,
	SkeletonT, //K
	LichT,
	MermaidT,
	NefrenT,
	OgreT,
	ParnasusT,
	QreT,
	RoccoT,
	SlimeT,
	TOWNTYPE,
	UgorT,
	VampireT,
	WolfT,
	XeonidT,
	CyclopT, //Y
	ZombieT
};

enum Colors
{
	Black = 0,
	Grey = FOREGROUND_INTENSITY,
	LightGrey = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
	White = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	Blue = FOREGROUND_BLUE,
	Green = FOREGROUND_GREEN,
	Cyan = FOREGROUND_GREEN | FOREGROUND_BLUE,
	Red = FOREGROUND_RED,
	Purple = FOREGROUND_RED | FOREGROUND_BLUE,
	LightBlue = FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	LightGreen = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	LightCyan = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	LightRed = FOREGROUND_RED | FOREGROUND_INTENSITY,
	LightPurple = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY,
	Orange = FOREGROUND_RED | FOREGROUND_GREEN,
	Yellow = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
};

struct Drop
{
	int experience;
	int gold;

	void create(int exp, int gold)
	{
		this->experience = exp;
		this->gold = gold;
	}

	Item ListOfItems[13] = {
		Item(),//0                        //ID
		Item("Small Heal Potion", 1, 50, 20, potion, hp, 45, "Potion with healing power!"), //1
		Item("Medium Heal Potion", 1, 110, 35, potion, hp, 110, "Potion with healing power!"),//2
		Item("Big Heal Potion", 1, 250, 45, potion, hp, 260, "Potion with healing power!"),//3
		Item("Small Mana Potion", 1, 60, 25, potion, mp, 45, "Potion with magic power!"), //4
		Item("Medium Mana Potion", 1, 150, 40, potion, mp, 110, "Potion with magic power!"),//5
		Item("Big Mana Potion", 1, 310, 55, potion, mp, 260, "Potion with magic power!"),//6
		Item("Wooden Sword", 1, 50, 20, weapon, attack, 2, "Basic sword."),//7
		Item("Steel Sword", 1, 150, 60, weapon, attack, 5, "Steel for masters."),//8
		Item("Leather Head", 1, 30, 10, head, intelligence, 3, "Simple head."),//9
		Item("Leather Body", 1, 70, 35, body, strength, 8, "Simple body."),//10
		Item("Leather Legs", 1, 55, 25, legs, agility, 4, "Simple legs."),//11
		Item("Leather Legs", 1, 55, 25, legs, agility, 4, "Simple legs.")//12
	};

	int getDExp();
	int getDGold();
};

class RPGUtils
{
public:
	static int getRandom(int from, int to);
	static double getRandom(double from, double to);
	static void clearConsole();
	static void setAndDraw(int x, int y, string ch);
	static void setAndDraw(int x, int y, char ch);
	static void setColor(Colors color, Colors backColor);
	static void setColor(Colors color = White);
	static void setWriteCursor(int x, int y)
	{
		COORD position;
		HANDLE out_handle = GetStdHandle(STD_OUTPUT_HANDLE);
		position.X = x;
		position.Y = y;
		SetConsoleCursorPosition(out_handle, position);
	}
};
