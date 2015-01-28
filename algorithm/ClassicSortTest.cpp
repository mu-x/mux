#include "ClassicSort.hpp"

#include <iostream>
#include <vector>

template<typename Iterator>
void print(Iterator begin, Iterator end)
{
    while (begin != end)
        std::cout << *(begin++) << " ";
    std::cout << std::endl;
}

int main()
{
    int raw[] = { 2, 4, 5, 7, 3, 6, 10, 1, 2, 2, 6 };
    size_t raw_size = sizeof(raw) / sizeof(int);

    std::vector<int> arr(raw, raw + raw_size);
    print(arr.begin(), arr.end());

    simplified_tim_sort(arr.begin(), arr.end());
    print(arr.begin(), arr.end());
}
