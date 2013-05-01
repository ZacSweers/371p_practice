// --------------
// Singleton.java
// --------------

interface A {
    String f ();}

class B implements A {
    public static final B only = new B();

    private B ()
        {}

    public String f () {
        return "B.f()";}}

class C implements A {
    private static C _only;

    private C ()
        {}

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
