/**
 * 1. Why do we make friend operations for operators and have them take in two objects?
 * 		For example:
 * 			friend bool operator == (const Shape& lhs, const Shape& rhs) {...}
 * 
 * 2. What's the difference between static_cast and dynamic_cast? When would you use them?
 * 
 * 3. Does the following compile? Is there anything wrong with it?
 * 		Shape*  const p = new Circle(2, 3, 4);
 * 		delete p;
 *
 * 4. Is dynamic binding automatically on or off in C++? In Java?
 *
 * 5. Consider the following snippet:
 *
 * 		const Shape  a[] = {Shape(2, 3), Circle(4, 5, 6)};
 *
 * 	  Would a[1].area() call Shape's area() or Circle's?
 *
 * 6. Using the above snippet, would this compile?
 * 		const Circle c = static_cast<const Circle>(a[1]);
 * 
 */