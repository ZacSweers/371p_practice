// ---------------------
// MethodOverriding1.c++
// ---------------------

#include <cassert>  // assert
#include <iostream> // cout, endl
#include <string>   // string, ==

struct A {
    std::string f1 (int) {
        return "A::f1";}

    std::string f2 (int) {
        return "A::f2";}

    std::string g1 (int) {
        return "A::g1";}

    std::string g2 (int) {
        return "A::g2";}};

struct B : A {
    /* C++ wants you to specify which parent methods you'll be using */
    using A::f2;
    using A::g2;

    std::string f1 (std::string) {
        return "B::f1";}

    std::string f2 (std::string) {
        return "B::f2";}

    std::string g1 (double) {
        return "B::g1";}

    std::string g2 (double) {
        return "B::g2";}};

int main () {
    using namespace std;
    cout << "MethodOverriding1.c++" << endl;

    /* x is an A object, so calls all the A methods */
    {
    A x;
    assert(x.f1(2)     == "A::f1");
    assert(x.f2(2)     == "A::f2");
    assert(x.g1(2)     == "A::g1");
    assert(x.g2(2)     == "A::g2");
    }


    {
    B x;
//  assert(x.f1(2)     == "A::f1"); // doesn't compile because C++ wants you to explicitly call parent function if you didn't specify you'd use it (lines 24-25)
    assert(x.A::f1(2)  == "A::f1"); /* Calling parent function explicitly */
    assert(x.f1("abc") == "B::f1"); /* Otherwise pass a string and it works fine */

    assert(x.f2(2)     == "A::f2"); /* Works because we specified we'd use A's f2() too */
    assert(x.A::f2(2)  == "A::f2"); /* Calling parent function explicitly */
    assert(x.f2("abc") == "B::f2"); /* But if we pass a string, we'll get B's, as expected */

    assert(x.g1(2)     == "B::g1"); /* Works as expected, upcasts int as a double */
    assert(x.A::g1(2)  == "A::g1"); /* If we explicitly call A, we get A's g1() */
    assert(x.g1(3.45)  == "B::g1"); /* Works as expected if we pass a real double */

    assert(x.g2(2)     == "A::g2"); /* Get A's g2() because it takes an int, better suited, and works because we specified we wanted to use A's g2() in line 25 */
    assert(x.A::g2(2)  == "A::g2"); /* Explicitly call A's g2() */
    assert(x.g2(3.45)  == "B::g2"); /* Works as expected if we pass in a double */
    }

    cout << "Done." << endl;
    return 0;}
