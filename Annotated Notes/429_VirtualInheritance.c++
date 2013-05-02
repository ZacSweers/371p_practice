// ----------------------
// VirtualInheritance.c++
// ----------------------

#include <cassert>  // assert
#include <iostream> // cout, endl

/**
 * Remember this was invented for the iostream library to use
 * This is the more elegant and efficient way of doing inheritance where parents could have a common ancestor
 * Remember in DoubleInheritance we ended up with TWO copies of the common ancestor object
 */

/* Common ancestor */
struct V {
    double _v;

    V (double v) :
            _v (v)
        {}};

/* A struct, child of V */
struct A : virtual V {  /* Note that now we declare it virtually inherits from V */
    double _x;

    A (double v, double x) :
            V  (v), /* Still calls parent V constructor, but in C's constructor below, this DOES NOT RUN */
            _x (x)  /* We still have the V constructor though in case another class inherits from it and doesn't do virtual inheritance */
        {}};

/* B struct, child of V */
struct B : virtual V {  /* Note that now we declare it virtually inherits from V */
    double _y;

    B (double v, double y) :
            V  (v), /* Still calls parent V constructor, but in C's constructor below, this DOES NOT RUN */
            _y (y)  /* We still have the V constructor though in case another class inherits from it and doesn't do virtual inheritance */
        {}};

/**
 * The C struct, inheriting both A and B, and their common ancestor
 * The way that virtual inheritance works is that it must call the common ancestor's constructor DIRECTLY
 */
struct C : A, B {
    double _z;

    C (double v, double x, double y, double z) :
            V  (v), /* Calling the common ancestor constructor */
            A  (v, x),  /* A's constructor, still passing v but remember line 27 doesn't actually run in this case */
            B  (v, y),  /* B's constructor, still passing v but remember line 36 doesn't actually run in this case */
            _z (z)
        {}};

int main () {
    using namespace std;
    cout << "VirtualInheritance.c++" << endl;

    assert(sizeof(V) ==      sizeof(double));                                               /* V contains just a double, so it's the sizeof a double */

    /**
     * Since V is virtually inherited by C, the parents must both point to the same V, thus we have one pointer to the same one
     */
    assert(sizeof(A) ==      sizeof(void*)                   + sizeof(double) + sizeof(V)); /* Size of a pointer to the shared V, the _x double variable, and a V object */
    assert(sizeof(B) ==      sizeof(void*)                   + sizeof(double) + sizeof(V)); /* Size of a pointer to the shared V, the _y double variable, and a V object */
    assert(sizeof(C) == 2 * (sizeof(void*) + sizeof(double)) + sizeof(double) + sizeof(V)); /* Size of two parents (A and B are the same size), C's _z, and the V object virtually inherited */

    C t(2, 3, 4, 5);

    char* p = reinterpret_cast<char*>(&t);      /* Pointer to the C object "t" */
    char* v = reinterpret_cast<char*>(&t._v);   /* Pointer to C's virtually inherited _v */
    char* x = reinterpret_cast<char*>(&t._x);   /* Pointer to C's A's _x */
    char* y = reinterpret_cast<char*>(&t._y);   /* Pointer to C's B's _y */
    char* z = reinterpret_cast<char*>(&t._z);   /* Pointer to C's _z */


    assert(p +                  sizeof(void*) == x);    /* Remember the inherited V is actually in C, so the parent A just has a pointer and its double _x */
    assert(x + sizeof(double) + sizeof(void*) == y);    /* Go past C's A to get to C's B, then go past its pointer to get to _y */
    assert(y + sizeof(double)                 == z);    /* Go past C's B to get to C's _z (no pointer this time, V._v is in C) */
    assert(z + sizeof(double)                 == v);    /* Go past C's _z and you arrive at C's V object, and its _v variable */

    /* ASCII Diagram of a C object */
    /* Note that it's not to scale. a D pointer would only be 4 bytes, not the same size as a double */
    /* Total size is 4+8+4+8+8+8 = 40 bytes (C.A.D* + C.A._x + C.B.D* + C.B._y + C._z + C.V._v) */
    /* The doubleInheritance method size is  */

    /**
     *        _________________points to________________________
     *       /                                                  \
     *      |                      ________points to___________  \
     *      |                     /                            \  \
     * -------------------------------------------------------------------
     * |  C.A.D*  |  C.A._x  |  C.B.D*  |  C.B._y  |   C._z   |  C.V._v  |
     * -------------------------------------------------------------------
     * |<---D*--->|          |<---D*--->|          |                     |
     * |          |          |          |          |                     |          
     * |<---------A--------->|<---------B--------->|                     |          
     * |                     |                     |                     |          
     * |<------------------------------C-------------------------------->|
     *
     */


    cout << "Done." << endl;
    return 0;}
