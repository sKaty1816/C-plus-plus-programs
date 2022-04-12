#ifndef COMMANDER_H
#define COMMANDER_H
#include "Warrior.h"
#include "Sorcerer.h"

class Commander : public Warrior
{
private:
	char* descrCommander;
	Sorcerer* mags;
	int numMags;
	int capMags;
public:
	Commander();
	Commander(const char*, const int, const int, const int,
		const char*, const Sorcerer*, const int);
	Commander(const Commander&);
	Commander& operator=(const Commander&);
	~Commander();
	int sumLevels()const;
	int sumPeople()const;
	int averageLvl()const;
	int sumMana()const;
	int averageMana()const;
	int sumGold()const;
	int sumMaxSpells()const;
};

#endif