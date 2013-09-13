#C++ Immutable String
This repo contains the source and tests for an immutable string class in C++. The class is designed to follow the interface of `std::basic_string` where possible, and otherwise implements reasonable alternatives to provide maximum functionality.

What is an immutable string?
--
An immutable string is a string that cannot be modified once the initialization has completed. The class guarantees that the string value will not change. Ever.

Any attempt to modify a string will create a new string with the resulting value, and the existing string will remain in tact.

For example,
    
    immutable_string hello("Hello");
    auto hello_world = hello.append(", World!");
    
    assert(hello == "Hello");
    assert(hello_world == "Hello, World!");

An attempt to assign a value to an immutable string will fail:

    immutable_string message("Hello");
    message = "Goodbye";    // compiler error

##Interface
The interface follows the C++11 `std::basic_string` as closely as possible. Some differences to note:
* append() functions return a new `immutable_string` object rather than a reference to the modified `this` object
* construction from `std::basic_string`
* a new constructor taking a single character
* comparison with `std::string` aswell as other `immutable_string` objects, and character pointers
* a member function `mutable_string()` returns a `std::string` object with a copy of the string data

These functions are not implemented because they don't make sense with immutables
###Capacity
    resize()
    reserve()
    clear()
    shrink_to_fit

###Element access
    reference operator[] (size_type pos);
    reference at (size_type pos);
    charT &back();
    charT &front();

###Modifiers
    operator+=
    push_back
    assign
    swap
    pop_back

### free functions
    swap
    operator>>
    getline

##License - MIT
Copyright (c) 2013 Craig Henderson

https://github.com/cdmh/cpp_immutable_string
 
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
 
The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.
 
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
