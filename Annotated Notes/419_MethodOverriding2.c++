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
    /* NOTE that we don't have to specify which ones we want to use since they're virtual */
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

    assert(p->f(2) == "B::f");  /* Get B's because it also takes an int */
    assert(p->g(2) == "A::g");  /* Get A's because its signature is better suited for an int */
    assert(p->h(2) == "A::h");  /* Get A's because its signature is better suited for an int */

    delete p;

    cout << "Done." << endl;
    return 0;}
