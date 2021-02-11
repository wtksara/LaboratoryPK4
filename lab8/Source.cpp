#include <iostream>
#include <string>
#include <regex>
#include <conio.h>
using std::regex;
using std::smatch;

/*Zadanie 1.
Napisz funkcjê, która sprawdzi, czy ci¹g znaków jest poprawnym numerem domu
Przyjmij ¿e poprawny numer domu sk³ada siê z dodatniej liczby dziesiêtnej (patrz prezentacja),
po której mo¿e wyst¹piæ 0 lub wiêcej ma³ych lub wielkich liter.
Wykorzystaj funkcjê regex_match.
*/
bool sprawdz_nr_domu(const std::string& nr_domu) {
	regex numer_domu("[1-9][0-9]*[a-zA-Z]*");
	bool czy_poprawny = std::regex_match(nr_domu, numer_domu);
	return czy_poprawny;
}

/*Zadanie 2.
Napisz funkcjê, która znajduje kod pocztowy w adresie.
Funkcja powinna zwróciæ znaleziony kod pocztowy lub ci¹g "nie znaleziono"
Wykorzystaj funkcjê regex_search.
*/
std::string znajdz_kod_pocztowy(const std::string& adres) {

	std::string padres = adres;
	regex kod_pocztowy("[0-9]{2}-[0-9]{3}");
	smatch kod;
	std::string znaleziony_kod;
	int i = 0;
	if (!(regex_search(padres, kod, kod_pocztowy))) {
		return "nie znaleziono";
	}
	else {
		while (regex_search(padres, kod, kod_pocztowy)) {
			for (auto x : kod) {
				std::string pkod;
				pkod = kod[0];
				znaleziony_kod.append(pkod);
				znaleziony_kod.push_back(' / ');
				padres = kod.suffix().str();
			}
		}
		return znaleziony_kod;
	}
}

/*Zadanie 3.
Wykonaj dwa razy funkcjê regex_search: raz dla str, m1 i r1, a drugi raz dla str, m2 i r2
SprawdŸ, jaki wynik zwraca metoda size() dla m1 i m2 oraz jaki tekst znajduje siê w m1[0], m2[0], m2[1] i m2[2]
Napisz w komentarzu, do jakiej czêœci wyra¿enia r2 dopasowany zosta³ tekst w m2[0], m2[1] i m2[2]
*/
void zadanie_search() {
	std::regex r1("a+5c{1,3}");
	std::regex r2("(a+)5(c{1,3})");
	std::string str("ac 5c aaa5cc aa5d");
	std::smatch m1, m2;

	std::regex_search(str, m1, r1);
	std::regex_search(str, m2, r2);
	std::cout << "m1.size(): " << m1.size() << std::endl;
	std::cout << "m2.size(): " << m2.size() << std::endl;
	std::cout << "Tekst w m1[0]: " << m1[0] << std::endl;
	std::cout << "Tekst w m2[0]: " << m2[0] << std::endl;
	std::cout << "Tekst w m2[1]: " << m2[1] << std::endl;
	std::cout << "Tekst w m2[2]: " << m2[2] << std::endl;
	//Tekst w m2[0] zosta³ dopasowany ca³ego wyra¿enia r2
	//Tekst w m2[1] zosta³ dopasowany do pierwszej grupy (a+)
	//Tekst w m2[2] zosta³ dopasowany do drugiej grupy (c{1,3})
}

/*Zadanie 4.
Napisz funkcjê, która wypisze do std::cout wszystkie hashtagi z tekstu. Wykorzystaj std::sregex_iterator.
Przyjmij, ¿e hashtag sk³ada siê ze znaku #,
po którym wystêpuje co najmniej jeden znak niebêd¹cy znakiem niedrukowalnym (\\S)
*/
void wypisz_hashtagi(const std::string& tekst) {

	std::string ptekst = tekst;
	regex hashtag("#\\S+");
	smatch hashtagi;
	while (regex_search(ptekst, hashtagi, hashtag)) {
		for (auto x : hashtagi) {
			std::cout << hashtagi[0] << " "; 
			ptekst = hashtagi.suffix().str();
		}
	}
	std::cout << std::endl;
}

/*Zadanie 5.
Napisz funkcjê, zmieni format godziny z zapisu z kropk¹ (np. 13.45) na zapis z dwukropkiem (13:45).
Wykorzystaj funkcjê regex_replace.
Uwaga: w wyra¿eniu regularnym znak "." oznacza dowolny znak. Kropkê oznaczamy przez "\\.".
*/
std::string zmien_format(const std::string& tekst) {
	regex godzina("([0-9]{1,2})\\.([0-9]{1,2})");
	std::string zmiana("$1:$2");
	std::string wynik = std::regex_replace(tekst, godzina, zmiana);
	return wynik;
}

//W funkcji main znajduje siê kod do testowania funkcji wraz z oczekiwanymi wynikami
int main()
{
	std::cout << std::boolalpha;
	//Zadanie 1.
	
	std::cout << "Zadanie 1 (numer domu)" << std::endl;
	std::cout << "2 " << sprawdz_nr_domu("2") << std::endl;			//true
	std::cout << "88af " << sprawdz_nr_domu("88af") << std::endl;	//true
	std::cout << "06b " << sprawdz_nr_domu("06b") << std::endl;		//false
	std::cout << "x " << sprawdz_nr_domu("x") << std::endl;			//false
	std::cout << std::endl;
	

	//Zadanie 2.
	
	std::string adres1("Akademicka 2A, 44-100 Gliwice");
	std::string adres2("245-67 23-505 44-555");
	std::string adres3("Za siedmioma gorami");

	std::cout << "Zadanie 2 (znajdz adres)" << std::endl;
	std::cout << znajdz_kod_pocztowy(adres1) << std::endl << std::endl;			//44-100

	std::cout << znajdz_kod_pocztowy(adres2) << std::endl;			//23-505 
	std::cout << "Tu chyba jeszcze musi byc 44-555 bo to tez kod pocztowy \n\n";
	std::cout << znajdz_kod_pocztowy(adres3) << std::endl;			//nie znaleziono
	std::cout << std::endl;
	

	//Zadanie 3.
	
	std::cout << "Zadanie 3" << std::endl;
	zadanie_search();
	std::cout << std::endl;
	

	//Zadanie 4.
	
	std::cout << "Zadanie 4 (hashtagi)" << std::endl;
	wypisz_hashtagi("#a kot Filemon #+30% #hot16challenge");
	//Wynik: #a #+30% #hot16challenge
	std::cout << std::endl;
	

	//Zadanie 5.
	
	std::cout << "Zadanie 5 (zmiana formatu godziny)" << std::endl;
	std::string tekst_czas("Ich stehe um 7.00 Uhr auf. Ich esse das Abendessen um 21.00 Uhr und ich gehe zu Bett um 23.30 Uhr.");
	std::cout << zmien_format(tekst_czas) << std::endl;
	//Wynik: "Ich stehe um 7:00 Uhr auf. Ich esse das Abendessen um 21:00 Uhr und ich gehe zu Bett um 23:30 Uhr.
	
}

