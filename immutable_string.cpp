#include <memory>
#include <string>

// "MSVC2013 Preview" didn't have initializer_list but _MSC_VER was defined 1800,
// so if you are using that compiler, you'll need to modify this condition
#if !defined(_MSC_VER)  ||  _MSC_VER > 1700
#define HAS_INITIALIZER_LIST 1
#include <initializer_list>
#endif

#ifdef __GNUC__
#define GCC_VERSION (__GNUC__ * 10000 \
                   + __GNUC_MINOR__ * 100 \
                   + __GNUC_PATCHLEVEL__)
#if GCC_VERSION <= 40801
#define _LIBSTDC_BUG_53221_WORKAROUND
#endif
#endif

namespace reliablecpp {

#if !defined(_MSC_VER)  ||  _MSC_VER <= 1800
#define noexcept throw()
#endif

template<typename charT,
         typename Traits = std::char_traits<charT>,    // basic_string::traits_type
         typename Alloc = std::allocator<charT>>       // basic_string::allocator_type
class basic_immutable_string
{
  public:
    typedef Traits traits_type;
    typedef Alloc  allocator_type;
    typedef charT  value_type;
    typedef typename Alloc::const_reference        const_reference;
    typedef typename Alloc::const_pointer          const_pointer;
    typedef typename Alloc::difference_type        difference_type;
    typedef typename Alloc::size_type              size_type;
    typedef typename std::basic_string<charT, Traits, Alloc>::const_iterator         const_iterator;
    typedef typename std::basic_string<charT, Traits, Alloc>::const_reverse_iterator const_reverse_iterator;

    static size_type const npos = (size_type)-1;

/* we are not defining the mutable types:
    typedef typename std::basic_string<charT, Traits, Alloc>::reference              reference;
    typedef typename std::basic_string<charT, Traits, Alloc>::pointer                pointer;
    typedef typename std::basic_string<charT, Traits, Alloc>::iterator               iterator;
    typedef typename std::basic_string<charT, Traits, Alloc>::reverse_iterator       reverse_iterator;
*/

    /*
      constructors
    */
    // default
    explicit basic_immutable_string(allocator_type const &alloc = allocator_type()) : string_(alloc) { }

    // copy
    basic_immutable_string(basic_immutable_string const &str) : string_(str.string_)                                     { }
#ifndef _LIBSTDC_BUG_53221_WORKAROUND
    basic_immutable_string(basic_immutable_string const &str, allocator_type const &alloc) : string_(str.string_, alloc) { }
#endif

    // substring
    basic_immutable_string(basic_immutable_string const &str, size_type pos, size_type len = npos,
                           allocator_type const &alloc = allocator_type()) : string_(str.string_, pos, len, alloc) { }

    // from c-string
    basic_immutable_string(charT const * const s, allocator_type const &alloc = allocator_type()) : string_(s, alloc) { }

    // from buffer
    basic_immutable_string(charT const * const s, size_type n,
                           allocator_type const &alloc = allocator_type()) : string_(s, n, alloc) { }

    // fill
    basic_immutable_string(size_type n, charT c,
                           allocator_type const &alloc = allocator_type()) : string_(n, c, alloc) { }

    basic_immutable_string(charT c, allocator_type const &alloc = allocator_type()) : string_(1, c, alloc) { }

    // range
    template <class InputIterator>
    basic_immutable_string(InputIterator first, InputIterator last,
                           allocator_type const &alloc = allocator_type()) : string_(first, last, alloc) { }
#if HAS_INITIALIZER_LIST
    // initializer list
    basic_immutable_string(std::initializer_list<charT> il,
                           allocator_type const &alloc = allocator_type()) : string_(il, alloc) { }
#endif

    // move
    basic_immutable_string(basic_immutable_string &&str) noexcept : string_(std::move(str.string_))                            { }
#ifndef _LIBSTDC_BUG_53221_WORKAROUND
    basic_immutable_string(basic_immutable_string &&str, allocator_type const &alloc) : string_(std::move(str.string_), alloc) { }
#endif

    // custom ctors (i.e. not from the C++ std::basic_string
    basic_immutable_string(std::basic_string<charT, Traits, Alloc> const &str) : string_(str) { }
    basic_immutable_string(std::basic_string<charT, Traits, Alloc> &&str) : string_(std::forward<std::basic_string<charT, Traits, Alloc>>(str)) { }

    int const compare(basic_immutable_string const &str)                                                const noexcept { return string_.compare(str.string_);                       }
    int const compare(std::basic_string<charT, Traits, Alloc> const &str)                               const noexcept { return string_.compare(str);                               }
    int const compare(size_type pos, size_type len, basic_immutable_string const &str)                  const          { return string_.compare(pos,len,str.string_);               }
    int const compare(size_type pos, size_type len, std::basic_string<charT, Traits, Alloc> const &str) const          { return string_.compare(pos,len,str);                       }
    int const compare(size_type pos, size_type len, basic_immutable_string const &str,   
                      size_type subpos, size_type sublen)                                               const          { return string_.compare(pos,len,str.string_,subpos,sublen); }
    int const compare(size_type pos, size_type len, std::basic_string<charT, Traits, Alloc> const &str,   
                      size_type subpos, size_type sublen)                                               const          { return string_.compare(pos,len,str,subpos,sublen);         }
    int const compare(charT const *s)                                                                   const          { return string_.compare(s);                                 }
    int const compare(size_type pos, size_type len, charT const *s)                                     const          { return string_.compare(pos,len,s);                         }
    int const compare(size_type pos, size_type len, charT const *s, size_type n)                        const          { return string_.compare(pos,len,s,n);                       }

    // Iterators
    const_iterator         cbegin(void)                                                  const noexcept { return string_.cbegin();               }
    const_iterator         cend(void)                                                    const noexcept { return string_.cend();                 }
    const_reverse_iterator crbegin(void)                                                 const noexcept { return string_.crbegin();              }
    const_reverse_iterator crend(void)                                                   const noexcept { return string_.crend();                }

    // Capacity
    bool             const empty(void)                                                   const noexcept { return string_.empty();                }
    size_type        const length(void)                                                  const noexcept { return string_.length();               }
    size_type        const size(void)                                                    const noexcept { return string_.size();                 }
    size_type        const max_size(void)                                                const noexcept { return string_.max_size();             }
    size_type        const capacity(void)                                                const noexcept { return string_.capacity();             }

    // Element access
    const_reference         operator[](size_type pos)                                    const          { return string_[pos];                   }
    const_reference         at(size_type pos)                                            const          { return string_.at(pos);                }
    charT            const &back(void)                                                   const          { return string_.back();                 }
    charT            const &front(void)                                                  const          { return string_.front();                }

