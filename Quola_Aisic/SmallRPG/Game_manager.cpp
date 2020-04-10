#include "Game_manager.h"
//using namespace audiere;
using namespace std;


Game_manager::Game_manager()
{
	GameIsRunning = true; 
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			enMap[j][i] = new EnemyMap(0);
		}
	}
}

void Game_manager::StartGame()
{
	HANDLE out_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD crd = { 120, 50 };//max 120
	SMALL_RECT src = { 0, 0, crd.X - 1, crd.Y - 1 };

	SetConsoleWindowInfo(out_handle, true, &src);
	SetConsoleScreenBufferSize(out_handle, crd);

	Game_manager game;

	printMainMenu();
	
	mapa = new Map();
	unsigned int seed = 0 + rand() % MAXLONG;

	Inventory inv;
	Drop del;
	for (int i = 0; i < 100; i++)
	{
		inv.createSlot(); // slots for 100 items
	}
	//List of all Items (for test)
	inv.addItem(del.ListOfItems[0]);
	inv.addItem(del.ListOfItems[1]);
	inv.addItem(del.ListOfItems[2]);
	inv.addItem(del.ListOfItems[3]);
	inv.addItem(del.ListOfItems[4]);
	inv.addItem(del.ListOfItems[5]);
	inv.addItem(del.ListOfItems[6]);
	inv.addItem(del.ListOfItems[7]);
	inv.addItem(del.ListOfItems[8]);
	inv.addItem(del.ListOfItems[9]);
	inv.addItem(del.ListOfItems[10]);
	inv.addItem(del.ListOfItems[11]);
	//

	Hero* hero = new Archer("Aisic");
	//welcome(hero);
	UpgradeBlock upBlock;
	
	
	COORD position;
	Sleep(500);
	RPGUtils::clearConsole();
	position.X = 0;
	position.Y = 0;
	RPGUtils::setColor(Yellow);
	SetConsoleCursorPosition(out_handle, position);
	printf("Start creating map...\n\n\n  Creating bioms...\n");
	mapa->doBiomeMap(seed);
	printf(" Done!\n\n  Do map...\n");
	mapa->fillMap(seed);
	printf(" Done!\n\n  Set towns...\n");
	mapa->setTowns(5);
	printf(" Done!\n\n  Set roads...\n");
	mapa->doRoad(5);
	printf(" Done!\n\n");
	mapa->printTown(5);
	printf("Map created!\n\n");
	Sleep(500);
	RPGUtils::clearConsole();
	position.X = 0;
	position.Y = 0;
	SetConsoleCursorPosition(out_handle, position);
	RPGUtils::setColor(White);

	

	Menu(inv, out_handle, hero, upBlock);

	Monster* monster[10] = { new Goblin(), new Skeleton(), new Slime(), new Zombie(), new Goblin(), new Vampire(),
							 new Goblin(), new Dragon(), new Devil(), new GOD() };


	int monsterCount = 0;
	while (GameIsRunning)
	{
		printBattle(inv, out_handle, hero, monster[monsterCount]);
		cin.clear();

		hero->updateStats();
		if (hero->getExp() >= hero->getMaxExp())hero->levelup();

		if (hero->getHealth() > 0 && monsterCount!=9)
		{
			Menu(inv, out_handle, hero, upBlock);
		}
		else if(hero->getHealth() <= 0)
		{
			loseGame();
			break;
		}

		if (monsterCount == 9 && hero->getHealth() > 0)
		{
			winGame();
		}
		monsterCount++;
	}
	//delete monster;
	//+ delete inventory (delete when exit)
	delete mapa;
	EndGame();
}

void Game_manager::welcome(Hero* &hero)
{
	string name = "NONE";
	int heroType = 0;
	RPGUtils::setColor(Yellow);
	printf("/////////////////////////////////////\n");
	printf("WELCOME TO LITTLE RPG!\n");
	printf("P.S. set a Pointed font :)\n");
	printf("PRINT YOUR NAME! ( Please without numbers)) )\n"); //printf("char= %c", (char)i);
	printf("Name: ");
	RPGUtils::setColor(Green);
	cin >> name;
	printf("\n");
	RPGUtils::setColor(Yellow);
	printf("CHOOSE HERO\n");
	printf("0: WIZARD!\n");
	printf("1: WARRIOR!\n");
	printf("2: ARCHER!\n");
	printf("Choice: ");
	RPGUtils::setColor(Green);
	cin >> heroType;
	//scanf_s("%d", &heroType);
	printf("\n\n");
	RPGUtils::setColor(Yellow);
	printf("\n////////////////////////////////////\n\n\n");
	cin.clear();
	RPGUtils::setColor();

	switch (heroType)
	{
	case 0:
		hero = new Wizard(name);
		break;
	case 1:
		hero = new Warrior(name);
		break;
	case 3:
		hero = new Archer(name);
	default:
		hero = new Archer(name);
		break;
	}
	hero->updateStats();
}

void Game_manager::EndGame() { GameIsRunning = false; }

void Game_manager::Menu(Inventory &inv, HANDLE out_handle, Hero* hero, UpgradeBlock &upBlock)
{
	//system("cls");

	int choic = -1;
	string sChoic = " ";
	bool menu = true;

	cin.clear();
	COORD position;


	while (menu) {
		cin.clear();

		RPGUtils::setColor(Yellow);
		printf("What to do?\n");
		printf("0: Map\n");
		printf("1: Settings\n");
		printf("2: Give stats\n");
		printf("3: Inventory\n");
		printf("4: Upgrades\n");
		RPGUtils::setColor(Red);
		printf("5: Exit\n");
		RPGUtils::setColor(Yellow);
		printf("Choice: ");

		//printf("                           ");
		//RPGUtils::setWriteCursor(7, 6);

		RPGUtils::setColor(Green);
		sChoic = " ";
		getline(cin, sChoic);
		//cin >> sChoic;
		RPGUtils::setColor();
		if (sChoic[0] >= '0' && sChoic[0] <= '9')choic = sChoic[0] - 48;
		else choic = -1;

		cin.clear();
		printf("\n\n");

		
		position.X = 0;
		position.Y = 0;
		SetConsoleCursorPosition(out_handle, position);

		switch (choic)
		{
		case 0:
			cin.clear();
			RPGUtils::clearConsole();
			position.X = 0;
			position.Y = 0;
			SetConsoleCursorPosition(out_handle, position);

			Sleep(100);
			printMaps(inv, out_handle, hero);

			cin.clear();
			RPGUtils::clearConsole();
			position.X = 0;
			position.Y = 0;
			SetConsoleCursorPosition(out_handle, position);
			break;
		case 1:
			cin.clear();
			RPGUtils::clearConsole();

			position.X = 0;
			position.Y = 0;
			SetConsoleCursorPosition(out_handle, position);

			Sleep(100);
			settings();
			RPGUtils::clearConsole();
			RPGUtils::setWriteCursor(0, 0);
			//menu = false;
			cin.clear();
			break;
		case 2:
			cin.clear();
			RPGUtils::clearConsole();

			position.X = 0;
			position.Y = 0;
			SetConsoleCursorPosition(out_handle, position);

			Sleep(100);
			hero->getSAI();
			hero->getStats();
			cin.clear();
			break;
		case 3:
			cin.clear();
			RPGUtils::clearConsole();
			position.X = 0;
			position.Y = 0;
			SetConsoleCursorPosition(out_handle, position);

			Sleep(100);
			printInventory(inv, out_handle, hero);
			cin.clear();
			break;
		case 4:
			cin.clear();
			RPGUtils::clearConsole();
			position.X = 0;
			position.Y = 0;
			SetConsoleCursorPosition(out_handle, position);

			Sleep(100);
			printUpgrage(out_handle, hero, upBlock);
			cin.clear();
			break;
		case 5:
			exit(0);
			break;
		default:
			cin.clear();
			RPGUtils::clearConsole();

			position.X = 0;
			position.Y = 0;
			SetConsoleCursorPosition(out_handle, position);
			cin.clear();
			break;
		}
	}
}

void Game_manager::printMaps(Inventory &inv, HANDLE out_handle, Hero* hero)
{

	bool exit = false;
	bool get = false;

	while (!exit)
	{
		get = true;//!!!!!!!!!!

		printEnemyOnMap();
		mapa->printEarlyMap(xFlying, yFlying, xExpand, yExpand);

		RPGUtils::setColor(White);
		enemyTrigger(inv, out_handle, hero);
	
		int k = 0;
		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 16; j++)
			{

				k = mapa->biomMapI[j][i];
				if (k == 0)
				{
					RPGUtils::setColor(Blue);
					RPGUtils::setAndDraw(j + 90, i + 1, '~');
				}
				else if (k == 1)
				{
					RPGUtils::setColor(Yellow);
					RPGUtils::setAndDraw(j + 90, i + 1, '#');
				}
				else if (k == 2)
				{
					RPGUtils::setColor(Orange);
					RPGUtils::setAndDraw(j + 90, i + 1, (char)177);
				}
				else if (k == 3)
				{
					RPGUtils::setColor(Purple);
					RPGUtils::setAndDraw(j + 90, i + 1, '*');
				}
				else if (k == 4)
				{
					RPGUtils::setColor(Green);
					RPGUtils::setAndDraw(j + 90, i + 1, 'O');
				}
				else if (k == 5)
				{
					RPGUtils::setColor(Grey);
					RPGUtils::setAndDraw(j + 90, i + 1, '^');
				}
				else if (k == 6)
				{
					RPGUtils::setColor(Red);
					RPGUtils::setAndDraw(j + 90, i + 1, '-');
				}
				else if (k == 7)
				{
					RPGUtils::setColor(LightRed);
					RPGUtils::setAndDraw(j + 90, i + 1, 'T');
				}
				else
				{
					RPGUtils::setColor(White);
					RPGUtils::setAndDraw(j + 90, i + 1, '!');
				}

				if (j == (45 + xFlying) / 89 && i == (25 + yFlying) / 49)
				{
					RPGUtils::setColor(White);
					RPGUtils::setAndDraw(j + 90, i + 1, '@');
				}
			}
		}

		RPGUtils::setColor(White);

		//setAndDraw(90, 20, " ");
		/*while (!get)
		{*/
			if (GetAsyncKeyState(VK_DOWN))
			{
				if (mapa->m[45 + xFlying][25 + yFlying + yMove] != '^' && mapa->m[45 + xFlying][25 + yFlying + yMove] != (char)127)
				{
					yFlying += yMove;//up  49
					get = true;
				}
				//yFlying += yMove;
			}

			else if (GetAsyncKeyState(VK_UP))
			{
				if (mapa->m[45 + xFlying][25 + yFlying - yMove] != '^' && mapa->m[45 + xFlying][25 + yFlying - yMove] != (char)127)
				{
					yFlying -= yMove;//down
					get = true;
				}
				//yFlying -= yMove;
			}

			else if (GetAsyncKeyState(VK_RIGHT))
			{
				if (mapa->m[45 + xFlying + xMove][25 + yFlying] != '^' && mapa->m[45 + xFlying + xMove][25 + yFlying] != (char)127)
				{
					xFlying += xMove;//left
					get = true;
				}
				//xFlying += xMove;
			}

			else if (GetAsyncKeyState(VK_LEFT))
			{
				if (mapa->m[45 + xFlying - xMove][25 + yFlying] != '^' && mapa->m[45 + xFlying - xMove][25 + yFlying] != (char)127)
				{
					xFlying -= xMove;
					get = true;
				}

				//xFlying -= xMove;
			}
			else if (GetAsyncKeyState(VK_ESCAPE))
			{
				exit = true;
				get = true;
			}
		//}
		get = false;

		int speed = (((89 / (xExpand * 2 + 1))*2*(49 / (yExpand * 2 + 1))) - 1); 
		speed = 89 / (xExpand * 2 + 1) * 49 * 2 + (49 / (yExpand * 2 + 1) * 2 * 89) - 89*2 - 49;
		speed = speed*2;

		if(speed > 0)Sleep(speed);
		
		tick++;
		if (tick>=5000)
		{
			mapa->day = !mapa->day;
			tick = 0;
		}


		RPGUtils::setColor(White);
		RPGUtils::setAndDraw(90, 24, " ");

		printf("%s:", hero->getName().c_str());

		RPGUtils::setAndDraw(90, 25, " ");
		printf("X = %d", xFlying);
		RPGUtils::setAndDraw(90, 26, " ");
		printf("Y = %d", yFlying);

		if (xFlying < 0) xFlying = 0;
		if (yFlying < 0) yFlying = 0;
		if (xFlying >= 89 * 15) xFlying = 89 * 15;
		if (yFlying >= 49 * 15) yFlying = 49 * 15;



		Sleep(0);
	}
}

