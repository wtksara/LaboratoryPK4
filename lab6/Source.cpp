// ZadaniaIntWsk.cpp : Ten plik zawiera funkcj� �main�. W nim rozpoczyna si� i ko�czy wykonywanie programu.
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
    //Zadanie 1 tutaj zadeklaruj wska�nik
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

        {//podw�jne klamry
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
    std::cout << "Uzycie use_count() dla pointera wp zwrocilo wartosc 0, poniewaz to, �e weak_ptr wskazuje na dan� wartosc nie zwieksza jej licznika referencji.";
}


//1. Zadeklaruj unikalny wska�nik typu Weapon na obiekt Shotgun przy pomocy metody make_unique.
//2. Napisz Konstruktor przyjmuj�cy jako argumenty float hp oraz unikalny wska�nik na bro� typu Weapon inicjalizuj�cy obiekt Player.I utw�rz obiekt player.
//3. Napisz funkcj� Inicjalizuj�c� wektor unikalnych wska�nik�w na obiekt Zombie wykorzystuj�c podany silnik liczb losowych do nadania �ycia ka�demu z zombie.
//4. Zaimplementuj Metod� Shoot przyjmuj�c� jako argument vektor unikalnych wska�nik�w, kt�ra ka�demu z Zombie odejmuje �ycie (U�yj metody ChangeHp), 
//   gdy �ycie zombie jest mniejsze b�d� r�wne 0 usu� wska�nik z wektora metod� pop_back. Sprawd� czy w ten spos�b powstaj� wycieki pami�ci np. programem vld.
//5. Zadeklaruj shared pointer typu Zombie o nazwie sp na nowy obiekt maj�cy 100 HP wewn�trz pojedynczych klamr nast�pnie wypisz licznik referencji tego wska�nika za pomoc� metody use_count().
//6. Zadeklaruj shared pointer typu Zombie o nazwie spp wewn�trz podw�jnych klamr,
//   przypisz do spp wska�nik sp i wypisz licznik referencji obu z nich po czym po zamkni�ciu podw�jnej klamry wypisz licznik referencji sp.
//7. Zadeklaruj weak pointer typu Zombie o nazwie wp przed klamrami nast�pnie wewn�trz klamr pojedynczych przypisz do niego warto�� pointera sp, 
//   wypisz jego licznik referencji wewn�trz klamr.
//8. Spr�buj wypisa� licznik referencji pointera wp poza klamrami wypisz coutem dlaczego use_count() zwr�ci� tak� warto��
