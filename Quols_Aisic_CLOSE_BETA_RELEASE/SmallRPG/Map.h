#pragma once
#include "hero.h"
#include "monster.h"
#include "Utils.h"
#include "Inventory.h"
#include "PerlinNoise.h"


const int W_ = 49 * 16;         // высота рабочего пол€  89*16
const int H_ = 89 * 16;         // ширина рабочего пол€   49*16
const int WALL = -1;         // непроходима€ €чейка
const int BLANK = -2;         // свободна€ непомеченна€ €чейка

const int _height = 49;//50//45
const int _width = 89;//119//29

/*int playerX = 0;
int playerY = 0;*/

//int px[W * H], py[W * H];      // координаты €чеек, вход€щих в путь
//int len;                       // длина пути
//int grid[H][W];                // рабочее поле
//char chGrid[H][W];

class WaveRoad
{
public:
	int px[W_ * H_], py[W_ * H_];
	int len;
	int radi = 0;
	int grid[H_][W_];


	WaveRoad(char m[1424][784], bool radiant)
	{
		//ofstream file;
		//file.open("Road.txt", ios_base::app);

		if (!radiant) radi = 89 * 8;

		for (int i = 0; i < W_; i++)
		{
			for (int j = radi; j < H_ + radi; j++)
			{
				if (m[i][j] == '^' || m[i][j] == '~' || m[i][j] == '*') // || m[j][i] == '~' || m[j][i] == '*'
				{

					grid[j - radi][i] = WALL;
				}
				else
				{
					//printf("i ");
					grid[j - radi][i] = BLANK;
				}
				//file << grid[j][i] << " ";
			  // grid[j-radi][i] = BLANK;
			}
			//file << endl;
		}
		//file.close();
	}

	void reloadMap(char m[1424][784], bool radiant)
	{
		if (!radiant) radi = 89 * 8;

		for (int i = 0; i < W_; i++)
		{
			for (int j = radi; j < H_ + radi; j++)
			{
				if (m[i][j] == '^' || m[i][j] == '~' || m[i][j] == '*') // || m[j][i] == '~' || m[j][i] == '*'
				{

					grid[j - radi][i] = WALL;
				}
				else
				{

					grid[j - radi][i] = BLANK;
				}
				//grid[j-radi][i] = BLANK;
			}
		}
	}

	bool lee(int ax, int ay, int bx, int by)   // поиск пути из €чейки (ax, ay) в €чейку (bx, by)
	{
		int dx[4] = { 1, 0, -1, 0 };   // смещени€, соответствующие сосед€м €чейки
		int dy[4] = { 0, 1, 0, -1 };   // справа, снизу, слева и сверху
		int d, x, y, k;
		bool stop;

		if (grid[ay][ax] == WALL || grid[by][bx] == WALL) return false;  // €чейка (ax, ay) или (bx, by) - стена

		// распространение волны
		d = 0;
		grid[ay][ax] = 0;            // стартова€ €чейка помечена 0
		do {
			stop = true;               // предполагаем, что все свободные клетки уже помечены
			for (y = 0; y < H_; ++y)
				for (x = 0; x < W_; ++x)
					if (grid[y][x] == d)                         // €чейка (x, y) помечена числом d
					{
						for (k = 0; k < 4; ++k)                    // проходим по всем непомеченным сосед€м
						{
							int iy = y + dy[k], ix = x + dx[k];
							if (iy >= 0 && iy < H_ && ix >= 0 && ix < W_ &&
								grid[iy][ix] == BLANK)
							{
								stop = false;              // найдены непомеченные клетки
								grid[iy][ix] = d + 1;      // распростран€ем волну
							}
						}
					}
			d++;
		} while (!stop && grid[by][bx] == BLANK);

		//printf("%d", d);

		if (grid[by][bx] == BLANK) return false;  // путь не найден

		// восстановление пути
		len = grid[by][bx];            // длина кратчайшего пути из (ax, ay) в (bx, by)
		x = bx;
		y = by;

		d = len;

		px[d] = x;
		py[d] = y;

		while (d > 0)
		{
			// записываем €чейку (x, y) в путь
			d--;
			for (int _k = 0; _k < 4; _k++)
			{
				int iy = y + dy[_k], ix = x + dx[_k];

				if (iy >= 0 && iy < H_ && ix >= 0 && ix < W_ && grid[iy][ix] == d)//
				{
					//std::cout << ix << ", " << iy << "   " << grid[ix][iy] << "=" << d << std::endl << std::endl;
					x = x + dx[_k];
					y = y + dy[_k];
					px[d] = x;
					py[d] = y;           // переходим в €чейку, котора€ на 1 ближе к старту
					//std::cout << ix << ", " << iy << "   " << grid[ix][iy] << "=" << d << std::endl;
					break;
				}

			}

			//std::cout << d << " ";
		}
		px[0] = ax;
		py[0] = ay;                    // теперь px[0..len] и py[0..len] - координаты €чеек пути
		return true;
	}
};


class Biom
{
public:
	double water, sand, swamp, ground, kliff, hiKliff;
	bool err = false;
	Biom(double water, double sand, double ground, double swamp, double kliff, double hiKliff, bool err = false)
	{
		this->water = water;
		this->sand = sand;
		this->swamp = swamp;
		this->ground = ground;
		this->kliff = kliff;
		this->hiKliff = hiKliff;
		this->err = err;
	}
};


class Map
{
public://PRIVATE or PROTECTED
	const int stolb = 89 * 16, strok = 49 * 16;
	char m[89 * 16][49 * 16];
	Biom* biomeMap[16][16];
	int biomMapI[16][16];

	int townsX[100];
	int townsY[100];
	int dTownsX[100];
	int dTownsY[100];

	bool day = true;


	//const int dir=8; // number of possible directions to go at any position

public:
	Map()
	{
		for (int i = 0; i < strok; i++)
		{
			for (int j = 0; j < stolb; j++)
			{
				m[j][i] = ' ';
			}
		}

	}

