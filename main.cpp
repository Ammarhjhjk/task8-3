#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>

using namespace std;

class Weapon {
private:
    string name;
    int damage;
    int accuracy;
    string description;

public:
    Weapon(string n, int d, int acc, string desc) 
        : name(n), damage(d), accuracy(acc), description(desc) {}

    string getName() const { return name; }
    int getDamage() const { return damage; }
    int getAccuracy() const { return accuracy; }
    string getDescription() const { return description; }

    bool willHit() const {
        return (rand() % 100) < accuracy;
    }
};

class Character {
protected:
    string name;
    int health;
    vector<Weapon> weapons;

public:
    Character(string n, int h) : name(n), health(h) {}

    string getName() const { return name; }
    int getHealth() const { return health; }
    vector<Weapon> getWeapons() const { return weapons; }

    void addWeapon(Weapon weapon) {
        weapons.push_back(weapon);
    }

    void takeDamage(int damage) {
        health -= damage;
        if (health < 0) health = 0;
    }

    bool isAlive() const {
        return health > 0;
    }

    virtual void attack(Character& opponent) {
        if (weapons.empty()) return;

        int weaponIndex = rand() % weapons.size();
        Weapon selectedWeapon = weapons[weaponIndex];

        cout << name << " uses " << selectedWeapon.getName() << "..." << endl;
        this_thread::sleep_for(chrono::milliseconds(800));

        if (selectedWeapon.willHit()) {
            cout << "✅ HIT! (" << selectedWeapon.getDescription() << ")" << endl;
            opponent.takeDamage(selectedWeapon.getDamage());
            cout << "❤️  " << opponent.getName() << "'s health: " << opponent.getHealth() << endl;
        } else {
            cout << "❌ MISSED!" << endl;
        }
    }

    virtual ~Character() {}
};

class OptimusPrime : public Character {
public:
    OptimusPrime() : Character("Optimus Prime", 100) {
        addWeapon(Weapon("Ion Rifle", 6, 100, "Precise energy rifle that rarely misses"));
        addWeapon(Weapon("Energon Swords", 12, 80, "Powerful energy swords for close combat"));
        addWeapon(Weapon("Shoulder Canon", 45, 25, "Powerful but inaccurate shoulder cannon"));
    }
};

class Megatron : public Character {
public:
    Megatron() : Character("Megatron", 100) {
        addWeapon(Weapon("Fusion Cannon", 9, 90, "Strong and accurate fusion cannon"));
        addWeapon(Weapon("Fusion Sword", 18, 70, "Sharp fusion sword for close combat"));
        addWeapon(Weapon("Tank Mode", 60, 15, "Destructive but inaccurate tank mode"));
    }
};

void simulateBattle(OptimusPrime& optimus, Megatron& megatron) {
    cout << "===== BATTLE BEGINS =====" << endl;
    cout << optimus.getName() << " vs " << megatron.getName() << endl;
    cout << "=========================" << endl << endl;

    srand(time(0));

    while (optimus.isAlive() && megatron.isAlive()) {
        cout << "--- Optimus Prime's Turn ---" << endl;
        optimus.attack(megatron);
        cout << endl;
        
        if (!megatron.isAlive()) break;
        
        this_thread::sleep_for(chrono::milliseconds(1000));
        
        cout << "--- Megatron's Turn ---" << endl;
        megatron.attack(optimus);
        cout << endl;
        
        this_thread::sleep_for(chrono::milliseconds(1000));
    }

    cout << "===== BATTLE RESULT =====" << endl;
    if (optimus.isAlive()) {
        cout << "🎉 Optimus Prime Wins!" << endl;
        cout << "Remaining health: " << optimus.getHealth() << endl;
    } else {
        cout << "💀 Megatron Wins!" << endl;
        cout << "Remaining health: " << megatron.getHealth() << endl;
    }
}

int main() {
    OptimusPrime optimus;
    Megatron megatron;
    
    simulateBattle(optimus, megatron);
    
    return 0;
}
