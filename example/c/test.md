# Chapter 2. Binary and Number Representation

## Binary — the basis of computing

### Binary Theory

#### Introduction
Binary is a base-2 number system that uses two mutually exclusive states to represent information. A binary number is made up of elements called bits where each bit can be in one of the two possible states. Generally, we represent them with the numerals 1 and 0. We also talk about them being true and false. Electrically, the two states might be represented by high and low voltages or some form of switch turned on or off.

We build binary numbers the same way we build numbers in our traditional base 10 system. However, instead of a one's column, a 10's column, a 100's column (and so on) we have a one's column, a two's columns, a four's column, an eight's column, and so on, as illustrated below.

Table 2.1. Binary

2... | 2<sup>6</sup> | 2<sup>5</sup> | 2<sup>4</sup> | 2<sup>3</sup> | 2<sup>2</sup> | 2<sup>1</sup> | 2<sup>0</sup>
-----|----|----|----|----|----|----|----
...  | 64 | 32 | 16 | 8  | 4  | 2  | 1

For example, to represent the number 203 in base 10, we know we place a 3 in the 1's column, a 0 in the 10's column and a 2 in the 100's column. This is expressed with exponents in the table below.

Table 2.2. 203 in base 10

10<sup>2</sup> |10<sup>1</sup> | 10<sup>0</sup>
----|----|----
2   | 0  | 3

Or, in other words, 2 × 10<sup>2</sup> + 3 × 10<sup>0</sup> = 200 + 3 = 203. To represent the same thing in binary, we would have the following table.

Table 2.3. 203 in base 2

2<sup>7<sup> |2<sup>6<sup> |2<sup>5<sup> |2<sup>4<sup> |2<sup>3<sup> |2<sup>2<sup> |2<sup>1<sup> |2<sup>0<sup>
--|--|--|--|--|--|--|--
1 |1 |0 |0 |1 |0 |1 |1

That equates to 2<sup>7</sup> + 2<sup>6</sup> + 2<sup>3</sup>+2<sup>1</sup> + 2<sup>0</sup> = 128 + 64 + 8 + 2 + 1 = 203.

## The basis of computing
You may be wondering how a simple number is the basis of all the amazing things a computer can do. Believe it or not, it is! The processor in your computer has a complex but ultimately limited set of instructions it can perform on values such as addition, multiplication, etc. Essentially, each of these instructions is assigned a number so that an entire program (add this to that, multiply by that, divide by this and so on) can be represented by a just a stream of numbers. For example, if the processor knows operation 2 is addition, then 252 could mean "add 5 and 2 and store the output somewhere". The reality is of course much more complicated (see Chapter 3, Computer Architecture) but, in a nutshell, this is what a computer is.

In the days of punch-cards, one could see with their eye the one's and zero's that make up the program stream by looking at the holes present on the card. Of course this moved to being stored via the polarity of small magnetic particles rather quickly (tapes, disks) and onto the point today that we can carry unimaginable amounts of data in our pocket.

Translating these numbers to something useful to humans is what makes a computer so useful. For example, screens are made up of millions of discrete pixels, each too small for the human eye to distinguish but combining to make a complete image. Generally each pixel has a certain red, green and blue component that makes up it's display color. Of course, these values can be represented by numbers, which of course can be represented by binary! Thus any image can be broken up into millions of individual dots, each dot represented by a tuple of three values representing the red, green and blue values for the pixel. Thus given a long string of such numbers, formatted correctly, the video hardware in your computer can convert those numbers to electrical signals to turn on and off individual pixels and hence display an image.

As you read on, we will build up the entire modern computing environment from this basic building block; from the bottom-up if you will!

## Bits and Bytes
As discussed above, we can essentially choose to represent anything by a number, which can be converted to binary and operated on by the computer. For example, to represent all the letters of the alphabet we would need at least enough different combinations to represent all the lower case letters, the upper case letters, numbers and punctuation, plus a few extras. Adding this up means we need probably around 80 different combinations.

If we have two bits, we can represent four possible unique combinations (00 01 10 11). If we have three bits, we can represent 8 different combinations. In general, with n bits we can represent 2n unique combinations.

8 bits gives us 28 = 256 unique representations, more than enough for our alphabet combinations. We call a group of 8 bits a byte. Guess how big a C char variable is? One byte.

## ASCII
Given that a byte can represent any of the values 0 through 255, anyone could arbitrarily make up a mapping between characters and numbers. For example, a video card manufacturer could decide that 1 represents A, so when value 1 is sent to the video card it displays a capital 'A' on the screen. A printer manufacturer might decide for some obscure reason that 1 represented a lower-case 'z', meaning that complex conversions would be required to display and print the same thing.

To avoid this happening, the American Standard Code for Information Interchange or ASCII was invented. This is a 7-bit code, meaning there are 27 or 128 available codes.

The range of codes is divided up into two major parts; the non-printable and the printable. Printable characters are things like characters (upper and lower case), numbers and punctuation. Non-printable codes are for control, and do things like make a carriage-return, ring the terminal bell or the special NULL code which represents nothing at all.

127 unique characters is sufficient for American English, but becomes very restrictive when one wants to represent characters common in other languages, especially Asian languages which can have many thousands of unique characters.

