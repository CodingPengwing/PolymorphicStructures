
#include "Node.h"
#include "Structure.h"

#include "data_types/IntData.h"
#include "data_types/StringData.h"
#include "data_types/StructureData.h"
#include "data_types/FloatData.h"
#include "data_types/TupleData.h"

#include "structure_types/Array.h"
#include "structure_types/List.h"

/*  ATTENTION: input infrastructure has not yet been created for this program,
    therefore all test cases have been hardcoded into this file. The user can
    look at each test case to see how different types of Data can be created.

    Test 1: to test that a polymorphic array works
    Test 2: to test that nesting arrays inside one another works
    Test 3: to test that a polymorphic linked list works
    Test 4: to test that nesting lists inside one another works
    Test 5: to test that nesting a list inside an array works
    Test 6: to test that nesting multiple depth levels works (nesting depth of 8)
 */

// The test cases:
void test_array_1(); // Test 1
void test_array_2(); // Test 2
void test_list_1(); // Test 3
void test_list_2(); // Test 4
void test_both(); // Test 5
void test_crazy_nested(); // Test 6

// Some test values
char *string_samples[] = {"puppy", "corgi", "doge", "chonk", "shiba", "hooman", "bulldog", "husky", "kitty", "pug"};
size_t test_size = 10;

int main(int argc, char const *argv[])
{
    // TEST 6 SCENARIOS
    println("--- DOING TEST 1: testing polymorphic array");
    test_array_1();
    println("--- \n");
    println("--- DOING TEST 2: testing nested arrays");
    test_array_2();
    println("--- \n");
    println("--- DOING TEST 3: testing polymorphic linked list");
    test_list_1();
    println("--- \n");
    println("--- DOING TEST 4: testing nested linked lists");
    test_list_2();
    println("--- \n");
    println("--- DOING TEST 5: testing nested lists and arrays");
    test_both();
    println("--- \n");
    println("--- DOING TEST 6: testing a crazy amount of nesting");
    test_crazy_nested();
    println("--- \n");

    return 0;
}


// Doing our test number 1, these arrays only contain simple data like ints or strings (ie... both hehe).
// This test is for testing polymorphic arrays.
void test_array_1()
{
    size_t array_size = test_size;
    // Here is our array, initially malloced to array_size but empty
    Array_t *array = array_Create(array_size);

    // Let's get some values into our array
    for (size_t i = 0; i < array_size/3; i++)
    {
        // Filling ints
        IntData_t *intData = intData_Create(i);
        Node_t *intNode = node_Create(intData, NodeInterface_IntData);
        array_Insert(array, intNode, i);
        // Filling strings
        StringData_t *stringData = stringData_Create(string_samples[i+3]);
        Node_t *stringNode = node_Create(stringData, NodeInterface_StringData);
        array_Insert(array, stringNode, i+3);
        // Filling floats
        FloatData_t *floatData = floatData_Create(3.1415);
        Node_t *floatNode = node_Create(floatData, NodeInterface_FloatData);
        array_Insert(array, floatNode, i+6);
    }
    // Notice how we left the last index empty, only filled indices 0->8
    
    // Make a structures to hold this array
    Structure_t *structure_1 = structure_Create(array, StructureInterface_Array);

    // Can only sort if data type is the same, we have different types of Data in here
    // so sorting wouldn't work.
    //structure_Sort(structure_1);

    // Let's see what we got. It shuold be an Array with random values in it and an empty slot
    // at the end.
    structure_Print(structure_1);
    println("");;

    // Freedom is fundamental. Recursively free our objects.
    structure_Free(structure_1);
    array = NULL;
    structure_1 = NULL;
}



