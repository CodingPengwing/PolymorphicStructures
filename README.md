# Polymorphic Structures in C #

This library was inspired by [Chris Wood's post](https://chris-wood.github.io/2016/02/12/Polymorphism-in-C.html)
on polymorphism in C:

_(Test instructions at the bottom)_

This is a library of polymorphic components. I took upon myself the challenge of 
creating polymorphism in a non-object-oriented (and infamously hedious) language in
order to understand how polymorphism works under the hood. The polymorphism in this 
implementation is the "is-a" type of polymorphism. Specifically, polymorphism is 
achieved through the use of interfaces held by objects, where each interface contains 
function pointers that define the behaviour of that object. Interfaces are created
specifically for each new data type.

_Note_:  
The polymorphism achieved in this implementation can be pushed one step further, 
with the use of vtables, and the addition of "has-a" polymorphism, which would 
introduce another layer of indirection, and would bring the implementation very close
to what happens under the hood for polymorphism in C++ and Java. However, the current 
state of this library only uses references to function pointers held by objects.

_Example of current implementation_:  
A Node contains a Data, the Data *is a* IntData. The Node can then be put into a
structure like a linked list or an array (or others). It gets more exciting when a 
Data can be more than just primitive types, it can also *be* a Structure; eg. a Data 
can be a LinkedList. This means that a Node can contain a linked list as its Data,
and that same Node can belong to an Array or another LinkedList. (Data can literally
be anything as long as the user creates proper files for that Data that follows the
template given with other defined Data files like TupleData or StringData.)

Eg. 
- LinkedList1 = A->B->C (where A, B, C are Nodes)
- Node A is a IntData, A.data = 4
- Node B is a StringData, B.data = "blaze"
- Node C is a StructureData, C.data = [2, 0, "it"] (an array with more Nodes inside).

Thus, when we print LinkedList1, we get:  [4->blaze->[2, 0, it]]

(Node vs Data? - The Node was created so that it could be included in any kind of
structure, eg. a linked list or an array. All logic related to Node could have been 
associated with Data instead, and Node would no longer be needed in the program. 
However, this abstraction aims to separate the responsibilities of a Node - objects 
that make up a data structure - and a Data - the actual information held at each 
node (or each location in the structure). This separation improves the maintainability
of the program, and helps with the goal of polymorphism in Data.)

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
