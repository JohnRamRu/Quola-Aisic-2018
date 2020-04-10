#include "UpgradeBlock.h"

using namespace std;


UpgradeBlock::UpgradeBlock()
{
	type[0] = 2;//2, 8, 13

	for (int i = 1; i < 18; i++)
	{
		type[i] = 0;//0
	}
	type[18] = 1;
	type[1] = 1;
	type[8] = 1;
	type[13] = 1;
}

int UpgradeBlock::getType(int index)
{
	return type[index];
}

void UpgradeBlock::setAndDraw(int x, int y, string ch)
{
	COORD position;
	HANDLE out_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	position.X = x;
	position.Y = y;
	SetConsoleCursorPosition(out_handle, position);
	printf("%s", ch.c_str());
}

void UpgradeBlock::setAndDraw(int x, int y, int ch)
{
	COORD position;
	HANDLE out_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	position.X = x;
	position.Y = y;
	SetConsoleCursorPosition(out_handle, position);
	printf("%c", (char)ch);
}

void UpgradeBlock::draw(Hero* hero)
{

	if (choice == "*" || type[18] == 2)drawStartCube(2, 8, "*", choice, type[18]);//18
	else
	{
		setAndDraw(2, 8, " ");   setAndDraw(2 + 1, 8, " ");   setAndDraw(2 + 2, 8, " ");   setAndDraw(2 + 3, 8, " ");   setAndDraw(2 + 4, 8, " ");
		setAndDraw(2, 8 + 1, " ");                                                                                  setAndDraw(2 + 4, 8 + 1, " ");
		setAndDraw(2, 8 + 2, " ");                            setAndDraw(2 + 2, 8 + 2, " ");                            setAndDraw(2 + 4, 8 + 2, " ");
		setAndDraw(2, 8 + 3, " ");                                                                                  setAndDraw(2 + 4, 8 + 3, " ");
		setAndDraw(2, 8 + 4, " "); setAndDraw(2 + 1, 8 + 4, " "); setAndDraw(2 + 2, 8 + 4, " "); setAndDraw(2 + 3, 8 + 4, " "); setAndDraw(2 + 4, 8 + 4, " ");
	}
	//DRAW START CUBE
	drawUpTree(4, 20, "Q", choice, type[1]);//1
	drawDownTree(24, 19, "S", choice, type[2]);//2 !
	drawUpTree(24, 13, "W", choice, type[3]);//3
	drawDownTree(44, 12, "E", choice, type[4]);//4
	drawUpTree(64, 13, "T", choice, type[5]);//5 !
	drawUpTree(44, 6, "R", choice, type[6]);//6
	drawDownTree(64, 5, "T", choice, type[5]);//5
	drawDownTree(84, 12, "Y", choice, type[7]);//7

											   //
	drawStartCube(0, 21, "", "!!!!", type[0]);
	drawStraightTree(4, 23, "A", choice, type[8]);//8
	drawStraightTree(24, 23, "S", choice, type[2]);//2
	drawStraightTree(44, 23, "D", choice, type[9]);//9
	drawStraightTree(64, 23, "F", choice, type[10]);//10
	drawStraightTree(84, 23, "G", choice, type[11]);//11
	drawEndTree(104, 23, "H", choice, type[12]);//12
												//
	drawDownTree(4, 26, "Z", choice, type[13]);//13
	drawDownTree(24, 33, "X", choice, type[14]);//14
	drawUpTree(44, 34, "C", choice, type[15]);//15
	drawUpTree(64, 27, "F", choice, type[10]);//10 !
	drawDownTree(64, 33, "V", choice, type[16]);//16
	drawUpTree(84, 34, "B", choice, type[17]);//17 !
											  //
	RPGUtils::setWriteCursor(0, 40);
	for (int i = 0; i < 120; i++)
	{
		printf("%c", (char)205);
	}
	RPGUtils::setWriteCursor(0, 41);

	//Write a para of ability
	int t = transf();
	if (hero->getType() == hStrength)
	{

	}
	else if (hero->getType() == hAgility)
	{

	}
	else if (hero->getType() == hIntelligence)
	{

	}
	switch (t)
	{
	case Q:
		block.name = "Basic in defence";
		block.setPara(agility, 5, 0);
		block.setPara(no, 0, 1);
		block.setPara(no, 0, 2);
		break;
	case W:
		block.name = "Basic knowelege in shield";
		block.setPara(strength, 2, 0);
		block.setPara(agility, 5, 1);
		block.setPara(no, 0, 2);
		break;
	case R:
		block.name = "Medium knowelege in shield";
		block.setPara(strength, 4, 0);
		block.setPara(agility, 3, 1);
		block.setPara(intelligence, -1, 2);
		break;
	case E:
		block.name = "Medium in defence";
		block.setPara(agility, 6, 0);
		block.setPara(intelligence, -1, 1);
		block.setPara(no, 0, 2);
		break;
	case T:
		block.name = "High in defence";
		block.setPara(strength, 6, 0);
		block.setPara(agility, 4, 1);
		block.setPara(intelligence, -3, 2);
		break;
	case Y:
		block.name = "Master of defence";
		block.setPara(strength, 9, 0);
		block.setPara(agility, 6, 1);
		block.setPara(intelligence, -3, 2);
		break;
	case A:
		block.name = "Basic of heavy sword";
		block.setPara(attack, 2, 0);
		block.setPara(agility, -1, 1);
		block.setPara(no, 0, 2);
		break;
	case S:
		block.name = "Medium of heavy sword";
		block.setPara(strength, 1, 0);
		block.setPara(agility, -2, 1);
		block.setPara(attack, 4, 2);
		break;
	case D:
		block.name = "Master of heavy sword";
		block.setPara(strength, 3, 0);
		block.setPara(agility, -4, 1);
		block.setPara(attack, 7, 2);
		break;
	case F:
		block.name = "Medium of two-sword";
		block.setPara(strength, 2, 0);
		block.setPara(agility, -2, 1);
		block.setPara(attack, 5, 2);
		break;
	case G:
		block.name = "Master of two-sword";
		block.setPara(strength, 2, 0);
		block.setPara(attack, 8, 1);
		block.setPara(no, 0, 2);
		break;
	case H:
		block.name = "Paladin";
		block.setPara(strength, 8, 0);
		block.setPara(agility, 6, 1);
		block.setPara(intelligence, 5, 2);
		break;
	case Z:
		block.name = "Basic of holy magic";
		block.setPara(intelligence, 2, 0);
		block.setPara(no, 0, 1);
		block.setPara(no, 0, 2);
		break;
	case X:
		block.name = "Medium of holy magic";
		block.setPara(intelligence, 4, 0);
		block.setPara(attack, -1, 1);
		block.setPara(no, 0, 2);
		break;
	case C:
		block.name = "Medium of two-handled weapon";
		block.setPara(strength, 2, 0);
		block.setPara(agility, -2, 1);
		block.setPara(attack, 3, 2);
		break;
	case V:
		block.name = "Master of holy magic";
		block.setPara(strength, 2, 0);
		block.setPara(intelligence, 6, 1);
		block.setPara(attack, -2, 2);
		break;
	case B:
		block.name = "Holy warrior";
		block.setPara(strength, 5, 0);
		block.setPara(intelligence, 10, 1);
		block.setPara(attack, -3, 2);
		break;
	case star:
		block.name = "Mythic armor";
		block.setPara(strength, 5, 0);
		block.setPara(agility, 8, 1);
		block.setPara(intelligence, 10, 2);
		break;
	default:
		block.name = "                              ";
		block.setPara(no, 0, 0);
		block.setPara(no, 0, 1);
		block.setPara(no, 0, 2);
		break;
	}
	string sIPlusic[3];
	string sPluses[3];
	for (int i = 0; i < 3; i++)
	{
		if (block.iPlusic[i] == 0)sIPlusic[i] = "          ";
		else if (block.iPlusic[i] > 0) sIPlusic[i] = "+" + to_string(block.iPlusic[i]);
		else if (block.iPlusic[i] < 0) sIPlusic[i] = to_string(block.iPlusic[i]);


		switch (block.plusic[i])
		{
		case 1://strength
			sPluses[i] = "Strength";
			break;
		case 2://agility
			sPluses[i] = "Agility";
			break;
		case 3://intelligence
			sPluses[i] = "Intelligence";
			break;
		case 6://attack
			sPluses[i] = "Attack";
			break;
		default://no
			sPluses[i] = "                                                           ";
			break;
		}
	}

	printf("Ability: %s                                       \n\n", block.name.c_str());
	printf("%s %s                            \n", sPluses[0].c_str(), sIPlusic[0].c_str());
	printf("%s %s                            \n", sPluses[1].c_str(), sIPlusic[1].c_str());
	printf("%s %s                            \n", sPluses[2].c_str(), sIPlusic[2].c_str());

	RPGUtils::setWriteCursor(0, 46);
	for (int i = 0; i < 120; i++)
	{
		printf("%c", (char)205);
	}
	RPGUtils::setWriteCursor(0, 48);
	printf("Click to letter to choose.      ~ - upgrade      Esc - exit");
}


