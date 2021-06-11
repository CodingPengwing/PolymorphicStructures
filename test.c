
#include "Node.h"
#include "Structure.h"

#include "data_types/IntData.h"
#include "data_types/StringData.h"
#include "data_types/StructureData.h"
#include "data_types/FloatData.h"
#include "data_types/TupleData.h"

#include "structure_types/Array.h"
#include "structure_types/List.h"

// Some test cases;
void test_array_1();
void test_array_2();
void test_list_1();
void test_list_2();
void test_both();

// Some test values
char *string_samples[] = {"puppy", "corgi", "pug", "shiba", "golden", "kitty", "chonky", "husky", "chubby", "doge"};
size_t test_size = 10;

int main(int argc, char const *argv[])
{
    // TEST 5 SCENARIOS
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
        Node_t *intNode = node_Create(intData, IntData_as_Node);
        array_Insert(array, intNode, i);
        // Filling strings
        StringData_t *stringData = stringData_Create(string_samples[i+3]);
        Node_t *stringNode = node_Create(stringData, StringData_as_Node);
        array_Insert(array, stringNode, i+3);
        // Filling floats
        FloatData_t *floatData = floatData_Create(3.1415);
        Node_t *floatNode = node_Create(floatData, FloatData_as_Node);
        array_Insert(array, floatNode, i+6);
    }
    // Notice how we left the last index empty, only filled indices 0->8
    
    // Make a structures to hold this array
    Structure_t *structure_1 = structure_Create(array, Array_as_Structure);

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
        Node_t *intNode = node_Create(intData, IntData_as_Node);

        array_Insert(array, intNode, i);

        // Filling out the string array
        StringData_t *stringData = stringData_Create(string_samples[i]);
        Node_t *stringNode = node_Create(stringData, StringData_as_Node);
        array_Insert(string_array, stringNode, i);
    }
    
    // Make some structures to hold these arrays
    Structure_t *structure_1 = structure_Create(array, Array_as_Structure);
    Structure_t *structure_2 = structure_Create(string_array, Array_as_Structure);

    // NEW CONTENT
    /*-----------------------------------------------------------------------------*/

    // Here's the fun part, let's nest our structures in one another

    // Encapsulate the previous structures inside pieces of Datas
    StructureData_t *structureData_1 = structureData_Create(structure_1);
    StructureData_t *structureData_2 = structureData_Create(structure_2);

    // Put those Datas into Nodes
    Node_t *structNode_1 = node_Create(structureData_1, StructureData_as_Node);
    Node_t *structNode_2 = node_Create(structureData_2, StructureData_as_Node);

    // Make a root Array Structure
    Array_t *root_array = array_Create(array_size);

    // Fill it up half-arsedly
    for (size_t i = 0; i < 2; i++)
    {
        IntData_t *intData = intData_Create(i);
        Node_t *intNode = node_Create(intData, IntData_as_Node);
        array_Insert(root_array, intNode, i);
    }
    for (size_t i = 2; i < 5; i++)
    {
        StringData_t *stringData = stringData_Create(string_samples[i]);
        Node_t *stringNode = node_Create(stringData, StringData_as_Node);
        array_Insert(root_array, stringNode, i);   
    }
    
    // Put those Array Structure Nodes into our root Array Structure
    array_Insert(root_array, structNode_1, 8);
    array_Insert(root_array, structNode_2, 9);
    // Notice how we even left some spots empty in the root array (indexes 5 - 7)

    // Put the root array structure into a structure instance
    Structure_t *weirdStructure = structure_Create(root_array, Array_as_Structure);

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
        Node_t *node = node_Create(data, TupleData_as_Node);
        list_InsertBottom(list, node);
    }
    
    // Make a structure to hold this list
    Structure_t *structure_1 = structure_Create(list, List_as_Structure);

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
        TupleData_t *data = tupleData_Create(0, "inner_list_item");
        Node_t *node = node_Create(data, TupleData_as_Node);
        list_InsertBottom(inner_list, node);
    }

    // This will be our outer list, containing the inner_list
    List_t *list = list_Create();
    // Filling the outer list
    for (size_t i = 0; i < list_size; i++)
    {
        TupleData_t *data = tupleData_Create(i, string_samples[i]);
        Node_t *node = node_Create(data, TupleData_as_Node);
        list_InsertBottom(list, node);
    }

    // Make a structure to hold the inner_list
    Structure_t *inner_structure = structure_Create(inner_list, List_as_Structure);
    // Encapsulate this structure as a piece of Data
    StructureData_t *inner_list_as_data = structureData_Create(inner_structure);
    // Store it in a Node
    Node_t *inner_list_as_node = node_Create(inner_list_as_data, StructureData_as_Node);
    // Insert this Node into the bottom of the outer list
    list_InsertBottom(list, inner_list_as_node);
    
    // Make a structure to hold outer list
    Structure_t *structure = structure_Create(list, List_as_Structure);
    
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
        Node_t *intNode = node_Create(intData, IntData_as_Node);
        array_Insert(array, intNode, i);
    }
    // Filling in strings
    for (size_t i = 2; i < 4; i++)
    {
        StringData_t *stringData = stringData_Create(string_samples[i]);
        Node_t *stringNode = node_Create(stringData, StringData_as_Node);
        array_Insert(array, stringNode, i);
    }
    // Filling in floats
    for (size_t i = 4; i < 6; i++)
    {
        float pi = 3.1415;
        FloatData_t *floatData = floatData_Create(pi);
        Node_t *floatNode = node_Create(floatData, FloatData_as_Node);
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
        TupleData_t *data = tupleData_Create(0, "inner_list_DOGE");
        Node_t *node = node_Create(data, TupleData_as_Node);
        list_InsertBottom(inner_list, node);
    }

    // Create a Structure to store our inner_list
    Structure_t *inner_structure = structure_Create(inner_list, List_as_Structure);
    // Encapsulate this structure as a piece of Data
    StructureData_t *inner_list_as_data = structureData_Create(inner_structure);
    // Store it in a Node
    Node_t *inner_list_as_node = node_Create(inner_list_as_data, StructureData_as_Node);
    
    // Insert the list in the last position of the array
    // This will leave empty slots in the middle of array
    array_Insert(array, inner_list_as_node, array->size-1);

    // Make a structure to hold this array
    Structure_t *structure_1 = structure_Create(array, Array_as_Structure);

    // Let's see what we got, it should be an array with some random items at the start,
    // some empty nodes in the middle, and a really cool linked list at the last index.
    structure_Print(structure_1);
    println("");;

    // Freedom is really good for the world. Recursively free our objects.
    structure_Free(structure_1);
}