#include <iostream>
#include "Warrior.h"
using namespace std;

Warrior::Warrior()
{
	name = NULL;
	age = 0;
	level = 0;
	gold = 0;
}

Warrior::Warrior(const char* n, const int a, const int lvl, const int g)
{
	name = new char[strlen(n) + 1];
	strcpy_s(name, strlen(n) + 1, n);
	age = a;
	level = lvl;
	gold = g;
}

Warrior::Warrior(const Warrior& w)
{
	name = new char[strlen(w.name) + 1];
	strcpy_s(name, strlen(w.name) + 1, w.name);
	age = w.age;
	level = w.level;
	gold = w.gold;
}

Warrior& Warrior::operator=(const Warrior& w)
{
	if (this != &w)
	{
		delete[] name;
		name = NULL;
		age = 0;
		level = 0;
		gold = 0;
		name = new char[strlen(w.name) + 1];
		strcpy_s(name, strlen(w.name) + 1, w.name);
		age = w.age;
		level = w.level;
		gold = w.gold;
	}
	return *this;
}

Warrior::~Warrior()
{
	delete[]name;
}

void Warrior::setName(const char* n)
{
	delete[] name;
	name = new char[strlen(n) + 1];
	strcpy_s(name, strlen(n) + 1, n);
}

void Warrior::setAge(const int a)
{
	age = a;
}
void Warrior::setLevel(const int lvl)
{
	level = lvl;
}

void Warrior::setGold(const int g)
{
	gold = g;
}

char* Warrior::getName()const
{
	return name;
}

int Warrior::getAge()const
{
	return age;
}

int Warrior::getLevel()const
{
	return level;
}

int Warrior::getGold()const
{
	return gold;
}