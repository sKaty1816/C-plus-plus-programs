#ifndef SPELL_H
#define SPELL_H

class Spell
{
private:
	char* description;
	char* type;
	int mana;
public:
	Spell();
	Spell(const char*, const char*, const int);
	Spell(const Spell&);
	Spell& operator=(const Spell&);
	~Spell();
	char* getDescription()const;
	char* getType()const;
	int getMana()const;
};

#endif