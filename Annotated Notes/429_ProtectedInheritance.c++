// ------------------------
// ProtectedInheritance.c++
// ------------------------

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

class B : protected A {
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
//          assert(p->h() == "A::h"); // doesn't compile
            }};

class C : public B {
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
