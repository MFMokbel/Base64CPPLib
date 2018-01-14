# Base64CPPLib
Base64CPPLib is an open source Base64 encoding and decoding library written in “modern” C++. The library is highly extensible, and supports working with strings, hexadecimal streams, and files.

# Library Features

* OS and system architecture independent
* No dependency on any other third-party libraries or code
* Support for the customization of the core elements of the algorithm such as, padding character and alphabet (substitution) table
* Support for multiple levels of encoding/decoding
* Support for ascii string, hexadecimal string streams and files
* Strict handling and error reporting of any potential misuse of the algorithms
* Use of Exception handling
* Ease of use
* MS VS UnitTests

Here's a quick example:

```c++
#include <iostream>
#include “base64.h”

int main(int argc, char* argv[])
{
    try
    {
        // instantiate an object of the class Base64
        Base64 b64;
        // encode a string
        std::cout << b64.encode_str("hello world") << std::endl;
        // decode a string
        std::cout << b64.decode_str("aGVsbG8gd29ybGQ=") << std::endl;
        // hex(“hello world”) = "68656C6C6F20776F726C64"
        std::cout << b64.encode_hex("68656C6C6F20776F726C64") << std::endl;
    }
    catch (const std::string& es)
    {
        std::cerr << std::endl << "exception: " << es << std::endl;
    }
    catch (const std::exception& ee)
    {
        std::cerr << std::endl << "exception: " << ee.what() << std::endl;
    }
    return 0;
}
```
# Design

The library has two classes, **Base64** and **HFuncs**. The base class is **Base64** that contains the core functionality of the encoding and decoding algorithms, and **HFuncs** is just a derived class with support for couple of helper functions that could be used independent of the library.

The code throws exceptions of the types *std::exception* and *std::string* that need to be handled with try and catch blocks.

# Types of Violation Checks

The library throws exceptions whenever an attempt is made to violate some of the core prinicples of the algorithm. Such violations include:

* padding character is more than one character
* padding character is not set
* padding character is not unique (different from any character in the alphabet (substitution) table)
* alphabet table size is anything other than 64
* alphabet table is not set
* alphabet table contains duplicate characters
* hexadecimal byte stream that is not a multiple of 2
* encoded string length is not a mulitple of 4
* encode character that does not exist in the alphabet table

# Examples

1. To encode a string with a custom padding character and custom alphabet (substitution) table
```c++
{
Base64 b64;
// set custom padding character
b64.set_p_char("*");
// set custom alphabet (substitution) table
b64.set_s_table("23456789APQRSTUVW@#$abcdefghijk~!0mnopqrstuvwxy^&CDEFGHIJKLMNO()");
b64.encode_str("hello world"); // output: “g8bwh8N!jHODh8W*”
}
```
2. To encode a string multiple (5) times
```c++
{
Base64 b64;
b64.encode_str("hello world", 5); // output: “VjFaV2ExWXlUWGxUYTJoUVVqSlNjbFJYY0hOT1ZteHlXa1pLVVZWVU1Eaz0=”
}
```
3. To decode a 5 times Base64 encoded string
```c++
{
Base64 b64;
b64.decode_str("VjFaV2ExWXlUWGxUYTJoUVVqSlNjbFJYY0hOT1ZteHlXa1pLVVZWVU1Eaz0=", 5); // output: “hello world”
}
```
4. To encode a delimited (for example, with the delimiter “::”) hexadecimal stream
```c++
{
Base64 b64;
// hexstream is “hello world”
// since encode_hex method is not overloaded
b64.encode_hex("68::65::6C::6C::6F::20::77::6F::72::6C::64","::"); // output: “aGVsbG8gd29ybGQ=”
}
```
5. To encode a file and save encoded version to another file
```c++
{
Base64 b64;
std::string hfile = b64.open_file_binay("sample_file.bin");
std::string encoded_file = b64.encode_hex(hfile);
b64.save_file_text(encoded_file,"encoded_file.txt");
}
```
# Usage

Simply add the headers “helper_funcs.h” and “base64.h”, and the source files “helper_funcs.cpp” and “base64.cpp” to your project. And then, include the base class header file “base64.h” into your project.

Other than the examples provided in this readme file, I recommend that you take a look at the code base since it is fairly small and “well” documented to get a better understanding of how it works.

# Note on the performance of the library

I wrote the library without taking performance into consideration as a major design goal. I wanted something simple and clear. However, to speed things up, simply do the following (I myself have tested both variants, but I  won't upload the faster version, I just want to maintain one repo.):

* Replace std::stringstream objects with something faster
* Use binary operations for bit manipulations inside the *encode()* and *decode()* methods instead of **casting** and **bitset**
* Replace *strtl()* when converting to hex with a custom implementation
* ...

# Requirements

The only requirement is a C++ compiler with support for C++11 and C++14.

# Contributing

Open for pull requests and issues. Comments and suggestions are greatly appreciated.
