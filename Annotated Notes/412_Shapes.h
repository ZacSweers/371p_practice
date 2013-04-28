// --------
// Shapes.h
// --------

#ifndef Shapes_h
#define Shapes_h

#include <iostream> // istream, ostream

class AbstractShape {

    /* See Inheritance.c++ for explanation */
    friend bool operator == (const AbstractShape& lhs, const AbstractShape& rhs) {
        return lhs.equals(rhs);}

    friend bool operator != (const AbstractShape& lhs, const AbstractShape& rhs) {
        return !(lhs == rhs);}

    friend std::istream& operator >> (std::istream& lhs, AbstractShape& rhs) {
        return rhs.read(lhs);}

    friend std::ostream& operator << (std::ostream& lhs, const AbstractShape& rhs) {
        return rhs.write(lhs);}

    private:
        int _x;
        int _y;

    protected:

        /* Protected, but not public. Can't instantiate an abstract class anyway, no need to be public */
        AbstractShape& operator = (const AbstractShape& that) {
            _x = that._x;
            _y = that._y;
            return *this;}

        /**
         * The following are pure virtual functions (AKA the equivelant of making a function abstract)
         * NOTE: to make it pure virtual, it must be equal to 0 and be declared virtual.
         */
        virtual bool equals (const AbstractShape& that) const = 0;

        virtual std::istream& read (std::istream& in) = 0;

        virtual std::ostream& write (std::ostream& out) const = 0;

    public:

        /**
         * Int constructor
         * Note that coordinates are set in initializer block
         */
        AbstractShape (int x, int y) :
                _x (x),
                _y (y)
            {}
/*
        AbstractShape (const AbstractShape& that) :
                _x (that._x),
                _y (that._y)
            {}
*/

        /* Virtual, but not pure virtual. If we tried to delete an AbstractShape pointer, compiler would complain */
        virtual ~AbstractShape ()
            {}

        /**
         * The area() and clone() functions are pure virtual though because we'll implement them later
         * in derived classes
         */
        virtual double area () const = 0;

        virtual AbstractShape* clone () const = 0;

        /* Not virtual because this won't change in derived classes. The equivelant of calling it "final" */
        void move (int x, int y) {
            _x = x;
            _y = y;}};

/**
 * The following three functions were marked PURE VIRTUAL in the class, but c++ allows for
 * optionally defining a pure virtual function outside of the class. Can only be done outside though
 */
bool AbstractShape::equals (const AbstractShape& that) const {
    return (_x == that._x) && (_y == that._y);}

std::istream& AbstractShape::read (std::istream& in) {
    return in >> _x >> _y;}

std::ostream& AbstractShape::write (std::ostream& out) const {
    return out << _x << " " << _y;}

/* Circle class, inherits from AbstractShape */
class Circle : public AbstractShape {
    private:
        /* Radius comes into play */
        int _r;

    protected:
        /* Overrides the AbstractCircle equals, read, and write functions */
        /* See DynamicBinding.c++ for method explanations */
        virtual bool equals (const AbstractShape& that) const {
            if (const Circle* const p = dynamic_cast<const Circle*>(&that))
                return AbstractShape::equals(*p) && (_r == p->_r);
            return false;}

        virtual std::istream& read (std::istream& in) {
            return AbstractShape::read(in) >> _r;}

        virtual std::ostream& write (std::ostream& out) const {
            return AbstractShape::write(out) << " " << _r;}

    public:
        /* Int constructor, note initializer block */
        Circle (int x, int y, int r) :
                AbstractShape (x, y),
                _r            (r)
            {}
/*
        Circle (const Circle& that) :
                AbstractShape (that),
                _r            (that._r)
            {}

        virtual ~Circle ()
            {}

        Circle& operator = (const Circle& that) {
            AbstractShape::operator=(that);
            _r = that._r;
            return *this;}
*/

        /* area() function now defined */
        virtual double area () const {
            return 3.14 * _r * _r;}

        /* clone() function now defined */
        virtual Circle* clone () const {
            return new Circle(*this);}

        /* Radius getter */
        int radius () const {
            return _r;}};

        /**
         * NOTE: a few other nuances
         * C++ requires that if class is abstract, a derived class is also abstract unless it defines ALL of its parents' abstract methods
         * Circle still gets move(), but it can't override it, nor does it need to define it
         * C++ allows for multiple inheritance. As a result, you can't just call super. You have to specifically call the constructor of the particular parent
         */

#endif // Shapes_h
