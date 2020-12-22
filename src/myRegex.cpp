#include "myRegex.h"
#include <string>
#include <regex>
#include <iostream>
#include <iomanip>
#ifdef _MSC_BUILD
#pragma execution_character_set("utf-8")
#endif
namespace hzx_regex
{

    void out(bool b)
    {
        std::cout << (b ? "found" : "not found") << std::endl;
    }

    void test2()
    {
        std::string data = "XML tag: <tag-name>the value</tag-name>the value";
        std::cout << "data:                       " << data << "\n\n";

        //
        std::smatch m;
        bool found = std::regex_search(data, m, std::regex("<(.*)>(.*)</\\1>\\2"));
        out(found);

        std::cout << "m.empty():    " << std::boolalpha << m.empty() << std::endl;

        std::cout << "m.size():    " << m.size() << std::endl;

        if (found)
        {
            std::cout << "m.str():    " << m.str() << std::endl;
            std::cout << "m.length():    " << m.length() << std::endl;
            std::cout << "m.position():    " << m.position() << std::endl;
            std::cout << "m.prefix().str():    " << m.prefix().str() << std::endl;
            std::cout << "m.suffix().str():    " << m.suffix().str() << std::endl;
            std::cout << std::endl;

            for (int i = 0; i < m.size(); ++i)
            {
                std::cout << "m[" << i << "].str(): " << m[i].str() << std::endl;
                std::cout << "m.str(" << i << "): " << m.str(i) << std::endl;
                std::cout << "m.position(" << i << "): " << m.position(i)
                          << std::endl;
            }
            std::cout << std::endl;

            // iterating over all matches (using iterators):
            std::cout << "matches: " << std::endl;
            for (auto pos = m.begin(); pos != m.end(); ++pos)
            {
                std::cout << " " << *pos << " ";
                std::cout << "(lenght: " << pos->length() << ")" << std::endl;
            }
        }
    }

    void test()
    {
        std::string str("<tage>value</tag>");
        std::regex reg1("<.*>.*</.*>");
        bool found = std::regex_match(str, reg1);
        out(found);

        // () represents group, itself is not a symblole. \\1 represent to refer the first ().
        std::regex reg2("<(.*)>.*</\\1>");
        found = std::regex_match(str, reg2);
        out(found);

        std::regex reg3("<\\(.*\\)>.*</\\1>", std::regex_constants::grep);
        found = std::regex_match(str, reg3);
        out(found);

        found = std::regex_match(str, std::regex(R"(<(.*)>.*</\1>)")); // regular expression
        out(found);
        std::cout << std::endl;

        found = std::regex_match("XML tag: <tag>value</tag>",
                                 std::regex("<(.*)>.*</\\1>")); // fails to match
        out(found);

        found = std::regex_match("XML tag: <tag>value</tag>",
                                 std::regex(".*<(.*)>.*</\\1>.*")); // matches
        out(found);

        found = std::regex_search("XML tag: <tag>value</tag>",
                                  std::regex("<(.*)>.*</\\1>")); // matches
        out(found);

        found = std::regex_search("XML tag: <tag>value</tag>",
                                  std::regex(".*<(.*)>.*</\\1>")); // matches
        out(found);

        found = std::regex_match("", std::regex(".*"));
        out(found);

        std::cout << "test2------------\n";
        test2();
    }

}; // namespace hzx_regex
