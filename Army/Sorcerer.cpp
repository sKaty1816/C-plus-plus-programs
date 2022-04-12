#include <iostream>
using namespace std;
#include "Sorcerer.h"

Sorcerer::Sorcerer() : Warrior(), magicbook()
{
	descrSorc = NULL;
	sergeants = NULL;
	numSergeants = 0;
	capSergeants = 1;
	mana = 0;
	sergeants = new Sergeant[1];
}

Sorcerer::Sorcerer(const char* n, const int a, const int lvl, const int g,
	const char* dsorc, const Sergeant* s, const int ns, const int m, const Book mb)
{
	Warrior::setName(n);
	Warrior::setAge(a);
	Warrior::setLevel(lvl);
	Warrior::setGold(g);
	descrSorc = new char[strlen(dsorc) + 1];
	strcpy_s(descrSorc, strlen(dsorc) + 1, dsorc);
	sergeants = new Sergeant[ns * 2];
	for (int i = 0; i < ns; i++)
	{
		sergeants[i] = s[i];
	}
	numSergeants = ns;
	capSergeants = ns * 2;
	mana = m;
	magicbook = mb;
}

Sorcerer::Sorcerer(const Sorcerer& s)
{
	Warrior::setName(s.getName());
	Warrior::setAge(s.getAge());
	Warrior::setLevel(s.getLevel());
	Warrior::setGold(s.getGold());
	descrSorc = new char[strlen(s.descrSorc) + 1];
	strcpy_s(descrSorc, strlen(s.descrSorc) + 1, s.descrSorc);
	sergeants = new Sergeant[s.capSergeants];
	for (int i = 0; i < s.numSergeants; i++)
	{
		sergeants[i] = s.sergeants[i];
	}

	numSergeants = s.numSergeants;
	capSergeants = s.capSergeants;
	mana = s.mana;
	magicbook = s.magicbook;
}

Sorcerer& Sorcerer::operator=(const Sorcerer& s)
{
	if (this != &s)
	{
		delete[] descrSorc;
		delete[] sergeants;
		numSergeants = 0;
		capSergeants = 1;
		Warrior::setName(s.getName());
		Warrior::setAge(s.getAge());
		Warrior::setLevel(s.getLevel());
		Warrior::setGold(s.getGold());
		descrSorc = new char[strlen(s.descrSorc) + 1];
		strcpy_s(descrSorc, strlen(s.descrSorc) + 1, s.descrSorc);
		sergeants = new Sergeant[s.capSergeants];
		for (int i = 0; i < s.numSergeants; i++)
		{
			sergeants[i] = s.sergeants[i];
		}

		numSergeants = s.numSergeants;
		capSergeants = s.capSergeants;
		mana = s.mana;
		magicbook = s.magicbook;
	}

	return *this;
}

Sorcerer::~Sorcerer()
{
	delete[] descrSorc;
	delete[] sergeants;
}

int Sorcerer::sumLevels()const
{
	int sum = 0;
	for (int i = 0; i < numSergeants; i++)
	{
		sum += sergeants[i].sumLevels();
	}
	sum += Warrior::getLevel();
	return sum;
}

int Sorcerer::getMana()const
{
	return mana;
}

int Sorcerer::sumGold()const
{
	int sum = 0;
	for (int i = 0; i < numSergeants; i++)
	{
		sum += sergeants[i].sumGold();
	}
	sum += Warrior::getGold();
	return sum;
}

int Sorcerer::sumPeople()const
{
	int sum = 0;
	for (int i = 0; i < numSergeants; i++)
	{
		sum += sergeants[i].getUnits();
	}
	sum += numSergeants;
	return sum;
}

int Sorcerer::maxSpells()
{
	magicbook.sort();
	int cnt = 0;
	for (int i = 0; i < magicbook.getSize(); i++)
	{
		if (mana < magicbook.ManaForSpell(i))
		{
			break;
		}
		cnt++;
		mana -= magicbook.ManaForSpell(i);
	}

	return cnt;
}