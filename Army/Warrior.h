#ifndef WARRIOR_H
#define WARRIOR_H

class Warrior
{
private:
	char *name;
	int age;
	int level;
	int gold;
public:
	Warrior();
	Warrior(const char*, const int, const int, const int);
	Warrior(const Warrior&);
	Warrior& operator=(const Warrior&);
	~Warrior();
	char* getName()const;
	int getAge()const;
	int getLevel()const;
	int getGold()const;
	void setName(const char*);
	void setAge(const int);
	void setLevel(const int);
	void setGold(const int);
};

#endif