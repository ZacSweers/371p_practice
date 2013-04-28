/**
 * 1. No. Shape y = x calls the copy constructor, which in turn eventually calls x's _p's clone() method
 *
 * 2. Pointer constructor
 *
 * 3. Operator=, and yes, they point to the same object after because swap makes y's _p the same as x's
 *
 * 4. 
 * 		Shape (AbstractShape* p) :
 *          Handle<AbstractShape> (p)
 *      {}
 *
 * 5. Copy constructor, destructor, operator=
 *
 * 
 */