// 2nd test incoming! This one is not for the faint-hearted...
// We're going to make the same array as test 1, however, we're going to put that inside another array.
// This test is for testing nested arrays.
void test_array_2()
{   
    // This first half is the same as test 1, just creating an array
    /*-----------------------------------------------------------------------------*/
    size_t array_size = test_size;

    // Here are our arrays, initially malloced to array_size but empty
    Array_t *array = array_Create(array_size);
    Array_t *string_array = array_Create(array_size);
    // Let's get some values into our arrays structures
    for (size_t i = 0; i < array_size; i++)
    {
        // Filling out the int array in reverse
        IntData_t *intData = intData_Create(array_size - i - 1);
        Node_t *intNode = node_Create(intData, NodeInterface_IntData);

        array_Insert(array, intNode, i);

        // Filling out the string array
        StringData_t *stringData = stringData_Create(string_samples[i]);
        Node_t *stringNode = node_Create(stringData, NodeInterface_StringData);
        array_Insert(string_array, stringNode, i);
    }
    
    // Make some structures to hold these arrays
    Structure_t *structure_1 = structure_Create(array, StructureInterface_Array);
    Structure_t *structure_2 = structure_Create(string_array, StructureInterface_Array);

    // NEW CONTENT
    /*-----------------------------------------------------------------------------*/

    // Here's the fun part, let's nest our structures in one another

    // Encapsulate the previous structures inside pieces of Datas
    StructureData_t *structureData_1 = structureData_Create(structure_1);
    StructureData_t *structureData_2 = structureData_Create(structure_2);

    // Put those Datas into Nodes
    Node_t *structNode_1 = node_Create(structureData_1, NodeInterface_StructureData);
    Node_t *structNode_2 = node_Create(structureData_2, NodeInterface_StructureData);

    // Make a root Array Structure
    Array_t *root_array = array_Create(array_size);

    // Fill it up half-arsedly
    for (size_t i = 0; i < 2; i++)
    {
        IntData_t *intData = intData_Create(i);
        Node_t *intNode = node_Create(intData, NodeInterface_IntData);
        array_Insert(root_array, intNode, i);
    }
    for (size_t i = 2; i < 5; i++)
    {
        StringData_t *stringData = stringData_Create(string_samples[i]);
        Node_t *stringNode = node_Create(stringData, NodeInterface_StringData);
        array_Insert(root_array, stringNode, i);   
    }
    
    // Put those Array Structure Nodes into our root Array Structure
    array_Insert(root_array, structNode_1, 8);
    array_Insert(root_array, structNode_2, 9);
    // Notice how we even left some spots empty in the root array (indexes 5 - 7)

    // Put the root array structure into a structure instance
    Structure_t *weirdStructure = structure_Create(root_array, StructureInterface_Array);

    // We can even go ahead and turn this weirdStructure into a Data like the previous ones.
    // Then we can go further and put it inside a Node as well if we like.
    // We would do that if we want to nest this weirdStructure yet again in another structure.
    // The nesting possibilities are infinite... if your RAM stick can handle it.
    // But for the purpose of this test, we will stop here.

    // And voila! Let's see what we got. It should be an array containing some random values at
    // the start, some empty nodes in the middle, and another array at the end.
    structure_Print(weirdStructure);
    println("");

    // Don't forget freedom is a right. Recursively free everything held under weirdStructure.
    structure_Free(weirdStructure);
}

// Now, test number 3. This test is for testing polymorphic linked lists.
void test_list_1()
{
    size_t list_size = test_size;
    List_t *list = list_Create();

    // Filling in the list
    for (size_t i = 0; i < list_size; i++)
    {
        TupleData_t *data = tupleData_Create(i%2, string_samples[i]);
        Node_t *node = node_Create(data, NodeInterface_TupleData);
        list_InsertBottom(list, node);
    }
    
    // Make a structure to hold this list
    Structure_t *structure_1 = structure_Create(list, StructureInterface_List);

    // Show our original list
    println("Original list:");
    structure_Print(structure_1);
    println("");

    // Sort the list and show it
    println("Sorted list:");
    structure_Sort(structure_1);
    structure_Print(structure_1);
    println("");

    // I repeat, freedom is a right. Recursively free our objects.
    structure_Free(structure_1);
}

