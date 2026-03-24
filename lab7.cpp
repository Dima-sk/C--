#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

class Point {
protected:
    int x, y;
    bool visible;
public:
    Point(int x = 0, int y = 0) : x(x), y(y), visible(true) {}
    virtual ~Point() {}
    virtual void Show() = 0;
    virtual void Hide() { visible = false; }
    virtual void Fly() = 0;
    int GetX() { return x; }
    int GetY() { return y; }
};

class Krug : public Point {
    int radius;
public:
    Krug(int x, int y, int r) : Point(x, y), radius(r) {}
    void Show() override {
        cout << "Круг: (" << x << ", " << y << "), R=" << radius << endl;
    }
    void Fly() override {
        x += rand() % 10 - 5;
        y += rand() % 10 - 5;
    }
};

int main() {
    srand(time(0));
    Krug k1(100, 100, 50);
    Krug k2(200, 200, 30);
    
    Point* objs[] = {&k1, &k2};
    
    for (int i = 0; i < 10; i++) {
        cout << "\nШаг " << i + 1 << ":" << endl;
        objs[0]->Fly();
        objs[1]->Fly();
        objs[0]->Show();
        objs[1]->Show();
    }
    
    return 0;
}