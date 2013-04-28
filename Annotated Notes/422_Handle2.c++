// -----------
// Handle2.c++
// -----------

#include <cassert>  // assert
#include <iostream> // cout, endl
#include <typeinfo> // bad_cast

#include "Handle2.h"
#include "Shapes.h"

typedef Handle<AbstractShape> Shape;

int main () {
    using namespace std;
    cout << "Handle2.c++" << endl;

    {
    Circle x(2, 3, 4);
    assert(x.area() == 3.14 * 4 * 4);
    x.move(5, 6);
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
    const Shape x = new Circle(2, 3, 4);
//  x->move(5, 6);                                                           // doesn't compile
    assert(x->area() == (3.14 * 4 * 4));
//  assert(x->radius() == 4);                                                // doesn't compile
    if (const Circle* const q = dynamic_cast<const Circle*>(x.operator->()))
        assert(q->radius() == 4);
    try {
        const Circle& r = dynamic_cast<const Circle&>(x.operator*());
        assert(r.radius() == 4);}
    catch (const bad_cast& e) {
        assert(false);}
    }

    {
    Shape x = new Circle(2, 3, 4);
    x->move(5, 6);
    assert(x->area() == (3.14 * 4 * 4));
//  assert(x->radius() == 4);                                          // doesn't compile
    if (const Circle* const q = dynamic_cast<Circle*>(x.operator->()))
        assert(q->radius() == 4);
    try {
        const Circle& r = dynamic_cast<Circle&>(x.operator*());
        assert(r.radius() == 4);}
    catch (const bad_cast& e) {
        assert(false);}
    }

    {
    const Shape x = new Circle(2, 3, 4);
          Shape y = x;
    y->move(5, 6);
    assert(y->area() == (3.14 * 4 * 4));
    }

    {
    const Shape x = new Circle(2, 3, 4);
          Shape y = new Circle(2, 3, 5);
    assert(x != y);
    y = x;
    assert(x == y);
    }

    {
    Shape x = new Circle(2, 3, 4);
    assert(x->area() == (3.14 * 4 * 4));
    x = new Circle(5, 6, 7);
    assert(x->area() == (3.14 * 7 * 7));
    }

    cout << "Done." << endl;
    return 0;}
