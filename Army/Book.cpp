#include <iostream>
using namespace std;
#include "Book.h"

Spell Book::operator[](const int index)const
{
	if (index < 0 || index > size)
		cout << "Wrong index.";
	return spells[index];
}

void Book::change()
{
	int newcapacity;
	if (size >= capacity)
	{
		newcapacity = size + 1;
	}
	else if (size + 1 < capacity)
	{
		newcapacity = capacity - 1;
	}
	else
		return;
	Spell* newspells = new Spell[newcapacity];
	for (int i = 0; i < size; i++)
	{
		newspells[i] = spells[i];
	}
	capacity = newcapacity;
	delete[] spells;
	spells = newspells;

}
Book::Book()
{
	spells = NULL;
	size = 0;
	capacity = 1;
	spells = new Spell[1];
}

Book::Book(const Book& b)
{
	spells = new Spell[b.capacity];
	for (int i = 0; i < b.size; i++)
	{
		spells[i] = b.spells[i];
	}
	size = b.size;
	capacity = b.capacity;
}

Book& Book::operator=(const Book& b)
{
	if (this != &b)
	{
		delete[] spells;
		size = 0;
		capacity = 1;
		spells = new Spell[b.capacity];
		for (int i = 0; i < b.size; i++)
		{
			spells[i] = b.spells[i];
		}
		size = b.size;
		capacity = b.capacity;
	}
	return *this;
}

Book::~Book()
{
	delete[] spells;
}

void Book::add(const Spell& s)
{
	change();
	spells[size] = s;
	size++;
}


void Book::remove(const int index)
{
	if (index < 0 || index > size)
		cout << "Wrong index.";
	for (int j = index; j < size - 1; j++)
	{
		spells[j] = spells[j + 1];
	}
	size--;
	change();
}

int Book::getSize()const
{
	return size;
}

int Book::ManaForSpell(const int index)const
{
	if (index < 0 || index > size)
		cout << "Wrong index.";
	return spells[index].getMana();
}

void Book::sort()
{
	for (int i = 0; i < size - 1; i++)
		for (int j = i + 1; j < size; j++)
		if (spells[i].getMana() > spells[j].getMana())
		{
			Spell tmp = spells[i];
			spells[i] = spells[j];
			spells[j] = tmp;
		}
}