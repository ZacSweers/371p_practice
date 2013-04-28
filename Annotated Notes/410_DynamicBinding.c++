// ------------------
// DynamicBinding.c++
// ------------------

#include <cassert>  // assert
#include <iostream> // cout, endl, istream, ostream
#include <utility>  // !=


/**
 * This is basically a little package containing what we did in our quiz over relational ops
 * Defines the four relational ops derived from == and <
 */
using namespace std::rel_ops;

// Really looks like this:
// namespace rel_ops {
//   template <class T> bool operator!= (const T& x, const T& y) { return !(x==y); }
//   template <class T> bool operator>  (const T& x, const T& y) { return y<x; }
//   template <class T> bool operator<= (const T& x, const T& y) { return !(y<x); }
//   template <class T> bool operator>= (const T& x, const T& y) { return !(x<y); }
// }

class Shape {
    friend bool operator == (const Shape& lhs, const Shape& rhs) {
        return lhs.equals(rhs);}

    friend std::istream& operator >> (std::istream& lhs, Shape& rhs) {
        return rhs.read(lhs);}

    friend std::ostream& operator << (std::ostream& lhs, const Shape& rhs) {
        return rhs.write(lhs);}

    /**
     * X and y coordinates
     */
    private:
        int _x;
        int _y;

    /**
     * Protected methods because we want subclasses to be able to call these
     */
    protected:

        /**
         * Equals method that children can use as well as parent
         * Not open to other classes though
         */
        virtual bool equals (const Shape& that) const {
            return (_x == that._x) && (_y == that._y);}

        /**
         * Read function that that outputs the coordinates as an istream object
         */
        virtual std::istream& read (std::istream& in) {
            return in >> _x >> _y;}

        /**
         * Write function that outputs the coordinates as an ostream object
         * Think, we could now use this:
         * Shape x;
         * std::cout << x << std::endl;
         */
        virtual std::ostream& write (std::ostream& out) const {
            return out << _x << " " << _y;}

    public:

        /**
         * Int constructor. Notice that it uses an initializer block to set _x and _y
         * but doesn't have anything in the actual method block
         */
        Shape (int x, int y) :
                _x (x),
                _y (y)
            {}

        /* We make the constructor virtual so that children implement their own */
        virtual ~Shape ()
            {}

/**
 * Given to use for free
 */
/*
        Shape (const Shape& that) :
                _x (that._x),
                _y (that._y)
            {}

        Shape& operator = (const Shape& that) {
            _x = that._x;
            _y = that._y;
            return *this;}

        template <typename T>       // doesn't compile
        virtual double f () const {
            return 0;}
*/

        /**
         * Returns 0, because what could a shape with only coordinates possibly return for an area?
         * Notice it's virtual so that it can be extended
         */
        virtual double area () const {
            return 0;}

        /**
         * Moves shape to new coordinates
         * Notice now we don't use an initializer block because only constructors can use those
         * Also notice it's not virtual, AKA not open for extension
         */
        void move (int x, int y) {
            _x = x;
            _y = y;}};

class Circle : public Shape {
    private:
        /* Radius variable */
        int _r;

    protected:

        /**
         * Equals method, extended from Shape
         */
        virtual bool equals (const Shape& that) const {

            /* Dynamic case returns 0 if it's not. Basically C++'s version of 'instanceof', and gives you a pointer to use if it works */
            if (const Circle* const p = dynamic_cast<const Circle*>(&that))

                /* Call shape's equals() and also check radii */
                return Shape::equals(*p) && (_r == p->_r);

            /* Must not be a circle object */
            return false;}

        /* Calls Shape's read (for coordinates) and tacks on the radius */
        virtual std::istream& read (std::istream& in) {
            return Shape::read(in) >> _r;}

        /* Calls Shape's write (for coordinates) and tacks on the radius */
        virtual std::ostream& write (std::ostream& out) const {
            return Shape::write(out) << " " << _r;}

    public:

        /**
         * Circle's int constructor
         * Notice again the use of an initializer block, including calling Shape's int constructor
         */
        Circle (int x, int y, int r) :
                Shape (x, y),
                _r    (r)
            {}

/**
 * Given to us for free
 */
/*
        Circle (const Circle& that) :
                Shape (that),
                _r    (that.r)
            {}

        ~Circle ()
            {}

        Circle& operator = (const Circle& that) {
            Shape::operator=(that);
            _r = that.r;
            return *this;}
*/

        /* Circle's extension of area() */
        virtual double area () const {
            return 3.14 * _r * _r;}