To alleviate this, modern systems are moving away from ASCII to Unicode, which can use up to 4 bytes to represent a character, giving much more room!

## Parity
ASCII, being only a 7-bit code, leaves one bit of the byte spare. This can be used to implement parity which is a simple form of error checking. Consider a computer using punch-cards for input, where a hole represents 1 and no hole represents 0. Any inadvertent covering of a hole will cause an incorrect value to be read, causing undefined behaviour.

Parity allows a simple check of the bits of a byte to ensure they were read correctly. We can implement either odd or even parity by using the extra bit as a parity bit.

In odd parity, if the number of 1's in the 7 bits of information is odd, the parity bit is set, otherwise it is not set. Even parity is the opposite; if the number of 1's is even the parity bit is set to 1.

In this way, the flipping of one bit will case a parity error, which can be detected.

XXX more about error correcting

## 16, 32 and 64 bit computers
Numbers do not fit into bytes; hopefully your bank balance in dollars will need more range than can fit into one byte! Modern architectures are at least 32 bit computers. This means they work with 4 bytes at a time when processing and reading or writing to memory. We refer to 4 bytes as a word; this is analogous to language where letters (bits) make up words in a sentence, except in computing every word has the same size! The size of a C int variable is 32 bits. Modern architectures are 64 bits, which doubles the size the processor works with to 8 bytes.

## Kilo, Mega and Giga Bytes
Computers deal with a lot of bytes; that's what makes them so powerful! We need a way to talk about large numbers of bytes, and a natural way is to use the "International System of Units" (SI) prefixes as used in most other scientific areas. So for example, kilo refers to 103 or 1000 units, as in a kilogram has 1000 grams.

