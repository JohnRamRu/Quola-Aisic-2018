#include "Monsters.h"
#include "string.h"

Goblin::Goblin() : Monster(110, "Goblin")
{
	mPic[0] = "";
	mPic[1] = "";
	mPic[2] = "";
	mPic[3] = "";
	mPic[4] = "          ,,|||||,,                  ";
	mPic[5] = "     ,||||||,,,,,,,,,|||/||,         ";
	mPic[6] = "      ,,|||////||,||||/,             ";
	mPic[7] = "        ,,,|||,,|,/||||,,|,          ";
	mPic[8] = "           |//||//|,,,,,,,,|,        ";
	mPic[9] = "           |/||,,|||,,,|/|,,||,      ";
	mPic[10] = "           ,|,|||,,, ,/,,||||,||     ";
	mPic[11] = "         ,|||/, ,|,,,,,,|, ,|,,||    ";
	mPic[12] = "        ,|,,|,   |,,|,,||  ,|,,|,    ";
	mPic[13] = "        |,|,|    |,,,,,/,   |,|,     ";
	mPic[14] = "       ,,|/,   ,|//||||,|,,          ";
	mPic[15] = "       |,/,  ,|,,,,|,,,,,||,,,,,     ";
	mPic[16] = "      ,|,|, ,|,,|,|,,|,,,|/|///,     ";
	mPic[17] = "       /|,| ||,,|,    ,,,||,||/#,    ";
	mPic[18] = "     ,/|||| ||,,,|    ,/||/,||/|,    ";
	mPic[19] = "    |||||/,  ,,||/,    ,|,,|,,,,,    ";
	mPic[20] = "     ,,///,    ,||/|    ,||,,,,      ";
	mPic[21] = "            ,,||,,\,    ,|\,         ";
	mPic[22] = "          ,//|//|,      |||/,        ";
	mPic[23] = "           ,,,|,        //|////,     ";
	mPic[24] = "                        |, ,| ,      ";
	setPic(mPic);

	type = GoblinT;
	mobLevel = 5;
}
void Goblin::attack(Creature* hero) {
	int hit = RPGUtils::getRandom(2, 5);
	//printf("A Goblin hits you on the head with his baton!\n Damage: %d\n\n", hit);
	hero->setHealth(hero->getHealth() - (hit - hero->getArmor()));
	sAttack = "A Goblin hits you on the head with his baton! Damage : " + std::to_string(hit);
}
void Goblin::dropItem(Inventory &inv)
{
	dropID = 4;
	drop.create(40, 5);
	inv.addItem(drop.ListOfItems[dropID]);
	//return NONE;
}
Drop Goblin::getDrop() { return drop; }

Skeleton::Skeleton() : Monster(135, "Skeleton")
{
	mPic[0] = "            |,|||||||,|            ";
	mPic[1] = "          ,|||||||||||||,          ";
	mPic[2] = "         ,|||||||||||||||,         ";
	mPic[3] = "        ||||||       ||||,,        ";
	mPic[4] = "        ,|||||||   ||||||,,        ";
	mPic[5] = "        ||||    | |    ||,|        ";
	mPic[6] = "         ,,     |||     ,,         ";
	mPic[7] = "         ,,|||||| ||||||,.         ";
	mPic[8] = "          |,,||,,|,,||,,|          ";
	mPic[9] = "            ,,,,,,,,,,,            ";
	mPic[10] = "          |,..|.....|..,|          ";
	mPic[11] = "           ,,.,|| ||,.,,           ";
	mPic[12] = "           ,| ,|,,,|, ,,           ";
	mPic[13] = "          |,.   |,,   .,|          ";
	mPic[14] = "           ,| ,|||||. |,           ";
	mPic[15] = "          |,,,.,,|,..,,,|          ";
	mPic[16] = "          |.,|,|   |,|,.|          ";
	mPic[17] = "          ||  ,|   |,  ||          ";
	mPic[18] = "             ||.   .||             ";
	mPic[19] = "             ||,   ,||             ";
	mPic[20] = "              ,|   |,              ";
	mPic[21] = "              ,|   |,              ";
	mPic[22] = "             |,.   .,|             ";
	mPic[23] = "             |..   ..|             ";
	mPic[24] = "             |,|   |,|             ";
	setPic(mPic);

	type = SkeletonT;
}
void Skeleton::attack(Creature* hero) {
	int hit = RPGUtils::getRandom(5, 8);
	//printf("Skeleton shoots you with a bow, watch out!\n Damage: %d\n\n", hit);
	hero->setHealth(hero->getHealth() - (hit - hero->getArmor()));
	sAttack = "Skeleton shoots you with a bow, watch out! Damage : " + std::to_string(hit);
}
void Skeleton::dropItem(Inventory &inv)
{
	dropID = 1;
	inv.addItem(drop.ListOfItems[dropID]);
	drop.create(70, 10);
	//return drop; 
}
Drop Skeleton::getDrop() { return drop; }

