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

    if (parser.cmd_option_exists("-p")) {
        network_config.policy_name = parser.get_cmd_option("-p");
    }

    if (parser.cmd_option_exists("-ts")) {
        network_config.network_three_size = stoi(parser.get_cmd_option("-ts"));
    }

    if (parser.cmd_option_exists("-np")) {
        network_config.number_of_packets = stoi(parser.get_cmd_option("-np"));
    }

    if (parser.cmd_option_exists("-rs")) {
        network_config.round_size = stoi(parser.get_cmd_option("-rs"));
    }

    if (parser.cmd_option_exists("-ws")) {
        network_config.warmup_size = stoi(parser.get_cmd_option("-ws"));
    }

    print_configuration(&network_config);

    /**************************************************************
    **************         START SIMULATION          **************
    **************************************************************/
    VLOG(0) << "[DAEDALUS] Setting up network simulator";
    network::network_simulator simulator(network_config);

    VLOG(0) << "[DAEDALUS] Starting simulation";
    simulator.start();

    return 0;
}

void print_configuration(network::network_config* network_config) {
    VLOG(0) << "[DAEDALUS][CONFIG] "
        << "Policy: "
        << network_config->policy_name;

    VLOG(0) << "[DAEDALUS][CONFIG] "
        << "Number of nodes in the network three under the target node: "
        << network_config->network_three_size;

    VLOG(0) << "[DAEDALUS][CONFIG] "
        << "Number of unique packets: "
        << network_config->number_of_packets;

    VLOG(0) << "[DAEDALUS][CONFIG] "
        << "How many packets will be used during simulation: "
        << network_config->round_size;

    VLOG(0) << "[DAEDALUS][CONFIG] "
        << "Percentage of packets used during warm up: "
        << network_config->warmup_size;
}

void print_help() {
    network::network_config network_config;

    std::cout << "OVERVIEW: Daedalus is an Information Centric Network simulator." << std::endl;
    std::cout << std::endl;

    std::cout << "USAGE: daedalus [options]" << std::endl;
    std::cout << std::endl;

    std::cout << "OPTIONS:" << std::endl;
    std::cout << "-p  <arg>   Policy name. Default: "                                                << network_config.policy_name        << std::endl;
    std::cout << "-ts <arg>   Number of nodes in the network three under the target node. Default: " << network_config.network_three_size << std::endl;
    std::cout << "-np <arg>   Number of unique packets. Default: "                                   << network_config.number_of_packets  << std::endl;
    std::cout << "-rs <arg>   Number of packets used during simulation. Default: "                   << network_config.round_size         << std::endl;
    std::cout << "-ws <arg>   Number of packets used during warm-up. Default: "                      << network_config.warmup_size        << std::endl;

    std::cout << std::endl;
    std::cout << "LOGGING OPTIONS:" << std::endl;
    std::cout << "--v=<arg>   Verbosity Level. Default: 0. Possible options: 0 (INFO), 9 (DEBUG)"  << std::endl;
}