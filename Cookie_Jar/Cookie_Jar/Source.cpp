#include "Cookie.h"
#include "Jar.h"
#include <iostream>

int main() {

	Cookie c1;
	c1.addFeature("crunchy");
	c1.addFeature("oreo");
	c1.printCookie();

	Cookie c2;
	c2.addFeature("caramel");
	c2.addFeature("milka");
	c2.printCookie();
	//c2 = c1;
	//c2.printCookie();

	Cookie c3;
	c3 = c1;
	c3.printCookie();
	c3.addFeature("chocolate");
	c3.printCookie();

	Jar newJar;
	newJar.putCookie(c1);
	newJar.putCookie(c2);
	newJar.putCookie(c3);
	newJar.printJar();
	newJar.takeCookie();
	newJar.takeCookie();
	newJar.takeCookie();
	newJar.takeCookie();
	newJar.takeCookie();
	newJar.printJar();
	newJar.putCookie(c1);
	newJar.printJar();

	return 0;
}
