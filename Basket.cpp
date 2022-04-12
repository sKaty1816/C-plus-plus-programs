#include "Basket.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
using namespace std;
const int INITIAL = 4;

Basket::Basket()
{
	name = NULL;
	size = 0;
	capacity = INITIAL;
	yolk = NULL;
	setName("");
	reserve(capacity);
}

Basket::Basket(const Basket & bask)
{
	name = NULL;
	yolk = NULL;
	setName(bask.name);
	reserve(bask.capacity);
	addData(bask.yolk, size);
}

Basket& Basket::operator=(const Basket & other)
{
	if (this != &other)
	{
		setName(other.name);
		reserve(other.capacity);
		addData(other.yolk, other.size);
	}
	return *this;
}

Basket::~Basket()
{
	delete[] name;
	delete[] yolk;
}

Basket::Basket(const char* n)
{
	size = 0;
	capacity = INITIAL;
	name = NULL;
	yolk = NULL;
	setName(n);
	reserve(capacity);
}

void Basket::setName(const char * str)
{
	char* n_name = new char[strlen(str) + 1];
	if (!n_name) return;
	strcpy(n_name, str);
	delete[] name;
	name = n_name;
}
//Allocates enough memory to contain at least n_cap eggs.
void Basket::reserve(int n_cap)
{
	if (yolk && n_cap <= capacity) return;
	int s = pow(2, ceil(log(n_cap) / log(2)));
	n_cap = s;
	Egg* n_yolk = new Egg[n_cap];
	if (!n_yolk) return;
	delete[] yolk;
	size = 0;
	capacity = n_cap;
	yolk = n_yolk;
}

void Basket::addData(Egg* eg, int s)
{
	for (int i = size; i < s; i++)
		add(eg[i]);
}

void Basket::resize(int n)
{
	capacity = n;
	Egg* n_yolk = new Egg[capacity];
	if (!n_yolk) return;
	for (int i = 0; i < size; i++)
		n_yolk[i] = yolk[i];
	delete[] yolk;
	yolk = n_yolk;
}

void Basket::add(const Egg& eg)
{
	if (size >= capacity)
		resize(capacity * 2);
	yolk[size] = eg;
	size++;
}

void Basket::remove(const char* str)
{
	for (int i = 0; i < size; i++)
	{
		if (strcmp(str, yolk[i].getName()) == 0)
		{
			if (i + 1 != size)
			for (int j = i; j < size; j++)
				yolk[j] = yolk[j + 1];
			size--;
			break;
		}
	}
	if (size <= capacity / 4)
		resize(capacity / 2);
}

void Basket::report()
{
	char* prefix = "report_";
	char* suffix = ".txt";
	int len = strlen(prefix) + strlen(suffix) + strlen(name);
	char* fname = new char[len + 1];
	if (!fname) return;
	strcpy(fname, prefix);
	strcat(fname, name);
	strcat(fname, suffix);
	ofstream out(fname, ios::out);
	delete[] fname;
	if (!out)
	{
		cerr << "Error opening file " << fname << " for writing!\n";
		return;
	}
	for (int i = 0; i < size; i++)
	{
		out << yolk[i].getName() << " " << yolk[i].getSize() << endl;
	}
}

int Basket::binSize() const
{
	int s = 0;
	s += strlen(name) + 1;
	for (int i = 0; i < size; i++)
	{
		s += yolk[i].binSize();
	}
	return s;
}

void Basket::serialize(char* d)
{
	memcpy(d, name, strlen(name) + 1); //Copies the values of strlen(name) + 1 bytes from the location pointed to
	d += strlen(name) + 1;			   //by name directly to the memory block pointed to by d.
	memcpy(d, &size, sizeof(size));
	d += sizeof(size);
	int len;
	for (int i = 0; i < size; i++)
	{
		len = yolk[i].length();
		memcpy(d, yolk[i].getName(), len + 1);
		d += len + 1;
		int t = yolk[i].getSize();
		memcpy(d, &t, sizeof(int));
		d += sizeof(int);
	}
}

