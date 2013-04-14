// -------------------
// AbstractClasses.c++
// -------------------

#include <cassert>  // assert
#include <iostream> // cout, endl
#include <typeinfo> // bad_cast

#include "Shapes.h"

int main () {
    using namespace std;
    cout << "AbstractClasses.c++" << endl;
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
    Circle x(2, 3, 4);
    x.move(5, 6);
    assert(x.area()   == 3.14 * 4 * 4);
    assert(x.radius() == 4);
    }

    {
    const Circle x(2, 3, 4);
          Circle y(2, 3, 5);
    assert(x != y);
    y = x;
    assert(x == y);
    }

    {
//  Circle*        const p = new AbstractShape(2, 3);           // doesn't compile
    AbstractShape* const p = new Circle(2, 3, 4);
    p->move(5, 6);
    assert(p->area()                == 3.14 * 4 * 4);
//  assert(p->AbstractShape::area() == 0);                      // doesn't compile
//  assert(p->radius() == 4);                                   // doesn't compile
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
    const AbstractShape* const p = new Circle(2, 3, 4);
    const AbstractShape*       q = new Circle(2, 3, 5);
    assert(*p != *q);
//  *q = *p;                                            // doesn't compile
    delete q;
    q = p->clone();
    assert(*p == *q);
    delete p;
    delete q;
    }
/*
    {
    const Circle        a[] = {AbstractShape(2, 3), Circle(4, 5, 6)};
    const AbstractShape a[] = {AbstractShape(2, 3), Circle(4, 5, 6)};
    assert(a[0].area() == 0);
    assert(a[1].area() == 0);
    }
*/
    {
    const Circle a[] = {Circle(2, 3, 4), Circle(5, 6, 7)};
    assert(a[0].area() == 3.14 * 4 * 4);
    assert(a[1].area() == 3.14 * 7 * 7);
    const AbstractShape* const p = a;
    assert(p[0].area() == 3.14 * 4 * 4);
//  assert(p[1].area() == 3.14 * 7 * 7);                    // illdefined
    }

    cout << "Done." << endl;
    return 0;}
