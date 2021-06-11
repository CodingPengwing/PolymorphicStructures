
/*  This code was retrieved from 
    https://chris-wood.github.io/2016/02/12/Polymorphism-in-C.html

    It was used as guidance in building the interfaces for this
    library of polymorphic functions. As mentioned in the linked post,
    this implementation of polymophism utilises interfaces to design
    objects in the "is-a" way rather than the "has-a" way. 
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>


/********************* Shape Interface *********************/

typedef struct shape_interface {
    double (*Area)(void *instance);
} ShapeInterface;

typedef struct {
    void *instance;
    const ShapeInterface *interface;
} Shape;


Shape *
shape_Create(void *instance, ShapeInterface *interface)
{
    Shape *shape = (Shape *) malloc(sizeof(Shape));
    shape->instance = instance;
    shape->interface = interface;
    return shape;
}

double
shape_Area(Shape *shape)
{
    return (shape->interface->Area)(shape->instance);
}

/*********************** Square Shape ***********************/

typedef struct {
    double x;
} Square;

double
square_Area(Square *square)
{
    return square->x * square->x;
}

ShapeInterface *SquareAsShape = &(ShapeInterface) {
    .Area = (double (*)(void *)) square_Area
};

Square *
square_Create(double sideLength)
{
    Square *square = (Square *) malloc(sizeof(Square));
    square->x = sideLength;
    return square;
}

/*********************** Circle Shape ***********************/

typedef struct {
    double radius;
} Circle;

double
circle_Area(Circle *circle)
{
    return M_PI * (circle->radius * circle->radius);
}

ShapeInterface *CircleAsShape = &(ShapeInterface) {
    .Area = (double (*)(void *)) circle_Area
};

Circle *
circle_Create(double radius)
{
    Circle *circle = (Circle *) malloc(sizeof(Circle));
    circle->radius = radius;
    return circle;
}

/********************** Testing it out! **********************/

int
main(int argc, char **argv)
{
    // Create concrete types.
    Circle *circle = circle_Create(5.0);
    Square *square = square_Create(10.0);

    // Wire up the tables.
    Shape *circleShape = shape_Create(circle, CircleAsShape);
    Shape *squareShape = shape_Create(square, SquareAsShape);

    // Sanity check.
    printf("Equal circle areas? %d\n", circle_Area(circle) == shape_Area(circleShape));
    printf("Equal square areas? %d\n", square_Area(square) == shape_Area(squareShape));

    // ... free up memory


    return 0;
}
