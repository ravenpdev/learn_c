#include <stdio.h>

// The FILE* Data Type
//
// When we do any kind of I/O in C, we do so through a piece of data that you get in the form of a
// FILE* type. This FILE* holds all the information needed to communicate with the I/O subsystem
// about which file you have open, where you are in the file, and so on.
//
// The spec refers to these as streams, i.e. a stream of data from a file or from any source. I'm
// going to use "files" and "streams" interchangeably, but really you should think of a "file" as a
// special case of a "stream". There are ways to stream data into a program than just reading from a
// file.
//
// The three streams that are already open for you and ready for use
// stdin - Standard Input, generally the keyboard by default
// stdout - Stanndard Output, generally the screen by default
// stderr - Standard Error, generally the screen by default, as well

int main(void) {

    // We've actually been using these implicitly already, it turns out. For example, these two
    // calls are the same:
    {
        printf("Hello, world!\n");
        fprintf(stdout, "Hello, world!\n");
    }

    // Reading Text Files
    // Streams are largely categorized two different ways: text and binary
    //
    // Text streams are allowed to do significant translation of the data, most notably translations
    // of newlines to their different representations. Text files are logically a sequence of linnes
    // separated by newlines. To be portable, your input data should always end with a newline.
    //
    // But the general rule is that if you're able to edit the file in a regular text editor. it's a
    // text file. Otherwise, it's binary.
    {
        FILE *fp;
        int c;

        // fopen will return NULL if something goes wrong, like file-not-found
        fp = fopen("hello.txt", "r");

        while ((c = fgetc(fp)) != EOF) {
            printf("%c", c);
        }

        // All streams are automatically closed when the program exits. but it's good form and good
        // housekeepingn to explicitly close ay files yourself when done with them.
        fclose(fp);

        // The FILE* keeps track of our position in the file. So subsequent calls to fgetch() would
        // get the next character in nthe file, and then the next, until the end.
    }

    // The Eend of File: EOF
    // There is a special character defined as macro: EOF. This is what fetch() will return when the
    // end of the file has been reached and you've attempted to read another character.
    //
    // Turns out EOF is the reason why fgetc() and functions like it return an int isntead of a
    // char. EOF isn't a character proper, and its value likely falls outside the range of char.
    // Since fgetc() needs to be able to return any byte and EOF, it needs to be a weider type than
    // can hold more values.

    // Reading a Line at a Time
    {
        FILE *fp;
        char s[1024];
        int linecount = 0;

        fp = fopen("quote.txt", "r");

        if (fp == NULL) {
            fprintf(stderr, "Something went wrong\n");
        }

        while (fgets(s, sizeof s, fp) != NULL) {
            printf("%d: %s", ++linecount, s);
        }
        fclose(fp);
    }

    // Formatted Input
    {
        FILE *fp;
        char name[1024];
        float length;
        int mass;

        fp = fopen("whales.txt", "r");

        if (fp == NULL) {
            fprintf(stderr, "Something went wrong\n");
        }

        while (fscanf(fp, "%s %f %d", name, &length, &mass) != EOF) {
            printf("%s whale, %d tonnes, %.f meters\n", name, mass, length);
        }

        fclose(fp);
    }

    // Writing Text Files
    //
    // fgetc(), fgets(), fscanf() to read text streams, we can use fputc(), fputs(), and fprintf()
    // to write text streams.
    {
        FILE *fp;
        int x = 32;

        fp = fopen("output.txt", "w");

        if (fp == NULL) {
            fprintf(stderr, "Unable to open file");
        }

        fputc('B', fp);
        fputc('\n', fp);
        fprintf(fp, "x = %d\n", x);
        fputs("Hello, world!\n", fp);

        fclose(fp);

        fp = fopen("output.txt", "r");
        char line[1024];

        if (fp == NULL) {
            fprintf(fp, "Unable to open file");
        }

        while (fgets(line, sizeof(line), fp) != NULL) {
            printf("%s\n", line);
        }
        fclose(fp);
    }

    // Binary File I/O
    {
        FILE *fp;
        unsigned char bytes[6] = {5, 37, 0, 88, 255, 12};

        fp = fopen("output.bin", "wb"); // wb mode for "write binary"

        // In the all to fwrite, the arguments area:
        //
        // * Pointer to data to write
        // * Size of each "piece" of data
        // * Count of each "piece" of data
        // * FILE*
        fwrite(bytes, sizeof(char), 6, fp);

        // Those two middle arguments to fwrite() are pretty odd. But basically what we want to tell
        // the function is, "We have items that are this big, and we want to write that many of
        // them.". This makes it convenient if you have a record of a fixed length, and you have a
        // bunch of them in an narray.

        fclose(fp);
    }

    // Read Binary File I/O
    {
        FILE *fp;
        unsigned char c;

        fp = fopen("output.bin", "rb"); // rb for "read binary"
        while (fread(&c, sizeof(char), 1, fp) > 0) {
            printf("%d\n", c);
        }
        fclose(fp);
    }

    // struct and Number caveats
    //
    // As we saw in the structs sections, the compiler is free to add padding to a struct as it sees
    // fit. And different compilers might do this differently. And the sample compiler on different
    // architecture could do it differently. And the same compiler on the same architectures could
    // do it differently.
    //
    // What I'm getting at is this: it's not portable to jsut fwrite() an entire struct out to a
    // file when you don't know where the padding will end up.
    //
    // Numbers!
    //
    // Turns out all architectures don't represent numbers in memory the same way.
    //
    // Let's look at simple fwrite() of a 2-byte number. We'll write it in hex so each byte is
    // clear. The most significant byte will have the value 0x12 and the least significant will have
    // the value 0x34.
    //
    // Buf if I run this on my machine and hexdump the result, I get:
    // 34 12
    //
    // The're reversed! What gives?
    // This has something to do with what's called the endianess of the architecture. Some write the
    // most significant bytes first, and some the least significant bytes first.
    //
    // This means that if you write a multibyte number out straight from meory, you can't do it in a
    // portable way.
    //
    // A similar problem exists with floating point. Most systems use the same format for their
    // floating point numbers, but some do not. No guarantees!
    //
    // So...how can we fix all these problems with numbers and structs to get our data written in a
    // portable way?
    //
    // The summary is to serialize the data, which is a general term that means to take all the data
    // and write it out in a format that you control, that is well-known, and programmable to work
    // the same way on all platforms.
    //
    // AS you might imagine, this is a solved problem. There are bunch of serialization libraries
    // you can take advantage of, such as Google's protocol buffers, out there and ready to use.
    // They will take care of all the gritty details for you, and even will allow data from your C
    // programs to interoperate with other languages that support the same serialization methods.
    //
    // Do yourself and everyone a favor! Serialize your binary data when you write it to a stream!
    {
        FILE *fp;

        fp = fopen("hex.txt", "wb");

        unsigned short v = 0x1234;

        fwrite(&v, sizeof v, 1, fp);

        printf("Done writing hex to a hex.txt\n");

        fclose(fp);
    }
}

// Decimal to Hex
// 4660
//
// 291 - 4
// 18 - 3
// 1 - 2
// 0 - 1
//
// 1234

// Hex to Decimal
// 1 * 16 * 16 * 16 = 4096
// 2 *16 * 16 = 512
// 3 * 16 = 48
// 4 * 1 = 4
// 0x1234 = 4660
