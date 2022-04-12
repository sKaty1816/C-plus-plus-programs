#ifndef EGG_H
#define EGG_H

class Egg
{
private:
	char* name;
	int size;
public:
	Egg();
	Egg(const Egg&);
	Egg& operator= (const Egg&);
	~Egg();
	void setName(const char*);
	void setSize(int);
	const char* getName() const;
	int getSize();
	int length() const;
	int binSize() const;
public:
	Egg& operator+=(const char*);
	Egg& operator*=(const int);
	Egg& operator/=(const int);
};

bool operator==(const Egg&, const Egg&);
bool operator!=(const Egg&, const Egg&);
bool operator<(const Egg&, const Egg&);
bool operator>(const Egg&, const Egg&);
Egg operator+(const Egg&, const char*);
Egg operator*(const Egg&, const int);
Egg operator/(const Egg&, const int);


#endif 