void UpgradeBlock::print(Hero* hero)
{
	draw(hero);
}


void UpgradeBlock::drawStartCube(int x, int y, string key, string in, int type)
{
	if (type > 0)
	{
		if (key == this->choice)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);	
		}//RED
		if (type == 2)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		}//GREEN

		setAndDraw(x, y, 201);   setAndDraw(x + 1, y, 205);   setAndDraw(x + 2, y, 205);   setAndDraw(x + 3, y, 205);   setAndDraw(x + 4, y, 187);
		setAndDraw(x, y + 1, 186);                                                                                  setAndDraw(x + 4, y + 1, 186);
		setAndDraw(x, y + 2, 186);                            setAndDraw(x + 2, y + 2, key);                            setAndDraw(x + 4, y + 2, 186);
		setAndDraw(x, y + 3, 186);                                                                                  setAndDraw(x + 4, y + 3, 186);
		setAndDraw(x, y + 4, 200); setAndDraw(x + 1, y + 4, 205); setAndDraw(x + 2, y + 4, 205); setAndDraw(x + 3, y + 4, 205); setAndDraw(x + 4, y + 4, 188);
		
		//WHITE
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);//white
	}
}

void UpgradeBlock::drawUpTree(int x, int y, string key, string in, int type)
{
	if (type > 0)
	{
		setAndDraw(x + 1, y - 2, 201); setAndDraw(x + 2, y - 2, 205); setAndDraw(x + 3, y - 2, 205); setAndDraw(x + 4, y - 2, 205);
		setAndDraw(x + 5, y - 2, 205); setAndDraw(x + 6, y - 2, 205); setAndDraw(x + 7, y - 2, 205); setAndDraw(x + 8, y - 2, 205); setAndDraw(x + 9, y - 2, 205);
		setAndDraw(x + 10, y - 2, 205); setAndDraw(x + 11, y - 2, 205); setAndDraw(x + 12, y - 2, 205); setAndDraw(x + 13, y - 2, 205); setAndDraw(x + 14, y - 2, 205);
		setAndDraw(x + 15, y - 2, 205); drawStartCube(x + 16, y - 6, key, in, type);
		setAndDraw(x + 1, y - 1, 188);
		setAndDraw(x, y - 1, 201);
		setAndDraw(x, y, 186);
	}
}