Slime::Slime() : Monster(120, "Slime")
{
	mPic[0] = "";
	mPic[1] = "";
	mPic[2] = "              ,,,|||/////||,,,               ";
	mPic[3] = "          ,|||||,,,,|||||||||//|,,           ";
	mPic[4] = "       ,|||,,,,,,|||||||||||||||///|,        ";
	mPic[5] = "     ,|||,,,,|||||||||||||||||||||//||,      ";
	mPic[6] = "    ,||,,,||||||||||||||||||||||||||//|,     ";
	mPic[7] = "   ,||,,,||||||||||||||||||||||||||||//|,    ";
	mPic[8] = "  ,||,,,||||||||||||||||||||||||||||||/||,   ";
	mPic[9] = "  |||,,||||||||||||||||||||||||||||||||/|,   ";
	mPic[10] = " ,|||||||||||||||||||||||||||||||||||||/||,  ";
	mPic[11] = " |||||||//##/|||||||||||/###|||||||||||//||, ";
	mPic[12] = ",|||,,|||######|||||||#|####|||||||||||//||, ";
	mPic[13] = ",/|||||||||///|||||||||///||||||||||||||//|, ";
	mPic[14] = ",||||||||||||||||||||||||||||||||||||||///||,";
	mPic[15] = ",||||||||||||||||||||||||||||||||||||||///||,";
	mPic[16] = ",||||||||||||||||||||||||||||||||||||||///||,";
	mPic[17] = ",||||||||||||||||||||||||||||||||||||||///||,";
	mPic[18] = "||||||||||||||||||||||||||||||||||||||///||,,";
	mPic[19] = "|/|||||||||||||||||||||||||||||||||||///|||,|";
	mPic[20] = "/|/|||||||||||||||||||||||||||||||||///||||,/";
	mPic[21] = "/||//||||||||||||||||||||||||||||||///|||||,#";
	mPic[22] = "|//|//////||||||||||||||||||||||////||||,,//,";
	mPic[23] = "  ,,|/##///////////////////////////####/|,   ";
	mPic[24] = "       ,,,,||////#######///#//||,,,,         ";
	setPic(mPic);

	type = SlimeT;
}
void Slime::attack(Creature* hero) {
	int hit = RPGUtils::getRandom(10, 15);
	//printf("Slime throws you in a toxic goo.\n Damage: %d\n\n", hit);
	hero->setHealth(hero->getHealth() - (hit - hero->getArmor()));
	sAttack = "Slime throws you in a toxic goo. Damage : " + std::to_string(hit);
}
void Slime::dropItem(Inventory &inv)
{
	drop.create(80, 15);
	dropID = 7;
	inv.addItem(drop.ListOfItems[dropID]);
	//return drop; 
}
Drop Slime::getDrop() { return drop; }

Zombie::Zombie() : Monster(150, "Zombie")
{
	type = ZombieT;
}
void Zombie::attack(Creature* hero) {
	int hit = RPGUtils::getRandom(8, 10);
	//printf("You were bitten by a zombie, do not let him get to the brain!\n Damage: %d\n\n", hit);
	hero->setHealth(hero->getHealth() - (hit - hero->getArmor()));
	sAttack = "You were bitten by a zombie! Damage : " + std::to_string(hit);
}
void Zombie::dropItem(Inventory &inv)
{
	drop.create(90, 20);
	dropID = 2;
	inv.addItem(drop.ListOfItems[dropID]);
	//return drop;
}
Drop Zombie::getDrop() { return drop; }

/*
Gost::Gost() : Monster(175, "Gost")
{
	type = GostT;
}
void Gost::attack(Creature* hero) {
	int hit = RPGUtils::getRandom(7, 11);
	//printf("Ghost beats you with chains.\n Damage: %d\n\n", hit);
	hero->setHealth(hero->getHealth() - (hit - hero->getArmor()));
	sAttack = "Ghost beats you with chains. Damage : " + std::to_string(hit);
}
void Gost::dropItem(Inventory &inv)
{
	drop.create(100, 25);
	dropID = 2;
	inv.addItem(drop.ListOfItems[dropID]);
	//return drop;
}
Drop Gost::getDrop() { return drop; }*/

