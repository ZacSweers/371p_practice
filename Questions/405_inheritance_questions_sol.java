/**
 * 1. No. ArrayLists in java just don't allow that (forgive the lame explanation). You could make an ArrayList
 * 		of Shapes though, and then add Circles to that list.
 * 		
 * 2. a[0] would call Shape's, and a[1] would call Circle's, because Java handles it all for us.
 * 		In C++, a[0] would work, but a[1] wouldn't. Explanation in DynamicBinding.c++
 * 
 * 3. Final makes the method not extendable (AKA you couldn't override it in a derived class)
 * 		C++ equivelant would be to NOT mark the method as virtual
 * 
 * 4. It requires an Object because you're overriding Object's equals() method (because all objects in Java inherit from Object)
 * 
 * 5. super.equals(rhs)
 * 
 */