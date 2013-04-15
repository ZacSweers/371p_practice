// ----------------
// CloneEquals.java
// ----------------

import java.util.Arrays;

/*
 * EXPLANATION: This is Object's clone() method that we're overriding below

class Object {
    protected Object clone () throws CloneNotSupportedException {
        if (!(this instanceof Cloneable))
            throw new CloneNotSupportedException();
        // ...magic...
        }

    public boolean equals (Object that) {
        return this == that;}}
*/

/**
 * Must implement cloneable from above in order to be cloneable (inherit its superclass method)
 */
final class MyArrayList<T> implements Cloneable {
    private int s;  /* Size */
    private T[] a;  /* Template array */

    /**
     * Default constructor, calls int constructor below with size 10
     */
    public MyArrayList () {
        this(10);}

    /**
     * Int constructor, sets size to 0 (because we haven't filled anything)
     * Creates template array of objects of size c
     */
    public MyArrayList (int c) {
        s = 0;
        a = (T[]) new Object[c];}                                       // warning: unchecked cast

    /**
     * Puts x at index i, increments s. Seems like it should've been called "insert"
     * This is a poor-man's arraylist function because it doesn't check the bound
     */
    public void add (int i, T x) {
        a[i] = x;
        ++s;}

    /**
     * Clone function
     */
    public Object clone () {

        /**
         * Tries to create a new MyArrayList catches if it's not cloneable
         */
        try {

            /* Create a clone of our current object, must implement cloneable in class declaration  */
            final MyArrayList<T> that = (MyArrayList<T>) super.clone(); // warning: unchecked cast

            // that = (MyArrayList<T>) super.clone();       /* Final keyword makes "that" reference immutable. i.e. can't point to something else */

            /**
             * "that" is final, but its contents are not. Create a new T[] array of size s.
             * We do this because it's initially not initialized after clone()
             */
            that.a = (T[]) new Object[s];                               // warning: unchecked cast

            /**
             * Copy contents of original array into the new object, using Java's arraycopy
             * arraycopy(src, start_index, dest, start_index, length)
             */
            System.arraycopy(a, 0, that.a, 0, s);
            return that;}
        catch (CloneNotSupportedException e) {
            return null;}}

    /**
     * Must pass in an Object (and not MyArraylist).
     * If we don't pass in Object, then we won't override Object's equals(Object) method
     */
    public boolean equals (Object that) {

        /* Check references, if it's the same object */
        if (this == that)
            return true;

        /* Make sure they're compatable classes */
        if (!(that instanceof MyArrayList))
            return false;

        /* Temporary object, used in order to cast it as a MyArrayList<T> */
        final MyArrayList<T> tmp = (MyArrayList<T>) that;               // warning: unchecked cast
        if (s != tmp.s)
            return false;
        if (!(Arrays.equals(a, tmp.a)))
            return false;
        return true;}}

final class CloneEqualsTest {
    public static void main (String[] args) {
        System.out.println("CloneEquals.java");

        {

        /* Make two instances, they'll have the same size because of its default constructor */
        final MyArrayList<String> x = new MyArrayList<String>();
        final MyArrayList<String> y = new MyArrayList<String>(10);

        /* Both are size 10 because the default constructor calls the int constructor with 10, not same object */
        assert x != y;
        assert x.equals(y);
        }

        {

        /* Elaborates on above code, shows that default only makes size 10 */
        final MyArrayList<String> x = new MyArrayList<String>();
        final MyArrayList<String> y = new MyArrayList<String>(20);

        /* Not the same object and not same sizes */
        assert x != y;
        assert !x.equals(y);

        /* Doesn't compile, but here for clarity */
        // assert x.s == 10;
        // assert y.s == 20;
        }

        {

        /* Create new instance, add 3 strings. */
        final MyArrayList<String> x = new MyArrayList<String>(3);
        x.add(0, "abc");
        x.add(1, "def");
        x.add(2, "ghi");

        /* Clone x into a y */
        final MyArrayList<String> y = (MyArrayList<String>) x.clone();   // warning: unchecked cast

        /* Different objects */
        assert x != y;

        /* But they have the same contents (strings at respective array indices would be equal) */
        assert x.equals(y);

        /**
         * But they still point to the same strings because Java caches strings, points to same strings
         * If we wanted separate strings we would have to force java to create a new string object
         */
        // assert x.a[0] == y.a[0];
        }

        System.out.println("Done.");}}