    /*
      Modifiers
    */
    basic_immutable_string append(basic_immutable_string const &str)                                                         const;    // immutable string
    basic_immutable_string append(std::basic_string<charT, Traits, Alloc> const &str)                                        const;    // string
    basic_immutable_string append(basic_immutable_string const &str, size_type subpos, size_type sublen)                     const;    // substring (immutable source)
    basic_immutable_string append(std::basic_string<charT, Traits, Alloc> const &str, size_type subpos, size_type sublen)    const;    // substring
    basic_immutable_string append(charT const * const s)                                                                     const;    // c-string
    basic_immutable_string append(charT const * const s, size_type n)                                                        const;    // buffer
    basic_immutable_string append(size_type n, charT c)                                                                      const;    // fill
    basic_immutable_string append(charT c)                                                                                   const;
    template <class InputIterator>                                                                                           
    basic_immutable_string append(InputIterator first, InputIterator last)                                                   const;    // range
#if HAS_INITIALIZER_LIST                                                                                                     
    basic_immutable_string append(std::initializer_list<charT> il)                                                           const;    // initializer list
#endif                                                                                                                       

    basic_immutable_string insert(size_type pos, basic_immutable_string const &str)                                          const;    // immutable string
    basic_immutable_string insert(size_type pos, std::basic_string<charT, Traits, Alloc> const &str)                         const;    // string
    basic_immutable_string insert(size_type pos, basic_immutable_string const &str,                                                    // substring (immutable source)
                                  size_type subpos, size_type sublen)                                                        const;    // substring
    basic_immutable_string insert(size_type pos, std::basic_string<charT, Traits, Alloc> const &str,                         
                                  size_type subpos, size_type sublen)                                                        const;    // substring
    basic_immutable_string insert(size_type pos, charT const *s)                                                             const;    // c-string
    basic_immutable_string insert(size_type pos, charT const *s, size_type n)                                                const;    // buffer
    basic_immutable_string insert(size_type pos,   size_type n, charT c)                                                     const;    // fill
    basic_immutable_string insert(const_iterator p, size_type n, charT c)                                                    const;    // fill
    basic_immutable_string insert(const_iterator p, charT c)                                                                 const;    // single character
    template <class InputIterator>                                                                                           
    basic_immutable_string insert(const_iterator p, InputIterator first, InputIterator last)                                 const;    // range
#if HAS_INITIALIZER_LIST                                                                                                     
    basic_immutable_string insert(const_iterator p, std::initializer_list<charT> il)                                         const;    // initializer list
#endif                                                                                                                       

    basic_immutable_string erase(size_type pos=0, size_type len=npos)                                                        const;    // sequence
    basic_immutable_string erase(const_iterator p)                                                                           const;    // character
    basic_immutable_string erase(const_iterator first, const_iterator last)                                                  const;    // range


    basic_immutable_string replace(size_type pos,     size_type len,     basic_immutable_string const &str)                  const;    // string
    basic_immutable_string replace(size_type pos,     size_type len,     std::basic_string<charT, Traits, Alloc> const &str) const;    // string
    basic_immutable_string replace(const_iterator i1, const_iterator i2, basic_immutable_string const &str)                  const;    // string
    basic_immutable_string replace(const_iterator i1, const_iterator i2, std::basic_string<charT, Traits, Alloc> const &str) const;    // string

    basic_immutable_string replace(size_type pos, size_type len,
                                   basic_immutable_string const &str,
                                   size_type subpos, size_type sublen)                                                       const;    // substring
    basic_immutable_string replace(size_type pos, size_type len,
                                   std::basic_string<charT, Traits, Alloc> const &str,
                                   size_type subpos, size_type sublen)                                                       const;    // substring

    basic_immutable_string replace(size_type pos,     size_type len,     charT const *s)                                     const;    // c-string
    basic_immutable_string replace(const_iterator i1, const_iterator i2, charT const *s)                                     const;    // c-string

    basic_immutable_string replace(size_type pos,     size_type len,     charT const *s, size_type n)                        const;    // buffer
    basic_immutable_string replace(const_iterator i1, const_iterator i2, charT const *s, size_type n)                        const;    // buffer

    basic_immutable_string replace(size_type pos,     size_type len,     size_type n, charT c)                               const;    // fill
    basic_immutable_string replace(const_iterator i1, const_iterator i2, size_type n, charT c)                               const;    // fill

    template <class InputIterator>
    basic_immutable_string replace(const_iterator i1, const_iterator i2,
                                   InputIterator first, InputIterator last)                                                  const;    // range

#if HAS_INITIALIZER_LIST
    basic_immutable_string replace(const_iterator i1, const_iterator i2, std::initializer_list<charT> il)                    const;    // initializer list
#endif

    charT const *  c_str(void)                                  const noexcept { return string_.c_str();         }
    charT const *  data(void)                                   const noexcept { return string_.data();          }
    std::string    mutable_string(void)                         const          { return string_;                 }
    allocator_type get_allocator(void)                          const noexcept { return string_.get_allocator(); }
    size_type      copy(charT* s, size_type len, size_type pos) const          { return string_.copy(s,len,pos); }

    size_type const find(basic_immutable_string const &str, size_type pos=0)                                                 const noexcept;    // string
    size_type const find(std::basic_string<charT, Traits, Alloc> const &str, size_type pos=0)                                const noexcept;    // string
    size_type const find(charT const *s, size_type pos=0)                                                                    const;             // c-string
    size_type const find(charT const *s, size_type pos, size_type n)                                                         const;             // buffer
    size_type const find(charT c, size_type pos=0)                                                                           const noexcept;    // character

    size_type const rfind(basic_immutable_string const &str, size_type pos=npos)                                             const;             // string
    size_type const rfind(std::basic_string<charT, Traits, Alloc> const &str, size_type pos=npos)                            const;             // string
    size_type const rfind(charT const *s, size_type pos=npos)                                                                const;             // c-string
    size_type const rfind(charT const *s, size_type pos, size_type n)                                                        const;             // buffer
    size_type const rfind(charT c, size_type pos=npos)                                                                       const;             // character

    size_type const find_first_of(basic_immutable_string const &str, size_type pos=0)                                        const noexcept;    // string
    size_type const find_first_of(std::basic_string<charT, Traits, Alloc> const &str, size_type pos=0)                       const noexcept;    // string
    size_type const find_first_of(charT const *s, size_type pos=0)                                                           const;             // c-string
    size_type const find_first_of(charT const *s, size_type pos, size_type n)                                                const;             // buffer
    size_type const find_first_of(charT c, size_type pos=0)                                                                  const noexcept;    // character

