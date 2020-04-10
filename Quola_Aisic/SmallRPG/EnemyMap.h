#pragma once
#include "Monsters.h"
#include "cstdlib"
#include "Map.h"
#include <vector>
#include "time.h"
#include <iostream>
using namespace std;



class EnemyMap
{
private:
	int count = 0;
	int policy = 0;
	vector <Monster*> monster;
	//Monster* monster;
	vector <int> monsterX;
	vector <int> monsterY;
	vector <char> deletedChar;
public:
	EnemyMap(int monsters)
	{	
		count = monsters;

		monster.resize(monsters);
		monsterX.resize(monsters);
		monsterY.resize(monsters);
		deletedChar.resize(monsters);

		policy = 0;
	}

	void setEnemyOnMap(int xMin, int yMin, int xMax, int yMax, int index, Map& map)
	{	
		int rdY = 0;
		int rdX = 0;
		//int type;

		bool key;

		key = false;

			while (!key)
			{
				rdX = RPGUtils::getRandom(xMin, (xMax - xMin));

				rdY = RPGUtils::getRandom(yMin, (yMax - yMin));

				switch (monster[index]->getType())
				{
				case AgrostiniT://Агростини
					if (map.m[rdX][rdY] == (char)178)
					{
						monsterX[index] = rdX;
						monsterY[index] = rdY;

						deletedChar[index] = map.m[rdX][rdY];
						map.m[rdX][rdY] = 'A';
						key = true;
					}
					break;
				case BearT://Медведь
					if (map.m[rdX][rdY] == (char)178 || map.m[rdX][rdY] == (char)177)
					{
						monsterX[index] = rdX;
						monsterY[index] = rdY;

						deletedChar[index] = map.m[rdX][monsterY[index]];
						map.m[rdX][monsterY[index]] = 'B';
						key = true;
					}
					break;
				case CockatriceT://Василиск
					if (map.m[rdX][rdY] == (char)178 || map.m[rdX][rdY] == (char)177 || map.m[rdX][rdY] == '*')
					{
						monsterX[index] = rdX;
						monsterY[index] = rdY;

						deletedChar[index] = map.m[rdX][monsterY[index]];
						map.m[rdX][monsterY[index]] = 'C';
						key = true;
					}
					break;
				case DragonT://Дракон
					if (map.m[rdX][rdY] == (char)178)
					{
						monsterX[index] = rdX;
						monsterY[index] = rdY;

						deletedChar[index] = map.m[rdX][monsterY[index]];
						map.m[rdX][monsterY[index]] = 'D';
						key = true;
					}
					break;
				case EntT://Ент
					if (map.m[rdX][rdY] == (char)178)
					{
						monsterX[index] = rdX;
						monsterY[index] = rdY;

						deletedChar[index] = map.m[rdX][monsterY[index]];
						map.m[rdX][monsterY[index]] = 'E';
						key = true;
					}
					break;
				case FerralT://Феррал
					if (map.m[rdX][rdY] == (char)178)
					{
						monsterX[index] = rdX;
						monsterY[index] = rdY;

						deletedChar[index] = map.m[rdX][monsterY[index]];
						map.m[rdX][monsterY[index]] = 'F';
						key = true;
					}
					break;
				case GoblinT://Гоблин
					if (map.m[rdX][rdY] == (char)178 || map.m[rdX][rdY] == (char)177)
					{
						monsterX[index] = rdX;
						monsterY[index] = rdY;

						deletedChar[index] = map.m[rdX][monsterY[index]];
						map.m[rdX][monsterY[index]] = 'G';
						key = true;
					}
					break;
				case HydraT://Гидра
					if (map.m[rdX][rdY] == (char)178)
					{
						monsterX[index] = rdX;
						monsterY[index] = rdY;

						deletedChar[index] = map.m[rdX][monsterY[index]];
						map.m[rdX][monsterY[index]] = 'H';
						key = true;
					}
					break;
				case SirenT: //I  Сирена
					if (map.m[rdX][rdY] == (char)178 || map.m[rdX][rdY] == (char)177 || map.m[rdX][rdY] == '~')
					{
						monsterX[index] = rdX;
						monsterY[index] = rdY;

						deletedChar[index] = map.m[rdX][monsterY[index]];
						map.m[rdX][monsterY[index]] = 'I';
						key = true;
					}
					break;
				case JarryT://Джерри
					if (map.m[rdX][rdY] == (char)177)
					{
						monsterX[index] = rdX;
						monsterY[index] = rdY;

						deletedChar[index] = map.m[rdX][monsterY[index]];
						map.m[rdX][monsterY[index]] = 'J';
						key = true;
					}
					break;
				case SkeletonT: //K  Скелет
					if (map.m[rdX][rdY] == (char)178 || map.m[rdX][rdY] == (char)177 || map.m[rdX][rdY] == '*')
					{
						monsterX[index] = rdX;
						monsterY[index] = rdY;

						deletedChar[index] = map.m[rdX][monsterY[index]];
						map.m[rdX][monsterY[index]] = 'K';
						key = true;
					}
					break;
				case LichT://Лич
					if (map.m[rdX][rdY] == (char)178)
					{
						monsterX[index] = rdX;
						monsterY[index] = rdY;

						deletedChar[index] = map.m[rdX][monsterY[index]];
						map.m[rdX][monsterY[index]] = 'L';
						key = true;
					}
					break;
				case MermaidT://РУСалка
					if (map.m[rdX][rdY] == '~')
					{
						monsterX[index] = rdX;
						monsterY[index] = rdY;

						deletedChar[index] = map.m[rdX][monsterY[index]];
						map.m[rdX][monsterY[index]] = 'M';
						key = true;
					}
					break;
				case NefrenT://Нефрен
					if (map.m[rdX][rdY] == (char)178)
					{
						monsterX[index] = rdX;
						monsterY[index] = rdY;

						deletedChar[index] = map.m[rdX][monsterY[index]];
						map.m[rdX][monsterY[index]] = 'N';
						key = true;
					}
					break;
				case OgreT://Огр
					if (map.m[rdX][rdY] == (char)178 || map.m[rdX][rdY] == '*')
					{
						monsterX[index] = rdX;
						monsterY[index] = rdY;

						deletedChar[index] = map.m[rdX][monsterY[index]];
						map.m[rdX][monsterY[index]] = 'O';
						key = true;
					}
					break;
				case ParnasusT://Парнасус
					if (map.m[rdX][rdY] == (char)178 || map.m[rdX][rdY] == (char)177)
					{
						monsterX[index] = rdX;
						monsterY[index] = rdY;

						deletedChar[index] = map.m[rdX][monsterY[index]];
						map.m[rdX][monsterY[index]] = 'P';
						key = true;
					}
					break;
				case QreT://Кьюр
					if (map.m[rdX][rdY] == (char)177)
					{
						monsterX[index] = rdX;
						monsterY[index] = rdY;

						deletedChar[index] = map.m[rdX][monsterY[index]];
						map.m[rdX][monsterY[index]] = 'Q';
						key = true;
					}
					break;
				case RoccoT://Рокко
					if (map.m[rdX][rdY] == '~')
					{
						monsterX[index] = rdX;
						monsterY[index] = rdY;

						deletedChar[index] = map.m[rdX][monsterY[index]];
						map.m[rdX][monsterY[index]] = 'R';
						key = true;
					}
					break;
				case SlimeT://Слайм
					if (map.m[rdX][rdY] == '*')
					{
						monsterX[index] = rdX;
						monsterY[index] = rdY;

						deletedChar[index] = map.m[rdX][monsterY[index]];
						map.m[rdX][monsterY[index]] = 'S';
						key = true;
					}
					break;
				case UgorT://Угор
					if (map.m[rdX][rdY] == (char)177)
					{
						monsterX[index] = rdX;
						monsterY[index] = rdY;

						deletedChar[index] = map.m[rdX][monsterY[index]];
						map.m[rdX][monsterY[index]] = 'U';
						key = true;
					}
					break;
				case VampireT://Вампир
					if (map.m[rdX][rdY] == (char)178)
					{
						monsterX[index] = rdX;
						monsterY[index] = rdY;

						deletedChar[index] = map.m[rdX][monsterY[index]];
						map.m[rdX][monsterY[index]] = 'V';
						key = true;
					}
					break;
				case WolfT://Волк
					if (map.m[rdX][rdY] == (char)178 || map.m[rdX][rdY] == (char)177)
					{
						monsterX[index] = rdX;
						monsterY[index] = rdY;

						deletedChar[index] = map.m[rdX][monsterY[index]];
						map.m[rdX][monsterY[index]] = 'W';
						key = true;
					}
					break;
				case XeonidT://Ксеонид
					if (map.m[rdX][rdY] == (char)178 || map.m[rdX][rdY] == (char)177 || map.m[rdX][rdY] == '~')
					{
						monsterX[index] = rdX;
						monsterY[index] = rdY;

						deletedChar[index] = map.m[rdX][monsterY[index]];
						map.m[rdX][monsterY[index]] = 'X';
						key = true;
					}
					break;
				case CyclopT: //Y  Циклоп
					if (map.m[rdX][rdY] == (char)178)
					{
						monsterX[index] = rdX;
						monsterY[index] = rdY;

						deletedChar[index] = map.m[rdX][monsterY[index]];
						map.m[rdX][monsterY[index]] = 'Y';
						key = true;
					}
					break;
				case ZombieT://Зомби
					if (map.m[rdX][rdY] == (char)178 || map.m[rdX][rdY] == (char)177 || map.m[rdX][rdY] == '*')
					{
						monsterX[index] = rdX;
						monsterY[index] = rdY;

						deletedChar[index] = map.m[rdX][monsterY[index]];
						map.m[rdX][monsterY[index]] = 'Z';
						key = true;
					}
					break;

				default:
					key = true;
					break;
				}
				rdX = 0;
				rdY = 0;
			}
	}

