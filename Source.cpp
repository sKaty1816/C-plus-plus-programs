#include <iostream>
#include "Egg.h"
#include "Basket.h"
#include <cstring>
using namespace std;

const int COM = 10;
const int ES = 1000;

Basket setobj1()
{
	Egg e;
	Basket b("Stavri");
	e.setName("a");
	e.setSize(1);
	b.add(e);

	e.setName("b");
	e.setSize(2);
	b.add(e);

	e.setName("c");
	e.setSize(3);
	b.add(e);

	return b;
}

Basket setobj2()
{
	Egg e;
	Basket b("Bunny");
	e.setName("d");
	e.setSize(4);
	b.add(e);

	e.setName("e");
	e.setSize(5);
	b.add(e);

	e.setName("f");
	e.setSize(6);
	b.add(e);

	return b;
}

void Demo1(Basket& db, Egg& de)
{
	cout << endl << "Demonstrate operator[int]" << endl;
	de = db[0];
	cout << de.getName() << " " << de.getSize() << endl;
}

void Demo2(Basket& db, Egg& de)
{
	cout << endl << "Demonstrate operator[char*]" << endl;
	de = db["a"];
	cout << de.getName() << " " << de.getSize() << endl;
}

void Demo3()
{
	Basket b, newb;
	cout << endl << "Demonstrate operator+=(cosnt Basket&)" << endl;
	b = setobj1();
	newb = setobj2();
	b += newb;
	cout << b.getBName() << endl;
	for (int i = 0; i < b.getBSize(); i++)
		cout << b[i].getName() << " " << b[i].getSize() << endl;
}

void Demo4()
{
	Basket b, newb1;
	cout << endl << "Demonstrate operator+(cosnt Basket&, const Basket&)" << endl;
	b = setobj1();
	newb1 = setobj2();
	Basket result;
	result = b + newb1;
	cout << result.getBName() << endl;
	for (int i = 0; i < result.getBSize(); i++)
		cout << result[i].getName() << " " << result[i].getSize() << endl;
}

void Demo5()
{
	Basket b;
	cout << endl << "Demonstrate operator+=(cosnt char*)" << endl;
	b = setobj1();
	char *str = "string";
	b += str;
	cout << b.getBName() << endl;
	for (int i = 0; i < b.getBSize(); i++)
		cout << b[i].getName() << " " << b[i].getSize() << endl;
}

void Demo6()
{
	Basket b;
	cout << endl << "Test operator*=(cosnt int)" << endl;
	b = setobj1();
	int num = 3;
	b *= num;
	cout << b.getBName() << endl;
	for (int i = 0; i < b.getBSize(); i++)
		cout << b[i].getName() << " " << b[i].getSize() << endl;
}

void Demo7()
{
	Basket b;
	cout << endl << "Test operator*(cosnt Basket&, const int)" << endl;
	b = setobj1();
	int num = 3;
	Basket newb;
	newb = b * num;
	cout << newb.getBName() << endl;
	for (int i = 0; i < newb.getBSize(); i++)
		cout << newb[i].getName() << " " << newb[i].getSize() << endl;
}

void Demo8()
{
	Basket b;
	cout << endl << "Demonstrate operator/=(cosnt int)" << endl;
	b = setobj1();
	int num = 2;
	b /= num;
	cout << b.getBName() << endl;
	for (int i = 0; i < b.getBSize(); i++)
		cout << b[i].getName() << " " << b[i].getSize() << endl;
}

void Demo9()
{
	Basket b;
	cout << endl << "Demonstrate operator/(cosnt Basket&, const int)" << endl;
	b = setobj1();
	Basket newb;
	int num = 2;
	newb = b / num;
	cout << newb.getBName() << endl;
	for (int i = 0; i < newb.getBSize(); i++)
		cout << newb[i].getName() << " " << newb[i].getSize() << endl;
}

