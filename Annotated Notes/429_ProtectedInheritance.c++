// ------------------------
// ProtectedInheritance.c++
// ------------------------

#include <cassert>  // assert
#include <iostream> // cout, endl
#include <string>   // string

/* A class */
class A {
    public:
        std::string f () {
            return g();}

        virtual std::string g () = 0;

    protected:
        std::string h () {
            return "A::h";}};

/* B class protectedly inheriting A. B's children can know about A, but no one else */
class B : protected A {
    public:
        std::string g () {
            return "B::g";}

        /* These all for the most part work because B knows about A and inherits its methods */
        void m () {
            assert(f() == "B::g");
            assert(g() == "B::g");
            assert(h() == "A::h");
            A* const p = this;
            assert(p->f() == "B::g");
            assert(p->g() == "B::g");
//          assert(p->h() == "A::h"); // doesn't compile because h() is a protected method only visible by B
            }};

class C : public B {

    /* These work (as opposed to in private inheritance) because B's children can also know about A */
    public:
        void m () {
            assert(f() == "B::g");
            assert(g() == "B::g");
            assert(h() == "A::h");
            A* const p = this;
            assert(p->f() == "B::g");
            assert(p->g() == "B::g");
//          assert(p->h() == "A::h"); // doesn't compile
            }};

int main () {
    using namespace std;
    cout << "ProtectedInheritance.c++" << endl;

    /* These still don't work because only B's children can know about A */
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
