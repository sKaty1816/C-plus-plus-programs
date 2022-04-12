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
#ifndef ELEVATOR_H
#define ELEVATOR_H
#include "Dynamic_Array.h"
#include <string>
#include "Queue.h"
using namespace std;

void case1(Dyn_arr &arr_time, Dyn_arr &arr_floors)
{
	for (int i = 0; i < arr_time.size(); i++)
	{
		cout << arr_time[i] << " " << arr_floors[i] << " down"<<endl;
	}
}

void elevator(Dyn_arr &arr_time, Dyn_arr &arr_floors, int N, Queue& seconds, Queue& floors)
{
	int currentFloor = 1;
	int clock = arr_time[0];
	int item;
	string direction;
	while (arr_floors.size()>0)
	{
		item = arr_floors.peek();
		direction = (item >= currentFloor) ? "up" : "down";
		while (currentFloor != item)
		{
			(direction == "up") ? currentFloor++ : currentFloor--;
			clock += 5;
			for (int z = 0; z < arr_time.size(); z++)
			{
				if (clock >= arr_time[z] && currentFloor == arr_floors[z])
				{
					if (floors.back() != currentFloor)
					{
						seconds.enqueue(clock);
						floors.enqueue(currentFloor);
					}
					arr_time.erase(z, z + 1);
					arr_floors.erase(z, z + 1);
					z--;
				} //end of if
			} //end of Z for
		} //end of Y for	
	} //end of X for
}

void print(Queue& seconds, Queue& floors)
{
	int item1, item2;
	int currentFloor = 1;
	while (!seconds.empty() && !floors.empty())
	{
		seconds.dequeue(item1);
		cout << item1 << " ";
		floors.dequeue(item2);
		cout << item2 << " ";
		if (currentFloor > item2) cout << "down";
		else cout << "up";
		currentFloor = item2;
		cout << endl;
	}
}
#endif