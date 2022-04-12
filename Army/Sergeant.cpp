#include <iostream>
#include "Sergeant.h"
using namespace std;

Sergeant::Sergeant() : Warrior()
{
	squad = NULL;
	units = NULL;
	numUnits = 0;
	capUnits = 1;
	units = new Warrior[1];
}

Sergeant::Sergeant(const char* n, const int a, const int lvl, const int gold,
	const char* sq, const Warrior* un, const int numUn)
{
	Warrior::setName(n);
	Warrior::setAge(a);
	Warrior::setLevel(lvl);
	Warrior::setGold(gold);
	squad = new char[strlen(sq) + 1];
	strcpy_s(squad, strlen(sq) + 1, sq);
	numUnits = numUn;
	capUnits = numUn * 2;
	units = new Warrior[capUnits];
	for (int i = 0; i < numUnits; i++)
	{
		units[i] = un[i];
	}
}

Sergeant::Sergeant(const Sergeant& s)
{
	Warrior::setName(s.getName());
	Warrior::setAge(s.getAge());
	Warrior::setLevel(s.getLevel());
	Warrior::setGold(s.getGold());
	squad = new char[strlen(s.squad) + 1];
	strcpy_s(squad, strlen(s.squad) + 1, s.squad);
	units = new Warrior[s.capUnits];
	for (int i = 0; i < s.numUnits; i++)
	{
		units[i] = s.units[i];
	}
	numUnits = s.numUnits;
	capUnits = s.capUnits;
}

Sergeant& Sergeant::operator=(const Sergeant& s)
{
	if (this != &s)
	{
		delete[] squad;
		delete[] units;
		numUnits = 0;
		capUnits = 1;
		Warrior::setName(s.getName());
		Warrior::setAge(s.getAge());
		Warrior::setLevel(s.getLevel());
		Warrior::setGold(s.getGold());
		squad = new char[strlen(s.squad) + 1];
		strcpy_s(squad, strlen(s.squad) + 1, s.squad);
		units = new Warrior[s.capUnits];
		for (int i = 0; i < s.numUnits; i++)
		{
			units[i] = s.units[i];
		}
		numUnits = s.numUnits;
		capUnits = s.capUnits;
	}
	return *this;
}

Sergeant::~Sergeant()
{
	delete[] squad;
	delete[] units;
}

int Sergeant::getUnits()const
{
	return numUnits;
}

int Sergeant::sumLevels()const
{
	int sum = 0;
	for (int i = 0; i < numUnits; i++)
	{
		sum += units[i].getLevel();
	}
	sum += Warrior::getLevel();
	return sum;
}

int Sergeant::sumGold()const
{
	int sum = 0;
	for (int i = 0; i < numUnits; i++)
	{
		sum += units[i].getGold();
	}
	sum += Warrior::getGold();
	return sum;
}

