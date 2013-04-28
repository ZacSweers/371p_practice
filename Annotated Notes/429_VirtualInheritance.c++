// ----------------------
// VirtualInheritance.c++
// ----------------------

#include <cassert>  // assert
#include <iostream> // cout, endl

struct V {
    double _v;

    V (double v) :
            _v (v)
        {}};

struct A : virtual V {
    double _x;

    A (double v, double x) :
            V  (v),
            _x (x)
        {}};

struct B : virtual V {
    double _y;

    B (double v, double y) :
            V  (v),
            _y (y)
        {}};

struct C : A, B {
    double _z;

    C (double v, double x, double y, double z) :
            V  (v),
            A  (v, x),
            B  (v, y),
            _z (z)
        {}};

int main () {
    using namespace std;
    cout << "VirtualInheritance.c++" << endl;

    assert(sizeof(V) ==      sizeof(double));
    assert(sizeof(A) ==      sizeof(void*)                   + sizeof(double) + sizeof(V));
    assert(sizeof(B) ==      sizeof(void*)                   + sizeof(double) + sizeof(V));
    assert(sizeof(C) == 2 * (sizeof(void*) + sizeof(double)) + sizeof(double) + sizeof(V));

    C t(2, 3, 4, 5);

    char* p = reinterpret_cast<char*>(&t);
    char* v = reinterpret_cast<char*>(&t._v);
    char* x = reinterpret_cast<char*>(&t._x);
    char* y = reinterpret_cast<char*>(&t._y);
    char* z = reinterpret_cast<char*>(&t._z);

    assert(p +                  sizeof(void*) == x);
    assert(x + sizeof(double) + sizeof(void*) == y);
    assert(y + sizeof(double)                 == z);
    assert(z + sizeof(double)                 == v);

    cout << "Done." << endl;
    return 0;}
