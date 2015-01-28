#ifndef CLASSIC_SORT_HPP
#define CLASSIC_SORT_HPP

#include <iterator>
#include <utility>

#ifdef DEBUG // enables std-err debug output
    #include <iostream>
    #define TRACE(x) \
        std::cerr << __PRETTY_FUNCTION__ << " -- " << x << std::endl;
#else
    #define TRACE(x)
#endif

#ifdef THREAD_CXX11 // enables c++11 parallelism
    #include <thread>
#endif

// helper
template<typename Iterator>
struct FuncType
{
    typedef void (*Two)(Iterator, Iterator);
    static void none(Iterator begin, Iterator end) {}
};

/** Insertion Sorts [@param begin, @param end) in place */
template<typename Iterator>
void insertion_sort(Iterator begin, Iterator end)
{
    for (Iterator border = begin + 1; border != end; ++border)
    {
        Iterator self = border, prev = border - 1;
        if (*prev < *self) continue;

        typename Iterator::value_type save = *border;
        while (save < *prev && self != begin)
            *(self--) = *(prev--);
        *self = save;
    }
}

/** Merges sorted [@param begin, @param mid) and [@param mid, @param end) in
 *  place [@param begin, @param end) */
template<typename Iterator>
void merge(Iterator begin, Iterator mid, Iterator end)
{
    Iterator cbegin = begin; // elements
    while (begin < mid && mid < end)
    {
        if (*cbegin < *mid)
        {
            if (cbegin == begin)
                cbegin++;
            else
                std::swap(*begin, *cbegin);
            begin++;
        }
        else
        {
            if (cbegin == begin) cbegin = mid;
            std::swap(*(begin++), *(mid++));
        }
    }
}

/** Merge Sorts [@param begin, @param end) with optimization @param subsort
 *  on @param threshold */
template<typename Iterator>
void merge_sort(Iterator begin, Iterator end, int threshold = 1,
    typename FuncType<Iterator>::Two subsort = &FuncType<Iterator>::none)
{
    size_t size = std::distance(begin, end);
    if (size <= threshold)
    {
        subsort(begin, end);
        return;
    }

    Iterator mid = begin;
    std::advance(mid, size / 2);

    #ifdef THREAD_CXX11
        void (*sort)(Iterator, Iterator, int, typename FuncType<Iterator>::Two)
            = &merge_sort<Iterator>;

        std::thread t1(sort, begin, mid, threshold, subsort);
        std::thread t2(sort, mid, end, threshold, subsort);

        t1.join(); t2.join();
    #else
        merge_sort(begin, mid, threshold, subsort);
        merge_sort(mid, end, threshold, subsort);
    #endif

    merge(begin, mid, end);
}

/** Simplified Tim Sorts [@param begin, @param end) */
template<typename Iterator>
void simplified_tim_sort(Iterator begin, Iterator end)
{
    typename FuncType<Iterator>::Two subsort = &insertion_sort<Iterator>;
    merge_sort(begin, end, 10, subsort);
}

#endif // CLASSIC_SORT_HPP
