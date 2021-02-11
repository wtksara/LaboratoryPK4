#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <mutex>
#include <math.h>
#include <chrono>

using namespace std;

class Foo {

	int ilosc_wywolan = 0;
	vector<thread> th;

public:

	Foo(const int rozmiar);

	void join() {
		for (int i = 0; i < th.size(); i++) {
			th[i].join();
		}
	}

	void wyswietl_klasa() {

		int _liczba = ilosc_wywolan++;

		for (int i = 0; i < 5; i++)
			cout << "Foo: " + to_string(_liczba) + "\n";
	}

};

void wyswietl_10x(string napis) {

	for (int i = 0; i < 10; i++) {
		cout << napis + "\n";
	}

}

void wyswietl(string napis, int liczba) {

	for (int i = 0; i < liczba; i++) {
		cout << napis + "\n";
	}

}

void inkrementuj(int& liczba) {
	while (true) {
		liczba++;
		if (liczba > 50)
			break;
	}
}


//////////////////////////
// KOD PONI¯EJ MO¯NA EDYTOWAÆ

//////////////////////////
//ZAD1: Wyœwietl liczbê w¹tków, które mog¹ byæ wykonywane równolegle przez CPU na Twoim komputerze. Skorzystaj z metody podanej na prezentacji.
void zadanie_1() {

	cout << "ZAD 1 \n";
	cout << "Twoja liczba watkow: ";
	cout << thread::hardware_concurrency() << endl; // Moja liczba w¹tków wynosi 4.
}

//////////////////////////
//ZAD2: Stwórz 2 w¹tki w których u¿yjesz funkcji wyswietl_10x(string napis) aby wyœwietliæ napisy "Pierwszy" i "Drugi". Nastêpnie odpowiedz na pytanie dlaczego napis "Drugi" niekiedy pojawia siê przed napisem "Pierwszy". OdpowiedŸ wyœwietl w cout. 
void zadanie_2() {

	cout << "ZAD 2 \n";
	thread thread1(wyswietl_10x, "Pierwszy"), thread2(wyswietl_10x, "Drugi"); 
	thread1.join(); 
	thread2.join(); 
	cout << "Koniec glownego watku! Dlaczego napis \"Drugi\" niekiedy pojawia sie przed napisem \"Pierwszy\"?" << endl;
	cout << "Oby dwa watki dzialaja rownolegle, sa rozne i ich wyniki moga sie przeplatac. Aby uzyskaæ kontrole na wykonywaniem w¹tkow nalezalo by zastosowac jawne blokowanie - muteksy."<<endl;
			
}

//////////////////////////
//ZAD3: Stwórz 2 w¹tki u¿ywaj¹c funkcji inkrementuj(int liczba) aby zmieniæ wartoœæ liczby a. U¿yj do tego std::ref.
void zadanie_3() {

	cout << "ZAD 3 \n";

	int a = 0;
	thread thread1(inkrementuj, ref(a)), thread2(inkrementuj, ref(a));
	thread1.join();
	thread2.join();
	cout << "Liczba a wynosi " << a << endl;

}

//////////////////////////
//ZAD4: U¿ywaj¹c wy³¹cznie metod detach i join, wyœwietl napis "Trzeci" po wypisaniu 10 napisów "Pierwszy", a napis "Drugi" wyœwietla³ siê niezale¿nie od g³ównego w¹tku. 
void zadanie_4() {

	cout << "ZAD 4 \n";

	thread watek_1(wyswietl, "Pierwszy", 10), watek_2(wyswietl, "Drugi", 20);
	watek_2.detach();
	watek_1.join();
	thread watek_3(wyswietl, "Trzeci", 10);

	watek_3.join();

}

//////////////////////////
//ZAD5: Zdefiniuj konstruktor dla klasy Foo, który bêdzie tworzy³ w¹tki w wektorze th o rozmiarze wartoœci zmiennej rozmiar. W¹tki maj¹ byæ tworzone na podstawie metody klasy Foo wyswietl_klasa(). Nastêpnie stwórz obiekt tej klasy i wywo³aj potrzebne metody.
Foo::Foo(const int rozmiar) {

	ilosc_wywolan = 0;

	//ZAD 5
	this->th.reserve(rozmiar);
	for (int i = 0; i < rozmiar; i++) {
		this->th.emplace_back(&Foo::wyswietl_klasa, this);
	}
}

void zadanie_5() {

	cout << "ZAD 5 \n";
	Foo nowy(10);
	nowy.join();
}

//////////////////////////
//ZAD6: Popraw klasê Bar tak aby zakomentowany kod w funkcji zadanie_6() dzia³a³ i po jego u¿yciu wyœwietla³ siê wynik sumy x i y.
class Bar {

	int x;
	int y;

public:

	Bar(int _x, int _y) : x(_x), y(_y) {}

	void operator()() {
		cout << x + y << endl;
	}

};

void zadanie_6() {

	Bar obiekt(5, 6);
	thread th(obiekt);
	th.join();

}

//////////////////////////
//ZAD7: U¿ywaj¹c wy³¹cznie klasy mutex, zrób tak aby zawsze siê wyœwietla³ prostok¹t z znaków 'X'

mutex pmutex;
void rysuj_linie() {

	pmutex.lock();
	for (int i = 0; i <= 20; i++) {
		cout << 'X';
	}

	cout << "\n";
	pmutex.unlock();
}

void zadanie_7() {

	thread th_1(rysuj_linie);
	thread th_2(rysuj_linie);
	thread th_3(rysuj_linie);
	thread th_4(rysuj_linie);

	th_1.join();
	th_2.join();
	th_3.join();
	th_4.join();

}

//////////////////////////
//ZAD8: U¿ywaj¹c wy³¹cznie klasy mutex i lock_guard odpowiednio zablokuj dostêp do zmiennej globalnej w funkcja_wyjatek(int a). Nastêpnie zdefiniuj vector w¹tków (iloœæ 8) w funkcji zadanie_8() u¿ywaj¹c metody funkcja_wyjatek(int a).

double globalna_zmienna = 100;
mutex pmutex2;

void funkcja_wyjatek(int a) {

	lock_guard<mutex> lockm(pmutex2);
	if (a == 0) {
		return;
	}

	while (globalna_zmienna > a) {
		globalna_zmienna -= a;
	}

	std::cout << globalna_zmienna << endl;

}

void zadanie_8() {

	vector<thread> threads;

	for (int i = 8; i >= 0; i--) {
		threads.push_back(std::thread(funkcja_wyjatek, i));
	}

	for (int i = 0; i < threads.size(); i++) {
		threads[i].join();
	}

}

//////////////////////////
//ZAD9: Napisaæ funkcjê o nazwie watek_id, która bêdzie wyœwietla³a w konsoli id danego w¹tku. Nastêpnie stworzyæ jeden w¹tek na podstawie tej funkcji w zadanie_9()

void watek_id() {
	cout << this_thread::get_id() << endl;
}

void zadanie_9() {
	thread th(watek_id);
	th.join();

}


//////////////////////////

int main() {

	//UWAGA, wszystkie zadania z w¹tkami nale¿y uruchamiaæ pojedynczo!

	/*zadanie_1();*/
	/*zadanie_2();*/
	/*zadanie_3();*/
	/*zadanie_4();*/
	/*zadanie_5();*/
	/*zadanie_6();*/
	/*zadanie_7();*/
	/*zadanie_8();*/
	zadanie_9();

	return 0;
}
