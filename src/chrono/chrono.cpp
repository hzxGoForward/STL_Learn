#include <chrono>
#include <iostream>
#include <iomanip>
#include <ratio>
#include <ctime>
#include <string>

namespace hzx
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

    std::string ToString(const std::chrono::system_clock::time_point &tp)
    {
        const std::time_t t = std::chrono::system_clock::to_time_t(tp);
        // std::string ts = std::ctime(&t);
        std::string ts = std::asctime(gmtime(&t));
        ts.resize(ts.size() - 1);
        return ts;
    }

    void test()
    {
        auto sys_start = std::chrono::steady_clock::now();
        std::ios::sync_with_stdio(false);

        std::cout << "system_clock: " << std::endl;
        hzx::printClockData<std::chrono::system_clock>();

        std::cout << "\nhigh_resolution_clock: " << std::endl;
        hzx::printClockData<std::chrono::high_resolution_clock>();

        std::cout << "\nsteady_clock: " << std::endl;
        hzx::printClockData<std::chrono::steady_clock>();

        

        std::chrono::system_clock::time_point tp;
        std::cout << "epoch: " << hzx::ToString(tp) << std::endl;

        tp = std::chrono::system_clock::time_point::min();
        std::cout << "min: " << hzx::ToString(tp) << std::endl;

        tp = std::chrono::system_clock::time_point::max();
        std::cout << "max: " << hzx::ToString(tp) << std::endl;

        tp = std::chrono::system_clock::now();
        std::cout << "now: " << hzx::ToString(tp) << std::endl;

        // define type for durations that represent day(s):
        auto dur = tp.time_since_epoch();
        typedef std::chrono::duration<int, std::ratio<24 * 365>> Years;
        auto nyears = std::chrono::duration_cast<Years>(dur);
        std::cout << nyears.count() << std::endl;

        auto fifty_years_later = tp + std::chrono::duration<int, std::ratio<3600 * 24 * 365>>(500);
        std::cout << "+500 years: " << hzx::ToString(fifty_years_later) << std::endl;

        auto diff = std::chrono::steady_clock::now() - sys_start;
        auto nano_sec = std::chrono::duration_cast<std::chrono::nanoseconds>(diff);

        std::cout << "this program runs: " << nano_sec.count() << " nanoseconds" << std::endl;
    }

} // namespace hzx
