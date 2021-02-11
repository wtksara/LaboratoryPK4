#pragma once
#include <iostream>
#include <string>

using namespace std;


template <class A, class B, class C>

A mix(A x, B y, C z) {
    x += (A)z;
    x -= (A)y;
    return x;
}

template <class T>
class Lista {

    T* glowa;

public:

    Lista () : glowa(nullptr) {}
    ~Lista () { delete_all_items(); }

    void add_item (string nazwa);
    void delete_all_items();
};

class Toy
{
    string Name;

public:
    Toy* next;
    Toy(string name) :Name(name), next(nullptr) {}
    string getName() { return Name; }
};


class Country
{
    string Name;

public:
    Country* next;
    Country(string name) :Name(name), next(nullptr) {}
    string getName() { return Name; }
};


class Person
{
    string Name;

public:
    Person* next;
    Person(string name) :Name(name), next(nullptr) {}
    string getName() { return Name; }
};


template <class T>
void Lista <T>::add_item(string nazwa)
{
	T* nowy = new T(nazwa);
	cout << "Added item " << nowy->getName() << endl;
	if (glowa == nullptr)
	{
		glowa = nowy;
	}
	else {
		T* ptr = glowa;
		while (ptr->next != nullptr) {
			ptr = ptr->next;
		}
		ptr->next = nowy;
	}
}

template <class T>
void Lista <T>::delete_all_items()
{
	T* ptr = glowa;
	while (ptr != nullptr)
	{
		glowa = glowa->next;
		cout << "Deleted item " << ptr->getName() << endl;
		delete ptr;
		ptr = glowa;
	}
}