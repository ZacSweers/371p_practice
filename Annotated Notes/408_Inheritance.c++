// ---------------
// Inheritance.c++
// ---------------

#include <cassert>  // assert
#include <iostream> // cout, endl, istream, ostream
#include <utility>  // !=
#include <vector>   // vector

class Shape {

    /* We need these in order to correctly do comparisons */
    /* This is the C++ version of .equals() and toString() in Java */

    /* .equals() version. Compares two inputted shapes */
    friend bool operator == (const Shape& lhs, const Shape& rhs) {
        return (lhs._x == rhs._x) && (lhs._y == rhs._y);}

    /* Takes our coordinates and bundles them into an istream object */
    friend std::istream& operator >> (std::istream& lhs, Shape& rhs) {
        return lhs >> rhs._x >> rhs._y;}

    /* Takes our coordinates and bundles them into an ostream object */
    friend std::ostream& operator << (std::ostream& lhs, const Shape& rhs) {
        return lhs << rhs._x << " " << rhs._y;}

    /* Coordinates */
    private:
        int _x;
        int _y;

    /**
     * Shape's int constructor
     * Notice the initializer block before the actual method block
     * _x(x) is the same as _x = x;
     */
    public:
        Shape (int x, int y) :
                _x (x),
                _y (y)
            {}

/* Given to us for free */
/*
        Shape (const Shape& that) :
                _x (that._x),
                _y (that._y)
            {}

        ~Shape ()
            {}

        Shape& operator = (const Shape& that) {
            _x = that._x;
            _y = that._y;
            return *this;}
*/

        /* Area() method, returns 0 since shapes don't have area */
        double area () const {
            return 0;}

        /* Move() function, moves to new coordinates */
        void move (int x, int y) {
            _x = x;
            _y = y;}};

/* Circle class, extends Shape */
class Circle : public Shape {

    /* Again with ops, but now we also account for radius */
    friend bool operator == (const Circle& lhs, const Circle& rhs) {
        return (static_cast<const Shape&>(lhs) == rhs) && (lhs._r == rhs._r);}

    friend std::istream& operator >> (std::istream& lhs, Circle& rhs) {
        return lhs >> static_cast<Shape&>(rhs) >> rhs._r;}

    friend std::ostream& operator << (std::ostream& lhs, const Circle& rhs) {
        return lhs << static_cast<const Shape&>(rhs) << " " << rhs._r;}

    private:
        /* introducing the Radius */
        int _r;

    public:

        /**
         * Circle's int constructor
         * Notice again with the initializer block
         * Also notice we use Shape(x,y), and not super(x,y)
         */
        Circle (int x, int y, int r) :
                Shape (x, y),
                _r    (r)
            {}
/*
        Circle (const Circle& that) :
                Shape (that),
                _r    (that._r)
            {}

        ~Circle ()
            {}

        Circle& operator = (const Circle& that) {
            Shape::operator=(that);
            _r = that._r;
            return *this;}
*/

        /* Area() method, does circle's area formula */
        double area () const {
            return 3.14 * _r * _r;}

        /* Radius getter (Oh no he didn't) */
        int radius () const {
            return _r;}};

/* A, holds a double */
struct A {
    double x;};

/* B struct, extends from A and holds two more doubles */
struct B : A {
    double y;
    double z;};

