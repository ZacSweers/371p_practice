// -------------
// Singleton.c++
// -------------

#include <cassert>  // assert
#include <iostream> // cout, endl
#include <string>   // string, substr

using namespace std;

struct A {
    virtual std::string f () const = 0;};

class B : public A {
    public:
        static B only;

    private:
        B ()
            {}

        B (const B&);

    public:
        std::string f () const {
            return "B::f()";}};

B B::only;

class C : public A {
    public:
        static C& only () {
            static C x;
            return x;}

    private:
        C ()
            {}

        C (const C&);

    public:
        std::string f () const {
            return "C::f()";}};

void g (const A& x) {
    assert(x.f().substr(1, 5) == "::f()");}

int main () {
    cout << "Singleton.c++" << endl;

    assert(&B::only    == &B::only);
    assert(B::only.f() == "B::f()");
    g(B::only);

    assert(&C::only()    == &C::only());
    assert(C::only().f() == "C::f()");
    g(C::only());

    cout << "Done." << endl;
    return 0;}
