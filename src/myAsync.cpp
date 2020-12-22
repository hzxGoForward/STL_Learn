#include "myAsync.h"
#include <vector>

// STL 18.1
/*
If you start to use async(), you should pass all objects necessary to
process the passed functionality by value so that async() uses only local copies.

If copying is
too expensive, ensure that the objects are passed as constant reference and that mutable is not used.

*/
namespace hzx_async
{
    int doSomething(const char c, const size_t sec)
    {
        // random-number generator(use c as seed to get different sequences)
        std::default_random_engine dre(c);

        std::uniform_int_distribution<int> id(10, 1000);

        for (size_t i = 0; i < sec; ++i)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(id(dre)));
            std::cout.put(c).flush();
        }
        return c;
    }

    void outputSomething(const char c, std::shared_future<int> f)
    {
        try
        {
            // wait for number of characters to print
            int num = f.get(); //get result of queryNumber()

            for (int i = 0; i < num; ++i)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                std::cout.put(c).flush();
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << "EXCEPTION in thread " << std::this_thread::get_id()
                      << ": " << e.what() << std::endl;
        }
    }

    int func1()
    {
        return doSomething('*');
    }

    int func2()
    {
        return doSomething('+');
    }

    int func(const char c, const int sec)
    {
        return doSomething(c, sec);
    }

    void test()
    {
        // start a lot of thread to occupy all the cores.
        std::vector<std::future<int>> vecFuture;
        for (size_t i = 0; i < std::thread::hardware_concurrency(); ++i)
        {
            const char c = static_cast<char>('a' + i);
            vecFuture.emplace_back(std::future<int>(std::async(std::launch::async, func, c, 20)));
        }

        std::cout << "start func1() * with async and policy async way in background" << std::endl;
        std::cout << "start func2() + in foreground: " << std::endl;
        std::cout << "start func() ? with async and policy default way in background" << std::endl;

        // start func1 async
        std::future<int> result1(std::async(std::launch::async, func1));
        std::future<int> result3(std::async(func, '?', 20));
        int result2 = func2();
        int result = result1.get() + result2;

        std::cout << "\nresult of func1()+func2(): " << result2 << std::endl;
        const size_t n_thread_cnt = std::thread::hardware_concurrency();
        std::cout << "concurrency thread count " << n_thread_cnt << std::endl;

        std::cout << "the result3 is " << result3.get() << std::endl;
        std::cout << "result3 is valid: " << result3.valid() << std::endl;

        try
        {
            // get result3's result again to trigger a exception
            const int a = result3.get();
        }
        catch (const std::exception &e)
        {
            // the exception is no state
            std::cerr << "Exception in thread " << std::this_thread::get_id()
                      << ": " << e.what() << std::endl;
        }
    }

    int queryNumber()
    {
        // read number
        std::cout << "read number:";
        int num;
        std::cin >> num;

        // throw exception if none;
        if (!std::cin)
        {
            throw std::runtime_error("no number read");
        }
        return num;
    }
    void test2()
    {

        try
        {
            std::shared_future<int> f = std::async(queryNumber);
            auto f1 = std::async(std::launch::async, outputSomething, '.', f);
            auto f2 = std::async(std::launch::async, outputSomething, '+', f);
            auto f3 = std::async(std::launch::async, outputSomething, '*', f);

            // wait for all loops to be finished
            f1.get();
            f2.get();
            f3.get();
        }
        catch (const std::exception &e)
        {
            std::cout << "\nEXCEPTION: " << e.what() << std::endl;
        }
        std::cout << "\ndone" << std::endl;
    }

}; // namespace hzx_async
