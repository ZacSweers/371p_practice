// -----------------------
// MultipleInheritance.c++
// -----------------------

#include <cassert>  // assert
#include <iostream> // cout, endl

struct A {
    double _x;

    A (double x) :
            _x (x)
        {}};

struct B {
    double _y;

    B (double y) :
            _y (y)
        {}};

struct C : A, B {
    double _z;

    C (double x, double y, double z) :
            A  (x),
            B  (y),
            _z (z)
        {}};

int main () {
    using namespace std;
    cout << "MultipleInheritance.c++" << endl;

    assert(sizeof(A) == sizeof(double));
    assert(sizeof(B) == sizeof(double));
    assert(sizeof(C) == sizeof(A) + sizeof(B) + sizeof(double));

    C t(2, 3, 4);

    char* p = reinterpret_cast<char*>(&t);
    char* x = reinterpret_cast<char*>(&t._x);
    char* y = reinterpret_cast<char*>(&t._y);
    char* z = reinterpret_cast<char*>(&t._z);

    assert(p                  == x);
    assert(x + sizeof(double) == y);
    assert(y + sizeof(double) == z);

    cout << "Done." << endl;
    return 0;}
