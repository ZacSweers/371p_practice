// -------------------
// DynamicBinding.java
// -------------------

/* Parent A class */
class A {
    public String f1 () {
        return f2();}

    public String f2 () {
        return "A.f2";}

    public String g1 () {
        return g2();}

    /* Cannot be extended with static keyword */
    public static String g2 () {
        return "A.g2";}

    public String h1 () {
        return h2();}

    /* Private methods cannot be extended either */
    /* Automatically declared as "final", and hidden from derived classes */
    private String h2 () {
        return "A.h2";}}

/* Child B class, extends from A */
class B extends A {

    /* This overrides A's f2() */
    public String f2 () {
        return "B.f2";}

    /* This overrides A's g2() */
    public static String g2 () {
        return "B.g2";}

    /* Doesn't override A's h2() because A's is private */
    public String h2 () {
        return "B.h2";}

    /* This wouldn't compile though if we tried to force the override */
    // @override
    // public String h2 () {
    //     return "B.h2";}

    }

final class DynamicBinding {
    public static void main (String[] args) {
        System.out.println("MethodOverriding.java");

        /* Testing A's methods */
        {
            A x = new A();
            assert x.f1() == "A.f2";
            assert x.g1() == "A.g2";
            assert x.h1() == "A.h2";
        }

        /* Testing B's inherited (but not overridden) methods */
        {
            B x = new B();

            /* Still print's B because f1() calls f2(), in this case calling B's overridden f2() */
            assert x.f1() == "B.f2";
            assert x.g1() == "A.g2";
            assert x.h1() == "A.h2";
            /* All of these are inherited from A */
        }

        /* Testing polymorphism */
        {
            A x = new B();
            assert x.f1() == "B.f2";
            /* Still print's B's because Java is automatically dynamically bound */

            assert x.g1() == "A.g2";
            assert x.h1() == "A.h2";

            /* To be honest I'm not sure what this showed, since g1 and h1 are both A methods anyway */
        }

        System.out.println("Done.");}}
