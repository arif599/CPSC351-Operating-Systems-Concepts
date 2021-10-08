# Project 2 - Implementing the Memory API

## Source files:

- `allocator.cpp` (custom memory allocator)

- `allocator.h` (header file containing class definition)

- `testalloc.cpp` (client program that uses the allocator)

## Makefile

To run the make file, enter `make`

To run the example program, enter `make test` or `./testalloc`

## Testing

The program `testalloc` tests the `Allocator` class with the following
scenario:

1. Create an allocator object with the default memory size of 4KB.

2. Create block A of size 1KB, filling it with the letter 'A.'

3. Create block B of size 2KB, filling it with the letter 'B.'

4. Try to create block C of size 2 KB. This will fail since 3KB are already in
   use.

5. Verify that the contents of blocks A and B are intact, then free Block B

6. Try again to create block C. Since B has been freed, this should succeed.

7. Free blocks A and C.

8. Dump the contents of the allocator's memory. *Note*: when debugging, you
   may wish to do this earlier in the program as well.

9. Destroy the allocator object.

*Note*: While `testalloc` makes for a good sanity-check, do not rely
exclusively on this test. I will test your memory allocator in more
complicated scenarios as well.
