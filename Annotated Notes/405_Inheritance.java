// ----------------
// Inheritance.java
// ----------------

/* Remember this is like a Java version of Vector */
import java.util.ArrayList;

class Shape {

    /* X and y coordinates */
    private int _x;
    private int _y;

    /* Shape's int constructor */
    public Shape (int x, int y) {
        _x = x;
        _y = y;}

    /* Shape's area() method. Returns 0 because we'll be extending this later */
    public double area () {
        return 0;}

    /* Equals() method, requires that we take in an "Object" because we're overriding Java's equals() method */
    public boolean equals (Object rhs) {

        /* Check to make sure it's an instance of Shape */
        if (!(rhs instanceof Shape))
            return false;

        /* If it is, cast it as a Shape into a tmp variable ("that") */
        Shape that = (Shape) rhs;

        /* Check coordinates to determine equality */
        return (_x == that._x) && (_y == that._y);}


    /* move() method to move Shape to new coordinates */
    /* "final" keyword means it's not extendable by direved classes. The java equivelant of NOT marking virtual */
    public final void move (int x, int y) {
        _x = x;
        _y = y;}

    /* Tostring method to make it pretty to print */
    public String toString () {
        return _x + ", " + _y;}}

/* Circle class that inherits from Shape */
class Circle extends Shape {

    /* Introduction of a radius variable */
    private int _r;

    /* Circle's int constructor. Call's shape's int constructor with super(), sets Circle's _r val */
    public Circle (int x, int y, int r) {
        super(x, y);
        _r = r;}

    /* Overriden area() method for Circle */
    public double area () {
        return 3.14 * _r * _r;}

    /* Overriden equals() method. again, takes in an Object, because we're overriding Object's equals() */
    public boolean equals (Object rhs) {

        /* Make sure it's a Circle */
        if (rhs instanceof Circle)
            /* If it is, call Shape's equals() and also compare radii */
            return super.equals(rhs) && (_r == ((Circle) rhs)._r);
        return false;}

    /* Radius getter function (Oh no he didn't!) */
    public int radius () {
        return _r;}

    /* Tostring function. Call's parent's toString and also tacks on the radius */
    public String toString () {
        return "(" + super.toString() + ", " + _r + ")";}}

final class Inheritance {
    public static void main (String[] args) {
        System.out.println("Inheritance.java");

        /**
         * This block makes a shape
         * area() is 0 because shapes don't have areas by themselves
         * move works
         * radius() doesn't compile because there's no radius in Shape
         * toString works
         */
        {
            final Shape x = new Shape(2, 3);
            assert x.area()     == 0;
            x.move(5, 6);
    //      assert x.radius()   == 0;           // error: cannot find symbol
            assert x.toString().equals("5, 6");
        }

        /**
         * Makes two shape objects.
         * Confirms they're different objects
         * But that they're equal in value
         */
        {
            final Shape x = new Shape(2, 3);
            final Shape y = new Shape(2, 3);
            assert x != y;
            assert x.equals(y);
        }

        /**
         * Testing Circle's stuff, all looks good
         * radius() now works
         */
        {
            final Circle x = new Circle(2, 3, 4);
            assert x.area()   == 3.14 * 4 * 4;
            x.move(5, 6);
            assert x.radius() == 4;
            assert x.toString().equals("(5, 6, 4)");
        }

        /**
         * Two circle objects.
         * Confirms they're not the same object,
         * but are equal in value (including radii)
         */
        {
            final Circle x = new Circle(2, 3, 4);
            final Circle y = new Circle(2, 3, 4);
            assert x != y;
            assert x.equals(y);
        }

        {
            /* Nope, shape isn't a type of Circle. Circle is a type of Shape */
    //      final Circle x = new Shape(2, 3);             // error: incompatible types
            final Shape  x = new Circle(2, 3, 4);

            /* Calls Circle's area(), remember Java is automatically dynamically bound */
            assert x.area()              == 3.14 * 4 * 4;
            x.move(5, 6);

            /* Doesn't work because x is a Shape, which doesn't have a radius() function in its API */
    //      assert x.radius()            == 0;            // error: cannot find symbol
         
            /* Does work if we cast x as Circle though */
            assert ((Circle) x).radius() == 4;

            /* Again, call's Circle's toString() because dynamic binding means functions fall through to derived ones */
            assert x.toString().equals("(5, 6, 4)");
        }

        {
            /* Makes two shape objects, confirms they're different objects */
            final Shape x = new Circle(2, 3, 4);
            final Shape y = new Circle(2, 3, 4);
            assert x != y;

            /* Calls Circle's equals() function because Java is dynamically bound automatically */
            assert x.equals(y);
        }

        {
            /* Circle array can't contain shapes because Shapes aren't types of Circles */
    //      final Circle[] a = {new Shape(2, 3), new Circle(2, 3, 4)}; // error: incompatible types
            
            /* Shape array will work though because Circles are types of Shapes */
            final Shape[]  a = {new Shape(2, 3), new Circle(2, 3, 4)};

            /**
             * Here's a difference between C++ and Java
             * in C++, the second line wouldn't work (see DynamicBinding.c++)
             * In Java however, even though it's a Shape array, it automatically moves over accordingly to the correct
             * address so that it does indeed call Circle's area() and not Shape's, or whatever undefined area it could end
             * up at in between (like what would happen in C++)
             */
            assert a[0].area() == 0;
            assert a[1].area() == 3.14 * 4 * 4;
        }

        {
            /* This is ok */
            final Shape[]          a = new Circle[3];

            /* This is not. ArrayList requires them to be all the same types */
    //      final ArrayList<Shape> x = new ArrayList<Circle>(10); // error: incompatible types
            /* You could, however, create an arraylist of shapes and then add circles to it */
        }

        System.out.println("Done.");}}
