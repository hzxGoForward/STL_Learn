#include <iostream>
#include <cstdlib>
#include <string>
#include <memory>
#include "cmd_parser.h"

namespace hzx_cmd_parser {

	void regist_and_parse(int argc, char* argv[], boost::program_options::variables_map& vm) {
		namespace bp = boost::program_options;
		bp::options_description all("Ethereum RPC API");
		bp::options_description general("General options");
		bp::options_description common("Common options");

		// clang-format off
		general.add_options()
			("help", "help message")
			("eth_blockNumber", "eth_blockNumber api")
			("eth_getBalance", "eth_getBalance api")
			("eth_getBlockByNumber", "eth_getBlockByNumber api")
			("eth_sendTransaction", "eth_sendTransaction api")
			("eth_call", "eth_sendTransaction api")
			("eth_getTransactionByHash", "eth_getTransactionByHash api");

		common.add_options()
			("address", bp::value<std::string>(), "account address")
			("height", bp::value<uint64_t>(), "block height");

		common.add_options()
			("txhash", bp::value<std::string>(), "transaction hash");

		common.add_options()
			("method", bp::value<std::string>(), "contract method")
			("from", bp::value<std::string>(), "source address")
			("to", bp::value<std::string>(), "target address")
			("value", bp::value<uint64_t>(), "transaction value")
			("data", bp::value<std::string>(), "transaction payload")
			("file", bp::value<std::string>(), "transaction payload file");
		// clang-format on

		all.add(general).add(common);
		bp::store(bp::parse_command_line(argc, argv, all), vm);
	}


	void test(int argc, char* argv[]) {
		namespace bp = boost::program_options;
		bp::variables_map vm;
		try {
			regist_and_parse(argc, argv, vm);
		}
		catch (...) {
			std::cout << "invalid cmd line parameters!" << std::endl;
			exit(-1);
		}

		if (vm.count("eth_blockNumber")) {
			std::cout << "block height: 656578" << std::endl;
		}
		else if (vm.count("eth_getBalance")) {
			auto addr = vm["address"].as<std::string>();
			auto height = vm["height"].as<uint64_t>();
			std::cout << "addr: " << addr << "height: " << height << std::endl;
		}
	}
};
