// ---------
// Handle2.h
// ---------

#ifndef Handle2_h
#define Handle2_h

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
        pointer _p;

    public:
        Handle (pointer p) {
            _p = p;}

        Handle (const Handle& that) {
            if (!that._p)
                _p = 0;
            else
                _p = that._p->clone();}

        ~Handle () {
            delete _p;}

        Handle& operator = (Handle that) {
            swap(that);
            return *this;}

        reference operator * () {
            return *_p;}

        const_reference operator * () const {
            return *_p;}

        pointer operator -> () {
            return _p;}

        const_pointer operator -> () const {
            return _p;}

        void swap (Handle& that) {
            std::swap(_p, that._p);}};

#endif // Handle2_h
