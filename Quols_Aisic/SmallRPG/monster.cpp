#include "monster.h"

Monster::Monster(int health, std::string name) : Creature(health, name) {}
Monster::~Monster() {}
EnemyType Monster::getType()
{
	return type;
}
string Monster::getAttack() { return sAttack; }
