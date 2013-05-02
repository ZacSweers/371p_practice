// ---------------------
// PublicInheritance.c++
// ---------------------

/* See private and protected inheritance for more notes, only chance here is in main */

#include <cassert>  // assert
#include <iostream> // cout, endl
#include <string>   // string

class A {
    public:
        std::string f () {
            return g();}

        virtual std::string g () = 0;

    protected:
        std::string h () {
            return "A::h";}};

class B : public A {
    public:
        std::string g () {
            return "B::g";}

        void m () {
            assert(f() == "B::g");
            assert(g() == "B::g");
            assert(h() == "A::h");
            A* const p = this;
            assert(p->f() == "B::g");
            assert(p->g() == "B::g");
         // assert(p->h() == "A::h"); // doesn't compile because h() is a protected method only visible by B, but this is an A* context
            }};

class C : public B {
    public:
        void m () {
            assert(f() == "B::g");
            assert(g() == "B::g");
            assert(h() == "A::h");  // This does compile though because C inherits B's protected methods
            A* const p = this;
            assert(p->f() == "B::g");
            assert(p->g() == "B::g");
//          assert(p->h() == "A::h"); // doesn't compile because h() is a protected method only visible by B, but this is an A* context
            }};

int main () {
    using namespace std;
    cout << "PublicInheritance.c++" << endl;

    /* these (except A::h) work now because B is publically derived from A, aka everyone can know about it */
    B x;
    assert(x.f() == "B::g");
    assert(x.g() == "B::g");
//  assert(x.h() == "A::h");  // doesn't compile because h() is a protected method only visible by B, but this is an A* context and outside of a B
    A* p = &x;
    assert(p->f() == "B::g");
    assert(p->g() == "B::g");
//  assert(p->h() == "A::h"); // doesn't compile because h() is a protected method only visible by B, but this is an A* context

    cout << "Done." << endl;
    return 0;}