        /* Getter function for radius (oh no he didn't!) */
        int radius () const {
            return _r;}};

/**
 * A struct that contains a double and a virtual function f()
 */
struct A {
    double _x;
    virtual void f () {}};

/**
 * B struct that inherits from A, contains an A in it (thus a _x and inherited f())
 * Also adds a _y and _z double
 */
struct B : A {
    double _y;
    double _z;};

int main () {
    using namespace std;
    cout << "DynamicBinding.c++" << endl;

    {
        Shape x(2, 3);  /* Instantiates a Shape object at (2,3) */
        x.move(4, 5);   /* Moves x to (4,5) */
        assert(x.area()   == 0);    /* Returns 0 because it's Shape, not a circle */
    //  assert(x.radius() == 0); // doesn't compile because Shape doesn't have a radius() method
    }

    {
        /* Instantiates two shapes on the stack, x is const */
        const Shape x(2, 3);
              Shape y(4, 5);

        /* Confirm they're different objects */
        assert(x != y);

        /* Set y equal to x */
        y = x;

        // x = y;   /* Doesn't work the other way around because x is const */
        
        /* Now they're the same */
        assert(x == y);
    }

    {
        /* Circle object at (2,3) with radius 4 */
        Circle x(2, 3, 4);

        /* Moved to (5,6) */
        x.move(5, 6);

        /* area() function now returns something nonzero because it's using circle's overrode the parent's */
        assert(x.area()   == 3.14 * 4 * 4);

        /* Radius function works now because Circle has one */
        assert(x.radius() == 4);
    }

    {
        /* Instantiates two Circles on the stack, x is const */
        const Circle x(2, 3, 4);
              Circle y(2, 3, 5);

        /* Confirm they're different objects */
        assert(x != y);

        /* Set y equal to x */
        y = x;

        // x = y;   /* Doesn't work the other way around because x is const */
        
        /* Now they're equal */
        assert(x == y);
    }

    {
        /* Doesn't compile because Shape isn't a type of Circle */
    //  Circle* const p = new Shape(2, 3);              // doesn't compile
     
        /* Rather, Circle is a type of shape! */
        Shape*  const p = new Circle(2, 3, 4);
        p->move(5, 6);

        /* Dynamically bound, so p call's Circle's area() even though it's a Shape pointer */
        /* This happens because we marked area() in Shape as "Virtual" */
        assert(p->area()        == 3.14 * 4 * 4);

        /* If we call Shape's area() directly, it fails */
        assert(p->Shape::area() == 0);

        /* Still doesn't work because it thinks it's a shape object */
    //  assert(p->radius() == 4);                       // doesn't compile
     
        /* Try to cast as circle. If it works, cool! */
        if (Circle* const q = dynamic_cast<Circle*>(p))
            assert(q->radius() == 4);
        try {
            /* Works with references too, but must be in try/catch block to catch bad_cast exception */
            Circle& r = dynamic_cast<Circle&>(*p);
            assert(r.radius() == 4);}
        catch (const bad_cast& e) {
            assert(false);}
        delete p;
    }

    {
        /* Creates two Circles with Shape pointers, const pointers, p is a const Shape */
        const Shape* const p = new Circle(2, 3, 4);
              Shape* const q = new Circle(2, 3, 5);

        /* Not the same object */
        assert(*p != *q);

        /* Ill defined. We can change what the Shape that q points to is, but this is insane because who knows what would happen */
    //  *q = *p;                                                    // illdefined
     
        /* Doesn't work because p is a const Shape object as well as a const pointer */
        // *p = *q;

        /* Try to case as const circle pointer to a const circle */
        if (const Circle* const r = dynamic_cast<const Circle*>(p))
            /* If it gets here, try to case it as just a const Circle pointer (AKA the Circle object itself is mutable) */
            if (Circle* const s = dynamic_cast<Circle*>(q))
                /* Now we can mutate *s, which is pointing to the same Circle as p */
                *s = *r;

        /* Now they're equal. */
        assert(*p == *q);
        delete p;
        delete q;

        /**
         * NOTE: Remember that const is just a flag of sorts. It doesn't protect the object per say, it just tells the program
         * that whatever you're dealing with shouldn't be changed. You can cast away constness like we did above to ignore this.
         * It's like having a sign on a painting that says "Do not touch", but then you cast it as, say, a "touchable" painting,
         * and suddenly you're allowed to touch it.
         */
    }

    {
        /* Doesn't work because a Circle array can only contain Circles or objects that are types of Circles */
        /* AKA Shape is not a type of Circle, so we can't put one in there */
    //  const Circle a[] = {Shape(2, 3), Circle(4, 5, 6)}; // doesn't compile
        const Shape  a[] = {Shape(2, 3), Circle(4, 5, 6)};

        /* Treats them all as Shape pointers, statically bound so a[1].area() is also 0 even though it's a circle */
        /* This is because we made it Shape array and not a Shape* array */
        /* We'd have to dynamically cast each one to see if we can do something else with it. */
        assert(a[0].area() == 0);
        assert(a[1].area() == 0);
    }

    {
        /* Here we make an array of Circles, and as a result we can get the correct return vals. */
        const Circle a[] = {Circle(2, 3, 4), Circle(5, 6, 7)};
        assert(a[0].area() == 3.14 * 4 * 4);
        assert(a[1].area() == 3.14 * 7 * 7);

        /* We set p to our Circle array now. This is ok, because it's polymorphic. Circles are types of Shapes */
        const Shape* const p = a;

        /* First one works */
        assert(p[0].area() == 3.14 * 4 * 4);
    //  assert(p[1].area() == 0);               // illdefined because pointer p doesn't advance correctly 
                                                //to the second item in the array. Full explanation from 
                                                //Piazza post @408 (https://piazza.com/class#spring2013/cs371p/408): 
                                                //p[0].area() calls the correct area method because of dynamic binding. 
                                                //But because p is a pointer to a Shape, when you look at the next 
                                                //element of p (p[1]), you're not moving the correct amount of space 
                                                //in memory to look at a[1] (because a is an array of Circles, not Shapes).
                                                //So p[1] points at some weird thing that's not actually pointing at 
                                                //a[1]. So the area method is illdefined for that weird place in memory.
                                                
        /**
         * A more basic example:
         * Say you have class A, that holds a double object
         * And you have class B, that extends A and holds an extra double object
         * sizeof(A) == 8
         * sizeof(B) == 16 (because it's two doubles now total)
         *
         * If you have an array of B
         * B x[2];
         * x[0]
         * x[1]'s address in mem would be 16 bytes forward, or the size of one B object
         *
         * Now if we reassign x
         * A y[2] = x;
         *
         * y[0] would be the same address as x[0]
         * but
         * y[1]'s address would be 8 bytes forward (size of one A object), but that would be in the middle of x[0]'s B object!
         *
         *
         * Arrays:
         * A array, each block is 8 bytes
         * 
         * ---------------------------------
         * |  A[0] |  A[1] |  A[2] |  A[3] |
         * ---------------------------------
         * |       B[0]    |       B[1]    |
         * ---------------------------------
         * 
         * B array, each block is 16 bytes
         *
         * 
         */

    }

    {
        /* A is the size of one double pls a pointer, because it contains one double */
        /* Pointer value is either 4 bytes (on 32bit system) or 8 bytes (64bit) */
        assert(sizeof(A) == sizeof(void*) +     sizeof(double));

        /* B is two more doubles plus an A */
        assert(sizeof(B) == sizeof(A)     + 2 * sizeof(double));

        /**
         * This example is to show that if we looked at the parts of each, they stack on top of each other like an array
         * Note all the attributes are public by default since we're using structs
         */
        B t;

        /* Starting address of B (and also the A object in it) */
        char* p = reinterpret_cast<char*>(&t);

        /* Address of A's _x double */
        char* x = reinterpret_cast<char*>(&t._x);

        /* Address of B's _y double */
        char* y = reinterpret_cast<char*>(&t._y);

        /* Address of B's _z double */
        char* z = reinterpret_cast<char*>(&t._z);

        /* Starting address plus the sizeof a pointer gives us our x address */
        assert(p + sizeof(void*)  == x);

        /* Our x address plus the sizeof a double puts us at the y address */
        assert(x + sizeof(double) == y);
        assert(y + sizeof(double) == z);

        // ASCII art of a B object as it appears on the heap/stack

        //      * = pointer
        // ----------------------------------------------------------
        // |    *   |      _x       |      _y       |      _z       |
        // ----------------------------------------------------------
        // ^                        ^                               ^
        // |                        |                               |
        //  \                      /                               /
        //   \                    /                               /
        //    \________ A _______/                               /
        //     \                                                /
        //      \                                              /
        //       \                                            /
        //        \                                          /
        //         \___________________ B __________________/

    }

    cout << "Done." << endl;
    return 0;}
