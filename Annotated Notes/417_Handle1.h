// ---------
// Handle1.h
// ---------

#ifndef Handle1_h
#define Handle1_h

#include <algorithm> // swap

template <typename T>
class Handle {
    friend bool operator == (const Handle& lhs, const Handle& rhs) {
        return (!lhs._p && !rhs._p) || (*lhs._p == *rhs._p);}

    friend bool operator != (const Handle& lhs, const Handle& rhs) {
        return !(lhs == rhs);}

    public:
        typedef T                 value_type;

        typedef value_type*       pointer;
        typedef const value_type* const_pointer;

        typedef value_type&       reference;
        typedef const value_type& const_reference;

    private:
        /* Pointer to object we're currently using */
        pointer _p;

    protected:

        /* Getters */
        pointer get () {
            return _p;}

        const_pointer get () const {
            return _p;}

    public:
        /* Pointer constructor */
        Handle (pointer p) {
            _p = p;}

        /* Copy constructor */
        Handle (const Handle& that) {
            /* Sanity check, make sure it's not the same object */
            if (!that._p)
                _p = 0;
            /* Set our _p to a clone of that's _p */
            else
                _p = that._p->clone();}

        ~Handle () {
            delete _p;}

        /* Operator=. Take in a tmp copy, swap contents, return this by reference */
        Handle& operator = (Handle that) {
            swap(that);
            return *this;}

        /* Swap function, takes in by reference and swaps _p values */
        /* By reference because we're using the "that" temp from operator= above */
        void swap (Handle& that) {
            std::swap(_p, that._p);}};

#endif // Handle1_h
