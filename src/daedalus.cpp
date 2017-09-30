#include <iostream>
#include <string>

#include "./../lib/easylogging++.h"

#include "./input_parser.hpp"
#include "./network/network_simulator.hpp"

INITIALIZE_EASYLOGGINGPP

void print_help();
void print_configuration(network::network_config* network_config);

int main(int argc, char const *argv[]) {
    input_parser parser(argc, argv);

    if (parser.cmd_option_exists("-h")) {
        print_help();
        return 0;
    }

    START_EASYLOGGINGPP(argc, argv);

    /**************************************************************
    **************             READ INPUT            **************
    **************************************************************/
    network::network_config network_config;

    network_config.policy_name = "NO_POLICY";

    if (parser.cmd_option_exists("-tn")) {
        network_config.policy_name = parser.get_cmd_option("-tn");
    }

    print_configuration(&network_config);

    /**************************************************************
    **************         START SIMULATION          **************
    **************************************************************/
    LOG(INFO) << "[DAEDALUS] Setting up network simulator";
    network::network_simulator simulator(network_config);

    LOG(INFO) << "[DAEDALUS] Starting simulation";
    simulator.start();

    return 0;
}

void print_configuration(network::network_config* network_config) {
    LOG(INFO) << "[DAEDALUS][CONFIG] "
        << "Policy: "
        << network_config->policy_name;
}

void print_help() {
    std::cout << "OVERVIEW: Daedalus is an Information Centric Network simulator." << std::endl;
    std::cout << std::endl;
    std::cout << "USAGE: daedalus [options]" << std::endl;
    std::cout << std::endl;
    std::cout << "OPTIONS:" << std::endl;
    std::cout << std::endl;
    std::cout << "-p <arg>" << "\t" << "Policy name. Supported values are: NO_POLICY" << std::endl;
}