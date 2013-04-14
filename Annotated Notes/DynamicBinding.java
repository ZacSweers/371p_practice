// -------------------
// DynamicBinding.java
// -------------------

class A {
    public String f1 () {
        return f2();}

    public String f2 () {
        return "A.f2";}

    public String g1 () {
        return g2();}

    public static String g2 () {
        return "A.g2";}

    public String h1 () {
        return h2();}

    private String h2 () {
        return "A.h2";}}

class B extends A {
    public String f2 () {
        return "B.f2";}

    public static String g2 () {
        return "B.g2";}

    public String h2 () {
        return "B.h2";}}

final class DynamicBinding {
    public static void main (String[] args) {
        System.out.println("MethodOverriding.java");

        {
        A x = new A();
        assert x.f1() == "A.f2";
        assert x.g1() == "A.g2";
        assert x.h1() == "A.h2";
        }

        {
        B x = new B();
        assert x.f1() == "B.f2";
        assert x.g1() == "A.g2";
        assert x.h1() == "A.h2";
        }

        {
        A x = new B();
        assert x.f1() == "B.f2";
        assert x.g1() == "A.g2";
        assert x.h1() == "A.h2";
        }

        System.out.println("Done.");}}
