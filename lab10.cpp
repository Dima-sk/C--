#include <iostream>
#include <string>
#include <windows.h>
using namespace std;

struct Bus {
    int number;
    string driver;
    string route;
};

struct Node {
    Bus data;
    Node* next;
    Node* prev;
};

class BusPark {
private:
    Node* head;
    Node* tail;

public:
    BusPark() : head(nullptr), tail(nullptr) {}

    ~BusPark() {
        Node* p = head;
        while (p) {
            Node* temp = p;
            p = p->next;
            delete temp;
        }
    }

    void addToPark(const Bus& bus) {
        Node* node = new Node{bus, nullptr, tail};

        if (!head) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }

    void departBus(int number) {
        Node* p = head;
        while (p) {
            if (p->data.number == number) {
                if (p->prev) p->prev->next = p->next;
                else head = p->next;

                if (p->next) p->next->prev = p->prev;
                else tail = p->prev;

                cout << "Автобус " << number << " выехал на маршрут " << p->data.route << endl;
                delete p;
                return;
            }
            p = p->next;
        }
        cout << "Автобус не найден.\n";
    }

    void returnBus(const Bus& bus) {
        addToPark(bus);
        cout << "Автобус " << bus.number << " вернулся в парк.\n";
    }

    void showPark() const {
        if (!head) {
            cout << "Парк пуст.\n";
            return;
        }

        cout << "\nАвтобусы в парке:\n";
        Node* p = head;
        while (p) {
            cout << "Номер: " << p->data.number
                 << ", Водитель: " << p->data.driver
                 << ", Маршрут: " << p->data.route << endl;
            p = p->next;
        }
    }
};

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    BusPark park;

    park.addToPark({101, "Францев", "Маршрут 1"});
    park.addToPark({202, "Петров", "Маршрут 2"});
    park.addToPark({303, "Иванов", "Маршрут 3"});

    park.showPark();

    cout << endl;
    park.departBus(202);
    park.showPark();

    cout << endl;
    park.returnBus({202, "Петров", "Маршрут 2"});
    park.showPark();

    return 0;
}