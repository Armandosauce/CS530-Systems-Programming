Armando Perez
armandoperez0001@gmail.com

There were three programs to complete in CS530Assignment 1. This README file briefly explains the purpose of each one and how it was implemented.

prog1_1.c
=========

prog1_1.c is to be compiled using the following line:

    gcc prog1_1.c -o prog1_1

and run using the following command line prompt:
 
    ./prog1_1 hello
    
where "hello" is the target filename. The programs takes in an .elf file and will output its CRC32 checksum as an 8 digit hex number.

For prog1_1.c, it is simple to obtain the length of the .elf input file in bytes by seeking to the end of the file, then using the call to ftell() with the same file pointer. After which, the file pointer is reset so that the entire elf file can be read into buff using the same length that was discovered by the previous process.

The same crc32 checksum function was used for all three of the programs, although program 3 was unsuccessful.

The crc32 checksum algorithm was accomplished by using a "makeshift" register that would bitwise shift once to the left and shift on the most significant bit of the buffer array (i.e. the data from the elf files). It was difficult to achieve desired behavior as individual bits needed to be checked for a value of 1 or 0. C does not natively support features like this (at least to my knowledge) so it needed to be implemented from scratch. The crc32 function used by all three programs takes advantage of the fact that a character is 1 byte, or 8 bits. By the use of nested "for loops", the algorithm will take a character from the input buffer, and bitwise shift it once to the left after determining the value of the most significant bit. This process is repeated in the inner loop 8 times, after which the next character is read in from the buffer array, and the process repeats.


prog1_2.c
=========

prog1_2.c is to be compiled using the following line:

    gcc prog1_2.c -o prog1_2

and run using the following command line prompt:

    ./prog1_2 hello
    
where "hello" is the target filename. The programs takes in an .elf file and will output the CRC32 checksum of ONLY the program header table as an 8 digit hex number.

For prog1_2.c, the code takes advantage of the fact that the program header will always begin at the same byte and have the same length for EVERY .elf file. As the .elf file format will pad fields such that they fulfill some required number of hex bytes. Because of this, the code was simplified to only use a static length of 504 bytes. While this made the result of program 2 faster to achieve, it ultimately made program 3, more difficult. And the static size of bytes had to be scrapped.

prog1_3.c
=========

prog1_3.c is incomplete, but its purpose was to take two command line arguments and seek to the section row in the section header provided as the second command line argument.

prog1_3.c is to be compiled using the following line:

    gcc prog1_3.c -o prog1_3
    
and run using the following command line prompt:

    ./prog1_2 hello .shstrtab
    
where "hello" is the target filename and ".shstrtab" is the section row name in the section header.

The main function of prog1_3.c has been commented out to prevent an infinite loop within the autograder. As such, there is no output other than the required Assignment header that prints at the start.

