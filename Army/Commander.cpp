#include <iostream>
using namespace std;
#include "Commander.h"

Commander::Commander() : Warrior()
{
	descrCommander = NULL;
	mags = NULL;
	numMags = 0;
	capMags = 0;
	mags = new Sorcerer[1];
}

Commander::Commander(const char* n, const int a, const int lvl, const int g,
	const char* dcom, const Sorcerer* s, const int ns)
{
	Warrior::setName(n);
	Warrior::setAge(a);
	Warrior::setLevel(lvl);
	Warrior::setGold(g);
	descrCommander = new char[strlen(dcom) + 1];
	strcpy_s(descrCommander, strlen(dcom) + 1, dcom);
	mags = new Sorcerer[ns * 2];
	for (int i = 0; i < ns; i++)
	{
		mags[i] = s[i];
	}
	numMags = ns;
	capMags = ns * 2;
}

Commander::Commander(const Commander& c)
{
	Warrior::setName(c.getName());
	Warrior::setAge(c.getAge());
	Warrior::setLevel(c.getLevel());
	Warrior::setGold(c.getLevel());
	descrCommander = new char[strlen(c.descrCommander) + 1];
	strcpy_s(descrCommander, strlen(c.descrCommander) + 1, c.descrCommander);
	mags = new Sorcerer[c.capMags];
	for (int i = 0; i < c.numMags; i++)
	{
		mags[i] = c.mags[i];
	}

	numMags = c.numMags;
	capMags = c.capMags;
}

Commander& Commander::operator=(const Commander& c)
{
	if (this != &c)
	{
		delete[] descrCommander;
		delete[] mags;
		numMags = 0;
		capMags = 1;
		Warrior::setName(c.getName());
		Warrior::setAge(c.getAge());
		Warrior::setLevel(c.getLevel());
		Warrior::setGold(c.getLevel());
		descrCommander = new char[strlen(c.descrCommander) + 1];
		strcpy_s(descrCommander, strlen(c.descrCommander) + 1, c.descrCommander);
		mags = new Sorcerer[c.capMags];
		for (int i = 0; i < c.numMags; i++)
		{
			mags[i] = c.mags[i];
		}

		numMags = c.numMags;
		capMags = c.capMags;
	}
	return *this;
}

Commander::~Commander()
{
	delete[] descrCommander;
	delete[] mags;
}

int Commander::sumLevels()const
{
	int sum = 0;
	for (int i = 0; i < numMags; i++)
	{
		sum += mags[i].sumLevels();
	}
	sum += Warrior::getLevel();
	return sum;
}

int Commander::sumMana()const
{
	int sum = 0;
	for (int i = 0; i < numMags; i++)
	{
		sum += mags[i].getMana();
	}
	return sum;
}

int Commander::sumGold()const
{
	int sum = 0;
	for (int i = 0; i < numMags; i++)
	{
		sum += mags[i].sumGold();
	}
	sum += Warrior::getGold();
	return sum;
}

int Commander::sumPeople()const
{
	int sum = 0;
	for (int i = 0; i < numMags; i++)
	{
		sum += mags[i].sumPeople();
	}
	sum += numMags;
	sum += 1;
	return sum;
}

int Commander::averageLvl()const
{

	return sumLevels() / sumPeople();
}

int Commander::averageMana()const
{
	return sumMana() / numMags;
}

int Commander::sumMaxSpells()const
{
	int sum = 0;
	for (int i = 0; i < numMags; i++)
	{
		sum += mags[i].maxSpells();
	}
	return sum;
}
