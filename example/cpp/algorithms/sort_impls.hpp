// Sorting algorithms implementations

#include <algorithm>
#include <vector>
#include <iterator>

namespace sort {

template< typename Iter > void buble( Iter begin, Iter end )
{
    for( auto it = begin + 1; it < end; ++it )
        if( *it < *(it - 1) )
        {
            std::swap( *it, *(it - 1) );
            it = begin;
        }
}

template< typename Iter > void select( Iter begin, Iter end )
{
    for( ; begin != end; ++begin )
    {
        Iter min = begin;
        for( Iter it = begin + 1; it != end; ++it )
            if( *min > *it )
                min = it;
        std::swap( *min, *begin );
    }
}

template< typename Iter > void heep( Iter begin, Iter end )
{
}

template< typename Iter > void quick( Iter begin, Iter end )
{
    static auto _iteration = 0;
    if ( _iteration++ > 10 )
        return;

    size_t size = std::distance( begin, end );
    if( size <= 1 )
        return;

    for(auto it = begin; it != end; ++it )
        std::cout << *it << " ";
    std::cout << "pre" << std::endl;

    Iter left = begin;
    Iter right = end - 2;
    Iter last = end - 1;

   // while( left < right )
    {
        while( *left < *last ) left++;
        while( *right > *last && right >= begin ) right--;
        std::swap( *left, *right );
    }

    std::swap( *left, *last );

    for(auto it = begin; it != end; ++it )
        std::cout << *it << " ";
    std::cout << "post" << std::endl;

    quick( begin, left );
    quick( left + 1, end );
}

template< typename Iter > void merge( Iter begin, Iter end )
{
    size_t size = std::distance( begin, end );
    if( size <= 1 )
    {
        return;
    }
    if( size == 2 )
    {
        auto& first = *begin, second = *(begin + 1);
        if( first > second )
            std::swap( first, second );
        return;
    }

    Iter mid = begin + size / 2;
    merge( begin, mid );
    merge( mid, end );

    Iter first = begin, second = mid;
    std::vector< typename Iter::value_type > result;
    result.reserve( size );

    while( first != mid || second != end )
    {
        if( first == mid )
            result.push_back( *( second++ ) );
        else
        if( second == end )
            result.push_back( *( first++ ) );
        else
        if( *first < *second )
            result.push_back( *( first++ ) );
        else
            result.push_back( *( second++ ) );
    }

    for( auto it = result.begin(); it != result.end(); it++, begin++ )
        *begin = *it;
}

} // namespace sort
