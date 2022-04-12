#ifndef BASKET_H
#define BASKET_H
#include "Egg.h"

class Basket
{
private:
	char* name;
	Egg* yolk;
	int size;
	int capacity;
	void resize(int);
	void addData(Egg* data, int);
public:
	Basket();
	Basket(const Basket&);
	Basket& operator=(const Basket&);
	~Basket();
	Basket(const char*);
	void setName(const char*);
	void reserve(int);
	void add(const Egg&);
	void remove(const char*);
	void report();
	void serialize(char*);
	void deserialize(const char*);
	int binSize() const;
	char* getBName()const;
	int getBSize() const;
public: //operators
	Egg operator[](int)const;
	Egg& operator[](const char*)const;
	Basket& operator+=(const Basket&);
	Basket& operator+=(const char*);
	Basket& operator*=(const int);
	Basket& operator/=(const int);
	Basket& operator%=(const Basket&);
};

Basket operator+(const Basket&, const Basket&);
Basket operator+(const Basket&, const char*);  
Basket operator*(const Basket&, const int);	   	
Basket operator/(const Basket&, const int);   
Basket operator%(const Basket&, const Basket&);
bool operator==(const Basket&, const Basket&);
bool operator!=(const Basket&, const Basket&);
bool operator<(const Basket&, const Basket&);
bool operator<=(const Basket&, const Basket&);
bool operator>=(const Basket&, const Basket&);

#endif 