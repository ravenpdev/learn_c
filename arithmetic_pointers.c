#include <_stdlib.h>
#include <stdio.h>
#include <string.h>

/* Pointer Arithmethic */

// Turns out you can do math on pointner, notably addition and subtraction.
//
// I you have a pointer to a type, adding one to the pointer moves to the next item of that type
// directly after it in memory.
//
//
// It's important to remember that as we move pointers around and look at different places in
// memory, we need to make sure that we're always pointing to a valid place in memory before we
// dereference. If we're off in the weeds and we try to see what's there, the behavior is undefined
// and a crash is a common result.

int my_strlen(char *s);

void *my_memcpy(void *dest, void *src, int byte_count) {
    // Convert void*s to char*s
    char *s = src, *d = dest;

    while (byte_count--) {
        *d++ = *s++;
    }

    return dest;
}

struct animal {
    char *name;
    int leg_count;
    int age;
};

int compar(const void *elem1, const void *elem2) {
    // We know we're sorting struct animals, so let's make both
    // arguments pointers to struct animals
    const struct animal *animal1 = elem1;
    const struct animal *animal2 = elem2;

    if (animal1->leg_count > animal2->leg_count) {
        return 1;
    }

    if (animal1->leg_count < animal2->leg_count) {
        return -1;
    }

    return 0;
}

int main(void) {
    /* {
        int a[5] = {11, 22, 33, 44, 55};

        int *p = &a[0]; // or "int *p = a;" works just as well

        printf("%d\n", *(p + 1)); // Prints 22!!

        // What happened there? C knows that p is a pointer to an int. So it knows the sizeof an int
        // and it knows to skip that many bytes to get to the next int after the first one!
        //
        // In fact, the prior example could be written these two equivalent ways:
        printf("%d\n", *p);
        printf("%d\n", *(p + 0));

        printf("size of in in bytes: %lu\n", sizeof(int));
    } */

    // Remember from early on that memory is like a big array, where a byte is stored at each array
    // index? Pointer is an index into memory, somewhere.
    //
    // And the array index into memory has a few names:
    // - Index into memory
    // - Location
    // - Address
    // - Pointer!
    //
    //
    // If we add 1 to the pointer, it actually jumps sizeof(int) bytes to the
    // next int.
    {
        int a[] = {11, 22, 33, 44, 55};

        int *p = &a[0]; // same as *p = a
        int len = sizeof(a) / 4;

        for (int i = 0; i < len; i++) {
            printf("%d\n", *(p + i)); // same as p[i];
        }
    }

    /* {
        int a[] = {11, 22, 33, 44, 55, 999};
        int *p = a;

        while (*p != 999) { // while the thing p points to isn't 999
            printf("%d\n", *p); // Print it
            p++; // Move p to the next int!
        }
    } */

    // Subracting Pointers
    //
    // Remember that you can only use pointer subtraction between to pointers that point to the same
    // array!
    /* {
        printf("%d\n", my_strlen("Hello, world!"));
    } */

    // Array/Pointer Equivalence
    // We're finally read to talk about this! We've seen plenty of examples of places where we've
    // intermixed array notation, but let's give out the fundamental formula of array/pointer
    // equivalence:
    //
    // a[b] == *(a + b)
    //
    // Those are equivalent and can be used intechangeably!
    //
    // The spec is specific, as always, declaring (in C11)
    //
    // E1[E2] is identical to (*((E1) + (E2)))
    //
    // The one big difference is that you can modify a pointer to point to a different address, but
    // you cna't do that with an array variable.
    {
        int a[] = {11, 22, 33, 44, 55};
        int *p = a;

        for (int i = 0; i < 5; i++) {
            printf("%d\n", a[i]);
        }
        for (int i = 0; i < 5; i++) {
            printf("%d\n", p[i]);
        }
        for (int i = 0; i < 5; i++) {
            printf("%d\n", *(a + i));
        }
        for (int i = 0; i < 5; i++) {
            printf("%d\n", *(p + i));
        }
        for (int i = 0; i < 5; i++) {
            printf("%d\n", *(p++));
        }
    }

    // void Pointers
    //
    // The void keyword used with functions, but this is an entirely separate, unrelated animal.
    //
    // Sometimes it's useful to have a pointer to a thing that you don't know the type of.
    //
    // There are basically two use cases for this.
    //
    // 1. A function is going to operate on something byte-by-byte. For example, memcpy() copies
    // bytes of memory from one pointer to another, but those pointers can point to any type.
    // memcpy() takes advantage of the fact that if you iterate through char*s, you're iterating
    // through the bytes of an object no matter what type the object is. More on this in the
    // Multibyte Values.
    //
    // 2. Another function is calling a function you passed to int (a callback), and it's passing
    // you data. You know the type of the data, but the function calling you doesn't. So it passes
    // you void*s - cause it doesn't know the type and you convert those to the type you need. The
    // build-in qsort() and bsearch() use this technique.
    //
    // Imagine if we dind't have void*. We'd have to write specialized memcpy() function for each
    // type:
    //
    // That's the power of void*. You can write functions that don't care about type and is still
    // able to do things with it.
    //
    // Limitations of void*:
    // 1. You cannot do pointer atihmetic on a void*.
    // 2. You cannot dereference a void*.
    // 3. You cannot use the arrow operator on a void*, since it's also a dereference.
    // 4. You cannot use array notation on a void*, since it's also a dereference, as well.
    //
    // An if you think about it, these rules make sense. All those operations rely on knowing the
    // size of the type of data pointed to, and with void* we don't know the size of the data being
    // pointe to - it could be anything.
    //
    // void* helps you write generic functions that can handle multiple types of data. But the
    // secret is that, deep down, you convert the void* to another type before you use it!.
    //
    // And conversion is easy: you can just assign into a variable ofthe desired type.
    {
        char s[] = "Goats!";
        char t[100];

        // void *memcpy(void *s1, void *s2, size_t n);
        memcpy(t, s, 2); // copy a 2 char of data

        printf("%s\n", t); // "Go"

        int a[] = {11, 22, 33};
        int b[3];

        memcpy(b, a, 3 * sizeof(int)); // copy 3 ints of data
        printf("%d\n", b[1]);          // 22

        char z = 'X'; // A single char, 1byte
        void *p = &z; // p points to the 'X';
        char *q = p;  // q also points to the 'X';

        /* printf("%d\n", *p); // Error--cannot dereference void*! */
        printf("%c\n", *q);
    }

    {
        struct animal a[4] = {
            {.name = "Dog", .leg_count = 4},
            {.name = "Monkey", .leg_count = 2},
            {.name = "Antnelope", .leg_count = 4},
            {.name = "Snake", .leg_count = 0},
        };

        printf("size of animal: %zu\n", sizeof(struct animal));

        qsort(a, sizeof(a) / 16, sizeof(struct animal), compar);

        for (int i = 0; i < 4; i++) {
            printf("%d: %s\n", a[i].leg_count, a[i].name);
        }
    }
}

int my_strlen(char *s) {
    char *p = s;

    while (*p != '\0') {
        p++;
    }

    return p - s;
}
