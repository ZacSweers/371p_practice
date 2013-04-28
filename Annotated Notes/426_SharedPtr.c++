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
    Circle x(2, 3, 4);                  /* Create a circle */
    assert(x.area() == 3.14 * 4 * 4);   /* Look! It has area */
    x.move(5, 6);                       /* Call that cirlce's move() */
    assert(x.radius() == 4);            /* The radius of the circle has been modified */
    }

    {
    const Circle x(2, 3, 4);            /* Const circle x */
          Circle y(2, 3, 5);            /* Non-const circle y */
    assert(x != y);                     /* x and y do not equal due to radius difference */
    y = x;                              /* Assignment operator copying x into y */
    assert(x == y);                     /* x is now equal to y */
    }

    {
    const Shape x(new Circle(2, 3, 4));                         /* creating new const shape x using a circle */
    x->move(5, 6);                                              /* calling Shape's move which calls Circle's */
    assert(x->area() == (3.14 * 4 * 4));                        /* you can access area() which is member of Shape */
//  assert(x->radius() == 4);                                   /* Shape does not know what a radius is */
    if (const Circle* const q = dynamic_cast<Circle*>(x.get()));/* Break the rules, get access to underlying circle */
        assert(q->radius() == 4);                               /* Calling circle's radius() directly */
    try {
        const Circle& r = dynamic_cast<Circle&>(*x.get());      /* Casting the actual object instead of Shape's pointer*/
        assert(r.radius() == 4);}                               /* Calling circle's radius() directly */
    catch (const bad_cast& e) {                                 /* Shape didn't contain a circle */
        assert(false);}
    assert(x.unique());                                         /* There's no one else pointing to Shape's Circle */
    assert(x.use_count() == 1);                                 /* so its use count should be 1 */
    }

    {
    Const_Shape x(new Circle(2, 3, 4));                         /* Creating a new Const_Shape */
//  x->move(5, 6);                                              /* Which has an unmodifiable AbstractShape pointer */
    assert(x->area() == (3.14 * 4 * 4));                        /* You can read from it though */
//  assert(x->radius() == 4);                                   /* Shape still doesn't know what a radius is */
    if (const Circle* const q = dynamic_cast<const Circle*>(x.get())) /* Same as above */
        assert(q->radius() == 4);                               /* But note that it was casted to a CONST circle */
    try {
        const Circle& r = dynamic_cast<const Circle&>(*x.get());
        assert(r.radius() == 4);}
    catch (const bad_cast& e) {
        assert(false);}
    assert(x.unique());                                         /* It's still unique. */
    assert(x.use_count() == 1);
    }

    {
    const Shape x(new Circle(2, 3, 4));                         /* Now we create a circle/shape */
          Shape y = x;                                          /* And copy it to another shape */
    assert(x == y);                                             /* The two are equal, of course. */
    assert(!x.unique());                                        /* But alas, x is no longer unique. */
    assert(x.use_count() == 2);                                 /* As x and y are pointing to the same internal */
    assert(!y.unique());                                        /* container, we can see that their counts are */
    assert(y.use_count() == 2);                                 /* both two. They point to the same Circle. */
    y->move(5, 6);                                              /* We can modify y even though x is const */
    assert(x == y);                                             /* and it also affects x. */
    assert(!x.unique());                                        /* This is due to x and y not being unique. */
    assert(x.use_count() == 2);                                 /* They share an internal container, and */
    assert(!y.unique());                                        /* modifying one of these containers will */
    assert(y.use_count() == 2);                                 /* end up modifying the other one. */
    y = Shape(y->clone());                                      /* However, when we decide to call clone on y */
    assert(x != y);                                             /* the container within is modified (cloned) */
    assert(x.unique());                                         /* so that they are now both unique, and do not */
    assert(x.use_count() == 1);                                 /* equal one another. Both containers have a count */
    assert(y.unique());                                         /* of 1, because they are no longer both pointing */
    assert(y.use_count() == 1);                                 /* to the same container. */
    y->move(5, 6);                                              /* y can still be modified. */
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
