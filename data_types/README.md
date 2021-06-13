* data_types *

The files in this folder define the data types that are usable in the program.
The user can create a new data type and use it with the framework provided. As
long as the new Data conforms to the template used by other defined Datas, it
should work perfectly fine. 

A new Data would require:
- A struct to define the Data
- The basic functions:
    - Create
    - Print
    - Compare
    - Free
    - Update (if data needs to be updated)
- An interface that allows a Node to "know" which kind of Data it contains.
