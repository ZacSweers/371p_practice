// ----------------------
// PrivateInheritance.c++
// ----------------------

#include <cassert>  // assert
#include <iostream> // cout, endl
#include <string>   // string

/* abstract parent class */
class A {
    public:
        /* f() function that calls g(), AKA should always return B::g since g() is pure virtual */
        std::string f () {
            return g();}

        /* Pure virtual  g()*/
        virtual std::string g () = 0;

    protected:
        std::string h () {
            return "A::h";}};

/* child class privately inheriting A. Only it may access A's methods, B's children can't know about A */
class B : private A {
    public:
        std::string g () {
            return "B::g";}

        void m () {
            assert(f() == "B::g");  /* Inherited f(), calls B's g() */
            assert(g() == "B::g");  /* Virtual, calls B's g() */
            assert(h() == "A::h");  /* Inherited, calls A's h() */
            A* const p = this;      /* Now we have a pointer, which a pointer is a different class than B */
            assert(p->f() == "B::g");   /* This works because we're still in B */
            assert(p->g() == "B::g");   /* Works because we're still in B  */
//          assert(p->h() == "A::h"); // doesn't compile because while we're still in B, p is an A object, so it can't (via B) access h()?
            }};

/* child of B, doesn't know about A */
class C : public B {
    public:
        void m () {
//          assert(f() == "B::g");    // doesn't compile    /* A is privately inherited, so can't access its inherited method */
            assert(g() == "B::g");                          /* Works because g() is virtually inherited and public in B */
//          assert(h() == "A::h");    // doesn't compile    /* A is privately inherited, and h() is protected, so can't access its inherited method */
//          A* const p = this;        // doesn't compile    /* A is privately inherited in B, so C doesn't inherit it by extension */
//          assert(p->f() == "B::g"); // doesn't compile    /* So on and so forth */
//          assert(p->g() == "B::g"); // doesn't compile
//          assert(p->h() == "A::h"); // doesn't compile
            }};

int main () {
    using namespace std;
    cout << "PrivateInheritance.c++" << endl;

    /* For the following lines, pretty much the same reasons as above except */

    B x;
//  assert(x.f() == "B::g");  // doesn't compile
    assert(x.g() == "B::g");
//  assert(x.h() == "A::h");  // doesn't compile
//  A* p = &x;                // doesn't compile
//  assert(p->f() == "B::g"); // doesn't compile
//  assert(p->g() == "B::g"); // doesn't compile
//  assert(p->h() == "A::h"); // doesn't compile

    cout << "Done." << endl;
    return 0;}