void Demo10()
{
	cout << endl << "Demonstrate operator%=(cosnt Basket&, const int)" << endl;
	Basket b, newb;
	b = setobj1();
	newb = setobj2();
	b %= newb;
	cout << b.getBName() << endl;
	for (int i = 0; i < b.getBSize(); i++)
		cout << b[i].getName() << " " << b[i].getSize() << endl;
}

void Demo11()
{
	Basket b, newb;
	cout << endl << "Demonstrate operator%(cosnt Basket&, const Basket&)" << endl;
	b = setobj1();
	newb = setobj2();
	Basket result;
	result = b % newb;
	cout << result.getBName() << endl;
	for (int i = 0; i < result.getBSize(); i++)
		cout << result[i].getName() << " " << result[i].getSize() << endl;
}

void Demo12()
{
	Basket b, newb;
	cout << endl << "Demonstrate operator==(cosnt Basket&, const Basket&)" << endl;
	b = setobj1();
	newb = setobj2();
	if (newb == b)
		cout << "They are equal" << endl;
	else
		cout << "They are Not equal" << endl;
}

void Demo13()
{
	Basket b, newb;
	cout << endl << "Demonstrate operator!=(cosnt Basket&, const Basket&)" << endl;
	b = setobj1();
	newb = setobj2();
	if (newb != b)
		cout << "They are Not equal" << endl;
	else
		cout << "They are equal" << endl;
}

void Demo14()
{
	Basket b, newb;
	cout << endl << "Demonstrate operator<(cosnt Basket&, const Basket&)" << endl;
	b = setobj1();
	newb = setobj2();
	if (b < newb)
		cout << "The left is less" << endl;
	else
		cout << "The left is Not less" << endl;
}

void Demo15()
{
	Basket b, newb;
	cout << endl << "Demonstrate operator<(cosnt Basket&, const Basket&)" << endl;
	b = setobj1();
	newb = setobj2();
	if (b <= newb)
		cout << "The left is less or they are equal" << endl;
	else
		cout << "The left is Not less and they are Not equal" << endl;
}

void Demo16()
{
	Basket b, newb;
	cout << endl << "Demonstrate operator>=(cosnt Basket&, const Basket&)" << endl;
	b = setobj1();
	newb = setobj2();
	if (b >= newb)
		cout << "The left is greater or they are equal" << endl;
	else
		cout << "The left is Not greater and they are Not equal" << endl;
}

int main()
{
	Basket b("Rabbit");
	Egg e;
	char command[COM];
	char eggstring[ES];
	int big;
	cout << "To add an egg enter 'add'" << endl
		<< "To remove an egg enter 'remove'" << endl
		<< "To get a report enter 'report'" << endl
		<< "To end the program enter 'end'" << endl;
	while (true)
	{
		cin.getline(command, COM);
		if (strcmp(command, "add") == 0)
		{
			cout << "Name: ";
			cin.getline(eggstring, ES);
			cout << "Size: ";
			cin >> big;
			e.setName(eggstring);
			e.setSize(big);
			b.add(e);
		}
		else if (strcmp(command, "remove") == 0)
		{
			cout << "Name: ";
			cin.getline(eggstring, ES);
			b.remove(eggstring);
		}
		else if (strcmp(command, "report") == 0)
		{
			b.report();
			cout << "Report generated.\n";
		}
		else if (strcmp(command, "end") == 0)
		{
			break;
		}
	}
	cout << "\nSerializing & Deserializing in progress... \n";
	char* s = new char[b.binSize()];
	b.serialize(s);
	Basket g;
	g.deserialize(s);
	g.setName("Deserialized");
	g.report();
	Demo1(b, e);
	Demo2(b, e);
	Demo3();
	Demo4();
	Demo5();
	Demo6();
	Demo7();
	Demo8();
	Demo9();
	Demo10();
	Demo11();
	Demo12();
	Demo13();
	Demo14();
	Demo15();
	Demo16();
	system("pause");
	return 0;
}
