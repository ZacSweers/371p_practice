// ---------------
// Inheritance.c++
// ---------------

#include <cassert>  // assert
#include <iostream> // cout, endl, istream, ostream
#include <utility>  // !=
#include <vector>   // vector

class Shape {
    friend bool operator == (const Shape& lhs, const Shape& rhs) {
        return (lhs._x == rhs._x) && (lhs._y == rhs._y);}

    friend std::istream& operator >> (std::istream& lhs, Shape& rhs) {
        return lhs >> rhs._x >> rhs._y;}

    friend std::ostream& operator << (std::ostream& lhs, const Shape& rhs) {
        return lhs << rhs._x << " " << rhs._y;}

    private:
        int _x;
        int _y;

    public:
        Shape (int x, int y) :
                _x (x),
                _y (y)
            {}
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
        double area () const {
            return 0;}

        void move (int x, int y) {
            _x = x;
            _y = y;}};

class Circle : public Shape {
    friend bool operator == (const Circle& lhs, const Circle& rhs) {
        return (static_cast<const Shape&>(lhs) == rhs) && (lhs._r == rhs._r);}

    friend std::istream& operator >> (std::istream& lhs, Circle& rhs) {
        return lhs >> static_cast<Shape&>(rhs) >> rhs._r;}

    friend std::ostream& operator << (std::ostream& lhs, const Circle& rhs) {
        return lhs << static_cast<const Shape&>(rhs) << " " << rhs._r;}

    private:
        int _r;

    public:
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

        double area () const {
            return 3.14 * _r * _r;}

        int radius () const {
            return _r;}};

struct A {
    double x;};

struct B : A {
    double y;
    double z;};

int main () {
    using namespace std;
    using namespace std::rel_ops;
    cout << "Inheritance.c++" << endl;

    {
    Shape x(2, 3);
    x.move(4, 5);
    assert(x.area()   == 0);
//  assert(x.radius() == 0); // doesn't compile
    }

    {
    const Shape x(2, 3);
          Shape y(4, 5);
    assert(x != y);
    y = x;
    assert(x == y);
    }

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
//  Circle* const p = new Shape(2, 3);         // doesn't compile
    Shape*  const p = new Circle(2, 3, 4);
    p->move(5, 6);
    assert(p->area()   == 0);
//  assert(p->radius() == 4);                  // doesn't compile
//  delete p;                                  // illdefined
    Circle* const q = static_cast<Circle*>(p);
    assert(q->area()   == 3.14 * 4 * 4);
    assert(q->radius() == 4);
    delete q;
    }

    {
    const Shape* const p = new Circle(2, 3, 4);
          Shape* const q = new Circle(2, 3, 5);
//  assert(*p != *q);                                      // illdefined
//  *q = *p;                                               // illdefined
//  assert(*p == *q);                                      // illdefined
//  delete p;                                              // illdefined
//  delete q;                                              // illdefined
    const Circle* const r = static_cast<const Circle*>(p);
          Circle* const s = static_cast<      Circle*>(q);
    assert(*r != *s);
    *s = *r;
    assert(*r == *s);
    delete r;
    delete s;
    }

    {
//  const Circle a[] = {Shape(2, 3), Circle(4, 5, 6)}; // doesn't compile
    const Shape  a[] = {Shape(2, 3), Circle(4, 5, 6)};
    assert(a[0].area() == 0);
    assert(a[1].area() == 0);
    }

    {
    const Circle a[] = {Circle(2, 3, 4), Circle(5, 6, 7)};
    assert(a[0].area() == 3.14 * 4 * 4);
    assert(a[1].area() == 3.14 * 7 * 7);
    const Shape* const p = a;
    assert(p[0].area() == 0);
//  assert(p[1].area() == 0);                              // illdefined
    }

    {
    assert(sizeof(A) ==                 sizeof(double));
    assert(sizeof(B) == sizeof(A) + 2 * sizeof(double));
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
