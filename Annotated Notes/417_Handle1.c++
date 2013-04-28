// -----------
// Handle1.c++
// -----------

#include <cassert>  // assert
#include <iostream> // cout, endl

#include "417_Handle1.h"
#include "412_Shapes.h"

/**
 * Create a Shape struct that inherits from Handle<AbstractShape>
 */
struct Shape : Handle<AbstractShape> {

    /**
     * Pointer constructor
     * Just passes input pointer to Handle's constructor
     */
    Shape (AbstractShape* p) :
            Handle<AbstractShape> (p)
        {}

/* Given to use for free */
/*
    Shape (const Shape& that) :
            Handle<AbstractShape> (that)
        {}

    ~Shape ()
        {}

    Shape& operator = (const Shape& that) {
        Handle<AbstractShape>::operator=(that);
        return *this;}
*/

    /* Mimicking Shape's API, called get(), which returns _p, then we can use like a pointer to the object we're pointing to */
    double area () const {
        return get()->area();}

    void move (int x, int y) {
        return get()->move(x, y);}};

int main () {
    using namespace std;
    cout << "Handle1.c++" << endl;

    /* Regular Circle stuff */
    {
    Circle x(2, 3, 4);
    assert(x.area() == 3.14 * 4 * 4);
    x.move(5, 6);
    assert(x.radius() == 4);
    }

    /* More regular Circle stuff */
    {
    const Circle x(2, 3, 4);
          Circle y(2, 3, 5);
    assert(x != y);
    y = x;
    assert(x == y);
    }


    /* Shape stuff */
    {
        /* Remember this would return a pointer, thus calling Shape's pointer constructor above */
        const Shape x = new Circle(2, 3, 4);

    //  x.move(5, 6);                         // doesn't compile because x is const
     
        /* Call's _p->area(), in this case a Circle */
        assert(x.area()   == (3.14 * 4 * 4));

        /* Shape doesn't know what a radius is */
    //  assert(x.radius() == 4);              // doesn't compile
    }


    {
        /* Same as above, except now we can move because x isn't const */
        Shape x = new Circle(2, 3, 4);
        x.move(5, 6);
        assert(x.area()   == (3.14 * 4 * 4));
    //  assert(x.radius() == 4);              // doesn't compile
    }

    {
        /* Create two shapes, y is a clone() of x */
        const Shape x = new Circle(2, 3, 4);
              Shape y = x;
              /* ^ Copy constructor, uses clone() */
        y.move(5, 6);
        assert(y.area() == (3.14 * 4 * 4));
    }

    {
        /* Regular Shape/Circle polymorphism */
        const Shape x = new Circle(2, 3, 4);
              Shape y = new Circle(2, 3, 5);
        assert(x != y);

        /* Operator=, uses swap */
        y = x;
        assert(x == y);
    }

    {
        /* Create a Circle */
        Shape x = new Circle(2, 3, 4);
        assert(x.area() == (3.14 * 4 * 4));

        /* Set x to a new Circle. */
        /* Uses operator= */
        x = new Circle(5, 6, 7);
        assert(x.area() == (3.14 * 7 * 7));
    }

    cout << "Done." << endl;
    return 0;}
