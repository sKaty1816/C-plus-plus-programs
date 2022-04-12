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
#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H
#include <cassert>
#include <stddef.h>

class Dyn_arr
{
private:
	//data
	int* data_;
	int size_;
	int capacity_;

	//methods
	void init_();
	void copy_(const Dyn_arr& other);
	void reserve_(int capacity);
	int compare_(const Dyn_arr& other) const;

public:
	//constructors
	Dyn_arr();
	//copy constructor
	Dyn_arr(const Dyn_arr& other);
	//assignment operator
	Dyn_arr& operator=(const Dyn_arr& other);
	//destructor
	~Dyn_arr();

	//accessors
	int size() const;
	bool empty() const;
	int& operator[](int index) const;

	//modifiers
	void push_back(const int& value);
	void erase(int first, int last);
	int peek();

	// Comparison operators
	bool operator < (const Dyn_arr& other) const;
	bool operator > (const Dyn_arr& other) const;
	bool operator == (const Dyn_arr& other) const;
};
//private methods
void Dyn_arr::init_()
{
	data_ = NULL;
	size_ = capacity_ = 0;
}

void Dyn_arr::copy_(const Dyn_arr& other)
{
	delete[] data_;
	data_ = NULL;
	size_ = capacity_ = 0;
	reserve_(other.size_);
	size_ = other.size_;
	for (int i = 0; i < size_; i++)
		data_[i] = other.data_[i];
}

void Dyn_arr::reserve_(int capacity)
{
	capacity = (capacity <= 0 ? 1 : capacity);
	if (capacity <= capacity_) return;
	int* data = new int[capacity];
	capacity_ = capacity;
	for (int i = 0; i < size_; i++)
		data[i] = data_[i];
	delete[] data_;
	data_ = data;
}

int Dyn_arr::compare_(const Dyn_arr& other) const
{
	int minSize = (size_ < other.size_ ? size_ : other.size_);
	for (int i = 0; i < minSize; i++)
	{
		if (data_[i] < other.data_[i])
			return -1;
		if (other.data_[i] < data_[i])
			return +1;
	}
	if (size_ != other.size_)
		return size_ < other.size_ ? -1 : +1;
	return 0;
}
//public methods
Dyn_arr::Dyn_arr()
{
	init_();
}

Dyn_arr::Dyn_arr(const Dyn_arr& other)
{
	init_();
	copy_(other);
}

Dyn_arr& Dyn_arr::operator=(const Dyn_arr& other)
{
	if (this != &other)
		copy_(other);
	return *this;
}

Dyn_arr::~Dyn_arr()
{
	delete[] data_;
	data_ = NULL;
	size_ = capacity_ = 0;
}

int Dyn_arr::size() const
{
	return size_;
}

bool Dyn_arr::empty() const
{
	return !size_;
}

int& Dyn_arr::operator[](int index) const
{
	
	return data_[index];
}

void Dyn_arr::push_back(const int& value)
{
	if (size_ >= capacity_)
		reserve_(capacity_ * 2);
	data_[size_] = value;
	size_++;
}

int Dyn_arr::peek()
{
	int item = data_[0];
	return item;
}

void Dyn_arr::erase(int first, int last = -1)
{
	first = (first < 0 ? 0 : first);
	last = (last < 0 ? first + 1 : last);
	if (first >= size_ || last <= first)
		return;
	for (int i = last; i < size_; i++)
		data_[first + i - last] = data_[i];
	size_ = size_ - (last - first);
}

bool Dyn_arr::operator<(const Dyn_arr& other) const
{
	return compare_(other) < 0;
}

bool Dyn_arr::operator>(const Dyn_arr& other) const
{
	return compare_(other) > 0;
}

bool Dyn_arr::operator==(const Dyn_arr& other) const
{
	return compare_(other) == 0;
}

#endif