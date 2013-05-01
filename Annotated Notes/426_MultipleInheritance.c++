// -----------------------
// MultipleInheritance.c++
// -----------------------

#include <cassert>  // assert
#include <iostream> // cout, endl

/* struct A with a double and one constructor - no inheiritance */
struct A {
    double _x;

    /* constructor to initialize _x */
    A (double x) :
            _x (x)
        {}};

/* struct B with a double and one constructor - no inheiritance */
struct B {
    double _y;

    /* constructor to initialize _y */
    B (double y) :
            _y (y)
        {}};

/* struct C with a double and one constructor - NOTE: MULTIPLE INHEIRITANCE */
struct C : A, B {
    double _z;

    /* Constructor to initialize data members - NOTE: use of initializer list (again) */
    C (double x, double y, double z) :
            /* Call A's constructor explicitly */
            A  (x),

            /* Call B's constructor explicitly */
            B  (y),

            /* Initialize _z */
            _z (z)
        {}};

int main () {
    using namespace std;
    cout << "MultipleInheritance.c++" << endl;
    
    /* Size of struct A is only a size of a double since it only contains 1 double */
    assert(sizeof(A) == sizeof(double));

    /* Size of struct B is only a size of a double since it only contains 1 double */
    assert(sizeof(B) == sizeof(double));

    /* Size of struct C 3 * size of a double because of double inheiritance */
    assert(sizeof(C) == sizeof(A) + sizeof(B) + sizeof(double));

    /* Create a C object with 2, 3, 4 */
    C t(2, 3, 4);

    /* One byte pointers to demonstrate layout in memory of t, and t's data members (both inheirited & non-inheirited) */
    char* p = reinterpret_cast<char*>(&t);
    char* x = reinterpret_cast<char*>(&t._x);
    char* y = reinterpret_cast<char*>(&t._y);
    char* z = reinterpret_cast<char*>(&t._z);

    /* p, which is the beginning of the struct, points at _x */
    assert(p                  == x);

    /* _y is located sizeof(double) away from _x */
    assert(x + sizeof(double) == y);

    /* _z is located sizeof(double) away from _y */
    assert(y + sizeof(double) == z);


    // ASCII art of a struct C as it appears on the heap/stack (modeled from 410_DynamicBinding.c++ (thanks Henri))

    //           |<---sizeof(double)--->|
    // -------------------------------------------------+
    // |   _x    |          _y          |      _z       |
    // -------------------------------------------------+
    // ^         ^                      ^                
    // |         |                      |
    // p         y                      z
    // ^
    // |
    // x                         


    cout << "Done." << endl;
    return 0;}