// This is test number 4, and we are creating a list, then putting it inside another list.
// This is similar to test number 2, but with Lists instead of Arrays.
// This test is for testing nested linked lists.
void test_list_2()
{
    size_t list_size = test_size;

    // Create a list, which will be stored inside another list.
    List_t *inner_list = list_Create();
    // Filling the inner_list
    for (size_t i = 0; i < list_size; i++)
    {
        TupleData_t *data = tupleData_Create(0, "inner_peace");
        Node_t *node = node_Create(data, NodeInterface_TupleData);
        list_InsertBottom(inner_list, node);
    }

    // This will be our outer list, containing the inner_list
    List_t *list = list_Create();
    // Filling the outer list
    for (size_t i = 0; i < list_size; i++)
    {
        TupleData_t *data = tupleData_Create(i, string_samples[i]);
        Node_t *node = node_Create(data, NodeInterface_TupleData);
        list_InsertBottom(list, node);
    }

    // Make a structure to hold the inner_list
    Structure_t *inner_structure = structure_Create(inner_list, StructureInterface_List);
    // Encapsulate this structure as a piece of Data
    StructureData_t *inner_list_as_data = structureData_Create(inner_structure);
    // Store it in a Node
    Node_t *inner_list_as_node = node_Create(inner_list_as_data, NodeInterface_StructureData);
    // Insert this Node into the bottom of the outer list
    list_InsertBottom(list, inner_list_as_node);
    
    // Make a structure to hold outer list
    Structure_t *structure = structure_Create(list, StructureInterface_List);
    
    // Let's see what we got, should be a linked list containing some elements and another linked
    // list
    structure_Print(structure);
    println("");

    // Freedom is the best. Recursively free our objects.
    structure_Free(structure);
}

// And this test is our test number 5! We are creating a linked_list
void test_both()
{
    size_t array_size = test_size;
    // Here is our outer array, initially malloced to array_size but empty.
    // This array will contain a list inside it.
    Array_t *array = array_Create(array_size);

    // Let's get some values into our array
    // Filling in ints
    for (size_t i = 0; i < 2; i++)
    {
        IntData_t *intData = intData_Create(i);
        Node_t *intNode = node_Create(intData, NodeInterface_IntData);
        array_Insert(array, intNode, i);
    }
    // Filling in strings
    for (size_t i = 2; i < 4; i++)
    {
        StringData_t *stringData = stringData_Create(string_samples[i]);
        Node_t *stringNode = node_Create(stringData, NodeInterface_StringData);
        array_Insert(array, stringNode, i);
    }
    // Filling in floats
    for (size_t i = 4; i < 6; i++)
    {
        float pi = 3.1415;
        FloatData_t *floatData = floatData_Create(pi);
        Node_t *floatNode = node_Create(floatData, NodeInterface_FloatData);
        array_Insert(array, floatNode, i);
    }

    // Now we have 3 different kinds of Data in our array, indices 0->5
    // We will leave indices 6->8 empty on purpose, then put a linked list
    // on index 9 (last position in array).

    // Create a list, we will put this inside the array
    List_t *inner_list = list_Create();
    // Filling in the list
    for (size_t i = 0; i < test_size; i++)
    {
        TupleData_t *data = tupleData_Create(0, "inner_DOGE");
        Node_t *node = node_Create(data, NodeInterface_TupleData);
        list_InsertBottom(inner_list, node);
    }

    // Create a Structure to store our inner_list
    Structure_t *inner_structure = structure_Create(inner_list, StructureInterface_List);
    // Encapsulate this structure as a piece of Data
    StructureData_t *inner_list_as_data = structureData_Create(inner_structure);
    // Store it in a Node
    Node_t *inner_list_as_node = node_Create(inner_list_as_data, NodeInterface_StructureData);
    
    // Insert the list in the last position of the array
    // This will leave empty slots in the middle of array
    array_Insert(array, inner_list_as_node, array->size-1);

    // Make a structure to hold this array
    Structure_t *structure_1 = structure_Create(array, StructureInterface_Array);

    // Let's see what we got, it should be an array with some random items at the start,
    // some empty nodes in the middle, and a really cool linked list at the last index.
    structure_Print(structure_1);
    println("");;

    // Freedom is really good for the world. Recursively free our objects.
    structure_Free(structure_1);
}



