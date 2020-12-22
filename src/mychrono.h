#include <string>
#include <iostream>
#include <chrono>

namespace hzx_chrono
{
    template <typename C>
    void printClockData()
    {
        using namespace std;

        cout << "- precision: ";
        typedef typename C::period P; // type of time unit
        if (std::ratio_less_equal<P, std::milli>::value)
        {
            typedef typename ratio_multiply<P, kilo>::type TT;
            std::cout << fixed << double(TT::num) / TT::den
                      << " milliseconds" << std::endl;
        }
        else
        {
            std::cout << fixed << double(P::num) / P::den << " seconds" << std::endl;
        }
        std::cout << "- is_steady: " << boolalpha << C::is_steady << std::endl;
    }

    std::string ToString(const std::chrono::system_clock::time_point &tp);

    void test();

}; // namespace hzx_chrono