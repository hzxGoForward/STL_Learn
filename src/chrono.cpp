#include <chrono>
#include <iostream>
#include <iomanip>
#include <ratio>
#include <ctime>
#include <string>
#include <../include/chrono.h>

namespace hzx_chrono
{

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
        hzx_chrono::printClockData<std::chrono::system_clock>();

        std::cout << "\nhigh_resolution_clock: " << std::endl;
        hzx_chrono::printClockData<std::chrono::high_resolution_clock>();

        std::cout << "\nsteady_clock: " << std::endl;
        hzx_chrono::printClockData<std::chrono::steady_clock>();

        

        std::chrono::system_clock::time_point tp;
        std::cout << "epoch: " << hzx_chrono::ToString(tp) << std::endl;

        tp = std::chrono::system_clock::time_point::min();
        std::cout << "min: " << hzx_chrono::ToString(tp) << std::endl;

        tp = std::chrono::system_clock::time_point::max();
        std::cout << "max: " << hzx_chrono::ToString(tp) << std::endl;

        tp = std::chrono::system_clock::now();
        std::cout << "now: " << hzx_chrono::ToString(tp) << std::endl;

        // define type for durations that represent day(s):
        auto dur = tp.time_since_epoch();
        typedef std::chrono::duration<int, std::ratio<24 * 365>> Years;
        auto nyears = std::chrono::duration_cast<Years>(dur);
        std::cout << nyears.count() << std::endl;

        auto fifty_years_later = tp + std::chrono::duration<int, std::ratio<3600 * 24 * 365>>(500);
        std::cout << "+500 years: " << hzx_chrono::ToString(fifty_years_later) << std::endl;

        auto diff = std::chrono::steady_clock::now() - sys_start;
        auto nano_sec = std::chrono::duration_cast<std::chrono::nanoseconds>(diff);

        std::cout << "this program runs: " << nano_sec.count() << " nanoseconds" << std::endl;
    }

} // namespace hzx_chrono
