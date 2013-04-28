// ------------------
// CopyAssignment.c++
// ------------------

#include <algorithm> // copy, equal, fill, swap
#include <cassert>   // assert
#include <cstddef>   // size_t
#include <iostream>  // cout, endl
#include <iterator>  // distance

template <typename T>
class my_vector {
    private:
        std::size_t _s; /* Size */
        T*          _a; /* Pointer to array of T */

    public:

        /**
         * Constructor that takes in size and a T
         * If no T is provied, creates a default T
         * If a T is provided, it fills the array with copies of it
         * Note the _s and _a are initialized in initializer block
         * Explicit blocks the compiler from implicitly calling this
         */
        explicit my_vector (std::size_t s, const T& v = T()) :
                _s (s),
                _a (new T[_s]) {
            /* Fills _a with copies of v */
            std::fill(begin(), end(), v);}

        /**
         * Copy constructor
         * Again note the initializer block
         */
        my_vector (const my_vector& that) :
                _s (that._s),
                _a (new T[_s]) {
            /* Copies contents of "that"'s array into ours */
            std::copy(that.begin(), that.end(), begin());}


        /**
         * Operator= method
         * Takes in a my_vector (but not by reference!)
         *     This means it takes in a copy of "that", which subsequently dies at the end of this method
         */
        my_vector& operator = (my_vector that) {
            /* Since 'that' is a temporary copy, swaps our contents with it before it dies */
            std::swap(_s, that._s);
            std::swap(_a, that._a);

            /* Then return ourselves, by REFERENCE */
            /* This is a big deal. My partner and I wasted abour 3 hours on Life because we were accidentally recieving copies */
            return *this;}

        ~my_vector () {
            delete [] _a;}

        /* begin() function, like Vector does. Returns pointer to first index of _a */
        T* begin () {
            return _a;}

        /* const version of begin, returns a const pointer */
        const T* begin () const {
            return _a;}

        /* end() function, like Vector does. Returns a pointer to the last address of _a */
        T* end () {
            return _a + _s;}

        const T* end () const {
            return _a + _s;}

        /* Size getter (oh no he didn't!) */
        std::size_t size () const {
            return _s;}};

int main () {
    using namespace std;
    cout << "CopyAssignment.c++" << endl;

    {
        /* Created a my_vector, size 10 and T(2) */
        const my_vector<int> x(10, 2);

        /* Creates a copy */
        const my_vector<int> y = x;

        /* Confirms copy constructor worked correctly */
        assert(equal(x.begin(), x.end(), y.begin()) == true);
    }

    {
        /* Creates two vectors, y is const */
              my_vector<int> x(10, 2);
        const my_vector<int> y(20, 3);

        /* Calls operator= method */
        x = y;
        // y = x;   // Doesn't compile because y is const

        /* Confirms operator= worked */
        assert(equal(x.begin(), x.end(), y.begin()) == true);
    }

    cout << "Done." << endl;
    return 0;}
