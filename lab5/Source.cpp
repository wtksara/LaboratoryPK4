//
//  main.cpp
//  zadanie.cpp
//
//  Created by Stanislaw Czembor on 03/05/2020.
//  Copyright © 2020 Stanislaw Czembor. All rights reserved.
//

#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <iomanip>

struct movie
{
    std::string title;
    std::vector<int> ratings;
};

void show(int i) {
    std::cout << ' ' << i;
}

void change(int& i) {
    if (i != 1) {
        i = i / 2;
    }
}

//zad1 a,b
std::vector<movie> prepareData(std::vector<movie> filmweb, std::vector<movie> rooten)
{
    std::vector<movie> toReturn{};

    std::cout << "FILMWEB \n\n\n";

    for (std::vector <movie>::iterator itr = filmweb.begin(); itr != filmweb.end(); itr++) {
        sort(itr->ratings.begin(), itr->ratings.end());
        std::cout << "PRZED USUNIECIEM \n";
        std::for_each(begin(itr->ratings), end(itr->ratings), show);
        itr->ratings.erase(
            remove_if(itr->ratings.begin(), itr->ratings.end(), [](int i) { return (i > 10) || (i < 1); }), itr->ratings.end());
        std::cout << "\nPO USUNIECIU \n";
        std::for_each(begin(itr->ratings), end(itr->ratings), show);
        std::cout << " \nZMIANA OCEN \n";
        std::for_each(begin(itr->ratings), end(itr->ratings), change);
        std::for_each(begin(itr->ratings), end(itr->ratings), show);
        std::cout << "\n\n";
    }
    toReturn.insert(toReturn.begin(), filmweb.begin(), filmweb.end());
    std::vector <movie>::iterator pat = toReturn.begin();

    std::cout << "ROOTEN \n\n\n";

    for (std::vector <movie>::iterator itr = rooten.begin(); itr != rooten.end(); itr++) {
        std::cout << "PRZED USUNIECIEM \n";
        sort(itr->ratings.begin(), itr->ratings.end());
        std::for_each(begin(itr->ratings), end(itr->ratings), show);
        sort(itr->ratings.begin(), itr->ratings.end());
        itr->ratings.erase(
            remove_if(itr->ratings.begin(), itr->ratings.end(), [](int i) { return (i > 5) || (i < 1); }), itr->ratings.end());
        std::cout << "\nPO USUNIECIU \n";
        std::for_each(begin(itr->ratings), end(itr->ratings), show);
        std::cout << "\n\n";
        pat->ratings.insert(pat->ratings.end(), itr->ratings.begin(), itr->ratings.end());
        pat++;
    }

    std::cout << "\n\nOCENY FILMOW PO ZMIANIE \n";
    for (pat = toReturn.begin(); pat != toReturn.end(); pat++) {
        std::cout << pat->title << std::endl;
        sort(pat->ratings.begin(), pat->ratings.end());
        std::cout << "Oceny : ";
        std::for_each(begin(pat->ratings), end(pat->ratings), show);
        std::cout << "\n\n";
    }

    return toReturn;
}

//zad1 c
double truncatedMean(std::vector<int> values, double const percentage)
{
    double toReturn;

    int obciecie = (int)((values.size() * percentage) / 2);
    int rozmiar = values.size() - (2 * obciecie);
    int sum = 0;
    sum = accumulate(values.begin() + obciecie, values.end() - obciecie, sum);
    toReturn = sum / (double)rozmiar;
    return toReturn;
}

void printMovieRatings(std::vector<movie> const& movies)
{
    std::cout << " \n\nRANKING \n";
    for (auto const& m : movies)
    {
        std::cout << m.title << " : "
            << std::fixed << std::setprecision(1)
            << truncatedMean(m.ratings, 0.05) << std::endl << std::endl;
    }
}

//zad2
void printPermutations(std::string str)
{
    std::cout << " \n\nPERMUTACJE \n";
    std::sort(str.begin(), str.end());
    do {
        std::cout << str << '\n';
    } while (std::next_permutation(str.begin(), str.end()));
}

int main()
{
    std::vector<movie> filmweb
    {
        {"The Matrix", {-1,0,0,0,0,0,0,1,1,10, 9, 10, 9, 9, 8, 7, 10, 5, 9, 9, 8} },
        {"Gladiator", {-5,0,0,10, 5, 7, 8, 9, 8, 9, 10, 10, 5, 9, 8, 10} },
        {"Interstellar", {-1,10, 10, 10, 9, 3, 8, 8, 9, 6, 4, 7, 10}}
    };
    std::vector<movie> rooten
    {
        {"The Matrix", {2,3,5,2,3,4,4,4,5,0,0,0,0} },
        {"Gladiator", {-1,2,3,3,4,3,2,5,1,3,4} },
        {"Interstellar", {0,0,0,0,5,5,3,3,4,5,2,3,4,5}}
    };

    printMovieRatings(prepareData(filmweb, rooten));

    printPermutations("main");

    return 0;
}
/*
1. Otrzymaliœmy dwie bazy danych z ocenami filmów. Jedna pochodzi z serwisu filmweb (skala ocen 1-10),
 druga z serwisu rottentomatoes (skala ocen 1-5). Naszym zadaniem jest:
a) usunaæ z ka¿dej z baz oceny wykraczaj¹ce poza sklale np. -1,300,
b) scaliæ dwie bazy danych w jedn¹ w taki sposób ¿eby wartoœci ocen siê zgadza³y tj ocena 10 z filmweb by³a równa ocene 5 z rooten,
 podpunkty a i b zrealizowaæ uzuep³niaj¹c cia³o funkcji UpdateData. funkcja zwraca vector ze scalonymi, przygotowanymi danymi do liczenia œredniej.
c) obliczyæ œredni¹ ucinan¹(trymowan¹) odrzucaj¹c procent skrajnych wartoœci przekazany jako parametr funkcji uzupe³niaj¹c cia³o funkcji truncatedMean
 Przydatne algorytmy w zad 1:
 -sort
 -remove_if,
 -for_each,
 -merge,
 -erase - metoda klasy kontenera
 -acumulate.
 info o œredniej ucinanej :https://pl.wikipedia.org/wiki/Œrednia_ucinana
 Do wypisania œredniej ocen filmów u¿yæ funkcji printMovieRatings
2. Uzupe³niæ ca³o funkcji wypisuj¹cej wszystkie permutacje s³owa przekazanego przez parametr. printPermuattions
Przydatne algorytmy potrzebne w zad 2:
 -sort,
 -next_permutation.*/


