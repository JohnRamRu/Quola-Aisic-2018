#pragma once
#include "hero.h"
#include "Item.h"
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
using namespace std;

enum upTypes { Q = 1, S, W, E, T, R, Y, A, D, F, G, H, Z, X, C, V, B, star };

struct block
{
	string name = " ";
	Plus plusic[3] = {no, no, no};//1, 2, 3, 6
	int iPlusic[3] = {0, 0, 0};
	void setPara(Plus plusic, int iPlusic, int index);
};

class UpgradeBlock
{
protected:
	block block;
	int type[19];
	string choice = "Q";

public:
	UpgradeBlock();

	int getType(int index);

	void setAndDraw(int x, int y, string ch);

	void setAndDraw(int x, int y, int ch);

	void draw(Hero* hero);

	void print(Hero* hero);

	void drawStartCube(int x, int y, string key, string in, int type);

	void drawUpTree(int x, int y, string key, string in, int type);

	void drawDownTree(int x, int y, string key, string in, int type);

	void drawStraightTree(int x, int y, string key, string in, int type);

	void drawEndTree(int x, int y, string key, string in, int type);

	void setChoice(string choice);

	string getChoice();

	int transf();

	void setOpen(Hero* hero);
};


