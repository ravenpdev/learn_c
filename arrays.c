#include <stdio.h>

// Arrays
//
// C only barely has arrays!, arrays are just syntactic sugar in C- they're actually
// all pointers and stuff deep down. Freak out! But for now, let's just use them as
// arrays.
//
// When you declare an array, you have to give it a size. And the size has to be fixed.

// Getting the Length of an Array
//
// You can't...ish. C doesn't record this information. You have to manage it separetly
// in other variable.
//
// There are some circumstances when you can. There is a trick to get the number of elements
// in an array in the scope in which an array is declared. But, generally speaking, this
// won't work the way you want if you pass the array to a function.
//
// This is because when you "pass" arrays to functions, you're only passing a pointer to
// first element, and that's what sizeof measures.
//
// One more thing you can do with sizeof and arrays is get the size of an array of fixed
// number of elements without declaring the array. This is like how you can get the size
// of an int with sizeof(int).

void foo(int x[12]) {
    printf("%zu\n", sizeof x);    // 8?! What happened to 48?
    printf("%zu\n", sizeof(int)); // 4 bytes per int

    printf("%zu\n", sizeof x / sizeof(int)); // 8/4 = 2 ints?? WRONG.
}

// Array Initializers
//
// you can initialize an array with constants ahead of time:

// You can put simple constant expression in there, as well
#define COUNT 5

void array_initializer() {
    int i;
    int a[5] = {22, 37, 3490, 18, 95}; // Initialize with these values

    for (i = 0; i < 5; i++) {
        printf("%d\n", a[i]);
    }

    // You should never have more items in your initializer than ther is romm
    // for in the array or the compiler with get cranky:
    //
    // But you can have fewer items in your initializer than there is room for in
    // the array. The raimining elements in the array will be automatically initialized
    // with zero. This is true in general for all types of array initializers: if you
    // have an initializer, anything not explicitly set to a value will be set to zero.

    int arr1[5] = {22, 37, 3490};
    // is the same as:
    int arr2[5] = {22, 37, 3490, 0, 0};

    // It's a common shortcut to see this in an initializer when you wannt to set an
    // entire array to zero:
    //
    // Which means, "make the first element zero, andn then automatically make the rest
    // zero, as well."
    int arr3[100] = {0};

    // You can set specific array elements inn the initializer, as well, by specifying an
    // index for the value! When you do this, C will happily keep initializing subsequent
    // values for you until the initializer runs out, filling everthing else with 0.
    int arr4[10] = {0, 11, 22, [5] = 55, 66, 77}; // 0 11 22 0 0 55 66 77 0 0

    int arr5[COUNT] = {[COUNT - 3] = 3, 2, 1}; // 0 0 3 2 1

    // Lastly, you can also have C compute the size of the array from the initializer, just
    // by leaving the size off:
    int arr6[3] = {22, 37, 3490};
    // is the same as:
    int arra7[] = {22, 37, 3490}; // Left he size off!
}

// Out of Bounds!
//
// C doesn't stop you from accessing arrays out of bounds. It might not even warn you.
void out_of_bounds(void) {
    int a[5] = {22, 37, 3490, 18, 95};
    int i;
    // Turns out printing off the end of an array result in what C developers call
    // "undefined behavior".
    //
    // Anything could happen during your program run, and by anything, I mean typically
    // things like finding zeroes, finding garbage numbers, or crashing. But really the
    // C specs says in this circumstance the compiler is allowed to emit code that does
    // anything.
    //
    // Short version: don't do anything that causes undefined behavior. Ever
    for (i = 0; i < 10; i++) {
        printf("%d\n", a[i]);
    }
}

// Multidimensional Arrays
//
// You can add as many dimensions as you want to your arrays.
void multidimensional_array(void) {
    int a[10];
    int b[2][7];
    int c[4][5][6];
    // These are stored in memory in row-major order. This means with a 2D array, the
    // first index listed indicates the row, and the second the column.

    int row, col;
    int arr[2][5] = {{0, 1, 2, 3, 4}, {5, 6, 7, 8, 9}};

    for (row = 0; row < 2; row++) {
        for (col = 0; col < 5; col++) {
            printf("(%d, %d) = %d\n", row, col, arr[row][col]);
        }
    }

    // And you can initialize with explicit indexes:
    // Make a 3x3 identity matrix
    int board[3][3] = {[0][0] = 1, [1][1] = 1, [2][2] = 1};
    // which builds a 2D array like this:
    // 1 0 0
    // 0 1 0
    // 0 0 1
}

