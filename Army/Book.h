#ifndef BOOK_H
#define BOOK_H
#include "Spell.h"

class Book
{
private:
	Spell* spells;
	int size;
	int capacity;
	Spell operator[](const int)const;
	void change();
public:
	Book();
	Book(const Book&);
	Book& operator=(const Book&);
	~Book();
	void add(const Spell&);
	void remove(const int);
	int getSize()const;
	int ManaForSpell(const int)const;
	void sort();
};

#endif