void Game_manager::enemyTrigger(Inventory &inv, HANDLE out_handle, Hero* hero)
{
	int x = (xFlying+45) / 89;
	int y = (yFlying+25) / 49;
	bool end = false;
	int i = 0;

	for (int p = 0; p < enMap[x][y]->getCount(); p++)
	{
		if ((xFlying+45) == enMap[x][y]->getXOfMonster(p) && (yFlying+25) == enMap[x][y]->getYOfMonster(p))
		{	
			
			while (!end)
			{
				for (int j = 0; j < 25; j++)
				{
					RPGUtils::setAndDraw(i, j, ' ');
				}
				for (int j = 25; j < 49; j++)
				{
					RPGUtils::setAndDraw(119 - i, j, ' ');
				}
				i+=1;
				if (i == 119) end = true;
			}
			end = false;

			RPGUtils::clearConsole();
			RPGUtils::setWriteCursor(0, 0);

			if (printBattle(inv, out_handle, hero, enMap[x][y]->getMonster(p)))
			{	
				enMap[x][y]->deleteMonster(p, *mapa);
			}
			else
			{
				//if lose...
			}
		}
	}
}


void Game_manager::printEnemyOnMap()
{
	// 0 - none
	// 1 - spawned
	int plX = (45 + xFlying) / 89;
	int plY = (25 + yFlying) / 49;
	int random = 0;

	for (int i = 0; i < 16; i++)
	{	
		for (int j = 0; j < 16; j++)
		{	
			plX = (45 + xFlying) / 89;
			plY = (45 + yFlying) / 49;

			if ((j >= plX - 2 && j <= plX + 2) && (i >= plY - 2 && i <= plY + 2))//j >= plX - 1 && j <= plX + 1 && i >= plY - 1 && i <= plY + 1
			{	
				
				if (enMap[j][i]->getPolicy() == 0) 
				{
					if (j > 8)
					{	
						if (mapa->day)
						{
							random = RPGUtils::getRandom(8, 15 - 8);
						}
						else
						{
							random = RPGUtils::getRandom(15, 25 - 15);
						}
					}
					else
					{	
						if (mapa->day)
						{
							random = RPGUtils::getRandom(5, 10 - 5);
						}
						else
						{
							random = RPGUtils::getRandom(8, 15 - 8);
						}
					}
					enMap[j][i] = new EnemyMap(random);
					enMap[j][i]->setEnemies((j * 89), (i * 49), (j * 89 + 88), (i * 49 + 48), *mapa);
				}
			}
			else
			{
				enMap[j][i]->deleteMonsters(*mapa);
			}
		}
	}
}

void Game_manager::printMainMenu()
{	
	RPGUtils::clearConsole();

	int current = 0;
	bool out = false;
	bool quit = false;
	while (!out)
	{	
		//RPGUtils::clearConsole();

		drawQUOLA();
		drawAISIC();
		RPGUtils::setWriteCursor(0, 21);
		for (int i = 0; i < 120; i++)
		{
			cout << (char)205;
		}
		drawNewGame();
		drawContinue();
		drawSettings();
		drawCredits();
		drawExitGame();

		switch (current)
		{
		case 0:
			drawCurrentCursor(33, 23 + 2);
			drawOppCurrentCursor(81, 23 + 2);
			drawVoid(31, 28 + 2);
			drawVoid(83, 28 + 2);
			drawVoid(31, 33 + 2);
			drawVoid(83, 33 + 2);
			drawVoid(34, 38 + 2);
			drawVoid(80, 38 + 2);
			drawVoid(43, 43 + 2);
			drawVoid(71, 43 + 2);
			break;
		case 1:
			if (existLastGame)
			{
				drawCurrentCursor(31, 28 + 2);
				drawOppCurrentCursor(83, 28 + 2);

				drawVoid(33, 23 + 2);
				drawVoid(81, 23 + 2);
				drawVoid(31, 33 + 2);
				drawVoid(83, 33 + 2);
				drawVoid(34, 38 + 2);
				drawVoid(80, 38 + 2);
				drawVoid(43, 43 + 2);
				drawVoid(71, 43 + 2);
				break;
			}
		case 2:
			drawCurrentCursor(31, 33 + 2);
			drawOppCurrentCursor(83, 33 + 2);

			drawVoid(33, 23 + 2);
			drawVoid(81, 23 + 2);
			drawVoid(31, 28 + 2);
			drawVoid(83, 28 + 2);
			drawVoid(34, 38 + 2);
			drawVoid(80, 38 + 2);
			drawVoid(43, 43 + 2);
			drawVoid(71, 43 + 2);
			break;
		case 3:
			drawCurrentCursor(34, 38 + 2);
			drawOppCurrentCursor(80, 38 + 2);

			drawVoid(33, 23 + 2);
			drawVoid(81, 23 + 2);
			drawVoid(31, 28 + 2);
			drawVoid(83, 28 + 2);
			drawVoid(31, 33 + 2);
			drawVoid(83, 33 + 2);
			drawVoid(43, 43 + 2);
			drawVoid(71, 43 + 2);
			break;
		case 4:
			drawCurrentCursor(43, 43 + 2);
			drawOppCurrentCursor(71, 43 + 2);

			drawVoid(33, 23 + 2);
			drawVoid(81, 23 + 2);
			drawVoid(31, 28 + 2);
			drawVoid(83, 28 + 2);
			drawVoid(31, 33 + 2);
			drawVoid(83, 33 + 2);
			drawVoid(34, 38 + 2);
			drawVoid(80, 38 + 2);
			break;
		default:
			break;
		}
		RPGUtils::setWriteCursor(119, 49);

		quit = false;
		while (!quit)
		{
			if (GetAsyncKeyState(0x28))//DOWN
			{
				if (current < 4) {
					RPGUtils::setWriteCursor(0, 0);

					current++;
					quit = true;
					Sleep(100);
				}
			}
			else if (GetAsyncKeyState(0x26))//UP
			{
				if (current > 0) {
					RPGUtils::setWriteCursor(0, 0);

					current--;
					quit = true;
					Sleep(100);
				}
			}
			else if (GetAsyncKeyState(VK_RETURN))
			{
				switch (current)
				{
				case 0:
					out = true;
					quit = true;
					Sleep(100);
					//new game
					break;
				case 1:
					if (existLastGame)
					{
						out = true;
						quit = true;
						//continue game
						Sleep(100);
						break;
					}	
				case 2:
					cin.clear();
					settings();
					RPGUtils::clearConsole();
					//settings
					Sleep(100);
					break;
				case 3:
					credits();
					//credits
					Sleep(100);
					break;
				case 4:
					out = true;
					Sleep(100);
					EndGame();
					break;
				default:
					break;
				}

				//quit = true;
				
				for (int i = 0; i < 1; i++)
				{
					 
				}

				cin.clear();
			}
		}

	}
	RPGUtils::clearConsole();
	RPGUtils::setWriteCursor(0, 0);
}

void Game_manager::settings()
{	
	int cursorPos = -1;
	bool out = false;
	bool get = false;

	RPGUtils::setColor();
	RPGUtils::clearConsole();

	while(!out)
	{
		RPGUtils::setWriteCursor(40, 5);
		printf("SETTINGS");

		RPGUtils::setWriteCursor(40, 10);
		if (cursorPos == 0)cout << (char)16;
		else cout << " ";
		printf("Map settings");

		RPGUtils::setWriteCursor(119, 49);
		cin.clear();
		while (!get)
		{
			cin.clear();
			if (GetAsyncKeyState(0x26))//UP
			{
				if (cursorPos > 0) {

					cursorPos --;
					get = true;
					Sleep(100);
				}
			}
			else if (GetAsyncKeyState(0x28))//DOWN
			{
				if (cursorPos < 1) {

					cursorPos ++;
					get = true;
					Sleep(100);
				}
			}
			else if (GetAsyncKeyState(VK_RETURN))//DOWN
			{	
				cin.clear();
				switch (cursorPos)
				{
				case 0:
					settingsMap();
				default:
					break;
				}
				get = true;
			}
			else if (GetAsyncKeyState(0x1B))//esc
			{
				get = true;
				out = true;
				Sleep(100);
			}
			cin.clear();
		}
		get = false;
	}
}

