#if !defined(VECTOR_HPP)
#define VECTOR_HPP

#include <memory>
#include <type_traits>
#include <concepts>
#include <limits>
#include <stdexcept>
#include <new>
#include <initializer_list>
#include <memory>

template< typename T >
class random_access_iterator;

template< typename T, typename Allocator = std::allocator<T> >
requires std::copy_constructible<T>
class vector {
    static_assert(std::is_copy_assignable<T>::value, "error: no copy assignment operator");
public:
    typedef T value_type;
    typedef Allocator allocator_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef typename std::allocator_traits<Allocator>::pointer pointer;
    typedef typename std::allocator_traits<Allocator>::const_pointer const_pointer;
    typedef random_access_iterator<T> iterator; 

private:
    void reallocate() {
        size_type new_capacity = m_capacity * 2;
        T* new_base = nullptr;
        try {
            new_base = m_allocator.allocate( new_capacity );
        } catch( std::bad_array_new_length const& err ){
            std::cerr << err.what() << ": not enoght memory to allocate\n"; 
        }
        for( size_type i = 0; i < m_size; ++i ){
            new_base[i] = m_base[i];
        }
        m_allocator.deallocate(m_base, m_capacity);
        m_base = new_base;
        m_capacity = new_capacity;
    }

public:
    vector() :
        m_base{ nullptr }, 
        m_allocator{},
        m_size{}, 
        m_capacity{}
    {}
    vector(std::initializer_list<T> l) {
        size_type lsize = l.size();
        m_base = m_allocator.allocate(lsize);
        m_size = lsize;
        m_capacity = lsize;

        auto from = l.begin();
        auto to = this->begin();

        while( from != l.end() ){
            (*to++) = (*from++);
        }
    }
    ~vector() {
        m_allocator.deallocate( m_base, m_capacity );
    }
    constexpr vector& operator=( const vector<T>& other ) {
        if( this == &other ){
            return *this;
        }
        this->clear();
        for ( auto& elem : other ) {
            this->push_back(elem);
        }
        return *this; 
    }
    constexpr vector& operator=( vector<T>&& other ){
        for( auto&& elem : other ){
            this->emplace( std::move(elem) );
        } 
    }

    //element access
    reference at( size_type pos ) {
        if( pos > m_size - 1 ){
           throw std::out_of_range( "error: out of range" ); 
        }
        return m_base[pos];
    }
    reference operator[]( size_type i ) {
        return m_base[i];
    }
    reference front() {
        return m_base[0];
    }
    reference back() {
        return m_base[m_size];
    }

    //iterators
    iterator begin() {
        return iterator( m_base ); 
    }
    iterator end() {
        return iterator( m_base + m_size );
    }

    //capacity
    bool empty() const {
        return m_size;
    }
    size_type max_size() const {
        return std::numeric_limits<std::size_t>::max() / sizeof(value_type);
    }
    size_type capacity() const {
        return m_capacity;
    }
    T* data() {
        return m_base;
    }
    void shrink_to_fit() {
        T* new_base = m_allocator.allocate( m_size );
        for( size_type i = 0; i < m_size; ++i ){
            new_base[i] = m_base[i];
        }
        m_allocator.deallocate( m_base, m_capacity );

        m_base = new_base;
        m_capacity = m_size;
    }

    //modifiers
    void push_back( const T& value ) {
        if( m_size == m_capacity ){
            reallocate();
        }
        m_base[m_size++] = value;
    }
    void pop_back() {
        m_base[m_size--] = value_type();
    }
    iterator emplace( iterator pos, T&& value ){
        *(--pos) = std::move(value);
        return pos;
    }
    void clear() {
        m_allocator.deallocate( m_base, m_capacity );
        m_base = m_allocator.allocate( m_capacity );
        m_size = 0;
    }

private:
    pointer m_base;
    Allocator m_allocator;
    size_type m_size;
    size_type m_capacity;
};

template< typename T > using vector_value_t = typename vector<T>::value_type;
template< typename T > using vector_allocator_t = typename vector<T>::allocator_type;
template< typename T > using vector_size_t = typename vector<T>::size_type;
template< typename T > using vector_diff_t = typename vector<T>::difference_type;
template< typename T > using vector_ref_t = typename vector<T>::reference;
template< typename T > using vector_const_ref_t = typename vector<T>::const_reference;
template< typename T > using vector_ptr_t = typename vector<T>::pointer;
template< typename T > using vector_const_ptr_t = typename vector<T>::const_pointer;
template< typename T > using vector_iterator_t = typename vector<T>::iterator;

template< typename T >
class random_access_iterator {
public:
    random_access_iterator( vector_ptr_t<T> ptr ) :
        m_ptr( ptr ) 
    {}

    vector_ref_t<T> operator*()
    {
        return *m_ptr;
    }
    vector_ptr_t<T> operator->()
    {
        return m_ptr;
    }
    vector_iterator_t<T>& operator++() 
    {
        ++m_ptr;
        return *this;
    }
    vector_iterator_t<T> operator++(int)
    {
        vector_iterator_t<T> temp{ *this };
        ++(*this);
        return temp;
    }
    vector_iterator_t<T>& operator+=( vector_diff_t<T> n )
    {
        vector_diff_t<T> m = n;

        if( m >= 0 ) while( m-- ) ++m_ptr;
        else while( m++ ) --m_ptr;
        return *this;
    }
    friend vector_iterator_t<T> operator+( vector_diff_t<T> lhs, vector_iterator_t<T> rhs )
    {
        rhs += lhs;
        return rhs;
    }
    friend vector_iterator_t<T> operator+( vector_iterator_t<T> lhs, vector_diff_t<T> rhs )
    {
        return operator+( rhs, lhs );
    }
    vector_iterator_t<T> operator--()
    {
        --m_ptr;
        return *this;
    }
    vector_iterator_t<T> operator--(int)
    {
        vector_iterator_t<T> temp = *this;
        --(*this);
        return temp;
    }
    vector_iterator_t<T>& operator-=( vector_diff_t<T> n )
    {
        return operator+=(-n);
    }
    friend vector_iterator_t<T> operator-( vector_diff_t<T> lhs, vector_iterator_t<T> rhs )
    {
        rhs -= lhs;
        return rhs;
    }
    friend vector_iterator_t<T> operator-( vector_iterator_t<T> lhs, vector_diff_t<T> rhs )
    {
        return operator-( rhs, lhs );
    }
    vector_diff_t<T> operator-( vector_iterator_t<T> other )
    {
        vector_diff_t<T> n{};

        if( this->m_ptr > other.m_ptr ) while( (*this)++ != other.m_ptr ) n++;
        else while( (*this)++ != other.m_ptr ) n--;
        return n;
    }
    // must be convertible to reference
    vector_iterator_t<T> operator[]( vector_diff_t<T> i )
    {
        return { m_ptr + i };
    }

    bool operator<( vector_iterator_t<T> other )
    {
        return this->m_ptr - other.m_ptr < 0;
    }
    bool operator<=( vector_iterator_t<T> other )
    {
        return !( this->m_ptr > other.m_ptr );
    }
    bool operator>( vector_iterator_t<T> other )
    {
        return this->m_ptr - other.m_ptr > 0;
    }
    bool operator>=( vector_iterator_t<T> other )
    {
        return !operator<( other );
    }
    bool operator==( vector_iterator_t<T> other )
    {
        return this->m_ptr == other.m_ptr;
    } 
    bool operator!=( vector_iterator_t<T> other )
    {
        return !operator==( other.m_ptr ); 
    }

private:
    vector_ptr_t<T> m_ptr;
};

#endif // VECTOR_HPP
