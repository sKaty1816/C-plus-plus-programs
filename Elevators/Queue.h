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
#ifndef QUEUE_H
#define QUEUE_H
#include <cstdlib>
using namespace std;
#include <iostream>

class Queue
{
private:
	int q_size; //max queue size
	int q_len;	//current queue size
	int q_front; //index to first element
	int q_back; //index to last element
	int *q_arr; //dynamic array 
	
public:
	Queue(int);
	~Queue();
	bool empty();
	void enqueue(const int&);
	void dequeue(int&);
	int back() const;
	int size() const;
};

Queue::Queue(int size)
{
	q_size = (size <= 0) ? 10 : size;
	q_arr = new int[q_size];
	q_front = -1;
	q_back = -1;
	q_len = 0;
}

Queue::~Queue()
{
	delete[]q_arr;
}

bool Queue::empty()
{
	return (q_len == 0);
}

void Queue::enqueue(const int& item)
{
		q_back = (q_back + 1) % q_size;
		q_arr[q_back] = item;
		q_len++;

}

void Queue::dequeue(int& item)
{
	if (empty())
	{
		std::cout << "The queue is empty.\n";
		exit(1);
	}
	else
	{
		q_front = (q_front + 1) % q_size;
		item = q_arr[q_front];
		q_len--;
	}
}

int Queue::back() const
{
	return q_arr[q_back];
}

#endif