void Game_manager::settingsMap()
{
	bool out = false;
	bool get = false;
	int cursorPos = 0;

	RPGUtils::clearConsole();
	RPGUtils::setWriteCursor(0, 0);
	cin.clear();
	while (!out)
	{	
		cin.clear();
		RPGUtils::setColor(White);

		RPGUtils::setWriteCursor(100, 23);
		printf("X: ");
		if (cursorPos == 0)cout << (char)16;
		else cout << " ";
		printf("  %d", xExpand);

		RPGUtils::setWriteCursor(100, 27);
		printf("Y: ");
		if (cursorPos == 1)cout << (char)16;
		else cout << " ";
		printf("  %d", yExpand);

		for (int i = 0; i < 49; i++)
		{
			for (int j = 0; j < 89; j++)
			{	
				if (i >= 24 - yExpand && i < 25 + yExpand && j >= 44 - xExpand && j < 45 + xExpand)
				{
					if (i == 24 - yExpand || i == 25 + yExpand - 1)
					{
						RPGUtils::setColor(Red);
						RPGUtils::setAndDraw(j, i, (char)219);
					}
					else if (j == 44 - xExpand || j == 45 + xExpand - 1)
					{
						RPGUtils::setColor(Red);
						RPGUtils::setAndDraw(j, i, (char)219);
					}
					else
					{
						RPGUtils::setColor(Black);
						RPGUtils::setAndDraw(j, i, (char)219);
					}
				}
				else
				{
					RPGUtils::setColor(Black);
					RPGUtils::setAndDraw(j, i, (char)219);
				}
			}
		}

		RPGUtils::setWriteCursor(119, 49);
		cin.clear();
		while (!get)
		{
			cin.clear();
			if (GetAsyncKeyState(0x26))//UP
			{
				if (cursorPos == 1) {

					cursorPos = 0;
					get = true;
					//Sleep(100);
				}
			}
			else if (GetAsyncKeyState(0x28))//DOWN
			{
				if (cursorPos == 0) {

					cursorPos = 1;
					get = true;
					//Sleep(100);
				}
			}
			else if (GetAsyncKeyState(0x25))//left
			{
				if (cursorPos == 0 && xExpand>11)
				{
					xExpand--;
					get = true;
					//Sleep(100);
				}
				else if(cursorPos == 1 && yExpand > 6)
				{
					yExpand--;
					get = true;
					//Sleep(100);
				}
			}
			else if (GetAsyncKeyState(0x27))//right
			{
				if (cursorPos == 0 && xExpand < 44)
				{
					xExpand++;
					get = true;
					//Sleep(100);
				}
				else if (cursorPos == 1 && yExpand < 24)
				{
					yExpand++;
					get = true;
					//Sleep(100);
				}
			}
			else if (GetAsyncKeyState(0x1B))//esc
			{
				get = true;
				out = true;
				Sleep(100);
			}
			cin.clear();

		}
		RPGUtils::clearConsole();
		get = false;
	}
	RPGUtils::setColor(White);
}

void Game_manager::credits()
{	
	RPGUtils::clearConsole();

	RPGUtils::setWriteCursor(50, 5);
	printf("Quola: Aisic");
	RPGUtils::setWriteCursor(40, 15);
	printf("Game designer & game director:");
	RPGUtils::setWriteCursor(45, 17);
	printf("Evgeny \"JohnRam\" Ageev");
	RPGUtils::setWriteCursor(45, 49);
	printf("Develop by JohnRam in 2019");

	cin.clear();
	if (GetAsyncKeyState(0x1B))//esc
	{
		return;
		Sleep(100);
	}
	cin.clear();
}
////////////////FOR MENU////////////////////

void Game_manager::drawQUOLA()
{
	RPGUtils::setWriteCursor(29, 4 - 3);
	cout << (char)219 << (char)219 << (char)219 << (char)219;

	RPGUtils::setWriteCursor(28, 5 - 3);
	cout << (char)219;
	RPGUtils::setWriteCursor(33, 5 - 3);
	cout << (char)219;
	RPGUtils::setWriteCursor(28, 6 - 3);
	cout << (char)219;
	RPGUtils::setWriteCursor(33, 6 - 3);
	cout << (char)219;

	RPGUtils::setWriteCursor(27, 7 - 3);
	cout << (char)219;
	RPGUtils::setWriteCursor(34, 7 - 3);
	cout << (char)219;
	RPGUtils::setWriteCursor(27, 8 - 3);
	cout << (char)219;
	RPGUtils::setWriteCursor(34, 8 - 3);
	cout << (char)219;
	RPGUtils::setWriteCursor(27, 9 - 3);
	cout << (char)219;
	RPGUtils::setWriteCursor(34, 9 - 3);
	cout << (char)219;
	RPGUtils::setWriteCursor(27, 10 - 3);
	cout << (char)219;
	RPGUtils::setWriteCursor(34, 10 - 3);
	cout << (char)219;
	RPGUtils::setWriteCursor(27, 11 - 3);
	cout << (char)219;
	RPGUtils::setWriteCursor(34, 11 - 3);
	cout << (char)219;

	RPGUtils::setWriteCursor(28, 12 - 3);
	cout << (char)219;
	RPGUtils::setWriteCursor(33, 12 - 3);
	cout << (char)219;
	RPGUtils::setWriteCursor(28, 13 - 3);
	cout << (char)219;
	RPGUtils::setWriteCursor(33, 13 - 3);
	cout << (char)219;
	RPGUtils::setWriteCursor(34, 13 - 3);
	cout << (char)219;

	RPGUtils::setWriteCursor(29, 14 - 3);
	cout << (char)219 << (char)219 << (char)219 << (char)219;

	RPGUtils::setWriteCursor(34, 14 - 3);
	cout << (char)219 << (char)219 << (char)219;

	///////////////////////////////////////     U
	for (int i = 0; i < 5; i++)
	{
		RPGUtils::setWriteCursor(40, 4 + i - 3);
		cout << (char)219;
		RPGUtils::setWriteCursor(49, 4 + i - 3);
		cout << (char)219;
	}
	for (int i = 0; i < 3; i++)
	{
		RPGUtils::setWriteCursor(41, 9 + i - 3);
		cout << (char)219;
		RPGUtils::setWriteCursor(48, 9 + i - 3);
		cout << (char)219;
	}
	for (int i = 0; i < 2; i++)
	{
		RPGUtils::setWriteCursor(42, 12 + i - 3);
		cout << (char)219;
		RPGUtils::setWriteCursor(47, 12 + i - 3);
		cout << (char)219;
	}
	RPGUtils::setWriteCursor(43, 14 - 3);
	cout << (char)219 << (char)219 << (char)219 << (char)219;


	///////////////////////////  O

	RPGUtils::setWriteCursor(55, 4 - 3);
	cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219;

	RPGUtils::setWriteCursor(54, 5 - 3);
	cout << (char)219;
	RPGUtils::setWriteCursor(61, 5 - 3);
	cout << (char)219;
	RPGUtils::setWriteCursor(54, 6 - 3);
	cout << (char)219;
	RPGUtils::setWriteCursor(61, 6 - 3);
	cout << (char)219;

	for (int i = 0; i < 5; i++)
	{
		RPGUtils::setWriteCursor(53, 7 + i - 3);
		cout << (char)219;
		RPGUtils::setWriteCursor(62, 7 + i - 3);
		cout << (char)219;
	}

	RPGUtils::setWriteCursor(54, 12 - 3);
	cout << (char)219;
	RPGUtils::setWriteCursor(61, 12 - 3);
	cout << (char)219;
	RPGUtils::setWriteCursor(54, 13 - 3);
	cout << (char)219;
	RPGUtils::setWriteCursor(61, 13 - 3);
	cout << (char)219;

	RPGUtils::setWriteCursor(55, 14 - 3);
	cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219;

	///////////////    L

	RPGUtils::setWriteCursor(66, 4 - 3);
	cout << (char)219 << (char)219 << (char)219;


	for (int i = 0; i < 6; i++)
	{
		RPGUtils::setWriteCursor(66, 5 + i - 3);
		cout << (char)219;
	}
	RPGUtils::setWriteCursor(74, 11 - 3);
	cout << (char)219;
	for (int i = 0; i < 3; i++)
	{
		RPGUtils::setWriteCursor(67, 11 + i - 3);
		cout << (char)219;
		RPGUtils::setWriteCursor(75, 11 + i - 3);
		cout << (char)219;
	}
	RPGUtils::setWriteCursor(68, 14 - 3);
	cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219;


	/////// A

	for (int i = 0; i < 3; i++)
	{
		RPGUtils::setWriteCursor(79, 14 - i - 3);
		cout << (char)219;
		RPGUtils::setWriteCursor(88, 14 - i - 3);
		cout << (char)219;
	}
	for (int i = 0; i < 2; i++)
	{
		RPGUtils::setWriteCursor(80, 11 - i - 3);
		cout << (char)219;
		RPGUtils::setWriteCursor(87, 11 - i - 3);
		cout << (char)219;
	}
	for (int i = 0; i < 2; i++)
	{
		RPGUtils::setWriteCursor(81, 9 - i - 3);
		cout << (char)219;
		RPGUtils::setWriteCursor(86, 9 - i - 3);
		cout << (char)219;
	}
	for (int i = 0; i < 3; i++)
	{
		RPGUtils::setWriteCursor(82, 7 - i - 3);
		cout << (char)219;
		RPGUtils::setWriteCursor(85, 7 - i - 3);
		cout << (char)219;
	}
	RPGUtils::setWriteCursor(81, 11 - 3);
	cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219 << (char)219;
	RPGUtils::setWriteCursor(83, 4 - 3);
	cout << (char)219 << (char)219;


	/////////    :

	RPGUtils::setWriteCursor(92, 11 - 3);
	cout << (char)219;

	RPGUtils::setWriteCursor(92, 7 - 3);
	cout << (char)219;
}

void Game_manager::drawAISIC()
{
	/////////////////      A
	RPGUtils::setWriteCursor(43 + 2, 15 - 2);
	cout << (char)219;

	for (int i = 0; i < 3; i++)
	{
		RPGUtils::setWriteCursor(42 + 2, 16 + i - 2);
		cout << (char)219;
		RPGUtils::setWriteCursor(44 + 2, 16 + i - 2);
		cout << (char)219;
	}
	RPGUtils::setWriteCursor(43 + 2, 18 - 2);
	cout << (char)219;
	for (int i = 0; i < 2; i++)
	{
		RPGUtils::setWriteCursor(41 + 2, 19 + i - 2);
		cout << (char)219;
		RPGUtils::setWriteCursor(45 + 2, 19 + i - 2);
		cout << (char)219;
	}

	////////////////            I

	RPGUtils::setWriteCursor(48 + 2, 15 - 2);
	cout << (char)219 << (char)219 << (char)219;
	for (int i = 0; i < 4; i++)
	{
		RPGUtils::setWriteCursor(49 + 2, 16 + i - 2);
		cout << (char)219;
	}
	RPGUtils::setWriteCursor(47 + 2, 20 - 2);
	cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219;

	/////////////////    S
	RPGUtils::setWriteCursor(54 + 2, 15 - 2);
	cout << (char)219 << (char)219 << (char)219;

	RPGUtils::setWriteCursor(53 + 2, 16 - 2);
	cout << (char)219;
	RPGUtils::setWriteCursor(57 + 2, 16 - 2);
	cout << (char)219;

	RPGUtils::setWriteCursor(53 + 2, 17 - 2);
	cout << (char)219;

	RPGUtils::setWriteCursor(54 + 2, 18 - 2);
	cout << (char)219 << (char)219 << (char)219;

	RPGUtils::setWriteCursor(57 + 2, 19 - 2);
	cout << (char)219;

	RPGUtils::setWriteCursor(53 + 2, 20 - 2);
	cout << (char)219 << (char)219 << (char)219 << (char)219;

	///////////    I

	RPGUtils::setWriteCursor(59 + 2, 15 - 2);
	cout << (char)219 << (char)219 << (char)219 << (char)219 << (char)219;
	for (int i = 0; i < 4; i++)
	{
		RPGUtils::setWriteCursor(61 + 2, 16 + i - 2);
		cout << (char)219;
	}
	RPGUtils::setWriteCursor(60 + 2, 20 - 2);
	cout << (char)219 << (char)219 << (char)219;


	////////////   C

	RPGUtils::setWriteCursor(66 + 2, 15 - 2);
	cout << (char)219 << (char)219 << (char)219;

	RPGUtils::setWriteCursor(69 + 2, 16 - 2);
	cout << (char)219;

	for (int i = 0; i < 4; i++)
	{
		RPGUtils::setWriteCursor(65 + 2, 16 + i - 2);
		cout << (char)219;
	}

	RPGUtils::setWriteCursor(69 + 2, 19 - 2);
	cout << (char)219;

	RPGUtils::setWriteCursor(66 + 2, 20 - 2);
	cout << (char)219 << (char)219 << (char)219;

}

