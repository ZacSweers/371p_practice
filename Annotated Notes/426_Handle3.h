// ---------
// Handle3.h
// ---------

#ifndef Handle3_h
#define Handle3_h

#include <algorithm> // swap
#include <cassert>   // assert
#include <cstddef>   // size_t

template <typename T>
class Handle {
    friend bool operator == (const Handle& lhs, const Handle& rhs) {
        return *lhs._p->_q == *rhs._p->_q;}

    friend bool operator != (const Handle& lhs, const Handle& rhs) {
        return !(lhs == rhs);}

    public:
        typedef T                 value_type;

        typedef value_type*       pointer;
        typedef const value_type* const_pointer;

        typedef value_type&       reference;
        typedef const value_type& const_reference;

    private:
        /* Reference count, keeps track of how often this Handle is used */
        /* This is from our discussion about inner classes */
        /* Instead of a _p,  */
        struct count {
            std::size_t _c; /* Count */
            pointer     _q; /* This is essentially our _p now, held in a count object now */

            /* Count constructor, takes in a _q and sets count to 1 */
            /* Note again that an initializer block is used */
            count (pointer q) :
                    _c (1),
                    _q (q) {
                assert(_q);}

            ~count () {
                assert(!_c);    /* Sanity check, makes sure count is now 0 */
                delete _q;}};

        count* _p;  /* Attribute of Handle3, pointer to a count object, which in turn holds a pointer to a "pointer" pointer */

    protected:
        /* get() comes back into play */
        pointer get () {
            /* Unique is true if RC == 1 */
            if (!unique()) {
                /* RC must be greater than 1, so decrement */
                --_p->_c;
                /* Make a new copy of what count was pointing to */
                _p = new count(_p->_q->clone());}
            return _p->_q;}

        /* Const, so nnothing changes, Just return the _q */
        const_pointer get () const {
            return _p->_q;}

    public:

        /* Now handle makes a new count, not just set _p = p like before */
        Handle (pointer q) {
            _p = new count(q);}

        /* Copy constructor */
        Handle (const Handle& that) {
            /* Checks to make sure it's not the same object */
            if (!that._p)
                _p = 0;
            else {
                /* Set it to the same count object */
                _p = that._p;
                /* increment the count, because now two objects point to it */
                ++_p->_c;}}

        /* Destructor. Decrements the count. if it's now 0, deletes _p entirely */
        ~Handle () {
            if (!--_p->_c)
                delete _p;}

        /* Swap works the same way, just swaps the pointer values */
            /* See Handle1 for in depth explanation */
        Handle& operator = (Handle that) {
            swap(that);
            return *this;}

        void swap (Handle& that) {
            std::swap(_p, that._p);}

        /* Auxiliary function used by get() */
        bool unique () const {
            return use_count() == 1;}

        /* Getter that just returns the RC */
        int use_count () const {
            return _p->_c;}};

#endif // Handle3_h