Vampire::Vampire() : Monster(190, "Vampire")
{
	type = VampireT;
}
void Vampire::attack(Creature* hero) {
	int hit = RPGUtils::getRandom(12, 18);
	//printf("A vampire is drinking your blood!\n Damage: %d\n\n", hit);
	hero->setHealth(hero->getHealth() - (hit - hero->getArmor()));
	sAttack = "A vampire is drinking your blood! Damage : " + std::to_string(hit);
}
void Vampire::dropItem(Inventory &inv)
{
	drop.create(120, 30);
	dropID = 3;
	inv.addItem(drop.ListOfItems[dropID]);
	//return drop;
}
Drop Vampire::getDrop() { return drop; }
/*
Troll::Troll() : Monster(200, "Troll")
{
	type = TrollT;
}
void Troll::attack(Creature* hero) {
	int hit = RPGUtils::getRandom(20, 25);
	//printf("The Troll throws at you with their sharp spears!\n Damage: %d\n\n", hit);
	hero->setHealth(hero->getHealth() - (hit - hero->getArmor()));
	sAttack = "The Troll throws at you with their sharp spears! Damage : " + std::to_string(hit);
}
void Troll::dropItem(Inventory &inv)
{
	drop.create(145, 35);
	dropID = 4;
	inv.addItem(drop.ListOfItems[dropID]);
	//return drop;
}
Drop Troll::getDrop() { return drop; }*/

Dragon::Dragon() : Monster(255, "Dragon")
{
	type = DragonT;
}
void Dragon::attack(Creature* hero) {
	int hit = RPGUtils::getRandom(30, 40);
	//printf("A breath of fire! Dodge!\n Damage: %d\n\n", hit);
	hero->setHealth(hero->getHealth() - (hit - hero->getArmor()));
	sAttack = "A breath of fire! Dodge! Damage : " + std::to_string(hit);
}
void Dragon::dropItem(Inventory &inv)
{
	drop.create(160, 40);
	dropID = 3;
	inv.addItem(drop.ListOfItems[dropID]);
	//return drop;
}
Drop Dragon::getDrop() { return drop; }

Devil::Devil() : Monster(299, "Devil")
{
	//type = DevilT;
}
void Devil::attack(Creature* hero) {
	int hit = RPGUtils::getRandom(40, 50);
	//printf("He sends a corruption!\n Damage: %d\n\n", hit);
	hero->setHealth(hero->getHealth() - (hit - hero->getArmor()));
	sAttack = "He sends a corruption! Damage : " + std::to_string(hit);
}
void Devil::dropItem(Inventory &inv)
{
	drop.create(200, 45);
	dropID = 2;
	inv.addItem(drop.ListOfItems[dropID]);
	//return drop;
}
Drop Devil::getDrop() { return drop; }

GOD::GOD() : Monster(500, "GOD") 
{
	//type = GODT;
}
void GOD::attack(Creature* hero) {
	int hit = RPGUtils::getRandom(1, 85);
	//printf("CAREFUL, VERY RANDOM DAMAGE!\n Damage: %d\n\n", hit);
	hero->setHealth(hero->getHealth() - (hit - hero->getArmor()));
	sAttack = "CAREFUL, VERY RANDOM DAMAGE! Damage : " + std::to_string(hit);
}
void GOD::dropItem(Inventory &inv)
{
	drop.create(285, 50);
	dropID = 3;
	inv.addItem(drop.ListOfItems[dropID]);
	//return drop;
}
Drop GOD::getDrop() { return drop; }

Agrostini::Agrostini() : Monster(1, "Agrostini")
{
	type = AgrostiniT;
}

void Agrostini::attack(Creature * hero)
{
}

void Agrostini::dropItem(Inventory & inv)
{
}

Drop Agrostini::getDrop()
{
	return Drop();
}

Bear::Bear() : Monster(1, "Bear")
{
	type = BearT;
}

void Bear::attack(Creature * hero)
{
}

void Bear::dropItem(Inventory & inv)
{
}

Drop Bear::getDrop()
{
	return Drop();
}

Cockatrice::Cockatrice() : Monster(1, "Cockatrice")
{
	type = CockatriceT;
}

void Cockatrice::attack(Creature * hero)
{
}

