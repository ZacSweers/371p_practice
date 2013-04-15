/**
 * 1. In the clone() method we create the following. What is it doing and what is it final?
 * 		
 * 		final MyArrayList<T> that = (MyArrayList<T>) super.clone();
 *
 * 2. What must the MyArrayList class implement to use clone() and why?
 *
 * 3. What's the benefit of using the "final" keyword in Java? Specifically, when making a tmp copy of a variable?
 *
 * 4. What's required to make an entire object immutable in Java?
 * 		- This might seem random but we felt like it's a question Downing would ask
 *
 * 5. Is the following assertion true?
 *
 * 		{
 * 		final MyArrayList<String> x = new MyArrayList<String>(3);
 *      x.add(0, "abc");
 *      x.add(1, "def");
 *      x.add(2, "ghi");
 *
 *      final MyArrayList<String> y = (MyArrayList<String>) x.clone();   // warning: unchecked cast
 *
 *      assert x != y;
 *
 * 		// This assertion
 *      assert x.a[0] == y.a[0];
 *      }
 */