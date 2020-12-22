#include <future>
#include <thread>
#include <chrono>
#include <random>
#include <iostream>
#include <exception>

namespace hzx_async
{

    int doSomething(const char c, const size_t sec = 10);
    void outputSomething(const char c, std::shared_future<int> f);

    int func1();
    int func2();
    int func(const char c, const int sec = 10);
    
    void test();

    int queryNumber();
    // test is an example of shared_future
    void test2();
}; // namespace hzx_async
