#include <iostream>
#include <string>
using namespace std;
#include "Warrior.h"
#include "Sergeant.h"
#include "Spell.h"
#include "Book.h"
#include "Sorcerer.h"
#include "Commander.h"

int main()
{
	Warrior* A = new Warrior[5];
	A[0] = Warrior("Warrior1", 20, 3, 2012);
	A[1] = Warrior("Warrior2", 29, 10, 2894);
	A[2] = Warrior("Warrior3", 42, 4, 2598);
	A[3] = Warrior("Warrior4", 67, 1, 1087);
	A[4] = Warrior("Warrior5", 32, 6, 2661);
	
	Sergeant* B = new Sergeant[5];
	B[0] = Sergeant ("Serg1", 38, 16, 3957, "squad1", A, 5);
	B[1] = Sergeant("Serg2", 22, 15, 3529, "squad2", A, 5);
	B[2] = Sergeant("Serg3", 39, 14, 3513, "squad3", A, 5);
	B[3] = Sergeant("Serg4", 50, 11, 3151, "squad4", A, 5);
	B[4] = Sergeant("Serg5", 31, 13, 3422, "squad5", A, 5);

	Spell C1("Fireball", "Fire", 21);
	Spell C2("Inferno", "Fire", 311);
	Spell C3("Shift", "Shapeshift", 243);
	Spell C4("Fear", "Entropy", 177);
	Spell C5("Purify", "Heal", 50);

	Book D;
	D.add(C1);
	D.add(C2);
	D.add(C3);
	D.add(C4);
	D.add(C5);
	
	Sorcerer* E = new Sorcerer[5];
	E[0] = Sorcerer("Mag1", 94, 48, 5728, "M1", B, 5, 194, D);
	E[1] = Sorcerer("Mag2", 91, 38, 5664, "M2", B, 5, 161, D);
	E[2] = Sorcerer("Mag3", 60, 49, 6587, "M3", B, 5, 277, D);
	E[3] = Sorcerer("Mag4", 73, 32, 5581, "M4", B, 5, 485, D);
	E[4] = Sorcerer("Mag5", 68, 33, 5612, "M5", B, 5, 422, D);

	Commander F("Com", 44, 50, 10000, "Army", E, 5);

	cout << "Sum lvl: " << F.sumLevels() << endl;
	cout << "Average lvl: " << F.averageLvl() << endl;
	cout << "Sum Mana: " << F.sumMana() << endl;
	cout << "Average Mana: " << F.averageMana() << endl;
	cout << "Sum gold: " << F.sumGold() << endl;
	cout << "Sum Max Spells: " << F.sumMaxSpells() << endl;
	system("pause");
	return 0;
}
