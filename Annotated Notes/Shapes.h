// --------
// Shapes.h
// --------

#ifndef Shapes_h
#define Shapes_h

#include <iostream> // istream, ostream

class AbstractShape {
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
        AbstractShape& operator = (const AbstractShape& that) {
            _x = that._x;
            _y = that._y;
            return *this;}

        virtual bool equals (const AbstractShape& that) const = 0;

        virtual std::istream& read (std::istream& in) = 0;

        virtual std::ostream& write (std::ostream& out) const = 0;

    public:
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
        virtual ~AbstractShape ()
            {}

        virtual double area () const = 0;

        virtual AbstractShape* clone () const = 0;

        void move (int x, int y) {
            _x = x;
            _y = y;}};

bool AbstractShape::equals (const AbstractShape& that) const {
    return (_x == that._x) && (_y == that._y);}

std::istream& AbstractShape::read (std::istream& in) {
    return in >> _x >> _y;}

std::ostream& AbstractShape::write (std::ostream& out) const {
    return out << _x << " " << _y;}

class Circle : public AbstractShape {
    private:
        int _r;

    protected:
        virtual bool equals (const AbstractShape& that) const {
            if (const Circle* const p = dynamic_cast<const Circle*>(&that))
                return AbstractShape::equals(*p) && (_r == p->_r);
            return false;}

        virtual std::istream& read (std::istream& in) {
            return AbstractShape::read(in) >> _r;}

        virtual std::ostream& write (std::ostream& out) const {
            return AbstractShape::write(out) << " " << _r;}

    public:
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

        virtual double area () const {
            return 3.14 * _r * _r;}

        virtual Circle* clone () const {
            return new Circle(*this);}

        int radius () const {
            return _r;}};

#endif // Shapes_h
