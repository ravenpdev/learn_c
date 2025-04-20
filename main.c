#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// #include <stdbool.h> // not needed in c23

// Function Prototypes
//
// Without function prototype you had to define the function before you used it,
// otherwise the compiler wouldn't know about it ahead of time, and would bomb out with an error.
//
// You can notify the compiler in advance that you'll be using a function of a certain type
// that has a certain parameter list. That way the function can be defined anywhere (even in a
// different file), as long as the function prototype has been declared before you call that
// function.
int increment(int);

int plus_one(int n) { return n + 1; }

// Empty Parameter Lists
//
// Always use "void" to indicate that a function takes no parameters. There's never a reason
// to skip this in modern code.
//
// Leaving void out of the prototype indicates to the compiler that there is no additional
// information about the parameters to the funtion. It effectively turns off all that
// type checking.

// EVERYTHING you pass to a function WITHOUT EXCEPTION is copied into its
// correspondinng parameter, and the function operates on that local copy,
// NO MATTER WHAT. Remember that, even when we're talking about this so-called
// passing by reference.

// main is a function!
// it returns an int.
//
// But what's this void thing? This is a keyword that's used to indicate
// that the function accepts no argument
//
// You can also return void to indicate that you don't return a value:
int main(void) {
    /* printf("Hello, World!\n"); */

    /* int i; */
    /* float f; */
    /* char c; */
    /* char *s; */

    /* i = 2; */
    /* f = 3.14; */
    /* c = 'A'; */
    /* s = "Hello World"; */

    /* printf("%s i = %d, f = %f and c = %c!\n", s, i, f, c); */

    // In c23, you get actual boo, true, and false.
    // Before that, if you have a modern-enough version of C,
    // you can #include <stdbool.h> to get the same thing.
    /* bool isLearning = true; */

    /* if (isLearning) { */
    /*     printf("x is  true!\n"); */
    /* } */

    /* printf("%d\n", true == 12); */

    /* int x = 10; */
    /* int y = 0; */

    /* y += x > 10 ? 17 : 37; */

    /* printf("%d\n", y); */

    // It's important to note that the ternary operator isn't flow control like
    // the if statement is. It's just an expression that evaluates to a value.
    /* printf("The number %d is %s.\n", x, x % 2 == 0 ? "even" : "odd"); */

    // Pr-and-Post Increment-and-Decrement
    //
    // With pre-increment and pre-decrement, the value of the variable is
    // incremented or decremented before the expression is evaluated.
    //
    // With post-increment and post-decrement, the value of the expression is
    // first computed with the value as-is, and then the value is incremented or
    // decremented after the value of the expression has been determined.
    /* int i1 = 0; */
    /* printf("The value of i1 = %d using pre\n", ++i1); */
    /* int i2 = 0; */
    /* printf("The value of i2 = %d using post\n", i2++); */

    /* for (x = 0; x < 10; x++) { */
    /*     printf("i is %d\n", x); */
    /* } */

    // The Comma Operator
    // This is an uncommonly-used way to separate expressions that will run
    // left to right
    {
        /* int x = 10, y = 10; // First assign 10 to x, then 20 to y */
        /* printf("x = %d, y = %d\n", x, y); */

        // Seems a bit silly, since you could just replace the comma with a
        // semicolon, right?
        /* x = 10; y = 20; // First assign 10 to x, then 20 to y */
        // But that's a little different. The latter is two separate
        // expressions, while the former is a single expression!

        // With the comma operator, the value of the comma expression is the
        // value of the rightmost expression:
        /* x = (1, 2, 3); */
        /* printf("x is %d\n", x); */

        // One common place the comma operator is used is in for loops to do
        // multiple things in each section of the statement:
        /* int i; */
        /* int j; */
        /* for (i = 0, j = 10; i < 100; i++, j++) */
        /*     printf("%d, %d\n", i, j); */
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

        /* int a = 10; */

        /* if (a <= 10) */
        /*     printf("Success!\n"); */
    }

    // Boolean Operators
    // && and
    // || or
    // !  not
    {
        /* int a = 10; */
        /* int y = 25; */

        /* if (x <= 10 && y >= 20) */
        /*     printf("Doing something!\n"); */

        /* if (!(x < 10)) */
        /*     printf("x is not less than 10\n"); */
        // ! has higher precedence than the other Boolean operators, so we have
        // to use parentheses in that case.
    }

    // The sizeof Operator
    //
    // This operator tells you the size (in bytes) that a particular variable or
    // data type uses in memory.
    //
    // More particularly, it tells you the size (in bytes) that the type of a
    // particular expression (which might be just a single variable) uses in
    // memory.
    //
    // This can be different on different systems, except for char and its
    // variants (which are always 1 byte).
    //
    // C has a special type to represent the return value from sizeof. it's
    // size_t, pronounce "size tee". All we know is that it's an unsigned
    // integer type that can hold the size in bytes of anything you can give to
    // sizeof.
    //
    // size_t shows up a lot of different places where counts of things are
    // passed or returned. Think of it as a value that represents a count.
    //
    // Remember: it's the size in bytes of the type of the expression, not the
    // size of the expression itself.
    //
    // Note: sizeof is a compile-time operation. The result of the expression is
    // determined entirely at compile-time, not at runtime.
    {
        // %zu is the format specifier for type size_t
        // If your compiler balks at the "z" part, leave it off
        /* int x = 0; */
        /* printf("the sizeof x in bytes is %zu\n", sizeof x); */
        /* float f = 0.0; */
        /* printf("the sizeof f in bytes is %zu\n", sizeof y); */
        /* char c = 'A'; */
        /* printf("the sizeof c in bytes is %zu\n", sizeof c); */
        /* char *name = "raven paragas"; */
        /* printf("the sizeof name in bytes is %zu\n", sizeof name); */

        // Where we'll see you can take the sizeof a type (not the parentheses
        // are required around a type name, unlike an expression):
        /* printf("%zu\n", sizeof(int)); */
        /* printf("%zu\n", sizeof(char)); */
    }

    // Flow Control
    {
        /* int x = 10; */

        /* if (x == 10) { */
        /*     printf("x is 10\n"); */
        /* } */

        /* // Weird Stuff Happen :) */
        /* if (x == 10) */
        /*     printf("This happens if x is 10\n"); */
        /*     printf("This happens ALWAYS\n"); */
    }

    // The if-else statement
    {
        /* int i = 99; */

        /* if (i == 10) { */
        /*     printf("i is 10!.\n"); */
        /* } else if (i == 99) { */
        /*     printf("I is decidedly not 10.\n"); */
        /*     printf("Which irritates me a little, frankly.\n"); */
        /* } else { */
        /*     printf("i is some crazy number I've never heard of.\n"); */
        /* } */
    }

    // The while statement
    {
        /* int i = 0; */

        /* while (i < 10) { */
        /*     printf("i is now %d!\n", i); */
        /*     i++; */
        /* } */

        /* printf("All done!\n"); */

        // A not-uncommon use of while is for infinite loops where you repeat
        // while true:
        /* while (1) { */
        /*     printf("1 is always true, so this repeats forever.\n"); */
        /* } */
    }

    // The do-while statement
    {
        /* int i = 10; */

        // This is executed once, because the loop condition is not checked
        // after the body of the loop runs:
        /* do { */
        /*     printf("do-while: i is %d\n", i); */
        /*     i++; */
        /* } while (i < 10); */
        /* printf("All done!\n"); */

        /* srand(time(NULL)); */

        /* int r; */
        /* do { */
        /*     r = rand() % 100; // Get random number between 0 and 99 */
        /*     printf("%d\n", r); */
        /* } while (r != 37); */
    }

    // The for statement
    {
        srand(time(NULL));

        int i = 0;
        int r = 0;
        for (i = 0; i < 10; i++) {
            r = rand() % 100;
            printf("%d: %d\n", i, r);
        }

        // You can use the comma operator to do multiple things in each caluse
        // of the for loop!
        int x;
        int y;
        for (x = 0, y = 999; x < 10; x++, y--) {
            printf("%d, %d\n", x, y);
        }

        // An empty for will run forever:
        /* for(;;) { */
        /*     printf("I will print this again and again and again\n"); */
        /*     printf("for all eternity until the heat-death of the
         * universe.\n");
         */

        /*     printf("Or until you hit CTRL-C.\n"); */
        /* } */
    }

    // The switch statement
    //
    // switch is often faster to jump to the correct code (though the spec makes
    // no such guarantee) if-else can do things like relational conditionals
    // like < and >= and floating point and other types, whi switch cannot.
    //
    // There's one more neat thing about switch that you sometimes see that is
    // quite interesting: fall through
    {
        int goat_count = 2;

        switch (goat_count) {
        case 0:
            printf("You have no goats.\n");
            break;
        case 1:
            printf("You have a singular goat.\n");
            break;
        case 2:
            printf("You have a brace of goats.\n");
            break;
        default:
            printf("You have a bona fide plethora of goats!\n");
            break;
        }

        int x = 1;

        switch (x) {
        case 1:
            printf("1\n");
            // Fall through
        case 2:
            printf("2\n");
            break;
        case 3:
            printf("3\n");
            break;
        }

        // One loophole-ish thing here is that you can use character types
        // because those are secretly integers themeselves. So this is perfectly
        // acceptable:
        //
        // Finally, you can use enums in switch since they are also integer
        // types.

        char c = 'b';

        switch (c) {
        case 'a':
            printf("It's 'a'!\n");
            break;
        case 'b':
            printf("It's 'b'!\n");
            break;
        case 'c':
            printf("It's 'c'!\n");
            break;
        }
    }

    // Functions
    {
        int x = plus_one(2);
        printf("x is now %d\n", x);

        // We can call increment(int) here before it's definition because the
        // prototype has already been declared, above!
        int y = 0;
        y = increment(y);
        printf("y is %d\n", y);
    }
}

int increment(int x) { return x += 1; }
