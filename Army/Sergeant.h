#ifndef SERGEANT_H
#define SERGEANT_H
#include "Warrior.h"

class Sergeant : public Warrior
{
private:
	char* squad;
	Warrior* units;
	int numUnits;
	int capUnits;
public:
	Sergeant();
	Sergeant(const char*, const int, const int, const int, const char*, const Warrior*, const int);
	Sergeant(const Sergeant&);
	Sergeant& operator=(const Sergeant&);
	~Sergeant();
	int getUnits()const;
	int sumLevels()const;
	int sumGold()const;
};

#endif