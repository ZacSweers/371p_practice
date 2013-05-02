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
//          assert(p->h() == "A::h"); // doesn't compile because I guess A can't see its own methods if it's accessing them through B and B has it private?
            }};                       // doesn't compile because we're using private inheritance, and f is protected in A.
                                      // To make it compile, would need p to be an B* const. (i.e. would need "B* const p = this;" on line 33)
/* child of B, doesn't know about A */
class C : public B {
    public:
        void m () {
//          assert(f() == "B::g");    // doesn't compile    /* A is privately inherited, so can't access its inherited method */
            assert(g() == "B::g");                          /* Works because g() is virtually inherited and public in B */
//          assert(h() == "A::h");    // doesn't compile because h() is a protected method only visible by B, and A is private so it doesn't inherit B's protected h()
//          A* const p = this;        // doesn't compile    /* A is privately inherited in B, so C doesn't inherit it by extension */
//          assert(p->f() == "B::g"); // doesn't compile    /* So on and so forth */
//          assert(p->g() == "B::g"); // doesn't compile
//          assert(p->h() == "A::h"); // doesn't compile because h() is a protected method only visible by B, but this is an A* context
            }};

int main () {
    using namespace std;
    cout << "PrivateInheritance.c++" << endl;

    /* For the following lines, pretty much the same reasons as above */

    B x;
//  assert(x.f() == "B::g");  // doesn't compile
    assert(x.g() == "B::g");
//  assert(x.h() == "A::h");  // doesn't compile
//  A* p = &x;                // doesn't compile
//  assert(p->f() == "B::g"); // doesn't compile
//  assert(p->g() == "B::g"); // doesn't compile
//  assert(p->h() == "A::h"); // doesn't compile because h() is a protected method only visible by B, but this is an A* context

    cout << "Done." << endl;
    return 0;}
