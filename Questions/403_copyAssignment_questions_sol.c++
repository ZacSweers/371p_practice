/**
 * 1. Filles the my_vector _a array with copies of v
 *
 * 2. Blocks the compiler from implicitly calling this constructor
 * 		I didn't really think this example was a good example, here's another from stackoverflow:
 * 			You have a MyString(int size) class with a constructor that constructs a string of the given size. 
 * 		 	You have a function print(MyString &), and you call it with print(3). 
 * 		 	You expect it to print "3", but it prints an empty string of length 3 instead.
 *
 * 		This happens because the compiler implicitly called the int constructor, even though you didn't mean to
 * 		Explicit in front of the MyString(int size) would require you to be explicit to get the empty string of length 3
 * 		AKA:
 * 			print(MyString(3)), instead of just print(3)
 *
 * 3. Copies the contents of the _a array in the input my_vector into our new _a array
 *
 * 4. Swaps the contents of the _a array in the temporary my_vector input into our current _a array
 *
 * 5. Does not take in by reference, does return by reference.
 * 		Takes in by reference because we want to take in a deep copy that will die once the method ends.
 * 		Return by reference because we don't want to return a copy
 * 
 */