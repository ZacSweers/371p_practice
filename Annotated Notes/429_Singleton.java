// --------------
// Singleton.java
// --------------

/* See the singleton.c++ notes for indepth explanation. Only change here is the "only" initialization at line 11 and only() method at line 25 */

interface A {
    String f ();}

class B implements A {
    /* No initializing outside of the class, initialized just inside of the class */
    public static final B only = new B();

    private B ()
        {}

    public String f () {
        return "B.f()";}}

class C implements A {
    private static C _only;

    private C ()
        {}

    /* This is different in java, has to check to see if _only was initialized already. In java, static local variables can only be initialized
        ouside of the static method */
    public static C only () {
        if (C._only == null)
            C._only = new C();
        return C._only;}

    public String f () {
        return "C.f()";}}

final class Singleton {
    public static void g (A x) {
        assert x.f().substring(1) !=     ".f()";
        assert x.f().substring(1).equals(".f()");}

    public static void main (String[] args) {
        System.out.println("Singleton.java");

        assert B.only     == B.only;
        assert B.only.f() == "B.f()";
        g(B.only);

        assert C.only()     == C.only();
        assert C.only().f() == "C.f()";
        g(C.only());

        System.out.println("Done.");}}