// And here we got our test number 6. Insane nesting, 9 levels of depth, with base 
// object at the bottom. 
void test_crazy_nested() 
{
    StringData_t *base_data = stringData_Create(" Much wow, such cool ");
    Node_t *base_node = node_Create(base_data, NodeInterface_StringData);

    // Nest structures
    // I do realize there is quite a bit of code here for initialising a Node that 
    // contains a data Structure, then put it into another Node. I may create 
    // functions for this in the future.

    // The alternative is mentioned in the README, where another layer of 
    // indirection is introduced by creating vtables, which will also reduce the
    // number of lines required to create a new Structure, or just any Data in
    // general.

    // Create the 1st Structure, put base_node inside it
    Array_t *struct1 = array_Create(1);
    array_InsertNext(struct1, base_node);
    Structure_t *wrapper1 = structure_Create(struct1, StructureInterface_Array);
    StructureData_t *data1 = structureData_Create(wrapper1);
    Node_t *node1 = node_Create(data1, NodeInterface_StructureData);

    // Create the 2nd Structure, put node_1 inside it
    List_t *struct2 = list_Create();
    list_InsertTop(struct2, node1);
    Structure_t *wrapper2 = structure_Create(struct2, StructureInterface_List);
    StructureData_t *data2 = structureData_Create(wrapper2);
    Node_t *node2 = node_Create(data2, NodeInterface_StructureData);

    // Create the 3rd Structure, put node_2 inside it
    Array_t *struct3 = array_Create(1);
    array_InsertNext(struct3, node2);
    Structure_t *wrapper3 = structure_Create(struct3, StructureInterface_Array);
    StructureData_t *data3 = structureData_Create(wrapper3);
    Node_t *node3 = node_Create(data3, NodeInterface_StructureData);
    
    // Create the 4th Structure, put node_3 inside it
    List_t *struct4 = list_Create();
    list_InsertTop(struct4, node3);
    Structure_t *wrapper4 = structure_Create(struct4, StructureInterface_List);
    StructureData_t *data4 = structureData_Create(wrapper4);
    Node_t *node4 = node_Create(data4, NodeInterface_StructureData);

    // Create the 5th Structure, put node_4 inside it
    Array_t *struct5 = array_Create(1);
    array_InsertNext(struct5, node4);
    Structure_t *wrapper5 = structure_Create(struct5, StructureInterface_Array);
    StructureData_t *data5 = structureData_Create(wrapper5);
    Node_t *node5 = node_Create(data5, NodeInterface_StructureData);

    // Create the 6th Structure, put node_5 inside it
    List_t *struct6 = list_Create();
    list_InsertTop(struct6, node5);
    Structure_t *wrapper6 = structure_Create(struct6, StructureInterface_List);
    StructureData_t *data6 = structureData_Create(wrapper6);
    Node_t *node6 = node_Create(data6, NodeInterface_StructureData);

    // Create the 7th Structure, put node_6 inside it
    Array_t *struct7 = array_Create(1);
    array_InsertNext(struct7, node6);
    Structure_t *wrapper7 = structure_Create(struct7, StructureInterface_Array);
    StructureData_t *data7 = structureData_Create(wrapper7);
    Node_t *node7 = node_Create(data7, NodeInterface_StructureData);

    // Create the 8th Structure, put node_7 inside it
    List_t *struct8 = list_Create();
    list_InsertTop(struct8, node7);
    Structure_t *wrapper8 = structure_Create(struct8, StructureInterface_List);
    StructureData_t *data8 = structureData_Create(wrapper8);
    Node_t *node8 = node_Create(data8, NodeInterface_StructureData);

    // Recursively print everything inside node_8, the Node that contains everything else
    node_Print(node8);
    println("");
    fflush(stdout);

    // Recursively free everything, since freedom is the key to happiness.
    node_Free(node8);
}