	void doBiomeMap(unsigned int seed)
	{
		float yoff = 0;
		float xoff = 0;
		PerlinNoise pn(seed);

		for (int i = 49 * 16; i < 49 * 16 + 16; ++i) {     // y
			double y = (double)yoff / ((double)_height);// ((double) _height)

			for (int j = 89 * 16; j < 89 * 16 + 16; ++j) {  // x
				double x = (double)xoff / ((double)_width);// ((double) _width)
				double n = pn.noise(15 * x, 15 * y, 0.8);//0.8//2.3  pn.noise(3.88 * x, 3.88 * y, 0.8)//15

				// Watter (or a Lakes)
				if (n <= 0.4) {

					biomeMap[j - 89 * 16][i - 49 * 16] = new Biom(0.48, 0.50, 1, 1, 1, 1);
					biomMapI[j - 89 * 16][i - 49 * 16] = 0;//0
					/*
					water = 0.4;
					sand = 0.48;
					ground = 0.8;
					swamp = 1;
					kliff = 2;//
					hiKliff = 2;//
					*/
					//biomeMap[j-89*16][i-49*16] = '~';
					/*setColor(Blue);
					setAndDraw(j, i, "O");*/
				}
				else if ((n > 0.4 && n <= 0.41) || (n > 0.415 && n <= 0.42)) {

					biomeMap[j - 89 * 16][i - 49 * 16] = new Biom(0.35, 0.6, 1, 1, 1, 1);
					biomMapI[j - 89 * 16][i - 49 * 16] = 1;
					/*
					water = 0.35;
				   sand = 0.55;
				   ground = 1;
				   swamp = 2;
				   kliff = 2;
				   hiKliff = 2;
					*/
					//biomeMap[j-89*16][i-49*16] = '#';
				 /*setColor(Green);
				 setAndDraw(j, i, "O");*/
				}
				else if (n > 0.41 && n <= 0.415) {
					biomeMap[j - 89 * 16][i - 49 * 16] = new Biom(0.25, 0.5, 0.56, 0.56, 1, 1);
					biomMapI[j - 89 * 16][i - 49 * 16] = 2;
					/*
					water = 0.25;
				   sand = 0.68;
				   ground = 0.68;
				   swamp = 0.68;
				   kliff = 1;
				   hiKliff = 2;
					*/
					//biomeMap[j-89*16][i-49*16] = '*';
				 /*setColor(Green);
				 setAndDraw(j, i, "O");*/
				}
				else if (n > 0.42 && n <= 0.445) {
					biomeMap[j - 89 * 16][i - 49 * 16] = new Biom(0.35, 0.37, 0.58, 0.85, 1, 1);
					biomMapI[j - 89 * 16][i - 49 * 16] = 3;
					/*
					water = 0.35;
					sand = 0.35;
					ground = 0.58;
					swamp = 1;
					kliff = 2;
					hiKliff = 2;
					*/
					//biomeMap[j-89*16][i-49*16] = 'S';
				/*setColor(Orange);
				 setAndDraw(j, i, "O");*/
				}
				else if (n > 0.445 && n <= 0.585) {
					biomeMap[j - 89 * 16][i - 49 * 16] = new Biom(0.38, 0.41, 0.7, 0.7, 1, 1);
					biomMapI[j - 89 * 16][i - 49 * 16] = 4;
					/*
					water = 0.27;
					sand = 0.35;
					ground = 0.75;
					swamp = 0.75;
					kliff = 0.9;
					hiKliff = 1;
					*/
					//biomeMap[j-89*16][i-49*16] = 'O';
				/*setColor(Orange);
				 setAndDraw(j, i, "O");*/
				}
				else if (n > 0.585 && n <= 0.71) {
					biomeMap[j - 89 * 16][i - 49 * 16] = new Biom(0.28, 0.32, 0.6, 0.6, 0.9, 1);
					biomMapI[j - 89 * 16][i - 49 * 16] = 5;
					/*
					water = 0.3;
					sand = 0.35;
					ground = 0.5;
					swamp = 0.5;
					kliff = 0.8;
					hiKliff = 1;
					*/
					//biomeMap[j-89*16][i-49*16] = '^';
				/*setColor(Orange);
				 setAndDraw(j, i, "O");*/
				}
				else if (n > 0.71 && n <= 1) {
					biomeMap[j - 89 * 16][i - 49 * 16] = new Biom(0.22, 0.23, 0.57, 0.57, 0.72, 1);
					biomMapI[j - 89 * 16][i - 49 * 16] = 6;
					/*
					water = 0.2;
					sand = 0.2;
					ground = 0.40;
					swamp = 0.40;
					kliff = 0.65;
					hiKliff = 1;
					*/
					//biomeMap[j-89*16][i-49*16] = '-';
				/*setColor(Orange);
				 setAndDraw(j, i, "O");*/
				}
				else biomMapI[j - 89 * 16][i - 49 * 16] = -1;
				xoff += 1;//1

			}
			xoff = 0;
			yoff += 1;
		}
		for (int i = 0; i < 16; i++)
		{
			biomMapI[8][i] = 4;
			biomMapI[7][i] = 4;
			biomeMap[8][i] = new Biom(0.38, 0.41, 0.7, 0.7, 1, 1);
			biomeMap[7][i] = new Biom(0.38, 0.41, 0.7, 0.7, 1, 1);
		}

	}

