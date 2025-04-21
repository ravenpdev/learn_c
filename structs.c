/* #include <stdbool.h> */
#include <stdio.h>

// Structs
//
// You can think of a struct as a class with only data members, and no methods.

// The full type name is struct person. (Not just person - that wonn't work.)
//
// Struct is somewhat large and it's more expensive to copy that onto the stack than it is to just
// copy a pointer.

struct person {
    char *name;
    int age;
    /* bool is_married; */
};

void set_age(struct person *p, int value) {
    // The dot operator only works on structs... it doesn't work on poitners to structs.
    //
    // Ok, so we can dereference the variable c to de-pointer it to get the struct itself.
    // Dereferencing a struct person* results in the struct person that the pointer points to, which
    // we should be able to use the dot operator on:

    /* (*p).age = age; // Works, but is ugly and non-idiomatic */

    // The Arrow Operator
    // The arrow operator helps refer to fields in pointers to structs.
    p->age = value;

    // So when accessing fields, when do we use dot and when do we use arrow?
    // - If you have a struct, use dot (.).
    // - If you have a pointer to a struct, use arrow (->).
}

int main(void) {
    struct person john; // uninitialized variable john of type struct person.

    john.name = "John Doe";
    john.age = 32;

    printf("Name: %s\n", john.name);
    printf("Age: %d\n", john.age);

    // Struct Initializers
    {
        // With this initializer, fields need to be in the same order
        struct person jane = {"Jane Doe", 30};
        printf("Name: %s\n", jane.name);
        printf("Age: %d\n", jane.age);

        // With this initializer, it's independed of the order in the struct declaration.
        struct person bob = {.name = "Bob Doe", .age = 30};
        printf("Name: %s\n", bob.name);
        printf("Age: %d\n", bob.age);
    }

    {
        struct person john = {.name = "John Doe", .age = 33};

        set_age(&john, 33);

        printf("Name: %s, Age: %d\n", john.name, john.age);
    }

    // Copying and Returning structs
    //
    // Just assign from one to the other!
    // And returning a struct (as opposed to a pointer to one) from a function also makes a similar
    // copy to the receiving variable.
    //
    // This is not a deep copy. All fields are copied as-is, including pointers to things.
    {
        struct person a, b;

        a.name = "john";
        a.age = 32;

        b = a;

        b.name = "jane";

        printf("%s, %d\n", a.name, a.age);
        printf("%s, %d\n", b.name, b.age);
    }

    // Coparing structs
    //
    // There's only one safe way to do it; compare each field one at a time.
    //
    // You might think you could use memcmp(), but that doesn't handle the case of the possible
    // padding bytes that might be in there.
    //
    // If you clear the struct to zero first with memset(), then it might work, though there could
    // be weird elements that might not compare as you expect.
}