void Game_manager::drawNewGame()
{
	//////////////////  N
	for (int i = 0; i < 4; i++)
	{
		RPGUtils::setWriteCursor(37, 22 + i + 2);
		cout << (char)219;
	}
	RPGUtils::setWriteCursor(38, 23 + 2);
	cout << (char)219;
	RPGUtils::setWriteCursor(39, 24 + 2);
	cout << (char)219;
	for (int i = 0; i < 4; i++)
	{
		RPGUtils::setWriteCursor(40, 22 + i + 2);
		cout << (char)219;
	}

	/////////////////// E

	RPGUtils::setWriteCursor(43, 22 + 2);
	cout << (char)219 << (char)219 << (char)219 << (char)219;

	for (int i = 0; i < 2; i++)
	{
		RPGUtils::setWriteCursor(43, 23 + i + 2);
		cout << (char)219;
	}

	RPGUtils::setWriteCursor(44, 23 + 2);
	cout << (char)220 << (char)220;
	RPGUtils::setWriteCursor(44, 24 + 2);
	cout << (char)223 << (char)223;

	RPGUtils::setWriteCursor(43, 25 + 2);
	cout << (char)219 << (char)219 << (char)219 << (char)219;

	/////////////////  W

	for (int i = 0; i < 3; i++)
	{
		RPGUtils::setWriteCursor(49, 22 + i + 2);
		cout << (char)219;
		RPGUtils::setWriteCursor(52, 22 + i + 2);
		cout << (char)219;
	}

	RPGUtils::setWriteCursor(50, 23 + 2);
	cout << (char)222 << (char)221;

	for (int i = 0; i < 2; i++)
	{
		RPGUtils::setWriteCursor(50, 24 + i + 2);
		cout << (char)219;
		RPGUtils::setWriteCursor(51, 24 + i + 2);
		cout << (char)219;
	}

	////////////////   G
	RPGUtils::setWriteCursor(58, 22 + 2);
	cout << (char)219 << (char)219 << (char)219;

	for (int i = 0; i < 2; i++)
	{
		RPGUtils::setWriteCursor(57, 23 + i + 2);
		cout << (char)219;
	}

	RPGUtils::setWriteCursor(59, 24 + 2);
	cout << (char)223;

	RPGUtils::setWriteCursor(60, 24 + 2);
	cout << (char)219;

	RPGUtils::setWriteCursor(58, 25 + 2);
	cout << (char)219 << (char)219 << (char)219;


	////////////// A
	RPGUtils::setWriteCursor(64, 22 + 2);
	cout << (char)219 << (char)219;

	RPGUtils::setWriteCursor(64, 24 + 2);
	cout << (char)219 << (char)219;

	for (int i = 0; i < 3; i++)
	{
		RPGUtils::setWriteCursor(63, 23 + i + 2);
		cout << (char)219;
		RPGUtils::setWriteCursor(66, 23 + i + 2);
		cout << (char)219;
	}
	/////////////////// M

	for (int i = 0; i < 4; i++)
	{
		RPGUtils::setWriteCursor(69, 22 + i + 2);
		cout << (char)219;
		RPGUtils::setWriteCursor(72, 22 + i + 2);
		cout << (char)219;
	}
	RPGUtils::setWriteCursor(70, 22 + 2);
	cout << (char)220 << (char)220;

	RPGUtils::setWriteCursor(70, 23 + 2);
	cout << (char)222 << (char)221;

	/////// E

	RPGUtils::setWriteCursor(75, 22 + 2);
	cout << (char)219 << (char)219 << (char)219 << (char)219;

	for (int i = 0; i < 2; i++)
	{
		RPGUtils::setWriteCursor(75, 23 + i + 2);
		cout << (char)219;
	}

	RPGUtils::setWriteCursor(76, 23 + 2);
	cout << (char)220 << (char)220;
	RPGUtils::setWriteCursor(76, 24 + 2);
	cout << (char)223 << (char)223;

	RPGUtils::setWriteCursor(75, 25 + 2);
	cout << (char)219 << (char)219 << (char)219 << (char)219;
}

void Game_manager::drawContinue()
{
	///////////////////  C
	RPGUtils::setWriteCursor(34 + 2, 27 + 2);
	cout << (char)219 << (char)219 << (char)219;

	for (int i = 0; i < 2; i++)
	{
		RPGUtils::setWriteCursor(33 + 2, 28 + i + 2);
		cout << (char)219;
	}
	RPGUtils::setWriteCursor(34 + 2, 30 + 2);
	cout << (char)219 << (char)219 << (char)219;

	//////////////O

	RPGUtils::setWriteCursor(40 + 2, 27 + 2);
	cout << (char)219 << (char)219;
	for (int i = 0; i < 2; i++)
	{
		RPGUtils::setWriteCursor(39 + 2, 28 + i + 2);
		cout << (char)219;
		RPGUtils::setWriteCursor(42 + 2, 28 + i + 2);
		cout << (char)219;
	}
	RPGUtils::setWriteCursor(40 + 2, 30 + 2);
	cout << (char)219 << (char)219;

	/////////  N
	for (int i = 0; i < 4; i++)
	{
		RPGUtils::setWriteCursor(45 + 2, 27 + i + 2);
		cout << (char)219;
	}
	RPGUtils::setWriteCursor(46 + 2, 28 + 2);
	cout << (char)219;
	RPGUtils::setWriteCursor(47 + 2, 29 + 2);
	cout << (char)219;
	for (int i = 0; i < 4; i++)
	{
		RPGUtils::setWriteCursor(48 + 2, 27 + i + 2);
		cout << (char)219;
	}
	//////////// T
	RPGUtils::setWriteCursor(51 + 2, 27 + 2);
	cout << (char)219 << (char)219 << (char)219 << (char)219;
	for (int i = 0; i < 3; i++)
	{
		RPGUtils::setWriteCursor(52 + 2, 28 + i + 2);
		cout << (char)222;
		RPGUtils::setWriteCursor(53 + 2, 28 + i + 2);
		cout << (char)221;
	}

	///////// I

	RPGUtils::setWriteCursor(57 + 2, 27 + 2);
	cout << (char)219 << (char)219 << (char)219 << (char)219;
	for (int i = 0; i < 2; i++)
	{
		RPGUtils::setWriteCursor(58 + 2, 28 + i + 2);
		cout << (char)222;
		RPGUtils::setWriteCursor(59 + 2, 28 + i + 2);
		cout << (char)221;
	}
	RPGUtils::setWriteCursor(57 + 2, 30 + 2);
	cout << (char)219 << (char)219 << (char)219 << (char)219;

	/////// N

	for (int i = 0; i < 4; i++)
	{
		RPGUtils::setWriteCursor(63 + 2, 27 + i + 2);
		cout << (char)219;
	}
	RPGUtils::setWriteCursor(64 + 2, 28 + 2);
	cout << (char)219;
	RPGUtils::setWriteCursor(65 + 2, 29 + 2);
	cout << (char)219;
	for (int i = 0; i < 4; i++)
	{
		RPGUtils::setWriteCursor(66 + 2, 27 + i + 2);
		cout << (char)219;
	}

	//////////// U

	for (int i = 0; i < 3; i++)
	{
		RPGUtils::setWriteCursor(68 + 3, 27 + i + 2);
		cout << (char)219;
		RPGUtils::setWriteCursor(71 + 3, 27 + i + 2);
		cout << (char)219;
	}
	RPGUtils::setWriteCursor(69 + 3, 30 + 2);
	cout << (char)219 << (char)219;

	//////// E

	RPGUtils::setWriteCursor(74 + 3, 27 + 2);
	cout << (char)219 << (char)219 << (char)219 << (char)219;

	for (int i = 0; i < 2; i++)
	{
		RPGUtils::setWriteCursor(74 + 3, 28 + i + 2);
		cout << (char)219;
	}

	RPGUtils::setWriteCursor(75 + 3, 28 + 2);
	cout << (char)220 << (char)220;
	RPGUtils::setWriteCursor(75 + 3, 29 + 2);
	cout << (char)223 << (char)223;

	RPGUtils::setWriteCursor(74 + 3, 30 + 2);
	cout << (char)219 << (char)219 << (char)219 << (char)219;
}

