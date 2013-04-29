// -----------
// Handle3.c++
// -----------

#include <cassert>   // assert
#include <cstddef>   // size_t
#include <iostream>  // cout, endl
#include <stdexcept> // bad_cast

#include "426_Handle3.h"
#include "412_Shapes.h"


/**
 * Note that the API is the same as Handle1, but now we keep track of reference counts
 * This is to illustrate that in OOP, you want to be able to change one package/class without
 * Having to change anything in the code that depends on it
 * For anything missing an explanation, see Handle1 for explanation
 */

struct Shape : Handle<AbstractShape> {

    /* Same constructor as before, but now it  */
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
 
    /* There's only one instance, so count is one. Must be unique */
    assert(x.unique());
    assert(x.use_count() == 1);
    }

    {
    const Shape x = new Circle(2, 3, 4);
          Shape y = x;
    assert(x == y);

    /* There's two counts now since y and x point to same count struct */
    assert(!x.unique());
    assert(x.use_count() == 2);
    assert(!y.unique());
    assert(y.use_count() == 2);


    y.move(5, 6);

    /* Both are unique now because y is now pointing to a different count struct since it's not equal to x */
    /* This happens because move() calls get(), which changes them in its new implementation */
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

    /* Still unique because it's a new Circle above, not pointing to the same one that x originally pointed to */
    assert(x.unique());
    assert(x.use_count() == 1);
    }

    cout << "Done." << endl;
    return 0;}
