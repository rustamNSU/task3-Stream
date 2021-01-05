#include "Stream.hpp"
#include "gtest/gtest.h"
#include <iostream>

TEST(Stream, initializer_list_constructor){
    auto s1 = Stream{1, 2, 3, 4, 5};

    std::vector<int> v{1,2,3,4,5};
    Stream<int> svec(v.begin(), v.end());

    std::array<int, 5> arr{1,2,3,4,5};
    Stream<int> sarr(arr.begin(), arr.end());

    Stream<int> sContArr(arr);
    int i = 10;
}

TEST(Stream, print_to){
    auto s1 = Stream{1, 2, 3, 4, 5};
    (s1 | print_to(std::cout)) << std::endl;

    auto result = s1 | map([](int x){return x*x;}) 
                     | filter([](int x){return x%2;})
                     | sum();
                     
    (s1 | print_to(std::cout)) << std::endl;
    EXPECT_EQ(20, result);
}