    size_type const find_last_of(basic_immutable_string const &str, size_type pos=npos)                                      const noexcept;    // string
    size_type const find_last_of(std::basic_string<charT, Traits, Alloc> const &str, size_type pos=npos)                     const noexcept;    // string
    size_type const find_last_of(charT const *s, size_type pos=npos)                                                         const;             // c-string
    size_type const find_last_of(charT const *s, size_type pos, size_type n)                                                 const;             // buffer
    size_type const find_last_of(charT c, size_type pos=npos)                                                                const noexcept;    // character

    size_type const find_first_not_of(basic_immutable_string const &str, size_type pos=0)                                    const noexcept;    // string
    size_type const find_first_not_of(std::basic_string<charT, Traits, Alloc> const &str, size_type pos=0)                   const noexcept;    // string
    size_type const find_first_not_of(charT const *s, size_type pos=0)                                                       const;             // c-string
    size_type const find_first_not_of(charT const *s, size_type pos, size_type n)                                            const;             // buffer
    size_type const find_first_not_of(charT c, size_type pos=0)                                                              const noexcept;    // character

    size_type const find_last_not_of(basic_immutable_string const &str, size_type pos=npos)                                  const noexcept;    // string
    size_type const find_last_not_of(std::basic_string<charT, Traits, Alloc> const &str, size_type pos=npos)                 const noexcept;    // string
    size_type const find_last_not_of(charT const *s, size_type pos=npos)                                                     const;             // c-string
    size_type const find_last_not_of(charT const *s, size_type pos, size_type n)                                             const;             // buffer
    size_type const find_last_not_of(charT c, size_type pos=npos)                                                            const noexcept;    // character

    basic_immutable_string substr(size_type pos=0, size_type len=npos) const { return basic_immutable_string(*this, pos, len); }

    ///!!! maybe modifiers should return a shouty value to warn against non-assignment?
/*
  Capacity:
     resize()
     reserve()
     clear()
     shrink_to_fit

 Element access
    reference operator[] (size_type pos);
    reference at (size_type pos);
    charT &back();
    charT &front();

  Modifiers
    operator+=
    push_back
    assign
    swap
    pop_back

  free functions
    swap
    operator>>
    getline
*/

