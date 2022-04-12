#include <iostream>
#include "Spell.h"
using namespace std;

Spell::Spell()
{
	description = NULL;
	type = NULL;
	mana = 0;
}

Spell::Spell(const char* d, const char* t, int m)
{
	description = new char[strlen(d) + 1];
	strcpy_s(description, strlen(d) + 1, d);
	type = new char[strlen(t) + 1];
	strcpy_s(type, strlen(t) + 1, t);
	mana = m;
}

Spell::Spell(const Spell& s)
{
	description = new char[strlen(s.description) + 1];
	strcpy_s(description, strlen(s.description) + 1, s.description);
	type = new char[strlen(s.type) + 1];
	strcpy_s(type, strlen(s.type) + 1, s.type);
	mana = s.mana;
}

Spell& Spell::operator=(const Spell& s)
{
	if (this != &s)
	{
		delete[] description;
		description = NULL;
		delete[] type;
		type = NULL;
		mana = 0;
		description = new char[strlen(s.description) + 1];
		strcpy_s(description, strlen(s.description) + 1, s.description);
		type = new char[strlen(s.type) + 1];
		strcpy_s(type, strlen(s.type) + 1, s.type);
		mana = s.mana;
	}
	return *this;
}

Spell::~Spell()
{
	delete[] description;
	delete[] type;
}

char* Spell::getDescription()const
{
	return description;
}


char* Spell::getType()const
{
	return type;
}

int Spell::getMana()const
{
	return mana;
}
