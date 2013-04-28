// ---------------------
// DoubleInheritance.c++
// ---------------------

#include <cassert>  // assert
#include <iostream> // cout, endl

struct D {
    double _d;

    D (double d) :
            _d (d)
        {}};

struct A : D {
    double _x;

    A (double d, double x) :
            D  (d),
            _x (x)
        {}};

struct B : D {
    double _y;

    B (double d, double y) :
            D  (d),
            _y (y)
        {}};

struct C : A, B {
    double _z;

    C (double d, double x, double y, double z) :
            A  (d, x),
            B  (d, y),
            _z (z)
        {}};

int main () {
    using namespace std;
    cout << "DoubleInheritance.c++" << endl;

    assert(sizeof(D) == sizeof(double));
    assert(sizeof(A) == sizeof(D) + sizeof(double));
    assert(sizeof(B) == sizeof(D) + sizeof(double));
    assert(sizeof(C) == sizeof(A) + sizeof(B) + sizeof(double));

    C t(2, 3, 4, 5);

    char* p  = reinterpret_cast<char*>(&t);
//  char* d  = reinterpret_cast<char*>(&t._d);                    // error: request for member '_d' is ambiguous
    char* da = reinterpret_cast<char*>(&static_cast<A&>(t)._d);
    char* db = reinterpret_cast<char*>(&static_cast<B&>(t)._d);
    char* x  = reinterpret_cast<char*>(&t._x);
    char* y  = reinterpret_cast<char*>(&t._y);
    char* z  = reinterpret_cast<char*>(&t._z);

    assert(p                   == da);
    assert(da + sizeof(double) == x);
    assert(da + sizeof(A)      == db);
    assert(db + sizeof(double) == y);
    assert(db + sizeof(B)      == z);

    cout << "Done." << endl;
    return 0;}
