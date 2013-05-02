// -------------
// Singleton.c++
// -------------

#include <cassert>  // assert
#include <iostream> // cout, endl
#include <string>   // string, substr

using namespace std;

/**
 * NOTE: Remember that with Singletons, the only instance of that class exists solely within the class itself, and can't be
 * instantiated elsewhere. Singletons are all stored on the heap by the compiler. Must be called via the class (AKA SingletonClass::<methods>(...))
 * 
 * Singleton classes allow us to implement interfaces without inheriting from them (perk of this over having a static class)
 *     Static classes also have all their members as static, while singletons do not
 *     Singletons can be lazily loaded
 *     Singles go on the heap but static objects go on the stack
 *     We can clone singletons, not static classes
 *     Singletons can use polymorphism, static classes can't
 *
 * Some uses of singletons:
 *     Hardware interface access (to avoid concurrent accessess, avoiding deadlocks)
 *     Loggers
 *     Config files
 *     Caches (make a cache a singleton object, suddenly it's global for any call to the cache)
 */


/* Abstract class A with a pure virtual function f() */
struct A {
    virtual std::string f () const = 0;};

/**
 * Class B derived from A
 * This one has a public class attribute of B called only
 * Remember the constructors are private, so we can't build instances of them
 */
class B : public A {
    public:
        static B only;  /* our static B variable */

    private:
        /* Default constructor is private */
        B ()
            {}
        /* Copy constructor, doesn't do anything though, also private */
        B (const B&);

    public:
        /* Defined virtual f() function inherited from A */
        std::string f () const {
            return "B::f()";}};

/* B initialization outside of class B, because it doesn't technically exist in class B*/
/* Think of it this way. only belongs to the class B, not to objects of B. This allows us to reference "only" by name rather than through an object */
            /* This is the standard way to access static member variables in C++ */
B B::only;

/**
 * C class inheriting from A
 * This one has public only() method that gets initialized at compilation
 * And just returns itself every time after.
 * Remember the constructors are private, so we can't build instances of them
 */
class C : public A {
    public:
        /* static only() call */
        /* remember x is local, but because it's static, each method call uses the same x variable */
        /* the method is also static so that multiple instances of C, the same exact method (and by extension, its same local static x variable) are used */
        static C& only () {
            static C x; /* initializes if x doesn't already exist */
            return x;}

    /* like in B, constructors are private */
    private:
        C ()
            {}

        C (const C&);

    public:
        std::string f () const {
            return "C::f()";}};

/* Function that asserts that it's polymorphically calling B or C's inherited f() */
void g (const A& x) {
    assert(x.f().substr(1, 5) == "::f()");}

int main () {
    cout << "Singleton.c++" << endl;

    /* The compiler generates it already, confirms that each call returns the same object */
    assert(&B::only    == &B::only);

    /* Confirms that it virtually inherited correctly */
    assert(B::only.f() == "B::f()");
    g(B::only);

    /* Compiler generates it already and confirms each call to static method only() returns the same static x in it */
    assert(&C::only()    == &C::only());
    assert(C::only().f() == "C::f()");
    g(C::only());

    cout << "Done." << endl;
    return 0;}