void Cockatrice::dropItem(Inventory & inv)
{
}

Drop Cockatrice::getDrop()
{
	return Drop();
}

Ent::Ent() : Monster(1, "Ent")
{
	type = EntT;
}

void Ent::attack(Creature * hero)
{
}

void Ent::dropItem(Inventory & inv)
{
}

Drop Ent::getDrop()
{
	return Drop();
}

Ferral::Ferral() : Monster(1, "Ferral")
{
	type = FerralT;
}

void Ferral::attack(Creature * hero)
{
}

void Ferral::dropItem(Inventory & inv)
{
}

Drop Ferral::getDrop()
{
	return Drop();
}

Hydra::Hydra() : Monster(1, "Hydra")
{
	type = HydraT;
}

void Hydra::attack(Creature * hero)
{
}

void Hydra::dropItem(Inventory & inv)
{
}

Drop Hydra::getDrop()
{
	return Drop();
}

Siren::Siren() : Monster(1, "Siren")
{
	type = SirenT;
}

void Siren::attack(Creature * hero)
{
}

void Siren::dropItem(Inventory & inv)
{
}

Drop Siren::getDrop()
{
	return Drop();
}

Jarry::Jarry() : Monster(1, "Jarry")
{
	type = JarryT;
}

void Jarry::attack(Creature * hero)
{
}

void Jarry::dropItem(Inventory & inv)
{
}

Drop Jarry::getDrop()
{
	return Drop();
}

Lich::Lich() : Monster(1, "Lich")
{
	type = LichT;
}

void Lich::attack(Creature * hero)
{
}

void Lich::dropItem(Inventory & inv)
{
}

Drop Lich::getDrop()
{
	return Drop();
}

Mermaid::Mermaid() : Monster(1, "Mermaid")
{
	type = MermaidT;
}

void Mermaid::attack(Creature * hero)
{
}

void Mermaid::dropItem(Inventory & inv)
{
}

Drop Mermaid::getDrop()
{
	return Drop();
}

Nefren::Nefren() : Monster(1, "Nefren")
{
	type = NefrenT;
}

void Nefren::attack(Creature * hero)
{
}

void Nefren::dropItem(Inventory & inv)
{
}

Drop Nefren::getDrop()
{
	return Drop();
}

Ogre::Ogre() : Monster(1, "Ogre")
{
	type = OgreT;
}

void Ogre::attack(Creature * hero)
{
}

void Ogre::dropItem(Inventory & inv)
{
}

Drop Ogre::getDrop()
{
	return Drop();
}

Parnasus::Parnasus() : Monster(1, "Parnasus")
{
	type = ParnasusT;
}

void Parnasus::attack(Creature * hero)
{
}

void Parnasus::dropItem(Inventory & inv)
{
}

Drop Parnasus::getDrop()
{
	return Drop();
}

Qre::Qre() : Monster(1, "Qre")
{
	type = QreT;
}

void Qre::attack(Creature * hero)
{
}

void Qre::dropItem(Inventory & inv)
{
}

Drop Qre::getDrop()
{
	return Drop();
}

Rocco::Rocco() : Monster(1, "Rocco")
{
	type = RoccoT;
}

void Rocco::attack(Creature * hero)
{
}

void Rocco::dropItem(Inventory & inv)
{
}

Drop Rocco::getDrop()
{
	return Drop();
}

Ugor::Ugor() : Monster(1, "Ugor")
{
	type = UgorT;
}

void Ugor::attack(Creature * hero)
{
}

void Ugor::dropItem(Inventory & inv)
{
}

Drop Ugor::getDrop()
{
	return Drop();
}

Wolf::Wolf() : Monster(1, "Wolf")
{
	type = WolfT;
}

void Wolf::attack(Creature * hero)
{
}

void Wolf::dropItem(Inventory & inv)
{
}

Drop Wolf::getDrop()
{
	return Drop();
}

Xeonid::Xeonid() : Monster(1, "Xeonid")
{
	type = XeonidT;
}

void Xeonid::attack(Creature * hero)
{
}

void Xeonid::dropItem(Inventory & inv)
{
}

Drop Xeonid::getDrop()
{
	return Drop();
}

Cyclop::Cyclop() : Monster(1, "Cyclop")
{
	type = CyclopT;
}

void Cyclop::attack(Creature * hero)
{
}

void Cyclop::dropItem(Inventory & inv)
{
}

Drop Cyclop::getDrop()
{
	return Drop();
}