1000 is a nice round number in base 10, but in binary it is 1111101000 which is not a particularly "round" number. However, 1024 (or 210) is a round number — (10000000000 — and happens to be quite close to the base 10 meaning value of "kilo" (1000 as opposed to 1024). Thus 1024 bytes naturally became known as a kilobyte. The next SI unit is "mega" for 106 and the prefixes continue upwards by 103 (corresponding to the usual grouping of three digits when writing large numbers). As it happens, 220 is again close to the SI base 10 definition for mega; 1048576 as opposed to 1000000. Increasing the base 2 units by powers of 10 remains functionally close to the SI base 10 value, although each increasing factor diverges slightly further from the base SI meaning. Thus the SI base-10 units are "close enough" and have become the commonly used for base 2 values.

Table 2.4. Base 2 and 10 factors related to bytes

Name |	Base 2 Factor |	Bytes |	Close Base 10 Factor |	Base 10 bytes
-----|----------------|-------|----------------------|------------------
1 Kilobyte |	2<sup>10<sup> |	1,024 |	10<sup>3<sup> |	1,000
1 Megabyte |	2<sup>20<sup> |	1,048,576 |	10<sup>6<sup> |	1,000,000
1 Gigabyte |	2<sup>30<sup> |	1,073,741,824 |	10<sup>9<sup> |	1,000,000,000
1 Terabyte |	2<sup>40<sup> |	1,099,511,627,776 |	10<sup>12<sup> |	1,000,000,000,000
1 Petabyte |	2<sup>50<sup> |	1,125,899,906,842,624 |	10<sup>15<sup> |	1,000,000,000,000,000
1 Exabyte |	2<sup>60<sup> |	1,152,921,504,606,846,976 |	10<sup>18<sup> |	1,000,000,000,000,000,000

> SI units compared in base 2 and base 10

It can be very useful to commit the base 2 factors to memory as an aid to quickly correlate the relationship between number-of-bits and "human" sizes. For example, we can quickly calculate that a 32 bit computer can address up to four gigabytes of memory by noting the recombination of 22 (4) + 230. A 64-bit value could similarly address up to 16 exabytes (24 + 260); you might be interested in working out just how big a number this is. To get a feel for how big that number is, calculate how long it would take to count to 264 if you incremented once per second.

## Kilo, Mega and Giga Bits
Apart from the confusion related to the overloading of SI units between binary and base 10, capacities will often be quoted in terms of bits rather than bytes. Generally this happens when talking about networking or storage devices; you may have noticed that your ADSL connection is described as something like 1500 kilobits/second. The calculation is simple; multiply by 1000 (for the kilo), divide by 8 to get bytes and then 1024 to get kilobytes (so 1500 kilobits/s=183 kilobytes per second).

The SI standardisation body has recognised these dual uses and has specified unique prefixes for binary usage. Under the standard 1024 bytes is a kibibyte, short for kilo binary byte (shortened to KiB). The other prefixes have a similar prefix (Mebibyte, MiB, for example). Tradition largely prevents use of these terms, but you may seem them in some literature.

## Conversion
The easiest way to convert between bases is to use a computer, after all, that's what they're good at! However, it is often useful to know how to do conversions by hand.

The easiest method to convert between bases is repeated division. To convert, repeatedly divide the quotient by the base, until the quotient is zero, making note of the remainders at each step. Then, write the remainders in reverse, starting at the bottom and appending to the right each time. An example should illustrate; since we are converting to binary we use a base of 2.

Table 2.5. Convert 203 to binary

Quotient |	  |	Remainder	 | 
---------|--------|----------------------|-----------
203<sub>10</sub> ÷ 2 = | 101 |	1 |	 
101<sub>10</sub> ÷ 2 = | 50 |	1 |	↑ |
50<sub>10</sub> ÷ 2 = |	25 |	0 |	↑ |
25<sub>10</sub> ÷ 2 = |	12 |	1 |	↑ |
12<sub>10</sub> ÷ 2 = |	6 |	0 |	↑ |
6<sub>10</sub> ÷ 2 = |	3 |	0 |	↑ |
3<sub>10</sub> ÷ 2 = |	1 |	1 |	↑ |
1<sub>10</sub> ÷ 2 = |	0 |	1 |	↑ |

## Boolean Operations
George Boole was a mathematician who discovered a whole area of mathematics called Boolean Algebra. Whilst he made his discoveries in the mid 1800's, his mathematics are the fundamentals of all computer science. Boolean algebra is a wide ranging topic, we present here only the bare minimum to get you started.

Boolean operations simply take a particular input and produce a particular output following a rule. For example, the simplest boolean operation, not simply inverts the value of the input operand. Other operands usually take two inputs, and produce a single output.

The fundamental Boolean operations used in computer science are easy to remember and listed below. We represent them below with truth tables; they simply show all possible inputs and outputs. The term true simply reflects 1 in binary.

### Not
Usually represented by !, not simply inverts the value, so 0 becomes 1 and 1 becomes 0

Table 2.6. Truth table for not

Input|	Output
------|--------
1|	0
0|	1

### And

To remember how the and operation works think of it as "if one input and the other are true, result is true

Table 2.7. Truth table for and

Input 1	| Input 2 | Output
--------|---------|----------
0 | 	0 | 	0
1 | 	0 | 	0
0 | 	1 | 	0
1 | 	1 | 	1

### Or

To remember how the or operation works think of it as "if one input or the other input is true, the result is true

Table 2.8. Truth table for or

Input 1 | Input 2 | Output
--------|---------|----------
0 | 	0 | 	0
1 | 	0 | 	1
0 | 	1 | 	1
1 | 	1 | 	1

### Exclusive Or (xor)

Exclusive or, written as xor is a special case of or where the output is true if one, and only one, of the inputs is true. This operation can surprisingly do many interesting tricks, but you will not see a lot of it in the kernel.

Table 2.9. Truth table for xor

Input 1 | Input 2 | Output
--|---|--
0 | 0 | 0
1 | 0 | 1
0 | 1 | 1
1 | 1 | 0

## How computers use boolean operations

Believe it or not, essentially everything your computer does comes back to the above operations. For example, the half adder is a type of circuit made up from boolean operations that can add bits together (it is called a half adder because it does not handle carry bits). Put more half adders together, and you will start to build something that can add together long binary numbers. Add some external memory, and you have a computer.

Electronically, the boolean operations are implemented in gates made by transistors. This is why you might have heard about transistor counts and things like Moore's Law. The more transistors, the more gates, the more things you can add together. To create the modern computer, there are an awful lot of gates, and an awful lot of transistors. Some of the latest Itanium processors have around 460 million transistors.

## Working with binary in C

In C we have a direct interface to all of the above operations. The following table describes the operators

Table 2.10. Boolean operations in C

Operation | Usage in C
----|----
not | !
and | &
or | |
xor | ^

We use these operations on variables to modify the bits within the variable. Before we see examples of this, first we must divert to describe hexadecimal notation.

## Hexadecimal

Hexadecimal refers to a base 16 number system. We use this in computer science for only one reason, it makes it easy for humans to think about binary numbers. Computers only ever deal in binary and hexadecimal is simply a shortcut for us humans trying to work with the computer.

So why base 16? Well, the most natural choice is base 10, since we are used to thinking in base 10 from our every day number system. But base 10 does not work well with binary -- to represent 10 different elements in binary, we need four bits. Four bits, however, gives us sixteen possible combinations. So we can either take the very tricky road of trying to convert between base 10 and binary, or take the easy road and make up a base 16 number system -- hexadecimal!

Hexadecimal uses the standard base 10 numerals, but adds A B C D E F which refer to 10 11 12 13 14 15 (n.b. we start from zero).

Traditionally, any time you see a number prefixed by 0x this will denote a hexadecimal number.

As mentioned, to represent 16 different patterns in binary, we would need exactly four bits. Therefore, each hexadecimal numeral represents exactly four bits. You should consider it an exercise to learn the following table off by heart.

Table 2.11. Hexadecimal, Binary and Decimal

Hexadecimal | Binary | Decimal
--|----------|------- 
0 | 	0000 | 	0
1 | 	0001 | 	1
2 | 	0010 | 	2
3 | 	0011 | 	3
4 | 	0100 | 	4
5 | 	0101 | 	5
6 | 	0110 | 	6
7 | 	0111 | 	7
8 | 	1000 | 	8
9 | 	1001 | 	9
A | 	1010 | 	10
B | 	1011 | 	11
C | 	1100 | 	12
D | 	1101 | 	13
E | 	1110 | 	14
F | 	1111 | 	15

Of course there is no reason not to continue the pattern (say, assign G to the value 16), but 16 values is an excellent trade off between the vagaries of human memory and the number of bits used by a computer (occasionally you will also see base 8 used, for example for file permissions under UNIX). We simply represent larger numbers of bits with more numerals. For example, a sixteen bit variable can be represented by 0xAB12, and to find it in binary simply take each individual numeral, convert it as per the table and join them all together (so 0xAB12 ends up as the 16-bit binary number 1010101100010010). We can use the reverse to convert from binary back to hexadecimal.

We can also use the same repeated division scheme to change the base of a number. For example, to find 203 in hexadecimal

Table 2.12. Convert 203 to hexadecimal

Quotient     |     | Remainder | 
-------------|-----|------------------ 
20310 ÷ 16 = | 	12 | 11 (0xB) | 
1210 ÷ 16 =  | 0   | 12 (0xC) | ↑

Hence 203 in hexadecimal is 0xCB.

Practical Implications
Use of binary in code
Whilst binary is the underlying language of every computer, it is entirely practical to program a computer in high level languages without knowing the first thing about it. However, for the low level code we are interested in a few fundamental binary principles are used repeatedly.

## Masking and Flags

### Masking

In low level code, it is often important to keep your structures and variables as space efficient as possible. In some cases, this can involve effectively packing two (generally related) variables into one.

Remember each bit represents two states, so if we know a variable only has, say, 16 possible states it can be represented by 4 bits (i.e. 24=16 unique values). But the smallest type we can declare in C is 8 bits (a char), so we can either waste four bits, or find some way to use those left over bits.

We can easily do this by the process of masking. Remembering the rules of the logical operations, it should become clear how the values are extracted.

The process is illustrated in the figure below. We are interested in the lower four bits, so set our mask to have these bits set to 1. Since the logical and operation will only set the bit if both bits are 1, those bits of the mask set to 0 effectively hide the bits we are not interested in.

Figure 2.1. Masking

![Figure 2.1. Masking](http://www.bottomupcs.com/chapter01/figures/masking.png)

----

To get the top (blue) four bits, we would invert the mask. You will note this gives a result of 0x90 when really we want a value of 0x09. To get the bits into the right position we use the right shift operation.

Setting the bits requires the logical or operation. However, rather than using 1's as the mask, we use 0's. You should draw a diagram similar to the above figure and work through setting bits with the logical or operation.

### Flags

Often a program will have a large number of variables that only exist as flags to some condition. For example, a state machine is an algorithm that transitions through a number of different states but may only be in one at a time. Say it has 8 different states; we could easily declare 8 different variables, one for each state. But in many cases it is better to declare one 8 bit variable and assign each bit to flag flag a particular state.

Flags are a special case of masking, but each bit represents a particular boolean state (on or off). An n bit variable can hold n different flags. See the code example below for a typical example of using flags -- you will see variations on this basic code very often.

Example 2.1. Using flags

```c
#include <stdio.h>

/*
 *  define all 8 possible flags for an 8 bit variable
 *      name  hex     binary
 */
#define FLAG1 0x01 /* 00000001 */
#define FLAG2 0x02 /* 00000010 */
#define FLAG3 0x04 /* 00000100 */
#define FLAG4 0x08 /* 00001000 */
/* ... and so on */
#define FLAG8 0x80 /* 10000000 */

int main(int argc, char *argv[])
{
	char flags = 0; /* an 8 bit variable */

	/* set flags with a logical or */
	flags = flags | FLAG1; /* set flag 1 */
	flags = flags | FLAG3; /* set flag 3
	/* check flags with a logical and.  If the flag is set (1)
	 * then the logical and will return 1, causing the if
	 * condition to be true. */
	if (flags & FLAG1)
		printf("FLAG1 set!\n");

	/* this of course will be untrue. */
	if (flags & FLAG8)
		printf("FLAG8 set!\n");

	/* check multiple flags by using a logical or
	 * this will pass as FLAG1 is set */
	if (flags & (FLAG1|FLAG4))
		printf("FLAG1 or FLAG4 set!\n");

	return 0;
}
```

## Types and Number Representation

### C Standards

Although a slight divergence, it is important to understand a bit of history about the C language.

C is the common languge of the systems programming world. Every operating system and its associated system libraries in common use is written in C, and every system provides a C compiler. To stop the language diverging across each of these systems where each would be sure to make numerous incompatible changes, a strict standard has been written for the language.

Officially this standard is known as ISO/IEC 9899:1999(E), but is more commonly referred to by its shortened name C99. The standard is maintained by the International Standards Organisation (ISO) and the full standard is available for purchase online. Older standards versions such as C89 (the predecessor to C99 released in 1989) and ANSI C are no longer in common usage and are encompassed within the latest standard. The standard documentation is very technical, and details most every part of the language. For example it explains the syntax (in Backus Naur form), standard #define values and how operations should behave.

It is also important to note what the C standards does not define. Most importantly the standard needs to be appropriate for every architecture, both present and future. Consequently it takes care not to define areas that are architecture dependent. The "glue" between the C standard and the underlying architecture is the Application Binary Interface (or ABI) which we discuss below. In several places the standard will mention that a particular operation or construct has an unspecified or implementation dependent result. Obviously the programmer can not depend on these outcomes if they are to write portable code.

### GNU C
The GNU C Compiler, more commonly referred to as gcc, almost completely implements the C99 standard. However it also implements a range of extensions to the standard which programmers will often use to gain extra functionality, at the expense of portability to another compiler. These extensions are usually related to very low level code and are much more common in the system programming field; the most common extension being used in this area being inline assembly code. Programmers should read the gcc documentation and understand when they may be using features that diverge from the standard.

gcc can be directed to adhere strictly to the standard (the -std=c99 flag for example) and warn or create an error when certain things are done that are not in the standard. This is obviously appropriate if you need to ensure that you can move your code easily to another compiler.

### Types
As programmers, we are familiar with using variables to represent an area of memory to hold a value. In a typed language, such as C, every variable must be declared with a type. The type tells the compiler about what we expect to store in a variable; the compiler can then both allocate sufficient space for this usage and check that the programmer does not violate the rules of the type. In the example below, we see an example of the space allocated for some common types of variables.

Figure 2.2. Types

![](http://www.bottomupcs.com/chapter01/figures/types.png)

----

The C99 standard purposely only mentions the smallest possible size of each of the types defined for C. This is because across different processor architectures and operating systems the best size for types can be wildly different.

To be completely safe programmers need to never assume the size of any of their variables, however a functioning system obviously needs agreements on what sizes types are going to be used in the system. Each architecture and operating system conforms to an Application Binary Interface or ABI. The ABI for a system fills in the details between the C standard and the requirements of the underlying hardware and operating system. An ABI is written for a specific processor and operating system combination.

Table 2.13. Standard Integer Types and Sizes

Type | C99 minimum size (bits) | Common size (32 bit architecture)
-----|---|-------
char | 8 | 8
short | 16 | 16
int | 16 | 32
long | 32 | 32
long long | 64 | 64
Pointers | Implementation dependent | 32

Above we can see the only divergence from the standard is that int is commonly a 32 bit quantity, which is twice the strict minimum 16 bit size that the C99 requires.

Pointers are really just an address (i.e. their value is an address and thus "points" somewhere else in memory) therefore a pointer needs to be sufficient in size to be able to address any memory in the system.

### 64 bit

One area that causes confusion is the introduction of 64 bit computing. This means that the processor can handle addresses 64 bits in length (specifically the registers are 64 bits wide; a topic we discuss in Chapter 3, Computer Architecture).

This firstly means that all pointers are required to be a 64 bits wide so they can represent any possible address in the system. However, system implementers must then make decisions about the size of the other types. Two common models are widely used, as shown below.

Table 2.14. Standard Scalar Types and Sizes

Type | C99 minimum size (bits) | Common size (LP64) | Common size (Windows)
-----|---|---|---
char | 8 | 8 | 8
short | 16 | 16 | 16
int | 16 | 32 | 32
long | 32 | 64 | 32
long long | 64 | 64 | 64
Pointers | Implementation dependent | 64 | 64

You can see that in the LP64 (long-pointer 64) model long values are defined to be 64 bits wide. This is different to the 32 bit model we showed previously. The LP64 model is widely used on UNIX systems.

In the other model, long remains a 32 bit value. This maintains maximum compatibility with 32 code. This model is in use with 64 bit Windows.

There are good reasons why the size of int was not increased to 64 bits in either model. Consider that if the size of int is increased to 64 bits you leave programmers no way to obtain a 32 bit variable. The only possibly is redefining shorts to be a larger 32 bit type.

A 64 bit variable is so large that it is not generally required to represent many variables. For example, loops very rarely repeat more times than would fit in a 32 bit variable (4294967296 times!). Images usually are usually represented with 8 bits for each of a red, green and blue value and an extra 8 bits for extra (alpha channel) information; a total of 32 bits. Consequently for many cases, using a 64 bit variable will be wasting at least the top 32 bits (if not more). Not only this, but the size of an integer array has now doubled too. This means programs take up more system memory (and thus more cache; discussed in detail in Chapter 3, Computer Architecture) for no real improvement. For the same reason Windows elected to keep their long values as 32 bits; since much of the Windows API was originally written to use long variables on a 32 bit system and hence does not require the extra bits this saves considerable wasted space in the system without having to re-write all the API.

If we consider the proposed alternative where short was redefined to be a 32 bit variable; programmers working on a 64 bit system could use it for variables they know are bounded to smaller values. However, when moving back to a 32 bit system their same short variable would now be only 16 bits long, a value which is much more realistically overflowed (65536).

By making a programmer request larger variables when they know they will be needed strikes a balance with respect to portability concerns and wasting space in binaries.

### Type qualifiers
The C standard also talks about some qualifiers for variable types. For example const means that a variable will never be modified from its original value and volatile suggests to the compiler that this value might change outside program execution flow so the compiler must be careful not to re-order access to it in any way.

signed and unsigned are probably the two most important qualifiers; and they say if a variable can take on a negative value or not. We examine this in more detail below.

Qualifiers are all intended to pass extra information about how the variable will be used to the compiler. This means two things; the compiler can check if you are violating your own rules (e.g. writing to a const value) and it can make optimisations based upon the extra knowledge (examined in later chapters).

### Standard Types
C99 realises that all these rules, sizes and portability concerns can become very confusing very quickly. To help, it provides a series of special types which can specify the exact properties of a variable. These are defined in <stdint.h> and have the form qtypes_t where q is a qualifier, type is the base type, s is the width in bits and _t is an extension so you know you are using the C99 defined types.

So for example uint8_t is an unsigned integer exactly 8 bits wide. Many other types are defined; the complete list is detailed in C99 17.8 or (more cryptically) in the header file. [3]

It is up to the system implementing the C99 standard to provide these types for you by mapping them to appropriate sized types on the target system; on Linux these headers are provided by the system libraries.

### Types in action
Below in Example 2.2, “Example of warnings when types are not matched” we see an example of how types place restrictions on what operations are valid for a variable, and how the compiler can use this information to warn when variables are used in an incorrect fashion. In this code, we firstly assign an integer value into a char variable. Since the char variable is smaller, we loose the correct value of the integer. Further down, we attempt to assign a pointer to a char to memory we designated as an integer. This operation can be done; but it is not safe. The first example is run on a 32-bit Pentium machine, and the correct value is returned. However, as shown in the second example, on a 64-bit Itanium machine a pointer is 64 bits (8 bytes) long, but an integer is only 4 bytes long. Clearly, 8 bytes can not fit into 4! We can attempt to "fool" the compiler by casting the value before assigning it; note that in this case we have shot ourselves in the foot by doing this cast and ignoring the compiler warning since the smaller variable can not hold all the information from the pointer and we end up with an invalid address.

Example 2.2. Example of warnings when types are not matched

```c
/*
 * types.c
 */

#include <stdio.h>
#include <stdint.h>

int main(void)
{
	char a;
	char *p = "hello";

	int i;

	// moving a larger variable into a smaller one
	i = 0x12341234;
	a = i;
	i = a;
	printf("i is %d\n", i);

	// moving a pointer into an integer
	printf("p is %p\n", p);
	i = p;
	// "fooling" with casts
	i = (int)p;
	p = (char*)i;
	printf("p is %p\n", p);

	return 0;
}
```

```
$ uname -m
i686

$ gcc -Wall -o types types.c
types.c: In function 'main':
types.c:19: warning: assignment makes integer from pointer without a cast

$ ./types
i is 52
p is 0x80484e8
p is 0x80484e8

$ uname -m
ia64

$ gcc -Wall  -o types types.c
types.c: In function 'main':
types.c:19: warning: assignment makes integer from pointer without a cast
types.c:21: warning: cast from pointer to integer of different size
types.c:22: warning: cast to pointer from integer of different size

$ ./types
i is 52
p is 0x40000000000009e0
p is 0x9e0

```

## Number Representation

### Negative Values
With our modern base 10 numeral system we indicate a negative number by placing a minus (-) sign in front of it. When using binary we need to use a different system to indicate negative numbers.

There is only one scheme in common use on modern hardware, but C99 defines three acceptable methods for negative value representation.

### Sign Bit
The most straight forward method is to simply say that one bit of the number indicates either a negative or positive value depending on it being set or not.

This is analogous to mathematical approach of having a + and -. This is fairly logical, and some of the original computers did represent negative numbers in this way. But using binary numbers opens up some other possibilities which make the life of hardware designers easier.

However, notice that the value 0 now has two equivalent values; one with the sign bit set and one without. Sometimes these values are referred to as +0 and -0 respectively.

### One's Complement

One's complement simply applies the not operation to the positive number to represent the negative number. So, for example the value -90 (-0x5A) is represented by ~01011010 = 10100101[4]

With this scheme the biggest advantage is that to add a negative number to a positive number no special logic is required, except that any additional carry left over must be added back to the final value. Consider

Table 2.15. One's Complement Addition

Decimal | Binary | Op
----|------------|---------
-90 | 	10100101 | 	+
100 | 	01100100 | 	 
--- | 	-------- | 	 
10 | 	100001001 | 	9
  | 	00001010 | 	10

If you add the bits one by one, you find you end up with a carry bit at the end (highlighted above). By adding this back to the original we end up with the correct value, 10

Again we still have the problem with two zeros being represented. Again no modern computer uses one's complement, mostly because there is a better scheme.

### Two's Complement

Two's complement is just like one's complement, except the negative representation has one added to it and we discard any left over carry bit. So to continue with the example from before, -90 would be ~01011010+1=10100101+1 = 10100110.

This means there is a slightly odd symmetry in the numbers that can be represented; for example with an 8 bit integer we have 2^8 = 256 possible values; with our sign bit representation we could represent -127 thru 127 but with two's complement we can represent -127 thru 128. This is because we have removed the problem of having two zeros; consider that "negative zero" is (~00000000 +1)=(11111111+1)=00000000 (note discarded carry bit).


You can see that by implementing two's complement hardware designers need only provide logic for addition circuits; subtraction can be done by two's complement negating the value to be subtracted and then adding the new value.

Similarly you could implement multiplication with repeated addition and division with repeated subtraction. Consequently two's complement can reduce all simple mathematical operations down to addition!

All modern computers use two's complement representation.

### Sign-extension
Because of two's complement format, when increasing the size of signed value, it is important that the additional bits be sign-extended; that is, copied from the top-bit of the existing value.

For example, the value of an 32-bit int -10 would be represented in two's complement binary as 11111111111111111111111111110110. If one were to cast this to a 64-bit long long int, we would need to ensure that the additional 32-bits were set to 1 to maintain the same sign as the original.

Thanks to two's complement, it is sufficient to take the top bit of the exiting value and replace all the added bits with this value. This processes is referred to as sign-extension and is usually handled by the compiler in situations as defined by the language standard, with the processor generally providing special instructions to take a value and sign-extended it to some larger value.

### Floating Point
So far we have only discussed integer or whole numbers; the class of numbers that can represent decimal values is called floating point.

To create a decimal number, we require some way to represent the concept of the decimal place in binary. The most common scheme for this is known as the IEEE-754 floating point standard because the standard is published by the Institute of Electric and Electronics Engineers. The scheme is conceptually quite simple and is somewhat analogous to "scientific notation".

In scientific notation the value 123.45 might commonly be represented as 1.2345x102. We call 1.2345 the mantissa or significand, 10 is the radix and 2 is the exponent.

In the IEEE floating point model, we break up the available bits to represent the sign, mantissa and exponent of a decimal number. A decimal number is represented by sign × significand × 2^exponent.

The sign bit equates to either 1 or -1. Since we are working in binary, we always have the implied radix of 2.

There are differing widths for a floating point value -- we examine below at only a 32 bit value. More bits allows greater precision.

Table 2.17. IEEE Floating Point

Sign | 	Exponent | Significand/Mantissa
--|----------|--------------------------
S | EEEEEEEE | MMMMMMMMMMMMMMMMMMMMMMM

The other important factor is bias of the exponent. The exponent needs to be able to represent both positive and negative values, thus an implied value of 127 is subtracted from the exponent. For example, an exponent of 0 has an exponent field of 127, 128 would represent 1 and 126 would represent -1.

Each bit of the significand adds a little more precision to the values we can represent. Consider the scientific notation representation of the value 198765. We could write this as 1.98765x106, which corresponds to a representation below

Table 2.18. Scientific Notation for 1.98765x10^6

100 | 	. | 	10-1 | 	10-2 | 	10-3 | 	10-4 | 	10-5
--|-------|-------|-------|-------|-------|----------
1 | 	. | 	9 | 	8 | 	7 | 	6 | 	5

Each additional digit allows a greater range of decimal values we can represent. In base 10, each digit after the decimal place increases the precision of our number by 10 times. For example, we can represent 0.0 through 0.9 (10 values) with one digit of decimal place, 0.00 through 0.99 (100 values) with two digits, and so on. In binary, rather than each additional digit giving us 10 times the precision, we only get two times the precision, as illustrated in the table below. This means that our binary representation does not always map in a straight-forward manner to a decimal representation.

Table 2.19. Significands in binary

20 | 	. | 2<sup>-1</sup> | 2<sup>-2</sup> | 2<sup>-3</sup> | 2<sup>-4</sup> | 2<sup>-5</sup>
--|-------|-------|-------|-------|-------|----------
1 | 	. | 	1/2 | 	1/4 | 	1/8 | 	1/16 | 	1/32
1 | 	. | 	0.5 | 	0.25 | 	0.125 | 0.0625 | 0.03125

With only one bit of precision, our fractional precision is not very big; we can only say that the fraction is either 0 or 0.5. If we add another bit of precision, we can now say that the decimal value is one of either 0,0.25,0.5,0.75. With another bit of precision we can now represent the values 0,0.125,0.25,0.375,0.5,0.625,0.75,0.875.

Increasing the number of bits therefore allows us greater and greater precision. However, since the range of possible numbers is infinite we will never have enough bits to represent any possible value.

For example, if we only have two bits of precision and need to represent the value 0.3 we can only say that it is closest to 0.25; obviously this is insufficient for most any application. With 22 bits of significand we have a much finer resolution, but it is still not enough for most applications. A double value increases the number of significand bits to 52 (it also increases the range of exponent values too). Some hardware has an 84-bit float, with a full 64 bits of significand. 64 bits allows a tremendous precision and should be suitable for all but the most demanding of applications (XXX is this sufficient to represent a length to less than the size of an atom?)

Example 2.3. Floats versus Doubles

```c
$ cat float.c
#include <stdio.h>

int main(void)
{
        float a = 0.45;
        float b = 8.0;

        double ad = 0.45;
        double bd = 8.0;

        printf("float+float, 6dp    : %f\n", a+b);
        printf("double+double, 6dp  : %f\n", ad+bd);
        printf("float+float, 20dp   : %10.20f\n", a+b);
        printf("dobule+double, 20dp : %10.20f\n", ad+bd);

        return 0;
}

$ gcc -o float float.c

$ ./float
float+float, 6dp    : 8.450000
double+double, 6dp  : 8.450000
float+float, 20dp   : 8.44999998807907104492
dobule+double, 20dp : 8.44999999999999928946

$ python
Python 2.4.4 (#2, Oct 20 2006, 00:23:25)
[GCC 4.1.2 20061015 (prerelease) (Debian 4.1.1-16.1)] on linux2
Type "help", "copyright", "credits" or "license" for more information.
>>> 8.0 + 0.45
8.4499999999999993
```

A practical example is illustrated above. Notice that for the default 6 decimal places of precision given by printf both answers are the same, since they are rounded up correctly. However, when asked to give the results to a larger precision, in this case 20 decimal places, we can see the results start to diverge. The code using doubles has a more accurate result, but it is still not exactly correct. We can also see that programmers not explicitly dealing with float values still have problems with precision of variables!

### Normalised Values
In scientific notation, we can represent a value in many different ways. For example, 10023x10<sup>0</sup> = 1002.3x10<sup>1</sup> = 100.23x10<sup>2</sup>. We thus define the normalised version as the one where 1/radix <= significand < 1. In binary this ensures that the leftmost bit of the significand is always one. Knowing this, we can gain an extra bit of precision by having the standard say that the leftmost bit being one is implied.

Table 2.20. Example of normalising 0.375

2<sup>0</sup> | . | 2<sup>-1</sup> | 2<sup>-2</sup> |2<sup>-3</sup> |2<sup>-4</sup> |2<sup>-5</sup> |Exponent | 	Calculation
---|------|-------|-------|-------|-------|-------|---------|------------------------
0 | 	. | 	0 | 	1 | 	1 | 	0 | 	0 | 	2^0 | 	(0.25+0.125) × 1 = 0.375
0 | 	. | 	1 | 	1 | 	0 | 	0 | 	0 | 	2^-1 | 	(0.5+0.25)×.5=0.375
1 | 	. | 	1 | 	0 | 	0 | 	0 | 	0 | 	2^-2 | 	(1+0.5)×0.25=0.375

As you can see above, we can make the value normalised by moving the bits upwards as long as we compensate by increasing the exponent.

### Normalisation Tricks

A common problem programmers face is finding the first set bit in a bitfield. Consider the bitfield 0100; from the right the first set bit would be bit 2 (starting from zero, as is conventional).

The standard way to find this value is to shift right, check if the uppermost bit is a 1 and either terminate or repeat. This is a slow process; if the bitfield is 64 bits long and only the very last bit is set, you must go through all the preceding 63 bits!

However, if this bitfield value were the signficand of a floating point number and we were to normalise it, the value of the exponent would tell us how many times it was shifted. The process of normalising a number is generally built into the floating point hardware unit on the processor, so operates very fast; usually much faster than the repeated shift and check operations.

The example program below illustrates two methods of finding the first set bit on an Itanium processor. The Itanium, like most server processors, has support for an 80-bit extended floating point type, with a 64-bit significand. This means a unsigned long neatly fits into the significand of a long double. When the value is loaded it is normalised, and and thus by reading the exponent value (minus the 16 bit bias) we can see how far it was shifted.

Example 2.4. Program to find first set bit

```c
#include <stdio.h>

int main(void)
{
	//  in binary = 1000 0000 0000 0000
	//  bit num     5432 1098 7654 3210
	int i = 0x8000;
	int count = 0;
	while ( !(i & 0x1) ) {
		count ++;
		i = i >> 1;
	}
	printf("First non-zero (slow) is %d\n", count);

	// this value is normalised when it is loaded
	long double d = 0x8000UL;
	long exp;

	// Itanium "get floating point exponent" instruction
	asm ("getf.exp %0=%1" : "=r"(exp) : "f"(d));

	// note exponent include bias
	printf("The first non-zero (fast) is %d\n", exp - 65535);

}
```

### Bringing it together

In the example code below we extract the components of a floating point number and print out the value it represents. This will only work for a 32 bit floating point value in the IEEE format; however this is common for most architectures with the float type.

Example 2.5. Examining Floats

```c
#include <stdio.h>

int main(void)
{
	//  in binary = 1000 0000 0000 0000
	//  bit num     5432 1098 7654 3210
	int i = 0x8000;
	int count = 0;
	while ( !(i & 0x1) ) {
		count ++;
		i = i >> 1;
	}
	printf("First non-zero (slow) is %d\n", count);

	// this value is normalised when it is loaded
	long double d = 0x8000UL;
	long exp;

	// Itanium "get floating point exponent" instruction
	asm ("getf.exp %0=%1" : "=r"(exp) : "f"(d));

	// note exponent include bias
	printf("The first non-zero (fast) is %d\n", exp - 65535);

}
```

Sample output of the value 8.45, which we previously examined, is shown below.

Example 2.6. Analysis of 8.45

```
$ ./float 8.45
8.450000 = 1 * (1/2^0 + 1/2^5 + 1/2^6 + 1/2^7 + 1/2^10 + 1/2^11 + 1/2^14 + 1/2^15 + 1/2^18 + 1/2^19 + 1/2^22 + 1/2^23) * 2^3
8.450000 = 1 * (1/1 + 1/32 + 1/64 + 1/128 + 1/1024 + 1/2048 + 1/16384 + 1/32768 + 1/262144 + 1/524288 + 1/4194304 + 1/8388608) * 2^3
8.450000 = 1 * 1.05624997616 * 8.000000
8.450000 = 8.44999980927
```

From this example, we get some idea of how the inaccuracies creep into our floating point numbers.

## Note

[1] Often you will see that the names of the parameters are omitted, and only the type of the parameter is specified. This allows the implementer to specify their own parameter names avoiding warnings from the compiler.

[2] A double-underscore function __foo may conversationally be referred to as "dunder foo".

[3] Note that C99 also has portability helpers for printf. The PRI macros in <inttypes.h> can be used as specifiers for types of specified sizes. Again see the standard or pull apart the headers for full information.

[4] The ~ operator is the C language operator to apply NOT to the value. It is also occasionally called the one's complement operator, for obvious reasons now!