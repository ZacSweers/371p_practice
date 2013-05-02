// ---------------------
// DoubleInheritance.c++
// ---------------------

#include <cassert>  // assert
#include <iostream> // cout, endl

/* single struct, no inheritance */
struct D {
    double _d;

    D (double d) :
            _d (d)
        {}};

/* single struct inheriting from D */
struct A : D {
    double _x;

    /* Constructor, takes in two doubles */
    A (double d, double x) :
            D  (d),             /* sends d to the parent D */
            _x (x)              /* initializes its on x */
        {}};                    /* Notice both happen in the initializer block */

/* Another struct inheriting from D */
struct B : D {
    double _y;

    /* Same setup as above, but with a _y */
    B (double d, double y) :
            D  (d),
            _y (y)
        {}};

/**
 * And here's the double inheritance
 * Note how it inherits from A and B, which both inherit from D
 * Now we'd have TWO D objects in a C object, which is inefficient and explained in virtual inheritance
 */
struct C : A, B {
    double _z;

    /* Constructor initializing everything */
    C (double d, double x, double y, double z) :
            A  (d, x),  /* Sends same d to both A and B constructors, but remember we'd still end up with two copies of it */
            B  (d, y),
            _z (z)
        {}};

int main () {
    using namespace std;
    cout << "DoubleInheritance.c++" << endl;

    /* Because it's just one double */
    assert(sizeof(D) == sizeof(double));

    /* it contains a D object and another double _x */
    assert(sizeof(A) == sizeof(D) + sizeof(double));

    /* it contains a D object and another double _y */
    assert(sizeof(B) == sizeof(D) + sizeof(double));

    /* contains an A and a B as well as another double _z */
    assert(sizeof(C) == sizeof(A) + sizeof(B) + sizeof(double));

    /* Note that this is the same as above */
    assert(sizeof(C) == sizeof(A) + sizeof(B) + sizeof(double));                                                    /* A and B plus a double */
    assert(sizeof(C) == sizeof(A) + sizeof(D) + sizeof(double) + sizeof(double));                                   /* substitute B */
    assert(sizeof(C) == sizeof(D) + sizeof(double) + sizeof(D) + sizeof(double) + sizeof(double));                  /* substitute B and A, ephasizing there's two copies of D */
    assert(sizeof(C) == sizeof(double) + sizeof(double) + sizeof(double) + sizeof(double) + sizeof(double));        /* substitute the D's */
    assert(sizeof(C) == 5 * sizeof(double));                                                                        /* it's 5 D objects, ephasizing there's two copies of D */

    C t(2, 3, 4, 5);

    char* p  = reinterpret_cast<char*>(&t);                         /* Pointer to t */
//  char* d  = reinterpret_cast<char*>(&t._d);                    // error: request for member '_d' is ambiguous because a C inherits two _d's from a D object in the lineage
    char* da = reinterpret_cast<char*>(&static_cast<A&>(t)._d);     /* pointer to A's _d, note the required static_cast since it's statically bound */
    char* db = reinterpret_cast<char*>(&static_cast<B&>(t)._d);     /* pointer to B's _d, note the required static_cast since it's statically bound */
    char* x  = reinterpret_cast<char*>(&t._x);                      /* pointer to A's _x (inherited by C) */
    char* y  = reinterpret_cast<char*>(&t._y);                      /* pointer to B's _y (inherited by C) */
    char* z  = reinterpret_cast<char*>(&t._z);                      /* pointer to C's _z */

    assert(p                   == da);  /* Because A was inherited first, its D is first. This is a pointer to A's D object (and by extension its _d variable) */
    assert(da + sizeof(double) == x);   /* Because A was inherited first, its object is before B, including it's _x */
    assert(da + sizeof(A)      == db);  /* After the A object, we're now in the B object (which, the pointer to B is also a pointer to B's D object) */
    assert(db + sizeof(double) == y);   /* And now we go past B's D's _d to get to B's _y */
    assert(db + sizeof(B)      == z);   /* After we go past B, we're now at C's _z variable */

    /* ASCII Diagram of a C object */
    /* Note that the size is 8+8+8+8+8 = 40 bytes (C.A.D._d + C.A._x + C.B.D._d + C.B._y + C._z) */

    /**
     * --------------------------------------------------------
     * | C.A.D._d |  C.A._x  | C.B.D._d |  C.B._y  |   C._z   |
     * --------------------------------------------------------
     * |<----D--->|          |<----D--->|          |          |
     * |          |          |          |          |          |
     * |<---------A--------->|<---------B--------->|          |
     * |                     |                     |          |
     * |<------------------------C--------------------------->|
     *
     */

    cout << "Done." << endl;
    return 0;}