void UpgradeBlock::drawDownTree(int x, int y, string key, string in, int type)
{
	if (type > 0)
	{
		setAndDraw(x + 1, y + 2, 200); setAndDraw(x + 2, y + 2, 205); setAndDraw(x + 3, y + 2, 205); setAndDraw(x + 4, y + 2, 205);
		setAndDraw(x + 5, y + 2, 205); setAndDraw(x + 6, y + 2, 205); setAndDraw(x + 7, y + 2, 205); setAndDraw(x + 8, y + 2, 205); setAndDraw(x + 9, y + 2, 205);
		setAndDraw(x + 10, y + 2, 205); setAndDraw(x + 11, y + 2, 205); setAndDraw(x + 12, y + 2, 205); setAndDraw(x + 13, y + 2, 205); setAndDraw(x + 14, y + 2, 205);
		setAndDraw(x + 15, y + 2, 205); drawStartCube(x + 16, y + 2, key, in, type);
		setAndDraw(x + 1, y + 1, 187);
		setAndDraw(x, y + 1, 200);
		setAndDraw(x, y, 186);
	}
}

void UpgradeBlock::drawStraightTree(int x, int y, string key, string in, int type)
{
	if (type > 0)
	{
		setAndDraw(x + 1, y, 205); setAndDraw(x + 2, y, 205); setAndDraw(x + 3, y, 205); setAndDraw(x + 4, y, 205);
		setAndDraw(x + 5, y, 205); setAndDraw(x + 6, y, 205); setAndDraw(x + 7, y, 205); setAndDraw(x + 8, y, 205); setAndDraw(x + 9, y, 205);
		setAndDraw(x + 10, y, 205); setAndDraw(x + 11, y, 205); setAndDraw(x + 12, y, 205); setAndDraw(x + 13, y, 205); setAndDraw(x + 14, y, 205);
		setAndDraw(x + 15, y, 205); drawStartCube(x + 16, y - 2, key, in, type);
	}
}

