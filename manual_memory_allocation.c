#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Manual Memory Allocation
//
// You can tell C explicitly to allocate for you a certain number of bytes that you can use as you
// please. And these bytes will remain allocated until you explicitly free the memory.
//
// It's important to free the memory you're done with! if you don't, we call that a memory leak and
// your process will continue to reserve that memory until it exits.
//
// If you manually allocated it, you have to manually free it when you're done with it.

char *readline(FILE *fp) {
    int offset = 0;
    int bufsize = 4;
    char *buf;
    int c;

    buf = malloc(bufsize);

    if (buf == NULL) {
        return NULL;
    }

    while (c = fgetc(fp), c != '\n' && c != EOF) {
        if (offset == bufsize - 1) {
            bufsize *= 2;

            char *new_buf = realloc(buf, bufsize);

            if (new_buf == NULL) {
                free(buf);
                return NULL;
            }

            buf = new_buf;
        }

        buf[offset++] = c;
    }
    printf("%d\n", offset);

    if (c == EOF && offset == 0) {
        free(buf);
        return NULL;
    }

    if (offset < bufsize - 1) {
        char *new_buf = realloc(buf, offset + 1);

        if (new_buf != NULL) {
            buf = new_buf;
        }

        printf("buf size: %lu\n", sizeof(buf));
    }

    buf[offset] = '\0';

    return buf;
}

int main(void) {
    // Allocating and Deallocating, malloc() and free()
    //
    // The malloc() function accepts a number of bytes to allocate, and returns a void pointer to
    // that block of newly-allocated memory.
    //
    // Since it's a void*, you can assign it into whatever pointer type you want... normally this
    // will correspond in some way to the number of bytes you're allocation.
    {
        /* int *p = malloc(sizeof(int)); */
        int *p = malloc(sizeof *p); // *p is an int, so same as sizeof(int)
        *p = 12;                    // Store something there

        printf("%d\n", *p); // Print it: 12

        free(p); // All done with that memory

        // One more thing you'll commonly see takes advantages of the fact that sizeof can give you
        // the size of the result type of any constant expression. So you could put a variable name
        // in there, too, and use that. Here's an example of that, just like the previous one:
        // int *p = malloc(sizeof *p);
    }

    // Error Checking
    //
    // All the allocation functions return a pointer to the newly-allocated stretch of memory, or
    // NULL if the memory cannot be allocated for some reason.
    {
        int *x;

        x = malloc(sizeof(int) * 10);

        if (x == NULL) {
            fprintf(stderr, "Error allocatin 10 ints\n");
        }

        free(x);

        // Here's a common pattern that you'll see, where we do the assignment and the condition on
        // the same line:
        {
            int *x;

            if ((x = malloc(sizeof(int) * 10)) == NULL) {
                fprintf(stderr, "Error allocatin 10ints\n");
            }

            free(x);
        }
    }

    // Allocatin Space for an Array
    {
        // Note: There's no initialization done on the newly-allocated memory - it's full of
        // garbage. clean it with memset() if you want to, or see calloc()
        int *p = malloc(sizeof(int) * 10);

        // Assign nthem values 0-45:
        /* for (int i = 0; i < 10; i++) { */
        /*     *(p + i) = i * 5; // same as p[i] = i * 5; */
        /* } */

        for (int i = 0; i < 10; i++) {
            /* printf("%d\n", *(p + i)); // same sa p[i]; */
            printf("%d\n", p[i]);
        }

        free(p);
    }

    // An Alternative: calloc()
    //
    // This is another allocation function that works similarly to malloc(), with two key
    // differennces:
    //
    // 1. Instead of a single argument, you pass the size of one element, and the number of elements
    // you wish to allocate. It's like it's made for allocation arrays.
    // 2. It clears the memory to zero.
    //
    // You still use free() to deallocate memory obtained through calloc().
    {
        int *p = calloc(10, sizeof(int));

        for (int i = 0; i < 10; i++) {
            printf("%d\n", *(p + i));
        }

        free(p);
    }

    // Changing Allocated Size with realloc()
    //
    // It takes a pointer to some previously-allocated memory (by malloc() or calloc()) and a new
    // size for the memory region to be.
    //
    // It then grows or shrinks that memory, and returns a pointer to it. Sometimes it might return
    // the same pointer (if the data didn't have to be copied elsewhere), or it might return a
    // different one (if the data did have to be copied).
    //
    // Be sure when you call realloc(), you specify the number of bytes to allocate.
    {
        float *p = malloc(sizeof *p * 20); // same with sizeof(float)

        for (int i = 0; i < 20; i++) {
            *(p + i) = i / 20.0;
        }

        float *new_p = realloc(p, sizeof *p * 40);
        if (new_p == NULL) {
            fprintf(stderr, "Something went wrong");
            return 1;
        }

        p = new_p;

        for (int i = 20; i < 40; i++) {
            p[i] = 1.0 + (i - 20) / 20.0;
        }

        for (int i = 0; i < 40; i++) {
            printf("%d: %f\n", i, p[i]);
        }

        free(p);
    }

    {
        FILE *fp = fopen("quote.txt", "r");

        char *line;

        while ((line = readline(fp)) != NULL) {
            printf("%s\n", line);
            free(line);
        }

        fclose(fp);
    }

    // Realloc with NULL
    {
        // These two line are equivalent
        char *p = malloc(3490);
        char *q = realloc(NULL, 3490);

        // That could be convenient if you have some kind of allocation loop and you don't want to
        // special-case the first malloc()

        int *a = NULL;
        int length = 0;
        bool done = false;

        while (!done) {
            length += 10;
            p = realloc(p, sizeof *p * length);
        }
    }
}
