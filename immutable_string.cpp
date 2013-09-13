// Copyright (c) 2013 Craig Henderson
// https://github.com/cdmh/cpp_immutable_string
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "immutable_string.h"
#include <cassert>
#include <iostream>
#include <cstring>
//#define TEST_COMPILER_ERRORS

int main(int, char *[])
{
#if defined(BOOST_MSVC)  &&  defined(_DEBUG)
    _CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
#endif

    using cdmh::immutable_string;

    // test default ctor, empty() and zero length
    assert(immutable_string().empty());                                                 // ctor 1

    immutable_string hello_world = "Hello, World!";                                     // ctor 4
    immutable_string const pangram1("the quick brown fox jumps over the lazy dog");     // ctor 4

    // test copy ctor and copy assignment
    immutable_string pangram2(pangram1);                                                // ctor 2.1
    immutable_string const pangram3 = "Bored? Craving a pub quiz fix? Why, just come to the Royal Oak!";   // ctor 4
#ifdef TEST_COMPILER_ERRORS
    pangram2 = pangram3;    // not allowed
    pangram2 = "Goodbye";   // not allowed
#endif

#ifndef _LIBSTDC_BUG_53221_WORKAROUND
    immutable_string pangram4(pangram1, std::allocator<char>());                        // ctor 2.2
    assert(pangram1 == pangram4);
#endif

    assert(immutable_string(pangram3, 21, 4) == "quiz");                                // ctor 3
    assert(immutable_string(pangram3.c_str(), 6) == "Bored?");                          // ctor 5
    assert(immutable_string(6, '*') == "******");                                       // ctor 6
    assert(immutable_string(pangram3.cbegin(), pangram3.cbegin() + 6) == "Bored?");
    assert(immutable_string('#') == "#");

    // test all the equivalence and relational operators
    std::string abc1("abc");
    std::string const xyz1("xyz1");
    immutable_string abc2("abc");
    immutable_string const xyz2(xyz1);                                                  // ctor 10.1

    std::string reversed;
    std::copy(pangram1.crbegin(), pangram1.crend(), std::back_inserter(reversed));
    assert(reversed == "god yzal eht revo spmuj xof nworb kciuq eht");

    // Capacity
    assert(immutable_string().empty());
    assert(immutable_string("Hello, World!").length() == 13);
    assert(immutable_string("Hello, World!").size() == 13);
    assert(immutable_string("Hello, World!").length() ==  immutable_string("Hello, World!").size());
    assert(immutable_string().max_size() == std::string().max_size());
    assert(immutable_string().capacity() == std::string().capacity());

    // Element access
    assert(pangram1[4] == 'q');
    assert(pangram1[5] == 'u');
    assert(pangram1.front() == 't');
    assert(pangram1.back() == 'g');
    assert(hello_world[0] == 'H');

    // test move ctors
    auto lambda = [&](immutable_string str) { return assert(str == pangram1); };
    lambda(pangram1);
    lambda(immutable_string(immutable_string(pangram1)));                                                   // ctor 2.1, 9.1
#ifndef _LIBSTDC_BUG_53221_WORKAROUND
    lambda(immutable_string(immutable_string(pangram1, std::allocator<char>()), std::allocator<char>()));   // ctor 2.2, 9.2
#endif
    assert(pangram1.append(pangram2) == pangram2.append(pangram1));
    assert(pangram1.append(abc1) == "the quick brown fox jumps over the lazy dogabc");
    assert(pangram1.append(abc1) == pangram2.append(abc2));
    assert(pangram1.append(abc1, 1, 2) == "the quick brown fox jumps over the lazy dogbc");
    assert(pangram1.append(abc1, 1, 2) == pangram2.append(abc2, 1, 2));
    assert(pangram1.append(", faster than a rabbit") == "the quick brown fox jumps over the lazy dog, faster than a rabbit");
    assert(pangram1.append(", faster than a rabbit", 6) == "the quick brown fox jumps over the lazy dog, fast");
    assert(pangram1.append(5, '*') == "the quick brown fox jumps over the lazy dog*****");
    assert(pangram1.append(abc1.cbegin(), abc1.cend()) == "the quick brown fox jumps over the lazy dogabc");
#if HAS_INITIALIZER_LIST
    assert(pangram1.append({ 'x', 'y', 'z'}) == "the quick brown fox jumps over the lazy dogxyz");
#endif

    assert(pangram1.substr(4, 5) == "quick");

    assert(pangram1.insert(3, " very") == "the very quick brown fox jumps over the lazy dog");
    assert(pangram1.insert(3, " very very", 5) == "the very quick brown fox jumps over the lazy dog");
    assert(pangram1.insert(3, std::string(" very")) == "the very quick brown fox jumps over the lazy dog");
    assert(pangram1.insert(3, immutable_string(" very")) == "the very quick brown fox jumps over the lazy dog");
    assert(pangram1.insert(3, std::string("awesomely very quite"), 9, 5) == "the very quick brown fox jumps over the lazy dog");
    assert(pangram1.insert(3, immutable_string("awesomely very quite"), 9, 5) == "the very quick brown fox jumps over the lazy dog");
    assert(pangram1.insert(3, 4, '*') == "the**** quick brown fox jumps over the lazy dog");
    assert(pangram1.insert(16, 6, '*') == "the quick brown ******fox jumps over the lazy dog");
    assert(pangram1.insert(pangram1.cbegin()+15, 6, '*') == "the quick brown****** fox jumps over the lazy dog");
    assert(pangram1.insert(pangram1.cbegin()+15, '*') == "the quick brown* fox jumps over the lazy dog");
    assert(pangram1.insert(pangram1.cbegin()+16, pangram1.cbegin(), pangram1.cend()) == "the quick brown the quick brown fox jumps over the lazy dogfox jumps over the lazy dog");
#if HAS_INITIALIZER_LIST
    assert(pangram1.insert(pangram1.cbegin()+4, { 'v','e','r','y',' ' }) == "the very quick brown fox jumps over the lazy dog");
#endif

    assert(pangram1.erase(10,6) == "the quick fox jumps over the lazy dog");
    assert(pangram1.erase(pangram1.cbegin()+15) == "the quick brownfox jumps over the lazy dog");
    assert(pangram1.erase(pangram1.cbegin()+10, pangram1.cbegin()+16) == "the quick fox jumps over the lazy dog");

    assert(pangram1.replace(4, 5, immutable_string("slow")) == "the slow brown fox jumps over the lazy dog");
    assert(pangram1.replace(4, 5, std::string("slow")) == "the slow brown fox jumps over the lazy dog");
    assert(pangram1.replace(pangram1.cbegin()+4, pangram1.cbegin()+9, immutable_string("slow")) == "the slow brown fox jumps over the lazy dog");
    assert(pangram1.replace(pangram1.cbegin()+4, pangram1.cbegin()+9, std::string("slow")) == "the slow brown fox jumps over the lazy dog");
    assert(pangram1.replace(4, 5, immutable_string("quick slow sly"), 6, 4) == "the slow brown fox jumps over the lazy dog");
    assert(pangram1.replace(4, 5, std::string("quick slow sly"), 6, 4) == "the slow brown fox jumps over the lazy dog");

    assert(pangram1.replace(4, 5, "slow") == "the slow brown fox jumps over the lazy dog");
    assert(pangram1.replace(pangram1.cbegin()+4, pangram1.cbegin()+9, "slow") == "the slow brown fox jumps over the lazy dog");
    assert(pangram1.replace(4, 5, "slower", 4) == "the slow brown fox jumps over the lazy dog");
    assert(pangram1.replace(pangram1.cbegin()+4, pangram1.cbegin()+9, "slower", 4) == "the slow brown fox jumps over the lazy dog");
    assert(pangram1.replace(4, 5, 9, '*') == "the ********* brown fox jumps over the lazy dog");
    assert(pangram1.replace(pangram1.cbegin()+4, pangram1.cbegin()+9, 9, '*') == "the ********* brown fox jumps over the lazy dog");
    assert(pangram1.replace(pangram1.cbegin()+4, pangram1.cbegin()+9, abc1.cbegin(), abc1.cend()) == "the abc brown fox jumps over the lazy dog");
#if HAS_INITIALIZER_LIST
    assert(pangram1.replace(pangram1.cbegin()+4, pangram1.cbegin()+9, {'s','l','o','w'}) == "the slow brown fox jumps over the lazy dog");
#endif

    assert(pangram1.c_str() == pangram1.data());
    assert(pangram1.get_allocator() == std::allocator<char>());
    char buffer[44] = { 0 };
    assert(pangram1.copy(buffer, 43, 0) == 43);
    assert(strcmp(buffer,pangram1.c_str()) == 0);

    assert(pangram1.compare(pangram2) == 0);
    assert(pangram1.compare(std::string("the quick brown fox jumps over the lazy dog")) == 0);

    assert(pangram1.compare(10, 5, "brown") == 0);
    assert(pangram1.compare(10, 5, immutable_string("brown")) == 0);
    assert(pangram1.compare(10, 5, std::string("brown")) == 0);
    assert(pangram1.compare(6, 10, pangram2, 6, 10) == 0);
    assert(pangram1.compare(6, 10, std::string("the quick brown fox jumps over the lazy dog"), 6, 10) == 0);

    assert(pangram1.compare("the quick brown fox jumps over the lazy dog") == 0);
    assert(pangram1.compare(10, 5, "brown fox", 5) == 0);

    assert(pangram1.find(immutable_string("brown"), 0) == 10);
    assert(pangram1.find(std::string("brown"), 0) == 10);
    assert(pangram1.find("brown", 0) == 10);
    assert(pangram1.find("brown sauce", 0, 6) == 10);
    assert(pangram1.find('z', 0) == 37);

    assert(pangram1.rfind(immutable_string("brown")) == 10);
    assert(pangram1.rfind(std::string("brown")) == 10);
    assert(pangram1.rfind("brown") == 10);
    assert(pangram1.rfind("brown sauce", immutable_string::npos, 6) == 10);
    assert(pangram1.rfind('z') == 37);

    assert(pangram3.find_first_of(immutable_string("!?,")) == 5);
    assert(pangram3.find_first_of(std::string("!?,")) == 5);
    assert(pangram3.find_first_of("!?,") == 5);
    assert(pangram3.find_first_of("!?,", 0, 1) == 62);
    assert(pangram3.find_first_of('z') == 24);

    assert(pangram3.find_last_of(immutable_string("!?,")) == 62);
    assert(pangram3.find_last_of(std::string("?,")) == 34);
    assert(pangram3.find_last_of("!?,") == 62);
    assert(pangram3.find_last_of("?!,",immutable_string::npos, 1) == 29);
    assert(pangram3.find_last_of('o') == 54);

    assert(pangram3.find_first_not_of(immutable_string("abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ")) == 5);
    assert(pangram3.find_first_not_of(std::string("abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ")) == 5);
    assert(pangram3.find_first_not_of("abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ") == 5);
    assert(pangram3.find_first_not_of("B?abcdefghijklmnopqrstuvwxyz", 0, 27) == 6);
    assert(pangram3.find_first_not_of('B') == 1);

    assert(pangram3.find_last_not_of(immutable_string("abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ!")) == 34);
    assert(pangram3.find_last_not_of(std::string("abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ!")) == 34);
    assert(pangram3.find_last_not_of("abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ!") == 34);
    assert(pangram3.find_last_not_of("O!abcdefghijklmnopqrstuvwxyz", immutable_string::npos, 27) == 58);
    assert(pangram3.find_last_not_of('!') == 61);

    assert(pangram1 + abc1 == immutable_string("the quick brown fox jumps over the lazy dogabc"));
    assert(abc1 == "abc");   // ensure the std::string didn't get modified
    assert(abc1 + pangram1 == immutable_string("abcthe quick brown fox jumps over the lazy dog"));
    assert(abc1 == "abc");   // ensure the std::string didn't get modified
    assert(immutable_string(pangram1) + std::string(abc1) == immutable_string("the quick brown fox jumps over the lazy dogabc"));
    assert(std::string(abc1) + immutable_string(pangram1) == immutable_string("abcthe quick brown fox jumps over the lazy dog"));

    assert(pangram1 + abc2 == "the quick brown fox jumps over the lazy dogabc");
    assert(immutable_string(pangram1) + abc2 == "the quick brown fox jumps over the lazy dogabc");
    assert(pangram1 + immutable_string(abc2) == "the quick brown fox jumps over the lazy dogabc");
    assert(immutable_string(pangram1) + immutable_string(abc2) == "the quick brown fox jumps over the lazy dogabc");
    assert(pangram1 + std::string(abc1) == "the quick brown fox jumps over the lazy dogabc");
    assert(immutable_string(pangram1) + abc1 == "the quick brown fox jumps over the lazy dogabc");
    assert(std::string(abc1) + pangram1 == "abcthe quick brown fox jumps over the lazy dog");
    assert(immutable_string(pangram1) + "abc" == "the quick brown fox jumps over the lazy dogabc");
    assert(pangram1 + "abc" == "the quick brown fox jumps over the lazy dogabc");
    assert("abc" + immutable_string(pangram1) == "abcthe quick brown fox jumps over the lazy dog");
    assert("abc" + pangram1 == "abcthe quick brown fox jumps over the lazy dog");
    assert(immutable_string(pangram1) + '#' == "the quick brown fox jumps over the lazy dog#");
    assert(pangram1 + '#' == "the quick brown fox jumps over the lazy dog#");
    assert('#' + immutable_string(pangram1) == "#the quick brown fox jumps over the lazy dog");
    assert('#' + pangram1 == "#the quick brown fox jumps over the lazy dog");

    assert(immutable_string("abc") == immutable_string("abc"));
    assert(immutable_string("abc") == std::string("abc"));
    assert(immutable_string("abc") == "abc");
    assert(std::string("abc")      == immutable_string("abc"));
    assert("abc"                   == immutable_string("abc"));

    assert(immutable_string("abc") != immutable_string("xyz"));
    assert(immutable_string("abc") != std::string("xyz"));
    assert(immutable_string("abc") != "xyz");
    assert(std::string("abc")      != immutable_string("xyz"));
    assert("abc"                   != immutable_string("xyz"));

    assert(immutable_string("abc") < immutable_string("xyz"));
    assert(immutable_string("abc") < std::string("xyz"));
    assert(immutable_string("abc") < "xyz");
    assert(std::string("abc")      < immutable_string("xyz"));
    assert("abc"                   < immutable_string("xyz"));

    assert(immutable_string("abc") <= immutable_string("xyz"));
    assert(immutable_string("abc") <= std::string("xyz"));
    assert(immutable_string("abc") <= "xyz");
    assert(std::string("abc")      <= immutable_string("xyz"));
    assert("abc"                   <= immutable_string("xyz"));

    assert(immutable_string("xyz") > immutable_string("abc"));
    assert(immutable_string("xyz") > std::string("abc"));
    assert(immutable_string("xyz") > "abc");
    assert(std::string("xyz")      > immutable_string("abc"));
    assert("xyz"                   > immutable_string("abc"));

    assert(immutable_string("xyz") >= immutable_string("abc"));
    assert(immutable_string("xyz") >= std::string("abc"));
    assert(immutable_string("xyz") >= "abc");
    assert(std::string("xyz")      >= immutable_string("abc"));
    assert("xyz"                   >= immutable_string("abc"));

    immutable_string finished("finished");
    std::cout << finished << "\n";
    return 0;
}

