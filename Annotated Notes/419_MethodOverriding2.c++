// ---------------------
// MethodOverriding2.c++
// ---------------------

#include <cassert>  // assert
#include <iostream> // cout, endl
#include <string>   // string, ==

struct A {
    virtual ~A() {}

    virtual std::string f (int) {
        return "A::f";}

    virtual std::string g (int) {
        return "A::g";}

    virtual std::string h (int) {
        return "A::h";}};

struct B : A {
    virtual std::string f (int) {
        return "B::f";}

    virtual std::string g (double) {
        return "B::g";}

    virtual std::string h (int) const {
        return "B::h";}};

int main () {
    using namespace std;
    cout << "MethodOverriding2.c++" << endl;

    A* const p = new B();

    assert(p->f(2) == "B::f");
    assert(p->g(2) == "A::g");
    assert(p->h(2) == "A::h");

    delete p;

    cout << "Done." << endl;
    return 0;}
