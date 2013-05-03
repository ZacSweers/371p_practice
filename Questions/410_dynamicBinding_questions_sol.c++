/**
* Dynamic Binding Questions
* =========================
* 1. Can you inline a virtual method in C++?
* A: Yes. 
*
* 2. What are the 4 situations in which you can inline a virtual method?
* A: You can inline a virtual method if you:
*     1. Invoke it on an object
*     2. Invoke it by saying the class name explicitly
*     3. Invoke it in a constructor
*     4. Invoke it in a destructor
*
* 3. If you invoke a virtual method on an object, which type of binding always occurs?
* A: Static.
*
* 4. If you invoke a virtual method explicitly stating the name of the class, such as calling Animal::run(),
* which type of binding always occurs?
* A: Static
*
* 5. In which two methods is dynamic binding always turned off?
* A: Constructor and Destructor.
*
* 6. In C++, how do you enable dynamic binding?
* A: By declaring something "virtual". 
*/

