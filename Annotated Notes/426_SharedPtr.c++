// -------------
// SharedPtr.c++
// -------------

#include <cassert>  // assert
#include <iostream> // cout, endl
#include <typeinfo> // bad_cast

#include "boost/shared_ptr.hpp" // shared_ptr

#include "Shapes.h"

typedef boost::shared_ptr<      AbstractShape>       Shape;
typedef boost::shared_ptr<const AbstractShape> Const_Shape;

int main () {
    using namespace std;
    using namespace boost;
    cout << "SharedPtr.c++" << endl;

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
    const Shape x(new Circle(2, 3, 4));
    x->move(5, 6);
    assert(x->area() == (3.14 * 4 * 4));
//  assert(x->radius() == 4);                                   // doesn't compile
    if (const Circle* const q = dynamic_cast<Circle*>(x.get()))
        assert(q->radius() == 4);
    try {
        const Circle& r = dynamic_cast<Circle&>(*x.get());
        assert(r.radius() == 4);}
    catch (const bad_cast& e) {
        assert(false);}
    assert(x.unique());
    assert(x.use_count() == 1);
    }

    {
    Const_Shape x(new Circle(2, 3, 4));
//  x->move(5, 6);                                                    // doesn't compile
    assert(x->area() == (3.14 * 4 * 4));
//  assert(x->radius() == 4);                                         // doesn't compile
    if (const Circle* const q = dynamic_cast<const Circle*>(x.get()))
        assert(q->radius() == 4);
    try {
        const Circle& r = dynamic_cast<const Circle&>(*x.get());
        assert(r.radius() == 4);}
    catch (const bad_cast& e) {
        assert(false);}
    assert(x.unique());
    assert(x.use_count() == 1);
    }

    {
    const Shape x(new Circle(2, 3, 4));
          Shape y = x;
    assert(x == y);
    assert(!x.unique());
    assert(x.use_count() == 2);
    assert(!y.unique());
    assert(y.use_count() == 2);
    y->move(5, 6);
    assert(x == y);
    assert(!x.unique());
    assert(x.use_count() == 2);
    assert(!y.unique());
    assert(y.use_count() == 2);
    y = Shape(y->clone());
    assert(x != y);
    assert(x.unique());
    assert(x.use_count() == 1);
    assert(y.unique());
    assert(y.use_count() == 1);
    y->move(5, 6);
    }

    {
    const Shape x(new Circle(2, 3, 4));
          Shape y(new Circle(2, 3, 5));
    assert(x != y);
    y = x;
    assert(x == y);
    assert(!x.unique());
    assert(x.use_count() == 2);
    assert(!y.unique());
    assert(y.use_count() == 2);
    y->move(5, 6);
    assert(x == y);
    assert(!x.unique());
    assert(x.use_count() == 2);
    assert(!y.unique());
    assert(y.use_count() == 2);
    y = Shape(y->clone());
    assert(x != y);
    assert(x.unique());
    assert(x.use_count() == 1);
    assert(y.unique());
    assert(y.use_count() == 1);
    y->move(5, 6);
    }

    {
    Shape x(new Circle(2, 3, 4));
    assert(x->area() == (3.14 * 4 * 4));
    x = Shape(new Circle(5, 6, 7));
    assert(x->area() == (3.14 * 7 * 7));
    assert(x.unique());
    assert(x.use_count() == 1);
    }

    cout << "Done." << endl;
    return 0;}
