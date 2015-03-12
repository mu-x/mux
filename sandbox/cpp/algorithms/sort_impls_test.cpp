#include <algorithm>
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "sort_impls.hpp"

template< typename T > bool container_cmp( const T& c1, const T& c2 )
{
    if( c1.size() != c2.size() )
        return false;
    for( auto i1 = c1.begin(), i2 = c2.begin(); i1 != c1.end(); ++i1, ++i2)
        if( *i1 != *i2 )
            return false;
    return true;
}

template< typename T > std::string container_str( const T& c )
{
    if( c.empty() )
        return "EMPTY";
    std::stringstream ss;
    ss << "{ " << c.front();
    for( auto i = c.begin() + 1; i != c.end(); ++i )
        ss << ", " << *i;
    ss << " }";
    return ss.str();
}

template< typename T > void container_assert( const T& c1, const T& c2 )
{
    std::cout << ( container_cmp( c1, c2 ) ? "PASSED: " : "FAILED: " )
              << container_str( c2 ) << std::endl;
}

#define ASSERT_ALG(alg, container, std_sort)    \
{                                               \
    auto cpy = container;                       \
    alg( cpy.begin(), cpy.end() );              \
    std::cout << std::setw(8) << #alg << ": ";  \
    container_assert( std_sort, cpy );          \
}

int main()
{
    const std::vector< std::vector< int > > tests =
    {
        { 3, 5, 2, 5, 7, 3 ,34, -2 ,1 ,4 },
        { 33 },
        { },
    };
    for( auto v = tests.begin(); v != tests.end(); ++v )
    {
        auto std_sort = *v;
        std::sort( std_sort.begin(), std_sort.end() );

        ASSERT_ALG( std::sort,      *v, std_sort );
        ASSERT_ALG( sort::buble,    *v, std_sort );
        ASSERT_ALG( sort::select,   *v, std_sort );
        ASSERT_ALG( sort::heep,     *v, std_sort );
        ASSERT_ALG( sort::quick,    *v, std_sort );
        ASSERT_ALG( sort::merge,    *v, std_sort );
    }
}
