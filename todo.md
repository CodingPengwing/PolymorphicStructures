- Introduce vtables  
    - Goal: introduce another layer of indirection, complete the polymorphic behaviour.
    - Potential: make use of macros  
    
- Create a "factory" file for Nodes  
    - Goal: remove direct dependency between main classes and Data types.
    - Problem: this is a great idea for concrete Datas, but might introduce difficulties for 
    data structures
    - Potential: make use of macros to configure different types of Nodes automatically

