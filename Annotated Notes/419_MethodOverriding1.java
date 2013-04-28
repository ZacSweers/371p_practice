// ----------------------
// MethodOverriding1.java
// ----------------------

/* Java assumes you want access to all the parent class's method, while C++ wants you to specify which ones */

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

        assert x.f(3)     == "A.f"; /* Passed an int, so we get A's */
        assert x.f("abc") == "B.f"; /* Passed a string, so we get B's */

        assert x.g(3)     == "A.g"; /* Passed an int, so we get A's */
        assert x.g(5.67)  == "B.g"; /* Passed a double, so we get B's */

        System.out.println("Done.");}}
