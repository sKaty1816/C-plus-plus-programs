#ifndef SORCERER_H
#define SORCERER_H
#include "Warrior.h"
#include "Sergeant.h"
#include "Book.h"

class Sorcerer: public Warrior
{
private:
	char* descrSorc;
	Sergeant* sergeants;
	int numSergeants;
	int capSergeants;
	int mana;
	Book magicbook;
public:
public:
	Sorcerer();
	Sorcerer(const char*, const int, const int, const int,
		const char*, const Sergeant*, const int, const int, const Book);
	Sorcerer(const Sorcerer&);
	Sorcerer& operator=(const Sorcerer&);
	~Sorcerer();
	int sumLevels()const;
	int getMana()const;
	int sumGold()const;
	int sumPeople()const;
	int maxSpells();
};

#endif