void Game_manager::drawSettings()
{
	////////////// S
	RPGUtils::setWriteCursor(36, 32 + 2);
	cout << (char)219 << (char)219 << (char)219;
	RPGUtils::setWriteCursor(35, 33 + 2);
	cout << (char)219;
	RPGUtils::setWriteCursor(36, 34 + 2);
	cout << (char)223 << (char)223;
	RPGUtils::setWriteCursor(38, 34 + 2);
	cout << (char)219;
	RPGUtils::setWriteCursor(35, 35 + 2);
	cout << (char)219 << (char)219 << (char)219;

	////////////// E

	RPGUtils::setWriteCursor(41, 32 + 2);
	cout << (char)219 << (char)219 << (char)219 << (char)219;

	for (int i = 0; i < 2; i++)
	{
		RPGUtils::setWriteCursor(41, 33 + i + 2);
		cout << (char)219;
	}

	RPGUtils::setWriteCursor(42, 33 + 2);
	cout << (char)220 << (char)220;
	RPGUtils::setWriteCursor(42, 34 + 2);
	cout << (char)223 << (char)223;

	RPGUtils::setWriteCursor(41, 35 + 2);
	cout << (char)219 << (char)219 << (char)219 << (char)219;

	/////////// T

	RPGUtils::setWriteCursor(47, 32 + 2);
	cout << (char)219 << (char)219 << (char)219 << (char)219;
	for (int i = 0; i < 3; i++)
	{
		RPGUtils::setWriteCursor(48, 33 + i + 2);
		cout << (char)222;
		RPGUtils::setWriteCursor(49, 33 + i + 2);
		cout << (char)221;
	}

	////////// T

	RPGUtils::setWriteCursor(53, 32 + 2);
	cout << (char)219 << (char)219 << (char)219 << (char)219;
	for (int i = 0; i < 3; i++)
	{
		RPGUtils::setWriteCursor(54, 33 + i + 2);
		cout << (char)222;
		RPGUtils::setWriteCursor(55, 33 + i + 2);
		cout << (char)221;
	}

	///////////// I

	RPGUtils::setWriteCursor(59, 32 + 2);
	cout << (char)219 << (char)219 << (char)219 << (char)219;
	for (int i = 0; i < 2; i++)
	{
		RPGUtils::setWriteCursor(60, 33 + i + 2);
		cout << (char)222;
		RPGUtils::setWriteCursor(61, 33 + i + 2);
		cout << (char)221;
	}
	RPGUtils::setWriteCursor(59, 35 + 2);
	cout << (char)219 << (char)219 << (char)219 << (char)219;

	////////////// N
	for (int i = 0; i < 4; i++)
	{
		RPGUtils::setWriteCursor(65, 32 + i + 2);
		cout << (char)219;
	}
	RPGUtils::setWriteCursor(66, 33 + 2);
	cout << (char)219;
	RPGUtils::setWriteCursor(67, 34 + 2);
	cout << (char)219;
	for (int i = 0; i < 4; i++)
	{
		RPGUtils::setWriteCursor(68, 32 + i + 2);
		cout << (char)219;
	}

	/////////// G

	RPGUtils::setWriteCursor(72, 32 + 2);
	cout << (char)219 << (char)219 << (char)219;

	for (int i = 0; i < 2; i++)
	{
		RPGUtils::setWriteCursor(71, 33 + i + 2);
		cout << (char)219;
	}

	RPGUtils::setWriteCursor(73, 34 + 2);
	cout << (char)223;

	RPGUtils::setWriteCursor(74, 34 + 2);
	cout << (char)219;

	RPGUtils::setWriteCursor(72, 35 + 2);
	cout << (char)219 << (char)219 << (char)219;

	////////////// S

	RPGUtils::setWriteCursor(78, 32 + 2);
	cout << (char)219 << (char)219 << (char)219;
	RPGUtils::setWriteCursor(77, 33 + 2);
	cout << (char)219;
	RPGUtils::setWriteCursor(78, 34 + 2);
	cout << (char)223 << (char)223;
	RPGUtils::setWriteCursor(80, 34 + 2);
	cout << (char)219;
	RPGUtils::setWriteCursor(77, 35 + 2);
	cout << (char)219 << (char)219 << (char)219;
}

void Game_manager::drawCredits()
{
	//////////// C
	RPGUtils::setWriteCursor(39, 37 + 2);
	cout << (char)219 << (char)219 << (char)219;

	for (int i = 0; i < 2; i++)
	{
		RPGUtils::setWriteCursor(38, 38 + i + 2);
		cout << (char)219;
	}
	RPGUtils::setWriteCursor(39, 40 + 2);
	cout << (char)219 << (char)219 << (char)219;

	////R
	RPGUtils::setWriteCursor(44, 37 + 2);
	cout << (char)219 << (char)219 << (char)219;

	RPGUtils::setWriteCursor(44, 38 + 2);
	cout << (char)219;
	RPGUtils::setWriteCursor(46, 38 + 2);
	cout << (char)219;

	RPGUtils::setWriteCursor(44, 39 + 2);
	cout << (char)219 << (char)219 << (char)219 << (char)219;

	RPGUtils::setWriteCursor(44, 40 + 2);
	cout << (char)219;
	RPGUtils::setWriteCursor(47, 40 + 2);
	cout << (char)219;

	//////////// E

	RPGUtils::setWriteCursor(50, 37 + 2);
	cout << (char)219 << (char)219 << (char)219 << (char)219;

	for (int i = 0; i < 2; i++)
	{
		RPGUtils::setWriteCursor(50, 38 + i + 2);
		cout << (char)219;
	}

	RPGUtils::setWriteCursor(51, 38 + 2);
	cout << (char)220 << (char)220;
	RPGUtils::setWriteCursor(51, 39 + 2);
	cout << (char)223 << (char)223;

	RPGUtils::setWriteCursor(50, 40 + 2);
	cout << (char)219 << (char)219 << (char)219 << (char)219;

	////// D

	RPGUtils::setWriteCursor(56, 37 + 2);
	cout << (char)219 << (char)219 << (char)219;
	for (int i = 0; i < 2; i++)
	{
		RPGUtils::setWriteCursor(56, 38 + i + 2);
		cout << (char)219;
		RPGUtils::setWriteCursor(59, 38 + i + 2);
		cout << (char)219;
	}
	RPGUtils::setWriteCursor(56, 40 + 2);
	cout << (char)219 << (char)219 << (char)219;

	//////////  I
	RPGUtils::setWriteCursor(62, 37 + 2);
	cout << (char)219 << (char)219 << (char)219 << (char)219;
	for (int i = 0; i < 2; i++)
	{
		RPGUtils::setWriteCursor(63, 38 + i + 2);
		cout << (char)222;
		RPGUtils::setWriteCursor(64, 38 + i + 2);
		cout << (char)221;
	}
	RPGUtils::setWriteCursor(62, 40 + 2);
	cout << (char)219 << (char)219 << (char)219 << (char)219;

	////////////T
	RPGUtils::setWriteCursor(68, 37 + 2);
	cout << (char)219 << (char)219 << (char)219 << (char)219;
	for (int i = 0; i < 3; i++)
	{
		RPGUtils::setWriteCursor(69, 38 + i + 2);
		cout << (char)222;
		RPGUtils::setWriteCursor(70, 38 + i + 2);
		cout << (char)221;
	}

	///////   S
	RPGUtils::setWriteCursor(75, 37 + 2);
	cout << (char)219 << (char)219 << (char)219;
	RPGUtils::setWriteCursor(74, 38 + 2);
	cout << (char)219;
	RPGUtils::setWriteCursor(75, 39 + 2);
	cout << (char)223 << (char)223;
	RPGUtils::setWriteCursor(77, 39 + 2);
	cout << (char)219;
	RPGUtils::setWriteCursor(74, 40 + 2);
	cout << (char)219 << (char)219 << (char)219;
}

void Game_manager::drawExitGame()
{
	/////////////   E
	RPGUtils::setWriteCursor(47, 42 + 2);
	cout << (char)219 << (char)219 << (char)219 << (char)219;

	for (int i = 0; i < 2; i++)
	{
		RPGUtils::setWriteCursor(47, 43 + i + 2);
		cout << (char)219;
	}

	RPGUtils::setWriteCursor(48, 43 + 2);
	cout << (char)220 << (char)220;
	RPGUtils::setWriteCursor(48, 44 + 2);
	cout << (char)223 << (char)223;

	RPGUtils::setWriteCursor(47, 45 + 2);
	cout << (char)219 << (char)219 << (char)219 << (char)219;

	//////////X
	RPGUtils::setWriteCursor(53, 42 + 2);
	cout << (char)219 << "  " << (char)219;
	for (int i = 0; i < 2; i++)
	{
		RPGUtils::setWriteCursor(54, 43 + i + 2);
		cout << (char)219 << (char)219;
	}
	RPGUtils::setWriteCursor(53, 45 + 2);
	cout << (char)219 << "  " << (char)219;

	///////////// I
	RPGUtils::setWriteCursor(59, 42 + 2);
	cout << (char)219 << (char)219 << (char)219 << (char)219;
	for (int i = 0; i < 2; i++)
	{
		RPGUtils::setWriteCursor(60, 43 + i + 2);
		cout << (char)222;
		RPGUtils::setWriteCursor(61, 43 + i + 2);
		cout << (char)221;
	}
	RPGUtils::setWriteCursor(59, 45 + 2);
	cout << (char)219 << (char)219 << (char)219 << (char)219;

	///////////// T
	RPGUtils::setWriteCursor(65, 42 + 2);
	cout << (char)219 << (char)219 << (char)219 << (char)219;
	for (int i = 0; i < 3; i++)
	{
		RPGUtils::setWriteCursor(66, 43 + i + 2);
		cout << (char)222;
		RPGUtils::setWriteCursor(67, 43 + i + 2);
		cout << (char)221;
	}
}

void Game_manager::drawCurrentCursor(int x, int y)
{
	RPGUtils::setWriteCursor(x, y);
	cout << (char)219 << (char)220;
	RPGUtils::setWriteCursor(x, y+1);
	cout << (char)219 << (char)223;
}

void Game_manager::drawOppCurrentCursor(int x, int y)
{
	RPGUtils::setWriteCursor(x, y);
	cout << (char)220 << (char)219;
	RPGUtils::setWriteCursor(x, y + 1);
	cout << (char)223 << (char)219;
}

void Game_manager::drawVoid(int x, int y)
{
	RPGUtils::setWriteCursor(x, y);
	cout << ' ' << ' ';
	RPGUtils::setWriteCursor(x, y + 1);
	cout << ' ' << ' ';
}

/////////////////////////////////////////////

void Game_manager::battleStats(Hero* hero, Monster* monster)
{
	printf("%s:\nHP: %d\nMP: %d\n\n", hero->getName().c_str(), hero->getHealth(), hero->getMana());
	printf("%s:\nHP: %d\n\n", monster->getName().c_str(), monster->getHealth());
}

void Game_manager::endl()
{
	for (int i = 0; i < 40; i++) printf("%c", (char)196);//clear line!//196
	printf("%c", (char)185);//NOT need to fill all of next (FREE LINE) 179 180
}

void Game_manager::winGame()
{
	RPGUtils::setColor(Orange);
	printf("\n\n\n//////////////////////\n");
	printf("YOU WIN THE GAME, MINE CONGRATULATIONS!\n");
	printf("//////////////////////////\n\n\n");
	RPGUtils::setColor();
	Sleep(2000);
	EndGame();
}
void Game_manager::loseGame()
{
	printf("\n\n\n//////////////////////\n");
	printf("YOU LOSE...\n");
	printf("//////////////////////////\n\n\n");
	Sleep(2000);
}