	void fillMap(unsigned int seed)
	{
		double water, sand, swamp, ground, kliff, hiKliff;
		int xC = 0, yC = 0;
		bool err = false;

		float yFlying = 0;
		float xFlying = 0;

		float yoff = yFlying;
		float xoff = xFlying;

		PerlinNoise pn(seed);

		for (int i = 0; i < strok; ++i) {     // y //0
			double y = (double)yoff / ((double)_height);// ((double) _height)

			for (int j = 0; j < stolb; ++j) {  // x
				double x = (double)xoff / ((double)_width);// ((double) _width)
				double n = pn.noise(3.88 * x, 3.88 * y, 0.8);//0.8//2.3


				/*switch(biomeMap[j/89][i/49])
				{
				case 0:
					water = 0.4;
					sand = 0.45;
					ground = 0.8;
					swamp = 1;
					kliff = 2;//
					hiKliff = 2;//
					break;
				case 1:
					water = 0.35;
					sand = 0.55;
					ground = 1;
					swamp = 2;
					kliff = 2;
					hiKliff = 2;
					break;
				case 2:
					water = 0.25;
					sand = 0.65;
					ground = 0.65;
					swamp = 0.65;
					kliff = 1;
					hiKliff = 2;
					break;
				case 3:
					water = 0.35;
					sand = 0.35;
					ground = 0.55;
					swamp = 1;
					kliff = 2;
					hiKliff = 2;
					break;
				case 4:
					water = 0.27;
					sand = 0.35;
					ground = 0.75;
					swamp = 0.8;
					kliff = 0.9;
					hiKliff = 1;
					break;
				case 5:
					water = 0.3;
					sand = 0.35;
					ground = 0.5;
					swamp = 0.53;
					kliff = 0.8;
					hiKliff = 1;
					break;
				case 6:
					water = 0.2;
					sand = 0.2;
					ground = 0.40;
					swamp = 0.43;
					kliff = 0.65;
					hiKliff = 1;
					break;
				default:
					water = -1;
					sand = -1;
					swamp = -1;
					ground = -1;
					kliff = -1;
					hiKliff = -1;
					err = true;
					break;
				}*/



				if (m[j][i] == ' ') {

					xC = j / 89;
					yC = i / 49;

					//START ANGLE
					if (((j == xC * 89 && i == xC * 49) || (j == xC * 89 + 1 && i == xC * 49) || (j == xC * 89 && i == xC * 49 + 1)) && yC != 0 && xC != 0)//LEFT UP FIRST
					{

						double cWater = (biomeMap[xC][yC]->water + 2 * biomeMap[xC - 1][yC - 1]->water) / 3;
						double cSand = (biomeMap[xC][yC]->sand + 2 * biomeMap[xC - 1][yC - 1]->sand) / 3;
						double cGround = (biomeMap[xC][yC]->ground + 2 * biomeMap[xC - 1][yC - 1]->ground) / 3;
						double cSwamp = (biomeMap[xC][yC]->swamp + 2 * biomeMap[xC - 1][yC - 1]->swamp) / 3;
						double cKliff = (biomeMap[xC][yC]->kliff + 2 * biomeMap[xC - 1][yC - 1]->kliff) / 3;
						double cHiKliff = (biomeMap[xC][yC]->hiKliff + 2 * biomeMap[xC - 1][yC - 1]->hiKliff) / 3;

						bool err = biomeMap[xC][yC]->err || biomeMap[xC - 1][yC - 1]->err;



						if (n <= cWater) {
							m[j][i] = '~';
							/*setColor(Blue);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cWater && n <= cSand) {
							m[j][i] = (char)177;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						// Floors (or Planes)
						else if (n > cSand && n <= cGround) {
							m[j][i] = (char)178;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cGround && n <= cSwamp) {
							m[j][i] = '*';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						// Walls (or Mountains)
						else if (n > cSwamp && n <= cKliff) {
							m[j][i] = '^';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (n > cKliff && n <= cHiKliff) {
							m[j][i] = (char)127;
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (err) m[j][i] = '!';

					}

					else if (((j == xC * 89 + 88 && i == xC * 49) || (j == xC * 89 + 87 && i == xC * 49) || (j == xC * 89 + 88 && i == xC * 49 + 1)) && yC != 0 && xC != 15)//RIGHT UP FIRST
					{
						double cWater = (biomeMap[xC][yC]->water + 2 * biomeMap[xC + 1][yC - 1]->water) / 3;
						double cSand = (biomeMap[xC][yC]->sand + 2 * biomeMap[xC + 1][yC - 1]->sand) / 3;
						double cGround = (biomeMap[xC][yC]->ground + 2 * biomeMap[xC + 1][yC - 1]->ground) / 3;
						double cSwamp = (biomeMap[xC][yC]->swamp + 2 * biomeMap[xC + 1][yC - 1]->swamp) / 3;
						double cKliff = (biomeMap[xC][yC]->kliff + 2 * biomeMap[xC + 1][yC - 1]->kliff) / 3;
						double cHiKliff = (biomeMap[xC][yC]->hiKliff + 2 * biomeMap[xC + 1][yC - 1]->hiKliff) / 3;
						bool err = biomeMap[xC][yC]->err || biomeMap[xC + 1][yC - 1]->err;

						if (n <= cWater) {
							m[j][i] = '~';
							/*setColor(Blue);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cWater && n <= cSand) {
							m[j][i] = (char)177;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						// Floors (or Planes)
						else if (n > cSand && n <= cGround) {
							m[j][i] = (char)178;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cGround && n <= cSwamp) {
							m[j][i] = '*';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						// Walls (or Mountains)
						else if (n > cSwamp && n <= cKliff) {
							m[j][i] = '^';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (n > cKliff && n <= cHiKliff) {
							m[j][i] = (char)127;
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (err) m[j][i] = '!';
					}

					else if (((j == xC * 89 + 88 && i == xC * 49 + 48) || (j == xC * 89 + 87 && i == xC * 49 + 48) || (j == xC * 89 + 88 && i == xC * 49 + 47)) && yC != 15 && xC != 15)//RIGHT DOWN FIRST
					{

						double cWater = (biomeMap[xC][yC]->water + 2 * biomeMap[xC + 1][yC + 1]->water) / 3;
						double cSand = (biomeMap[xC][yC]->sand + 2 * biomeMap[xC + 1][yC + 1]->sand) / 3;
						double cGround = (biomeMap[xC][yC]->ground + 2 * biomeMap[xC + 1][yC + 1]->ground) / 3;
						double cSwamp = (biomeMap[xC][yC]->swamp + 2 * biomeMap[xC + 1][yC + 1]->swamp) / 3;
						double cKliff = (biomeMap[xC][yC]->kliff + 2 * biomeMap[xC + 1][yC + 1]->kliff) / 3;
						double cHiKliff = (biomeMap[xC][yC]->hiKliff + 2 * biomeMap[xC + 1][yC + 1]->hiKliff) / 3;
						bool err = biomeMap[xC][yC]->err || biomeMap[xC + 1][yC + 1]->err;

						if (n <= cWater) {
							m[j][i] = '~';
							/*setColor(Blue);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cWater && n <= cSand) {
							m[j][i] = (char)177;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						// Floors (or Planes)
						else if (n > cSand && n <= cGround) {
							m[j][i] = (char)178;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cGround && n <= cSwamp) {
							m[j][i] = '*';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						// Walls (or Mountains)
						else if (n > cSwamp && n <= cKliff) {
							m[j][i] = '^';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (n > cKliff && n <= cHiKliff) {
							m[j][i] = (char)127;
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (err) m[j][i] = '!';
					}

					else if (((j == xC * 89 && i == xC * 49 + 48) || (j == xC * 89 + 1 && i == xC * 49 + 48) || (j == xC * 89 && i == xC * 49 + 47)) && yC != 15 && xC != 0)//LEFT DOWN FIRST
					{
						double cWater = (biomeMap[xC][yC]->water + 2 * biomeMap[xC - 1][yC + 1]->water) / 3;
						double cSand = (biomeMap[xC][yC]->sand + 2 * biomeMap[xC - 1][yC + 1]->sand) / 3;
						double cGround = (biomeMap[xC][yC]->ground + 2 * biomeMap[xC - 1][yC + 1]->ground) / 3;
						double cSwamp = (biomeMap[xC][yC]->swamp + 2 * biomeMap[xC - 1][yC + 1]->swamp) / 3;
						double cKliff = (biomeMap[xC][yC]->kliff + 2 * biomeMap[xC - 1][yC + 1]->kliff) / 3;
						double cHiKliff = (biomeMap[xC][yC]->hiKliff + 2 * biomeMap[xC - 1][yC + 1]->hiKliff) / 3;
						bool err = biomeMap[xC][yC]->err || biomeMap[xC - 1][yC + 1]->err;

						if (n <= cWater) {
							m[j][i] = '~';
							/*setColor(Blue);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cWater && n <= cSand) {
							m[j][i] = (char)177;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						// Floors (or Planes)
						else if (n > cSand && n <= cGround) {
							m[j][i] = (char)178;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cGround && n <= cSwamp) {
							m[j][i] = '*';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						// Walls (or Mountains)
						else if (n > cSwamp && n <= cKliff) {
							m[j][i] = '^';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}

						// Walls (or Mountains)
						else if (n > cKliff && n <= cHiKliff) {
							m[j][i] = (char)127;
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (err) m[j][i] = '!';
					}

					else if (((j == xC * 89 + 1 && i == xC * 49 + 1) || (j == xC * 89 + 2 && i == xC * 49 + 1) || (j == xC * 89 + 1 && i == xC * 49 + 2)) && yC != 0 && xC != 0)//LEFT DOWN SECOND
					{

						double cWater = (biomeMap[xC][yC]->water + biomeMap[xC - 1][yC - 1]->water) / 2;
						double cSand = (biomeMap[xC][yC]->sand + biomeMap[xC - 1][yC - 1]->sand) / 2;
						double cGround = (biomeMap[xC][yC]->ground + biomeMap[xC - 1][yC - 1]->ground) / 2;
						double cSwamp = (biomeMap[xC][yC]->swamp + biomeMap[xC - 1][yC - 1]->swamp) / 2;
						double cKliff = (biomeMap[xC][yC]->kliff + biomeMap[xC - 1][yC - 1]->kliff) / 2;
						double cHiKliff = (biomeMap[xC][yC]->hiKliff + biomeMap[xC - 1][yC - 1]->hiKliff) / 2;
						bool err = biomeMap[xC][yC]->err || biomeMap[xC - 1][yC - 1]->err;

						if (n <= cWater) {
							m[j][i] = '~';
							/*setColor(Blue);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cWater && n <= cSand) {
							m[j][i] = (char)177;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						// Floors (or Planes)
						else if (n > cSand && n <= cGround) {
							m[j][i] = (char)178;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cGround && n <= cSwamp) {
							m[j][i] = '*';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						// Walls (or Mountains)
						else if (n > cSwamp && n <= cKliff) {
							m[j][i] = '^';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (n > cKliff && n <= cHiKliff) {
							m[j][i] = (char)127;
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (err) m[j][i] = '!';
					}

					else if (((j == xC * 89 + 87 && i == xC * 49 + 1) || (j == xC * 89 + 86 && i == xC * 49 + 1) || (j == xC * 89 + 87 && i == xC * 49 + 2)) && yC != 0 && xC != 15)//RIGHT UP SECOND
					{

						double cWater = (biomeMap[xC][yC]->water + biomeMap[xC + 1][yC - 1]->water) / 2;
						double cSand = (biomeMap[xC][yC]->sand + biomeMap[xC + 1][yC - 1]->sand) / 2;
						double cGround = (biomeMap[xC][yC]->ground + biomeMap[xC + 1][yC - 1]->ground) / 2;
						double cSwamp = (biomeMap[xC][yC]->swamp + biomeMap[xC + 1][yC - 1]->swamp) / 2;
						double cKliff = (biomeMap[xC][yC]->kliff + biomeMap[xC + 1][yC - 1]->kliff) / 2;
						double cHiKliff = (biomeMap[xC][yC]->hiKliff + biomeMap[xC + 1][yC - 1]->hiKliff) / 2;
						bool err = biomeMap[xC][yC]->err || biomeMap[xC + 1][yC - 1]->err;

						if (n <= cWater) {
							m[j][i] = '~';
							/*setColor(Blue);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cWater && n <= cSand) {
							m[j][i] = (char)177;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						// Floors (or Planes)
						else if (n > cSand && n <= cGround) {
							m[j][i] = (char)178;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cGround && n <= cSwamp) {
							m[j][i] = '*';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						// Walls (or Mountains)
						else if (n > cSwamp && n <= cKliff) {
							m[j][i] = '^';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (n > cKliff && n <= cHiKliff) {
							m[j][i] = (char)127;
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (err) m[j][i] = '!';
					}

					else if (((j == xC * 89 + 87 && i == xC * 49 + 47) || (j == xC * 89 + 86 && i == xC * 49 + 47) || (j == xC * 89 + 87 && i == xC * 49 + 46)) && yC != 15 && xC != 15)//RIGHT DOWN SECOND
					{

						double cWater = (biomeMap[xC][yC]->water + biomeMap[xC + 1][yC + 1]->water) / 2;
						double cSand = (biomeMap[xC][yC]->sand + biomeMap[xC + 1][yC + 1]->sand) / 2;
						double cGround = (biomeMap[xC][yC]->ground + biomeMap[xC + 1][yC + 1]->ground) / 2;
						double cSwamp = (biomeMap[xC][yC]->swamp + biomeMap[xC + 1][yC + 1]->swamp) / 2;
						double cKliff = (biomeMap[xC][yC]->kliff + biomeMap[xC + 1][yC + 1]->kliff) / 2;
						double cHiKliff = (biomeMap[xC][yC]->hiKliff + biomeMap[xC + 1][yC + 1]->hiKliff) / 2;
						bool err = biomeMap[xC][yC]->err || biomeMap[xC + 1][yC + 1]->err;

						if (n <= cWater) {
							m[j][i] = '~';
							/*setColor(Blue);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cWater && n <= cSand) {
							m[j][i] = (char)177;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						// Floors (or Planes)
						else if (n > cSand && n <= cGround) {
							m[j][i] = (char)178;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cGround && n <= cSwamp) {
							m[j][i] = '*';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						// Walls (or Mountains)
						else if (n > cSwamp && n <= cKliff) {
							m[j][i] = '^';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (n > cKliff && n <= cHiKliff) {
							m[j][i] = (char)127;
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (err) m[j][i] = '!';
					}

					else if (((j == xC * 89 + 1 && i == xC * 49 + 47) || (j == xC * 89 + 2 && i == xC * 49 + 47) || (j == xC * 89 + 1 && i == xC * 49 + 46)) && yC != 15 && xC != 0)//LEFT DOWN FIRD
					{

						double cWater = (biomeMap[xC][yC]->water + biomeMap[xC - 1][yC + 1]->water) / 2;
						double cSand = (biomeMap[xC][yC]->sand + biomeMap[xC - 1][yC + 1]->sand) / 2;
						double cGround = (biomeMap[xC][yC]->ground + biomeMap[xC - 1][yC + 1]->ground) / 2;
						double cSwamp = (biomeMap[xC][yC]->swamp + biomeMap[xC - 1][yC + 1]->swamp) / 2;
						double cKliff = (biomeMap[xC][yC]->kliff + biomeMap[xC - 1][yC + 1]->kliff) / 2;
						double cHiKliff = (biomeMap[xC][yC]->hiKliff + biomeMap[xC - 1][yC + 1]->hiKliff) / 2;
						bool err = biomeMap[xC][yC]->err || biomeMap[xC - 1][yC + 1]->err;

						if (n <= cWater) {
							m[j][i] = '~';
							/*setColor(Blue);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cWater && n <= cSand) {
							m[j][i] = (char)177;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						// Floors (or Planes)
						else if (n > cSand && n <= cGround) {
							m[j][i] = (char)178;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cGround && n <= cSwamp) {
							m[j][i] = '*';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						// Walls (or Mountains)
						else if (n > cSwamp && n <= cKliff) {
							m[j][i] = '^';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (n > cKliff && n <= cHiKliff) {
							m[j][i] = (char)127;
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (err) m[j][i] = '!';
					}

					else if (((j == xC * 89 + 2 && i == xC * 49 + 2) || (j == xC * 89 + 3 && i == xC * 49 + 2) || (j == xC * 89 + 2 && i == xC * 49 + 3)) && yC != 0 && xC != 0)//LEFT DOWN FIRD
					{

						double cWater = (2 * biomeMap[xC][yC]->water + biomeMap[xC - 1][yC - 1]->water) / 3;
						double cSand = (2 * biomeMap[xC][yC]->sand + biomeMap[xC - 1][yC - 1]->sand) / 3;
						double cGround = (2 * biomeMap[xC][yC]->ground + biomeMap[xC - 1][yC - 1]->ground) / 3;
						double cSwamp = (2 * biomeMap[xC][yC]->swamp + biomeMap[xC - 1][yC - 1]->swamp) / 3;
						double cKliff = (2 * biomeMap[xC][yC]->kliff + biomeMap[xC - 1][yC - 1]->kliff) / 3;
						double cHiKliff = (2 * biomeMap[xC][yC]->hiKliff + biomeMap[xC - 1][yC - 1]->hiKliff) / 3;
						bool err = biomeMap[xC][yC]->err || biomeMap[xC - 1][yC - 1]->err;

						if (n <= cWater) {
							m[j][i] = '~';
							/*setColor(Blue);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cWater && n <= cSand) {
							m[j][i] = (char)177;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						// Floors (or Planes)
						else if (n > cSand && n <= cGround) {
							m[j][i] = (char)178;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cGround && n <= cSwamp) {
							m[j][i] = '*';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						// Walls (or Mountains)
						else if (n > cSwamp && n <= cKliff) {
							m[j][i] = '^';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (n > cKliff && n <= cHiKliff) {
							m[j][i] = (char)127;
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (err) m[j][i] = '!';
					}

					else if (((j == xC * 89 + 86 && i == xC * 49 + 2) || (j == xC * 89 + 85 && i == xC * 49 + 2) || (j == xC * 89 + 86 && i == xC * 49 + 3)) && yC != 0 && xC != 15)//RIGHT UP FIRD
					{

						double cWater = (2 * biomeMap[xC][yC]->water + biomeMap[xC + 1][yC - 1]->water) / 3;
						double cSand = (2 * biomeMap[xC][yC]->sand + biomeMap[xC + 1][yC - 1]->sand) / 3;
						double cGround = (2 * biomeMap[xC][yC]->ground + biomeMap[xC + 1][yC - 1]->ground) / 3;
						double cSwamp = (2 * biomeMap[xC][yC]->swamp + biomeMap[xC + 1][yC - 1]->swamp) / 3;
						double cKliff = (2 * biomeMap[xC][yC]->kliff + biomeMap[xC + 1][yC - 1]->kliff) / 3;
						double cHiKliff = (2 * biomeMap[xC][yC]->hiKliff + biomeMap[xC + 1][yC - 1]->hiKliff) / 3;
						bool err = biomeMap[xC][yC]->err || biomeMap[xC + 1][yC - 1]->err;

						if (n <= cWater) {
							m[j][i] = '~';
							/*setColor(Blue);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cWater && n <= cSand) {
							m[j][i] = (char)177;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						// Floors (or Planes)
						else if (n > cSand && n <= cGround) {
							m[j][i] = (char)178;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						// Walls (or Mountains)
						else if (n > cGround && n <= cSwamp) {
							m[j][i] = '*';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						// Walls (or Mountains)
						else if (n > cSwamp && n <= cKliff) {
							m[j][i] = '^';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (n > cKliff && n <= cHiKliff) {
							m[j][i] = (char)127;
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (err) m[j][i] = '!';
					}

					else if (((j == xC * 89 + 86 && i == xC * 49 + 46) || (j == xC * 89 + 85 && i == xC * 49 + 46) || (j == xC * 89 + 86 && i == xC * 49 + 45)) && yC != 15 && xC != 15)//RIGHT DOWN FIRD
					{
						double cWater = (2 * biomeMap[xC][yC]->water + biomeMap[xC + 1][yC + 1]->water) / 3;
						double cSand = (2 * biomeMap[xC][yC]->sand + biomeMap[xC + 1][yC + 1]->sand) / 3;
						double cGround = (2 * biomeMap[xC][yC]->ground + biomeMap[xC + 1][yC + 1]->ground) / 3;
						double cSwamp = (2 * biomeMap[xC][yC]->swamp + biomeMap[xC + 1][yC + 1]->swamp) / 3;
						double cKliff = (2 * biomeMap[xC][yC]->kliff + biomeMap[xC + 1][yC + 1]->kliff) / 3;
						double cHiKliff = (2 * biomeMap[xC][yC]->hiKliff + biomeMap[xC + 1][yC + 1]->hiKliff) / 3;
						bool err = biomeMap[xC][yC]->err || biomeMap[xC + 1][yC + 1]->err;

						if (n <= cWater) {
							m[j][i] = '~';
							/*setColor(Blue);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cWater && n <= cSand) {
							m[j][i] = (char)177;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						// Floors (or Planes)
						else if (n > cSand && n <= cGround) {
							m[j][i] = (char)178;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cGround && n <= cSwamp) {
							m[j][i] = '*';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						// Walls (or Mountains)
						else if (n > cSwamp && n <= cKliff) {
							m[j][i] = '^';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (n > cKliff && n <= cHiKliff) {
							m[j][i] = (char)127;
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (err) m[j][i] = '!';
					}

					else if (((j == xC * 89 + 2 && i == xC * 49 + 46) || (j == xC * 89 + 3 && i == xC * 49 + 46) || (j == xC * 89 + 2 && i == xC * 49 + 45)) && yC != 15 && xC != 0)//LEFT DOWN FIRD
					{

						double cWater = (2 * biomeMap[xC][yC]->water + biomeMap[xC - 1][yC + 1]->water) / 3;
						double cSand = (2 * biomeMap[xC][yC]->sand + biomeMap[xC - 1][yC + 1]->sand) / 3;
						double cGround = (2 * biomeMap[xC][yC]->ground + biomeMap[xC - 1][yC + 1]->ground) / 3;
						double cSwamp = (2 * biomeMap[xC][yC]->swamp + biomeMap[xC - 1][yC + 1]->swamp) / 3;
						double cKliff = (2 * biomeMap[xC][yC]->kliff + biomeMap[xC - 1][yC + 1]->kliff) / 3;
						double cHiKliff = (2 * biomeMap[xC][yC]->hiKliff + biomeMap[xC - 1][yC + 1]->hiKliff) / 3;
						bool err = biomeMap[xC][yC]->err || biomeMap[xC - 1][yC + 1]->err;

						if (n <= cWater) {
							m[j][i] = '~';
							/*setColor(Blue);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cWater && n <= cSand) {
							m[j][i] = (char)177;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						// Floors (or Planes)
						else if (n > cSand && n <= cGround) {
							m[j][i] = (char)178;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cGround && n <= cSwamp) {
							m[j][i] = '*';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						// Walls (or Mountains)
						else if (n > cSwamp && n <= cKliff) {
							m[j][i] = '^';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (n > cKliff && n <= cHiKliff) {
							m[j][i] = (char)127;
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (err) m[j][i] = '!';
					}
					//END OF ANGLE
					//START LINE
					else if ((j >= xC * 89 + 2 && j <= xC * 89 + 85) && (i >= xC * 49 && i <= xC * 49) && yC != 0)//UP FIRST
					{
						double cWater = (biomeMap[xC][yC]->water + 2 * biomeMap[xC][yC - 1]->water) / 3;
						double cSand = (biomeMap[xC][yC]->sand + 2 * biomeMap[xC][yC - 1]->sand) / 3;
						double cGround = (biomeMap[xC][yC]->ground + 2 * biomeMap[xC][yC - 1]->ground) / 3;
						double cSwamp = (biomeMap[xC][yC]->swamp + 2 * biomeMap[xC][yC - 1]->swamp) / 3;
						double cKliff = (biomeMap[xC][yC]->kliff + 2 * biomeMap[xC][yC - 1]->kliff) / 3;
						double cHiKliff = (biomeMap[xC][yC]->hiKliff + 2 * biomeMap[xC][yC - 1]->hiKliff) / 3;
						bool err = biomeMap[xC][yC]->err || biomeMap[xC][yC - 1]->err;

						if (n <= cWater) {
							m[j][i] = '~';
							/*setColor(Blue);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cWater && n <= cSand) {
							m[j][i] = (char)177;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						// Floors (or Planes)
						else if (n > cSand && n <= cGround) {
							m[j][i] = (char)178;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cGround && n <= cSwamp) {
							m[j][i] = '*';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						// Walls (or Mountains)
						else if (n > cSwamp && n <= cKliff) {
							m[j][i] = '^';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (n > cKliff && n <= cHiKliff) {
							m[j][i] = (char)127;
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (err) m[j][i] = '!';
					}
					else if ((j >= xC * 89 + 88 && j <= xC * 89 + 88) && (i >= xC * 49 + 2 && i <= xC * 49 + 46) && xC != 15)//RIGHT FIRST
					{
						double cWater = (biomeMap[xC][yC]->water + 2 * biomeMap[xC + 1][yC]->water) / 3;
						double cSand = (biomeMap[xC][yC]->sand + 2 * biomeMap[xC + 1][yC]->sand) / 3;
						double cGround = (biomeMap[xC][yC]->ground + 2 * biomeMap[xC + 1][yC]->ground) / 3;
						double cSwamp = (biomeMap[xC][yC]->swamp + 2 * biomeMap[xC + 1][yC]->swamp) / 3;
						double cKliff = (biomeMap[xC][yC]->kliff + 2 * biomeMap[xC + 1][yC]->kliff) / 3;
						double cHiKliff = (biomeMap[xC][yC]->hiKliff + 2 * biomeMap[xC + 1][yC]->hiKliff) / 3;
						bool err = biomeMap[xC][yC]->err || biomeMap[xC + 1][yC]->err;

						if (n <= cWater) {
							m[j][i] = '~';
							/*setColor(Blue);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cWater && n <= cSand) {
							m[j][i] = (char)177;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						// Floors (or Planes)
						else if (n > cSand && n <= cGround) {
							m[j][i] = (char)178;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cGround && n <= cSwamp) {
							m[j][i] = '*';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						// Walls (or Mountains)
						else if (n > cSwamp && n <= cKliff) {
							m[j][i] = '^';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (n > cKliff && n <= cHiKliff) {
							m[j][i] = (char)127;
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (err) m[j][i] = '!';
					}
					else if ((j >= xC * 89 + 2 && j <= xC * 89 + 85) && (i >= xC * 49 + 48 && i <= xC * 49 + 48) && yC != 15)//DOWN FIRST
					{

						double cWater = (biomeMap[xC][yC]->water + 2 * biomeMap[xC][yC + 1]->water) / 3;
						double cSand = (biomeMap[xC][yC]->sand + 2 * biomeMap[xC][yC + 1]->sand) / 3;
						double cGround = (biomeMap[xC][yC]->ground + 2 * biomeMap[xC][yC + 1]->ground) / 3;
						double cSwamp = (biomeMap[xC][yC]->swamp + 2 * biomeMap[xC][yC + 1]->swamp) / 3;
						double cKliff = (biomeMap[xC][yC]->kliff + 2 * biomeMap[xC][yC + 1]->kliff) / 3;
						double cHiKliff = (biomeMap[xC][yC]->hiKliff + 2 * biomeMap[xC][yC + 1]->hiKliff) / 3;
						bool err = biomeMap[xC][yC]->err || biomeMap[xC][yC + 1]->err;

						if (n <= cWater) {
							m[j][i] = '~';
							/*setColor(Blue);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cWater && n <= cSand) {
							m[j][i] = (char)177;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						// Floors (or Planes)
						else if (n > cSand && n <= cGround) {
							m[j][i] = (char)178;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cGround && n <= cSwamp) {
							m[j][i] = '*';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						// Walls (or Mountains)
						else if (n > cSwamp && n <= cKliff) {
							m[j][i] = '^';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (n > cKliff && n <= cHiKliff) {
							m[j][i] = (char)127;
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (err) m[j][i] = '!';
					}
					else if ((j >= xC * 89 && j <= xC * 89) && (i >= xC * 49 + 2 && i <= xC * 49 + 46) && xC != 0)//LEFT FIRST
					{
						double cWater = (biomeMap[xC][yC]->water + 2 * biomeMap[xC - 1][yC]->water) / 3;
						double cSand = (biomeMap[xC][yC]->sand + 2 * biomeMap[xC - 1][yC]->sand) / 3;
						double cGround = (biomeMap[xC][yC]->ground + 2 * biomeMap[xC - 1][yC]->ground) / 3;
						double cSwamp = (biomeMap[xC][yC]->swamp + 2 * biomeMap[xC - 1][yC]->swamp) / 3;
						double cKliff = (biomeMap[xC][yC]->kliff + 2 * biomeMap[xC - 1][yC]->kliff) / 3;
						double cHiKliff = (biomeMap[xC][yC]->hiKliff + 2 * biomeMap[xC - 1][yC]->hiKliff) / 3;
						bool err = biomeMap[xC][yC]->err || biomeMap[xC - 1][yC]->err;

						if (n <= cWater) {
							m[j][i] = '~';
							/*setColor(Blue);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cWater && n <= cSand) {
							m[j][i] = (char)177;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						// Floors (or Planes)
						else if (n > cSand && n <= cGround) {
							m[j][i] = (char)178;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cGround && n <= cSwamp) {
							m[j][i] = '*';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						// Walls (or Mountains)
						else if (n > cSwamp && n <= cKliff) {
							m[j][i] = '^';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (n > cKliff && n <= cHiKliff) {
							m[j][i] = (char)127;
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (err) m[j][i] = '!';
					}

					else if ((j >= xC * 89 + 2 && j <= xC * 89 + 85) && (i >= xC * 49 + 1 && i <= xC * 49 + 1) && yC != 0)//UP SECOND
					{
						double cWater = (biomeMap[xC][yC]->water + biomeMap[xC][yC - 1]->water) / 2;
						double cSand = (biomeMap[xC][yC]->sand + biomeMap[xC][yC - 1]->sand) / 2;
						double cGround = (biomeMap[xC][yC]->ground + biomeMap[xC][yC - 1]->ground) / 2;
						double cSwamp = (biomeMap[xC][yC]->swamp + biomeMap[xC][yC - 1]->swamp) / 2;
						double cKliff = (biomeMap[xC][yC]->kliff + biomeMap[xC][yC - 1]->kliff) / 2;
						double cHiKliff = (biomeMap[xC][yC]->hiKliff + biomeMap[xC][yC - 1]->hiKliff) / 2;
						bool err = biomeMap[xC][yC]->err || biomeMap[xC][yC - 1]->err;

						if (n <= cWater) {
							m[j][i] = '~';
							/*setColor(Blue);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cWater && n <= cSand) {
							m[j][i] = (char)177;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						// Floors (or Planes)
						else if (n > cSand && n <= cGround) {
							m[j][i] = (char)178;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cGround && n <= cSwamp) {
							m[j][i] = '*';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						// Walls (or Mountains)
						else if (n > cSwamp && n <= cKliff) {
							m[j][i] = '^';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (n > cKliff && n <= cHiKliff) {
							m[j][i] = (char)127;
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (err) m[j][i] = '!';
					}
					else if ((j >= xC * 89 + 87 && j <= xC * 89 + 87) && (i >= xC * 49 + 2 && i <= xC * 49 + 46) && xC != 15)//RIGHT SECOND
					{
						double cWater = (biomeMap[xC][yC]->water + biomeMap[xC + 1][yC]->water) / 2;
						double cSand = (biomeMap[xC][yC]->sand + biomeMap[xC + 1][yC]->sand) / 2;
						double cGround = (biomeMap[xC][yC]->ground + biomeMap[xC + 1][yC]->ground) / 2;
						double cSwamp = (biomeMap[xC][yC]->swamp + biomeMap[xC + 1][yC]->swamp) / 2;
						double cKliff = (biomeMap[xC][yC]->kliff + biomeMap[xC + 1][yC]->kliff) / 2;
						double cHiKliff = (biomeMap[xC][yC]->hiKliff + biomeMap[xC + 1][yC]->hiKliff) / 2;
						bool err = biomeMap[xC][yC]->err || biomeMap[xC + 1][yC]->err;

						if (n <= cWater) {
							m[j][i] = '~';
							/*setColor(Blue);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cWater && n <= cSand) {
							m[j][i] = (char)177;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						// Floors (or Planes)
						else if (n > cSand && n <= cGround) {
							m[j][i] = (char)178;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cGround && n <= cSwamp) {
							m[j][i] = '*';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						// Walls (or Mountains)
						else if (n > cSwamp && n <= cKliff) {
							m[j][i] = '^';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (n > cKliff && n <= cHiKliff) {
							m[j][i] = (char)127;
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (err) m[j][i] = '!';
					}
					else if ((j >= xC * 89 + 2 && j <= xC * 89 + 85) && (i >= xC * 49 + 47 && i <= xC * 49 + 47) && yC != 15)//DOWN SECOND
					{
						double cWater = (biomeMap[xC][yC]->water + biomeMap[xC][yC + 1]->water) / 2;
						double cSand = (biomeMap[xC][yC]->sand + biomeMap[xC][yC + 1]->sand) / 2;
						double cGround = (biomeMap[xC][yC]->ground + biomeMap[xC][yC + 1]->ground) / 2;
						double cSwamp = (biomeMap[xC][yC]->swamp + biomeMap[xC][yC + 1]->swamp) / 2;
						double cKliff = (biomeMap[xC][yC]->kliff + biomeMap[xC][yC + 1]->kliff) / 2;
						double cHiKliff = (biomeMap[xC][yC]->hiKliff + biomeMap[xC][yC + 1]->hiKliff) / 2;
						bool err = biomeMap[xC][yC]->err || biomeMap[xC][yC + 1]->err;

						if (n <= cWater) {
							m[j][i] = '~';
							/*setColor(Blue);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cWater && n <= cSand) {
							m[j][i] = (char)177;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						// Floors (or Planes)
						else if (n > cSand && n <= cGround) {
							m[j][i] = (char)178;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cGround && n <= cSwamp) {
							m[j][i] = '*';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						// Walls (or Mountains)
						else if (n > cSwamp && n <= cKliff) {
							m[j][i] = '^';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (n > cKliff && n <= cHiKliff) {
							m[j][i] = (char)127;
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (err) m[j][i] = '!';
					}
					else if ((j >= xC * 89 + 1 && j <= xC * 89 + 1) && (i >= xC * 49 + 2 && i <= xC * 49 + 46) && xC != 0)//LEFT SECOND
					{
						double cWater = (biomeMap[xC][yC]->water + biomeMap[xC - 1][yC]->water) / 2;
						double cSand = (biomeMap[xC][yC]->sand + biomeMap[xC - 1][yC]->sand) / 2;
						double cGround = (biomeMap[xC][yC]->ground + biomeMap[xC - 1][yC]->ground) / 2;
						double cSwamp = (biomeMap[xC][yC]->swamp + biomeMap[xC - 1][yC]->swamp) / 2;
						double cKliff = (biomeMap[xC][yC]->kliff + biomeMap[xC - 1][yC]->kliff) / 2;
						double cHiKliff = (biomeMap[xC][yC]->hiKliff + biomeMap[xC - 1][yC]->hiKliff) / 2;
						bool err = biomeMap[xC][yC]->err || biomeMap[xC - 1][yC]->err;

						if (n <= cWater) {
							m[j][i] = '~';
							/*setColor(Blue);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cWater && n <= cSand) {
							m[j][i] = (char)177;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						// Floors (or Planes)
						else if (n > cSand && n <= cGround) {
							m[j][i] = (char)177;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cGround && n <= cSwamp) {
							m[j][i] = '*';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						// Walls (or Mountains)
						else if (n > cSwamp && n <= cKliff) {
							m[j][i] = '^';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (n > cKliff && n <= cHiKliff) {
							m[j][i] = (char)127;
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (err) m[j][i] = '!';
					}

					else if ((j >= xC * 89 + 2 && j <= xC * 89 + 85) && (i >= xC * 49 + 2 && i <= xC * 49 + 2) && yC != 0)//UP SECOND
					{
						double cWater = (2 * biomeMap[xC][yC]->water + biomeMap[xC][yC - 1]->water) / 3;
						double cSand = (2 * biomeMap[xC][yC]->sand + biomeMap[xC][yC - 1]->sand) / 3;
						double cGround = (2 * biomeMap[xC][yC]->ground + biomeMap[xC][yC - 1]->ground) / 3;
						double cSwamp = (2 * biomeMap[xC][yC]->swamp + biomeMap[xC][yC - 1]->swamp) / 3;
						double cKliff = (2 * biomeMap[xC][yC]->kliff + biomeMap[xC][yC - 1]->kliff) / 3;
						double cHiKliff = (2 * biomeMap[xC][yC]->hiKliff + biomeMap[xC][yC - 1]->hiKliff) / 3;
						bool err = biomeMap[xC][yC]->err || biomeMap[xC][yC - 1]->err;

						if (n <= cWater) {
							m[j][i] = '~';
							/*setColor(Blue);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cWater && n <= cSand) {
							m[j][i] = (char)177;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						// Floors (or Planes)
						else if (n > cSand && n <= cGround) {
							m[j][i] = (char)178;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cGround && n <= cSwamp) {
							m[j][i] = '*';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						// Walls (or Mountains)
						else if (n > cSwamp && n <= cKliff) {
							m[j][i] = '^';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (n > cKliff && n <= cHiKliff) {
							m[j][i] = (char)127;
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (err) m[j][i] = '!';
					}
					else if ((j >= xC * 89 + 86 && j <= xC * 89 + 86) && (i >= xC * 49 + 2 && i <= xC * 49 + 46) && xC != 15)//RIGHT SECOND
					{
						double cWater = (2 * biomeMap[xC][yC]->water + biomeMap[xC + 1][yC]->water) / 3;
						double cSand = (2 * biomeMap[xC][yC]->sand + biomeMap[xC + 1][yC]->sand) / 3;
						double cGround = (2 * biomeMap[xC][yC]->ground + biomeMap[xC + 1][yC]->ground) / 3;
						double cSwamp = (2 * biomeMap[xC][yC]->swamp + biomeMap[xC + 1][yC]->swamp) / 3;
						double cKliff = (2 * biomeMap[xC][yC]->kliff + biomeMap[xC + 1][yC]->kliff) / 3;
						double cHiKliff = (2 * biomeMap[xC][yC]->hiKliff + biomeMap[xC + 1][yC]->hiKliff) / 3;
						bool err = biomeMap[xC][yC]->err || biomeMap[xC + 1][yC]->err;

						if (n <= cWater) {
							m[j][i] = '~';
							/*setColor(Blue);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cWater && n <= cSand) {
							m[j][i] = (char)177;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						// Floors (or Planes)
						else if (n > cSand && n <= cGround) {
							m[j][i] = (char)178;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cGround && n <= cSwamp) {
							m[j][i] = '*';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						// Walls (or Mountains)
						else if (n > cSwamp && n <= cKliff) {
							m[j][i] = '^';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (n > cKliff && n <= cHiKliff) {
							m[j][i] = (char)127;
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (err) m[j][i] = '!';
					}
					else if ((j >= xC * 89 + 2 && j <= xC * 89 + 85) && (i >= xC * 49 + 46 && i <= xC * 49 + 46) && yC != 15)//DOWN SECOND
					{
						double cWater = (2 * biomeMap[xC][yC]->water + biomeMap[xC][yC + 1]->water) / 3;
						double cSand = (2 * biomeMap[xC][yC]->sand + biomeMap[xC][yC + 1]->sand) / 3;
						double cGround = (2 * biomeMap[xC][yC]->ground + biomeMap[xC][yC + 1]->ground) / 3;
						double cSwamp = (2 * biomeMap[xC][yC]->swamp + biomeMap[xC][yC + 1]->swamp) / 3;
						double cKliff = (2 * biomeMap[xC][yC]->kliff + biomeMap[xC][yC + 1]->kliff) / 3;
						double cHiKliff = (2 * biomeMap[xC][yC]->hiKliff + biomeMap[xC][yC + 1]->hiKliff) / 3;
						bool err = biomeMap[xC][yC]->err || biomeMap[xC][yC + 1]->err;

						if (n <= cWater) {
							m[j][i] = '~';
							/*setColor(Blue);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cWater && n <= cSand) {
							m[j][i] = (char)177;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						// Floors (or Planes)
						else if (n > cSand && n <= cGround) {
							m[j][i] = (char)178;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cGround && n <= cSwamp) {
							m[j][i] = '*';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						// Walls (or Mountains)
						else if (n > cSwamp && n <= cKliff) {
							m[j][i] = '^';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (n > cKliff && n <= cHiKliff) {
							m[j][i] = (char)127;
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (err) m[j][i] = '!';
					}
					else if ((j >= xC * 89 + 2 && j <= xC * 89 + 2) && (i >= xC * 49 + 2 && i <= xC * 49 + 46) && xC != 0)//LEFT SECOND
					{
						double cWater = (2 * biomeMap[xC][yC]->water + biomeMap[xC - 1][yC]->water) / 3;
						double cSand = (2 * biomeMap[xC][yC]->sand + biomeMap[xC - 1][yC]->sand) / 3;
						double cGround = (2 * biomeMap[xC][yC]->ground + biomeMap[xC - 1][yC]->ground) / 3;
						double cSwamp = (2 * biomeMap[xC][yC]->swamp + biomeMap[xC - 1][yC]->swamp) / 3;
						double cKliff = (2 * biomeMap[xC][yC]->kliff + biomeMap[xC - 1][yC]->kliff) / 3;
						double cHiKliff = (2 * biomeMap[xC][yC]->hiKliff + biomeMap[xC - 1][yC]->hiKliff) / 3;
						bool err = biomeMap[xC][yC]->err || biomeMap[xC - 1][yC]->err;

						if (n <= cWater) {
							m[j][i] = '~';
							/*setColor(Blue);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cWater && n <= cSand) {
							m[j][i] = (char)177;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						// Floors (or Planes)
						else if (n > cSand && n <= cGround) {
							m[j][i] = (char)178;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						else if (n > cGround && n <= cSwamp) {
							m[j][i] = '*';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						// Walls (or Mountains)
						else if (n > cSwamp && n <= cKliff) {
							m[j][i] = '^';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (n > cKliff && n <= cHiKliff) {
							m[j][i] = (char)127;
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (err) m[j][i] = '!';
					}
					//END LINE
					//OTHER BLOCKS
					else
					{

						if (n <= biomeMap[xC][yC]->water) {

							m[j][i] = '~';
							/*setColor(Blue);
							setAndDraw(j, i, "O");*/
						}
						else if (n > biomeMap[xC][yC]->water && n <= biomeMap[xC][yC]->sand) {

							m[j][i] = (char)177;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						// Floors (or Planes)
						else if (n > biomeMap[xC][yC]->sand && n <= biomeMap[xC][yC]->ground) {
							m[j][i] = (char)178;
							/*setColor(Green);
							setAndDraw(j, i, "O");*/
						}
						else if (n > biomeMap[xC][yC]->ground && n <= biomeMap[xC][yC]->swamp) {

							m[j][i] = '*';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						// Walls (or Mountains)
						else if (n > biomeMap[xC][yC]->swamp && n <= biomeMap[xC][yC]->kliff) {
							m[j][i] = '^';
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (n > biomeMap[xC][yC]->kliff && n <= biomeMap[xC][yC]->hiKliff) {
							m[j][i] = (char)127;
							/*setColor(Orange);
							 setAndDraw(j, i, "O");*/
						}
						else if (biomeMap[xC][yC]->err)
						{

							m[j][i] = '!';
						}

					}



				}

				xoff += 1;//1

			}
			xoff = xFlying;
			yoff += 1;

			for (int i = 0; i < 49 * 16; i++)
			{
				if ((i < 49 * 5 + 16) || (i >= 49 * 6 - 16 && i < 49 * 11 + 16) || (i >= 49 * 12 - 16 && i < 49 * 16))
				{
					m[89 * 8 - 4][i] = '^'; m[89 * 8 - 3][i] = '^'; m[89 * 8 - 2][i] = '^'; m[89 * 8 - 1][i] = '^'; m[89 * 8][i] = '^'; m[89 * 8 + 1][i] = '^'; m[89 * 8 + 2][i] = '^'; m[89 * 8 + 3][i] = '^'; m[89 * 8 + 4][i] = '^'; m[89 * 8 + 5][i] = '^'; m[89 * 8 + 6][i] = '^';
				}
				else
				{
					m[89 * 8 - 4][i] = (char)177; m[89 * 8 - 3][i] = (char)177; m[89 * 8 - 2][i] = (char)177; m[89 * 8 - 1][i] = (char)177; m[89 * 8][i] = (char)177;
					m[89 * 8 + 1][i] = 'D';
					m[89 * 8 + 2][i] = (char)177; m[89 * 8 + 3][i] = (char)177; m[89 * 8 + 4][i] = (char)177; m[89 * 8 + 5][i] = (char)177; m[89 * 8 + 6][i] = (char)177;
				}

			}
		}

		for (int i = 0; i < 25; ++i)//up
		{
			for (int j = 0; j < stolb; ++j)
			{
				if (i >= 21)
				{
					//RPGUtils::setColor(Orange);
					m[j][i] = '^';
				}
				else
				{
					//RPGUtils::setColor(Blue);
					m[j][i] = '~';
				}
			}
		}
		for (int i = 49 * 16 - 23; i < strok; ++i)//down
		{
			for (int j = 0; j < stolb; ++j)
			{
				if (i <= 49 * 16 - 19)
				{
					//RPGUtils::setColor(Orange);
					m[j][i] = '^';
				}
				else
				{
					//RPGUtils::setColor(Blue);
					m[j][i] = '~';
				}
			}
		}

		for (int i = 21; i < 49 * 16 - 18; ++i)//left
		{
			for (int j = 0; j < 45; ++j)
			{
				if (j >= 40)
				{
					//RPGUtils::setColor(Orange);
					m[j][i] = '^';
				}
				else
				{
					//RPGUtils::setColor(Blue);
					m[j][i] = '~';
				}
			}
		}
		for (int i = 21; i < 49 * 16 - 18; ++i)//right
		{
			for (int j = stolb - 43; j < stolb; ++j)
			{
				if (j <= stolb - 38)
				{
					//RPGUtils::setColor(Orange);
					m[j][i] = '^';
				}
				else
				{
					//RPGUtils::setColor(Blue);
					m[j][i] = '~';
				}
			}
		}

		/*yoff = yFlying;
		xoff = xFlying;*/
	}

	void printEarlyMap(int indexX, int indexY, int xExpand, int yExpand)
	{
		int x = indexX;
		int y = indexY;

		for (int i = 24 - yExpand; i < 24 + yExpand; i++)
		{
			for (int j = 44 - xExpand; j < 44 + xExpand; j++)
			{
				if (day)
				{
					RPGUtils::setColor(White);
					if (m[j + indexX][i + indexY] == '~')RPGUtils::setColor(White, LightBlue);//Blue
					else if (m[j + indexX][i + indexY] == (char)177)RPGUtils::setColor(Yellow, Orange);//Orange  Orange
					else if (m[j + indexX][i + indexY] == '*')RPGUtils::setColor(LightPurple, LightCyan);//Purple Cyan
					else if (m[j + indexX][i + indexY] == (char)178)RPGUtils::setColor(LightGreen, Black);//Green
					else if (m[j + indexX][i + indexY] == '^')RPGUtils::setColor(Black, LightGrey);//grey
					else if (m[j + indexX][i + indexY] == (char)127)RPGUtils::setColor(Black, LightRed);//Red  (char)127
					else if (m[j + indexX][i + indexY] == (char)219)RPGUtils::setColor(Orange);//Red  (char)127
					else if (m[j + indexX][i + indexY] == (char)176)RPGUtils::setColor(Orange, Grey);//Red  (char)127
					else RPGUtils::setColor(White);
				}
				else
				{
					RPGUtils::setColor(White);
					if (m[j + indexX][i + indexY] == '~')RPGUtils::setColor(White, Blue);//Blue
					else if (m[j + indexX][i + indexY] == (char)177)RPGUtils::setColor(Orange, Orange);//Orange Orange
					else if (m[j + indexX][i + indexY] == '*')RPGUtils::setColor(Purple, Cyan);//Purple Cyan
					else if (m[j + indexX][i + indexY] == (char)178)RPGUtils::setColor(Green, Black);//Green
					else if (m[j + indexX][i + indexY] == '^')RPGUtils::setColor(Black, Grey);//grey
					else if (m[j + indexX][i + indexY] == (char)127)RPGUtils::setColor(Black, Red);//Red  (char)127
					else if (m[j + indexX][i + indexY] == (char)219)RPGUtils::setColor(Orange);//Red  (char)127
					else if (m[j + indexX][i + indexY] == (char)176)RPGUtils::setColor(Grey, Black);//Red  (char)127
					else RPGUtils::setColor(White);
				}


				if (j == 45 && i == 25)
				{
					RPGUtils::setColor(White);
					RPGUtils::setAndDraw(j, i, "@");
				}
				else RPGUtils::setAndDraw(j, i, m[j + indexX][i + indexY]);

				//printf("%14f ", massive[j][i]);
			}
			//printf("\n");
		}
		//printf("\n");
	}


	void printTown(int count)
	{
		for (int i = 0; i < count; i++)
		{
			putTowns(townsX[i], townsY[i]);
		}
	}

	void putTowns(int x, int y)
	{
		//up wall
		for (int i = y - 25; i <= y + 26; i++)
		{
			for (int j = x - 45; j <= x + 46; j++)
			{
				if (i > y - 25 && i < y + 25)
				{
					if (j > x - 46 && j < x + 45)
					{
						m[j][i] = (char)176;
					}
				}
				else
				{
					m[j][i] = (char)219;
				}
			}
		}

	}

	void printEarlyTown(int x, int y)
	{
		for (int i = y - 25; i < y + 26; i++)
		{
			for (int j = x - 45; j < x + 46; j++)
			{
				m[j][i] = (char)219;
			}
		}
	}

	void setTowns(int count)
	{
		//srand(time(NULL));
		int reservX[10];
		int reservY[10];
		int res = count;

		int ticks = 0;

		for (int g = 0; g < count; ticks++)
		{
			for (int i = 0; i <= 15; i++)
			{
				for (int j = 0; j <= 15; j++)
				{

					int k = biomMapI[j][i];
					int rD = 0 + rand() % 100;
					if (k == 4 && g < count && j>0 && j < 15 && i>0 && i < 15 && rD>98 && biomMapI[j - 1][i] != 7 && biomMapI[j + 1][i] != 7 && biomMapI[j][i + 1] != 7 && biomMapI[j][i - 1] != 7 && biomMapI[j + 1][i + 1] != 7
						&& biomMapI[j + 1][i - 1] != 7 && biomMapI[j - 1][i + 1] != 7 && biomMapI[j - 1][i - 1] != 7 && biomMapI[j - 2][i] != 7 && biomMapI[j][i - 2] != 7 && biomMapI[j + 2][i] != 7 && biomMapI[j][i + 2] != 7)//biomMapI[j][i]
					{
						//int x = (j*89+15) + rand() % (j*89+50);
						int x = (j * 89 + 45);
						if (x <= 600)
						{
							//int y = (i*49+7) + rand() % (i*49+30);
							int y = (i * 49 + 25);
							/*while(m[x][y] == '^' || m[x][y] == '~' || m[x][y] == '*')
							{
								x = (j*89+35) + rand() % (j*89+55);
								Sleep(100);
								y = (i*49+20) + rand() % (i*49+30);
								Sleep(100);
							}*/
							printEarlyTown(x, y);
							reservX[g] = x;
							reservY[g] = y;

							biomMapI[j][i] = 7;////!!!!!!!!!
							//printf("%d, %d\n", reservX[g], reservY[g]);

							g++;
							Sleep(50);
						}

					}
				}
			}
			if (ticks > count * 100)
			{
				count = g;
				res = g;
				break;
			}
		}


		int l = 5000001;
		int idex = 0;

		for (int i = 0; i < count; i++)
		{
			for (int j = 0; j < count; j++)
			{
				if ((reservX[j] + reservY[j]) < l)
				{
					l = reservX[j] + reservY[j];

					idex = j;
				}
			}
			townsX[i] = reservX[idex];
			townsY[i] = reservY[idex];

			reservX[idex] = 9999999;
			reservY[idex] = 9999999;

			//printf("TOWN %d (%d): %d, %d\n", i, idex, townsX[i], townsY[i]);

			idex = 0;
			l = 5000001;
		}
	}

	
	void doRoad(int townCount)
	{
		int x;
		int y;
		int c = 0;

		WaveRoad* road = new WaveRoad(m, true);

		while (townCount > 1)
		{
			c = 0;
			road->len = 0;
			road->reloadMap(m, true);
			//doDefoultRoadMap();

			int xA = townsX[townCount - 1];
			int yA = townsY[townCount - 1];
			int xB = townsX[townCount - 2];
			int yB = townsY[townCount - 2];

			//printf("%d, %d\n", xA, yA);
			//printf("%d, %d\n", xB, yB);

			road->lee(xA, yA, xB, yB);

			//printf("DONE : length %d\n", road->len);

			while (c < road->len)
			{
				//printf("H\n", len);
				for (int i = 0; i < 49 * 16; i++)
				{
					for (int j = 0; j < 89 * 16; j++)
					{
						if (j == road->px[c] && i == road->py[c])
						{
							m[j - 1][i - 1] = 'R'; m[j - 1][i] = 'R'; m[j - 1][i + 1] = 'R';
							m[j][i - 1] = 'R'; m[j][i] = 'R'; m[j][i + 1] = 'R';
							m[j + 1][i - 1] = 'R'; m[j + 1][i] = 'R'; m[j + 1][i + 1] = 'R';
							c++;
						}
					}
				}
			}


			//printf("DONE\n");

			townCount--;
			//printf("%d, %d\n\n", x, y);//?????
			Sleep(50);
		}
		delete road;
	}

	~Map()
	{
		//delete biomeMap;
	}
};

