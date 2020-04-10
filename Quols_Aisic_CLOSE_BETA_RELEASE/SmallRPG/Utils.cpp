#include "Utils.h"


int Drop::getDExp() { return experience; }

int Drop::getDGold() { return gold; }


int RPGUtils::getRandom(int from, int to)
{
	return from + rand() % to;
}
double RPGUtils::getRandom(double from, double to)
{
	return from + ((double)rand() / (double)RAND_MAX) * (to - from);
}
void RPGUtils::clearConsole()
{
	printf("\n\n\n\n\n\n\n\n\n\n");
	printf("\n\n\n\n\n\n\n\n\n\n");
	printf("\n\n\n\n\n\n\n\n\n\n");
	printf("\n\n\n\n\n\n\n\n\n\n");
	printf("\n\n\n\n\n\n\n\n\n\n");
	printf("\n\n\n\n\n\n\n\n\n\n");
	printf("\n\n\n\n\n\n\n\n\n\n");
	printf("\n\n\n\n\n\n\n\n\n\n");
	printf("\n\n\n\n\n\n\n\n\n\n");
	printf("\n\n\n\n\n\n\n\n\n\n");
}
void RPGUtils::setAndDraw(int x, int y, string ch)
{
	COORD position;
	HANDLE out_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	position.X = x;
	position.Y = y;
	SetConsoleCursorPosition(out_handle, position);
	printf("%s", ch.c_str());
}
void RPGUtils::setAndDraw(int x, int y, char ch)
{
	COORD position;
	HANDLE out_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	position.X = x;
	position.Y = y;
	SetConsoleCursorPosition(out_handle, position);
	printf("%c", ch);
}
void RPGUtils::setColor(Colors color) 
{
	/*int back = 0;
		if (colorBack & 1) back |= BACKGROUND_BLUE;
		if (colorBack & 2) back |= BACKGROUND_GREEN;
		if (colorBack & 4) back |= BACKGROUND_RED;
		if (colorBack & 8) back |= BACKGROUND_INTENSITY;

		int fore = 0;
		if (colorFore & 1) fore |= FOREGROUND_BLUE;
		if (colorFore & 2) fore |= FOREGROUND_GREEN;
		if (colorFore & 4) fore |= FOREGROUND_RED;
		if (colorFore & 8) fore |= FOREGROUND_INTENSITY;*/

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void RPGUtils::setColor(Colors color, Colors backColor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ((backColor << 4) | color));
}