void Game_manager::printInventory(Inventory &inv, HANDLE out_handle, Hero* hero)
{
	bool exit = false;
	int chosed = 0;
	COORD position;
	string typeC;
	int page = 0;
	int type = 0;
	inv.checkEquiped();

	while (!exit) {
		for (int i = 0; i < 120; i++)
		{
			if (i == 40)printf("%c", (char)209);
			else printf("%c", (char)205);
		}
		endl();
		printf("\n");

		type = inv.getItem(chosed + (10 * page))->getType();
		string bio = inv.getItem(chosed + (10 * page))->getBio().c_str();
		string bioTEMP = bio;
		string bioC[5];

		int k = 0;
		while (bioTEMP.length() > 48 && k != 4)
		{
			bioC[k] = bioTEMP.substr(0, 48);
			bioTEMP.erase(0, 48);
			k++;
		}
		bioC[k] = bioTEMP;
		string sType;

		for (int i = 0; i < 10; i++)
		{
			if (i != chosed)printf("  ");//becouse has no arrow
			else printf("%c ", (char)16);//arrow
			string name = inv.getItem(i + (10 * page))->getName().substr(0, 35);
			printf("%s", name.c_str());

			int end = 35 - name.length();

			for (int i = 0; i < end; i++)printf(" ");//every 2 print massive
			if (inv.getItem(i + (10 * page))->getName().length() > 35)printf("...");//need to fill all of next
			else { printf("   "); }
			printf("%c", (char)179);

			if (i == 1)
			{
				switch (type)
				{
				case 0:
					sType = "Thing ";
					break;
				case 1:
					sType = "Weapon ";
					break;
				case 2:
					sType = "Head ";
					break;
				case 3:
					sType = "Body ";
					break;
				case 4:
					sType = "Legs ";
					break;
				case 5:
					sType = "NONE ";
					break;
				case 6:
					sType = "Equiped Weapon ";
					break;
				case 7:
					sType = "Equiped Head ";
					break;
				case 8:
					sType = "Equiped Body ";
					break;
				case 9:
					sType = "Equiped Legs ";
					break;
				case 10:
					sType = "Potion ";
					break;
				default:
					sType = "NONE ";
					break;
				}

				name = inv.getItem(chosed + (10 * page))->getName().substr(0, 30);
				printf(" NAME: %s", name.c_str());//CAN 72 CHARS (MASSIVE[SELECTED].GETNAME();)

				int c;
				if (inv.getItem(chosed + (10 * page))->getName().length() > 30)
				{
					printf("...");
					c = 30 - name.length();
				}
				else
				{
					c = 33 - name.length();
				}

				for (int i = 0; i < c; i++)printf(" ");

				printf("| Type: %s", sType.c_str());
				c = 20 - sType.length();
				for (int i = 0; i < c; i++)printf(" ");
			}
			else if (i == 2)
			{
				int p = inv.getItem(chosed + (10 * page))->getPluses();
				string pType;
				if (p == 1)
				{
					pType = "Strength ";
				}
				else if (p == 2)
				{
					pType = "Agility ";
				}
				else if (p == 3)
				{
					pType = "Intelligence ";
				}
				else if (p == 4)
				{
					pType = "HP ";
				}
				else if (p == 5)
				{
					pType = "MP ";
				}
				else if (p == 6)
				{
					pType = "Attack ";
				}
				else
				{
					pType = "";
				}
				string zero = "";
				if (inv.getItem(chosed + (10 * page))->getIPluses() > 0)
				{
					zero = "+";
				}
				else if (inv.getItem(chosed + (10 * page))->getIPluses() == 0)
				{
					zero = "";
				}

				if (zero == "")
				{
					printf(" PLUSES: %s", pType.c_str());
				}
				else
				{
					printf(" PLUSES: %s%s%d", pType.c_str(), zero.c_str(), inv.getItem(chosed + (10 * page))->getIPluses());//CAN 70 CHARS (MMASIIVE[SELECTED].GETPLUSES();
				}

				int c = pType.length() + zero.length() + 10;
				c = 35 - c;																										  //int c = 49 - inv.getItem(chosed)->getPluses().length();
				for (int i = 0; i < c; i++)printf(" ");
			}
			else if (i == 3)
			{
				printf(" EXTRA: EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE...");//CAN 71 CHARS (MASSIVE[SELECTED].GETEXTRA
				  //EXTRA
			}
			else if (i == 4)
			{
				printf(" BIOGRATHY: %s", bioC[0].c_str());//CAN 51 CHARS (MASSIVE[SELECTED].GETFIRSTB)
				int c = 49 - bioC[0].length();
				for (int i = 0; i < c; i++)printf(" ");
				bio.erase(0, 50);
			}
			else if (i == 5)
			{
				printf("            %s", bioC[1].c_str());//CAN 51 CHARS (MASSIVE[SELECTED].GETFIRSTB)
				int c = 49 - bioC[1].length();
				for (int i = 0; i < c; i++)printf(" ");
				bio.erase(0, 50);
			}
			else if (i == 6)
			{
				printf("            %s", bioC[2].c_str());//CAN 51 CHARS (MASSIVE[SELECTED].GETFIRSTB)

				int c = 49 - bioC[2].length();
				for (int i = 0; i < c; i++)printf(" ");
				bio.erase(0, 50);
			}
			else if (i == 7)
			{
				printf(" Count: %d", inv.getItem(chosed + (10 * page))->getCount());//CAN 51 CHARS (MASSIVE[SELECTED].GETFIRSTB)

				int c = 49 - bioC[3].length();
				for (int i = 0; i < c; i++)printf(" ");
			}
			else if (i == 8)
			{
				printf(" Sell prices: %d", inv.getItem(chosed + (10 * page))->getSellValue());//CAN 51 CHARS (MASSIVE[SELECTED].GETFIRSTB)
				int j = 0;
				int p = inv.getItem(chosed + (10 * page))->getSellValue();

				while (p > 9)
				{
					p = p / 10;
					j++;
				}

				j = 49 - j;
				for (int i = 0; i < j; i++)printf(" ");
			}
			else if (i == 9)
			{
				printf(" Buy prices: %d", inv.getItem(chosed + (10 * page))->getBuyValue());
				int j = 0;
				int p = inv.getItem(chosed + (10 * page))->getBuyValue();
				while (p > 9)
				{
					p = p / 10;
					j++;
				}

				j = 49 - j;
				for (int i = 0; i < j; i++)printf(" ");
			}
			printf("\n");
			endl();
			printf("\n");
		}
		for (int i = 0; i < 120; i++)
		{
			if (i == 40)printf("%c", (char)207);
			else if (i == 19)printf("%d", page);
			else printf("%c", (char)205);
		}
		printf("\n");

		printf(" %s (%s):\n", hero->getName().c_str(), typeC.c_str());//TYPE = (Invoker, troll...)
		for (int i = 0; i < 120; i++)//end string
		{
			printf("%c", (char)196);
		}
		////////////////////////////////////////////////////////////
		string tempH = inv.head->getName().substr(0, 45);
		printf(" HEAD: %s", tempH.c_str());//45
		if (inv.head->getName().length() > 45)
		{
			printf("...");
		}
		else
		{
			int c = 48 - inv.head->getName().length();
			for (int i = 0; i < c; i++)printf(" ");
		}

		printf("\n");
		printf("\n");

		string tempB = inv.body->getName().substr(0, 45);
		printf(" BODY: %s", tempB.c_str());//body, weapon
		if (inv.body->getName().length() > 45)
		{
			printf("...");
		}
		else
		{
			int c = 48 - inv.body->getName().length();
			for (int i = 0; i < c; i++)printf(" ");
		}

		string tempW = inv.weapon->getName().substr(0, 45);
		printf("   |   WEAPON: %s", tempW.c_str());
		if (inv.weapon->getName().length() > 45)
		{
			printf("...");
		}
		else
		{
			int c = 48 - inv.weapon->getName().length();
			for (int i = 0; i < c; i++)printf(" ");
		}

		printf("\n");
		printf("\n");

		string tempL = inv.legs->getName().substr(0, 45);
		printf(" LEGS: %s", tempL.c_str());
		if (inv.legs->getName().length() > 45)
		{
			printf("...");
		}
		else
		{
			int c = 48 - inv.legs->getName().length();
			for (int i = 0; i < c; i++)printf(" ");
		}

		printf("\n");
		//////////////////////////////////////////////////////////////
		for (int i = 0; i < 120; i++)//end string
		{
			printf("%c", (char)220);
		}
		printf(" LEVEL: %d\n", hero->getLevel());
		printf(" EXP: %d/%d\n", hero->getExp(), hero->getMaxExp());
		printf("\n");
		printf(" GOLD: %d\n", hero->getGold());

		for (int i = 0; i < 120; i++)//end string
		{
			printf("%c", (char)223);
		}

		printf(" STATS:\n");
		printf("\n");
		printf(" HP: %d/%d", hero->getHealth(), hero->getMaxHealth());
		for (int i = 0; i < 5; i++)printf(" ");
		printf("|     MP: %d/%d", hero->getMana(), hero->getMaxMana());
		for (int i = 0; i < 5; i++)printf(" ");
		printf("|     ARMOR: %d", hero->getArmor());
		for (int i = 0; i < 5; i++)printf(" ");
		printf("|     ATTACK: %.0f - %.0f", hero->getAtk(), (hero->getAtk() + 10));
		for (int i = 0; i < 5; i++)printf(" ");

		printf("\n");
		printf("\n");

		printf(" STRENGTH: %d", hero->getStrength());
		for (int i = 0; i < 5; i++)printf(" ");

		printf("|     PLUSHEALTH: %.0f", (hero->getStrength()*22.5f));
		for (int i = 0; i < 5; i++)printf(" ");
		printf("\n");
		printf("\n");

		printf(" AGILITY: %d", hero->getAgility());
		for (int i = 0; i < 5; i++)printf(" ");
		printf("|     PLUSARMOR: %.0f", (hero->getAgility()* 0.2f));
		for (int i = 0; i < 5; i++)printf(" ");

		printf("\n");
		printf("\n");
		printf(" INTELLIGENCE: %d", hero->getIntelligence());
		for (int i = 0; i < 5; i++)printf(" ");
		printf("|     PLUSMANA: %.0f", (hero->getIntelligence()*15.2f));
		for (int i = 0; i < 5; i++)printf(" ");
		printf("\n");

		for (int i = 0; i < 120; i++)//end string
		{
			printf("%c", (char)205);
		}
		printf("\n");

		printf(" E -> Use               %c|%c -> Choose inventory slot                 %c | %c -> Choose a list                 Esc -> Exit ", (char)30, (char)31, (char)17, (char)16);//CONSOLE END HERE (120CHARS)
		bool get = false;
		while (!get) {
			if (GetAsyncKeyState(0x45))//E         GetAsyncKeyState (0x01)
			{
				position.X = 0;
				position.Y = 0;
				SetConsoleCursorPosition(out_handle, position);

				//inv.deleteItem(chosed + (10 * page));

				if (inv.getItem(chosed + (10 * page))->getType() == 10)//potion
				{
					int p = inv.getItem(chosed + (10 * page))->getPluses();
					if (p == 4)//hp
					{
						hero->setHealth(hero->getHealth() + inv.getItem(chosed + (10 * page))->getIPluses());
					}
					else // mp
					{
						hero->setMana(hero->getMana() + inv.getItem(chosed + (10 * page))->getIPluses());
					}
					inv.deleteItem(chosed + (10 * page));
					hero->updateStats();
				}
				else if (inv.getItem(chosed + (10 * page))->getType() >= 1 && inv.getItem(chosed + (10 * page))->getType() <= 4)
				{
					inv.checkEquiped();
					int p = inv.getItem(chosed + (10 * page))->getPluses();
					int j;

					if (inv.getItem(chosed + (10 * page))->getType() == weapon)
					{
						j = inv.weapon->getPluses();
						switch (j)
						{
						case 1:
							hero->setStrength(hero->getStrength() - inv.weapon->getIPluses());
							break;
						case 2:
							hero->setAgility(hero->getAgility() - inv.weapon->getIPluses());
							break;
						case 3:
							hero->setIntelligence(hero->getIntelligence() - inv.weapon->getIPluses());
							break;
						case 6:
							hero->setPlusAtk(hero->getPlusAtk() - inv.weapon->getIPluses());
							break;
						default:
							break;
						}
						inv.weapon->setType(weapon);
						inv.findItem(inv.weapon);

						inv.weapon = inv.getItem(chosed + (10 * page));
						inv.getItem(chosed + (10 * page))->setType(EqWeapon);
						hero->updateStats();
					}
					else if (inv.getItem(chosed + (10 * page))->getType() == head)
					{
						j = inv.head->getPluses();
						switch (j)
						{
						case 1:
							hero->setStrength(hero->getStrength() - inv.head->getIPluses());
							break;
						case 2:
							hero->setAgility(hero->getAgility() - inv.head->getIPluses());
							break;
						case 3:
							hero->setIntelligence(hero->getIntelligence() - inv.head->getIPluses());
							break;
						case 6:
							hero->setPlusAtk(hero->getPlusAtk() - inv.head->getIPluses());
							break;
						default:
							break;
						}
						inv.head->setType(head);
						inv.findItem(inv.head);
						inv.checkEquiped();

						inv.head = inv.getItem(chosed + (10 * page));
						inv.getItem(chosed + (10 * page))->setType(EqHead);
						hero->updateStats();
					}
					else if (inv.getItem(chosed + (10 * page))->getType() == body)
					{
						j = inv.body->getPluses();
						switch (j)
						{
						case 1:
							hero->setStrength(hero->getStrength() - inv.body->getIPluses());
							break;
						case 2:
							hero->setAgility(hero->getAgility() - inv.body->getIPluses());
							break;
						case 3:
							hero->setIntelligence(hero->getIntelligence() - inv.body->getIPluses());
							break;
						case 6:
							hero->setPlusAtk(hero->getPlusAtk() - inv.body->getIPluses());
							break;
						default:
							break;
						}
						inv.body->setType(body);
						inv.findItem(inv.body);
						inv.checkEquiped();

						inv.body = inv.getItem(chosed + (10 * page));
						inv.getItem(chosed + (10 * page))->setType(EqBody);
						hero->updateStats();
					}
					else if (inv.getItem(chosed + (10 * page))->getType() == legs)
					{
						j = inv.legs->getPluses();
						switch (j)
						{
						case 1:
							hero->setStrength(hero->getStrength() - inv.legs->getIPluses());
							break;
						case 2:
							hero->setAgility(hero->getAgility() - inv.legs->getIPluses());
							break;
						case 3:
							hero->setIntelligence(hero->getIntelligence() - inv.legs->getIPluses());
							break;
						case 6:
							hero->setPlusAtk(hero->getPlusAtk() - inv.legs->getIPluses());
							break;
						default:
							break;
						}
						inv.legs->setType(legs);
						inv.findItem(inv.legs);
						inv.checkEquiped();

						inv.legs = inv.getItem(chosed + (10 * page));
						inv.getItem(chosed + (10 * page))->setType(EqLegs);
						hero->updateStats();
					}

					if (p == 1)
					{
						hero->setStrength(hero->getStrength() + inv.getItem(chosed + (10 * page))->getIPluses());
						//pType = "Strength ";
					}
					else if (p == 2)
					{
						hero->setAgility(hero->getAgility() + inv.getItem(chosed + (10 * page))->getIPluses());

						//pType = "Agility ";
					}
					else if (p == 3)
					{
						hero->setIntelligence(hero->getIntelligence() + inv.getItem(chosed + (10 * page))->getIPluses());
						//pType = "Intelligence ";//13
					}
					else if (p == 6)
					{
						hero->setPlusAtk(hero->getPlusAtk() + inv.getItem(chosed + (10 * page))->getIPluses());
					}
					hero->updateStats();
				}
				get = true;
				Sleep(100);
			}
			else if (GetAsyncKeyState(0x1B))//escape
			{
				RPGUtils::clearConsole();
				//////////////////TO START POSITION
				position.X = 0;
				position.Y = 0;
				SetConsoleCursorPosition(out_handle, position);
				///////////////////////
				chosed = 0;
				int page = 0;
				int k = 0;
				exit = true;
				get = true;
				Sleep(100);
			}
			else if (GetAsyncKeyState(0x26))//UP
			{
				position.X = 0;
				position.Y = 0;
				SetConsoleCursorPosition(out_handle, position);
				if (chosed + (10 * page) > 0 + (10 * page))
				{
					chosed--;
					get = true;
					Sleep(100);
				}
			}
			else if (GetAsyncKeyState(0x28))//DOWN
			{
				position.X = 0;
				position.Y = 0;
				SetConsoleCursorPosition(out_handle, position);
				if (chosed + (10 * page) < 9 + (10 * page))
				{
					chosed++;
					get = true;
					Sleep(100);
				}
			}
			else if (GetAsyncKeyState(0x25))//left
			{
				position.X = 0;
				position.Y = 0;
				SetConsoleCursorPosition(out_handle, position);
				if (page > 0)
				{
					page--;
					chosed = 0;
					get = true;
					Sleep(100);
				}
			}
			else if (GetAsyncKeyState(0x27))//right
			{
				position.X = 0;
				position.Y = 0;
				SetConsoleCursorPosition(out_handle, position);
				if (page < 9)
				{
					page++;
					chosed = 0;
					get = true;
					Sleep(100);
				}
			}
			cin.clear();
		}
	}
}

