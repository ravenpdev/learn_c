#include <stdio.h>

// We use the address-of operator (which happens to be an ampersand: "&") to find
// the address of the data.

// Dereferencing
// When you have a pointer to a variable (roughly "a reference to a variable"), you can
// use the original variable through the pointer by dereferencing the pointer.
//
// What is the dereferene operator? it's actually called the "indirection operator", because
// you're accessing values indirectly via the pointer. And it is the asterisk again: *.
// Now, don't get this confused with the asterisk you used in the pointer declaration, earlier.
// They are the same character, but they have differentn meanings in different contexts.

void increment(int *p) { *p = *p + 1; }

int main(void) {
    {
        int i = 10;

        printf("The value of i is %d\n", i);
        printf("And its address is %p\n", (void *)&i);
    }

    {
        // Remember that p holds the dadress of i, What the indirection operator does
        // is tells the computer to use the object the pointer points to instead of
        // using the pointer itself. In this way, we have turned *p into an alias of
        // sorts for i.

        int i;
        int *p; // int-pointer

        p = &i; // p now points to i, p holds address of i

        i = 10;  // i is now 10
        *p = 20; // the thing p points to (namely i!) is now 20!!

        printf("i is %d\n", i);
        printf("i is %d\n", *p);
    }

    {
        int i = 10;
        int *j = &i; // note the address-of; turns it into a pointer to i

        printf("i is %d\n", i);       // prints "10"
        printf("i is also %d\n", *j); // prints "10"

        increment(j); // j is an int* to i

        printf("i is %d\n", i);
    }

    {
        int i = 10;
        increment(&i);
        printf("i is %d\n", i);
    }

    // The NULL Pointer
    //
    // Any pointer variable of anny poinnter type can be set to a special value called NULL.
    // This indicates that this pointer doesn't point to anything.
    {
        int *p;

        p = NULL;

        // Since it odesn't point to avalue, dereferencing it is undefined behavior, and
        // probably will result in a crash:

        // this will cause a segmentation fault.
        /* *p = 12; */
    }

    // The sizeof and Pointers
    //
    // Recall that sizeof operates on the type of the expression.
    {
        int *p;

        // Prints size of an 'int'
        printf("%zu\n", sizeof(int));

        // p is type 'int *', so prints size of 'int*'
        printf("%zu\n", sizeof p);

        // *p is type 'int', so prints size of 'int'
        printf("%zu\n", sizeof *p);
    }
}
