/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Ekaterina Kirilova
* @idnumber 45074
* @task 2
* @compiler VC
*
*/


#include <iostream>
#include <fstream>
#include "Queue.h"
#include <string>
#include "Dynamic_Array.h"
#include "Elevator.h"
using namespace std;

int main(int argc, char** argv)
{

	ifstream file(argv[1], ios::in);
	if (!file)
	{
		cout << argv[1] << " can't open.\n";
		return 1;
	}
	int N, K;
	file >> N >> K;
	string request;
	Dyn_arr arr_time;
	Dyn_arr arr_floors;
	Queue seconds(N);
	Queue floors(N);
	string direction;
	int floor;
	int time;
	while (!file.eof())
	{
		file >> request;
		if (request == "call")
		{
			file >> direction >> floor >> time;
			arr_time.push_back(time);
			arr_floors.push_back(floor);
		}
		else if (request == "go")
		{
			file >> floor >> time;
			arr_time.push_back(time);
			arr_floors.push_back(floor);
		}
	}
	file.close();
	if (N == 1) case1(arr_time, arr_floors);
	else 
	{
		elevator(arr_time, arr_floors, N, seconds, floors);
		print(seconds, floors);
	}

	system("pause");
	return 0;
}