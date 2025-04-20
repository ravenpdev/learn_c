#include <stdio.h>
#include <string.h>

int my_strlen(char *p);

// Strings
//
// Well, turns out string aren't actually strings in C. That's right! They're pointers!
// of course ther are!
//
// Much like arrays, stringgs in C barely exist.

// String Literals
// These are sequences of character in double quotes (")
// Examples:
// "Hello, world!\n"
// "This is a test."
// "When asked if this string had quotes in it, she replied, \"It does."

int main(void) {
    // Check out that type: pointer to a char. The string variable s is actually a pointer to the
    // first character in that string, namely the H.
    char *s = "hello, world!";
    printf("%s\n", s);

    // String Variables as Arrays
    char s2[] = "hello, world!";
    // This means you can use array notation to access characters in a string.
    for (int i = 0; i < 13; i++) {
        // Note that we're using the format specifier %c to print a single character.
        printf("%c", s2[i]);
    }
    printf("\n");

    // Also, check this out. The program will still work fine if we change the definition of s3 to
    // the a char* type:
    char *s3 = "Hello, world!";
    for (int i = 0; i < 13; i++) {
        printf("%c", s3[i]);
    }
    printf("\n");

    printf("%zu\n", sizeof(int));
    printf("%zu\n", sizeof(*s3));
    printf("%lu\n", strlen(s3));

    printf("%d\n", my_strlen(s3));

    // Copying a String
    // You can't copy a string though the assignment operator (=). All that does is make a copy of
    // the pointer to the first character...so you end up with two pointers to the same thing:
    {
        char s[] = "hello, world!";
        char *t;

        // This makes a copy of the pointer, not a copy of the string!
        t = s;

        // We modify t
        t[0] = 'z';

        // But printing s shows the modification!
        // Because t and s point to the same string!
        printf("%s\n", s);
        printf("%s\n", t);
    }

    // If you want to make a copy of a string, you have to copy it a byte at a time - this means
    // that you're going to take the individual bytes of the string from one place in memory and
    // duplicate them somewhere else in memory. This is made easier with strcpy() function.
    {
        char s[] = "hello, world!";
        char t[100];

        // This makes a copy of the string!
        strcpy(t, s);

        // We modify t
        t[0] = 'z';

        printf("%s\n", s);
        printf("%s\n", t);
    }
}

int my_strlen(char *s) {
    int count = 0;

    while (s[count] != '\0') {
        count++;
    }

    return count;
}
