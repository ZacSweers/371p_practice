// ----------------
// Inheritance.java
// ----------------

import java.util.ArrayList;

class Shape {
    private int _x;
    private int _y;

    public Shape (int x, int y) {
        _x = x;
        _y = y;}

    public double area () {
        return 0;}

    public boolean equals (Object rhs) {
        if (!(rhs instanceof Shape))
            return false;
        Shape that = (Shape) rhs;
        return (_x == that._x) && (_y == that._y);}

    public final void move (int x, int y) {
        _x = x;
        _y = y;}

    public String toString () {
        return _x + ", " + _y;}}

class Circle extends Shape {
    private int _r;

    public Circle (int x, int y, int r) {
        super(x, y);
        _r = r;}

    public double area () {
        return 3.14 * _r * _r;}

    public boolean equals (Object rhs) {
        if (rhs instanceof Circle)
            return super.equals(rhs) && (_r == ((Circle) rhs)._r);
        return false;}

    public int radius () {
        return _r;}

    public String toString () {
        return "(" + super.toString() + ", " + _r + ")";}}

final class Inheritance {
    public static void main (String[] args) {
        System.out.println("Inheritance.java");

        {
        final Shape x = new Shape(2, 3);
        assert x.area()     == 0;
        x.move(5, 6);
//      assert x.radius()   == 0;           // error: cannot find symbol
        assert x.toString().equals("5, 6");
        }

        {
        final Shape x = new Shape(2, 3);
        final Shape y = new Shape(2, 3);
        assert x != y;
        assert x.equals(y);
        }

        {
        final Circle x = new Circle(2, 3, 4);
        assert x.area()   == 3.14 * 4 * 4;
        x.move(5, 6);
        assert x.radius() == 4;
        assert x.toString().equals("(5, 6, 4)");
        }

        {
        final Circle x = new Circle(2, 3, 4);
        final Circle y = new Circle(2, 3, 4);
        assert x != y;
        assert x.equals(y);
        }

        {
//      final Circle x = new Shape(2, 3);             // error: incompatible types
        final Shape  x = new Circle(2, 3, 4);
        assert x.area()              == 3.14 * 4 * 4;
        x.move(5, 6);
//      assert x.radius()            == 0;            // error: cannot find symbol
        assert ((Circle) x).radius() == 4;
        assert x.toString().equals("(5, 6, 4)");
        }

        {
        final Shape x = new Circle(2, 3, 4);
        final Shape y = new Circle(2, 3, 4);
        assert x != y;
        assert x.equals(y);
        }

        {
//      final Circle[] a = {new Shape(2, 3), new Circle(2, 3, 4)}; // error: incompatible types
        final Shape[]  a = {new Shape(2, 3), new Circle(2, 3, 4)};
        assert a[0].area() == 0;
        assert a[1].area() == 3.14 * 4 * 4;
        }

        {
        final Shape[]          a = new Circle[3];
//      final ArrayList<Shape> x = new ArrayList<Circle>(10); // error: incompatible types
        }

        System.out.println("Done.");}}