bool Game_manager::printBattle(Inventory &inv, HANDLE out_handle, Hero* hero, Monster* monster)
{
	bool exit = false;
	bool preExit = false;
	Drop drop;
	COORD position;
	string battleLog[15];
	for (int i = 0; i < 15; i++)battleLog[i] = "";
	int skroll = 0;

	int clicks = 0;
	!GetAsyncKeyState(0x30);
	!GetAsyncKeyState(0x31);
	!GetAsyncKeyState(0x32);
	!GetAsyncKeyState(0x33);
	!GetAsyncKeyState(0x34);

	while (!exit) {
		cin.clear();
		for (int i = 0; i < 120; i++)
		{
			printf("%c", (char)205);
		}
		printf("\n");
		//print hero
		RPGUtils::setColor(Yellow);

		for (int i = 0; i < 25; i++)
		{
			printf("%s",hero->getPic(i).c_str());
		}
		for (int i = 0; i < 25; i++)
		{
			RPGUtils::setWriteCursor(70, 2 + i);
			printf("%s", monster->getPic(i).c_str());
		}

		RPGUtils::setColor();

		position.X = 0;
		position.Y = 28;//30
		if (hero->getHealth() <= 0)hero->setHealth(0);
		SetConsoleCursorPosition(out_handle, position);
		printf("\t %s: %dHP %dMP\t\t\t\t\t\t\t\t%s: %dHP \n\n", hero->getName().c_str(), hero->getHealth(),
			hero->getMana(), monster->getName().c_str(), monster->getHealth());

		for (int i = 0; i < 120; i++)//up
		{
			if (i == 80)
			{
				printf("%c", (char)194);
				for (int j = 0; j < 18; j++)//right box
				{
					position.X = 80;
					position.Y = 31 + j;
					SetConsoleCursorPosition(out_handle, position);
					printf("%c", (char)179);

					if (j == 1)printf("0 - Nothing");
					else if (j == 3)printf("1 - %s\n", hero->getFirst().c_str());
					else if (j == 5)printf("2 - %s\n", hero->getUlt().c_str());
					else if (j == 7)printf("3 - ...\n");
					else if (j == 9)printf("4 - ...\n");
					//printf из массива [j]
				}
				position.X = 81;
				position.Y = 30;
				SetConsoleCursorPosition(out_handle, position);
			}
			else printf("%c", (char)196);
		}
		//when new logs -> add it to battleLog and old ++ (if >15 - delete)
		for (int i = 8; i >= 0; i--)
		{
			if (i == 0)printf("%d: %s\n", i + skroll, battleLog[i + skroll].c_str());
			else printf("%d: %s\n\n", i + skroll, battleLog[i + skroll].c_str());
		}

		for (int i = 0; i < 120; i++)//end string
		{
			if (i == 80)printf("%c", (char)193);
			else printf("%c", (char)196);
		}

		bool get = false;
		if (preExit)
		{
			
			Sleep(4000);
			for (int i = 0; i < clicks; i++)
			{
				 
				 
			}
			

			exit = true;
			RPGUtils::clearConsole();
			position.X = 0;
			position.Y = 0;
			SetConsoleCursorPosition(out_handle, position);
			if (win == 1)
			{
				win = -1;
				return true;
			}
			else if (win == 0)
			{
				win = -1;
				return false;
			}
			//delete monster;
		}


		while (!get && !preExit) {
			cin.clear();
			if (GetAsyncKeyState(0x26))//UP
			{
				if (skroll < 6) {
					RPGUtils::clearConsole();
					position.X = 0;
					position.Y = 0;
					SetConsoleCursorPosition(out_handle, position);

					skroll++;
					get = true;
					Sleep(100);
				}
			}
			else if (GetAsyncKeyState(0x28))//DOWN
			{
				if (skroll > 0) {
					RPGUtils::clearConsole();
					position.X = 0;
					position.Y = 0;
					SetConsoleCursorPosition(out_handle, position);

					skroll--;
					get = true;
					Sleep(100);
				}
			}
			else if (GetAsyncKeyState(0x30))//0
			{
				!GetAsyncKeyState(0x30);
				if (monster->getHealth() > 0 && hero->getHealth() > 0)
				{
					for (int j = 13; j >= 0; j--)
					{
						battleLog[j + 1] = battleLog[j];
					}
					battleLog[0] = hero->getName() + " do nothing.";

					for (int j = 13; j >= 0; j--)
					{
						battleLog[j + 1] = battleLog[j];
					}
					monster->attack(hero);
					battleLog[0] = "\t" + monster->getName() + ": " + monster->getAttack();
				}

				Sleep(100);
				get = true;
				RPGUtils::clearConsole();
				position.X = 0;
				position.Y = 0;
				SetConsoleCursorPosition(out_handle, position);
				cin.clear();

			}
			else if (GetAsyncKeyState(0x31))//1
			{
				!GetAsyncKeyState(0x31);
				if (monster->getHealth() > 0 && hero->getHealth() > 0)
				{
					for (int j = 13; j >= 0; j--)
					{
						battleLog[j + 1] = battleLog[j];
					}
					hero->attack(monster);
					battleLog[0] = hero->getName() + ": " + hero->getFirst() + " - " + to_string(hero->getHit());

					monster->attack(hero);
					for (int j = 13; j >= 0; j--)
					{
						battleLog[j + 1] = battleLog[j];
					}
					battleLog[0] = "\t" + monster->getName() + ": " + monster->getAttack();
				}
				Sleep(100);
				get = true;
				RPGUtils::clearConsole();
				position.X = 0;
				position.Y = 0;
				SetConsoleCursorPosition(out_handle, position);
				cin.clear();
			}
			else if (GetAsyncKeyState(0x32))//2
			{
				!GetAsyncKeyState(0x32);
				if (monster->getHealth() > 0 && hero->getHealth() > 0)
				{
					for (int j = 13; j >= 0; j--)
					{
						battleLog[j + 1] = battleLog[j];
					}

					if (!hero->specialAttack(monster))battleLog[0] = hero->getName() + ": " + "NOT ENOUGH MANA! You lose you turn!";
					else battleLog[0] = hero->getName() + ": " + hero->getUlt() + " - " + to_string(hero->getHit());

					monster->attack(hero);
					for (int j = 13; j >= 0; j--)
					{
						battleLog[j + 1] = battleLog[j];
					}
					battleLog[0] = "\t" + monster->getName() + ": " + monster->getAttack();
				}

				Sleep(100);
				get = true;
				RPGUtils::clearConsole();
				position.X = 0;
				position.Y = 0;
				SetConsoleCursorPosition(out_handle, position);
				cin.clear();
			}
			else if (GetAsyncKeyState(0x33))//3
			{
				!GetAsyncKeyState(0x33);
				Sleep(100);
				get = true;
				RPGUtils::clearConsole();
				position.X = 0;
				position.Y = 0;
				SetConsoleCursorPosition(out_handle, position);
			}
			else if (GetAsyncKeyState(0x34))//4
			{
				!GetAsyncKeyState(0x34);
				Sleep(100);
				get = true;
				RPGUtils::clearConsole();
				position.X = 0;
				position.Y = 0;
				SetConsoleCursorPosition(out_handle, position);
			}

			if (monster->getHealth() <= 0)
			{
				win = 1;
				monster->setHealth(0);
				preExit = true;
			}
			if (hero->getHealth() <= 0)
			{
				win = 0;
				hero->setHealth(0);
				preExit = true;
			}

			if (win == 1)
			{
				for (int j = 13; j >= 0; j--)
				{
					battleLog[j + 1] = battleLog[j];
				}
				for (int j = 13; j >= 0; j--)
				{
					battleLog[j + 1] = battleLog[j];
				}
				for (int j = 13; j >= 0; j--)
				{
					battleLog[j + 1] = battleLog[j];
				}
				battleLog[2] = "=================================";
				battleLog[1] = "            YOU KILL THE " + monster->getName();
				battleLog[0] = "=================================";
				monster->dropItem(inv);
				hero->setExp(hero->getExp() + monster->getDrop().getDExp());
				hero->setGold(hero->getGold() + monster->getDrop().getDGold());

				//if (hero->getExp() >= hero->getMaxExp())hero->levelup();  !!!!!!!!!!!!!!!!!!!

				for (int j = 13; j >= 0; j--)
				{
					battleLog[j + 1] = battleLog[j];
				}
				for (int j = 13; j >= 0; j--)
				{
					battleLog[j + 1] = battleLog[j];
				}

				battleLog[1] = "YOU GOT " + to_string(monster->getDrop().getDExp()) + " XP!";
				battleLog[0] = "YOU GOT " + to_string(monster->getDrop().getDGold()) + " GOLD!";

				if (drop.ListOfItems[monster->getDropID()].getName() != "")
				{
					for (int j = 13; j >= 0; j--)
					{
						battleLog[j + 1] = battleLog[j];
					}
					battleLog[0] = "YOU GOT A " + drop.ListOfItems[monster->getDropID()].getName() + "!";
				}
				for (int j = 13; j >= 0; j--)
				{
					battleLog[j + 1] = battleLog[j];
				}
				battleLog[0] = "Wait 4 second. Don`t press anything...";
			}
			else if (win == 0)
			{
				for (int j = 13; j >= 0; j--)
				{
					battleLog[j + 1] = battleLog[j];
				}
				for (int j = 13; j >= 0; j--)
				{
					battleLog[j + 1] = battleLog[j];
				}
				for (int j = 13; j >= 0; j--)
				{
					battleLog[j + 1] = battleLog[j];
				}

				battleLog[2] = "*********************************";
				battleLog[1] = "            YOU DIE...";
				battleLog[0] = "*********************************";
				for (int j = 13; j >= 0; j--)
				{
					battleLog[j + 1] = battleLog[j];
				}
				battleLog[0] = "Wait 4 second. Don`t press anything...";
			}
			cin.clear();
		}
		clicks++;
	}
	!GetAsyncKeyState(0x30);
	!GetAsyncKeyState(0x31);
	!GetAsyncKeyState(0x32);
	!GetAsyncKeyState(0x33);
	!GetAsyncKeyState(0x34);
}

