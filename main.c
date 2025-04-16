#include<stdio.h>
// #include <stdbool.h> // not needed in c23

int main() {
    printf("Hello, World!\n");

    int i;
    float f;
    char c;
    char *s;

    i = 2;
    f = 3.14;
    c = 'A';
    s = "Hello World";

    printf("%s i = %d, f = %f and c = %c!\n", s, i, f, c);


    // In c23, you get actual boo, true, and false.
    // Before that, if you have a modern-enough version of C,
    // you can #include <stdbool.h> to get the same thing.
    bool isLearning = true;

    if (isLearning) {
        printf("x is  true!\n");
    }

    printf("%d\n", true == 12);

    int x = 10;
    int y = 0;

    y += x > 10 ? 17 : 37;

    printf("%d\n", y);
    
    // It's important to note that the ternary operator isn't flow control like the
    // if statement is. It's just an expression that evaluates to a value.
    printf("The number %d is %s.\n", x, x % 2 == 0 ? "even" : "odd");

    // Pr-and-Post Increment-and-Decrement
    //
    // With pre-increment and pre-decrement, the value of the variable is incremented
    // or decremented before the expression is evaluated.
    //
    // With post-increment and post-decrement, the value of the expression is first
    // computed with the value as-is, and then the value is incremented or decremented
    // after the value of the expression has been determined.
    int i1 = 0;
    printf("The value of i1 = %d using pre\n", ++i1);
    int i2 = 0;
    printf("The value of i2 = %d using post\n", i2++);

    for (x = 0; x < 10; x++) {
        printf("i is %d\n", x);
    }


    // The Comma Operator
    // This is an uncommonly-used way to separate expressions that will run
    // left to right
    {
        int x = 10, y = 10; // First assign 10 to x, then 20 to y
        printf("x = %d, y = %d\n", x, y);

        // Seems a bit silly, since you could just replace the comma with a semicolon, right?
        x = 10; y = 20; // First assign 10 to x, then 20 to y
        // But that's a little different. The latter is two separate expressions, while the
        // former is a single expression!

        // With the comma operator, the value of the comma expression is the value of the
        // rightmost expression:
        x = (1, 2, 3);
        printf("x is %d\n", x);

        // One common place the comma operator is used is in for loops to do multiple
        // things in each section of the statement:
        int i;
        int j;
        for (i = 0, j = 10; i < 100; i++, j++)
            printf("%d, %d\n", i, j);
    }

    // Conditional Operators
    {
        /*
        * a == b; // True if a is equivalent to b
        * a != b; // True if a is not equivalent to b
        * a < b; // True if a is less than b
        * a > b; // True if a is greater than b
        * a <= b; // True if a is less than or equal to b
        * a >= b; // True if a is greater than or equal to b
        */

        int a = 10;

        if (a <= 10)
            printf("Success!\n");
    }

    // Boolean Operators
    // && and
    // || or
    // !  not
    {
        int a = 10;
        int y = 25;

        if (x <= 10 && y >= 20)
            printf("Doing something!\n");

        if (!(x < 10))
            printf("x is not less than 10\n");
        // ! has higher precedence than the other Boolean operators, so we have to use
        // parentheses in that case.
    }

    // The sizeof Operator
    //
    // This operator tells you the size (in bytes) that a particular variable or data type
    // uses in memory.
    //
    // More particularly, it tells you the size (in bytes) that the type of a particular
    // expression (which might be just a single variable) uses in memory.
    //
    // This can be different on different systems, except for char and its variants
    // (which are always 1 byte).
    //
    // C has a special type to represent the return value from sizeof. it's size_t,
    // pronounce "size tee". All we know is that it's an unsigned integer type that
    // can hold the size in bytes of anything you can give to sizeof.
    //
    // size_t shows up a lot of different places where counts of thingns are passed or returned.
    // Think of it as a value that represents a count.
    //
    // Remember: it's the size in bytes of the type of the expression, not the size of
    // the expression itself.
    //
    // Note: sizeof is a compile-time operation. The result of the expression is determined
    // entirely at compile-time, not at runtime.
    {
        // %zu is the format specifier for type size_t
        // If your compiler balks at the "z" part, leave it off
        int x = 0;
        printf("the sizeof x in bytes is %zu\n", sizeof x);
        float f = 0.0;
        printf("the sizeof f in bytes is %zu\n", sizeof y);
        char c = 'A';
        printf("the sizeof c in bytes is %zu\n", sizeof c);
        char *name = "raven paragas";
        printf("the sizeof name in bytes is %zu\n", sizeof name);

        // Where we'll see you can take the sizeof a type (not the parentheses are
        // required around a type name, unlike an expression):
        printf("%zu\n", sizeof(int));
        printf("%zu\n", sizeof(char));
    }
}