  private:
    // the encapsulated string is not declared const as this would
    // prevent the object being moved, which may be important in
    // some situations for performance
    std::basic_string<charT, Traits, Alloc> string_;

#if !defined(_MSC_VER)  ||  _MSC_VER < 1800
    // private assignment operator prevents compiler generator function
    basic_immutable_string &operator=(basic_immutable_string);
#else
    basic_immutable_string &operator=(basic_immutable_string) = delete;
#endif
};

#if 1
// comparison with another string instance
template<typename charT, typename Traits, typename Alloc>
bool operator==(basic_immutable_string<charT, Traits, Alloc> const &lhs, basic_immutable_string<charT, Traits, Alloc> const &rhs) {
    return lhs.compare(rhs) == 0;
}

template<typename charT, typename Traits, typename Alloc>
bool operator!=(basic_immutable_string<charT, Traits, Alloc> const &lhs, basic_immutable_string<charT, Traits, Alloc> const &rhs) {
    return !(lhs == rhs);
}

template<typename charT, typename Traits, typename Alloc>
bool operator<(basic_immutable_string<charT, Traits, Alloc> const &lhs, basic_immutable_string<charT, Traits, Alloc> const &rhs) {
    return lhs.compare(rhs) < 0;
}

template<typename charT, typename Traits, typename Alloc>
bool operator<=(basic_immutable_string<charT, Traits, Alloc> const &lhs, basic_immutable_string<charT, Traits, Alloc> const &rhs) {
    return lhs.compare(rhs) <= 0;
}

template<typename charT, typename Traits, typename Alloc>
bool operator>(basic_immutable_string<charT, Traits, Alloc> const &lhs, basic_immutable_string<charT, Traits, Alloc> const &rhs) {
    return lhs.compare(rhs) > 0;
}

template<typename charT, typename Traits, typename Alloc>
bool operator>=(basic_immutable_string<charT, Traits, Alloc> const &lhs, basic_immutable_string<charT, Traits, Alloc> const &rhs) {
    return lhs.compare(rhs) >= 0;
}


// comparison with Standard Library basic_string
template<typename charT, typename Traits, typename Alloc>
bool operator==(basic_immutable_string<charT, Traits, Alloc> const &lhs, std::basic_string<charT, Traits, Alloc> const &rhs) {
    return lhs.compare(rhs) == 0;
}

template<typename charT, typename Traits, typename Alloc>
bool operator!=(basic_immutable_string<charT, Traits, Alloc> const &lhs, std::basic_string<charT, Traits, Alloc> const &rhs) {
    return !(lhs == rhs);
}

template<typename charT, typename Traits, typename Alloc>
bool operator<(basic_immutable_string<charT, Traits, Alloc> const &lhs, std::basic_string<charT, Traits, Alloc> const &rhs) {
    return lhs.compare(rhs) < 0;
}

template<typename charT, typename Traits, typename Alloc>
bool operator<=(basic_immutable_string<charT, Traits, Alloc> const &lhs, std::basic_string<charT, Traits, Alloc> const &rhs) {
    return lhs.compare(rhs) <= 0;
}

template<typename charT, typename Traits, typename Alloc>
bool operator>(basic_immutable_string<charT, Traits, Alloc> const &lhs, std::basic_string<charT, Traits, Alloc> const &rhs) {
    return lhs.compare(rhs) > 0;
}

template<typename charT, typename Traits, typename Alloc>
bool operator>=(basic_immutable_string<charT, Traits, Alloc> const &lhs, std::basic_string<charT, Traits, Alloc> const &rhs) {
    return lhs.compare(rhs) >= 0;
}

template<typename charT, typename Traits, typename Alloc>
bool operator==(std::basic_string<charT, Traits, Alloc> const &lhs, basic_immutable_string<charT, Traits, Alloc> const &rhs) {
    return rhs.compare(lhs) == 0;
}

template<typename charT, typename Traits, typename Alloc>
bool operator!=(std::basic_string<charT, Traits, Alloc> const &lhs, basic_immutable_string<charT, Traits, Alloc> const &rhs) {
    return !(lhs == rhs);
}

template<typename charT, typename Traits, typename Alloc>
bool operator<(std::basic_string<charT, Traits, Alloc> const &lhs, basic_immutable_string<charT, Traits, Alloc> const &rhs) {
    return rhs.compare(lhs) > 0;
}

template<typename charT, typename Traits, typename Alloc>
bool operator<=(std::basic_string<charT, Traits, Alloc> const &lhs, basic_immutable_string<charT, Traits, Alloc> const &rhs) {
    return rhs.compare(lhs) >= 0;
}

template<typename charT, typename Traits, typename Alloc>
bool operator>(std::basic_string<charT, Traits, Alloc> const &lhs, basic_immutable_string<charT, Traits, Alloc> const &rhs) {
    return rhs.compare(lhs) < 0;
}

template<typename charT, typename Traits, typename Alloc>
bool operator>=(std::basic_string<charT, Traits, Alloc> const &lhs, basic_immutable_string<charT, Traits, Alloc> const &rhs) {
    return rhs.compare(lhs) <= 0;
}



// comparison to charT*
template<typename charT, typename Traits, typename Alloc>
bool operator==(charT const * const lhs, basic_immutable_string<charT, Traits, Alloc> const &rhs) {
    return rhs.compare(lhs) == 0;
}


template<typename charT, typename Traits, typename Alloc>
bool operator==(basic_immutable_string<charT, Traits, Alloc> const &lhs, charT const * const rhs) {
    return lhs.compare(rhs) == 0;
}


template<typename charT, typename Traits, typename Alloc>
bool operator!=(charT const * const lhs, basic_immutable_string<charT, Traits, Alloc> const &rhs) {
    return !(rhs == lhs);
}


template<typename charT, typename Traits, typename Alloc>
bool operator!=(basic_immutable_string<charT, Traits, Alloc> const &lhs, charT const * const rhs) {
    return !(lhs == rhs);
}


template<typename charT, typename Traits, typename Alloc>
bool operator<(charT const * const lhs, basic_immutable_string<charT, Traits, Alloc> const &rhs) {
    return rhs.compare(lhs) > 0;
}


template<typename charT, typename Traits, typename Alloc>
bool operator<(basic_immutable_string<charT, Traits, Alloc> const &lhs,  charT const * const rhs) {
    return lhs.compare(rhs) < 0;
}


template<typename charT, typename Traits, typename Alloc>
bool operator<=(charT const * const lhs, basic_immutable_string<charT, Traits, Alloc> const &rhs) {
    return rhs.compare(lhs) >= 0;
}


template<typename charT, typename Traits, typename Alloc>
bool operator<=(basic_immutable_string<charT, Traits, Alloc> const &lhs, charT const * const rhs) {
    return lhs.compare(rhs) <= 0;
}


template<typename charT, typename Traits, typename Alloc>
bool operator>(charT const * const lhs, basic_immutable_string<charT, Traits, Alloc> const &rhs) {
    return rhs.compare(lhs) < 0;
}


template<typename charT, typename Traits, typename Alloc>
bool operator>(basic_immutable_string<charT, Traits, Alloc> const &lhs, charT const * const rhs) {
    return lhs.compare(rhs) > 0;
}


template<typename charT, typename Traits, typename Alloc>
bool operator>=(charT const * const lhs, basic_immutable_string<charT, Traits, Alloc> const &rhs) {
    return rhs.compare(lhs) <= 0;
}


template<typename charT, typename Traits, typename Alloc>
bool operator>=(basic_immutable_string<charT, Traits, Alloc> const &lhs, charT const * const rhs) {
    return lhs.compare(rhs) >= 0;
}

template<typename charT, typename Traits, typename Alloc>
basic_immutable_string<charT, Traits, Alloc>
basic_immutable_string<charT, Traits, Alloc>::append(basic_immutable_string const &str) const
{
    return string_ + str.string_;     // ctor 10.2
}

template<typename charT, typename Traits, typename Alloc>
basic_immutable_string<charT, Traits, Alloc>
basic_immutable_string<charT, Traits, Alloc>::append(std::basic_string<charT, Traits, Alloc> const &str) const
{
    return string_ + str;
}

template<typename charT, typename Traits, typename Alloc>
basic_immutable_string<charT, Traits, Alloc>
basic_immutable_string<charT, Traits, Alloc>::append(basic_immutable_string const &str, size_type subpos, size_type sublen) const
{
    return string_ + str.string_.substr(subpos, sublen);//!!!
}

template<typename charT, typename Traits, typename Alloc>
basic_immutable_string<charT, Traits, Alloc>
basic_immutable_string<charT, Traits, Alloc>::append(std::basic_string<charT, Traits, Alloc> const &str, size_type subpos, size_type sublen) const
{
    return string_ + str.substr(subpos, sublen);
}

template<typename charT, typename Traits, typename Alloc>
basic_immutable_string<charT, Traits, Alloc>
basic_immutable_string<charT, Traits, Alloc>::append(charT const * const s) const
{
    return std::basic_string<charT, Traits, Alloc>(string_ + s);
}

template<typename charT, typename Traits, typename Alloc>
basic_immutable_string<charT, Traits, Alloc>
basic_immutable_string<charT, Traits, Alloc>::append(charT const * const s, size_type n) const
{
    return string_ + std::basic_string<charT, Traits, Alloc>(s, n);
}

template<typename charT, typename Traits, typename Alloc>
basic_immutable_string<charT, Traits, Alloc>
basic_immutable_string<charT, Traits, Alloc>::append(size_type n, charT c) const
{
    return string_ + std::basic_string<charT, Traits, Alloc>(n, c);
}

template<typename charT, typename Traits, typename Alloc>
basic_immutable_string<charT, Traits, Alloc>
basic_immutable_string<charT, Traits, Alloc>::append(charT c) const
{
    return string_ + c;
}

template<typename charT, typename Traits, typename Alloc>
template <class InputIterator>
basic_immutable_string<charT, Traits, Alloc>
basic_immutable_string<charT, Traits, Alloc>::append(InputIterator first, InputIterator last) const
{
    return string_ + std::basic_string<charT, Traits, Alloc>(first, last);
}

#if HAS_INITIALIZER_LIST
template<typename charT, typename Traits, typename Alloc>
basic_immutable_string<charT, Traits, Alloc>
basic_immutable_string<charT, Traits, Alloc>::append(std::initializer_list<charT> il) const
{
    return string_ + std::basic_string<charT, Traits, Alloc>(il);
}
#endif

template<typename charT, typename Traits, typename Alloc>
basic_immutable_string<charT, Traits, Alloc>
basic_immutable_string<charT, Traits, Alloc>::insert(size_type pos, basic_immutable_string<charT, Traits, Alloc> const &str) const
{
    return std::basic_string<charT, Traits, Alloc>(string_).insert(pos, str.string_);
}

template<typename charT, typename Traits, typename Alloc>
basic_immutable_string<charT, Traits, Alloc>
basic_immutable_string<charT, Traits, Alloc>::insert(size_type pos, std::basic_string<charT, Traits, Alloc> const &str) const
{
    return std::basic_string<charT, Traits, Alloc>(string_).insert(pos, str);
}

template<typename charT, typename Traits, typename Alloc>
basic_immutable_string<charT, Traits, Alloc>
basic_immutable_string<charT, Traits, Alloc>::insert(size_type pos, basic_immutable_string<charT, Traits, Alloc> const &str,
                                                     size_type subpos, size_type sublen) const
{
    return std::basic_string<charT, Traits, Alloc>(string_).insert(pos, str.string_, subpos, sublen);
}

template<typename charT, typename Traits, typename Alloc>
basic_immutable_string<charT, Traits, Alloc>
basic_immutable_string<charT, Traits, Alloc>::insert(size_type pos, std::basic_string<charT, Traits, Alloc> const &str,
                                                     size_type subpos, size_type sublen) const
{
    return std::basic_string<charT, Traits, Alloc>(string_).insert(pos, str, subpos, sublen);
}

template<typename charT, typename Traits, typename Alloc>
basic_immutable_string<charT, Traits, Alloc>
basic_immutable_string<charT, Traits, Alloc>::insert(size_type pos, charT const *s) const
{
    return std::basic_string<charT, Traits, Alloc>(string_).insert(pos, s);
}

template<typename charT, typename Traits, typename Alloc>
basic_immutable_string<charT, Traits, Alloc>
basic_immutable_string<charT, Traits, Alloc>::insert(size_type pos, charT const *s, size_type n) const
{
    return std::basic_string<charT, Traits, Alloc>(string_).insert(pos, s, n);
}

template<typename charT, typename Traits, typename Alloc>
basic_immutable_string<charT, Traits, Alloc>
basic_immutable_string<charT, Traits, Alloc>::insert(size_type pos, size_type n, charT c) const
{
    return std::basic_string<charT, Traits, Alloc>(string_).insert(pos, n, c);
}

template<typename charT, typename Traits, typename Alloc>
basic_immutable_string<charT, Traits, Alloc>
basic_immutable_string<charT, Traits, Alloc>::insert(const_iterator p, size_type n, charT c) const
{
    std::basic_string<charT, Traits, Alloc> str(string_);
    str.insert(str.begin() + std::distance(cbegin(),p), n, c);
    return str;
}

template<typename charT, typename Traits, typename Alloc>
basic_immutable_string<charT, Traits, Alloc>
basic_immutable_string<charT, Traits, Alloc>::insert(const_iterator p, charT c) const
{
    std::basic_string<charT, Traits, Alloc> str(string_);
    str.insert(str.begin() + std::distance(cbegin(),p), c);
    return str;
}

template<typename charT, typename Traits, typename Alloc>
template <class InputIterator>
basic_immutable_string<charT, Traits, Alloc>
basic_immutable_string<charT, Traits, Alloc>::insert(const_iterator p, InputIterator first, InputIterator last) const
{
    std::basic_string<charT, Traits, Alloc> str(string_);
    str.insert(str.begin() + std::distance(cbegin(),p), first, last);
    return str;
}

#if HAS_INITIALIZER_LIST
template<typename charT, typename Traits, typename Alloc>
basic_immutable_string<charT, Traits, Alloc>
basic_immutable_string<charT, Traits, Alloc>::insert(const_iterator p, std::initializer_list<charT> il) const
{
    std::basic_string<charT, Traits, Alloc> str(string_);
    str.insert(str.begin() + std::distance(cbegin(),p), il);
    return str;
}
#endif

template<typename charT, typename Traits, typename Alloc>
basic_immutable_string<charT, Traits, Alloc>
basic_immutable_string<charT, Traits, Alloc>::erase(size_type pos, size_type len) const
{
    return std::basic_string<charT, Traits, Alloc>(string_).erase(pos,len);
}

template<typename charT, typename Traits, typename Alloc>
basic_immutable_string<charT, Traits, Alloc>
basic_immutable_string<charT, Traits, Alloc>::erase(const_iterator p) const
{
    std::basic_string<charT, Traits, Alloc> str(string_);
    str.erase(str.begin() + std::distance(cbegin(),p));
    return str;
}

template<typename charT, typename Traits, typename Alloc>
basic_immutable_string<charT, Traits, Alloc>
basic_immutable_string<charT, Traits, Alloc>::erase(const_iterator first, const_iterator last) const
{
    std::basic_string<charT, Traits, Alloc> str(string_);
    str.erase(str.begin() + std::distance(cbegin(),first), str.begin() + std::distance(cbegin(), last));
    return str;
}

template<typename charT, typename Traits, typename Alloc>
basic_immutable_string<charT, Traits, Alloc>
basic_immutable_string<charT, Traits, Alloc>::replace(size_type pos, size_type len, basic_immutable_string const &str) const
{
    return std::basic_string<charT, Traits, Alloc>(string_).replace(pos,len,str.string_);
}

template<typename charT, typename Traits, typename Alloc>
basic_immutable_string<charT, Traits, Alloc>
basic_immutable_string<charT, Traits, Alloc>::replace(size_type pos, size_type len, std::basic_string<charT, Traits, Alloc> const &str) const
{
    return std::basic_string<charT, Traits, Alloc>(string_).replace(pos,len,str);
}

template<typename charT, typename Traits, typename Alloc>
basic_immutable_string<charT, Traits, Alloc>
basic_immutable_string<charT, Traits, Alloc>::replace(const_iterator i1, const_iterator i2, basic_immutable_string const &str) const
{
    std::basic_string<charT, Traits, Alloc> newstr(string_);
    return 
        newstr.replace(
            newstr.begin() + std::distance(cbegin(),i1),
            newstr.begin() + std::distance(cbegin(),i2),
            str.string_);
}

template<typename charT, typename Traits, typename Alloc>
basic_immutable_string<charT, Traits, Alloc>
basic_immutable_string<charT, Traits, Alloc>::replace(const_iterator i1, const_iterator i2, std::basic_string<charT, Traits, Alloc> const &str) const
{
    std::basic_string<charT, Traits, Alloc> newstr(string_);
    return
        newstr.replace(
            newstr.begin() + std::distance(cbegin(),i1),
            newstr.begin() + std::distance(cbegin(),i2),
            str);
}

template<typename charT, typename Traits, typename Alloc>
basic_immutable_string<charT, Traits, Alloc>
basic_immutable_string<charT, Traits, Alloc>::replace(size_type pos, size_type len,
                                                      basic_immutable_string const &str,
                                                      size_type subpos, size_type sublen) const
{
    return std::basic_string<charT, Traits, Alloc>(string_).replace(pos, len, str.string_, subpos, sublen);
}

template<typename charT, typename Traits, typename Alloc>
basic_immutable_string<charT, Traits, Alloc>
basic_immutable_string<charT, Traits, Alloc>::replace(size_type pos, size_type len,
                                                      std::basic_string<charT, Traits, Alloc> const &str,
                                                      size_type subpos, size_type sublen) const
{
    return std::basic_string<charT, Traits, Alloc>(string_).replace(pos, len, str, subpos, sublen);
}

template<typename charT, typename Traits, typename Alloc>
basic_immutable_string<charT, Traits, Alloc>
basic_immutable_string<charT, Traits, Alloc>::replace(size_type pos, size_type len, charT const *s) const
{
    return std::basic_string<charT, Traits, Alloc>(string_).replace(pos, len, s);
}

template<typename charT, typename Traits, typename Alloc>
basic_immutable_string<charT, Traits, Alloc>
basic_immutable_string<charT, Traits, Alloc>::replace(const_iterator i1, const_iterator i2, charT const *s) const
{
    std::basic_string<charT, Traits, Alloc> newstr(string_);
    return 
        newstr.replace(
            newstr.begin() + std::distance(cbegin(),i1),
            newstr.begin() + std::distance(cbegin(),i2),
            s);
}

template<typename charT, typename Traits, typename Alloc>
basic_immutable_string<charT, Traits, Alloc>
basic_immutable_string<charT, Traits, Alloc>::replace(size_type pos, size_type len, charT const *s, size_type n) const
{
    return std::basic_string<charT, Traits, Alloc>(string_).replace(pos, len, s, n);
}

template<typename charT, typename Traits, typename Alloc>
basic_immutable_string<charT, Traits, Alloc>
basic_immutable_string<charT, Traits, Alloc>::replace(const_iterator i1, const_iterator i2, charT const *s, size_type n) const
{
    std::basic_string<charT, Traits, Alloc> newstr(string_);
    return
        newstr.replace(
            newstr.begin() + std::distance(cbegin(),i1),
            newstr.begin() + std::distance(cbegin(),i2),
            s, n);
}

template<typename charT, typename Traits, typename Alloc>
basic_immutable_string<charT, Traits, Alloc>
basic_immutable_string<charT, Traits, Alloc>::replace(size_type pos, size_type len, size_type n, charT c) const
{
    return std::basic_string<charT, Traits, Alloc>(string_).replace(pos, len, n, c);
}

template<typename charT, typename Traits, typename Alloc>
basic_immutable_string<charT, Traits, Alloc>
basic_immutable_string<charT, Traits, Alloc>::replace(const_iterator i1, const_iterator i2, size_type n, charT c) const
{
    std::basic_string<charT, Traits, Alloc> newstr(string_);
    return 
        newstr.replace(
            newstr.begin() + std::distance(cbegin(),i1),
            newstr.begin() + std::distance(cbegin(),i2),
            n, c);
}

template<typename charT, typename Traits, typename Alloc>
template <class InputIterator>
basic_immutable_string<charT, Traits, Alloc>
basic_immutable_string<charT, Traits, Alloc>::replace(const_iterator i1, const_iterator i2,
                                                      InputIterator first, InputIterator last) const
{
    std::basic_string<charT, Traits, Alloc> newstr(string_);
    return 
        newstr.replace(
            newstr.begin() + std::distance(cbegin(),i1),
            newstr.begin() + std::distance(cbegin(),i2),
            first, last);
}

#if HAS_INITIALIZER_LIST
template<typename charT, typename Traits, typename Alloc>
basic_immutable_string<charT, Traits, Alloc>
basic_immutable_string<charT, Traits, Alloc>::replace(const_iterator i1, const_iterator i2, std::initializer_list<charT> il)  const
{
    std::basic_string<charT, Traits, Alloc> newstr(string_);
    return 
        newstr.replace(
            newstr.begin() + std::distance(cbegin(),i1),
            newstr.begin() + std::distance(cbegin(),i2),
            il);
}
#endif


template<typename charT, typename Traits, typename Alloc>
typename basic_immutable_string<charT, Traits, Alloc>::size_type const
basic_immutable_string<charT, Traits, Alloc>::find(basic_immutable_string const &str, size_type pos) const noexcept
{
    return string_.find(str.c_str(), pos);
}

template<typename charT, typename Traits, typename Alloc>
typename basic_immutable_string<charT, Traits, Alloc>::size_type const
basic_immutable_string<charT, Traits, Alloc>::find(std::basic_string<charT, Traits, Alloc> const &str, size_type pos) const noexcept
{
    return string_.find(str, pos);
}

template<typename charT, typename Traits, typename Alloc>
typename basic_immutable_string<charT, Traits, Alloc>::size_type const
basic_immutable_string<charT, Traits, Alloc>::find(charT const *s, size_type pos) const
{
    return string_.find(s, pos);
}

template<typename charT, typename Traits, typename Alloc>
typename basic_immutable_string<charT, Traits, Alloc>::size_type const
basic_immutable_string<charT, Traits, Alloc>::find(charT const *s, size_type pos, size_type n) const
{
    return string_.find(s, pos, n);
}

template<typename charT, typename Traits, typename Alloc>
typename basic_immutable_string<charT, Traits, Alloc>::size_type const
basic_immutable_string<charT, Traits, Alloc>::find(charT c, size_type pos) const noexcept
{
    return string_.find(c, pos);
}

template<typename charT, typename Traits, typename Alloc>
typename basic_immutable_string<charT, Traits, Alloc>::size_type const
basic_immutable_string<charT, Traits, Alloc>::rfind(basic_immutable_string const &str, size_type pos) const
{
    return string_.rfind(str.c_str(), pos);
}

template<typename charT, typename Traits, typename Alloc>
typename basic_immutable_string<charT, Traits, Alloc>::size_type const
basic_immutable_string<charT, Traits, Alloc>::rfind(std::basic_string<charT, Traits, Alloc> const &str, size_type pos) const
{
    return string_.rfind(str, pos);
}

template<typename charT, typename Traits, typename Alloc>
typename basic_immutable_string<charT, Traits, Alloc>::size_type const
basic_immutable_string<charT, Traits, Alloc>::rfind(charT const *s, size_type pos) const
{
    return string_.rfind(s, pos);
}

template<typename charT, typename Traits, typename Alloc>
typename basic_immutable_string<charT, Traits, Alloc>::size_type const
basic_immutable_string<charT, Traits, Alloc>::rfind(charT const *s, size_type pos, size_type n) const
{
    return string_.rfind(s, pos, n);
}

template<typename charT, typename Traits, typename Alloc>
typename basic_immutable_string<charT, Traits, Alloc>::size_type const
basic_immutable_string<charT, Traits, Alloc>::rfind(charT c, size_type pos) const
{
    return string_.rfind(c, pos);
}

template<typename charT, typename Traits, typename Alloc>
typename basic_immutable_string<charT, Traits, Alloc>::size_type const
basic_immutable_string<charT, Traits, Alloc>::find_first_of(basic_immutable_string const &str, size_type pos) const noexcept
{
    return string_.find_first_of(str.c_str(), pos);
}

template<typename charT, typename Traits, typename Alloc>
typename basic_immutable_string<charT, Traits, Alloc>::size_type const
basic_immutable_string<charT, Traits, Alloc>::find_first_of(std::basic_string<charT, Traits, Alloc> const &str, size_type pos) const noexcept
{
    return string_.find_first_of(str, pos);
}

template<typename charT, typename Traits, typename Alloc>
typename basic_immutable_string<charT, Traits, Alloc>::size_type const
basic_immutable_string<charT, Traits, Alloc>::find_first_of(charT const *s, size_type pos) const
{
    return string_.find_first_of(s, pos);
}

template<typename charT, typename Traits, typename Alloc>
typename basic_immutable_string<charT, Traits, Alloc>::size_type const
basic_immutable_string<charT, Traits, Alloc>::find_first_of(charT const *s, size_type pos, size_type n) const
{
    return string_.find_first_of(s, pos, n);
}

template<typename charT, typename Traits, typename Alloc>
typename basic_immutable_string<charT, Traits, Alloc>::size_type const
basic_immutable_string<charT, Traits, Alloc>::find_first_of(charT c, size_type pos) const noexcept
{
    return string_.find_first_of(c, pos);
}

template<typename charT, typename Traits, typename Alloc>
typename basic_immutable_string<charT, Traits, Alloc>::size_type const
basic_immutable_string<charT, Traits, Alloc>::find_last_of(basic_immutable_string const &str, size_type pos) const noexcept
{
    return string_.find_last_of(str.c_str(), pos);
}

template<typename charT, typename Traits, typename Alloc>
typename basic_immutable_string<charT, Traits, Alloc>::size_type const
basic_immutable_string<charT, Traits, Alloc>::find_last_of(std::basic_string<charT, Traits, Alloc> const &str, size_type pos) const noexcept
{
    return string_.find_last_of(str, pos);
}

template<typename charT, typename Traits, typename Alloc>
typename basic_immutable_string<charT, Traits, Alloc>::size_type const
basic_immutable_string<charT, Traits, Alloc>::find_last_of(charT const *s, size_type pos) const
{
    return string_.find_last_of(s, pos);
}

template<typename charT, typename Traits, typename Alloc>
typename basic_immutable_string<charT, Traits, Alloc>::size_type const
basic_immutable_string<charT, Traits, Alloc>::find_last_of(charT const *s, size_type pos, size_type n) const
{
    return string_.find_last_of(s, pos, n);
}

template<typename charT, typename Traits, typename Alloc>
typename basic_immutable_string<charT, Traits, Alloc>::size_type const
basic_immutable_string<charT, Traits, Alloc>::find_last_of(charT c, size_type pos) const noexcept
{
    return string_.find_last_of(c, pos);
}

template<typename charT, typename Traits, typename Alloc>
typename basic_immutable_string<charT, Traits, Alloc>::size_type const
basic_immutable_string<charT, Traits, Alloc>::find_first_not_of(basic_immutable_string const &str, size_type pos) const noexcept
{
    return string_.find_first_not_of(str.c_str(), pos);
}

template<typename charT, typename Traits, typename Alloc>
typename basic_immutable_string<charT, Traits, Alloc>::size_type const
basic_immutable_string<charT, Traits, Alloc>::find_first_not_of(std::basic_string<charT, Traits, Alloc> const &str, size_type pos) const noexcept
{
    return string_.find_first_not_of(str, pos);
}

template<typename charT, typename Traits, typename Alloc>
typename basic_immutable_string<charT, Traits, Alloc>::size_type const
basic_immutable_string<charT, Traits, Alloc>::find_first_not_of(charT const *s, size_type pos) const
{
    return string_.find_first_not_of(s, pos);
}

template<typename charT, typename Traits, typename Alloc>
typename basic_immutable_string<charT, Traits, Alloc>::size_type const
basic_immutable_string<charT, Traits, Alloc>::find_first_not_of(charT const *s, size_type pos, size_type n) const
{
    return string_.find_first_not_of(s, pos, n);
}

template<typename charT, typename Traits, typename Alloc>
typename basic_immutable_string<charT, Traits, Alloc>::size_type const
basic_immutable_string<charT, Traits, Alloc>::find_first_not_of(charT c, size_type pos) const noexcept
{
    return string_.find_first_not_of(c, pos);
}

template<typename charT, typename Traits, typename Alloc>
typename basic_immutable_string<charT, Traits, Alloc>::size_type const
basic_immutable_string<charT, Traits, Alloc>::find_last_not_of(basic_immutable_string const &str, size_type pos) const noexcept
{
    return string_.find_last_not_of(str.c_str(), pos);
}

template<typename charT, typename Traits, typename Alloc>
typename basic_immutable_string<charT, Traits, Alloc>::size_type const
basic_immutable_string<charT, Traits, Alloc>::find_last_not_of(std::basic_string<charT, Traits, Alloc> const &str, size_type pos) const noexcept
{
    return string_.find_last_not_of(str, pos);
}

template<typename charT, typename Traits, typename Alloc>
typename basic_immutable_string<charT, Traits, Alloc>::size_type const
basic_immutable_string<charT, Traits, Alloc>::find_last_not_of(charT const *s, size_type pos) const
{
    return string_.find_last_not_of(s, pos);
}

template<typename charT, typename Traits, typename Alloc>
typename basic_immutable_string<charT, Traits, Alloc>::size_type const
basic_immutable_string<charT, Traits, Alloc>::find_last_not_of(charT const *s, size_type pos, size_type n) const
{
    return string_.find_last_not_of(s, pos, n);
}

template<typename charT, typename Traits, typename Alloc>
typename basic_immutable_string<charT, Traits, Alloc>::size_type const
basic_immutable_string<charT, Traits, Alloc>::find_last_not_of(charT c, size_type pos) const noexcept
{
    return string_.find_last_not_of(c, pos);
}

/*
  addition operators
*/
template <typename charT, typename traits, typename Alloc>
basic_immutable_string<charT, traits, Alloc>
operator+(basic_immutable_string<charT, traits, Alloc> &&lhs, basic_immutable_string<charT, traits, Alloc> &&rhs)
{
    return lhs.append(std::forward<basic_immutable_string<charT, traits, Alloc>>(rhs));
}

template <typename charT, typename traits, typename Alloc>
basic_immutable_string<charT, traits, Alloc>
operator+(basic_immutable_string<charT, traits, Alloc> &&lhs, std::basic_string<charT, traits, Alloc> &&rhs)
{
    return lhs.append(std::forward<std::basic_string<charT, traits, Alloc>>(rhs));
}

template <typename charT, typename traits, typename Alloc>
basic_immutable_string<charT, traits, Alloc>
operator+(std::basic_string<charT, traits, Alloc> &&lhs, basic_immutable_string<charT, traits, Alloc> &&rhs)
{
    return lhs + std::forward<basic_immutable_string<charT, traits, Alloc>>(rhs);
}

template <typename charT, typename traits, typename Alloc>
basic_immutable_string<charT, traits, Alloc>
operator+(basic_immutable_string<charT, traits, Alloc> const &lhs, basic_immutable_string<charT, traits, Alloc> const &rhs)
{
    return lhs.append(rhs);
}

template <typename charT, typename traits, typename Alloc>
basic_immutable_string<charT, traits, Alloc>
operator+(basic_immutable_string<charT, traits, Alloc> const &lhs, std::basic_string<charT, traits, Alloc> const &rhs)
{
    return lhs.append(rhs);
}

template <typename charT, typename traits, typename Alloc>
basic_immutable_string<charT, traits, Alloc>
operator+(std::basic_string<charT, traits, Alloc> const &lhs, basic_immutable_string<charT, traits, Alloc> const &rhs)
{
    return lhs + rhs.c_str();
}

template <typename charT, typename traits, typename Alloc>
basic_immutable_string<charT, traits, Alloc>
operator+(basic_immutable_string<charT, traits, Alloc> const &lhs, basic_immutable_string<charT, traits, Alloc> &&rhs)
{
    return lhs.append(std::forward<basic_immutable_string<charT, traits, Alloc>>(rhs));
}

template <typename charT, typename traits, typename Alloc>
basic_immutable_string<charT, traits, Alloc>
operator+(basic_immutable_string<charT, traits, Alloc> const &lhs, std::basic_string<charT, traits, Alloc> &&rhs)
{
    return lhs.append(std::forward<std::basic_string<charT, traits, Alloc>>(rhs));
}

template <typename charT, typename traits, typename Alloc>
basic_immutable_string<charT, traits, Alloc>
operator+(std::basic_string<charT, traits, Alloc> const &lhs, basic_immutable_string<charT, traits, Alloc> &&rhs)
{
    return lhs + rhs.c_str();
}

template <typename charT, typename traits, typename Alloc>
basic_immutable_string<charT, traits, Alloc>
operator+(basic_immutable_string<charT, traits, Alloc> &&lhs, basic_immutable_string<charT, traits, Alloc> const &rhs)
{
    return lhs.append(rhs);
}

template <typename charT, typename traits, typename Alloc>
basic_immutable_string<charT, traits, Alloc>
operator+(basic_immutable_string<charT, traits, Alloc> &&lhs, std::basic_string<charT, traits, Alloc> const &rhs)
{
    return lhs.append(rhs);
}

template <typename charT, typename traits, typename Alloc>
basic_immutable_string<charT, traits, Alloc>
operator+(std::basic_string<charT, traits, Alloc> &&lhs, basic_immutable_string<charT, traits, Alloc> const &rhs)
{
    return lhs + rhs;
}

template <typename charT, typename traits, typename Alloc>
basic_immutable_string<charT, traits, Alloc>
operator+(basic_immutable_string<charT, traits, Alloc> &&lhs, charT const *rhs)
{
    return lhs.append(rhs);
}

template <typename charT, typename traits, typename Alloc>
basic_immutable_string<charT, traits, Alloc>
operator+(basic_immutable_string<charT, traits, Alloc> const &lhs, charT const *rhs)
{
    return lhs.append(rhs);
}

template <typename charT, typename traits, typename Alloc>
basic_immutable_string<charT, traits, Alloc>
operator+(charT const *lhs, basic_immutable_string<charT, traits, Alloc> &&rhs)
{
    return basic_immutable_string<charT, traits, Alloc>(lhs).append(std::forward<basic_immutable_string<charT, traits, Alloc>>(rhs));
}

template <typename charT, typename traits, typename Alloc>
basic_immutable_string<charT, traits, Alloc>
operator+(charT const *lhs, basic_immutable_string<charT, traits, Alloc> const &rhs)
{
    return basic_immutable_string<charT, traits, Alloc>(lhs).append(rhs);
}

template <typename charT, typename traits, typename Alloc>
basic_immutable_string<charT, traits, Alloc>
operator+(basic_immutable_string<charT, traits, Alloc> &&lhs, charT rhs)
{
    return lhs.append(rhs);
}

template <typename charT, typename traits, typename Alloc>
basic_immutable_string<charT, traits, Alloc>
operator+(basic_immutable_string<charT, traits, Alloc> const &lhs, charT rhs)
{
    return lhs.append(rhs);
}

template <typename charT, typename traits, typename Alloc>
basic_immutable_string<charT, traits, Alloc>
operator+(charT lhs, basic_immutable_string<charT, traits, Alloc> &&rhs)
{
    return basic_immutable_string<charT, traits, Alloc>(lhs).append(std::forward<basic_immutable_string<charT, traits, Alloc>>(rhs));
}

template <typename charT, typename traits, typename Alloc>
basic_immutable_string<charT, traits, Alloc>
operator+(charT lhs, basic_immutable_string<charT, traits, Alloc> const &rhs)
{
    return basic_immutable_string<charT, traits, Alloc>(lhs).append(rhs);
}
#endif

template <class charT, class traits, class Alloc>
std::basic_ostream<charT, traits> &operator<<(std::basic_ostream<charT, traits>& os, basic_immutable_string<charT, traits, Alloc> const &str)
{
    os << str.mutable_string();
    return os;
}

typedef basic_immutable_string<char> immutable_string;

}   // namespace reliablecpp

#include <cassert>
#include <iostream>
#include <cstring>
//#define TEST_COMPILER_ERRORS

int main(int, char *[])
{
#if defined(BOOST_MSVC)  &&  defined(_DEBUG)
    _CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
#endif

    using reliablecpp::immutable_string;

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