int main () {
    using namespace std;
    using namespace std::rel_ops;
    cout << "Inheritance.c++" << endl;

    /**
     * This block makes a shape
     * area() is 0 because shapes don't have areas by themselves
     * move works
     * radius() doesn't compile because there's no radius in Shape
     */
    {
        Shape x(2, 3);
        x.move(4, 5);
        assert(x.area()   == 0);
    //  assert(x.radius() == 0); // doesn't compile
    }

    /**
     * Make two shape objects
     * Confirm they're not equal in value (i.e. coordinates aren't the same)
     * Set y equal to x
     * Now they're equal in value
     */
    {
        const Shape x(2, 3);
              Shape y(4, 5);
        assert(x != y);
        y = x;
        // x = y;   // Doesn't compile because x is const
        assert(x == y);
    }

    /**
     * Creates a Circle, moves it, confirms that
     * now area() computes correctl and radius() comes into play
     */
    {
        Circle x(2, 3, 4);
        x.move(5, 6);
        assert(x.area()   == 3.14 * 4 * 4);
        assert(x.radius() == 4);
    }

    /**
     * Make two circle objects
     * Confirm they're not equal in value (i.e. coordinates and radii aren't the same)
     * Set y equal to x
     * Now they're equal in value
     */
    {
        const Circle x(2, 3, 4);
              Circle y(2, 3, 5);
        assert(x != y);
        y = x;
        assert(x == y);
    }


    {
        /* Nope, shape isn't a type of Circle. Circle is a type of Shape */
    //  Circle* const p = new Shape(2, 3);         // doesn't compile
        Shape*  const p = new Circle(2, 3, 4);
        p->move(5, 6);

        /* We didn't mark area() as virtual, so it still uses Shape's */
        assert(p->area()   == 0);

        /* Shape doesn't know what a radius is */
    //  assert(p->radius() == 4);                  // doesn't compile
        
        /**
         * Doesn't work because it would only delete Shape's size
         * Say a Shape is 8 bytes
         * And a circle is 16 bytes
         * This would only delete 8 bytes, leaving 8 bytes left (and inaccessible), memory leak
         */
    //  delete p;                                  // illdefined
     
        /* So instead we must reinterpret the pointer as a Circle* */
        /* Static_cast because it's statically bound */
        Circle* const q = static_cast<Circle*>(p);

        /* Now we can use Circle's actual functions and delete properly */
        assert(q->area()   == 3.14 * 4 * 4);
        assert(q->radius() == 4);
        delete q;
    }



    {
        /* p - immutable shape and immutable pointer */
        const Shape* const p = new Circle(2, 3, 4);
        /* q - immutable pointer, mutable shape */
              Shape* const q = new Circle(2, 3, 5);

        /* Notice that the only difference between p and q are their shapes' radii */

    /* The following illdefined lines are all examples of why having them statically bound means that C++ will only treat them as Shape, and not 
        like Circles with proper polymorphism */

    //  assert(*p != *q);                                      // illdefined because p and q are shapes, aka this would only compare coordinates
    //  *q = *p;                                               // illdefined compiles but would only swap coordinates (because they're shapes!)
    //  *p = *q;                                               // Doesn't compile because p is const pointer AND const Shape
    //  assert(*p == *q);                                      // illdefined works because it only compares coordinates, but not radii
    //  delete p;                                              // illdefined comment at line 200 for explanation
    //  delete q;                                              // illdefined comment at line 200 for explanation
     
        /**
         * So how do we fix this? We have to re-cast the pointers as circle pointers!
         */
        const Circle* const r = static_cast<const Circle*>(p);
              Circle* const s = static_cast<      Circle*>(q);

        /* Now this is correct because they DO have different radii */
        assert(*r != *s);

        /* Even though they're const pointers, their objects are not */
        *s = *r;

        // *r = *s;    // Doesn't compile because r is both const pointer and const circle

        /* Now they're equal in value */
        assert(*r == *s);

        /* Now we can delete properly */
        delete r;
        delete s;
    }

    {
        /* Circle array can't contain objects of parent */
    //  const Circle a[] = {Shape(2, 3), Circle(4, 5, 6)}; // doesn't compile
     
        /* Shape array CAN contain objects of Circle though */
        const Shape  a[] = {Shape(2, 3), Circle(4, 5, 6)};

        /* Statically bound, so treats both objects as just Shapes and calls Shape's methods */
        assert(a[0].area() == 0);
        assert(a[1].area() == 0);

        /* We CAN'T do this either */
        // const Circle c = static_cast<const Circle>(a[1]);
        // assert(c.area() == 3.14 * 6 * 6);
    }


    {
        /* Circle array of Circles */
        const Circle a[] = {Circle(2, 3, 4), Circle(5, 6, 7)};

        /* Now the area methods work because it assumes they're all Circles */
        assert(a[0].area() == 3.14 * 4 * 4);
        assert(a[1].area() == 3.14 * 7 * 7);

        /* this is legal.... but */
        const Shape* const p = a;

        /* Now we're calling Shape's methods again, because it's statically bound */
        assert(p[0].area() == 0);

        /* See DynamicBinding.c++ for explanation */
    //  assert(p[1].area() == 0);                              // illdefined
    }


    {
        /* A has just a double, so A is the size of a Double */
        /* Not that since A doesn't have any methods, doesn't need a pointer */
        assert(sizeof(A) ==                 sizeof(double));

        /* B is the size of an A plus two more doubles */
        assert(sizeof(B) == sizeof(A) + 2 * sizeof(double));
        
        /* B is basically just an array of objects, with A at the beginning */
        /* See DynamicBinding.c++ for full explanation */
        B t;
        char* p = reinterpret_cast<char*>(&t);
        char* x = reinterpret_cast<char*>(&t.x);
        char* y = reinterpret_cast<char*>(&t.y);
        char* z = reinterpret_cast<char*>(&t.z);
        assert(p                  == x);
        assert(x + sizeof(double) == y);
        assert(y + sizeof(double) == z);
    }

    cout << "Done." << endl;
    return 0;}
