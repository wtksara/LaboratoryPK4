#include <iostream>
#include <string>
#include "hello.h"

using namespace std;

int main()
{
    // Testy do Zad 1
    cout<<mix('!',3,50)<<endl;
    cout<<mix('@',79,90)<<endl;
    cout<<mix(2947.20,2963.55,20.35)<<endl<<endl;

     //Testy do Zad 2 i 3
    Lista<Toy> lista_zabawek;
    Lista<Country> lista_panstw;
    Lista<Person> lista_osob;

    lista_zabawek.add_item("Mis");
    lista_zabawek.add_item("Lalka");
    lista_zabawek.add_item("Konik");

    lista_panstw.add_item("Polska");
    lista_panstw.add_item("Anglia");
    lista_panstw.add_item("Rosja");

    lista_osob.add_item("Jan");
    lista_osob.add_item("Ewa");
    lista_osob.add_item("Andrzej");
    cout<<endl;

    

    return 0;
}

/*
Zad 1.
Zadeklarowaæ i zdefiniowaæ funkcjê "mix", która przymuje 3 argumenty (kazdy z nich moze byc innego typu), nastepnie do pierwszego argumentu dodaje wartosc trzeciego,
a nastepnie od powstalego wyniku odejmuje wartosc drugiego argumentu. Na koniec funkcja zwraca otrzymany wynik w postaci (formacie) pierwszego argumentu.
UWAGA! Warto pamiêtaæ, aby "przerobiæ" typ zmiennej dodawanej lub odejmowanej na typ tej, na której operujemy (do ktorej dodajemy lub odejmujemy).

Zad 2.
Zadeklarowac klase "Lista", ktora moze sluzyc do zarzadzania lista jednokierunkowa obiektow klas Toy, Country i Person zadeklarowanych powyzej.
Klasa "Lista" powinna posiadac prywatny wskaznik na "glowe" listy, oraz publiczny konstruktor, ktory ustawia ta "glowe" na nullptr (lista inicjalizacyjna).
Publiczne maja byc tez 2 funkcje:
-add_item, ktora za argument przyjmuje nazwe dodawanego elementu
-delete_all_items, ktora nie przyjmuje zadnych argumentow
Nalezy tez zdefiniowac destruktor, ktory wywoluje funkcje delete_all_items.

Zad 3.
Zdefiniowac funkcje add_item oraz delete_all_items. WAZNE - nalezy to zrobic poza cialem klasy.
-funkcja add_item powinna tworzyc nowy obiekt klasy i nadac mu nazwe, ktora przyjmuje jako argument.
    Dodatkowo funkcja zaraz po utworzeniu nowego obiektu (jeszcze przed dodaniem go do listy) powinna wyswietlic komunikat "Added item (nazwa)".
    Nastepnie funkcja powinna umiescic nowo utworzony obiekt na koncu listy.
-funkcja delete_all_items powinna usunac wszystkie obiekty z listy, a przy usuwaniu kazdego z nich nalezy wyswietlic komunikat "Deleted item (nazwa)"
WAZNE - nalezy skorzystac z funkcji getName(), ktora zadeklarowana jest w kazdej klasie.


OGOLNE
W dostepnym kodzie nie nalezy niczego zmieniac. Po wykonaniu zadania nalezy odkomentowac odpowiedni fragment kodu z funkcji main() i skompilowaæ.
Oczekiwane rezultaty przedstawione sa w udostepnionych materialach.
*/

