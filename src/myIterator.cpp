#include "../include/myIterator.h"
#include <vector>
#include <list>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <iterator>

namespace hzx_iterator
{
    void test()
    {
        std::list<int> coll1 = {1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16};
        std::vector<int> coll2;
        std::vector<int> coll3;
        auto s1 = std::chrono::steady_clock::now();
        
        coll2.insert(coll2.cend(), coll1.cbegin(), coll1.cend());
        auto s2 = std::chrono::steady_clock::now();
        
        std::copy(coll1.cbegin(),coll1.cend(), std::back_inserter(coll3));
        auto s3 = std::chrono::steady_clock::now();

        std::cout<<"coll2: ";
        for(auto&e:coll2)
            std::cout<<e<<" ";
        std::cout<<std::endl;
        std::cout<<"insert algorithm constct coll2 use "<< std::chrono::duration_cast<std::chrono::nanoseconds>(s2-s1).count()<<" ms\n";

        std::cout<<"coll3: ";
        for(auto&e:coll2)
            std::cout<<e<<" ";
        std::cout<<std::endl;
        
        std::cout<<"copy algorithm constct coll3 use "<< std::chrono::duration_cast<std::chrono::nanoseconds>(s3-s2).count()<<" ms\n";
        
    }
}; // namespace hzx_iterator