// Getting a Pointer to an Array
//
// When a C programmer talks about a pointer to an array, they're talking about a pointer
// to the first element of the array.
void pointer_to_array(void) {
    int a[5] = {11, 22, 33, 44, 55};
    int *p;
    int *b;

    p = &a[0]; // p points to the array, Well, to the first element, actually
    printf("%d\n", *p);

    // This is so common to do in C that the language allows us a shorthand:
    //
    // Just referring to the array name in isolation is the same as getting a pointer
    // to the first element of the array!.
    b = a;
    printf("%d\n", *b);
}

// Passing Single Dimensional Arrays to Functions

// Passing as a pointer to the first element
void times2(int *a, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d\n", a[i] * 2);
    }
}

// Same thing, but using array notation
void times3(int a[], int len) {
    for (int i = 0; i < len; i++) {
        printf("%d\n", a[i] * 3);
    }
}

// Same thing, but using array notation with size
void times4(int a[5], int len) {
    for (int i = 0; i < len; i++) {
        printf("%d\n", a[i] * 4);
    }
}

// Changing Arrays in Functions
//
// We've said that arrays are just pointers in disguise. This means that if you pass
// an array to a function, you're likely passing a pointer to the first element in the
// array.
//
// But if the function has a pointer to the data, it is able to manipulate that data!
// So changes that a function makes to an array will be visible back out in the caller.
void doulbe_array(int *a, int len) {
    for (int i = 0; i < len; i++) {
        a[i] *= 2;
    }
}

// Passing Multidimensional Arrays to Functions
//
// The story changes a little when we're talking about multidimensional arrays.
// C needs to know all the dimensions (except the first one) so it has enough
// information to know where in memory to look to find a value.
void print_2D_array(int a[2][3]) {
    for (int row = 0; row < 2; row++) {
        for (int col = 0; col < 3; col++) {
            printf("%d ", a[row][col]);
        }
        printf("\n");
    }

    // But in this case, these two are equivalent:
    /* void print_2D_array(int a[2][3]) */
    /* void print_2D_array(int a[][3]) */

    // The compiler really only needs the second dimension so it can figure out how
    // far in memory to skip for each increment of the first dimension. In general, it
    // needs to know all the dimensions except the first one.
    //
    // Also, remember that the compiler does minimal compile-time bounds checking
    // (if you're lucky), and C does zero runtime checking of bounds, No seat belts!
    // Don't crash by accessing array elements out of bounds!
}

int main(void) {
    float f[4]; // Declare an array of 4 floats.

    // Indexing start at 0, of course.
    f[0] = 3.14159;
    f[1] = 1.41421;
    f[2] = 1.61803;
    f[3] = 2.71828;

    int i;
    for (i = 0; i < 4; i++) {
        printf("%f\n", f[i]);
    }

    // How to get a length of an array
    //
    // This trick only works in the scope in which the array was defined. If you pass
    // the array to a function, it doesn't work. Even if you make it "big" in the
    // function signature:
    {
        int x[12]; // 12 ints

        printf("%zu\n", sizeof x);    // 48 total bytes
        printf("%zu\n", sizeof(int)); // 4 bytes

        printf("%zu\n", sizeof x / sizeof(int)); // 48 / 4 = 12 int!
    }

    {
        array_initializer();
    }

    {
        printf("------- OUT OF BOUNDS! -------\n");
        out_of_bounds();
    }

    {
        printf("------- MULTI-DIMENSIONAL -------\n");
        multidimensional_array();
    }

    {
        printf("------- POINTER TO ARRAY -------\n");
        pointer_to_array();
    }

    {
        printf("------- Passing Dimensional Arrays to Funcntions -------\n");

        int x[5] = {11, 22, 33, 44, 55};

        times2(x, 5);
        times3(x, 5);
        times4(x, 5);
    }

    {
        printf("------- Changing Arrays in Functions -------\n");

        int x[5] = {1, 2, 3, 4, 5};

        doulbe_array(x, 5);

        for (int i = 0; i < 5; i++) {
            printf("%d\n", x[i]);
        }
    }
}
