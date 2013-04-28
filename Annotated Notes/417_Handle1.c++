// -----------
// Handle1.c++
// -----------

#include <cassert>  // assert
#include <iostream> // cout, endl

#include "Handle1.h"
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
    cout << "Handle1.c++" << endl;

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
    }

    {
    Shape x = new Circle(2, 3, 4);
    x.move(5, 6);
    assert(x.area()   == (3.14 * 4 * 4));
//  assert(x.radius() == 4);              // doesn't compile
    }

    {
    const Shape x = new Circle(2, 3, 4);
          Shape y = x;
    y.move(5, 6);
    assert(y.area() == (3.14 * 4 * 4));
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
    assert(x.area() == (3.14 * 4 * 4));
    x = new Circle(5, 6, 7);
    assert(x.area() == (3.14 * 7 * 7));
    }

    cout << "Done." << endl;
    return 0;}
