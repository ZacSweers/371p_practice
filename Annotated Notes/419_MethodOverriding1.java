// ----------------------
// MethodOverriding1.java
// ----------------------

class A {
    public String f (int i) {
        return "A.f";}

    public String g (int i) {
        return "A.g";}}

class B extends A {
    public String f (String s) {
        return "B.f";}

    public String g (double d) {
        return "B.g";}}

final class MethodOverriding1 {
    public static void main (String[] args) {
        System.out.println("MethodOverriding1.java");

        B x = new B();

        assert x.f(3)     == "A.f";
        assert x.f("abc") == "B.f";

        assert x.g(3)     == "A.g";
        assert x.g(5.67)  == "B.g";

        System.out.println("Done.");}}
