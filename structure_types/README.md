# structure_types #

The files in this folder define the structure types that are usable in the program.
The user can create a new structure type and use it with the framework provided. As
long as the new Structure conforms to the template used by other defined Structures,
it should work perfectly fine. 

A new Structure would require:
- A struct to define the Structure
- The basic functions:
    - Create
    - Print
    - Free
- An interface that allows a Node to "know" which kind of structure it contains.

