// -----------
// Handle3.c++
// -----------

#include <cassert>   // assert
#include <cstddef>   // size_t
#include <iostream>  // cout, endl
#include <stdexcept> // bad_cast

#include "Handle3.h"
#include "Shapes.h"

struct Shape : Handle<AbstractShape> {
    Shape (AbstractShape* p) :
            Handle<AbstractShape> (p)
        {}
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
    double area () const {
        return get()->area();}

    void move (int x, int y) {
        return get()->move(x, y);}};

int main () {
    using namespace std;
    cout << "Handle3.c++" << endl;

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
//  x.move(5, 6);                         // doesn't compile
    assert(x.area()   == (3.14 * 4 * 4));
//  assert(x.radius() == 4);              // doesn't compile
    assert(x.unique());
    assert(x.use_count() == 1);
    }

    {
    Shape x = new Circle(2, 3, 4);
    x.move(5, 6);
    assert(x.area()   == (3.14 * 4 * 4));
//  assert(x.radius() == 4);              // doesn't compile
    assert(x.unique());
    assert(x.use_count() == 1);
    }

    {
    const Shape x = new Circle(2, 3, 4);
          Shape y = x;
    assert(x == y);
    assert(!x.unique());
    assert(x.use_count() == 2);
    assert(!y.unique());
    assert(y.use_count() == 2);
    y.move(5, 6);
    assert(x.unique());
    assert(x.use_count() == 1);
    assert(y.unique());
    assert(y.use_count() == 1);
    assert(y.area() == (3.14 * 4 * 4));
    }

    {
    const Shape x = new Circle(2, 3, 4);
          Shape y = new Circle(2, 3, 5);
    assert(x != y);
    y = x;
    assert(x == y);
    assert(!x.unique());
    assert(x.use_count() == 2);
    assert(!y.unique());
    assert(y.use_count() == 2);
    y.move(5, 6);
    assert(x.unique());
    assert(x.use_count() == 1);
    assert(y.unique());
    assert(y.use_count() == 1);
    assert(y.area() == (3.14 * 4 * 4));
    }

    {
    Shape x = new Circle(2, 3, 4);
    assert(x.area() == (3.14 * 4 * 4));
    x = new Circle(5, 6, 7);
    assert(x.area() == (3.14 * 7 * 7));
    assert(x.unique());
    assert(x.use_count() == 1);
    }

    cout << "Done." << endl;
    return 0;}
