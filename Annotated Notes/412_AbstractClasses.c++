// -------------------
// AbstractClasses.c++
// -------------------

/**
 * NOTE: Much of the explanations for methods are in DynamicBinding.c++
 * If it's missing an explanation here, look there.
 */

#include <cassert>  // assert
#include <iostream> // cout, endl
#include <typeinfo> // bad_cast

#include "Shapes.h"

int main () {
    using namespace std;
    cout << "AbstractClasses.c++" << endl;

    /* None of these compile because you can't instantiate an abstract object */
/*
    {
    AbstractShape x(2, 3);
    x.move(4, 5);
    assert(x.area()   == 0);
//  assert(x.radius() == 0); // doesn't compile
    }

    {
    const AbstractShape x(2, 3);
          AbstractShape y(4, 5);
    assert(x != y);
    y = x;
    assert(x == y);
    }
*/


    {
        /* Instantiate a circle, all the methods work */
        Circle x(2, 3, 4);
        x.move(5, 6);
        assert(x.area()   == 3.14 * 4 * 4);
        assert(x.radius() == 4);
    }

    {
        /* Testing operator= methods */
        const Circle x(2, 3, 4);
              Circle y(2, 3, 5);
        assert(x != y);
        y = x;
        assert(x == y);
    }

    {
        /* Can't instantiate an AbstractShape, plus Circle is derived from AbstractShape, not the other way around */
    //  Circle*        const p = new AbstractShape(2, 3);           // doesn't compile
     
        /* Can't instantiate an AbstractShape, but we can make a pointer */
        AbstractShape* const p = new Circle(2, 3, 4);
        p->move(5, 6);
        assert(p->area()                == 3.14 * 4 * 4);

        /* area() is pure virtual in abstractShape */
    //  assert(p->AbstractShape::area() == 0);                      // doesn't compile
     
        /* AbstractShape doesn't know about radii */
    //  assert(p->radius() == 4);                                   // doesn't compile
     
        /* Cast it as a circle, now we can do stuff */
        /* Explanation in DynamicBinding.c++ */
        if (const Circle* const q = dynamic_cast<const Circle*>(p))
            assert(q->radius() == 4);
        try {
            const Circle& r = dynamic_cast<const Circle&>(*p);
            assert(r.radius() == 4);}
        catch (const bad_cast& e) {
            assert(false);}
        delete p;
    }

    {
        /* Explanation in DynamicBinding.c++ */
        const AbstractShape* const p = new Circle(2, 3, 4);
        const AbstractShape*       q = new Circle(2, 3, 5);
        assert(*p != *q);
    //  *q = *p;                                            // doesn't compile
     
        /* This isn't illdefined because we've made the destructor virtual */
        delete q;

        /* Returns a clone of p on the heap */
        q = p->clone();

        /* Asserts that they have the same value (should be 2,3,4) */
        assert(*p == *q);
        delete p;
        delete q;
    }

    /* Doesn't work because we can't instantiate abstractShapes, and we can't have a Circle array containing its parents */
/*
    {
    const Circle        a[] = {AbstractShape(2, 3), Circle(4, 5, 6)};
    const AbstractShape a[] = {AbstractShape(2, 3), Circle(4, 5, 6)};
    assert(a[0].area() == 0);
    assert(a[1].area() == 0);
    }
*/


    {
        /* Explanation in DynamicBinding.c++ */
        const Circle a[] = {Circle(2, 3, 4), Circle(5, 6, 7)};
        assert(a[0].area() == 3.14 * 4 * 4);
        assert(a[1].area() == 3.14 * 7 * 7);
        const AbstractShape* const p = a;
        assert(p[0].area() == 3.14 * 4 * 4);
    //  assert(p[1].area() == 3.14 * 7 * 7);                    // illdefined
    }

    cout << "Done." << endl;
    return 0;}
