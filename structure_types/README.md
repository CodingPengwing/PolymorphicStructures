* structure_types *

The files in this folder define the structure types that are usable in the program.
The user can create a new structure type and use it with the framework provided. As
long as the new Structure conforms to the template used by other defined Structures,
it should work perfectly fine. 

A new Structure would require:
- A struct to define the Structure
- The basic functions:
    - Create
    - Print
    - Compare
    - Free
    - Update (if Structure needs to be updated)
- An interface that allows a Structure to "know" which kind of structure it contains.

_Future ideas_:
The Structure definition and interface can actually be removed altogether and data structures can just use the Node interface as Datas do. Then there would be no need 
to put a Structure inside a StructureData, before putting it into a Node (as of
current implementation). However, the current implementation creates a distiction 
between Data's and data structures. This is not a necessity for the program to work,
it is just what I've chosen to do.