void Basket::deserialize(const char* d)
{
	setName(d);
	d += strlen(name) + 1;
	int amount = 0;
	memcpy(&amount, d, sizeof(int));
	d += sizeof(int);
	reserve(amount);
	Egg e;
	int tmp;
	for (int i = 0; i < amount; i++)
	{
		e.setName(d);
		d += e.length() + 1;
		memcpy(&tmp, d, sizeof(int));
		d += sizeof(int);
		e.setSize(tmp);
		add(e);
	}
}

char* Basket::getBName()const
{
	return name;
}

Egg Basket::operator[](int index) const
{
	if (index<0 || index>size)
		cout << "Invalid index." << endl;
	return yolk[index];
}

Egg& Basket::operator[](const char* str)const
{
	for (int i = 0; i < size; i++)
	if (strcmp(yolk[i].getName(), str) == 0)
		return yolk[i];
}

Basket& Basket::operator+=(const Basket& b)
{
	int sizenew = strlen(name) + strlen(b.name) + 1;
	char* newName = new char[sizenew + 1];
	strcpy(newName, name);
	strcat(newName, b.name);
	setName(newName);
	delete[] newName;
	for (int i = 0; i < b.size; i++)
		this->add(b[i]);
	return *this;
}

Basket& Basket::operator+=(const char* str)
{
	for (int i = 0; i < size; i++)
	{
		yolk[i] += str;
	}
	return *this;
}

Basket& Basket::operator*=(const int num)
{
	for (int i = 0; i < size; i++)
	{
		yolk[i] *= num;
	}
	return *this;
}

Basket& Basket::operator/=(const int num)
{
	for (int i = 0; i < size; i++)
	{
		yolk[i] /= num;
	}
	return *this;
}

Basket& Basket::operator%=(const Basket& b)
{
	bool cut=false;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < b.size; j++)
		{
			if (yolk[i] == b.yolk[j])
			{
				cut = true;
				break;
			}
		}
		if (cut == false)
		{
			this->remove(yolk[i].getName());
			i -= 1;
		}
		cut = false;
	}
	return *this;
}

Basket operator+(const Basket& one, const Basket& two)
{
	Basket nb = one;
	nb += two;
	return nb;
}

Basket operator+(const Basket& one, const char* str)
{
	Basket nb = one;
	nb += str;
	return nb;
}

Basket operator*(const Basket& one, const int num)
{
	Basket nb = one;
	nb *= num;
	return nb;
}

Basket operator/(const Basket& one, const int num)
{
	Basket nb = one;
	nb /= num;
	return nb;
}

Basket operator%(const Basket& one, const Basket& two)
{
	Basket nb = one;
	nb %= two;
	return nb;
}

int Basket::getBSize() const
{
	return size;
}

bool operator==(const Basket& one, const Basket& two)
{
	if (one.getBSize() != two.getBSize())
		return false;
	for (int i = 0; i < one.getBSize(); i++)
	{
		if (one[i] != two[i])
			return false;
	}
	return true;
}

bool operator!=(const Basket& one, const Basket& two)
{
	return !(one == two);
}

bool operator<(const Basket& one, const Basket& two)
{
	if (one == two)
	{
		return false;
	}
	else
		return one <= two;

}

bool operator<=(const Basket& one, const Basket& two)
{
	int onesize = one.getBSize();
	int twosize = two.getBSize();
	if (onesize != twosize && onesize == fmin(onesize, twosize))
	{
		return true;
	}
	if (one == two)
	{
		for (int i = 0; i < onesize; i++)
		{
			if (one[i] < two[i])
				return false;
		}
		return true;
	}
	else
		return false;
}

bool operator>=(const Basket& one, const Basket& two)
{
	if (one == two)
		return true;
	else
		return !(one <= two);
}
