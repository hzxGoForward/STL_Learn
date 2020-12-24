#pragma once
#include <boost/program_options.hpp>


namespace hzx_cmd_parser {
	void regist_and_parse(int argc, char* argv[], boost::program_options::variables_map& vm);

	void test(int argc, char* argv[]);
};
