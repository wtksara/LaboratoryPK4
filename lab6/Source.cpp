// ZadaniaIntWsk.cpp : Ten plik zawiera funkcjê „main”. W nim rozpoczyna siê i koñczy wykonywanie programu.
//

#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <random>
//#include "vld.h"

class Zombie {
    float hp;
    bool alive = true;
    std::string name = "Zombie";

public:

    static int howMany;
    Zombie(float hp) :hp(hp) { name = name + std::to_string(howMany); howMany++; }
    Zombie() = delete;

    float GetHp() { return hp; }

    void ChangeHp(float dmg) {
        this->hp -= dmg;
        if (hp <= 0)this->alive = false;
    }

    bool IsAlive() { return alive; }

    void ShowZombie() { std::cout << "Nazwa :" << name << " Hp:" << hp << IsAlive() << std::endl; }

    ~Zombie() {
        std::cout << "Destruktor" << std::endl;
        ShowZombie();
    }
};

bool SortByHp(std::unique_ptr <Zombie>& p, std::unique_ptr <Zombie>& p2) {
    return p->GetHp() > p2->GetHp();
}
class Weapon
{
public:
    virtual void Shoot(std::vector<std::unique_ptr <Zombie>>& enemy) = 0;
    virtual void ShowParam() = 0;
};

class Shotgun : public Weapon {
    float dmg;
public:
    Shotgun(float dmg) :dmg(dmg) { std::cout << "Konstruktor Shotgun" << std::endl; }
    Shotgun() = delete;

    void Shoot(std::vector<std::unique_ptr <Zombie>>& enemy) override {
        for (auto& oponent : enemy) {
            oponent->ChangeHp(dmg);
            if (!oponent->IsAlive()) {
                std::sort(std::begin(enemy), std::end(enemy), SortByHp);
                enemy.pop_back();
            }
        }
    }
    void ShowParam() override {
        std::cout << "DMG: " << dmg << " Nazwa broni: " << typeid(*this).name() << std::endl;
    }
};

void ShowVect(std::vector<std::unique_ptr <Zombie>>& enemy) {
    for (auto& p : enemy) {
        if (p)
            p->ShowZombie();
    }
}
class Player {

    std::unique_ptr<Weapon>& gun;
    float hp;

public:
    Player() = delete;
    Player(float hp, std::unique_ptr<Weapon>& gun) :hp(hp), gun(gun) {};
    void Shot(std::vector<std::unique_ptr <Zombie>>& enemy) {
        gun->Shoot(enemy);
    }

};

void Inicjalizer(int howMany, std::vector<std::unique_ptr <Zombie>>& vec) {

    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_real_distribution<float>distribution(1.0, 100.0);
    for (int i = 0; i < howMany; i++) {
        vec.emplace_back(std::move(new Zombie(distribution(generator))));
    }
}

int Zombie::howMany = 0;

int main()
{
    //Zadanie 1 tutaj zadeklaruj wskaŸnik
    std::unique_ptr<Weapon> gun = std::make_unique<Shotgun>(15.0f);

    //Zadanie 2
    Player player(200, gun);

    //Zadanie 3
    std::vector<std::unique_ptr <Zombie>> zombies;
    Inicjalizer(15, zombies);

    //Zadanie 4
    while (!zombies.empty()) {
        ShowVect(zombies);
        player.Shot(zombies);
    }


    //Zadanie 7
    std::weak_ptr <Zombie> wp;

    {//pojedyncze klamry
        //Zadanie 5

        std::shared_ptr<Zombie> sp = std::make_shared<Zombie>(100.0);
        std::cout << sp.use_count() << std::endl;
        wp = sp;
        std::cout << wp.use_count() << std::endl;

        {//podwójne klamry
            //Zadanie 6

            std::shared_ptr<Zombie> spp;
            spp = sp;
            std::cout << spp.use_count() << std::endl;
            std::cout << sp.use_count() << std::endl;
        }

        std::cout << sp.use_count() << std::endl;
    }

    //Zadanie 8
    std::cout << wp.use_count() << std::endl;
    std::cout << "Uzycie use_count() dla pointera wp zwrocilo wartosc 0, poniewaz to, ¿e weak_ptr wskazuje na dan¹ wartosc nie zwieksza jej licznika referencji.";
}


//1. Zadeklaruj unikalny wskaŸnik typu Weapon na obiekt Shotgun przy pomocy metody make_unique.
//2. Napisz Konstruktor przyjmuj¹cy jako argumenty float hp oraz unikalny wskaŸnik na broñ typu Weapon inicjalizuj¹cy obiekt Player.I utwórz obiekt player.
//3. Napisz funkcjê Inicjalizuj¹c¹ wektor unikalnych wskaŸników na obiekt Zombie wykorzystuj¹c podany silnik liczb losowych do nadania ¿ycia ka¿demu z zombie.
//4. Zaimplementuj Metodê Shoot przyjmuj¹c¹ jako argument vektor unikalnych wskaŸników, która ka¿demu z Zombie odejmuje ¿ycie (U¿yj metody ChangeHp), 
//   gdy ¿ycie zombie jest mniejsze b¹dŸ równe 0 usuñ wskaŸnik z wektora metod¹ pop_back. SprawdŸ czy w ten sposób powstaj¹ wycieki pamiêci np. programem vld.
//5. Zadeklaruj shared pointer typu Zombie o nazwie sp na nowy obiekt maj¹cy 100 HP wewn¹trz pojedynczych klamr nastêpnie wypisz licznik referencji tego wskaŸnika za pomoc¹ metody use_count().
//6. Zadeklaruj shared pointer typu Zombie o nazwie spp wewn¹trz podwójnych klamr,
//   przypisz do spp wskaŸnik sp i wypisz licznik referencji obu z nich po czym po zamkniêciu podwójnej klamry wypisz licznik referencji sp.
//7. Zadeklaruj weak pointer typu Zombie o nazwie wp przed klamrami nastêpnie wewn¹trz klamr pojedynczych przypisz do niego wartoœæ pointera sp, 
//   wypisz jego licznik referencji wewn¹trz klamr.
//8. Spróbuj wypisaæ licznik referencji pointera wp poza klamrami wypisz coutem dlaczego use_count() zwróci³ tak¹ wartoœæ
