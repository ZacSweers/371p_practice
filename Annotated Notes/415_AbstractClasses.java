// --------------------
// AbstractClasses.java
// --------------------

/**
 * NOTE: Much of the explanations for methods are in DynamicBinding.java
 * If it's missing an explanation here, look there.
 */

import java.util.ArrayList;

abstract class AbstractShape {
    private int _x;
    private int _y;

    protected AbstractShape (int x, int y) {
        _x = x;
        _y = y;}

    /* Note that if we make one method abstract in Java, we must mark the whole class as abstract */
    public abstract double area ();

    public boolean equals (Object rhs) {
        if (!(rhs instanceof AbstractShape))
            return false;
        AbstractShape that = (AbstractShape) rhs;
        return (_x == that._x) && (_y == that._y);}

    /* Final because it's not going to be extended */
    public final void move (int x, int y) {
        _x = x;
        _y = y;}

    /* toString is weird, because we can't define it outside of the class like in c++ */
    public abstract String toString ();

    /* Annoying auxiliary function that we can call in derived classes */
    protected String toString2 () {
        return _x + ", " + _y;}}

/* Circle extends AbstractShape. Final means nothing can extend from circle (say, class SemiCircle?) */
final class Circle extends AbstractShape {
    private int _r;

    /* Int constructor, note that we can use super and not have to be specific about which parent because java doesn't allow multiple inheritance */
    public Circle (int x, int y, int r) {
        super(x, y);
        _r = r;}

    /* Defining area() */
    public double area () {
        return 3.14 * _r * _r;}

    public boolean equals (Object rhs) {
        if (!(rhs instanceof Circle))
            return false;
        Circle that = (Circle) rhs;
        return super.equals(rhs) && (_r == that._r);}

    public int radius () {
        return _r;}

    /* toString. Calls super.toString2() as explained above */
    public String toString () {
        return "(" + super.toString2() + ", " + _r + ")";}}

final class AbstractClasses {
    public static void main (String[] args) {
        System.out.println("AbstractClasses.java");

        /* Can't instantiate abstract classes */
/*
        {
        final AbstractShape x = new AbstractShape(2, 3);
        assert x.area()   == 0;
        x.move(5, 6);
//      assert x.radius() == 0;

        {
        final AbstractShape x = new AbstractShape(2, 3);
        final AbstractShape y = new AbstractShape(2, 3);
        assert x != y;
        assert x.equals(y);
        }
        }
*/

        /* Constructor is working */
        {
        final Circle x = new Circle(2, 3, 4);
        assert x.area()   == 3.14 * 4 * 4;
        x.move(5, 6);
        assert x.radius() == 4;
        }

        /* Equals is working */
        {
        final Circle x = new Circle(2, 3, 4);
        final Circle y = new Circle(2, 3, 4);
        assert x != y;
        assert x.equals(y);
        }

        /* Polymorphism */
        {

        /* Can instantiate AbstractShape if it's a non-abstract derived class */
        final AbstractShape x = new Circle(2, 3, 4);

        /* Correctly calls Circle's area() */
        assert x.area()   == 3.14 * 4 * 4;
        x.move(5, 6);

        /* AbstractShape API doesn't know what a radius is */
//      assert x.radius() == 0;
     
        /* But if we cast it as a Circle it does */
        assert ((Circle) x).radius() == 4;
        }

        /* Testing polymorphic equals */
        {
        final AbstractShape x = new Circle(2, 3, 4);
        final AbstractShape y = new Circle(2, 3, 4);
        assert x != y;
        assert x.equals(y);
        }

        /* Can make an array of AbstractShapes if it's full of non-abstract derived classes */
        {
        final AbstractShape[] a = {new Circle(2, 3, 4), new Circle(5, 6, 7)};

        /* Correctly calls Circle's area() */
        assert a[0].area() == 3.14 * 4 * 4;
        assert a[1].area() == 3.14 * 7 * 7;
        }

        /* Can't make an ArrayList<AbstractShape> equal to an ArrayList<Circle> */
        /* We can however later add Circle objects to an ArrayList of AbstractShapes */
        {
        final AbstractShape[]          a = new Circle[3];
//      final ArrayList<AbstractShape> x = new ArrayList<Circle>(10);
        }

        System.out.println("Done.");}}