void UpgradeBlock::drawEndTree(int x, int y, string key, string in, int type)
{
	if (type > 0)
	{
		setAndDraw(x, y - 4, 186);

		setAndDraw(x + 1, y - 3, 187);
		setAndDraw(x, y - 3, 200);
		setAndDraw(x + 2, y - 2, 187);
		setAndDraw(x + 1, y - 2, 200);

		setAndDraw(x + 2, y - 1, 186);

		setAndDraw(x + 1, y, 205); setAndDraw(x + 2, y, 206); setAndDraw(x + 3, y, 205); setAndDraw(x + 4, y, 205);
		setAndDraw(x + 5, y, 205); setAndDraw(x + 6, y, 205); setAndDraw(x + 7, y, 205); setAndDraw(x + 8, y, 205); setAndDraw(x + 9, y, 205);
		setAndDraw(x + 10, y, 205); drawStartCube(x + 11, y - 2, key, in, type);

		setAndDraw(x, y + 4, 186);

		setAndDraw(x + 1, y + 3, 188);
		setAndDraw(x, y + 3, 201);
		setAndDraw(x + 2, y + 2, 188);
		setAndDraw(x + 1, y + 2, 201);

		setAndDraw(x + 2, y + 1, 186);
	}
}

void UpgradeBlock::setChoice(string choice) { this->choice = choice; }

string UpgradeBlock::getChoice() { return choice; }

int UpgradeBlock::transf()
{
	int t = Q;
	if (choice == "Q")t = Q;
	else if (choice == "S")t = S;
	else if (choice == "W")t = W;
	else if (choice == "E")t = E;
	else if (choice == "T")t = T;
	else if (choice == "R")t = R;
	else if (choice == "Y")t = Y;
	else if (choice == "A")t = A;
	else if (choice == "D")t = D;
	else if (choice == "F")t = F;
	else if (choice == "G")t = G;
	else if (choice == "H")t = H;
	else if (choice == "Z")t = Z;
	else if (choice == "X")t = X;
	else if (choice == "C")t = C;
	else if (choice == "V")t = V;
	else if (choice == "B")t = B;
	else if (choice == "*")t = star;

	return t;
}

void UpgradeBlock::setOpen(Hero* hero)
{
	int t = transf();

	switch (t)
	{
	case Q:
		type[Q] = 2;
		if (type[S] < 2)type[S] = 1;
		if (type[W] < 2)type[W] = 1;
		break;
	case W:
		type[W] = 2;
		if (type[R] < 2)type[R] = 1;
		if (type[E] < 2)type[E] = 1;
		break;
	case R:
		type[R] = 2;
		if (type[T] < 2)type[T] = 1;
		break;
	case E:
		type[E] = 2;
		if (type[T] < 2)type[T] = 1;
		break;
	case T:
		type[T] = 2;
		if (type[Y] < 2)type[Y] = 1;
		break;
	case Y:
		type[Y] = 2;
		if (type[H] < 2)type[H] = 1;
		break;
	case A:
		type[A] = 2;
		if (type[S] < 2)type[S] = 1;
		break;
	case S:
		type[S] = 2;
		if (type[D] < 2)type[D] = 1;
		break;
	case D:
		type[D] = 2;
		if (type[F] < 2)type[F] = 1;
		break;
	case F:
		type[F] = 2;
		if (type[G] < 2)type[G] = 1;
		break;
	case G:
		type[G] = 2;
		if (type[H] < 2)type[H] = 1;
		break;
	case H:
		type[H] = 2;
		break;
	case Z:
		type[Z] = 2;
		if (type[X] < 2)type[X] = 1;
		break;
	case X:
		type[X] = 2;
		if (type[C] < 2)type[C] = 1;
		break;
	case C:
		type[C] = 2;
		if (type[F] < 2)type[F] = 1;
		if (type[V] < 2)type[V] = 1;
		break;
	case V:
		type[V] = 2;
		if (type[B] < 2)type[B] = 1;
		break;
	case B:
		type[B] = 2;
		if (type[H] < 2)type[H] = 1;
		break;
	case star:
		type[star] = 2;
		break;
	default:
		break;
	}

	for (int i = 0; i < 3; i++)
	{
		switch (block.plusic[i])
		{
		case 1://strength
			hero->setStrength(hero->getStrength() + block.iPlusic[i]);
			break;
		case 2://agility
			hero->setAgility(hero->getAgility() + block.iPlusic[i]);
			break;
		case 3://intelligence
			hero->setIntelligence(hero->getIntelligence() + block.iPlusic[i]);
			break;
		case 6://attack
			hero->setAtk(hero->getAtk() + block.iPlusic[i]);
			break;
		default://no
			break;
		}
		hero->updateStats();
	}

}

void block::setPara(Plus plusic, int iPlusic, int index)
{
	if (index < 0)index = 0;
	if (index > 2)index = 2;
	this->plusic[index] = plusic;
	this->iPlusic[index] = iPlusic;
}
