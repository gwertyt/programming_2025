#include <iostream>
#include <string>

using namespace std;

class Player {
private:
    string name;
    int x;
    int y;

protected:
    int hp;
    string status;

public:
    Player() {
        name = "кто-то";
        x = 0;
        y = 0;
        hp = 100;
        status = "ничего не делает";
    }

    Player(const string& n, int posX, int posY, int health, const string& stat) {
        name = n;
        x = posX;
        y = posY;
        hp = health;
        status = stat;
    }

    Player(const Player& other) {
        name = other.name;
        x = other.x;
        y = other.y;
        hp = other.hp;
        status = other.status;
    }

    ~Player() {
        cout << "исчез " << name << endl;
    }

    string getName() const {
        return name;
    }

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    int getHP() const {
        return hp;
    }

    string getStatus() const {
        return status;
    }

    void setName(const string& newName) {
        if (!newName.empty()) {
            name = newName;
        }
    }

    void setPosition(int newX, int newY) {
        x = newX;
        y = newY;
    }

    void setHP(int newHP) {
        if (newHP >= 0 && newHP <= 100) {
            hp = newHP;
        }
    }

    void setStatus(const string& newStatus) {
        status = newStatus;
    }

    void printInfo() const {
        cout << "Имя: " << name << endl;
        cout << "Позиция: (" << x << ", " << y << ")" << endl;
        cout << "Здоровье: " << hp << endl;
        cout << "Статус: " << status << endl;
    }

    void takeDamage(int damage) {
        if (damage > 0 && hp>0) {
            hp -= damage;
            if (hp <= 0) {
                hp = 0;
                status = "мертв";
            }
            else if (hp < 20) {
                status = "тяжело ранен";
            }
        }
    }

    void heal(int amount) {
        if (amount > 0 && hp>0) {
            hp += amount;
            if (hp > 100) {
                hp = 100;
            }
            if (hp >= 20 && status !="мертв") {
                status = "активен";
            }
        }
    }
};

int main() {

    Player player1;
    player1.printInfo();
    cout << endl;

    Player player2("игрок2", 10, 20, 75, "в бою");
    player2.printInfo();
    cout << endl;

    Player player3 = player2;
    player3.printInfo();
    cout << endl;

    player2.takeDamage(30);
    player2.printInfo();
    cout << endl;

    player2.heal(50);
    player2.printInfo();
    cout << endl;

    player2.setPosition(100, 200);
    player2.printInfo();

    return 0;
}
