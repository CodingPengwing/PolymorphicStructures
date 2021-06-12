# Polymorphic Structures in C #

This library was inspired by [Chris Wood's post](https://chris-wood.github.io/2016/02/12/Polymorphism-in-C.html)
on polymorphism in C:

_(Test instructions at the bottom)_

_Introduction_:  
This is a library of polymorphic components. I took upon myself the challenge of 
creating polymorphism in a non-object-oriented (and infamously hedious) language in
order to understand how polymorphism works under the hood. The polymorphism in this 
implementation is the "is-a" type of polymorphism (inheritance). Specifically, 
polymorphism is achieved through the use of interfaces held by objects, where each 
interface contains function pointers that define the behaviour of that object. 
Interfaces are created specifically for each new data type. This is an example of 
static (or compile-time) polymorphism.

_Note_:  
The polymorphism achieved in the current implementation can be pushed one step further 
with the use of vtables and the addition of "has-a" polymorphism (composition); which 
would introduce another layer of indirection, and would bring the implementation very 
close to what actually happens under the hood for polymorphism in C++ and Java. This
would be an example of dynamic (or runtime) polymorphism.

_Example of current implementation_:  
A Node contains a Data, the Data *is a* IntData. The Node can then be put into a 
structure like a linked list or an array (or others). It gets more exciting when a Data 
can be more than just primitive types, it can also *be* a Structure; eg. a Data can be a
LinkedList. This means that a Node can contain a LinkedList as its Data, and that same 
Node can belong to an Array or another LinkedList. (Data can literally be anything as 
long as the user creates a proper interface for the type of Data they want to use, 
following on from templates of other defined Datas like TupleData or StringData.)

Eg. 
- LinkedList1 = A->B->C (where A, B, C are Nodes)
- Node A is a IntData, A.data = 4
- Node B is a StringData, B.data = "blaze"
- Node C is a StructureData, C.data = [2, 0, "it"] (an array with more Nodes inside).

Thus, when we print LinkedList1, we get:  [4->blaze->[2, 0, it]]

_Node vs Data?_  
The Node was created so that it could be included in any kind of structure, eg. a
linked list or an array. All logic related to Node could have been associated with Data 
instead, and Node would no longer be needed in the program. However, this abstraction 
aims to separate the responsibilities of a Node - objects that make up a data structure - 
and a Data - the actual information held at each Node (or each location in the structure). 
This separation improves the adaptability and maintainability of the program, and helps 
with the goal of polymorphism in Data.

_Other potential data structures_:  
As of current, the code only supports two data structures: linked lists and arrays.
However, the code is modular enough that any data structure from the 
[SimpleDataStructures](https://github.com/CodingPengwing/SimpleDataStructures)
libraries or other libraries can be adapted, given a proper interface is created for it 
(following on from the given templates of LinkedList or Array) and the data structure is
altered to contain Nodes at each of its positions (for the purpose of nesting data). 
But for the main goal of achieving polymorphism, I've happily stopped at the current 
two data structures.

**Test instructions**

-> Refer to main.c for 5 base test cases.  
To test this code, go to terminal, clone this directory, navigate to the top folder and 
run this command:
- make tester  
This should compile, execute main and clean up all executables.
If this doesn't work, run these commands:
- make test
- make run_test
- make clean  
Which will compile, then execute main, then clean up.

-> Refer to sample.c for the sample code provided in Chris Wood's post.  
To test sample code:
- make sample
- make clean

This should compile and execute sample.c. Clean up using 2nd line.
