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

    {
    A x;
    assert(x.f1(2)     == "A::f1");
    assert(x.f2(2)     == "A::f2");
    assert(x.g1(2)     == "A::g1");
    assert(x.g2(2)     == "A::g2");
    }

    {
    B x;
//  assert(x.f1(2)     == "A::f1"); // doesn't compile
    assert(x.A::f1(2)  == "A::f1");
    assert(x.f1("abc") == "B::f1");

    assert(x.f2(2)     == "A::f2");
    assert(x.A::f2(2)  == "A::f2");
    assert(x.f2("abc") == "B::f2");

    assert(x.g1(2)     == "B::g1");
    assert(x.A::g1(2)  == "A::g1");
    assert(x.g1(3.45)  == "B::g1");

    assert(x.g2(2)     == "A::g2");
    assert(x.A::g2(2)  == "A::g2");
    assert(x.g2(3.45)  == "B::g2");
    }

    cout << "Done." << endl;
    return 0;}
