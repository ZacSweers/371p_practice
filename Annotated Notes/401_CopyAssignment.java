// ----------------
// CloneEquals.java
// ----------------

import java.util.Arrays;

/*
class Object {
    protected Object clone () throws CloneNotSupportedException {
        if (!(this instanceof Cloneable))
            throw new CloneNotSupportedException();
        // ...magic...
        }

    public boolean equals (Object that) {
        return this == that;}}
*/

final class MyArrayList<T> implements Cloneable {
    private int s;
    private T[] a;

    public MyArrayList () {
        this(10);}

    public MyArrayList (int c) {
        s = 0;
        a = (T[]) new Object[c];}                                       // warning: unchecked cast

    public void add (int i, T x) {
        a[i] = x;
        ++s;}

    public Object clone () {
        try {
            final MyArrayList<T> that = (MyArrayList<T>) super.clone(); // warning: unchecked cast
            that.a = (T[]) new Object[s];                               // warning: unchecked cast
            System.arraycopy(a, 0, that.a, 0, s);
            return that;}
        catch (CloneNotSupportedException e) {
            return null;}}

    public boolean equals (Object that) {
        if (this == that)
            return true;
        if (!(that instanceof MyArrayList))
            return false;
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
        final MyArrayList<String> x = new MyArrayList<String>();
        final MyArrayList<String> y = new MyArrayList<String>(10);
        assert x != y;
        assert x.equals(y);
        }

        {
        final MyArrayList<String> x = new MyArrayList<String>();
        final MyArrayList<String> y = new MyArrayList<String>(20);
        assert x != y;
        assert !x.equals(y);
        }

        {
        final MyArrayList<String> x = new MyArrayList<String>(3);
        x.add(0, "abc");
        x.add(1, "def");
        x.add(2, "ghi");
        final MyArrayList<String> y = (MyArrayList<String>) x.clone();   // warning: unchecked cast
        assert x != y;
        assert x.equals(y);
        }

        System.out.println("Done.");}}
