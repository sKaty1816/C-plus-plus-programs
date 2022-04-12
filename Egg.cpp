#include "Egg.h"
#include <string.h>
#include <new>

Egg::Egg()
{
	name = NULL;
	size = 0;
}

Egg::Egg(const Egg& eg)
{
	name = NULL;
	size = eg.size;
	setName(eg.name);
}

Egg& Egg::operator=(const Egg & eg)
{
	if (this != &eg)
	{
		size = eg.size;
		setName(eg.name);
	}

	return *this;
}

Egg::~Egg()
{
	delete[] name;
}

void Egg::setName(const char* n)
{
	if (n == NULL) return;
	char* tmp = new char[strlen(n) + 1];
	if (!tmp) return;
	strcpy(tmp, n);
	delete[] name;
	name = tmp;
}

void Egg::setSize(int s)
{
	size = s;
}

const char* Egg::getName() const
{
	return name;
}

int Egg::getSize()
{
	return size;
}

int Egg::length() const
{
	return strlen(name);
}

int Egg::binSize() const
{
	return length() + sizeof(size)+1;
}

Egg& Egg::operator+=(const char* str)
{
	int sizenew = strlen(name) + strlen(str) + 1;
	char *newName = new char[sizenew + 1];
	strcpy(newName, name);
	strcat(newName, str);
	setName(newName);
	delete[] newName;
	return *this;
}

Egg& Egg::operator*=(const int num)
{
	size *= num;
	return *this;
}

Egg& Egg::operator/=(const int num)
{
	size /= num;
	return *this;
}

bool operator==(const Egg& one, const Egg& two)
{
	if (strcmp(one.getName(), two.getName()) == 0)
		return true;
	else
		return false;
}

bool operator!=(const Egg& one, const Egg& two)
{
	return !(one == two);
}

bool operator<(const Egg& one, const Egg& two)
{
	if (strcmp(one.getName(), two.getName()) < 0)
		return false;
	else
		return true;
}

bool operator>(const Egg& one, const Egg& two)
{
	return !(one > two);
}

Egg operator+(const Egg& one, const char* str)
{
	Egg newegg = one;
	newegg += str;
	return newegg;
}

Egg operator*(const Egg& one, const int num)
{
	Egg newegg = one;
	newegg *= num;
	return newegg;
}

Egg operator/(const Egg& one, const int num)
{
	Egg newegg = one;
	newegg /= num;
	return newegg;
}