	void setEnemies(int xMin, int yMin, int xMax, int yMax, Map& map)
	{
		policy = 1;
		int monsterRandom = 0;
		bool key = false;
		for (int i = 0; i < count; i++)
		{
			monsterRandom = RPGUtils::getRandom(0, 100);

			if (map.biomMapI[xMin / 89][yMin / 49] == 0)
			{
				if (monsterRandom <= 10)
				{
					monster[i] = new Rocco();
				}
				else if (monsterRandom > 10 && monsterRandom <= 30)
				{
					monster[i] = new Xeonid();
				}
				else if (monsterRandom > 30 && monsterRandom <= 65)
				{
					monster[i] = new Mermaid();
				}
				else if (monsterRandom > 65 && monsterRandom <= 100)
				{
					monster[i] = new Siren();
				}
			}
			else if (map.biomMapI[xMin / 89][yMin / 49] == 1)
			{
				if (monsterRandom <= 10)
				{
					monster[i] = new Skeleton();
				}
				else if (monsterRandom > 10 && monsterRandom <= 25)
				{
					monster[i] = new Zombie();
				}
				else if (monsterRandom > 25 && monsterRandom <= 40)
				{
					monster[i] = new Goblin();
				}
				else if (monsterRandom > 40 && monsterRandom <= 65)
				{
					monster[i] = new Parnasus();
				}
				else if (monsterRandom > 65 && monsterRandom <= 100)
				{
					monster[i] = new Xeonid();
				}
			}
			else if (map.biomMapI[xMin / 89][yMin / 49] == 2)
			{
				if (monsterRandom <= 8)
				{
					monster[i] = new Parnasus();
				}
				else if (monsterRandom > 8 && monsterRandom <= 18)
				{
					monster[i] = new Skeleton();
				}
				else if (monsterRandom > 18 && monsterRandom <= 30)
				{
					monster[i] = new Goblin();
				}
				else if (monsterRandom > 30 && monsterRandom <= 50)
				{
					monster[i] = new Jarry();
				}
				else if (monsterRandom > 50 && monsterRandom <= 70)
				{
					monster[i] = new Ugor();
				}
				else if (monsterRandom > 70 && monsterRandom <= 100)
				{
					monster[i] = new Qre();
				}
			}
			else if (map.biomMapI[xMin / 89][yMin / 49] == 3)
			{
				if (monsterRandom <= 8)
				{
					monster[i] = new Cockatrice();
				}
				else if (monsterRandom > 8 && monsterRandom <= 20)
				{
					monster[i] = new Ogre();
				}
				else if (monsterRandom > 20 && monsterRandom <= 42)
				{
					monster[i] = new Skeleton();
				}
				else if (monsterRandom > 42 && monsterRandom <= 65)
				{
					monster[i] = new Slime();
				}
				else if (monsterRandom > 65 && monsterRandom <= 100)
				{
					monster[i] = new Zombie();
				}
			}
			else if (map.biomMapI[xMin / 89][yMin / 49] == 4)
			{
				if (monsterRandom <= 5)
				{
					monster[i] = new Ent();
				}
				else if (monsterRandom > 5 && monsterRandom <= 18)
				{
					monster[i] = new Goblin();
				}
				else if (monsterRandom > 18 && monsterRandom <= 33)
				{
					monster[i] = new Zombie();
				}
				else if (monsterRandom > 33 && monsterRandom <= 48)
				{
					monster[i] = new Skeleton();
				}
				else if (monsterRandom > 48 && monsterRandom <= 63)
				{
					monster[i] = new Agrostini();
				}
				else if (monsterRandom > 63 && monsterRandom <= 80)
				{
					monster[i] = new Vampire();
				}
				else if (monsterRandom > 80 && monsterRandom <= 100)
				{
					monster[i] = new Wolf();
				}
			}
			else if (map.biomMapI[xMin / 89][yMin / 49] == 5)
			{
				if (monsterRandom <= 5)
				{
					monster[i] = new Nefren();
				}
				else if (monsterRandom > 5 && monsterRandom <= 15)
				{
					monster[i] = new Bear();
				}
				else if (monsterRandom > 15 && monsterRandom <= 25)
				{
					monster[i] = new Ferral();
				}
				else if (monsterRandom > 25 && monsterRandom <= 40)
				{
					monster[i] = new Skeleton();
				}
				else if (monsterRandom > 40 && monsterRandom <= 55)
				{
					monster[i] = new Zombie();
				}
				else if (monsterRandom > 55 && monsterRandom <= 75)
				{
					monster[i] = new Wolf();
				}
				else if (monsterRandom > 75 && monsterRandom <= 100)
				{
					monster[i] = new Goblin();
				}
			}
			else if (map.biomMapI[xMin / 89][yMin / 49] == 6)
			{
				if (monsterRandom <= 5)
				{
					monster[i] = new Lich();
				}
				else if (monsterRandom > 5 && monsterRandom <= 10)
				{
					monster[i] = new Dragon();
				}
				else if (monsterRandom > 10 && monsterRandom <= 19)
				{
					monster[i] = new Skeleton();
				}
				else if (monsterRandom > 19 && monsterRandom <= 31)
				{
					monster[i] = new Hydra();
				}
				else if (monsterRandom > 31 && monsterRandom <= 44)
				{
					monster[i] = new Goblin();
				}
				else if (monsterRandom > 44 && monsterRandom <= 59)
				{
					monster[i] = new Ferral();
				}
				else if (monsterRandom > 59 && monsterRandom <= 77)
				{
					monster[i] = new Cyclop();
				}
				else if (monsterRandom > 77 && monsterRandom <= 100)
				{
					monster[i] = new Nefren();
				}
			}
			else
			{
				count = 0;
			}

			if(count > 0) setEnemyOnMap(xMin, yMin, xMax, yMax, i, map);
		}
	}

	void deleteMonster(int index, Map& map)
	{
		map.m[monsterX[index]][monsterY[index]] = deletedChar[index];

		delete monster[index];
		monster.erase(monster.begin() + index);
		monsterX.erase(monsterX.begin() + index);
		monsterY.erase(monsterY.begin() + index);
		deletedChar.erase(deletedChar.begin() + index);

		count -=1;
	}

	int getXOfMonster(int index)
	{
		return monsterX[index];
	}

	int getYOfMonster(int index)
	{
		return monsterY[index];
	}
	Monster* getMonster(int index)
	{
		return monster[index];
	}
	
	void deleteMonsters(Map& map)
	{	
		policy = 0;

		for (int i = 0; i < count; i++)
		{
			map.m[monsterX[i]][monsterY[i]] = deletedChar[i];
			
			delete monster[i];
		} 
		monster.clear();
		monsterX.clear();
		monsterY.clear();
		deletedChar.clear();
		count = 0;
	}

	int getPolicy()
	{
		return policy;
	}
	int getCount()
	{
		return count;
	}
	void setCount(int count)
	{
		this->count = count;
	}
};