void Game_manager::printUpgrage(HANDLE out_handle, Hero * hero, UpgradeBlock & block)
{
	string lastChoice = "Q";

	bool exit = false;
	bool preExit = false;
	COORD position;

	!GetAsyncKeyState(0x30);
	!GetAsyncKeyState(0x31);
	!GetAsyncKeyState(0x32);
	!GetAsyncKeyState(0x33);
	!GetAsyncKeyState(0x34);
	!GetAsyncKeyState(0xC0);

	string choi;

	while (!exit) {
		cin.clear();

		printf("Your points: %d   ", hero->getUpPluses());
		block.print(hero);

		bool get = false;

		while (!get && !exit) {
			if (GetAsyncKeyState(0xC0))//  ~
			{
				if (hero->getUpPluses() > 0)
				{
					int index = block.transf();
					if (block.getType(index) < 2)
					{
						block.setOpen(hero);
						hero->setUpPluses(hero->getUpPluses() - 1);
					}
					
					Sleep(100);
					get = true;
					position.X = 0;
					position.Y = 0;
					SetConsoleCursorPosition(out_handle, position);
				}
			}
			else if (GetAsyncKeyState(0x1B))//escape
			{
				RPGUtils::clearConsole();
				position.X = 0;
				position.Y = 0;
				SetConsoleCursorPosition(out_handle, position);
				exit = true;
				get = true;
				Sleep(100);
			}
			else if (GetAsyncKeyState(0x51))//Q
			{
				choi = "Q";
				Sleep(100);
				get = true;
				position.X = 0;
				position.Y = 0;
				SetConsoleCursorPosition(out_handle, position);
			}
			else if (GetAsyncKeyState(0x57))//W
			{
				choi = "W";
				Sleep(100);
				get = true;
				position.X = 0;
				position.Y = 0;
				SetConsoleCursorPosition(out_handle, position);
			}
			else if (GetAsyncKeyState(0x45))//E
			{
				choi = "E";
				Sleep(100);
				get = true;
				position.X = 0;
				position.Y = 0;
				SetConsoleCursorPosition(out_handle, position);
			}
			else if (GetAsyncKeyState(0x52))//R
			{
				choi = "R";
				Sleep(100);
				get = true;
				position.X = 0;
				position.Y = 0;
				SetConsoleCursorPosition(out_handle, position);
			}
			else if (GetAsyncKeyState(0x54))//T
			{
				choi = "T";
				Sleep(100);
				get = true;
				position.X = 0;
				position.Y = 0;
				SetConsoleCursorPosition(out_handle, position);
			}
			else if (GetAsyncKeyState(0x59))//Y
			{
				choi = "Y";
				Sleep(100);
				get = true;
				position.X = 0;
				position.Y = 0;
				SetConsoleCursorPosition(out_handle, position);
			}
			else if (GetAsyncKeyState(0x41))//A
			{
				choi = "A";
				Sleep(100);
				get = true;
				position.X = 0;
				position.Y = 0;
				SetConsoleCursorPosition(out_handle, position);
			}
			else if (GetAsyncKeyState(0x53))//S
			{
				choi = "S";
				Sleep(100);
				get = true;
				position.X = 0;
				position.Y = 0;
				SetConsoleCursorPosition(out_handle, position);
			}
			else if (GetAsyncKeyState(0x44))//D
			{
				choi = "D";
				Sleep(100);
				get = true;
				position.X = 0;
				position.Y = 0;
				SetConsoleCursorPosition(out_handle, position);
			}
			else if (GetAsyncKeyState(0x46))//F
			{
				choi = "F";
				Sleep(100);
				get = true;
				position.X = 0;
				position.Y = 0;
				SetConsoleCursorPosition(out_handle, position);
			}
			else if (GetAsyncKeyState(0x47))//G
			{
				choi = "G";
				Sleep(100);
				get = true;
				position.X = 0;
				position.Y = 0;
				SetConsoleCursorPosition(out_handle, position);
			}
			else if (GetAsyncKeyState(0x48))//H
			{
				choi = "H";
				Sleep(100);
				get = true;
				position.X = 0;
				position.Y = 0;
				SetConsoleCursorPosition(out_handle, position);
			}
			else if (GetAsyncKeyState(0x5A))//Z
			{
				choi = "Z";
				Sleep(100);
				get = true;
				position.X = 0;
				position.Y = 0;
				SetConsoleCursorPosition(out_handle, position);
			}
			else if (GetAsyncKeyState(0x58))//X
			{
				choi = "X";
				Sleep(100);
				get = true;
				position.X = 0;
				position.Y = 0;
				SetConsoleCursorPosition(out_handle, position);
			}
			else if (GetAsyncKeyState(0x43))//C
			{
				choi = "C";
				Sleep(100);
				get = true;
				position.X = 0;
				position.Y = 0;
				SetConsoleCursorPosition(out_handle, position);
			}
			else if (GetAsyncKeyState(0x56))//V
			{
				choi = "V";
				Sleep(100);
				get = true;
				position.X = 0;
				position.Y = 0;
				SetConsoleCursorPosition(out_handle, position);
			}
			else if (GetAsyncKeyState(0x42))//B
			{
				choi = "B";
				Sleep(100);
				get = true;
				position.X = 0;
				position.Y = 0;
				SetConsoleCursorPosition(out_handle, position);
			}
			else if (GetAsyncKeyState(0x6A))//* SECRET!
			{

				choi = "*";
				Sleep(100);
				get = true;
				position.X = 0;
				position.Y = 0;
				SetConsoleCursorPosition(out_handle, position);
			}

		}
		block.setChoice(choi);
		int index = block.transf();
		if (block.getType(index) > 0)
		{
			lastChoice = choi;
		}
		else block.setChoice(lastChoice);

		cin.clear();
	}
	!GetAsyncKeyState(0x30);
	!GetAsyncKeyState(0x31);
	!GetAsyncKeyState(0x32);
	!GetAsyncKeyState(0x33);
	!GetAsyncKeyState(0x34);

	cin.clear();
}
