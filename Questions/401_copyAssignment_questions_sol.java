/**
 * 1.	Calls the Object clone() method to create a new (but empty) MyArrayList 
 * 		object. Final means that we cannot reassign the "that" variable to 
 * 		something else after declaration (see notes annotation)
 * 
 * 2.	MyArrayList must implement Cloneable. In order to use the Object clone()
 * 		interface, the object calling it must implement Cloneable.
 * 		
 * 		(From StackOverflow)
 * 			"The Java Object class does not extend the Cloneable interface. 
 * 			It does however have the clone() method. But this method is 
 * 			protected and will throw an exception if called on an object that 
 * 			does not implement the Cloneable interface. So if you cannot modify 
 * 			the class you want to clone you're out of luck and will have to find
 * 			 another way to copy the instance."
 *
 * 3. 	Means you cannot change what that variable points to (the reference), 
 * 		equivelant to having a const pointer to a non-const object (i.e. you 
 * 		can still mutate its non-final attributes). Use with a temp variable 
 * 		copy would be to ensure that it doesn't get reassigned later; it's good
 * 		practice and makes debugging easier since you know it's not changing.
 *
 * 4.	Make the class final, don't provide setter methods, make all fields 
 * 		final/private, and mark any regularly mutable objects (say, an int) as 
 * 		final.
 *
 * 		Example - 
 *
 * 			final public class someImmutable {
 * 				final private int someAttribute;
 * 			}
 *
 * 5.	Yes. Java caches strings, so while we've created a clone of the 
 * 		ArrayList object, its array still points to the same String references
 */