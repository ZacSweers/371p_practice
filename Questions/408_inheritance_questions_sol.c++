/**
 * 1. The operators are part of the <Utility> library, and we must define our
 * 		functions to return to their calls.
 *
 * 		i.e.
 * 		Circle x; y;
 * 		x == y;
 * 			actually calls
 * 				bool operator== (x, y);
 * 		 	so we define the result in our class
 *
 * 2. static_cast is used to cast a statically bound object to another object derived from it
 * 		AKA used when you want to force dynamic binding on a method that isn't marked virtual
 *
 * 	  dynamic_cast is used to cast a dynamically bound object to another object derived from it
 * 	  	AKA this one is used though when you specifically need to use the API of the derived object
 * 	  		i.e.
 * 	  			Shape x = new Circle();
 * 	  			need to cast x as a Circle to be able to use radius()
 * 	  	Also can be used as C++'s version of 'instanceof'. Returns 0 if cast isn't possible
 *
 * 3. It does compile, but delete p is illdefined because it doesn't delete the entire Circle object
 *
 * 4. Off in C++, on in Java
 *
 * 5. It would call Shape's
 *
 * 6. No. This would require a Circle(const Shape&) constructor, and you'd lose the value of _r during it
 * 
 */