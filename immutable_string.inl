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

namespace cdmh {

// comparison with another string instance
template<typename Char, typename Traits, typename Alloc>
bool operator==(basic_immutable_string<Char, Traits, Alloc> const &lhs, basic_immutable_string<Char, Traits, Alloc> const &rhs) {
    return lhs.compare(rhs) == 0;
}

template<typename Char, typename Traits, typename Alloc>
bool operator!=(basic_immutable_string<Char, Traits, Alloc> const &lhs, basic_immutable_string<Char, Traits, Alloc> const &rhs) {
    return !(lhs == rhs);
}

template<typename Char, typename Traits, typename Alloc>
bool operator<(basic_immutable_string<Char, Traits, Alloc> const &lhs, basic_immutable_string<Char, Traits, Alloc> const &rhs) {
    return lhs.compare(rhs) < 0;
}

template<typename Char, typename Traits, typename Alloc>
bool operator<=(basic_immutable_string<Char, Traits, Alloc> const &lhs, basic_immutable_string<Char, Traits, Alloc> const &rhs) {
    return lhs.compare(rhs) <= 0;
}

template<typename Char, typename Traits, typename Alloc>
bool operator>(basic_immutable_string<Char, Traits, Alloc> const &lhs, basic_immutable_string<Char, Traits, Alloc> const &rhs) {
    return lhs.compare(rhs) > 0;
}

template<typename Char, typename Traits, typename Alloc>
bool operator>=(basic_immutable_string<Char, Traits, Alloc> const &lhs, basic_immutable_string<Char, Traits, Alloc> const &rhs) {
    return lhs.compare(rhs) >= 0;
}


// comparison with Standard Library basic_string
template<typename Char, typename Traits, typename Alloc>
bool operator==(basic_immutable_string<Char, Traits, Alloc> const &lhs, std::basic_string<Char, Traits, Alloc> const &rhs) {
    return lhs.compare(rhs) == 0;
}

template<typename Char, typename Traits, typename Alloc>
bool operator!=(basic_immutable_string<Char, Traits, Alloc> const &lhs, std::basic_string<Char, Traits, Alloc> const &rhs) {
    return !(lhs == rhs);
}

template<typename Char, typename Traits, typename Alloc>
bool operator<(basic_immutable_string<Char, Traits, Alloc> const &lhs, std::basic_string<Char, Traits, Alloc> const &rhs) {
    return lhs.compare(rhs) < 0;
}

template<typename Char, typename Traits, typename Alloc>
bool operator<=(basic_immutable_string<Char, Traits, Alloc> const &lhs, std::basic_string<Char, Traits, Alloc> const &rhs) {
    return lhs.compare(rhs) <= 0;
}

template<typename Char, typename Traits, typename Alloc>
bool operator>(basic_immutable_string<Char, Traits, Alloc> const &lhs, std::basic_string<Char, Traits, Alloc> const &rhs) {
    return lhs.compare(rhs) > 0;
}

template<typename Char, typename Traits, typename Alloc>
bool operator>=(basic_immutable_string<Char, Traits, Alloc> const &lhs, std::basic_string<Char, Traits, Alloc> const &rhs) {
    return lhs.compare(rhs) >= 0;
}

template<typename Char, typename Traits, typename Alloc>
bool operator==(std::basic_string<Char, Traits, Alloc> const &lhs, basic_immutable_string<Char, Traits, Alloc> const &rhs) {
    return rhs.compare(lhs) == 0;
}

template<typename Char, typename Traits, typename Alloc>
bool operator!=(std::basic_string<Char, Traits, Alloc> const &lhs, basic_immutable_string<Char, Traits, Alloc> const &rhs) {
    return !(lhs == rhs);
}

template<typename Char, typename Traits, typename Alloc>
bool operator<(std::basic_string<Char, Traits, Alloc> const &lhs, basic_immutable_string<Char, Traits, Alloc> const &rhs) {
    return rhs.compare(lhs) > 0;
}

template<typename Char, typename Traits, typename Alloc>
bool operator<=(std::basic_string<Char, Traits, Alloc> const &lhs, basic_immutable_string<Char, Traits, Alloc> const &rhs) {
    return rhs.compare(lhs) >= 0;
}

template<typename Char, typename Traits, typename Alloc>
bool operator>(std::basic_string<Char, Traits, Alloc> const &lhs, basic_immutable_string<Char, Traits, Alloc> const &rhs) {
    return rhs.compare(lhs) < 0;
}

template<typename Char, typename Traits, typename Alloc>
bool operator>=(std::basic_string<Char, Traits, Alloc> const &lhs, basic_immutable_string<Char, Traits, Alloc> const &rhs) {
    return rhs.compare(lhs) <= 0;
}



// comparison to Char*
template<typename Char, typename Traits, typename Alloc>
bool operator==(Char const * const lhs, basic_immutable_string<Char, Traits, Alloc> const &rhs) {
    return rhs.compare(lhs) == 0;
}


template<typename Char, typename Traits, typename Alloc>
bool operator==(basic_immutable_string<Char, Traits, Alloc> const &lhs, Char const * const rhs) {
    return lhs.compare(rhs) == 0;
}


template<typename Char, typename Traits, typename Alloc>
bool operator!=(Char const * const lhs, basic_immutable_string<Char, Traits, Alloc> const &rhs) {
    return !(rhs == lhs);
}


template<typename Char, typename Traits, typename Alloc>
bool operator!=(basic_immutable_string<Char, Traits, Alloc> const &lhs, Char const * const rhs) {
    return !(lhs == rhs);
}


template<typename Char, typename Traits, typename Alloc>
bool operator<(Char const * const lhs, basic_immutable_string<Char, Traits, Alloc> const &rhs) {
    return rhs.compare(lhs) > 0;
}


template<typename Char, typename Traits, typename Alloc>
bool operator<(basic_immutable_string<Char, Traits, Alloc> const &lhs,  Char const * const rhs) {
    return lhs.compare(rhs) < 0;
}


template<typename Char, typename Traits, typename Alloc>
bool operator<=(Char const * const lhs, basic_immutable_string<Char, Traits, Alloc> const &rhs) {
    return rhs.compare(lhs) >= 0;
}


template<typename Char, typename Traits, typename Alloc>
bool operator<=(basic_immutable_string<Char, Traits, Alloc> const &lhs, Char const * const rhs) {
    return lhs.compare(rhs) <= 0;
}


template<typename Char, typename Traits, typename Alloc>
bool operator>(Char const * const lhs, basic_immutable_string<Char, Traits, Alloc> const &rhs) {
    return rhs.compare(lhs) < 0;
}


template<typename Char, typename Traits, typename Alloc>
bool operator>(basic_immutable_string<Char, Traits, Alloc> const &lhs, Char const * const rhs) {
    return lhs.compare(rhs) > 0;
}


template<typename Char, typename Traits, typename Alloc>
bool operator>=(Char const * const lhs, basic_immutable_string<Char, Traits, Alloc> const &rhs) {
    return rhs.compare(lhs) <= 0;
}


template<typename Char, typename Traits, typename Alloc>
bool operator>=(basic_immutable_string<Char, Traits, Alloc> const &lhs, Char const * const rhs) {
    return lhs.compare(rhs) >= 0;
}

template<typename Char, typename Traits, typename Alloc>
basic_immutable_string<Char, Traits, Alloc>
basic_immutable_string<Char, Traits, Alloc>::append(basic_immutable_string const &str) const
{
    return string_ + str.string_;     // ctor 10.2
}

template<typename Char, typename Traits, typename Alloc>
basic_immutable_string<Char, Traits, Alloc>
basic_immutable_string<Char, Traits, Alloc>::append(std::basic_string<Char, Traits, Alloc> const &str) const
{
    return string_ + str;
}

template<typename Char, typename Traits, typename Alloc>
basic_immutable_string<Char, Traits, Alloc>
basic_immutable_string<Char, Traits, Alloc>::append(basic_immutable_string const &str, size_type subpos, size_type sublen) const
{
    return string_ + str.string_.substr(subpos, sublen);
}

template<typename Char, typename Traits, typename Alloc>
basic_immutable_string<Char, Traits, Alloc>
basic_immutable_string<Char, Traits, Alloc>::append(std::basic_string<Char, Traits, Alloc> const &str, size_type subpos, size_type sublen) const
{
    return string_ + str.substr(subpos, sublen);
}

template<typename Char, typename Traits, typename Alloc>
basic_immutable_string<Char, Traits, Alloc>
basic_immutable_string<Char, Traits, Alloc>::append(Char const * const s) const
{
    return std::basic_string<Char, Traits, Alloc>(string_ + s);
}

template<typename Char, typename Traits, typename Alloc>
basic_immutable_string<Char, Traits, Alloc>
basic_immutable_string<Char, Traits, Alloc>::append(Char const * const s, size_type n) const
{
    return string_ + std::basic_string<Char, Traits, Alloc>(s, n);
}

template<typename Char, typename Traits, typename Alloc>
basic_immutable_string<Char, Traits, Alloc>
basic_immutable_string<Char, Traits, Alloc>::append(size_type n, Char c) const
{
    return string_ + std::basic_string<Char, Traits, Alloc>(n, c);
}

template<typename Char, typename Traits, typename Alloc>
basic_immutable_string<Char, Traits, Alloc>
basic_immutable_string<Char, Traits, Alloc>::append(Char c) const
{
    return string_ + c;
}

template<typename Char, typename Traits, typename Alloc>
template<typename InputIterator>
basic_immutable_string<Char, Traits, Alloc>
basic_immutable_string<Char, Traits, Alloc>::append(InputIterator first, InputIterator last) const
{
    return string_ + std::basic_string<Char, Traits, Alloc>(first, last);
}

#if HAS_INITIALIZER_LIST
template<typename Char, typename Traits, typename Alloc>
basic_immutable_string<Char, Traits, Alloc>
basic_immutable_string<Char, Traits, Alloc>::append(std::initializer_list<Char> il) const
{
    return string_ + std::basic_string<Char, Traits, Alloc>(il);
}
#endif

template<typename Char, typename Traits, typename Alloc>
basic_immutable_string<Char, Traits, Alloc>
basic_immutable_string<Char, Traits, Alloc>::insert(size_type pos, basic_immutable_string<Char, Traits, Alloc> const &str) const
{
    return std::basic_string<Char, Traits, Alloc>(string_).insert(pos, str.string_);
}

template<typename Char, typename Traits, typename Alloc>
basic_immutable_string<Char, Traits, Alloc>
basic_immutable_string<Char, Traits, Alloc>::insert(size_type pos, std::basic_string<Char, Traits, Alloc> const &str) const
{
    return std::basic_string<Char, Traits, Alloc>(string_).insert(pos, str);
}

template<typename Char, typename Traits, typename Alloc>
basic_immutable_string<Char, Traits, Alloc>
basic_immutable_string<Char, Traits, Alloc>::insert(size_type pos, basic_immutable_string<Char, Traits, Alloc> const &str,
                                                     size_type subpos, size_type sublen) const
{
    return std::basic_string<Char, Traits, Alloc>(string_).insert(pos, str.string_, subpos, sublen);
}

template<typename Char, typename Traits, typename Alloc>
basic_immutable_string<Char, Traits, Alloc>
basic_immutable_string<Char, Traits, Alloc>::insert(size_type pos, std::basic_string<Char, Traits, Alloc> const &str,
                                                     size_type subpos, size_type sublen) const
{
    return std::basic_string<Char, Traits, Alloc>(string_).insert(pos, str, subpos, sublen);
}

template<typename Char, typename Traits, typename Alloc>
basic_immutable_string<Char, Traits, Alloc>
basic_immutable_string<Char, Traits, Alloc>::insert(size_type pos, Char const *s) const
{
    return std::basic_string<Char, Traits, Alloc>(string_).insert(pos, s);
}

template<typename Char, typename Traits, typename Alloc>
basic_immutable_string<Char, Traits, Alloc>
basic_immutable_string<Char, Traits, Alloc>::insert(size_type pos, Char const *s, size_type n) const
{
    return std::basic_string<Char, Traits, Alloc>(string_).insert(pos, s, n);
}

template<typename Char, typename Traits, typename Alloc>
basic_immutable_string<Char, Traits, Alloc>
basic_immutable_string<Char, Traits, Alloc>::insert(size_type pos, size_type n, Char c) const
{
    return std::basic_string<Char, Traits, Alloc>(string_).insert(pos, n, c);
}

template<typename Char, typename Traits, typename Alloc>
basic_immutable_string<Char, Traits, Alloc>
basic_immutable_string<Char, Traits, Alloc>::insert(const_iterator p, size_type n, Char c) const
{
    std::basic_string<Char, Traits, Alloc> str(string_);
    str.insert(str.begin() + std::distance(cbegin(),p), n, c);
    return str;
}

template<typename Char, typename Traits, typename Alloc>
basic_immutable_string<Char, Traits, Alloc>
basic_immutable_string<Char, Traits, Alloc>::insert(const_iterator p, Char c) const
{
    std::basic_string<Char, Traits, Alloc> str(string_);
    str.insert(str.begin() + std::distance(cbegin(),p), c);
    return str;
}

template<typename Char, typename Traits, typename Alloc>
template<typename InputIterator>
basic_immutable_string<Char, Traits, Alloc>
basic_immutable_string<Char, Traits, Alloc>::insert(const_iterator p, InputIterator first, InputIterator last) const
{
    std::basic_string<Char, Traits, Alloc> str(string_);
    str.insert(str.begin() + std::distance(cbegin(),p), first, last);
    return str;
}

#if HAS_INITIALIZER_LIST
template<typename Char, typename Traits, typename Alloc>
basic_immutable_string<Char, Traits, Alloc>
basic_immutable_string<Char, Traits, Alloc>::insert(const_iterator p, std::initializer_list<Char> il) const
{
    std::basic_string<Char, Traits, Alloc> str(string_);
    str.insert(str.begin() + std::distance(cbegin(),p), il);
    return str;
}
#endif

template<typename Char, typename Traits, typename Alloc>
basic_immutable_string<Char, Traits, Alloc>
basic_immutable_string<Char, Traits, Alloc>::erase(size_type pos, size_type len) const
{
    return std::basic_string<Char, Traits, Alloc>(string_).erase(pos,len);
}

template<typename Char, typename Traits, typename Alloc>
basic_immutable_string<Char, Traits, Alloc>
basic_immutable_string<Char, Traits, Alloc>::erase(const_iterator p) const
{
    std::basic_string<Char, Traits, Alloc> str(string_);
    str.erase(str.begin() + std::distance(cbegin(),p));
    return str;
}

template<typename Char, typename Traits, typename Alloc>
basic_immutable_string<Char, Traits, Alloc>
basic_immutable_string<Char, Traits, Alloc>::erase(const_iterator first, const_iterator last) const
{
    std::basic_string<Char, Traits, Alloc> str(string_);
    str.erase(str.begin() + std::distance(cbegin(),first), str.begin() + std::distance(cbegin(), last));
    return str;
}

template<typename Char, typename Traits, typename Alloc>
basic_immutable_string<Char, Traits, Alloc>
basic_immutable_string<Char, Traits, Alloc>::replace(size_type pos, size_type len, basic_immutable_string const &str) const
{
    return std::basic_string<Char, Traits, Alloc>(string_).replace(pos,len,str.string_);
}

template<typename Char, typename Traits, typename Alloc>
basic_immutable_string<Char, Traits, Alloc>
basic_immutable_string<Char, Traits, Alloc>::replace(size_type pos, size_type len, std::basic_string<Char, Traits, Alloc> const &str) const
{
    return std::basic_string<Char, Traits, Alloc>(string_).replace(pos,len,str);
}

template<typename Char, typename Traits, typename Alloc>
basic_immutable_string<Char, Traits, Alloc>
basic_immutable_string<Char, Traits, Alloc>::replace(const_iterator i1, const_iterator i2, basic_immutable_string const &str) const
{
    std::basic_string<Char, Traits, Alloc> newstr(string_);
    return 
        newstr.replace(
            newstr.begin() + std::distance(cbegin(),i1),
            newstr.begin() + std::distance(cbegin(),i2),
            str.string_);
}

template<typename Char, typename Traits, typename Alloc>
basic_immutable_string<Char, Traits, Alloc>
basic_immutable_string<Char, Traits, Alloc>::replace(const_iterator i1, const_iterator i2, std::basic_string<Char, Traits, Alloc> const &str) const
{
    std::basic_string<Char, Traits, Alloc> newstr(string_);
    return
        newstr.replace(
            newstr.begin() + std::distance(cbegin(),i1),
            newstr.begin() + std::distance(cbegin(),i2),
            str);
}

template<typename Char, typename Traits, typename Alloc>
basic_immutable_string<Char, Traits, Alloc>
basic_immutable_string<Char, Traits, Alloc>::replace(size_type pos, size_type len,
                                                      basic_immutable_string const &str,
                                                      size_type subpos, size_type sublen) const
{
    return std::basic_string<Char, Traits, Alloc>(string_).replace(pos, len, str.string_, subpos, sublen);
}

template<typename Char, typename Traits, typename Alloc>
basic_immutable_string<Char, Traits, Alloc>
basic_immutable_string<Char, Traits, Alloc>::replace(size_type pos, size_type len,
                                                      std::basic_string<Char, Traits, Alloc> const &str,
                                                      size_type subpos, size_type sublen) const
{
    return std::basic_string<Char, Traits, Alloc>(string_).replace(pos, len, str, subpos, sublen);
}

template<typename Char, typename Traits, typename Alloc>
basic_immutable_string<Char, Traits, Alloc>
basic_immutable_string<Char, Traits, Alloc>::replace(size_type pos, size_type len, Char const *s) const
{
    return std::basic_string<Char, Traits, Alloc>(string_).replace(pos, len, s);
}

template<typename Char, typename Traits, typename Alloc>
basic_immutable_string<Char, Traits, Alloc>
basic_immutable_string<Char, Traits, Alloc>::replace(const_iterator i1, const_iterator i2, Char const *s) const
{
    std::basic_string<Char, Traits, Alloc> newstr(string_);
    return 
        newstr.replace(
            newstr.begin() + std::distance(cbegin(),i1),
            newstr.begin() + std::distance(cbegin(),i2),
            s);
}

template<typename Char, typename Traits, typename Alloc>
basic_immutable_string<Char, Traits, Alloc>
basic_immutable_string<Char, Traits, Alloc>::replace(size_type pos, size_type len, Char const *s, size_type n) const
{
    return std::basic_string<Char, Traits, Alloc>(string_).replace(pos, len, s, n);
}

template<typename Char, typename Traits, typename Alloc>
basic_immutable_string<Char, Traits, Alloc>
basic_immutable_string<Char, Traits, Alloc>::replace(const_iterator i1, const_iterator i2, Char const *s, size_type n) const
{
    std::basic_string<Char, Traits, Alloc> newstr(string_);
    return
        newstr.replace(
            newstr.begin() + std::distance(cbegin(),i1),
            newstr.begin() + std::distance(cbegin(),i2),
            s, n);
}

template<typename Char, typename Traits, typename Alloc>
basic_immutable_string<Char, Traits, Alloc>
basic_immutable_string<Char, Traits, Alloc>::replace(size_type pos, size_type len, size_type n, Char c) const
{
    return std::basic_string<Char, Traits, Alloc>(string_).replace(pos, len, n, c);
}

template<typename Char, typename Traits, typename Alloc>
basic_immutable_string<Char, Traits, Alloc>
basic_immutable_string<Char, Traits, Alloc>::replace(const_iterator i1, const_iterator i2, size_type n, Char c) const
{
    std::basic_string<Char, Traits, Alloc> newstr(string_);
    return 
        newstr.replace(
            newstr.begin() + std::distance(cbegin(),i1),
            newstr.begin() + std::distance(cbegin(),i2),
            n, c);
}

template<typename Char, typename Traits, typename Alloc>
template<typename InputIterator>
basic_immutable_string<Char, Traits, Alloc>
basic_immutable_string<Char, Traits, Alloc>::replace(const_iterator i1, const_iterator i2,
                                                      InputIterator first, InputIterator last) const
{
    std::basic_string<Char, Traits, Alloc> newstr(string_);
    return 
        newstr.replace(
            newstr.begin() + std::distance(cbegin(),i1),
            newstr.begin() + std::distance(cbegin(),i2),
            first, last);
}

#if HAS_INITIALIZER_LIST
template<typename Char, typename Traits, typename Alloc>
basic_immutable_string<Char, Traits, Alloc>
basic_immutable_string<Char, Traits, Alloc>::replace(const_iterator i1, const_iterator i2, std::initializer_list<Char> il)  const
{
    std::basic_string<Char, Traits, Alloc> newstr(string_);
    return 
        newstr.replace(
            newstr.begin() + std::distance(cbegin(),i1),
            newstr.begin() + std::distance(cbegin(),i2),
            il);
}
#endif


template<typename Char, typename Traits, typename Alloc>
typename basic_immutable_string<Char, Traits, Alloc>::size_type const
basic_immutable_string<Char, Traits, Alloc>::find(basic_immutable_string const &str, size_type pos) const noexcept
{
    return string_.find(str.c_str(), pos);
}

template<typename Char, typename Traits, typename Alloc>
typename basic_immutable_string<Char, Traits, Alloc>::size_type const
basic_immutable_string<Char, Traits, Alloc>::find(std::basic_string<Char, Traits, Alloc> const &str, size_type pos) const noexcept
{
    return string_.find(str, pos);
}

template<typename Char, typename Traits, typename Alloc>
typename basic_immutable_string<Char, Traits, Alloc>::size_type const
basic_immutable_string<Char, Traits, Alloc>::find(Char const *s, size_type pos) const
{
    return string_.find(s, pos);
}

template<typename Char, typename Traits, typename Alloc>
typename basic_immutable_string<Char, Traits, Alloc>::size_type const
basic_immutable_string<Char, Traits, Alloc>::find(Char const *s, size_type pos, size_type n) const
{
    return string_.find(s, pos, n);
}

template<typename Char, typename Traits, typename Alloc>
typename basic_immutable_string<Char, Traits, Alloc>::size_type const
basic_immutable_string<Char, Traits, Alloc>::find(Char c, size_type pos) const noexcept
{
    return string_.find(c, pos);
}

template<typename Char, typename Traits, typename Alloc>
typename basic_immutable_string<Char, Traits, Alloc>::size_type const
basic_immutable_string<Char, Traits, Alloc>::rfind(basic_immutable_string const &str, size_type pos) const
{
    return string_.rfind(str.c_str(), pos);
}

template<typename Char, typename Traits, typename Alloc>
typename basic_immutable_string<Char, Traits, Alloc>::size_type const
basic_immutable_string<Char, Traits, Alloc>::rfind(std::basic_string<Char, Traits, Alloc> const &str, size_type pos) const
{
    return string_.rfind(str, pos);
}

template<typename Char, typename Traits, typename Alloc>
typename basic_immutable_string<Char, Traits, Alloc>::size_type const
basic_immutable_string<Char, Traits, Alloc>::rfind(Char const *s, size_type pos) const
{
    return string_.rfind(s, pos);
}

template<typename Char, typename Traits, typename Alloc>
typename basic_immutable_string<Char, Traits, Alloc>::size_type const
basic_immutable_string<Char, Traits, Alloc>::rfind(Char const *s, size_type pos, size_type n) const
{
    return string_.rfind(s, pos, n);
}

template<typename Char, typename Traits, typename Alloc>
typename basic_immutable_string<Char, Traits, Alloc>::size_type const
basic_immutable_string<Char, Traits, Alloc>::rfind(Char c, size_type pos) const
{
    return string_.rfind(c, pos);
}

template<typename Char, typename Traits, typename Alloc>
typename basic_immutable_string<Char, Traits, Alloc>::size_type const
basic_immutable_string<Char, Traits, Alloc>::find_first_of(basic_immutable_string const &str, size_type pos) const noexcept
{
    return string_.find_first_of(str.c_str(), pos);
}

template<typename Char, typename Traits, typename Alloc>
typename basic_immutable_string<Char, Traits, Alloc>::size_type const
basic_immutable_string<Char, Traits, Alloc>::find_first_of(std::basic_string<Char, Traits, Alloc> const &str, size_type pos) const noexcept
{
    return string_.find_first_of(str, pos);
}

template<typename Char, typename Traits, typename Alloc>
typename basic_immutable_string<Char, Traits, Alloc>::size_type const
basic_immutable_string<Char, Traits, Alloc>::find_first_of(Char const *s, size_type pos) const
{
    return string_.find_first_of(s, pos);
}

template<typename Char, typename Traits, typename Alloc>
typename basic_immutable_string<Char, Traits, Alloc>::size_type const
basic_immutable_string<Char, Traits, Alloc>::find_first_of(Char const *s, size_type pos, size_type n) const
{
    return string_.find_first_of(s, pos, n);
}

template<typename Char, typename Traits, typename Alloc>
typename basic_immutable_string<Char, Traits, Alloc>::size_type const
basic_immutable_string<Char, Traits, Alloc>::find_first_of(Char c, size_type pos) const noexcept
{
    return string_.find_first_of(c, pos);
}

template<typename Char, typename Traits, typename Alloc>
typename basic_immutable_string<Char, Traits, Alloc>::size_type const
basic_immutable_string<Char, Traits, Alloc>::find_last_of(basic_immutable_string const &str, size_type pos) const noexcept
{
    return string_.find_last_of(str.c_str(), pos);
}

template<typename Char, typename Traits, typename Alloc>
typename basic_immutable_string<Char, Traits, Alloc>::size_type const
basic_immutable_string<Char, Traits, Alloc>::find_last_of(std::basic_string<Char, Traits, Alloc> const &str, size_type pos) const noexcept
{
    return string_.find_last_of(str, pos);
}

template<typename Char, typename Traits, typename Alloc>
typename basic_immutable_string<Char, Traits, Alloc>::size_type const
basic_immutable_string<Char, Traits, Alloc>::find_last_of(Char const *s, size_type pos) const
{
    return string_.find_last_of(s, pos);
}

template<typename Char, typename Traits, typename Alloc>
typename basic_immutable_string<Char, Traits, Alloc>::size_type const
basic_immutable_string<Char, Traits, Alloc>::find_last_of(Char const *s, size_type pos, size_type n) const
{
    return string_.find_last_of(s, pos, n);
}

template<typename Char, typename Traits, typename Alloc>
typename basic_immutable_string<Char, Traits, Alloc>::size_type const
basic_immutable_string<Char, Traits, Alloc>::find_last_of(Char c, size_type pos) const noexcept
{
    return string_.find_last_of(c, pos);
}

template<typename Char, typename Traits, typename Alloc>
typename basic_immutable_string<Char, Traits, Alloc>::size_type const
basic_immutable_string<Char, Traits, Alloc>::find_first_not_of(basic_immutable_string const &str, size_type pos) const noexcept
{
    return string_.find_first_not_of(str.c_str(), pos);
}

template<typename Char, typename Traits, typename Alloc>
typename basic_immutable_string<Char, Traits, Alloc>::size_type const
basic_immutable_string<Char, Traits, Alloc>::find_first_not_of(std::basic_string<Char, Traits, Alloc> const &str, size_type pos) const noexcept
{
    return string_.find_first_not_of(str, pos);
}

template<typename Char, typename Traits, typename Alloc>
typename basic_immutable_string<Char, Traits, Alloc>::size_type const
basic_immutable_string<Char, Traits, Alloc>::find_first_not_of(Char const *s, size_type pos) const
{
    return string_.find_first_not_of(s, pos);
}

template<typename Char, typename Traits, typename Alloc>
typename basic_immutable_string<Char, Traits, Alloc>::size_type const
basic_immutable_string<Char, Traits, Alloc>::find_first_not_of(Char const *s, size_type pos, size_type n) const
{
    return string_.find_first_not_of(s, pos, n);
}

template<typename Char, typename Traits, typename Alloc>
typename basic_immutable_string<Char, Traits, Alloc>::size_type const
basic_immutable_string<Char, Traits, Alloc>::find_first_not_of(Char c, size_type pos) const noexcept
{
    return string_.find_first_not_of(c, pos);
}

template<typename Char, typename Traits, typename Alloc>
typename basic_immutable_string<Char, Traits, Alloc>::size_type const
basic_immutable_string<Char, Traits, Alloc>::find_last_not_of(basic_immutable_string const &str, size_type pos) const noexcept
{
    return string_.find_last_not_of(str.c_str(), pos);
}

template<typename Char, typename Traits, typename Alloc>
typename basic_immutable_string<Char, Traits, Alloc>::size_type const
basic_immutable_string<Char, Traits, Alloc>::find_last_not_of(std::basic_string<Char, Traits, Alloc> const &str, size_type pos) const noexcept
{
    return string_.find_last_not_of(str, pos);
}

template<typename Char, typename Traits, typename Alloc>
typename basic_immutable_string<Char, Traits, Alloc>::size_type const
basic_immutable_string<Char, Traits, Alloc>::find_last_not_of(Char const *s, size_type pos) const
{
    return string_.find_last_not_of(s, pos);
}

template<typename Char, typename Traits, typename Alloc>
typename basic_immutable_string<Char, Traits, Alloc>::size_type const
basic_immutable_string<Char, Traits, Alloc>::find_last_not_of(Char const *s, size_type pos, size_type n) const
{
    return string_.find_last_not_of(s, pos, n);
}

template<typename Char, typename Traits, typename Alloc>
typename basic_immutable_string<Char, Traits, Alloc>::size_type const
basic_immutable_string<Char, Traits, Alloc>::find_last_not_of(Char c, size_type pos) const noexcept
{
    return string_.find_last_not_of(c, pos);
}

/*
  addition operators
*/
template <typename Char, typename traits, typename Alloc>
basic_immutable_string<Char, traits, Alloc>
operator+(basic_immutable_string<Char, traits, Alloc> &&lhs, basic_immutable_string<Char, traits, Alloc> &&rhs)
{
    return lhs.append(std::forward<basic_immutable_string<Char, traits, Alloc>>(rhs));
}

template <typename Char, typename traits, typename Alloc>
basic_immutable_string<Char, traits, Alloc>
operator+(basic_immutable_string<Char, traits, Alloc> &&lhs, std::basic_string<Char, traits, Alloc> &&rhs)
{
    return lhs.append(std::forward<std::basic_string<Char, traits, Alloc>>(rhs));
}

template <typename Char, typename traits, typename Alloc>
basic_immutable_string<Char, traits, Alloc>
operator+(std::basic_string<Char, traits, Alloc> &&lhs, basic_immutable_string<Char, traits, Alloc> &&rhs)
{
    return lhs.append(rhs.c_str());
}

template <typename Char, typename traits, typename Alloc>
basic_immutable_string<Char, traits, Alloc>
operator+(basic_immutable_string<Char, traits, Alloc> const &lhs, basic_immutable_string<Char, traits, Alloc> const &rhs)
{
    return lhs.append(rhs);
}

template <typename Char, typename traits, typename Alloc>
basic_immutable_string<Char, traits, Alloc>
operator+(basic_immutable_string<Char, traits, Alloc> const &lhs, std::basic_string<Char, traits, Alloc> const &rhs)
{
    return lhs.append(rhs);
}

template <typename Char, typename traits, typename Alloc>
basic_immutable_string<Char, traits, Alloc>
operator+(std::basic_string<Char, traits, Alloc> const &lhs, basic_immutable_string<Char, traits, Alloc> const &rhs)
{
    return lhs + rhs.c_str();
}

template <typename Char, typename traits, typename Alloc>
basic_immutable_string<Char, traits, Alloc>
operator+(basic_immutable_string<Char, traits, Alloc> const &lhs, basic_immutable_string<Char, traits, Alloc> &&rhs)
{
    return lhs.append(std::forward<basic_immutable_string<Char, traits, Alloc>>(rhs));
}

template <typename Char, typename traits, typename Alloc>
basic_immutable_string<Char, traits, Alloc>
operator+(basic_immutable_string<Char, traits, Alloc> const &lhs, std::basic_string<Char, traits, Alloc> &&rhs)
{
    return lhs.append(std::forward<std::basic_string<Char, traits, Alloc>>(rhs));
}

template <typename Char, typename traits, typename Alloc>
basic_immutable_string<Char, traits, Alloc>
operator+(std::basic_string<Char, traits, Alloc> const &lhs, basic_immutable_string<Char, traits, Alloc> &&rhs)
{
    return lhs.append(rhs.c_str());
}

template <typename Char, typename traits, typename Alloc>
basic_immutable_string<Char, traits, Alloc>
operator+(basic_immutable_string<Char, traits, Alloc> &&lhs, basic_immutable_string<Char, traits, Alloc> const &rhs)
{
    return lhs.append(rhs);
}

template <typename Char, typename traits, typename Alloc>
basic_immutable_string<Char, traits, Alloc>
operator+(basic_immutable_string<Char, traits, Alloc> &&lhs, std::basic_string<Char, traits, Alloc> const &rhs)
{
    return lhs.append(rhs);
}

template <typename Char, typename traits, typename Alloc>
basic_immutable_string<Char, traits, Alloc>
operator+(std::basic_string<Char, traits, Alloc> &&lhs, basic_immutable_string<Char, traits, Alloc> const &rhs)
{
    return lhs.append(rhs.c_str());
}

template <typename Char, typename traits, typename Alloc>
basic_immutable_string<Char, traits, Alloc>
operator+(basic_immutable_string<Char, traits, Alloc> &&lhs, Char const *rhs)
{
    return lhs.append(rhs);
}

template <typename Char, typename traits, typename Alloc>
basic_immutable_string<Char, traits, Alloc>
operator+(basic_immutable_string<Char, traits, Alloc> const &lhs, Char const *rhs)
{
    return lhs.append(rhs);
}

template <typename Char, typename traits, typename Alloc>
basic_immutable_string<Char, traits, Alloc>
operator+(Char const *lhs, basic_immutable_string<Char, traits, Alloc> &&rhs)
{
    return basic_immutable_string<Char, traits, Alloc>(lhs).append(std::forward<basic_immutable_string<Char, traits, Alloc>>(rhs));
}

template <typename Char, typename traits, typename Alloc>
basic_immutable_string<Char, traits, Alloc>
operator+(Char const *lhs, basic_immutable_string<Char, traits, Alloc> const &rhs)
{
    return basic_immutable_string<Char, traits, Alloc>(lhs).append(rhs);
}

template <typename Char, typename traits, typename Alloc>
basic_immutable_string<Char, traits, Alloc>
operator+(basic_immutable_string<Char, traits, Alloc> &&lhs, Char rhs)
{
    return lhs.append(rhs);
}

template <typename Char, typename traits, typename Alloc>
basic_immutable_string<Char, traits, Alloc>
operator+(basic_immutable_string<Char, traits, Alloc> const &lhs, Char rhs)
{
    return lhs.append(rhs);
}

template <typename Char, typename traits, typename Alloc>
basic_immutable_string<Char, traits, Alloc>
operator+(Char lhs, basic_immutable_string<Char, traits, Alloc> &&rhs)
{
    return basic_immutable_string<Char, traits, Alloc>(lhs).append(std::forward<basic_immutable_string<Char, traits, Alloc>>(rhs));
}

template <typename Char, typename traits, typename Alloc>
basic_immutable_string<Char, traits, Alloc>
operator+(Char lhs, basic_immutable_string<Char, traits, Alloc> const &rhs)
{
    return basic_immutable_string<Char, traits, Alloc>(lhs).append(rhs);
}

template<typename Char, typename traits, typename Alloc>
std::basic_ostream<Char, traits> &operator<<(std::basic_ostream<Char, traits>& os, basic_immutable_string<Char, traits, Alloc> const &str)
{
    os << str.mutable_string();
    return os;
}

}   // namespace cdmh
