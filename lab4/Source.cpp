#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <utility>
#include <random>
using namespace std;

class Car
{
private:
	double przebieg;
	int rocznik;
	string model;
public:
	double get_p() { return this->przebieg; };
	int get_r() { return this->rocznik; };
	string get_s() { return this->model; };
	Car(double przebieg, int rocznik, std::string model) :przebieg(przebieg), rocznik(rocznik), model(model) {};
	Car() {
		this->przebieg = 0.0;
		this->rocznik = 0;
		this->model = " ";
	};

	virtual~Car() {
		std::cout << "Usunieto " << this->model << std::endl;
	};
	friend std::ostream& operator<<(std::ostream& out, Car& car)
	{
		return out << "Int: " << car.get_r() << " Double: " << car.get_p() << " String: " << car.get_s() << std::endl;
	}
};

struct usun
{

	bool operator ()(Car* c1)
	{
		if (c1->get_p() > 200000) return true;
		return false;

	}
};


void wyswietl(list<Car*>& lista);

int main()
{
	// Zadanie 1
	vector<vector<int>>wektor;
	int size;
	cout << "Podaj rozmiar tabliczki mnozenia (x na x) ";
	cin >> size;
	wektor.reserve(size);
	int wielkosc = wektor.capacity();

	for (int i = 0; i < wielkosc; i++) {

		vector<int>column;
		for (int j = 0; j < wielkosc; j++) {

			wektor.push_back(column);
			wektor.at(j).push_back((i + 1) * (j + 1));
		}
	}
	for (int i = 0; i < wektor.size(); i++)
	{
		for (int j = 0; j < wektor[i].size(); j++)
		{
			cout << wektor[i][j] << " ";
		}
		cout << endl;
	}


	// Zadanie 2
	vector<Car*>carsone;
	for (int i = 0; i < 5; i++) {
		Car* example = new Car();
		carsone.push_back(example);
	}
	vector<Car*>carstwo(8);
	for (int i = 0; i < 8; i++) {
		Car* example = new Car();
		carstwo[i] = example;
	}
	cout << "VECTOR ONE SIZE  " << carsone.size() << endl;
	cout << "VECTOR TWO SIZE  " << carstwo.size() << endl;

	carsone.swap(carstwo);
	cout << "SWAP\n";
	cout << "VECTOR ONE SIZE  " << carsone.size() << endl;
	cout << "VECTOR TWO SIZE  " << carstwo.size() << endl;

	// Sprzatanie
	for (vector<Car*>::iterator clean = carsone.begin(); clean != carsone.end(); clean++) {
		Car* car = *clean;
		delete car;
	}
	carsone.clear();
	for (vector<Car*>::iterator clean = carstwo.begin(); clean != carstwo.end(); clean++) {
		Car* car = *clean;
		delete car;
	}
	carstwo.clear();

	//Zadanie 3
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(1, 200000);
	list <Car*> cars;
	for (int i = 0; i < 25; i++) {
		int n = distribution(generator);
		int number = (n + 100000);
		int number1 = (rand() % 67) + 1950;
		string name = "VECTRA" + to_string(i);
		cars.push_front(new Car(number, number1, name));
	}

	wyswietl(cars);
	// Sortowanie
	cars.sort();
	wyswietl(cars);
	// Usuwanie
	usun przebieg;
	cars.remove_if(przebieg);
	wyswietl(cars);

	list<Car*> newcars;
	wyswietl(newcars);
	// Zamien
	newcars.swap(cars);
	wyswietl(newcars);

	// Sprzatanie
	for (list<Car*>::iterator clean = cars.begin(); clean != cars.end(); clean++) {
		Car* car = *clean;
		delete car;
	}
	cars.clear();
	for (list<Car*>::iterator clean = newcars.begin(); clean != newcars.end(); clean++) {
		Car* car = *clean;
		delete car;
	}
	newcars.clear();
}

void wyswietl(list<Car*>& lista)
{
	cout << endl << "LISTA: " << endl << endl;
	list<Car*>::iterator i;
	for (i = lista.begin(); i != lista.end(); i++)
	{
		cout << **i << endl;
	}

}

/*
Zadanie 1
Zrobi� prost� tabliczk� mno�enia o wymiarach podanych przez u�ytkownika. Do jej utworzenia wykorzysta� dwuwymiarow� tablic� zrobion� z wektor�w. Ustawi� rozmiar tablicy za pomoc� funkcji reserve().

Zadanie 2
Utw�rz wektor zawieraj�cy 5 wska�nik�w na klas� samoch�d. U�yj funkcji push_back. Nast�pnie zr�b to samo 8 razy za pomoc� operatora []. Sprawd� rozmiar ka�dego z wektor�w, zamie� je miejscami (swap) i sprawd� ponownie. Wy�wietl rezultaty.

Zadanie 3
Utw�rz list� zawieraj�c� 25 wska�nik�w na obiekt typu Samoch�d. Obiekty dodawaj na pocz�tek listy. Warto�� przebiegu ma by� generowana losowo z zakresu od 100000 do 300000, a wieku od 1950 do 2016.
wy�wietl zawarto�� listy. Posortuj Samochody funkcji sort(). Usu� samocgody z przebiegiem powy�ej200000 za pomoc� funkcji remove_if(). Utw�rz now�, pust� list� i zamie� jej warto�ci z poprzedni�.

*/
